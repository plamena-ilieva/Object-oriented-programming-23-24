## Видове памет

#### Глобална (Статична)
- статични/глобални променливи

#### Стекова (stack)
* локални променливи (в телата на функциите)
* заделя се в момента на дефиниция на променливата и се освобождава в момента на изход от scope-a, в която е дефинирана
* последно заделената памет се освобождава първа (First in Last out);

	```cpp
	int f(int a) { // заделяне на a
		int b; // заделяне на b
		
		if (a > 0) {
			int c; // заделяне на c
		} // освобождаване на c
		
	} // освобождаване на b; освобождаване на a
	```


* Количеството заделена памет е определена по време на компилация
	```cpp
	int main() {
		constexpr int size1 = 50;
		int  arr1[size1]; // успешно заделяне
		
		int size2;
		std::cin >> size2;
		int  arr2[size2]; // грешка
	}
	```

#### Динамична (heap)

* заделя се и се освобождава по всяко време на изпълнение на програмата
	```cpp
	int main() {
		int size;
		std::cin >> size;
		
		int* arr = new int[size]; // заделяне
		//...

		delete[] arr; // освобождаване
	}
	```

* Областта за динамична памет е набор от свободни блокове памет;

* програмата може да заяви блок с произволна големина;

* имаме контрол над управлението на паметта;

#### Program Code
* памет, в която се пази компилираният код
* може да се достъпва с function pointer-и

## Референции и указатели, функции
- ако искаме да копираме променливата, а не да я променяме:
```cpp
void f(int a);
```
- ако искаме да променяме оригиналната променлива, която сме подали:
```cpp
void f(int& a); // предпочитаме, когато използваме единичен обект, защото 
				// ни гарантира, че обектът съществува
void f(int* a); // предпочитаме, когато работим с масиви (трябва да правим 
				// проверка за nullptr)
				// ако не променяме масива, използваме const int*
```
- ако искаме не просто да променим не просто паметта, към която сочи указателя, а да го пренасочим:
```cpp
void f(int*& a);
```
*Пример:*
```cpp
void f(int*& ptr) { 
	ptr = new int[5];
}

int main() {
	int* ptr = nullptr;
	f(ptr); // ако не е подаден по референция, ще се направи копие на 
			// указателя, ще се задели нова памет, към която само копието 
			// ще сочи и в края на функцията f, копието ще се изтрие от 
			// стека, но не и паметта в heap-a, към която сочи
	delete[] ptr;
}
```

- функцията ни може да връща копие (интересуваме се само от стойността)
```cpp
int f(...);
```
- може да връща променлива 
- трябва да си подсигурим, че променливата, което връщаме, ще живее след края на функцията, т.е. няма да е изтрита (да е подадана по референция във функцията или да е глобална променлива)
```cpp
int& f(...);
```
- може да връща указател
- отново трябва да подсигурим, че указателя ще съществува (подаден отвън или заделяме памет във функцията)
```cpp
int* f(...);
```

## Структури
- съставен тип данни
- използват се за групиране на елементи
- могат да бъдат от различен тип и с различна дължина, за разлика от масивите
```cpp
struct Product {
  int weight;
  double pricePerWeight;
};
```
- aко няма да променяме обекта, го подаваме по **константна референция**
- пестим памет и тежки копирания
	```c++
	double calculcatePrice(const Product& product) {
		return product.weight * product.pricePerWeight;
	}
	```

- ако искаме да променяме обекта, подаден като аргумент, го подаваме само по **референция**
	
	```c++
	void readProduct(Product& product) {
		std::cin >> product.weight >> product.pricePerWeight;
	}
	```

- ако искаме да извършим изчисление, за което ни е необходимо да променим обекта, но не искаме да променяме оригиналния обект, го подаваме по **копие**
- можем да създаваме **динамични истанции**
	```cpp
	int  main() {
		Product* ptr = new Product();
		
		(*ptr).weight = 10;
		(*ptr).pricePerWeight = 1.60;

		ptr->pricePerWeight = 2.00;
		delete ptr;
	}
	```

- можем да създаваме **масиви** от истанции
    ```cpp
    int  main() {
        Product arr1[30]; // stack
        Product* arr2 = new  Product[20]; // heap

        arr2[0].weight = 5;
        arr2[0].pricePerWeight = 1.00;

        delete[] arr2;
    }
    ```
## **Представяне в паметта и подравняване.**

