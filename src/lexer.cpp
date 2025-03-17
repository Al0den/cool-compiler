#include "../include/lexer.hpp"

#include <sstream>

std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << "Token(" << token.lexeme << ")";
    return os;
};

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    Token tok = nextToken();

    while (tok.type != TokenType::END) {
        tokens.push_back(tok);
        tok = nextToken();
    }

    tokens.push_back(tok);
    return tokens;
}

char Lexer::get() {
    if (isAtEnd())
        return '\0';
    return input[pos++];
}

char Lexer::peek() {
    if (pos < input.size())
        return input[pos];
    return '\0';
}

bool Lexer::isAtEnd() { return pos >= input.size(); }

void Lexer::skipWhitespace() {
    while (!isAtEnd() && std::isspace(peek())) {
        get();
    }
}

Token Lexer::makeToken(TokenType type, const std::string &lexeme) { return Token{type, lexeme, line}; }

TokenType Lexer::checkKeyword(const std::string &text) {
    if (text == "class")
        return TokenType::CLASS;
    if (text == "if")
        return TokenType::IF;
    if (text == "then")
        return TokenType::THEN;
    if (text == "else")
        return TokenType::ELSE;
    if (text == "fi")
        return TokenType::FI;
    if (text == "let")
        return TokenType::LET;
    if (text == "in")
        return TokenType::IN;
    return TokenType::ID;
}

Token Lexer::nextToken() {
    skipWhitespace();

    if (isAtEnd())
        return makeToken(TokenType::END, "");

    char c = get();

    switch (c) {
    case '+':
        return makeToken(TokenType::PLUS, "+");
    case '-':
        return makeToken(TokenType::MINUS, "-");
    case '*':
        return makeToken(TokenType::TIMES, "*");
    case '/':
        return makeToken(TokenType::DIVIDE, "/");
    case '=':
        return makeToken(TokenType::EQUALS, "=");
    case '(':
        return makeToken(TokenType::LPAREN, "(");
    case ')':
        return makeToken(TokenType::RPAREN, ")");
    case '{':
        return makeToken(TokenType::LBRACE, "{");
    case '}':
        return makeToken(TokenType::RBRACE, "}");
    case ':':
        return makeToken(TokenType::COLON, ":");
    case ';':
        return makeToken(TokenType::SEMICOLON, ";");
    case ',':
        return makeToken(TokenType::COMMA, ",");
    case '"':
        return lexString();
    default:
        break;
    }

    if (std::isdigit(c)) {
        return lexNumber(c);
    }

    if (std::isalpha(c)) {
        return lexIdentifier(c);
    }

    std::stringstream err;
    err << "Unexpected character '" << c << "' at line " << line;
    throw std::runtime_error(err.str());
}

Token Lexer::lexIdentifier(char first) {
    std::string lexeme(1, first);
    while (!isAtEnd() && (std::isalnum(peek()) || peek() == '_')) {
        lexeme.push_back(get());
    }

    TokenType type = checkKeyword(lexeme);
    return makeToken(type, lexeme);
}

Token Lexer::lexNumber(char first) {
    std::string lexeme(1, first);
    while (!isAtEnd() && std::isdigit(peek())) {
        lexeme.push_back(get());
    }
    return makeToken(TokenType::NUMBER, lexeme);
}

Token Lexer::lexString() {
    std::string lexeme;

    while (!isAtEnd() && peek() != '"') {
        char c = get();
        if (c == '\\' && !isAtEnd()) {
            char next = get();
            lexeme.push_back(next);
        } else {
            lexeme.push_back(c);
        }
    }

    if (isAtEnd()) {
        throw std::runtime_error("Unterminated string at line " + std::to_string(line));
    }

    get(); // consume closing quote

    return makeToken(TokenType::STRING, lexeme);
}
