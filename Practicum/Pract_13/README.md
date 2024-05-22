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


**Задача 2:**
Реализирайте темплейтна функция, която сортира подаден масив. Ако масивът е от символи, да се сортира, изпозвайки *counting sort*, иначе - *insertion sort*.

**Задача 3:**
Преди много години единствените живи организми на земята били три вида чудовища:
- ```Минотавър```
- ```Кентавър```
- ```Сфинкс```

За съжаление в процеса на еволюцията част от тях изчезват :(, след като се избиват помежду си, като:
- Минотавърът винаги побеждава сфинкса
- Кентавърът винаги побеждава минотавъра
- Сфинксът винаги побеждава кентавъра

Генерирайте на случаен принцип масив с 15 различни чудовища (не забивайте генерирането при нормалния flow на задачата), след което изберете чудовището на позиция i, и изведете в конзолата колко от останалите чудовища ще победи.
Чудовища от един и същ тип никога не се бият едни срещу други, а излизат на по бира.
