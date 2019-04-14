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

	Token lexer::scan()
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
		//handle whitespaces and newlines
		for (; ; peek = source_file.get())
		{
			if (peek == ' ' || peek == '\t')
				continue;
			else if (peek == '\n')
				++line;
			else break;
		}
		if (isdigit(peek)) {
			int v = 0;
			do {
				v = 10 * v + static_cast<char>(peek)-'0';
				peek = source_file.get();
			} while (isdigit(peek));
			Num n{ v };
			target_file << "Value: " << n.value << " " <<  "Tag: " << n.tag << '\n';
			return n;
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
				target_file << "Lexemme: " << w.lexemme << " " << "Tag: " << w.tag << '\n';
				return w;
			}
			else {
				target_file << "Lexemme: " << words_iterator->second.lexemme << " " << "Tag: " << words_iterator->second.tag << '\n';
				return words_iterator->second;
			}
		}
		Token t{ peek };
		if (t.tag != EOF) {
			target_file << "Token: " << static_cast<char>(t.tag) << '\n';
		}
		return t;
	}

	lexer::~lexer()
	{
		source_file.close();
		target_file.close();
	}

}

