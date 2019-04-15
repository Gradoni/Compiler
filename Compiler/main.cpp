#include <iostream>
#include <fstream>
#include "lexer.h"
#include "Token.h"

int main() {
	std::ofstream os;
	os.open("result.txt");
	lexer::lexer lex{"test.txt"};
	while (true) {
		std::unique_ptr<lexer::Token> t = lex.scan();
		t->print(std::cout);
		t->print(os);
		if (t->tag == EOF) break;
	} 
	std::cin.get();
	os.close();
	return 0;
}