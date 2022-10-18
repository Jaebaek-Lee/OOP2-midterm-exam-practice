#include <iostream>

using namespace std;

/* 얕은 복사생성자
class Student {
private:
	int id;
	string name;
public:
	Student(int id, string name) {
		this->id = id;
		this->name = name;
		cout << "parameter constructor: " << this->id << " " << this->name << endl;
	}
	Student(const Student& origin) { //레퍼런스를 사용하지 않으면 무한복사... const: 함수 내에서 변경되지 않고 값만 사용함을 명시한다.
		this->name = origin.name;
		this->id = origin.id;
		cout << "copy constructor: " << this->id << " " << this->name << endl;
	}
};

int main() {
	Student s1{ 1, "pby" };
	Student s2{ s1 };
}
*/