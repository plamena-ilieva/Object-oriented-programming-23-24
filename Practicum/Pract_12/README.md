# OOП - Практикум 15.05.2024 - Седмица 12

## Blitz Test №6

**При всички задачи работим в Little-Endian x86 операционна система (4-байтови указатели)** 

**Задача 1.** Какво ще се отпечата?
```c++
class A
{
    public:
    virtual void f()
    {
        std::cout << "A";
    }
};

class B : public A
{
    public:
    void f() override
    {
        std::cout << "B";
    }
};

class C : public B
{
    public:
    void f()
    {
        std::cout << "C";
    }
};

int main()
{
    A* ptr = new C();
    ptr->f();
}
```

**Задача 2.** Какво ще се отпечата на конзолата?
```c++
class A
{
    int number;
public:
    virtual void f()
    {
        std::cout<< "A";
    }
};

class B : public A
{
    int anotherNumber;
public:
    void f() override
    {
        std::cout << "B";
    }
};


int main()
{
    std::cout << sizeof(A);
    std::cout << sizeof(B);
}
```

**Задача 3.** Малко теория:
1) Как виртуалните функции "знаят" в кой клас да търсят своите реализации? (Накратко обяснете механизма - може да датете и пример/картинка)
2) Kакъв недостатък откъм производителност има употребата на виртуални функции?
3) Мога ли да създам статична (static) виртуална (virtual) член-функция?
4) При полиморфни йерархии защо се налага деструктура да е виртуален? (Ако ви е по-лесно, дайте пример и обяснете по него)

**Задача 4.** Какво ще се случи след изпълнение на кода?
```c++
class A
{
public:
    virtual void f()
    {
        std::cout << "From A";
    }
};

class B : public A
{
public:
    void f() override final
    {
        std::cout << "Virtual From B";
    }
};

class C : public B
{
public:
    void f()
    {
        std::cout << "Shadow From C";
    }
};

int main()
{
    A* ptr = new C();
    ptr->f();
}
```

**Задача 5.** Има ли проблем с кода? Ако да - обяснете какъв. Ако не - какво ще изведе?
```c++
class Base
{
    int number;
public:
    Base(int n): number(n)
    {

    }

    virtual void printData()
    {
        std::cout << "Base class" << std::endl;
        std::cout << "Number: " << number << std::endl;
    }
};

class Der : public Base
{
    int* myArr = nullptr;
    size_t mySize = 0;
public:
    Det(const int* arr, size_t size): Base(5)
    {
        // validation, nullptr checks and more...

        mySize = size;
        myArr = new int[mySize];

        for(size_t i = 0; i < size; i++)
        {
            myArr[i] = arr[i];
        }        
    }

    void printData() override
    {
        Base::printData();
        std::cout << "Der class" << std::endl;
        for(size_t i = 0; i < size; i++)
        {
            std::cout << i << ": "<< myArr[i] << std::endl;
        }  
    }

    ~Der()
    {
        delete[] myArr;
        myArr = nullptr;
        mySize = 0;
    }
};

int main()
{
    const int arr[] = {1, 2, 3};
    Base* ptr = new Der(arr, 3);

    ptr->f();

    delete ptr;
}
```

## Задачи за практикум
**Задача 1.** Време е да финализираме нашият `StringVector` от последните няколко практикума. В проектите ще ви се наложи да създавате вектори от различни типове (не само `String`). За целта ще преобразуваме вече написаният `StringVector` в клас `Vector`, който вместо със `String` ще работи с шаблони. Не забравяйте да преместите всички дефиниции на член-функции от *.cpp* файла при декларациите в header-а, както и да промените хедъра от *.h* на *.hpp*.

*Указания: просто навсякъде заменяте `String` с вашият template тип, най-често отбелязван с `T` (Type) или `E` (Element).*

**Задача 2.** Windows Forms е UI framework за лесно създаване на приложения за Windows OS. Той
представя лесен начин за създаване на приложения графично и се поддържа от езикци като C#. Приложенията представляват множество от форми (Forms), в които има контроли (Controls).
Да се създаде клас, който представя **Форма**. Формата има размер (широчина и дължина) и име. Всяка форма поддържа колекция от контроли.

Всеки **контрол** има размер и локация във формата. Също така, всеки контрол има функция `setDataDialog();`, която позволява на потребителя да промени контрола по подходящ начин. Всеки контрол може да променя размерите си. Имаме следните контроли:

1. *TextBox* - Контрол, в който се подава текст. `setDataDialog()` променя текста му.
![check](https://i.stack.imgur.com/AhOpr.jpg)
1. *CheckBox* - Контрол, който има текст и състояние (включен или изключен).
    `setDataDialog()` променя дали е включен или изключен по подразбиране. За промяна на текста може да добавите допълнителна функция.
    ![radio](https://images.theengineeringprojects.com/image/main/2017/10/C-CheckBox-9.png)
    
2. *RadioButton* - Контрол, който има няколко опции, но само една е избрана.
    `setDataDialog()` променя избраната опция. Може да добавите допълнителна логика за промяната на опциите. Броят им, веднъж зададен, не се променя.
    ![radio](https://i.stack.imgur.com/EyNQT.png)

Реализирайте хетерогенен контейнер, който съдържа различните контроли, които вашата форма притежава. 
Трябва да имате следните методи:
- метод за добавяне на контрола към контейнера
- метод за променяне на размера на формата, както и на всеки от контролите (може да достъпвате контролите по индекс)
- функция за промяна на локацията на контролите, като те не трябва да излизат извън формата
- метод `change(size_t index);` който променя контрола на подадения индекс. Промяната става чрез извикване на `setDataDialog` функцията на съответния контрол.