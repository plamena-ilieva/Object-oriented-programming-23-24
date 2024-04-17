#include <iostream>
#include "StudentsCollection.h"

int main()
{
    Student st1("Ivan", 16);
    Student st2("Mimi", 16);

    StudentsCollection students;
    students.addAtFirstFree(st1);
    students.addAtFirstFree(st2);

    students.removeAtIdx(0);
    std::cout << students.getNumberInClass("Mimi") << std::endl; //2

    Student st3("Pesho", 18);
    students.addAtFirstFree(st3);
    std::cout << students.getNumberInClass("Pesho") << std::endl; //1

    Student st4("Marto", 19);
    students.setAtIdx(st4, 0);
    std::cout << students.getNumberInClass("Marto") << std::endl; //1

}
