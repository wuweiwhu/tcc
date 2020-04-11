#ifndef __AST_NODE_H__
#define __AST_NODE_H__
#include "lexer.h"
#include "visitor.h"
namespace front_end {
using namespace lexer;
namespace parser {

enum class AstType { ASTNODE, ASTVARDECL, ASTFUNCDECL };

class AstProgram;
class AstConst;
class AstDeclList;
class AstVarDeclaration;
class AstFuncDeclaration;
class AstTypeSpecifier;
class AstVarDeclList;
class AstVarDeclInitialize;
class AstVarDeclId;

class AstNode {
  const std::string m_name;

protected:
  AstType m_type;
  std::vector<const AstNode *> m_child;
  explicit AstNode(const std::string &name, AstType type = AstType::ASTNODE)
      : m_name(name), m_type(type) {}

public:
  const std::string &getName() const { return m_name; }
  virtual void accept(Visitor &visitor) const {
    assert(false && "Visit a AstNode!";)
  };
};

class AstProgram : public AstNode {
public:
  AstProgram(const AstDeclList *DeclList) : AstNode("Program") {
    m_child.push_back(DeclList);
  }
  void accept(Visitor &visitor) const override { visitor.visit(this); }
  const AstDeclList *getDeclList() const {
    return static_cast<const AstDeclList *>(m_childe[0]);
  }
};

class AstDecl : public AstNode {
public:
  AstDecl(const std::string &name = "") : AstNode(name + "Declaration") {}
  void accept(Visitor &visitot) const override { visitor.visit(this); }
  bool isVarDecl() { return m_type == AstType::ASTVARDECL; }
  bool isFuncDecl() { return m_type == AstType::ASTFUNCDECL; }
};

class AstDeclList : public : AstNode {
public:
  AstDeclList(const AstDecl *decl) : m_child({decl}), AstNode("DeclList") {}
  AstDeclList(const AstDeclList *declList, const AstDecl *decl)
      : AstNode("DeclList") {
    m_child.push_back(declList);
    m_child.push_back(decl);
  }
  void accept(Visitor &visitor) const override { visitor.vist(this); }

  bool hasOnlyOneDecl() const { return m_child.size() == 1; }

  const AstDeclList *getDeclList() const {
    return static_cast<const AstDeclList *>(m_child[0]);
  }
  const AstDeclList *getDecl() const {
    assert(m_child.size() > 1 && "AstDeclList only has one childe!");
    return static_cast<const AstDecl *>(m_child[1]);
  }
}

class AstTypeSpecifier : public AstNode {
  Token m_tokType;
  bool m_isUnsigned;

public:
  AstTypeSpecifier(Token tok, bool isUnsigned = false)
      : AstNode("TypeSpecifier"), m_tokType(tok), m_isUnsigned(isUnsigned) {}
  void accept(Visitor &visitor) const override { visitor.visit(this); }
  bool isChar() const { return !m_isUnsigned && m_tokType == Token::CHAR; }
  bool isShort() const { return !m_isUnsigned && m_tokType == Token::SHORT; }
  bool isInt() const { return !m_isUnsigned && m_tokType == Token::INT; }
  bool isLong() const { return !m_isUnsigned && m_tokType == Token::Long; }
  bool isUChar() const { return m_isUnsigned && m_tokType == Token::CHAR; }
  bool isUShort() const { return m_isUnsigned && m_tokType == Token::SHORT; }
  bool isULong() const { return m_isUnsigned && m_tokType == Token::Long; }
  bool isUInt() const {
    return (m_isUnsigned && &&m_tokType == Token::INT) ||
           m_tokType == Token::UNSIGNED;
  }
  bool isFloat() const { return m_tokType == Token::FLOAT; }
  bool isDouble() const { return m_tokType == Token::DOUBLE; }
};

class AstVarDeclaration : public AstDecl {
public:
  AstVarDeclaration(const AstTypeSpecifier *typeSpecifier,
                    const AstVarDeclList *varDeclList)
      : AstDecl("Var", AstType::ASTVARDECL) {
    m_child.push_back(typeSpecifier);
    m_child.push_back(varDeclList);
  }
  void accept(Visitor &visitor) const override { visitor.visit(this); }
  const AstTypeSpecifier *getTypeSpecifier() const {
    return static_cast<const AstTypeSpecifier *>(m_child[0]);
  }
  const AstVarDeclList *getVarDeclList() const {
    return static_cast<const AstVarDeclList *>(m_child[1]);
  }
};

class AstVarDeclList : public AstNode {
public:
  AstVarDeclList(const AstVarDeclList *list, const AstVarDeclInitialize *init)
      : AstNode("AstVarDeclList") {
    m_child.push_back(list);
    m_child.push_back(init);
  }
  AstVarDeclList(const AstVarDeclInitialize *init) : AstNode("AstVarDeclList") {
    m_child.push_back(init);
  }
  void accept(Visitor &visitor) const override { visitor.visit(this); }
  bool hasOnlyOneInit() const { return m_child.size() == 1; }
  const AstVarDeclList *getVarDeclList() const {
    return static_cast<const AstVarDeclList *>(m_child[0]);
  }
  const AstVarDeclInit *getVarDeclInit() const {
    assert(m_child.size() > 1 && "only has one child");
    return static_cast<const AstVarDeclInit *>(m_child[1]);
  }
};

class AstVarDeclInit : public AstNode {
public:
  Ast
}

class AstFuncDeclaration : public AstDecl {
public:
  AstFuncDeclaration() : AstDecl("Function", AstType::ASTFUNCDECL) {}
  void accept(Visitor &visitor) const override { visitor.visit(this); }
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
