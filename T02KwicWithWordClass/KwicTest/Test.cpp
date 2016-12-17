#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "kwic.h"
#include "word.h"
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

void test_kwic() {
	std::istringstream inputStream{
		"this is a test\n"
		"another test this is\n"
		"\n" };

	std::ostringstream outputStream{};
	kwic(inputStream, outputStream);
	ASSERT_EQUAL(
		"a test this is \n"
		"another test this is \n"
		"is a test this \n"
		"is another test this \n"
		"test this is a \n"
		"test this is another \n"
		"this is a test \n"
		"this is another test \n", outputStream.str());
}

void test_cannot_create_empty_word() {
	ASSERT_THROWS(Wrd::Word{ "" }, std::invalid_argument);
}

void test_cannot_create_word_with_space() {
	ASSERT_THROWS(Wrd::Word{ "abc xyz" }, std::invalid_argument);
}

void test_cannot_create_word_with_number() {
	ASSERT_THROWS(Wrd::Word{ "abc3xyz" }, std::invalid_argument);
}

void test_cannot_create_word_with_punctuation() {
	ASSERT_THROWS(Wrd::Word{ "abc.xyz" }, std::invalid_argument);
}

void test_output_operator() {
	std::string const expected{ "Python" };
	Wrd::Word const w{ expected };
	std::ostringstream output{};
	output << w;
	ASSERT_EQUAL(expected, output.str());
}

void test_same_words_are_equal() {
	ASSERT_EQUAL(Wrd::Word{ "Ruby" }, Wrd::Word{ "Ruby" });
}

void test_different_words_are_not_equal() {
	ASSERT_NOT_EQUAL_TO(Wrd::Word{ "Haskell" }, Wrd::Word{ "ML" });
}

void test_same_word_with_different_cases_are_equal() {
	ASSERT_EQUAL(Wrd::Word{ "BASIC" }, Wrd::Word{ "basic" });
}

void test_same_word_is_not_lower_than() {
	ASSERT(!(Wrd::Word{ "Erlang" } < Wrd::Word{ "Erlang" }));
}

void test_smaller_word_is_smaller() {
	ASSERT_LESS(Wrd::Word{ "Erlang" }, Wrd::Word{ "Fortran" });
}

void test_smaller_word_with_capital_letters_is_smaller() {
	ASSERT_LESS(Wrd::Word{ "ADA" }, Wrd::Word{ "java" });
}

void test_same_word_with_different_cases_are_not_smaller() {
	ASSERT(!(Wrd::Word{ "Groovy" } < Wrd::Word{ "groovy" }));
}

void test_greater_word_is_greater() {
	ASSERT_GREATER(Wrd::Word{ "Rust" }, Wrd::Word{ "Prolog" });
}

void test_greater_word_with_capital_letters_is_greater() {
	ASSERT_GREATER(Wrd::Word{ "Lisp" }, Wrd::Word{ "brainfuck" });
}

void test_smaller_word_is_less_equal() {
	ASSERT_LESS_EQUAL(Wrd::Word{ "Algol" }, Wrd::Word{ "BCPL" });
}

void test_same_word_is_less_equal() {
	ASSERT_LESS_EQUAL(Wrd::Word{ "Assembler" }, Wrd::Word{ "Assembler" });
}

void test_greater_word_is_greater_equal() {
	ASSERT_GREATER_EQUAL(Wrd::Word{ "RPG" }, Wrd::Word{ "Perl" });
}

void test_same_word_is_greater_equal() {
	ASSERT_GREATER_EQUAL(Wrd::Word{ "Scala" }, Wrd::Word{ "Scala" });
}

void test_input_operator_single_word() {
	std::istringstream input{ "Elixir" };
	Wrd::Word w{};
	input >> w;
	ASSERT_EQUAL(Wrd::Word{ "Elixir" }, w);
}

void test_input_operator_single_word_stream_good() {
	std::istringstream input{ "Cobol" };
	Wrd::Word w{};
	ASSERT(input >> w);
}

void test_input_operator_called_once_first_word() {
	std::istringstream input{ "Ceylon Go" };
	Wrd::Word w{};
	input >> w;
	ASSERT_EQUAL(Wrd::Word{ "Ceylon" }, w);
}

void test_input_operator_called_once_stream_good() {
	std::istringstream input{ "Lua Oberon" };
	Wrd::Word w{};
	ASSERT(input >> w);
}

void test_input_operator_on_empty_stream_fail() {
	std::istringstream input{};
	Wrd::Word w{};
	input >> w;
	ASSERT(input.fail());
}

