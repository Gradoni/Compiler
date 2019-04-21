#include "lexer.h"

namespace lexer {
	lexer::lexer(std::string input_file)
	{
		reserve(Word(Tag::TRUE, std::string("true")));
		reserve(Word(Tag::FALSE, std::string("false")));
		source_file.open(input_file.c_str());
		target_file.open("result.txt");
	}

	void lexer::reserve(Word t)
	{
		words.insert({ t.lexemme, t });
	}

	std::unique_ptr<Token> lexer::scan()
	{
		//handle whitespaces and newlines
		for (; ; peek = source_file.get())
		{
			if (peek == ' ' || peek == '\t')
				continue;
			else if (peek == '\n')
				++line;
			else break;
		}
		//handle comments
		if (peek == '/')
		{
			peek = source_file.get();
			if (peek == '/')
			{
				while (true) {
					peek = source_file.get();
					if (peek == '\n')	
						break;				
				}
					
			}
			else if (peek == '*')
			{
				while (true)
				{
					peek = source_file.get();
					if (peek == '*')
					{
						peek = source_file.get();
						if (peek == '/')
						{
							peek = source_file.get();
							break;
						}
					}
				}
			}
			else {
				source_file.putback(peek);
				source_file.putback('/');
			}
		}
		//handle whitespaces and newlines added by exit from comments
		for (; ; peek = source_file.get())
		{
			if (peek == ' ' || peek == '\t')
				continue;
			else if (peek == '\n')
				++line;
			else break;
		}
		//handle relational operators
		if (peek == '<') {
			peek = source_file.get();
			if (peek == '=') {
				//handle <=
				peek = source_file.get();
				return std::make_unique<Operator>(Operator(Ops::LESS_THAN_EQ));
			}
			else {
				//handle <
				return std::make_unique<Operator>(Operator(Ops::LESS_THAN));
			} 
		}
		else if (peek == '>') {
			peek = source_file.get();
			if (peek == '=') {
				//handle >=
				peek = source_file.get();
				return std::make_unique<Operator>(Operator(Ops::MORE_THAN_EQ));
			}
			else {
				//handle >
				return std::make_unique<Operator>(Operator(Ops::MORE_THAN));
			}
		}
		else if (peek == '!') {
			peek = source_file.get();
			if (peek == '=') {
				//handle !=
				peek = source_file.get();
				return std::make_unique<Operator>(Operator(Ops::NOT_EQ));
			}
			else {
				//handle !
				return std::make_unique<Operator>(Operator(Ops::NOT));
			}
		}
		else if (peek == '=') {
			peek = source_file.get();
			if (peek == '=') {
				//handle ==
				peek = source_file.get();
				return std::make_unique<Operator>(Operator(Ops::EQ));
			}
			else {
				//handle =
				return std::make_unique<Operator>(Operator(Ops::ASSIGN));
			}
		}
		
		if (isdigit(peek)) {
			int v = 0;
			do {
				v = 10 * v + static_cast<char>(peek)-'0';
				peek = source_file.get();
			} while (isdigit(peek));
			return std::make_unique<Num>(Num{ v });
		}
		if (isalpha(peek)) {
			std::string s;
			do {
				s += static_cast<char>(peek);
				peek = source_file.get();
			} while (isalnum(peek));
			auto words_iterator = words.find(s);
			if (words_iterator == words.end())
			{
				Word w { Tag::ID, s };
				words.insert({ s, w });
				return std::make_unique<Word>(w);
			}
			else {
				return std::make_unique<Word>(words_iterator->second);
			}
		}
		Token t{ peek };
		return std::make_unique<Token>(t);
	}

	lexer::~lexer()
	{
		source_file.close();
		target_file.close();
	}

}

