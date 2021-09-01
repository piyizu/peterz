#include <iostream>
#include <array>
#include <forward_list>
#include <string>

std::forward_list<std::string>::iterator replace(
	std::forward_list<std::string>& sflst, std::string to_find, std::string to_insert_after) {
	/*This function insert to_insert_after after the element in sflst whose value equals to_find's. 
	* If no such element exists in sflst, to_insert_after will be inserted to the end of the fwd_list.
	* If there are more than one eligible elements, only the first will be affected.
	*/
	auto pre = sflst.before_begin();
	//pre stands for predecessor, which is important in forward_list insertion.
	auto cur = sflst.begin();
	while (cur != sflst.end()) {
		if (*cur == to_find) {
			cur = sflst.insert_after(cur, to_insert_after);
			return cur;
		}
		else {
			++pre;
			++cur;
		}
	}
	pre = sflst.insert_after(pre, to_insert_after);
	return pre;
}

int main() {
	std::forward_list<std::string> string_forward_list;
	std::array<std::string, 5> string_array{
		"Ava", "Besa", "Gala", "Delta", "Epison"
	};
	string_forward_list.assign(string_array.begin(), string_array.end());
	//using assign(), const char* elements will be converted to std::string ones.
	std::cout << *replace(string_forward_list, std::string("Gala"), std::string("Where is Celia?") ) << std::endl;
	//The std::cout... above does nothing more than showing what is returned by insert_after().
	for (auto& s : string_forward_list)
		std::cout << s << std::endl;
	return 0;
}