#ifndef __AST_NODE_H__
#define __AST_NODE_H__
#include "lexer.h"
#include "visitor.h"

#include <assert.h>
#include <string>
#include <vector>

namespace front_end {
using namespace lexer;
using namespace visitor;

#include "ast_node.decl"

enum class AstType { ASTNODE, ASTVARDECL, ASTFUNCDECL };

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
    assert(false && "Visit a AstNode!");
  };
};

class AstDeclaration : public AstNode {
public:
  AstDeclaration(const std::string &name, AstType type)
      : AstNode(name + "Declaration", type) {}
  void accept(Visitor &visitor) const override { visitor.visit(this); }
  bool isVarDecl() { return m_type == AstType::ASTVARDECL; }
  bool isFuncDecl() { return m_type == AstType::ASTFUNCDECL; }
};

class AstDeclarationList : public AstNode {
public:
  AstDeclarationList(const AstDeclaration *decl) : AstNode("DeclarationList") {
    m_child.push_back(decl);
  }
  AstDeclarationList(const AstDeclarationList *declList,
                     const AstDeclaration *decl)
      : AstNode("DeclList") {
    m_child.push_back(declList);
    m_child.push_back(decl);
  }
  void accept(Visitor &visitor) const override { visitor.visit(this); }

  bool hasOnlyOneDecl() const { return m_child.size() == 1; }

  const AstDeclarationList *getDeclList() const {
    return static_cast<const AstDeclarationList *>(m_child[0]);
  }
  const AstDeclaration *getDecl() const {
    assert(m_child.size() > 1 && "AstDeclList only has one childe!");
    return static_cast<const AstDeclaration *>(m_child[1]);
  }
};

class AstProgram : public AstNode {
public:
  AstProgram(const AstDeclarationList *DeclList) : AstNode("Program") {
    m_child.push_back(DeclList);
  }
  void accept(Visitor &visitor) const override { visitor.visit(this); }
  const AstDeclarationList *getDeclList() const {
    return static_cast<const AstDeclarationList *>(m_child[0]);
  }
};

class AstVarDeclID : public AstNode {
  bool m_isArray;
  size_t m_arraySize;
  const std::string &m_ID;

public:
  explicit AstVarDeclID(const std::string &ID, bool isArray = false,
                        size_t arraySize = 0)
      : AstNode("VarDeclID"), m_ID(ID), m_isArray(isArray),
        m_arraySize(arraySize) {}
  void accept(Visitor &visitor) const override { visitor.visit(this); }
  bool isArray() const { return m_isArray; }
  bool getArraySize() const { return m_arraySize; }
  const std::string &getID() const { return m_ID; }
};

class AstFuncDeclaration : public AstDeclaration {
public:
  AstFuncDeclaration() : AstDeclaration("Function", AstType::ASTFUNCDECL) {}
  void accept(Visitor &visitor) const override { visitor.visit(this); }
};

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
  bool isLong() const { return !m_isUnsigned && m_tokType == Token::LONG; }
  bool isUChar() const { return m_isUnsigned && m_tokType == Token::CHAR; }
  bool isUShort() const { return m_isUnsigned && m_tokType == Token::SHORT; }
  bool isULong() const { return m_isUnsigned && m_tokType == Token::LONG; }
  bool isUInt() const {
    return (m_isUnsigned && m_tokType == Token::INT) ||
           m_tokType == Token::UNSIGNED;
  }
  bool isFloat() const { return m_tokType == Token::FLOAT; }
  bool isDouble() const { return m_tokType == Token::DOUBLE; }
};

class AstVarDeclInit : public AstNode {
public:
  AstVarDeclInit(const AstVarDeclID *declID) : AstNode("VarDeclInit") {
    m_child.push_back(declID);
  }
  void accept(Visitor &visitor) const override { visitor.visit(this); }
  const AstVarDeclID *getVarDeclID() {
    return static_cast<const AstVarDeclID *>(m_child[0]);
  }
};

class AstVarDeclList : public AstNode {
public:
  AstVarDeclList(const AstVarDeclList *list, const AstVarDeclInit *init)
      : AstNode("AstVarDeclList") {
    m_child.push_back(list);
    m_child.push_back(init);
  }
  AstVarDeclList(const AstVarDeclInit *init) : AstNode("VarDeclList") {
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

class AstVarDeclaration : public AstDeclaration {
public:
  AstVarDeclaration(const AstTypeSpecifier *typeSpecifier,
                    const AstVarDeclList *varDeclList)
      : AstDeclaration("Var", AstType::ASTVARDECL) {
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

class AstStmt : public AstNode {};
} // namespace front_end
#endif
