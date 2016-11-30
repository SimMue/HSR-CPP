#include "calc.h"

int tryCalc(int n1, int n2, char opr, int &res)
{
	switch (opr) {
	case '+': res = n1 + n2; break;
	case '-': res = n1 - n2; break;
	case '*': res = n1 * n2; break;
	case '/': return tryDiv(n1, n2, res); break;
	default: return false;
	}
	return true;
}

bool tryDiv(int n1, int n2, int &res)
{
	if (n2 == 0) {
		return false;
	}
	res = n1 / n2;
	return true;
}
