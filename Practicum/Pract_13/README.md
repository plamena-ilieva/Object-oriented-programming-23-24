# OOП - Практикум 22.05.2024 - Седмица 13

## Blitz Test №7

**Задача 1.** Обяснете кратко как работи Visitor pattern-а.

**Задача 2.** Кои са необходимите функции, които типа `T` трябва да притежава, за да бъде приложима шаблонната функция `areEqual`?
```c++
template <typename T>
bool areEqual(const T& lhs, const T& rhs)
{
	if (lhs.size() != rhs.size())
	{
		return false;
	}

	for (size_t i = 0; i < lhs.size(); i++)
	{
		if (lhs[i] != rhs[i])
		{
			return false;
		}
	}

	return true;
}
```

**Задача 3.** Напишете **шаблонна** функция `linearSearch`, която извършва линейно търсене измежду елементите на подаден `Vector` от обекти. Функцията приема вектор от обекти от шаблонен тип, както и търсения обект. Резултатът от функцията е индекса на намерения елемент, а ако него го няма - връща `-1`.

**Задача 4.** Защо хетерогенните контейнери са от типа `Base**`? (Може да се обясни и схематично)

**Задача 5.** Какви грешки има в следния хетерогенен контейнер?
```c++
class Base
{
    // Correct Implementation here
};

class Container
{
private:
	Base** data = nullptr
	size_t capacity = 0;
	size_t count = 0;
          
    void copyFrom(const Container& other)
    {
        data = new Base*[other.capacity];
        for(int i = 0; i < other.count; i++)
            *(data[i]) = *(other.data[i]);
        count = other.count;
        capacity = other.capacity;
    }

    void moveFrom(Container&& other)
    {
        data = other.data;
        count = other.count;
        capacity = other.capacity;

        other.data = nullptr;
        other.data = other.capacity = 0;
    }

    void free()
    {
        delete[] data;
        capacity = count = 0;
    }
    
public:
	Container() = default;
	
    Container(const Container& other) 
    { 
        copyFrom(other);
    }

	Container(Container&& other) noexcept
    { 
        moveFrom(other);
    }

	Container& operator=(const Container& other)
    {
        if(this != &other)
        {
            free();
            copyFrom(other);
        }

        return *this;
    }

	Container& operator=(Container&&) noexcept
    {
        if(this != &other)
        {
            free();
            moveFrom(other);
        }

        return *this;
    }
    
    ~Container()
    {
        free();
    }
};
```

## Задачи за практикум

**Задача 1.** Реализирайте темплейтна функция, която сортира подаден масив. Ако масивът е от символи, да се сортира, изпозвайки *counting sort*, иначе - *insertion sort*.

**Задача 2.**
Да се реализира абстрактен клас **Employee**. Той представя работник във фирма и се описва с име с произволна дължина, възраст и заплата, която взема във фирмата. 

Да се реализира клас **Worker**, представляващ човек, който работи във фирмата. Той съдържа във себе си колко общо месеца е работил за компанията. Да се реализира клас, представляващ **Trainee** (стажант). Той пази цяло число, представляващо колко дни остават до края на стажа му. 

Да се създаде клас представляващ **Платен стажант**. Това е стажант, който е показал по-специални качества на своето интервю, но все още не е готов да започне на пълен работен ден. Въпреки това работата му се отчита не само като стажантска, а и също като редовна практика, която ще бъде отчетена, когато започне да работи (т.е. притежава функционалностите и на работник, и на стажант). Също така се описва и с рейтинг, показващ колко добре се справя с работата си (реално число от 0 до 100). 

Реализирайте клас, който представя **Компания** като множество от такива работници. Класът трябва да поддържа `addWorker()`, `addTrainee()` и `addPaidTrainee()` методи. Важното тук е, че при добавяне трябва да поддържаме колекцията сортирана по заплата на работниците. Да се напише функция, която показва средната заплата на работниците в тази компания. 

*Бонус*: Да се реализира функцията `bool TwoSum(double val) const;`, която връща дали има двама работника в компанията, чийто сбор на заплатите е равен на val.