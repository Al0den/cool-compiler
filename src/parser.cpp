#include "../include/parser.hpp"
#include <stdexcept>

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens), pos(0) {}

ASTNodePtr Parser::parse() {
    std::vector<ASTNodePtr> classes;

    while(!match(TokenType::END)) {
        classes.push_back(parseClass());
    }

    return std::make_shared<ProgramNode>(classes);
}

Token Parser::currentToken() {
    if (pos < tokens.size()) {
        return tokens[pos];
    }

    return Token{TokenType::END, "", 0};
}

bool Parser::match(TokenType expected) {
    if (currentToken().type == expected) {
        pos++;
        return true;
    }
    return false;
}

Token Parser::consume(TokenType expected, const std::string &message) {
    if (currentToken().type == expected) {
        return tokens[pos++];
    }
    throw std::runtime_error(message);
}

ASTNodePtr Parser::parseClass() {
    consume(TokenType::CLASS, "Expected 'class'");
    Token id = consume(TokenType::ID, "Expected class name");
    consume(TokenType::LBRACE, "Expected '{'");
    std::vector<ASTNodePtr> features = parseFeaturesList();
    consume(TokenType::RBRACE, "Expected '}'");
    consume(TokenType::SEMICOLON, "Expected ';'");

    return std::make_shared<ClassNode>(id.lexeme, "", features);
}

std::vector<ASTNodePtr> Parser::parseFeaturesList() {
    std::vector<ASTNodePtr> features;
    while (currentToken().type == TokenType::ID) {
        features.push_back(parseFeature());
    }
    return features;
}

ASTNodePtr Parser::parseFeature() {
    Token id = consume(TokenType::ID, "Expected feature name");
    if (match(TokenType::LPAREN)) {
        auto params = parseParamsList();
        consume(TokenType::RPAREN, "Expected ')' after parameters");
        consume(TokenType::COLON, "Expected ':' before return type");
        Token returnType = consume(TokenType::ID, "Expected return type");
        consume(TokenType::LBRACE, "Expected '{' before method body");
        ASTNodePtr body = parseExpr();
        consume(TokenType::RBRACE, "Expected '}' after method body");
        consume(TokenType::SEMICOLON, "Expected ';' after method definition");
        return std::make_shared<MethodFeature>(id.lexeme, returnType.lexeme, body);

    } else {
        consume(TokenType::COLON, "Expected ':' in attribute");
        Token returnType = consume(TokenType::ID, "Expected return type");
        consume(TokenType::SEMICOLON, "Expected ';' after attribute");
        return std::make_shared<AttrFeature>(id.lexeme, returnType.lexeme);
    }
}

std::vector<std::pair<std::string, std::string>> Parser::parseParamsList() {
    std::vector<std::pair<std::string, std::string>> params;

    if(currentToken().type == TokenType::RPAREN) {
        return params;
    }

    params.push_back(parseParam());

    while(match(TokenType::COMMA)) {
        params.push_back(parseParam());
    }

    return params;
}

std::pair<std::string, std::string> Parser::parseParam() {
    Token id = consume(TokenType::ID, "Expected parameter name");
    consume(TokenType::COLON, "Expected ':' after parameter name");
    Token type = consume(TokenType::ID, "Expected parameter type");
    return std::make_pair(id.lexeme, type.lexeme);
}

ASTNodePtr Parser::parseExpr() {
    return parseAddSub();
}

ASTNodePtr Parser::parseAddSub() {
    ASTNodePtr node = parseMulDiv();
    while (currentToken().type == TokenType::PLUS || currentToken().type == TokenType::MINUS) {
        Token op = tokens[pos++];
        ASTNodePtr right = parseMulDiv();
        node = std::make_shared<BinOpExpr>(op.lexeme[0], node, right);
    }
    return node;
}

ASTNodePtr Parser::parseMulDiv() {
    ASTNodePtr node = parseFactor();
    while (currentToken().type == TokenType::TIMES || currentToken().type == TokenType::DIVIDE) {
        Token op = tokens[pos++];
        ASTNodePtr right = parseFactor();
        node = std::make_shared<BinOpExpr>(op.lexeme[0], node, right);
    }
    return node;
}

ASTNodePtr Parser::parseFactor() {
    Token tok = currentToken();
    if (tok.type == TokenType::NUMBER) {
        pos++;
        return std::make_shared<NumberExpr>(std::stoi(tok.lexeme));
    } else if(tok.type == TokenType::STRING) {
        pos++;
        return std::make_shared<StringExpr>(tok.lexeme);
    } else if (tok.type == TokenType::ID) {
        pos++;
        // Check for a call expression.
        if (currentToken().type == TokenType::LPAREN) {
            pos++; // consume LPAREN
            std::vector<ASTNodePtr> args = parseArgList();
            consume(TokenType::RPAREN, "Expected ')' after call arguments");
            return std::make_shared<CallExpr>(tok.lexeme, args);
        } else {
            return std::make_shared<IdExpr>(tok.lexeme);
        }
    } else if (tok.type == TokenType::LPAREN) {
        pos++; // consume LPAREN
        ASTNodePtr expr = parseExpr();
        consume(TokenType::RPAREN, "Expected ')' after expression");
        return expr;
    } else if (tok.type == TokenType::LBRACE) {
        return parseBlock();
    }
    throw std::runtime_error("Unexpected token in expression at line " + std::to_string(tok.line) + ", token: " + tok.lexeme);
}

ASTNodePtr Parser::parseBlock() {
    consume(TokenType::LBRACE, "Expected '{' to start a block");
    std::vector<ASTNodePtr> exprs;

    if(currentToken().type != TokenType::RBRACE) {
        exprs.push_back(parseExpr());
        
        while(match(TokenType::SEMICOLON)) {
            if (currentToken().type == TokenType::RBRACE) break;
            exprs.push_back(parseExpr());
        }
    }

    consume(TokenType::RBRACE, "Expected '}' to end block");

    return std::make_shared<BlockExpr>(exprs);
}

std::vector<ASTNodePtr> Parser::parseArgList() {
    std::vector<ASTNodePtr> args;
    if (currentToken().type == TokenType::RPAREN)
        return args; // empty argument list
    args.push_back(parseExpr());
    while (match(TokenType::COMMA)) {
        args.push_back(parseExpr());
    }
    return args;
}
