#include <iostream>
#include <sstream> //support for istringstream and ostringstream
#include <string>
#include <vector>

class Student {
	std::vector<float> results;
public:
	std::string name;
	Student() = default;
	Student(std::string& s) : name(s) {};
	inline void append_result(float& result);
};

void Student::append_result(float &result) {
	this->results.push_back(result);
}

int main() {
	std::vector<Student> stu;
	Student stutemp;
	std::istringstream iss;
	std::ostringstream oss;
	std::string str;
	while (std::getline(std::cin, str)) {
		iss.str(str); //bind iss to std::string str
		iss >> stutemp.name; // >> operation
		float cur = 0.0, mmax = 0.0;
		while (iss >> cur)
			mmax < cur ? mmax = cur : 0;
		oss << stutemp.name << ' ' << mmax << '\n';
		//using oss to temporarily store the strings to print
		iss.clear();
		//std::istringstream::clear() makes iss available to bind to new string
	}
	std::cout << oss.str();
	return 0;
}