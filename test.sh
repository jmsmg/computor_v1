#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
NC='\033[0m'

run() {
    echo -e "${CYAN}> python3 computor.py \"$1\"${NC}"
    python3 computor.py "$1"
    echo ""
}

echo "===== 과제 예시 ====="
run "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
run "5 * X^0 + 4 * X^1 = 4 * X^0"
run "8 * X^0 - 6 * X^1 + 0 * X^2 - 5.6 * X^3 = 3 * X^0"

echo "===== 0차 ====="
run "42 * X^0 = 42 * X^0"
run "5 * X^0 = 3 * X^0"

echo "===== 1차 ====="
run "0 * X^0 + 4 * X^1 = 0 * X^0"
run "1 * X^0 + 1 * X^1 = 0 * X^0"

echo "===== 2차 - 판별식 0 (중근) ====="
run "1 * X^0 + 2 * X^1 + 1 * X^2 = 0 * X^0"

echo "===== 2차 - 판별식 음수 (복소수) ====="
run "1 * X^0 + 0 * X^1 + 1 * X^2 = 0 * X^0"

echo "===== 소수 계수 ====="
run "1.5 * X^0 + 3.2 * X^1 = 0 * X^0"

echo "===== 음수 계수 ====="
run "-1 * X^0 + -2 * X^1 = 0 * X^0"

echo "===== 에러 케이스 ====="
echo -e "${CYAN}> python3 computor.py${NC}"
python3 computor.py 2>&1
echo ""
