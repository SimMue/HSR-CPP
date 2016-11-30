#ifndef POCKETCALCULATOR_H_
#define POCKETCALCULATOR_H_
#include <iosfwd>
#include <string>
void calcInput(std::istream &inpStream, std::ostream &outStream);
bool tryReadExpr(std::string line, int &n1, int &n2, char &opr);
extern std::string headerText;
#endif // !POCKETCALCULATOR_H_
