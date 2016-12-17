#include "kwic.h"
#include "word.h"
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
#include <set>
std::set<std::vector<Wrd::Word>> read(std::istream & inputStream);
void print(std::set<std::vector<Wrd::Word>> lines, std::ostream & outputStream);
void addLineRotations(std::vector<Wrd::Word> & words, std::set<std::vector<Wrd::Word>> & lineRotations);
std::set<std::vector<Wrd::Word>> createLineRotations(std::set<std::vector<Wrd::Word>> lines);

std::set<std::vector<Wrd::Word>> read(std::istream & inputStream) {
	std::set<std::vector<Wrd::Word>> lines{};
	std::string line{};

	while (std::getline(inputStream, line) && line != "") {
		std::istringstream lineStream{ line };
		std::vector<Wrd::Word> words{ std::istream_iterator<Wrd::Word>{ lineStream }, std::istream_iterator<Wrd::Word>{} };
		lines.insert(words);
	}

	return lines;
}

void print(std::set<std::vector<Wrd::Word>> lines, std::ostream & outputStream) {
	std::for_each(lines.begin(), lines.end(), [&](std::vector<Wrd::Word> words) {
		std::copy(words.begin(), words.end(), std::ostream_iterator<Wrd::Word>{outputStream, " "});
		outputStream << '\n';
	});
}

void addLineRotations(std::vector<Wrd::Word> & words, std::set<std::vector<Wrd::Word>> & lineRotations)
{
	std::for_each(words.begin(), words.end(), [&](Wrd::Word word) {
		lineRotations.insert(words);
		std::rotate(words.begin(), words.begin() + 1, words.end());
	});
}

std::set<std::vector<Wrd::Word>> createLineRotations(std::set<std::vector<Wrd::Word>> lines) {
	std::set<std::vector<Wrd::Word>> lineRotations{};
	std::for_each(lines.begin(), lines.end(), [&lineRotations](std::vector<Wrd::Word> words) { addLineRotations(words, lineRotations); });
	return lineRotations;
}

void kwic(std::istream & inputStream, std::ostream & outputStream) {
	std::set<std::vector<Wrd::Word>> lines = read(inputStream);
	std::set<std::vector<Wrd::Word>> lineRotations = createLineRotations(lines);
	print(lineRotations, outputStream);
}