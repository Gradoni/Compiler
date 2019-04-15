#pragma once
#include "Token.h"

namespace lexer {
	class Num :
		public Token
	{
	public:
		const int value;
		void print(std::ostream& stream) override { stream << "Num: " << value << " Tag: " << tag << "\n"; };
		Num(int v) : Token(Tag::NUM), value(v) {};
		~Num() {};
	};

	
}
