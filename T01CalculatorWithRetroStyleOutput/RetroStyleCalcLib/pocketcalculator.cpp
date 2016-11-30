#include <algorithm>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include "pocketcalculator.h"
#include "calc.h"
#include "sevensegment.h"

void calcInput(std::istream &inpStream, std::ostream &out)
{
	out << headerText;
	out << "Please insert an arithmetic expression:\n";
	std::string line{};
	std::getline(inpStream, line);
	while (line != "end") {
		int n1(0);
		int n2(0);
		char opr;
		int res(0);
		if (!tryReadExpr(line, n1, n2, opr) || !tryCalc(n1, n2, opr, res)) {
			printError(out);
			std::getline(inpStream, line);
			continue;
		}
		printLargeNumber(res, out);
		inpStream.clear();
		std::getline(inpStream, line);
	}
}

bool tryReadExpr(std::string line, int & n1, int & n2, char & opr)
{
	if (std::regex_match(line, std::regex("[ ]*[\\d]+[ ]*[\-|+||\*|/][ ]*[\\d]+[ ]*"))) {
		std::stringstream strStream(line);
		strStream >> n1;
		strStream >> opr;
		strStream >> n2;
		return true;
	}
	return false;
}

std::string headerText
(
	"############################################\n"
	"#                                          #\n"
	"#    Calculator with retro style output    #\n"
	"#    Allowed inputs are:                   #\n"
	"#           [Number] + [Number]            #\n"
	"#           [Number] - [Number]            #\n"
	"#           [Number] * [Number]            #\n"
	"#           [Number] / [Number]            #\n"
	"#                                          #\n"
	"#    To end the programm type: \"end\"       #\n"
	"#                                          #\n"
	"############################################\n"
	);
