# Задачи и теория - подготовка за контролно 2 на Софтуерно Инженерство

## Част 1 - теоретични въпроси

<details>
<summary> <b>Задача първа</b> </summary>

#### Ще се компилират ли следните примери?

```c++
class A {
    int a;
public:
    std::ostream& operator<<(std::ostream& os) {
        return os << a;
    }
};

int main() {
    A a;
    std::cout << a;
}
```
</details>

<details>
<summary> <b> Задача втора </b> </summary>

#### Какво ще се отпечата на конзолата?

```c++
class A {
	~A() {
		std::cout << "Destr" << std::endl;
	}
};

void f() {
	A a;
	throw std::exception();
}

int main() {
	f();
	return 0;
}
```

```c++
class A {
	~A() {
		std::cout << "Destr" << std::endl;
	}
};

void f() {
	A a;
	throw std::exception();
}

int main() {
	try {
		f();
	} catch (...) {
		std::cout << "Unknown error"<< std::endl;
	} catch (const std::exception& e) {
		std::cout << "Exception"<< std::endl;
	}

	return 0;
}
```

```c++
class A {
	~A() {
		std::cout << "Destr" << std::endl;
	}
};

void f() {
	A* a = new A();
	throw std::exception();

	delete a;
}

int main() {
	try {
		f();
	} catch (...) {	} 
	
	return 0;
}
```
</details>

<details>
<summary> <b> Задача трета </b> </summary>

#### Има ли проблем в следния код?

```c++
class MyClass {
	static int unique_id = 0;
	
public:
	MyClass() {
		unique_id++;
	}
};
```
</details>

<details>
<summary> <b> Задача четвърта </b> </summary>

#### Какво ще се изведе на конзолата?

```c++
#include<iostream>

void g(int&&) {
	std::cout << "RValue";
}

void g(int&) {
	std::cout << "LValue";
}

void f(int&& a) {
	g(a);
}

int main() {
	int i = 0;

	f(std::move(i));
}
```
```c++
#include<iostream>

void g(int&&) {
	std::cout << "RValue";
}

void g(int&) {
	std::cout << "LValue";
}

void f(int&& a) {
	g(a);
}

int main() {
	int i = 0;

	f(i);
}
```

```c++
#include<iostream>

void g(int&&) {
	std::cout << "RValue";
}

void g(int&) {
	std::cout << "LValue";
}

void f(int&& a) {
	g(std::move(a));
}

int main() {
	int i = 0;

	f(std::move(i));
}
```

```c++
#include<iostream>

void g(const int&) {
	std::cout << "LValue";
}

void f(int&& a) {
	g(std::move(a));
}

int main() {
	int i = 0;

	f(std::move(i));
}
```

</details>

<details>
<summary> <b> Задача пета </b> </summary>

#### Компилира ли се този код и ако да, кои от функциите ще се извикат?

```c++
class A {};

class B : public A {};

void f(A& obj) { std::cout << "f:a" << std::endl; }
void f(B& obj) { std::cout << "f:b" << std::endl; }
void t(B& obj) { std::cout << "t:b" << std::endl; }

int main() {
    A obj1;
    B obj2;

    f(obj1);
    f(obj2);

    t(obj2);
    t(obj1);

    return 0;
}
```

</details>

<details>
<summary> <b> Задача шеста </b> </summary>

#### Ще се компилира ли следният код и ако да, какво ще се изведе на конзолата?

```c++
class A {
    int a;

public:
    A(int a) : a(a) {}
    void f() const {
        std::cout << a;
    }
};

template <typename T>
void f(const T& t) {
    t.f();
}

template <typename T>
void g(const T& t) {
    t.g();
}

int main() {
    f<A>(5);
    return 0;
}
```

</details>

<details>
<summary> <b> Задача седма </b> </summary>

Какво ще изведе кодът на конзолата?

```c++
#include<iostream>

template<class K, class V>
struct Entity {
	void print(const K& k, const V& v) {
		std::cout << k + v;
	}
};

template<class T>
struct Entity<int, T> {
	void print(int k, const T& t) {
		std::cout << 2 * k + t;
	}
};

int main() {
	Entity<int, int> e;
	e.print(2, 3);
}
```

</details>

<details>
<summary> <b> Задача осма </b> </summary>

#### Има ли проблем в кода?

```c++
class A {
	int a;
public:
	A(int a) a(a) {}
}

class B : public A {
	//динамични член-данни
public:
	B() = default;

	B(const B& other) {
		copyFrom(other);
	}

	B(B&& other) {
		moveFrom(other);
	}

	B& operator=(const B& other) {
		if (this != &other) {
			A::operator=(other);
			free();
			copyFrom(other);
		}
		return *this;
	}

	B& operator=(B&& other) {
		if (this != &other) {
			A::operator=(other);
			free();
			moveFrom(other);
		}
		return *this;
	}

	~B() {
		free();
	}
};
```

