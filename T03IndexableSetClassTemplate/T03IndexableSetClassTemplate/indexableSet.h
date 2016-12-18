#ifndef indexableSet_h
#define indexableSet_h
#include <iterator>
#include <set>
namespace indexable {
	template<typename T, typename COMPARE = std::less<T>>
	class IndexableSet : public std::set<T, COMPARE> {
	public:
		using std::set<T, COMPARE>::set;
		IndexableSet() = default;

		T const & operator[] (int index) {
			
			if (index < 0 && -index < this->size()) {
				return *std::next(this->crend(), -index);
			}
			else if (index < this->size()) {
				return *std::next(this->cbegin(), index);
			}
			throw std::out_of_range("Index out of range!");
		}

		T const & front() {
			return this->operator[](0);
		}

		T const & back() {
			return this->operator[](this->size());
		}
	};
}


#endif // !indexableSet_h
