// SourceLine class member-function definitions.

#include <iostream>
using std::cout;

#include "SourceLine.h" // SourceLine class definition

SourceLine::SourceLine()
	: sourceLine()
{
}

SourceLine& SourceLine::operator=(const char* const ptr)
{
	sourceLine = ptr;
	return *this;
}

void SourceLine::delComments()//刪除註解
{
	unsigned len = sourceLine.size();
	if (len > 1)
		for (unsigned int i = 0; i < len - 1; i++)
			if (sourceLine[i] == '/' && sourceLine[i + 1] == '/')
			{
				sourceLine.erase(i, len - i);
				break;
			}

}

void SourceLine::delStrConst()//刪除雙引號字串
{
	for (int begin = 0; sourceLine[begin] != '\0'; begin++) {
		if (sourceLine[begin] == '\"')
		{
			int count = 1;
			while (sourceLine[begin + count] != '\"')
				count++;
			sourceLine.erase(begin, count);
		}
	}
}

void SourceLine::delCharConst()//刪除字元 
{
	size_t length = sourceLine.size();
	unsigned int begin;
	while (true)
	{
		begin = sourceLine.find('\'', 0);
		if (begin == string::npos)//判斷是否有讀到最後
			return;
		sourceLine.erase(begin, 3);
	}
}

void SourceLine::extractIdentifiers(vector< Identifier >& identifiers)
{
	int begin, end, length;
	string a;
	for (int i = 0; i <= sourceLine.size() - 1; i++) {
		if ((isalpha(sourceLine[i])) || (sourceLine[i] == '_'))  //遇到是字母或_
		{
			begin = i;  //標記第一個字母出現的位置
			i++;
			while ((isalnum(sourceLine[i])) || (sourceLine[i] == '_'))  //找不是字母數字或_的位置
				i++;

			end = i;
			length = end - begin;  //這串的長度
			a = sourceLine.substr(begin, length);//把identifier放到a
			identifiers.push_back(a);  //把a放到identifier陣列
		}
	}
}

bool operator==(const SourceLine& lhs, const SourceLine& rhs)
{
	return lhs.sourceLine == rhs.sourceLine;
}

bool operator!=(const SourceLine& lhs, const SourceLine& rhs)
{
	return !(lhs == rhs);
}