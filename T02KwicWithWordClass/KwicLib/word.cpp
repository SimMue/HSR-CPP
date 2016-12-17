#include "word.h"
#include <istream>
#include <ostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cctype>
#include <string>
#include <stdexcept>

Wrd::Word::Word(const std::string value) {
	if (!isValidWord(value)) throw std::invalid_argument{ "Es können keine leeren Worte erstellt werden" };
	this->value = value;
};

bool Wrd::Word::isValidWord(const std::string value) {
	if (value.empty())
		return false;

	return std::all_of(value.begin(), value.end(), [](char c) { return std::isalpha(c); });;
}

void Wrd::Word::skipNonAlphabetics(std::istream & inputStream) {
	while (!std::isalpha(inputStream.peek()) && inputStream.good()) {
		inputStream.ignore();
	}
}

bool Wrd::Word::tryReadAlphabetics(std::istream & inputStream, std::string & content) {
	while (std::isalpha(inputStream.peek())) {
		char c;
		inputStream >> c;
		content += c;
	}
	return !content.empty();
}

void Wrd::Word::read(std::istream & inputStream) {
	this->skipNonAlphabetics(inputStream);
	std::string content{};
	if (this->tryReadAlphabetics(inputStream, content)) {
		this->value = content;
		inputStream.clear();
	}
	else {
		inputStream.setstate(std::ios::failbit | inputStream.rdstate());
	}
}

std::istream & Wrd::operator>>(std::istream & inputStream, Wrd::Word & word) {
	word.read(inputStream);
	return inputStream;
}

std::ostream & Wrd::operator<<(std::ostream & outputStream, const Wrd::Word & word) {
	outputStream << word.value;
	return outputStream;
}

bool Wrd::Word::operator<(Wrd::Word const & other) const {
	return std::lexicographical_compare(this->value.begin(), this->value.end(), other.value.begin(), other.value.end(), [](char c1, char c2) {
		return std::tolower(c1) < std::tolower(c2);
	});
}

bool Wrd::Word::operator>(Wrd::Word const & other) const {
	return other < *this;
}

bool Wrd::Word::operator>=(Wrd::Word const & other) const {
	return !(*this < other);
}

bool Wrd::Word::operator<=(Wrd::Word const & other) const {
	return !(*this > other);
}

bool Wrd::Word::operator==(Wrd::Word  const & other) const {
	return !(*this < other) && !(other < *this);
}

bool Wrd::Word::operator!=(Wrd::Word const & other) const {
	return !(*this == other);
}
