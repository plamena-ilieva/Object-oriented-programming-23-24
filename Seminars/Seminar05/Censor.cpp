#include <iostream>

#pragma warning (disable : 4996)
bool isLower(char a) {
    return a >= 'a' && a <= 'z';
}

class Censor {
    bool forbiddenLetters[26]{ false };

    void printLetter(char a) const {
        if (isLower(a) && forbiddenLetters[a - 'a']) {
            std::cout << '*';
        }
        else {
            std::cout << a;
        }
    }

public:
    void addLetter(char a) {
        if (!isLower(a)) {
            return;
        }
        forbiddenLetters[a - 'a'] = true;
    }

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
    Censor c1;
    c1.addLetter('e');
    Text t1(c1, "hello");
    Text t2(c1, "eeeeee");

    t1.print();
    t2.print();
}
