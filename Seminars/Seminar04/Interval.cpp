/*
Задача 1: Реализирайте клас/структура интервал, който представлява интервал [a,b] (задължително а <= b) от реалната права. Нашият интервал ще бъде дискретен - началото и краят му ще бъдат цели числа и ще разглеждаме само точки, които са цели числа. Релизирайте следният интерфейс:

Подразбиращ се контруктор, който създава интервала [0,0].
Конструктор, който приема двата параметъра. Ако a<=b, то създава интервала [a,b]. В противен случай, създава [0,0].
Член-функция, която връща дължината на интервала.
Член-функция, която приема число и проверява дали е част от интервала.
Член-функция, която връща броя на простите числа в интервала.
Член-функция, която връща броя на числата в интервала, които са палиндорми.
Член-функция, която връща броя на числата, които нямат повтарящи цифри.
Член-функция, която връща дали началото и края на интервала са степени на 2-ката. ([2,16] - истина)
Член-функция, която приема интервал и връща сечението на текущия интервал с подадения. (Сечението на [1, 5] [3, 7] e [3, 5]).
Член-функция, която приема интервал и връща дали подадения (като параметър) интервал е подинтервал на текущия(обектът, от който се извиква функцията).*/

#include <iostream>

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }

    double square = sqrt(n);
    for (size_t i = 2; i <= square; i++)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}
int reverse(int n) {
    int res = 0;

    while (n != 0)
    {
        int lastDigit = n % 10;
        (res *= 10) += lastDigit;
        n /= 10;
    }

    return res;
}
bool isPalindrome(int n) {
    return n == reverse(n);
}
bool isProwerOTwo(int n) {
    if (n < 0) {
        return false;
    }

    return (n & n - 1) == 0;
}


class Interval {
    int a = INT_MIN;
    int b = INT_MAX;

    unsigned getCount(bool (*predicate)(int)) const {
        unsigned cnt = 0;

        for (int i = a; i <= b; i++)
        {
            if (predicate(i)) {
                cnt++;
            }
        }

        return cnt;
    }

public:
    Interval() : Interval(0, 0) {}

    Interval(int valA, int valB) {
        if (valA > valB) {
            valA = valB = 0;
        }

        setA(valA);
        setB(valB);
    }

    void setA(int valA) {
        if (valA < b) {
            a = valA;
        }
    }

    void setB(int valB) {
        if (valB > a) {
            b = valB;
        }
    }

    int getA() const {
        return a;
    }

    int getB() const {
        return b;
    }

    int getLenght() const {
        return b - a + 1;
    }

    bool isInInterval(int x) const {
        return a <= x && x <= b;
    }
    
    unsigned getCountOfPrimes() const {
        return getCount(isPrime);
    }

    unsigned getCountOfPalindromes() const {
        return getCount(isPalindrome);
    }

    unsigned getCountOfPowerOfTwo() const {
        return getCount(isProwerOTwo);
    }

};

int main() {
    Interval i(11, 20);
    std::cout << i.getCountOfPalindromes() << std::endl;
    std::cout << i.getCountOfPrimes() << std::endl;
    std::cout << i.getCountOfPowerOfTwo() << std::endl;
}