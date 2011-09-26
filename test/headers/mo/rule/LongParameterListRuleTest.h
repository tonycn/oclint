#include <cxxtest/TestSuite.h>
#include "mo/rule/LongParameterListRule.h"

class LongParameterListRuleTest : public CxxTest::TestSuite { 
private:
  LongParameterListRule *_rule;
  
  void checkRule(string source, string sourcetype, bool isViolated);
  
public:
  void setUp();
  void tearDown();
  void testRuleName();
  void testObjCMethodWithThreeParametersIsNotASmell();
  void testObjCMethodWithFourParametersIsASmell();
  void testObjCMethodWithFiveParametersIsASmell();
  void testCppMethodWithThreeParametersIsNotASmell();
  void testCppMethodWithFourParametersIsASmell();
  void testCppMethodWithFiveParametersIsASmell();
};
