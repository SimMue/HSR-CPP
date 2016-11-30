#include "sevensegment.h"
#include <algorithm>
#include <iterator>
#include <string>

void printLargeDigit(int i, std::ostream & out)
{
	std::vector<std::string> digit = numbers.at(i);
	copy(begin(digit), end(digit), std::ostream_iterator<std::string>(out, "\n"));
}

void printLargeNumber(int n, std::ostream & out)
{
	std::vector<int> digits = toVector(n);
	std::vector<std::vector<std::string>> largeDigits = convertToLargeDigits(digits);
	if (largeDigits.size() > 8) {
		printError(out);
		return;
	}
	printLargeNumber(largeDigits, out);
}

std::vector<int> toVector(int n)
{
	std::string s = std::to_string(n);
	std::vector<int> vec(s.size());
	std::transform(begin(s), end(s), begin(vec), [](char c) {return c - '0'; });
	return vec;
}

std::vector<std::vector<std::string>> convertToLargeDigits(std::vector<int> digits)
{
	std::vector<std::vector<std::string>> largeDigits(digits.size());
	std::transform(begin(digits), end(digits), begin(largeDigits), [](int digit) {return numbers.at(digit); });
	return largeDigits;
}

void printLargeNumber(std::vector<std::vector<std::string>> largeDigits, std::ostream & out)
{
	std::vector<std::string> lines(3);
	std::for_each(begin(largeDigits), end(largeDigits), [&](std::vector<std::string> vec) { lines[0] += vec.at(0); lines[1] += vec.at(1); lines[2] += vec.at(2);  });
	copy(begin(lines), end(lines), std::ostream_iterator<std::string>(out, "\n"));
}

void printError(std::ostream &out)
{
	out << error;
}

std::vector<std::vector<std::string>> numbers
{
	{
		" _ ",
		"| |",
		"|_|"
	},
	{
		"   ",
		"  |",
		"  |"
	},
	{
		" _ ",
		" _|",
		"|_ "
	},
	{
		" _ ",
		" _|",
		" _|"
	},
	{
		"   ",
		"|_|",
		"  |"
	},
	{
		" _ ",
		"|_ ",
		" _|"
	},
	{
		" _ ",
		"|_ ",
		"|_|"
	},
	{
		" _ ",
		"  |",
		"  |"
	},
	{
		" _ ",
		"|_|",
		"|_|"
	},
	{
		" _ ",
		"|_|",
		" _|"
	}
};


std::string error{
	" _ ""   ""   ""   ""   \n"
	"|_ "" _ "" _ "" _ "" _ \n"
	"|_ ""|  ""|  ""|_|""|  \n"
};