#ifndef __VISITOR_H__
#define __VISITOR_H__

#include <assert.h>

namespace front_end{
#include "ast_node.decl"
namespace visitor{
class Visitor {
public:
  virtual void visit(const AstNode* node) final {
    assert(false && "Visit a AstNode!");
  }
  virtual void visit(const AstProgram *node) = 0;
  virtual void visit(const AstDeclaration *node) = 0;
  virtual void visit(const AstVarDeclaration *node) = 0;
  virtual void visit(const AstTypeSpecifier *node) = 0;
  virtual void visit(const AstVarDeclList *node) = 0;
  virtual void visit(const AstVarDeclInit *node) = 0;
  virtual void visit(const AstVarDeclID *node) = 0;
  virtual void visit(const AstFuncDeclaration *node) = 0;
  virtual void visit(const AstStmt *node) = 0;
  virtual void visit(const AstCompoundStmt *node) = 0;
  virtual void visit(const AstReturnStmt *node) = 0;
};
} // namespace visitor
} // namespace front_end
#endif