</details>

<details>
<summary> <b> Задача девета </b> </summary>

#### Има ли проблем в кода?
```c++
#include <iostream>

class Animal {
public:
	virtual void makeSound() const = 0;
};

class Dog : public Animal {
	char* breed;

public:
	void makeSound() override {
		std::cout << "Woof!" << std::endl;
	}
//G6

};

class Cat : public Animal {
public:
	void makeSound() override {
		std::cout << "Meow!" << std::endl;
	}
};

int main() {
	Animal* animal1 = new Animal();
	Animal* animal2 = new Dog();
	Animal* animal3 = new Cat();
	
	animal1->makeSound();
	animal2->makeSound();
	animal3->makeSound();
	
	delete animal1;
	delete animal2;
	delete animal3;

	return 0;
}
```

</details>

<details>
<summary> <b> Задача десета </b> </summary>

#### Какъв е размерът на следните структури?

```c++
struct A {
    int32_t a;
    static double b;
    char c;
};

struct B : A {
    int32_t* ptr;
};

struct C : B {
    char c;
};
```

```c++
struct A {
    char ch1;
    char ch2;

    virtual ~A() = default;
};

struct B : A {
    int32_t ch1;
};
```

</details>

<details>
<summary> <b> Задача единадесета </b> </summary>

#### Какво съдържат виртуалните таблици на следните структури:

```c++
struct A {
	virtual void f();
	virtual void g();
	void k();
};

struct B : public A {
	void f() override;
	virtual void h();
};

struct C : public B {
	int f() override;
};
```

```c++
struct A {
	virtual void f() final;
	virtual void g() final;
	void k();
};

struct B : public A {
	void f() override;
	virtual void h();
};

struct C : public B {
	int f() override;
};
```

</details>

<details>
<summary> <b> Задача дванадесета </b> </summary>

#### Има ли проблем следния код?

```c++
#include<iostream>

struct A {
	int x;
	
	A(int x) : x(x) {}
}

struct B : public A {
	int y;

	B(int x, int y) : A(x), y(y) {}
};

struct C : public B {
	int z;
	
	C(int x, int y, int z) : A(x), B(x, y), z(z) {}
};

int main() {
	C c(1, 2, 3);
	std::cout << c.z;
	return 0;
}
```
</details>

## Част 2 - задачи

# Задача първа
Да се имплементира темплейтен хетерогенен контейнер. Трябва да се поддържат функции за добавяне и достъпване на елементите на контейнера.

# Задача втора
Ще реализираме система, която следи за различни промени и при тяхната поява предприема различни действия. В разработката на тази система ще имаме два основни момента.

## Построяване на системата
Системата трябва да може да бъде построена от потребителя.

## Стартиране на системата
След като системата бъде построена от потребителя, тя започва да слуша за промени.

## Видове събития
Системата ни ще може да следи за два вида събития.
1. Промяна на подаден файл 
   - Всеки път, когато файл се промени, потребителят трябва да е известен за това с подходящо съобщение.
2. Период от време 
   - Всеки път, когато мине някакво време (в секунди), потребителят трябва да бъде известен за това с подходящо съобщение.

## Видове известия
1. Логване във файл 
   - При регистриране на някакво събитие, съобщението от него трябва да бъде логван във файл.
2. Изписване на стандартния изход 
   - При регистриране на някакво събитие, съобщението от него трябва да бъде изписван на стандартния изход.

## Добавяне на събития и известия
Събитията и известията ще бъдат представяни чрез низове. Низовете следват следния формат
1. Събития:
   1. Ако започва с `f`, то събитието следи за промяна по файла. Следващите символи представляват локацията на файла
   2. Ако започва с `t`, то събитието следи за изминало време. Следващите символи са времето в секунди, което трябва да измине. Действието ще ограничим до изпращане на съобщение, че времето е минало (въпреки, че това лесно може да се промени до каквото решим).
2. Известия
   1. Ако стойността на низа е `stdout`, то събитието се записва на стандартния изход
   2. Ако стойността на низа започва с `f`, то събитието се записва във файл. Следващите символи са пътя към файла.

## Примерен интерфейс
```cpp

int main()
{
    EventManager e;

    e.addEvent("ffile.txt");
    e.addEvent("t30");

    e.addObserver("stdout");
    e.addObserber("foutfile.txt");

    // При промяна на file.txt и на всеки 30 секунди
    // във файла outfile.txt и на стандартния изход ще се 
    // изписват съответните съобщения.
    e.run();
}
```