* в паметта променливите са разположени в същия ред, в който са декларирани в структурата
* всеки байт в паметта се достъпва индивидуално
* процесорът може да чете по няколко байта наведнъж (memory read cycle)
* колко памет може да прочете за един memory read cycle-a зависи от архектурата му (x32 - 4 bytes, x64 - 8 bytes);
* по тази причина е необходимо подравняване (padding)

### Подравняване

* размерът на структурата трябва да се дели на големината на **най-голямата примитивна член-данна**
* структурата се подравнява по големината на най-голямата си примитивна член-данна
* всяка член-данна се намира на адрес (започвакйи от 0), който се дели на големината на член-данната

-> За да бъде минимална паметта, която ползва една структура, подреждаме член-данните по големина

*Примери*
<img  style="object-fit:contain;"  align="right"  width="250"  height="220"  src="img\Screenshot 2024-02-23 152636.png">

```cpp
struct A {
	char a;	
	short b; 
	int c; 
}; 
// sizeof(A) = 8
// alignof(A) = 4
```

<img style="object-fit:contain;"  align="right"  width="200"  height="180"  src="img\Screenshot 2024-02-23 154620.png">

```cpp
struct B {
	char a;
	int c;
	short b;
};
// sizeof(B) = 12
// alignof(B) = 4
```

- масивите се представят като последователност от n елемента
<img style="object-fit:contain;"  align="right"  width="200"  height="170"  src="img\Screenshot 2024-02-23 155244.png">

```cpp
struct C {
	short b;
	char a[5];
	int c;
};
// sizeof(C) = 12
// alignof(C) = 4
```
- празните структури имат размер 1, за да имат място в паметта
<img  style="object-fit:contain;"  align="right"  width="150"  height="150"  src="img\Screenshot 2024-02-23 160257.png">

```cpp
struct D {

};
// sizeof(D) = 1
// alignof(D) = 1
```
<img  style="object-fit:contain;"  align="right"  width="300"  height="150"  src="img\Screenshot 2024-02-23 161912.png">

```cpp
struct E {
	double a;
	int b;
};
// sizeof(E) = 16
// alignof(E) = 8
```
- структурите запазват целостта си (подравняването обаче е по най-голямата примитивна член-данна)

<img  style="object-fit:contain;"  align="right"  width="280"  height="170"  src="img\Screenshot 2024-02-23 162259.png">

```cpp
struct F {
	char a;
	E e;
	char c;
};
// sizeof(F) = 32
// alignof(F) = 8
```
<img  style="object-fit:contain;"  align="right"  width="300"  height="200"  src="img\Screenshot 2024-02-23 162606.png">

```cpp
struct G {
	F f[2];
	char ch[3];
};
// sizeof(G) = 72
// alignof(G) = 8



```

- ако като последна член-данна сложим масив, без да определим размера му, той заема padding-а до края на структурата

<img  style="object-fit:contain;"  align="right"  width="300"  height="200"  src="img\Screenshot 2024-02-23 163157.png">

```cpp
struct H
{
	G g;
	char c1[4];
	char c2[];
};
// sizeof(H) = 80
// alignof(H) = 8
```

## Енумерации (Enums)
- тип, чиито стойности са ограничени в определен диапазон
- има основен тип, обикновено интегрален тип (по default e int, може да изберем друг)
- енумерацията има същия размер като основния тип

```cpp
enum X {
    val = 1
}
// sizeof(X) = 4
```

```cpp
enum X : char{
    val = 1
}
// sizeof(X) = 1
```

### Cтойностите по подразбиране 
- започват от 0 
- всяка следваща е с 1 по-голяма от предишната

```cpp
enum Example
{
	val1, // 0
	val2, // 1
	val3, // 2
	val4 // 3
};
```

```cpp
enum Example
{
	val1 = 9, // 9
	val2, // 10
	val3, // 11
	val4 // 12
};
```

```cpp
enum Example
{
	val1 = 9, // 9
	val2, // 10
	val3 = 9, // 9 -> няма проблем стоностите да се повтарят
	val4 // 10
};
```

### Unscoped enumarations vs Scoped enumarations
- при обикновените enum-и стойностите се преобразуват експлицитно към int, тоест могат да се сравняват с други типове

    ```cpp

    enum Country { USA, UK, Canada, Australia };
    enum Continent { America, Asia, Europe, Africa }; 

    int main() {
        Country country = Country::USA;
        Continent continent = Continent::America;

        if (continent == country) {} // позволено, но не искаме да можем да ги сравняваме

    }
    ```

