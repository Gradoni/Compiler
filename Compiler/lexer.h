#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include "Word.h"
#include "Token.h"
#include "Num.h"
#include "Operator.h"

namespace lexer {
	class lexer
	{
	public:
		int line = 1;
		lexer(std::string input_file);
		std::unique_ptr<Token> scan(); //scans input and returns tokens
		~lexer();


	private:
		std::ifstream source_file;
		std::ofstream target_file;
		char peek = ' ';
		void reserve(Word t); // reserves keyword
		std::unordered_map<std::string, Word> words;

	};
}


