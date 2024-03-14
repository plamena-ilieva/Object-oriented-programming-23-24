## Двоични файлове
- лесни за четене от машина, трудни за четене от човек
- за четене и писане в двоични файлове използваме функциите:

    `write (const char* s, streamsize n);` 
    - `s` е указател към мястото в паметта, от където взимаме байтовете, които записваме във файла
    - `n` указва броя байтове, които записваме във файла <br>

    `read (char* s, streamsize n);`
   - `s` е указател към мястото в паметта, където записваме байтовете, които сме прочели от файла
    - `n` указва броя байтове, които четем от файла <br> 
- функциите приемат `char*`, затова, ако искаме да запазим друг тип данни, трябва експлицитно да ги преобразуваме към `char*` (едни и същи байтове се интеропретират по различен начин)

```cpp
#include<fstream>

int main() {
    std::ofstream outFile("file.txt", std::ios::binary);

    int x = 26;

    //трябва ни адреса на x, затова използваме &x
    outFile.write((const char*)&x, sizeof(x));

    outFile.close();
}
```

```cpp
#include<iostream>
#include<fstream>

int main() {
    std::ifstream inFile("file.txt", std::ios::binary);

    int x;
    inFile.read((char*)&x, sizeof(x)); //x = 26

    inFile.close();
}
```

- байтовете се записват в обратна посока - старшият бит е накрая (little endian)

## Сереализация на структури
- ако в структурата няма динамична памет, можем да запишем целия блок от байтове наведнъж
- ако има статичен масив, това не променя записването и прочитането от файл, тъй като данните са вътре в структурата

```cpp
#include <iostream>
#include <fstream>

struct Test {
	bool b;
	int x;
};

int main()
{
	{
		Test t = { true, 45 };
		std::ofstream file("testObj.dat", std::ios::binary);

		if (!file.is_open()) {
			return -1;
		}

		file.write((const char*)&t, sizeof(t));
	}

	{
		Test t;
		std::ifstream file("testObj.dat", std::ios::binary);

		if (!file.is_open()) {
			return -1;
		}

		file.read((char*)&t, sizeof(t));
		std::cout << t.b << " " << t.x << std::endl;
	}
}
```

```cpp
#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning (disable: 4996)

struct Student {
	char name[25];
	int fn;
	int age;
};

int main()
{
	{
		Student st;
		strcpy(st.name, "Ivan");
		st.fn = 1234;
		st.age = 33;

		std::ofstream file("student.dat", std::ios::binary);

		if (!file.is_open()) {
			std::cout << "Error while writing to binary file!" << std::endl;
			return -1;
		}

		//since the data is grouped in the struct, we can save it like this.
		file.write((const char*)&st, sizeof(st));
	}

	{
		Student st;
		std::ifstream file("student.dat", std::ios::binary);

		if (!file.is_open()) {
			std::cout << "Error while reading from binary file!" << std::endl;
			return -1;
		}

		file.read((char*)&st, sizeof(st));
		std::cout << st.name << " " << st.fn << " " << st.age << std::endl;
	}
}
```
- освен че можем да запазим цяла структура наведнъж, можем да запазим и цял масив наведнъж
```c++
#include <iostream>
#include <fstream>
#include <cstring>

struct Student {
	char name[30];
	int age;
	int fn;
};

size_t getFileSize(ifstream& f) {
	size_t currentPos = f.tellg();
	f.seekg(0, std::ios::end);
	size_t size = f.tellg();

	f.seekg(currentPos);
	return size;
}

void readFromFile(Student*& ptr, size_t& studentsCount, ifstream& f) {
	size_t sizeOfFile = getFileSize(f);
	studentsCount = sizeOfFile / sizeof(Student);
	ptr = new Student[studentsCount];
	f.read((char*)ptr, sizeOfFile);
}

int main()
{
	Student* arr;
	size_t count;
	std::ifstream file("students.dat", std::ios::binary);

	if (!file.is_open()) {
		std::cout << "Error while opening the file!" << std::endl;
		return -1;
	}

	readFromFile(arr, count, file);

	for (int i = 0; i < count; i++) {
		std::cout << "Name: " << arr[i].name << ", age: " << arr[i].age << ", fn: " << arr[i].fn << std::endl;
	}

	delete[] arr;
}
```

      
- ако в структурата има динамична памет, не можем да я запишем наведнъж, защото тогава ще се запише адреса, а не данните, които искаме
- записваме всяка член-данна по отделно, а динамичната член-данна записваме, като първо записваме адреса, за да можем при четене да знаем колко да заделим и колко байта да прочетем от файла