void test_input_operator_on_stream_without_word() {
	std::istringstream input{ "1337" };
	Wrd::Word w{};
	input >> w;
	ASSERT(input.fail());
}

void test_input_operator_on_empty_stream_word_unchanged() {
	std::istringstream input{};
	Wrd::Word w{ "Eiffel" };
	input >> w;
	ASSERT_EQUAL(Wrd::Word{ "Eiffel" }, w);
}

void test_input_operator_stops_on_slash() {
	std::istringstream input{ "PL/SQL" };
	Wrd::Word w{};
	input >> w;
	ASSERT_EQUAL(Wrd::Word{ "PL" }, w);
}

void test_input_operator_stops_at_end_of_word() {
	std::istringstream input{ "VB6" };
	Wrd::Word w{};
	int i{};
	input >> w >> i;
	ASSERT_EQUAL(6, i);
}

void test_input_operator_skips_leading_non_alpha() {
	std::istringstream input{ "3switchBF" };
	Wrd::Word w{};
	input >> w;
	ASSERT_EQUAL(Wrd::Word{ "switchBF" }, w);
}

void test_input_operator_overwrites_word() {
	std::istringstream input{ "Kotlin" };
	Wrd::Word w{ "JavaScript" };
	input >> w;
	ASSERT_EQUAL(Wrd::Word{ "Kotlin" }, w);
}

void test_exercise_example() {
	std::istringstream input{ "compl33tely ~ weird !!??!! 4matted in_put" };
	Wrd::Word w{};
	input >> w;
	ASSERT_EQUAL(Wrd::Word{ "compl" }, w);
	input >> w;
	ASSERT_EQUAL(Wrd::Word{ "tely" }, w);
	input >> w;
	ASSERT_EQUAL(Wrd::Word{ "weird" }, w);
	input >> w;
	ASSERT_EQUAL(Wrd::Word{ "matted" }, w);
	input >> w;
	ASSERT_EQUAL(Wrd::Word{ "in" }, w);
	input >> w;
	ASSERT_EQUAL(Wrd::Word{ "put" }, w);
	input >> w;
	ASSERT_EQUAL(Wrd::Word{ "put" }, w);
}


bool runAllTests(int argc, char const *argv[]) {
	cute::suite s{};
	//TODO add your test here
	
	s.push_back(CUTE(test_kwic));
	s.push_back(CUTE(test_cannot_create_empty_word));
	s.push_back(CUTE(test_cannot_create_word_with_space));
	s.push_back(CUTE(test_cannot_create_word_with_number));
	s.push_back(CUTE(test_cannot_create_word_with_punctuation));
	s.push_back(CUTE(test_output_operator));
	s.push_back(CUTE(test_same_words_are_equal));
	s.push_back(CUTE(test_same_word_with_different_cases_are_equal));
	s.push_back(CUTE(test_same_word_is_not_lower_than));
	s.push_back(CUTE(test_smaller_word_with_capital_letters_is_smaller));
	s.push_back(CUTE(test_smaller_word_is_smaller));
	s.push_back(CUTE(test_greater_word_is_greater));
	s.push_back(CUTE(test_greater_word_with_capital_letters_is_greater));
	s.push_back(CUTE(test_smaller_word_is_less_equal));
	s.push_back(CUTE(test_same_word_is_less_equal));
	s.push_back(CUTE(test_greater_word_is_greater_equal));
	s.push_back(CUTE(test_same_word_is_greater_equal));
	s.push_back(CUTE(test_different_words_are_not_equal));
	s.push_back(CUTE(test_input_operator_single_word));
	s.push_back(CUTE(test_input_operator_called_once_first_word));
	s.push_back(CUTE(test_input_operator_called_once_stream_good));
	s.push_back(CUTE(test_input_operator_single_word_stream_good));
	s.push_back(CUTE(test_input_operator_on_empty_stream_fail));
	s.push_back(CUTE(test_input_operator_on_empty_stream_word_unchanged));
	s.push_back(CUTE(test_input_operator_stops_on_slash));
	s.push_back(CUTE(test_input_operator_stops_at_end_of_word));
	s.push_back(CUTE(test_input_operator_skips_leading_non_alpha));
	s.push_back(CUTE(test_same_word_with_different_cases_are_not_smaller));
	s.push_back(CUTE(test_input_operator_overwrites_word));
	s.push_back(CUTE(test_input_operator_on_stream_without_word));
	s.push_back(CUTE(test_exercise_example));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner{ cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
	return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}
