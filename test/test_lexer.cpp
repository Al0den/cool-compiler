#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "../include/lexer.hpp"  // Adjust the path if needed

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <source_file>" << std::endl;
        return 1;
    }
    
    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string source = buffer.str();
    
    Lexer lexer(source);
    std::vector<Token> tokens;
    
    try {
        tokens = lexer.tokenize();
    } catch (const std::exception &e) {
        std::cerr << "Tokenization error: " << e.what() << std::endl;
        return 1;
    }
    
    for (const auto &token : tokens) {
        std::cout << token << std::endl;
    }
    
    return 0;
}
