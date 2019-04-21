#pragma once
#include "Token.h"

namespace lexer {
	class Num :
		public Token
	{
	public:
		const double value;
		void print(std::ostream& stream) override { stream << "Num: " << value << " Tag: " << tag << "\n"; };
		Num(double v) : Token(Tag::NUM), value(v) {};
		~Num() {};
	};

	
}
