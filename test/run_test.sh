#!/bin/sh

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

LAMBDA="./lambda"
TEST_DIR="test/fixtures"
TMP_OUT="/tmp/lambda_test_out.txt"

PASSED=0
FAILED=0

run_case() {
	local file="$1"
	local expected_code="$2"
	local expected_output="$3"
	local test_name=$(basename "$file")

	$LAMBDA "$file" > "$TMP_OUT" 2>&1
	local actual_code=$?

	if [ "$actual_code" -ne "$expected_code" ]; then
		echo -e "[ ${RED}FAIL${NC} ] $test_name (Exit Code expected: $expected_code, got: $actual_code)"
		((FAILED++))
		return
	fi

	if [ $# -ge 3]; then
		local actual_output=$(cat "$TMP_OUT")
		if [ "$actual_output" != "$expected_output" ]; then
			echo -e "[ ${RED}FAIL${NC} ] $test_name"
			echo "  Expected: '$expected_output'"
			echo "  Got     : '$actual_output'"
			((FAILED++))
			return
		fi
	fi

	echo -e "[ ${GREEN}PASS${NC} ] $test_name"
	((PASSED++))
}

echo "========================================"
echo " Running Integration Tests"
echo "========================================"

run_case "$TEST_DIR/01_variable.lm" 0 "x"
run_case "$TEST_DIR/02_abstruction.lm" 0 "\x.x"
run_case "$TEST_DIR/03_application.lm" 0 "y"

run_case "$TEST_DIR/not_found.lm" 1



echo "========================================"
echo -e "Results: ${GREEN}${PASSED} passed${NC}, ${RED}${FAILED} failed${NC}"
echo "========================================"

rm -f "$TMP_OUT"

if [ "$FAILED" -gt 0 ]; then
	exit 1
fi
exit 0

