#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

PASS=0
FAIL=0

echo "=========================================="
echo "   MINISHELL TESTS"
echo "=========================================="
echo ""

test_cmd() {
    echo -n "Test: $1... "
    result=$(echo -e "$2\nexit" | ./minishell 2>/dev/null | grep -v ">>>" | grep -v "minishell" | grep -v "exit" | tail -1)
    expected="$3"
    
    if [ "$result" = "$expected" ]; then
        echo -e "${GREEN}✅${NC}"
        ((PASS++))
    else
        echo -e "${RED}❌${NC}"
        echo "  Expected: [$expected]"
        echo "  Got:      [$result]"
        ((FAIL++))
    fi
}

echo "=== QUOTE HANDLING ==="
test_cmd "Adjacent single quotes" "echo hello'world'" "helloworld"
test_cmd "Adjacent empty quotes" 'echo hello""world' "helloworld"
test_cmd "Multiple pairs" "echo 'a'b'c'" "abc"

echo ""
echo "=== VARIABLE EXPANSION ==="
test_cmd "Simple var" 'export X=test\necho $X' "test"
test_cmd "Exit code + text" 'echo $?HELLO' "0HELLO"
test_cmd "Var in quotes" 'export X=world\necho "hello $X"' "hello world"

echo ""
echo "=== HEREDOC ==="
test_cmd "Basic heredoc" 'cat << EOF\nhello\nEOF' "hello"
test_cmd "Heredoc with var" 'export U=test\ncat << EOF\nUser: $U\nEOF' "User: test"

echo ""
echo "=== PIPES ==="
test_cmd "Simple pipe" 'echo hello | cat' "hello"
test_cmd "Multiple pipes" 'echo test | cat | cat' "test"

echo ""
echo "=== EXIT CODES ==="
test_cmd "Success code" 'echo test > /dev/null\necho $?' "0"
test_cmd "CD error code" 'cd /nonexistent 2>/dev/null\necho $?' "1"
test_cmd "Export error" 'export 123 2>/dev/null\necho $?' "1"

echo ""
echo "=== REDIRECTIONS ==="
echo -e "echo hello > /tmp/test.txt\nexit" | ./minishell > /dev/null 2>&1
if [ -f /tmp/test.txt ] && [ "$(cat /tmp/test.txt)" = "hello" ]; then
    echo -e "Test: Output redir... ${GREEN}✅${NC}"
    ((PASS++))
else
    echo -e "Test: Output redir... ${RED}❌${NC}"
    ((FAIL++))
fi
rm -f /tmp/test.txt

echo ""
echo "=== EXIT BUILTIN ==="
echo "exit" | ./minishell > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo -e "Test: Exit works... ${GREEN}✅${NC}"
    ((PASS++))
else
    echo -e "Test: Exit works... ${RED}❌${NC}"
    ((FAIL++))
fi

echo ""
echo "=========================================="
echo -e "${GREEN}PASSED: $PASS${NC}"
echo -e "${RED}FAILED: $FAIL${NC}"
echo "=========================================="
echo ""
echo "MANUAL TESTS NEEDED:"
echo ""
echo "1. Run: ./minishell"
echo "   Press: Ctrl+C"
echo "   Expected: New line, shell continues"
echo ""
echo "2. Run: ./minishell"
echo "   Press: Ctrl+\\ (on empty prompt)"
echo "   Expected: Nothing happens"
echo ""
echo "3. Run: ./minishell"
echo "   Type: hello (DON'T press Enter)"
echo "   Press: Ctrl+\\"
echo "   Expected: Prints 'exit', shell quits"
echo ""

