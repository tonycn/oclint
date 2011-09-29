#include "mo/rule/EmptyIfStatementRuleTest.h"
#include "mo/util/TestCursorUtil.h"
#include "mo/ViolationSet.h"
#include "mo/Violation.h"
#include "mo/StringSourceCode.h"
#include "mo/util/CursorUtil.h"
#include "mo/util/CursorExtractionUtil.h"

#include <clang/AST/Stmt.h>

using namespace clang;

void EmptyIfStatementRuleTest::setUp() {
  _rule = new EmptyIfStatementRule();
}

void EmptyIfStatementRuleTest::tearDown() {
  delete _rule;
}

void EmptyIfStatementRuleTest::testRuleName() {
  TS_ASSERT_EQUALS(_rule->name(), "empty if statement");
}

void EmptyIfStatementRuleTest::checkRule(pair<CXCursor, CXCursor> cursorPair, bool isViolated) {
  ViolationSet violationSet;
  _rule->apply(cursorPair.first, cursorPair.second, violationSet);
  if (isViolated) {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 1);
    Violation violation = violationSet.getViolations().at(0);
    TS_ASSERT_EQUALS(violation.rule, _rule);
  }
  else {
    TS_ASSERT_EQUALS(violationSet.numberOfViolations(), 0);
  }
}

void EmptyIfStatementRuleTest::checkRule(string source, bool isViolated) {
  StringSourceCode strCode(source, "m");
  pair<CXCursor, CXCursor> cursorPair = extractCursor(strCode, ^bool(CXCursor node, CXCursor parentNode) {
    Stmt *stmt = CursorUtil::getStmt(node);
    return stmt && isa<IfStmt>(stmt);
  });
  checkRule(cursorPair, isViolated);
}

void EmptyIfStatementRuleTest::testGoodIfStatement() {
  checkRule("int main() { if (1) {;} return 0; }", false);
}

void EmptyIfStatementRuleTest::testIfStatementWithEmptyComponent() {
  checkRule("int main() { if (1) {} return 0; }", true);
}

void EmptyIfStatementRuleTest::testIfStatementWithNull() {
  checkRule("int main() { if (1); return 0; }", true);
}