```c++
#include <iostream>
#include <fstream>
#pragma warning (disable: 4996)

struct Student {
	char* name;
	int fn;
	int gradesCount;
	double averageGrade;
};

Student createStudent(const char* name, int fn, int gradesCount, double avGrade) {
	Student obj;

	size_t nameLen = strlen(name);

	obj.name = new char[nameLen + 1];
	strcpy(obj.name, name);

	obj.fn = fn;
	obj.gradesCount = gradesCount;
	obj.averageGrade = avGrade;

	return obj;
}

void saveStudentToFile(ofstream& f, const Student& st) {
	size_t nameLen = strlen(st.name);

	f.write((const char*)&nameLen, sizeof(nameLen));  //first we write the size of the name!
	f.write(st.name, nameLen);

	f.write((const char*)&st.fn, sizeof(st.fn));
	f.write((const char*)&st.gradesCount, sizeof(st.gradesCount));
	f.write((const char*)&st.averageGrade, sizeof(st.averageGrade));

}

Student readStudentFromFile(ifstream& f) {
	Student res;

	size_t nameLen;

	f.read((char*)&nameLen, sizeof(nameLen)); //first we read the size of the name!

	res.name = new char[nameLen + 1];
	f.read(res.name, nameLen);
	res.name[nameLen] = '\0';

	f.read((char*)&res.fn, sizeof(res.fn));
	f.read((char*)&res.gradesCount, sizeof(res.gradesCount));
	f.read((char*)&res.averageGrade, sizeof(res.averageGrade));

	return res;
}

void freeStudent(Student& s) {
	delete[] s.name;
	s.averageGrade = s.fn = s.gradesCount = 0;
}

void print(const Student& st) {
	std::cout << st.name << " " << st.fn << " " << st.gradesCount << " " << st.averageGrade << std::endl;
}

int main()
{
	{
		Student s1 = createStudent("Ivan", 1234, 2, 4);
		Student s2 = createStudent("Petur", 5555, 5, 5.5);

		std::ofstream f1("uni.dat", std::ios::binary);

		if (!f1.is_open()) {
			cout << "Error" << endl;
			return -1;
		}

		saveStudentToFile(f1, s1);
		saveStudentToFile(f1, s2);

		freeStudent(s1);
		freeStudent(s2);
	}

	{
		std::ifstream f2("uni.dat", std::ios::binary);

		if (!f2.is_open()) {
			cout << "Error" << endl;
			return -1;
		}
		
		Student s1 = readStudentFromFile(f2);
		Student s2 = readStudentFromFile(f2);

		print(s1);
		print(s2);

		freeStudent(s1);
		freeStudent(s2);
	}
}
```

## Задачи

**Задача 1.** 

Да се реализира фунцкия, която при подаден двоичен файл има масив от числа, записва в 2 различни двоични файла четните и нечетните числа от него.

**Задача 2.** 

Да се реализира програма за изглед и модификация на двоични файлове (hex viewer). При стартиране на програмата трябва да се въведе път до двоичен файл и да зареди съдържанието на файла в паметта. След като файлът се е заредил в паметта, трябва да поддържате следните операции:
 
 - Преглед на файла - отпечатва байтовете на файла (в шестнайсетична бройна система). След това да се отпечатат интерпретацията на байтовете като символи. Ако байтът отговаря на малка/голяма латинска буква, то да се отпечата символа. В противен случай да се отпечатва точка.  
 -  Промяна на байт по индекс
 -  Запазване на промените във файл
