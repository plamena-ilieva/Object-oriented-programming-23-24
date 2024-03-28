#include <iostream>

class Censor {
    bool (*shouldCensor) (char ch);

    void printLetter(char a) const {
        if (shouldCensor(a)) {
            std::cout << '*';
        }
        else {
            std::cout << a;
        }
    }

public:

    Censor() : shouldCensor([](char ch) {return false; }) {}
    Censor(bool (*pred)(char ch)) : shouldCensor(pred) {}

    void print(const char* str) const {
        if (!str) return;
        while(*str) {
            printLetter(*str);
            ++str;
        }
        std::cout << std::endl;
    }
};

constexpr int BUFF_SIZE = 20;
class Text {
    char buff[BUFF_SIZE + 1] = "";
    Censor& censor;

    void setBuffer(const char* val) {
        if (strlen(val) > BUFF_SIZE) {
            return;
        }
        strcpy(buff, val);
    }

public:
    Text(Censor& c, const char* buff) : censor(c) {
        setBuffer(buff);
    }

    void print() const {
        censor.print(buff);
    }
};


int main()
{
    Censor c1([](char ch) {return ch >= '0' && ch <= '9'; });
    Text t1(c1, "hello1234fgh");
    Text t2(c1, "eeeeee23456");

    t1.print();
    t2.print();
}