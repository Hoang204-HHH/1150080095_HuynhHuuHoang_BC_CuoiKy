#!/usr/bin/env node
/**
 * @file run-cbmc.js
 * @brief Runner tự động hóa cho project CBMC.
 *
 * Triết lý báo cáo của bản hoàn thiện:
 * - 19 testcase an toàn / hợp lệ => nếu CBMC SUCCESSFUL thì kết luận QA là Pass.
 * - 3 testcase demo defect (TC19, TC20, TC22) => nếu CBMC FAILED thì vẫn ghi
 *   "Trạng thái TC = Fail" vì module đang có lỗi đúng như mục tiêu minh họa.
 * - Đồng thời vẫn lưu cột "Khớp kỳ vọng kỹ thuật" để phân biệt:
 *   + FAIL đúng chủ đích
 *   + FAIL ngoài dự kiến
 */

const fs = require("fs");
const path = require("path");
const { spawnSync } = require("child_process");

const projectRoot = path.resolve(__dirname, "..", "..");
const configPath = path.join(projectRoot, "automation", "config", "testcases.json");
const bugsPath = path.join(projectRoot, "automation", "config", "bugs.json");
const outputDir = path.join(projectRoot, "output");
const logsDir = path.join(outputDir, "logs");

const args = process.argv.slice(2);
const dryRun = args.includes("--dry-run");
const idIndex = args.indexOf("--id");
const selectedId = idIndex >= 0 ? args[idIndex + 1] : null;

function ensureDir(dirPath) {
  fs.mkdirSync(dirPath, { recursive: true });
}

function loadJson(filePath) {
  return JSON.parse(fs.readFileSync(filePath, "utf8"));
}

function parseVerification(output) {
  if (output.includes("VERIFICATION SUCCESSFUL")) return "VERIFICATION SUCCESSFUL";
  if (output.includes("VERIFICATION FAILED")) return "VERIFICATION FAILED";
  return "UNKNOWN";
}

function csvEscape(value) {
  const text = String(value ?? "");
  if (text.includes(",") || text.includes('"') || text.includes("\n")) {
    return `"${text.replace(/"/g, '""')}"`;
  }
  return text;
}

function writeCsv(filePath, headers, rows) {
  const lines = [];
  lines.push(headers.map(csvEscape).join(","));
  for (const row of rows) {
    lines.push(headers.map((h) => csvEscape(row[h])).join(","));
  }
  fs.writeFileSync(filePath, "\ufeff" + lines.join("\n"), "utf8");
}

function findCbmc() {
  const result = spawnSync("cbmc", ["--version"], { encoding: "utf8" });
  if (result.error) return null;
  return (result.stdout || result.stderr || "").trim();
}

function evaluateRow(tc, actualVerification) {
  const technicalMatch = actualVerification === tc.expectedVerification;
  if (!technicalMatch) {
    return {
      qaStatus: "Fail",
      technicalMatch: "Không",
      verdictNote: "Kết quả thực tế không khớp kỳ vọng kỹ thuật"
    };
  }

  return {
    qaStatus: tc.qaStatus,
    technicalMatch: "Có",
    verdictNote:
      tc.qaStatus === "Fail"
        ? "Ca defect demo: công cụ bắt đúng lỗi nên testcase vẫn được ghi nhận là Fail ở góc nhìn QA"
        : "Ca hợp lệ chạy đúng như kỳ vọng"
  };
}

function buildMarkdownSummary(results, meta) {
  const total = results.length;
  const passed = results.filter((r) => r["Trạng thái TC"] === "Pass").length;
  const failed = results.filter((r) => r["Trạng thái TC"] === "Fail").length;
  const notRun = results.filter((r) => r["Trạng thái TC"] === "Not Run").length;
  const technicalMatch = results.filter((r) => r["Khớp kỳ vọng kỹ thuật"] === "Có").length;

  return [
    "# Test Execution Summary",
    "",
    `- Thời gian tạo báo cáo: ${new Date().toISOString()}`,
    `- Node.js: ${process.version}`,
    `- CBMC: ${meta.cbmcVersion || "không tìm thấy trong PATH"}`,
    `- Dry run: ${meta.dryRun ? "Có" : "Không"}`,
    `- Tổng số testcase: ${total}`,
    `- Pass (QA): ${passed}`,
    `- Fail (QA): ${failed}`,
    `- Not Run: ${notRun}`,
    `- Khớp kỳ vọng kỹ thuật: ${technicalMatch}/${total}`,
    "",
    "## Diễn giải",
    "",
    "- `Trạng thái TC = Pass` nghĩa là hàm/hành vi được kiểm chứng là đạt.",
    "- `Trạng thái TC = Fail` trong 3 ca TC19, TC20, TC22 là **có chủ đích**, dùng để minh họa bug buffer overflow / off-by-one.",
    "- Nếu chạy `--dry-run`, script chỉ kiểm tra cấu hình và sinh command, không có verdict thực tế.",
    "",
  ].join("\n");
}

