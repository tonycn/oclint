#include "mo/SmellFinder.h"
#include "mo/TraverseAST.h"

SmellFinder::SmellFinder(string src) {
  _index = clang_createIndex(0, 0);
  _translationUnit = clang_parseTranslationUnit(_index, src.c_str(), 0, 0, 0, 0, CXTranslationUnit_None);
  if (!_translationUnit) {
    throw "Code compilation fails!";
  }
}

SmellFinder::~SmellFinder() {
  if (_translationUnit) {
    clang_disposeTranslationUnit(_translationUnit); 
  }
  if (_index) {
    clang_disposeIndex(_index);
  }
}

bool SmellFinder::hasSmell() {
  clang_visitChildren(clang_getTranslationUnitCursor(_translationUnit), traverseAST, 0);
  return false;
}
