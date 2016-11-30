#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_
#include <vector>

void printLargeDigit(int i, std::ostream &out);
void printLargeNumber(int n, std::ostream &out);
void printLargeNumber(std::vector<std::vector<std::string>> largeNumbers, std::ostream & out);
void printError(std::ostream & out);
std::vector<int> toVector(int n);
std::vector<std::vector<std::string>> convertToLargeDigits(std::vector<int> digits);
extern std::vector<std::vector<std::string>> numbers;
extern std::string error;

#endif // !SEVENSEGMENT_H_