function main() {
  ensureDir(outputDir);
  ensureDir(logsDir);

  const testcases = loadJson(configPath);
  const bugs = loadJson(bugsPath);
  const filtered = selectedId ? testcases.filter((tc) => tc.id === selectedId) : testcases;

  if (selectedId && filtered.length === 0) {
    console.error(`Khong tim thay testcase: ${selectedId}`);
    process.exit(1);
  }

  let cbmcVersion = null;
  if (!dryRun) {
    cbmcVersion = findCbmc();
    if (!cbmcVersion) {
      console.error("Khong tim thay lenh 'cbmc' trong PATH. Hay cai CBMC roi thu lai.");
      process.exit(1);
    }
  }

  const rows = [];

  for (const tc of filtered) {
    const harnessPath = path.join(projectRoot, "tests", tc.harness);
    const sourcePath = path.join(projectRoot, tc.source);
    const commandArgs = [harnessPath, sourcePath, ...tc.cbmcArgs];
    const logPath = path.join(logsDir, `${tc.id}.log`);

    let actualVerification = "DRY RUN";
    let testcaseStatus = "Not Run";
    let technicalMatch = "N/A";
    let verdictNote = "Chưa chạy";
    let exitCode = "";
    let commandLine = `cbmc ${commandArgs.map((x) => `"${x}"`).join(" ")}`;
    let rawOutput = "";

    if (dryRun) {
      rawOutput = "[DRY RUN] " + commandLine;
      fs.writeFileSync(logPath, rawOutput, "utf8");
    } else {
      const result = spawnSync("cbmc", commandArgs, { encoding: "utf8", maxBuffer: 1024 * 1024 * 20 });
      exitCode = result.status;
      rawOutput = (result.stdout || "") + "\n" + (result.stderr || "");
      actualVerification = parseVerification(rawOutput);
      fs.writeFileSync(logPath, rawOutput, "utf8");

      const evaluated = evaluateRow(tc, actualVerification);
      testcaseStatus = evaluated.qaStatus;
      technicalMatch = evaluated.technicalMatch;
      verdictNote = evaluated.verdictNote;
    }

    rows.push({
      "TC ID": tc.id,
      "Tên TC": tc.name,
      "Module": tc.module,
      "Loại test": tc.type,
      "Kỹ thuật": tc.technique,
      "Kỳ vọng CBMC": tc.expectedVerification,
      "Kết quả thực tế": actualVerification,
      "Trạng thái TC": testcaseStatus,
      "Khớp kỳ vọng kỹ thuật": technicalMatch,
      "Exit code": exitCode,
      "Log file": path.relative(projectRoot, logPath).replace(/\\/g, "/"),
      "Command": commandLine,
      "Ghi chú": tc.note,
      "Phân tích": verdictNote
    });
  }

  writeCsv(path.join(outputDir, "test-execution-results.csv"), Object.keys(rows[0]), rows);
  fs.writeFileSync(path.join(outputDir, "test-execution-results.json"), JSON.stringify(rows, null, 2), "utf8");
  fs.writeFileSync(path.join(outputDir, "summary.md"), buildMarkdownSummary(rows, { cbmcVersion, dryRun }), "utf8");

  const executedBugRows = bugs.map((bug) => {
    const matched = rows.find((r) => r["TC ID"] === bug["Testcase liên quan"]);
    return {
      ...bug,
      "Kết quả chạy testcase liên quan": matched ? `${matched["TC ID"]}: ${matched["Kết quả thực tế"]}` : "Chưa chạy",
      "Link log": matched ? matched["Log file"] : ""
    };
  });
  writeCsv(path.join(outputDir, "bug-report-results.csv"), Object.keys(executedBugRows[0]), executedBugRows);

  console.log(`Da tao bao cao tai: ${path.relative(projectRoot, outputDir)}`);
}

main();
