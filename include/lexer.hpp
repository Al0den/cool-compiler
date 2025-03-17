#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

enum class TokenType {
    CLASS, IF, THEN, ELSE, FI, LET, IN,
    PLUS, MINUS, TIMES, DIVIDE, EQUALS, LPAREN, RPAREN, LBRACE, RBRACE, SEMICOLON, COLON, COMMA,
    ID, NUMBER, STRING, END
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
};


std::ostream& operator<<(std::ostream& os, const Token& token);

class Lexer {
public:
    Lexer(const std::string& input) : input(input), pos(0), line(1) {};

    std::vector<Token> tokenize();

private:
    const std::string &input;

    int pos;
    int line;

    char peek();
    char get();

    bool isAtEnd();
    void skipWhitespace();

    Token makeToken(TokenType type, const std::string &lexeme);
    TokenType checkKeyword(const std::string &lexeme);

    Token nextToken();

    Token lexNumber(char first);
    Token lexIdentifier(char first);
    Token lexString();

};
