#pragma once

namespace lexer {
	class Token
	{
	public:
		const int tag;
		Token(int t) : tag(t) {};
		
		~Token() {};
	};
	
	enum Tag
	{
		NUM = 256, ID, TRUE, FALSE
	};
}

