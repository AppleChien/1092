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

void SourceLine::delComments()//�R������
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

void SourceLine::delStrConst()//�R�����޸��r��
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

void SourceLine::delCharConst()//�R���r�� 
{
	size_t length = sourceLine.size();
	unsigned int begin;
	while (true)
	{
		begin = sourceLine.find('\'', 0);
		if (begin == string::npos)//�P�_�O�_��Ū��̫�
			return;
		sourceLine.erase(begin, 3);
	}
}

void SourceLine::extractIdentifiers(vector< Identifier >& identifiers)
{
	int begin, end, length;
	string a;
	for (int i = 0; i <= sourceLine.size() - 1; i++) {
		if ((isalpha(sourceLine[i])) || (sourceLine[i] == '_'))  //�J��O�r����_
		{
			begin = i;  //�аO�Ĥ@�Ӧr���X�{����m
			i++;
			while ((isalnum(sourceLine[i])) || (sourceLine[i] == '_'))  //�䤣�O�r���Ʀr��_����m
				i++;

			end = i;
			length = end - begin;  //�o�ꪺ����
			a = sourceLine.substr(begin, length);//��identifier���a
			identifiers.push_back(a);  //��a���identifier�}�C
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