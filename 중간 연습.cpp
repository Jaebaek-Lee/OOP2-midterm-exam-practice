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
/*
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
	string toString() const { //값을 내부에서 변경하면 안되는 단순 출력 함수이므로, const를 붙여서 내부에서 const만 사용할 수 있게 해준다.
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
	static int getCounter(); //일반적인 get에서는 const를 붙여서 내부 변수 수정을 막는게 좋다. 하지만 정적 변수는 객체 생성 전에 이미 존재한다. 이 안에서 객체의 변수를 사용할 일이 없다.
	//따라서 뒤에 static 아무짝에도 쓸모 없으므로, 금지된다.
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
*/

//얕은 복사, 깊은 복사, 이동생성자
/*
//클래스가 아닌 경우
int main() {
	const char* s1{ "jbl" };
	const char* s2{ s1 }; //얕은 복사
	char* s3{ new char[strlen(s1) + 1] }; //깊은 복사
	for (int i{ 0 }; s1[i] != '\0'; ++i) {
		s3[i] = s1[i];
	}
	s3[strlen(s1)] = '\0';
}
*/

/*
class Tmp {
public:
	Tmp(const char* name) : _name{ new char[strlen(name) + 1] } {//깊은 복사 수행문
		for (int i{ 0 }; name[i] != '\0'; ++i) {
			_name[i] = name[i];
		}
		_name[strlen(name)] = '\0';
	}
	Tmp(const Tmp& t) : Tmp{ t._name } {}//복사생성자
	void display() const {
		cout << _name << ' ' << static_cast<void*>(_name) << '\n';
	}
private:
	char* _name;
};

int main() {
	Tmp* ptr{ new Tmp{"jbl"} };
	Tmp t{ *ptr };
	ptr->display();
	delete ptr;
	t.display();
}
*/

//이동생성자
//const 객체는 const 멤버함수만. const멤함은 const 변수만
/*
class Tmp {
public:
	Tmp(const char* name) : _name{ new char[strlen(name) + 1] } {
		for (int i{ 0 }; name[i] != '\0'; ++i) {
			_name[i] = name[i];
		}
		_name[strlen(name)] = '\0';
	}
	Tmp(const Tmp& t) : Tmp{ t._name } { cout << "copy" << endl; }
	Tmp(Tmp&& t) noexcept : _name{ t._name } {
		cout << "move" << endl;
		t._name = nullptr;
	}
private:
	char* _name;
};

Tmp fun() {
	Tmp tmp{ "jbl" };
	return tmp;
}

int main() {
	Tmp t{ fun() };
}
*/

//과제 3

class Point {
	friend istream& operator>>(istream& input, Point& right) {//(x, y)
		input.ignore(255, '(');
		input >> right._x;//얘는 하나씩만 쓴다.
		input.ignore(255, ' ');
		input >> right._y;
		input.ignore();
		return input;
	}
	friend ostream& operator<<(ostream& output, const Point& right) {
		output << '(' << right._x << ", " << right._y << ")\n";
		return output;
	}
	friend int operator*(const Point& left, const Point& right) {
		return left._x * right._x + left._y * right._y;
	}
	friend Point& operator-=(Point& left, const Point& right) {
		left._x -= right._x;
		left._y -= right._y;
		return left;
	}
	friend Point operator++(Point& left, int) {//a++
		Point temp = left;
		++left._x;
		++left._y;
		return temp;
	}
	friend bool operator!=(const Point& left, const Point& right) {
		return ((left._x != right._x) && (left._y != right._y));
	}
	friend bool operator<=(const Point& left, const Point& right) {
		return ((left._x + left._y) <= (right._x + right._y));
	}
public:
	Point() : _x{ 0 }, _y{ 0 } {}
	bool operator==(const Point& right) {
		return ((_x == right._x) && (_y == right._y));
	}
	bool operator>(const Point& right) {
		return ((_x + _y) > (right._x + right._y));
	}
	Point operator+(const Point& right) const{ // a + b * c // a * b + c - 안됨. 얘는 friend로 따로 해줘야함. // a + b + c ㄱㄴ. cout << a + b - <<는 우측에 RV도 받을 수 있게 설계
		Point temp;
		temp._x = _x + right._x;
		temp._y = _y + right._y;
		return temp;
	}
	Point& operator++() {//++p1
		++_x; ++_y;
		return *this;
	}
	Point& operator+=(const Point& right) {
		_x += right._x;
		_y += right._y;
		return *this;
	}
	Point(const Point& right) {//=연산자였다면, 객체 전체를 바꾸는거라 friend로도 좀 위험. 멤버로 강제됨. 근데 그거 없이 그냥 복사생성자로...
		_x = right._x;
		_y = right._y;
	}
private:
	int _x, _y;
};

