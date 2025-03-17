#include "lexer.hpp"
#include "ast.hpp"

class Parser {
public:
    Parser(const std::vector<Token> &tokens);
    
    ASTNodePtr parse();
private:
    std::vector<Token> tokens;
    size_t pos;

    Token currentToken();
    Token consume(TokenType expected, const std::string &message);
    bool match(TokenType expected);

    ASTNodePtr parseClass();
    ASTNodePtr parseFeature();
    ASTNodePtr parseExpr();
    ASTNodePtr parseAddSub();
    ASTNodePtr parseMulDiv();
    ASTNodePtr parseFactor();
    ASTNodePtr parseBlock();
    std::vector<ASTNodePtr> parseArgList();
    
    std::vector<ASTNodePtr> parseFeaturesList();
    std::vector<std::pair<std::string, std::string>> parseParamsList();

    std::pair<std::string, std::string> parseParam();

};
