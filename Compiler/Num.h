#pragma once
#include "Token.h"

namespace lexer {
	class Num :
		public Token
	{
	public:
		const int value;
		Num(int v) : Token(Tag::NUM), value(v) {};
		~Num() {};
	};

}
