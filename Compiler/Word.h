#pragma once
#include <string>
#include "Token.h"

namespace lexer {
	class Word :
		public Token
	{
	public:
		std::string const lexemme;
		Word(int t, std::string s) : Token(t), lexemme(s) {};
		void print(std::ostream& stream) override { stream << "Word: " << lexemme << " " << "Tag: " << tag << "\n"; };
		~Word() { };
		
	};

}
