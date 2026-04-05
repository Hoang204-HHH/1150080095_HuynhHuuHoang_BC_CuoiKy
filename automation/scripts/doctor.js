#!/usr/bin/env node
/**
 * @file doctor.js
 * @brief Kiểm tra nhanh project trước khi chạy CBMC thật.
 *
 * Nội dung kiểm tra:
 * - JSON hợp lệ
 * - File harness/source tồn tại
 * - Đúng 22 testcase
 * - Đúng 3 testcase có qaStatus = Fail
 * - Nếu có gcc: chạy syntax check cho tất cả file C
 */

const fs = require("fs");
const path = require("path");
const { spawnSync } = require("child_process");

const projectRoot = path.resolve(__dirname, "..", "..");
const testsPath = path.join(projectRoot, "automation", "config", "testcases.json");
const bugsPath = path.join(projectRoot, "automation", "config", "bugs.json");

function fail(message) {
  console.error("[DOCTOR][FAIL] " + message);
  process.exitCode = 1;
}

function ok(message) {
  console.log("[DOCTOR][OK] " + message);
}

function hasTool(cmd, args) {
  const result = spawnSync(cmd, args, { encoding: "utf8" });
  return !result.error;
}

function syntaxCheck(filePaths) {
  if (!hasTool("gcc", ["--version"])) {
    console.log("[DOCTOR][SKIP] Khong tim thay gcc, bo qua syntax check.");
    return true;
  }

  let allGood = true;
  for (const file of filePaths) {
    const result = spawnSync("gcc", ["-std=c11", "-Wall", "-Wextra", "-pedantic", "-fsyntax-only", file], {
      encoding: "utf8",
      cwd: projectRoot
    });
    if (result.status !== 0) {
      allGood = false;
      console.error("[DOCTOR][FAIL] Loi syntax tai " + file);
      console.error(result.stdout || "");
      console.error(result.stderr || "");
    }
  }

  if (allGood) ok("Tat ca file C deu qua syntax check voi gcc.");
  return allGood;
}

function main() {
  const testcases = JSON.parse(fs.readFileSync(testsPath, "utf8"));
  const bugs = JSON.parse(fs.readFileSync(bugsPath, "utf8"));

  if (testcases.length !== 22) fail("Project phai co dung 22 testcase.");
  else ok("So luong testcase = 22.");

  const failing = testcases.filter((t) => t.qaStatus === "Fail");
  if (failing.length !== 3) fail("Project phai co dung 3 testcase Fail co chu dich.");
  else ok("So luong testcase Fail co chu dich = 3.");

  const ids = new Set();
  for (const tc of testcases) {
    if (ids.has(tc.id)) fail("Trung testcase id: " + tc.id);
    ids.add(tc.id);

    const harness = path.join(projectRoot, "tests", tc.harness);
    const source = path.join(projectRoot, tc.source);
    if (!fs.existsSync(harness)) fail("Khong tim thay harness: " + tc.harness);
    if (!fs.existsSync(source)) fail("Khong tim thay source: " + tc.source);
  }
  ok("Tat ca testcase deu co harness/source ton tai.");

  if (bugs.length !== 3) fail("Bugs.json phai co dung 3 bug demo.");
  else ok("bugs.json co dung 3 bug demo.");

  const filePaths = [
    path.join(projectRoot, "src", "string_utils.c"),
    path.join(projectRoot, "src", "string_utils.h"),
    path.join(projectRoot, "tests", "cbmc_utils.h"),
    ...testcases.map((t) => path.join(projectRoot, "tests", t.harness))
  ];
  syntaxCheck(filePaths);
}

main();
