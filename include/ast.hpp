#include <iostream>

struct ASTNode {
    virtual ~ASTNode() = default;
    virtual void print(int indent = 0) const = 0;
};

using ASTNodePtr = std::shared_ptr<ASTNode>;

void printIndent(int indent);

struct ExprNode : public ASTNode {
};

struct NumberExpr : public ExprNode {
    int value;
    NumberExpr(int value);
    void print(int indent = 0) const override;
};

struct IdExpr : public ExprNode {
    std::string name;
    IdExpr(const std::string &name);
    void print(int indent = 0) const override;
};

struct BinOpExpr : public ExprNode {
    char op;
    ASTNodePtr left, right;
    BinOpExpr(char op, ASTNodePtr left, ASTNodePtr right);
    void print(int indent = 0) const override;
};

struct BlockExpr : public ExprNode {
    std::vector<ASTNodePtr> exprs;
    BlockExpr(std::vector<ASTNodePtr> &exprs);
    void print(int indent = 0) const override;
};

struct CallExpr : public ExprNode {
    std::string callee;
    std::vector<ASTNodePtr> args;
    CallExpr(const std::string &callee, std::vector<ASTNodePtr> &args);
    void print(int indent = 0) const override;
};

struct StringExpr : public ExprNode {
    std::string value;
    StringExpr(const std::string &value);
    void print(int indent = 0) const override;
};

struct FeatureNode : public ASTNode {
};

struct AttrFeature : public FeatureNode {
    std::string name, returnType;
    AttrFeature(const std::string &name, const std::string &returnType);
    void print(int indent = 0) const override;
};

struct MethodFeature : public FeatureNode {
    std::string name, returnType;
    ASTNodePtr body;
    MethodFeature(const std::string &name, const std::string &returnType, ASTNodePtr body);
    void print(int indent = 0) const override;
};

struct ClassNode : public ASTNode {
    std::string name;
    std::vector<ASTNodePtr> features;
    ClassNode(const std::string &name, const std::string &parent, std::vector<ASTNodePtr> &features);
    void print(int indent = 0) const override;
};

struct ProgramNode : public ASTNode {
    std::vector<ASTNodePtr> classes;
    ProgramNode(std::vector<ASTNodePtr> &classes);
    void print(int indent = 0) const override;
};