int main() {
	Point p1, p2;
	cout << "Input 2 points: ";
	cin >> p1 >> p2;

	if (p1 == p2) cout << "p1 == p2" << endl;
	if (p1 != p2) cout << "p1 != p2" << endl;
	if (p1 > p2) cout << "p1 > p2" << endl;
	if (p1 <= p2) cout << "p1 <= p2" << endl;

	cout << endl;
	cout << "p1 + p2 = " << (p1 + p2) << endl;
	cout << "p1 * p2 = " << (p1 * p2) << endl;

	cout << endl;
	p1 -= p2++;
	cout << "p1 -= p2++" << endl;
	++p1 += p2;
	cout << "++p1 += p2" << endl;
	cout << "p1 = " << p1 << endl;
	//cout << p2;
	//p2 = (p2++)++; 임시객체는 객체는 맞지만, return되면서 메모리가 불분명해진다. 그냥 값만 가지고 오는 것. 따라서 rv가 된다. 이렇게 쓰려면 후위연산자가 rv를 받을 수 있게
	//const Point&로 변수를 받아야하는데, 이러면 ㅋㅋ 값 올리기가 불가능해져서 에러 발생. 그럼 Point&&로 한다면? 그럼 첫 번째 연산이 불가능해질 것.
	//cout << "\n" << p2;
}


//상속
//protacted는 관련된(상속된) 클래스에서는 자유롭게 사용 가능. but main같은 비연관 스코프에서는 사용 불가능.
//변수 가리기
//메인에서 파생 클래스만 호출하면, 파생클래스의 생성자 호출 - 파생클래스 내부 들어가기 전에 베이스 클래스의 "디폴트 기본 생성자"를 호출한다.
//그런데 만약 베이스 클래스에 디폴트 기본 생성자가 없고 사용자 정의 생성자가 정의되어있다면, 에러가 발생한다.
//해결 방법 - 멤버 이니셜라이저 리스트에서 베이스 클래스의 생성자를 직접 호출해준다.

//디폴트 생성자의 종류 - 기본생성자, 복사생성자, 이동생성자, 대입연산자, 이동대입연산자

//copy and paste의 단점 : 비용이 많이 발생한다. 수정이 어렵다. 악몽이 발생할 수 있다.

//protected의 단점 : 코드의존도가 높아진다. 베이스 클래스에서 변수에 조건이라도 걸어뒀다면, 파생에서 그 값을 바꿨을때 문제가 생긴다.

//다중 상속위 위험성 : 베이스의 함수 temp를 파생함수 a와 b가 갖는다. 그리고 a와 b를 다중상속받은 c에서temp를 호출하면 a건지 b건지 모호해짐.

//public 상속 - 부모의 private 빼고는 다 그대로 받아서 사용가능. protected 상속 - private는 못건들고, 나머지 부모의 public과 protected를 protected로 사용.
//private 상속 - 부모의 private는 여전히 접근 불가능. 부모의 public, protected를 private로 만들어 상속.
//부모의 private를 사용할 수 있는 유일한 방법 : 부모의 함수로 접근. friend는 부모에 직접 friend를 선언하지 않은 이상, 파생에 friend 사용해도 접근 불가능. 파생의 친구는
//파생의 친구일 뿐, 부모의 친구는 아니다.

/*
class A {
//private
	int a;
	int b;
	//A(int x, int y) { a = x; b = y; } //이자식이 있으면 파생 클래스의 생성 단계에서 디폴트 기본 생성자를 호출할 수가 없다.
	int getA() { return a; }
//public:
	void setA(int temp) { a = temp; }
};

class B : public A {
	friend void main();
	int c;
};

void main() {
	A a(2, 3);  //에러. 전용 생성자를 호출하려함.
	a.getA();   //에러. 전용 멤버 함수를 호출하려함.
	B b;
	b.c = 3;
	b.a = 3; //안된다.
	b.setA(5); //마찬가지로 private면 접근 불가.
}
*/