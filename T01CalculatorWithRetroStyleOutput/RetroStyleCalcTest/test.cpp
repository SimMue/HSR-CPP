#include <iostream>
#include <string>
#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "sevensegment.h"
#include "calc.h"
#include "pocketcalculator.h"

void test_sevensegment_printLargeDigit() {
	std::ostringstream out;
	printLargeDigit(9, out);
	ASSERT_EQUAL(
		" _ \n"
		"|_|\n"
		" _|\n", out.str());
}

void test_sevensegment_printLargeNumbers() {
	std::ostringstream out;
	printLargeNumber(923, out);
	ASSERT_EQUAL(
		" _ "" _ "" _ \n"
		"|_|"" _|"" _|\n"
		" _|""|_ "" _|\n", out.str());
}

void test_sevensegment_printError() {
	std::ostringstream out;
	printError(out);
	ASSERT_EQUAL(
		" _ ""   ""   ""   ""   \n"
		"|_ "" _ "" _ "" _ "" _ \n"
		"|_ ""|  ""|  ""|_|""|  \n", out.str());
}

void test_calculator_calc() {
	int res{ 0 };
	ASSERT(tryCalc(5, 3, '*', res) == true);
	ASSERT(res == 15);
}

void test_calculator_calc_wrongInput() {
	int res{ 0 };
	ASSERT(tryCalc(5, 3, 'a', res) == false);
}

void test_calculator_calc_divideByZero() {
	int res{ 0 };
	ASSERT(tryCalc(7, 0, '/', res) == false);
}

void test_pocketcalculator_tryReadExpr() {
	std::string line = "3     / 10";
	int n1{ 0 };
	int n2{ 0 };
	char opr{};
	ASSERT(tryReadExpr(line, n1, n2, opr) == true);
	ASSERT_EQUAL(3, n1);
	ASSERT_EQUAL(10, n2);
	ASSERT_EQUAL('/', opr);
}

void test_pocketcalculator_tryReadExpr_WrongInput() {
	std::string line = "abc * def";
	int n1{ 0 };
	int n2{ 0 };
	char opr{' '};
	ASSERT(tryReadExpr(line, n1, n2, opr) == false);
	ASSERT_EQUAL(0, n1);
	ASSERT_EQUAL(0, n2);
	ASSERT_EQUAL(' ', opr);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s{};
	//TODO add your test here
	s.push_back(CUTE(test_sevensegment_printLargeDigit));
	s.push_back(CUTE(test_sevensegment_printLargeNumbers));
	s.push_back(CUTE(test_sevensegment_printError));
	s.push_back(CUTE(test_calculator_calc));
	s.push_back(CUTE(test_calculator_calc_wrongInput));
	s.push_back(CUTE(test_calculator_calc_divideByZero));
	s.push_back(CUTE(test_pocketcalculator_tryReadExpr));
	s.push_back(CUTE(test_pocketcalculator_tryReadExpr_WrongInput));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner{ cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	std::cin.get();
	return success;
}

int main(int argc, char const *argv[]) {
	return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}