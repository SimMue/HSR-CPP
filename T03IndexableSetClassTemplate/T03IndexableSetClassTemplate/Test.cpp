#include "cute.h"
#include "ide_listener.h"
#include "xml_listener.h"
#include "cute_runner.h"
#include "indexableSet.h"
#include <sstream>
#include <string>
#include <cctype>

struct caselessCompare {
	using string = std::string;
	bool operator()(string const &l, string const &r) {
		return std::lexicographical_compare(l.begin(), l.end(), r.begin(), r.end(), [](char l, char r) {
			return std::tolower(l) < std::tolower(r);
		});
	}
};

void instantiate_like_set_vector_test() {
	std::vector<int> vector{ 3,1,4,1,5,9,2,6 };
	indexable::IndexableSet<int> indexSet{vector.begin(), vector.end()};
	
	ASSERT_EQUAL(3, indexSet[2]);
}

void add_some_values_pick_first_test() {
	indexable::IndexableSet<int> indexSet{};
	indexSet.insert(1);
	indexSet.insert(2);
	indexSet.insert(3);

	ASSERT_EQUAL(1, indexSet[0]);
}

void add_some_values_pick_last_reverse_test() {
	indexable::IndexableSet<int> indexSet{};
	indexSet.insert(1);
	indexSet.insert(2);
	indexSet.insert(3);

	ASSERT_EQUAL(3, indexSet[-1]);
}

void add_some_values_pick_first_reverse_test() {
	indexable::IndexableSet<int> indexSet{};
	indexSet.insert(1);
	indexSet.insert(2);
	indexSet.insert(3);

	ASSERT_EQUAL(1, indexSet[-(int)indexSet.size()]);
}

void add_some_values_pick_front_test() {
	indexable::IndexableSet<int> indexSet{};
	indexSet.insert(1);
	indexSet.insert(2);
	indexSet.insert(3);

	ASSERT_EQUAL(1, indexSet.front());
}

void add_some_values_pick_back_test() {
	indexable::IndexableSet<int> indexSet{};
	indexSet.insert(1);
	indexSet.insert(2);
	indexSet.insert(3);

	ASSERT_EQUAL(3, indexSet.back());
}

void out_of_range_test() {
	indexable::IndexableSet<int> indexSet{};
	indexSet.insert(1);

	ASSERT_THROWS(indexSet[1], std::out_of_range);
}

void caseless_Functor_test() {
	indexable::IndexableSet<std::string, caselessCompare> set{ "a", "B", "c" };
	ASSERT_EQUAL("a", set[0]);
}

void caseless_Functor2_test() {
	indexable::IndexableSet<std::string, caselessCompare> set{ "a", "B", "c" };
	ASSERT_EQUAL("B", set[1]);
}

bool runAllTests(int argc, char const *argv[]) {
	cute::suite s{};
	//TODO add your test here
	s.push_back(CUTE(instantiate_like_set_vector_test));
	s.push_back(CUTE(add_some_values_pick_first_test));
	s.push_back(CUTE(add_some_values_pick_last_reverse_test));
	s.push_back(CUTE(add_some_values_pick_first_reverse_test));
	s.push_back(CUTE(add_some_values_pick_front_test));
	s.push_back(CUTE(add_some_values_pick_back_test));
	s.push_back(CUTE(out_of_range_test));
	s.push_back(CUTE(caseless_Functor_test));
	s.push_back(CUTE(caseless_Functor2_test));
	
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto runner{ cute::makeRunner(lis, argc, argv) };
	bool success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const *argv[]) {
	return runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
}