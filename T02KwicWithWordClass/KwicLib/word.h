#ifndef word_h
#define word_h
#include <iosfwd>
#include <string>

namespace Wrd {
	class Word {
	private:
		std::string value;
		bool tryReadAlphabetics(std::istream & inputStream, std::string & content);
		void skipNonAlphabetics(std::istream & inputStream);
		void read(std::istream & inputStream);
		bool isValidWord(const std::string value);
	public:
		Word() = default;
		explicit Word(const std::string value);
		friend std::istream & operator>>(std::istream & inputStream, Word & word);
		friend std::ostream & operator<<(std::ostream & outputStream, const Word & word);
		bool operator<(const Word & other) const;
		bool operator>(const Word & other) const;
		bool operator>=(const Word & other) const;
		bool operator<=(const Word & other) const;
		bool operator==(const Word & other) const;
		bool operator!=(const Word & other) const;
	};
}
#endif // !word_h
