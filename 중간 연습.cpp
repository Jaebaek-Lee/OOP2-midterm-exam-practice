#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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

/*
void solution(string temp) {
	string ans;
	ans += temp[0];
	for (int i = 1; i < temp.size(); ++i) {

	}
	cout << ans;
}

int main() {
	string a;
	cin >> a;
	solution(a);
}
*/

// 과제 2 - static 멤버변수/함수, 동적할당
class Point {
public:
	Point() {
		++counter;
		cout << "\nPoint " << counter << " constructor.\n";
		cout << "Input x and y for Point: ";
		cin >> _x >> _y;
		while (true) {
			if ((_x < 1 || _y < 1) || (_x > 99 || _y > 99)) {
				cout << "Out of range. Input again\n";
				cout << "Input x and y for Point: ";
				cin >> _x >> _y;
			}
			else
				break;
		}
	}
	string toString() {
		ostringstream temp;
		if (_x < 10 && _y < 10) {
			temp << "x = 0" << _x << ", y = 0" << _y << '\n';
		}
		else if (_x < 10) {
			temp << "x = 0" << _x << ", y = " << _y << '\n';
		}
		else if (_y < 10) {
			temp << "x = " << _x << ", y = 0" << _y << '\n';
		}
		else {
			temp << "x = " << _x << ", y = " << _y << '\n';
		}
		return temp.str();
	}
	static int getCounter();
	~Point() {
		cout << "\nPoint " << counter << " destructor.";
		--counter;
	}
private:
	int _x;
	int _y;
	static int counter;
};

int Point::getCounter() { return counter; }
int Point::counter = 0; //응 static 안붙어~ 객체 없이도 사용 가능해야해서 전역 초기화야~

int main() {
	int num;
	cout << "The number of Point objects: " << Point::getCounter(); //static이긴 해도 private라 직접 접근 안되고 함수로.
	cout << "\nEnter the size of Point array: ";
	cin >> num;

	Point* point = new Point[num];

	cout << '\n';
	for (int i{ 0 }; i < num; ++i) {
		cout << point[i].toString() << '\n'; //원소에서 직접 접근하니까 -> 아니고 .
	}
	
	cout << "\nThe number of Point objects: " << Point::getCounter() << '\n';

	delete[] point;
}