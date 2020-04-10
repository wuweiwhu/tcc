#ifndef __AST_NODE_H__
#define __AST_NODE_H__
#include "lexer.h"
#include "visitor.h"
namespace front_end {
using namespace lexer;
namespace parser {

enum class AstType {

};

class AstProgram;
class AstDeclList;
class AstVarDecl;
class AstFuncDecl;
class AstTypeSpecifier;

class Visitor;
class AstNode {
  friend class Visitor;
  const std::string m_name;
  const AstType m_type;

public:
  AstNode(const std::string &name) : m_name(name) {}
  const std::string &getName() const { return m_name; }
  AstType getType() const { return m_type; }
  virtual void accept(const Visitor &visitor) {
    assert(std::string("visitor for") + m_name + "not implement yet";)
  };
};

class AstProgram : public AstNode {
  AstDeclList *m_declList;

public:
  AstProgram(AstDeclList *DeclList) : AstNode("Program") {}
  void accept(const Visitor &visitor) override {
    visitor.visit(this);
  }
};

class AstDecl : public AstNode {
public:
  AstDecl(const std::string &name) : AstNode(name + "Declaration") {}
};

class AstDeclList : public : AstDecl {
  std::vector<AstDecl *> m_decls;

public:
  AstDeclList(AstDecl *decl) : m_decls({decl}), AstDecl("List") {}
  AstDeclList(AstDeclList *declList, AstDecl *decl) : AstDecl("List") {
    m_decls.push_back(declList);
    m_decls.push_back(decl);
  }
  void accept(const Visitor &visitor) override { visitor.vist(this); }
}

class AstTypeSpecifier : public AstNode {
  Token m_type;
  bool isInt() { return m_type == Token::INT; }
  bool isFloat() { return m_type == Token::FLOAT; }
  bool isShort() { return m_type == Token::SHORT; }
  bool isDouble() { return m_type == Token::DOUBLE; }
  bool isChar() { return m_type == Token::CHAR; }
  bool isLong() { return m_type == Token::Long; }
  bool isUInt() { return m_type == Token::UNSIGNED; }
  // TODO: support unsigned char/short/int/long
public:
  AstTypeSpecifier(Token tok) : m_type(tok), AstNode("TypeSpecifier") {}
  void accept(const Visitor &visitor) { visitor.visit(this); }
};

class AstVarDecl : public AstDecl {
  AstTypeSpecifier *m_typeSpecifier;
  AstVarDeclList *m_varDeclList;

public:
  AstVarDecl(AstTypeSpecifier *typeSpecifier, AstVarDeclList *varDeclList)
      : AstDecl("Var"), m_typeSpecifier(typeSpecifier),
        m_varDeclList(varDeclList) {}
  void accept(const Visitor &visitor) override { visitor.visit(this); }
};

class AstFuncDecl : public AstDecl {
public:
  AstFuncDecl() : AstDecl("Function") {}
  void accept(const Visitor &visitor) override { visitor.visit(this); }
};

class AstStmt : public AstNode {};
class AstIfStmt : public AstStmt {};
class AstForStmt : public AstStmt {};
class AstWhileStmt : public AstStmt {};
class AstDoWhileStmt : public AstStmt {};
class AstCompoundStmt : public AstStmt {};
class AstExpression : public AstNode {};
class AstBinaryExpr : public AstExpression {};
class AstUnaryExpr : public AstExpression {};
class AstFunction : public AstNode {};
class AstFunctionProto : public AstNode {};
class AstFunctionBody : public AstCompoundStmt {};
class AstFunctionDecl : public AstDecl {};

} // namespace parser
} // namespace front_end
#endif
