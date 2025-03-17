#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "../include/parser.hpp"

// Make sure to include the declarations of your Lexer and Parser here
// (If you have them in separate headers, include them accordingly)
// #include "lexer.hpp"
// #include "parser.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path-to-file>\n";
        return 1;
    }

    // 1) Read file content
    std::ifstream inFile(argv[1]);
    if (!inFile) {
        std::cerr << "Error: Could not open file " << argv[1] << "\n";
        return 1;
    }

    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string input = buffer.str();

    try {
        // 2) Tokenize
        Lexer lexer(input);
        std::vector<Token> tokens = lexer.tokenize();

        // If you want to see the tokens, uncomment:
        for (const auto &t : tokens) {
            std::cout << t << std::endl;
        }
        std::cout << std::endl;

        // 3) Parse
        Parser parser(tokens);
        ASTNodePtr ast = parser.parse();

        // 4) Print the AST
        ast->print();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}

