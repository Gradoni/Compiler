#pragma once
#include "Token.h"

namespace lexer {
	class Operator :
		public Token
	{
	public:
		const int op;
		void print(std::ostream& stream) override { stream << "Operator: " << op << " Tag: " << tag << " \n"; };
		Operator(int o) :Token(Tag::OP), op(o) {};
		~Operator() {};
	};


	enum Ops {
		LESS_THAN, LESS_THAN_EQ, MORE_THAN, MORE_THAN_EQ, EQ, NOT_EQ, ASSIGN, NOT
	};
}

