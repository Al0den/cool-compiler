test_lexer:
	g++ -std=c++20 -o test_lexer test/test_lexer.cpp src/lexer.cpp

test_parser:
	g++ -std=c++20 -o test_parser test/test_parser.cpp src/parser.cpp src/lexer.cpp src/ast.cpp