- при enum класовете стойностите не се преобразуват експлицитно към int, тоест е позволено само сравняване на стойности в рамките на класа

    ```cpp
    enum Country { USA, UK, Canada, Australia };
    enum Continent { America, Asia, Europe, Africa }; 
    //... 

    if (continent == Continent::Europe) {}
    ```


- ако искаме да принтираме enum, трябва да определим как бихме принтирали всяка стойност и използваме switch-case конструкция (защото е интегрален тип)

```cpp
switch (continent) {
        case Continent::America:
            cout << "America" << endl;
            break;
        case Continent::Asia:
            cout << "Asia" << endl;
            break;
        case Continent::Europe:
            cout << "Europe" << endl;
            break;
        case Continent::Africa:
            cout << "Africa" << endl;
            break;
    }
```

## Пространства от имена (namespaces)
- предотвратяват конфликти с имена
- в един namespace могат да се използват цели други такива или само определени функции (всички функции с това име)

    ```cpp
    namespace A {
        void f() {}
        void f(int a) {}
        void g() {}
    }

    int main()
    {
        using A::f;
        f(); // работи
        f(3); // работи
        g(); // грешка - тази функция не е включена 
    }
    ```
- при използване на namespace се запазва scope-а, в който са дефинирани
- ако има променливи с едно и също име в различни namespaces и се използват едновременно повече от един от тях, с най-висок приоритет са декларациите в този namespace, който е деклариран в най-близкия външен scope

    ```c++
    namespace A
    {
        int i;
    }
    
    namespace B
    {
        int i;
        int j;
    
        namespace C
        {
            namespace D
            {
                using namespace A; // all names from A injected into global namespace
    
                int j;
                int k;
                int a = i;         // i is B::i, because A::i is hidden by B::i
            }
    
            using namespace D; // names from D are injected into C
                            // names from A are injected into global namespace
    
            int k = 89; // OK to declare name identical to one introduced by a using
            int l = k;  // ambiguous: C::k or D::k
            int m = i;  // ok: B::i hides A::i
            int n = j;  // ok: D::j hides B::j
        }
    }

    namespace Q
    {
        namespace V   	// V is a member of Q, and is fully defined within Q
        { 			 	// namespace Q::V // C++17 alternative to the lines above
            class C		// C is a member of V and is fully defined within V
            { 
                void m(); // C::m is only declared
            };
            void f(); // f is a member of V, but is only declared here
        }
    
        void V::C::m() // definition of V::C::m outside of the namespace (and the class body)
        {}             // enclosing namespaces are the global namespace, Q, and Q::V
    }
    ```
## Обединения (Unions)
- последователност от полета, които споделят една памет
    ```c++
    union Example
    {
        int a;
        char b;
    } var;

    int main()
    {
        var.a = 65;
        std::cout << var.a << " " << var.b; // 65 A
    }
    ```
- размерът на един union е колкото размерa на най-голямата променлива
- предназначени са за използване на точно едно поле (иначе - undefined behaviour)
- използват се, когато искаме повече от една интерпретация на определени данни или когато във всеки момент искаме да използваме точно една от променливите (трябва ни и флаг, който)


    ```cpp
    #include <iostream>

    enum DataType {
        CHAR,
        INT,
        FLOAT
    };

    struct data {
        DataType type;
        union {
            char char_value;
            int int_value;
            float float_value;
        };
    };

    int main() {
        data myData1;
        myData1.type = INT;
        myData1.int_value = 42;

        // проверяваме типа и използваме на съответната стойност
        switch (myData1.type) {
            case CHAR:
                std::cout << "Char Value: " << myData1.char_value << std::endl;
                break;
            case INT:
                std::cout << "Int Value: " << myData1.int_value << std::endl;
                break;
            case FLOAT:
                std::cout << "Float Value: " << myData1.float_value << std::endl;
                break;
        }

        return 0;
    }
    ```



**Задача 1:** Резлизирайте структура Rational, която е за работа с рационални числа. <br />
Имплементирайте функции за събиране, изваждане, умножение и деление. <br />
Имеплементирайте функция, която приема истанция(обект) от новия тип и връща дали е валидно рационално число, както и функция, която връща дали е цяло число. <br />


**Задача 2:** Реализирайте функция, която преобразува стринг към цяло число. Освен резултата, функцията да връща и код за грешка, ако е възникнала такава по време на преобразуването (OK, ако не е възникнала).