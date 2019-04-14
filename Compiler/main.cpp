#include <iostream>
#include "lexer.h"
#include "Token.h"

int main() {

	lexer::lexer lex{"test.txt"};
	while (true) {
		lexer::Token t = lex.scan();
		std::cout << t.tag << std::endl;
		if (t.tag == EOF) break;
	} 
	std::cin.get();
	return 0;
}