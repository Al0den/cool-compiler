#include "../include/ast.hpp"

void printIndent(int indent = 0) {
    for (int i = 0; i < indent; i++) {
        std::cout << "  ";
    }
}

NumberExpr::NumberExpr(int value) 
    : value(value) {}
IdExpr::IdExpr(const std::string &name) 
    : name(name) {}
BinOpExpr::BinOpExpr(char op, ASTNodePtr left, ASTNodePtr right) 
    : op(op), left(left), right(right) {}
BlockExpr::BlockExpr(std::vector<ASTNodePtr> &exprs)
    : exprs(exprs) {}
CallExpr::CallExpr(const std::string &callee, std::vector<ASTNodePtr> &args) 
    : callee(callee), args(args) {}
StringExpr::StringExpr(const std::string &value) 
    : value(value) {}

AttrFeature::AttrFeature(const std::string &name, const std::string &returnType) 
    : name(name), returnType(returnType) {}
MethodFeature::MethodFeature(const std::string &name, const std::string &returnType, ASTNodePtr body) 
    : name(name), returnType(returnType), body(body) {}
ClassNode::ClassNode(const std::string &name, const std::string &parent, std::vector<ASTNodePtr> &features) 
    : name(name), features(features) {}
ProgramNode::ProgramNode(std::vector<ASTNodePtr> &classes) 
    : classes(classes) {}


void NumberExpr::print(int indent) const {
    printIndent(indent);
    std::cout << "Number(" << value << ")" << std::endl;
}

void IdExpr::print(int indent) const {
    printIndent(indent);
    std::cout << "Id(" << name << ")" << std::endl;
}

void BinOpExpr::print(int indent) const {
    printIndent(indent);
    std::cout << "BinOp(" << op << ")" << std::endl;
    left->print(indent + 1);
    right->print(indent + 1);
}

void BlockExpr::print(int indent) const {
    printIndent(indent);
    std::cout << "Block" << std::endl;
    for (const auto &expr : exprs) {
        expr->print(indent + 1);
    }
}

void CallExpr::print(int indent) const {
    printIndent(indent);
    std::cout << "Call(" << callee << ")" << std::endl;
    for (const auto &arg : args) {
        arg->print(indent + 1);
    }
}

void StringExpr::print(int indent) const {
    printIndent(indent);
    std::cout << "String(" << value << ")" << std::endl;
}



void AttrFeature::print(int indent) const {
    printIndent(indent);
    std::cout << "Attr(" << name << ", " << returnType << ")" << std::endl;
}

void MethodFeature::print(int indent) const {
    printIndent(indent);
    std::cout << "Method(" << name << ", " << returnType << ")" << std::endl;
    body->print(indent + 1);
}

void ClassNode::print(int indent) const {
    printIndent(indent);
    std::cout << "Class(" << name << ")" << std::endl;
    for (const auto &feature : features) {
        feature->print(indent + 1);
    }
}

void ProgramNode::print(int indent) const {
    printIndent(indent);
    std::cout << "Program" << std::endl;
    for (const auto &cls : classes) {
        cls->print(indent + 1);
    }
}


