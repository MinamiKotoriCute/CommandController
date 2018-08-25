#include "CommandController.h"

#include <regex>
#include <iostream>

void f1(int i, double d)
{
	printf("f1 %d %lf\n", i, d);
}

struct SS
{
	int n;
	bool b;

	friend std::istream& operator>>(std::istream &is, SS &other)
	{
		is >> other.n >> other.b;
		return is;
	}

	friend std::ostream& operator<<(std::ostream &os, const SS &other)
	{
		os << "{" << other.n << ", " << other.b << "}";
		return os;
	}
};

void f2(SS s)
{
	std::cout << "f2 " << s;
}

struct SS2
{
	SS s;
	double d;

	friend std::istream& operator>>(std::istream &is, SS2 &other)
	{
		is >> other.s >> other.d;
		return is;
	}

	friend std::ostream& operator<<(std::ostream &os, const SS2 &other)
	{
		os << "{" << other.s << ", " << other.d << "}";
		return os;
	}
};

void f3(SS2 s)
{
	std::cout << "f3 " << s;
}

int main()
{
	CommandController c;
	c.regist("f1", f1);
	c.regist("f2", f2);
	c.regist("f3", f3);

	std::regex reg(R"abc(([\w\.]+)|"([^"]+)")abc");
	std::string input;
	while (std::getline(std::cin, input))
	{
		auto begin = std::sregex_iterator(input.begin(), input.end(), reg);
		auto end = std::sregex_iterator();
		std::vector<std::string> command;
		for (auto it = begin; it != end; ++it)
		{
			if((*it)[1].str().empty())
				command.push_back((*it)[2].str());
			else
				command.push_back((*it)[1].str());
		}

		if (command.empty())
			continue;

		c.call(command);
	}


	return 0;
}

