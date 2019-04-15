#pragma once

namespace lexer {
	class Token
	{
	public:
		const int tag;
		Token(int t) : tag(t) {};
		virtual void print(std::ostream& stream) { stream << "Token: " << tag << " \n"; };
		virtual ~Token() {};
	};
	

	enum Tag
	{
		NUM = 256, ID, TRUE, FALSE, OP
	};
}

