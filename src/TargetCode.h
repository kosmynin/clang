#pragma once

#include <deque>
#include <memory>
#include <set>
#include <string>

#include "clang/Rewrite/Core/Rewriter.h"

#include "TargetCodeFragment.h"

namespace clang {
class SourceManager;
};

using TargetCodeFragmentDeque = std::deque<std::shared_ptr<TargetCodeFragment>>;

class TargetCode {
  // std::unordered_set<VarDecl*> GlobalVarialesDecl; //TODO: we will use this
  // to avoid capturing global vars
  TargetCodeFragmentDeque CodeFragments;
  std::set<std::string> SystemHeaders;
  clang::Rewriter &TargetCodeRewriter;
  clang::SourceManager &SM;

public:
  TargetCode(clang::Rewriter &TargetCodeRewriter)
      : TargetCodeRewriter(TargetCodeRewriter),
        SM(TargetCodeRewriter.getSourceMgr()){};

  bool addCodeFragment(std::shared_ptr<TargetCodeFragment> Frag);
  bool addCodeFragmentFront(std::shared_ptr<TargetCodeFragment> Fag);
  void generateCode(llvm::raw_ostream &Out);
  TargetCodeFragmentDeque::const_iterator getCodeFragmentsBegin() {
    return CodeFragments.begin();
  }
  TargetCodeFragmentDeque::const_iterator getCodeFragmentsEnd() {
    return CodeFragments.end();
  }
  void addHeader(const std::string &Header) { SystemHeaders.insert(Header); }

private:
  void generateFunctionPrologue(TargetCodeRegion *TCR, llvm::raw_ostream &Out);
  std::string generateFunctionName(TargetCodeRegion *TCR);
  bool isCodeAlreadyInFragments(TargetCodeFragment *Frag);
};
