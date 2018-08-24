#include "CommandController.h"

void f1(int i, double d)
{
	printf("f1 %d %lf\n", i, d);
}

int main()
{
	CommandController c;
	c.regist("a", f1);

	c.call({ "a", "5", "9.487" });

	return 0;
}

