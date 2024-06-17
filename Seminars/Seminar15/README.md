# Solid Principles

SOLID е акроним за пет принципа на проектиране, предназначени да направят софтуерния дизайн по-разбираем, гъвкав и поддържащ. <br />
Въпреки че се прилагат за всеки обектно-ориентиран дизайн, принципите SOLID могат също да формират основна философия за гъвкаво развитие. <br />

## Single Responsibility principle
```
A class should have only one reason to change
```

- всеки модул носи отговорност за една и само една цел, има 1 предназначение
- класът трябва да има само една "причина" за промяна (под "причина" може да имаме предвид промяна в спецификацията на даденo изискване)
- този принцип позволява да пишем софтуер с висока кохезия и стабилност, тъй като той няма да бъде толкова повлиян с развиването на системата

```c++
#include <iostream>
#include <string>

using namespace std;

class OrderProcessor {
private:
    string order;

public:
    OrderProcessor(const string& order) : order(order) {}

    // Method to process the order
    void process_order() {
        cout << "Processing order: " << order << endl;
    }
};

class DatabaseManager {
public:
    void save_to_db(const string& order) {
        cout << "Saving " << order << " to database" << endl;
    }
};

class ErrorLogger {
public:
    void log_error(const string& error_message) {
        cout << "Logging error: " << error_message << endl;
    }
};

int main() {
    string order = "Order #123";

    OrderProcessor order_processor(order);
    order_processor.process_order();

    DatabaseManager db_manager;
    db_manager.save_to_db(order);

    ErrorLogger error_logger;
    error_logger.log_error("No errors");

    return 0;
}

```

## Open-Closed Principle
```
Software entities should be open for extension, but closed for modification
```
- софтуерните модули са отворени за разширение, но затворени за модификаци
- това позволява добавянето на нова функционалност без промяна на съществуващия изходен код, за да може да се налага промяна навсякъде, където вече е използван

- най-добрият начин да постигнете това със C++ е полиморфизмът
- с използването на абстрактни класове можем да разширим клас и да специализираме неговото поведение, без да променяме спецификацията на интерфейса
- този принцип позволява софтуер за многократна употреба и поддръжка

```c++
#include <iostream>
#include <memory>

using namespace std;

class Payment {
public:
    virtual void process(double amount) = 0;
    virtual ~Payment() {}
};

class CreditCardPayment : public Payment {
public:
    void process(double amount) override {
        cout << "Processing credit card payment of " << amount << endl;
    }
};

class PayPalPayment : public Payment {
public:
    void process(double amount) override {
        cout << "Processing PayPal payment of " << amount << endl;
    }
};

class PaymentProcessor {
public:
    void process_payment(Payment* payment, double amount) {
        payment->process(amount);
    }
};
```

## Liskov Substitution Principle
```
Objects of a superclass should be replaceable with objects of subclasses without affecting the correctness of the program.
```

- подкласовете не само задоволяват синтактичните очаквания, но и поведенческите на своите родители - достъп до функции, параметри на връщане, exception safety                             
- трябва да можем да използваме всяко от наследниците, които могат да ни бъдат подадени, без да се интересувам кое конкретно дете се използва                                  

```c++
#include <iostream>
#include <vector>

using namespace std;

// Bird base class
class Bird {
public:
    virtual string move() {
        return "Moving";
    }
};

// Sparrow class
class Sparrow : public Bird {
public:
    string move() override {
        return "Flying";
    }
};

// Penguin class
class Penguin : public Bird {
public:
    string move() override {
        return "Swimming";
    }
};
```

```c++
/*
The problem begins when different sensors, that is, the different children that implement the interface, return the orientation in different ranges.
For example, we have a Gyroscope that returns an orientation that is always positive, between 0 and 360 degrees,
while the Accelerometer provides an output that can be negative. Something between -180 and positive 180.
*/

class InertialMeasurementUnit {
public:
   virtual ~InertialMeasurementUnit() = default;
   virtual int getOrientation()       = 0;
};
class Gyroscope : public InertialMeasurementUnit {
public:
   /**
    * @return orientation in degrees [0, 360)
    */
   int getOrientation() override;
};
class Accelerometer : public InertialMeasurementUnit {
public:
   /**
    * @return orientation in degrees [-180, 180)
    */
   int getOrientation() override;
};
```

```c++
class InertialMeasurementUnit {
public:
   virtual ~InertialMeasurementUnit() = default;
   
   /**
    * Sets the orientation
    * @throw std::out_of_range exception if orientation is invalid
   */
   virtual void setOrientation(double) = 0;
   
    /**
    * Provides the valid range
    * @return <minimum orientation, maximum orientation>
    */
   virtual pair<double, double> getFrequencyRange() const = 0;
};

class Gyroscope : public InertialMeasurementUnit {
public:
   /**
    * @return orientation in degrees [0, 360)
    */
   int getOrientation() override;
};
class Accelerometer : public InertialMeasurementUnit {
public:
   /**
    * @return orientation in degrees [-180, 180)
    */
   int getOrientation() override;
};
```

## Interface Segregation Principle
```
No client should be forced to depend on methods it does not use
```
- класове с точно и ясно предназначение - специфични класове/методи
- трябва да избягваме класове/методи, които да правят "всичко", ако няма да се възползваме от всички функционалности
- по-добре е да имате много интерфейси с едно предназначение, отколкото един (или няколко) многоцелеви
- това позволява на нашия софтуер да бъде по-преизползваем и персонализиран, тъй като не е нужно да разчитаме или да прилагаме функционалност, която не използваме

```c++
struct IMachine {
    virtual void print(Document &doc) = 0;
    virtual void fax(Document &doc) = 0;
    virtual void scan(Document &doc) = 0;
};

struct MultiFunctionPrinter : IMachine {      // OK
    void print(Document &doc) override { //code 
    }
    void fax(Document &doc) override { //code 
    }
    void scan(Document &doc) override { //code 
    }
};

struct Scanner : IMachine {                   // Not OK
    void print(Document &doc) override { /* Blank */ }
    void fax(Document &doc) override { /* Blank */ }
    void scan(Document &doc) override {  
        // Do scanning ...
    }
};
```

```c++
/* -------------------------------- Interfaces ----------------------------- */
struct IPrinter {
    virtual void print(Document &doc) = 0;
};
struct IScanner {
    virtual void scan(Document &doc) = 0;
};
/* ------------------------------------------------------------------------ */
struct Printer : IPrinter {
    void print(Document &doc) override;
};
struct Scanner : IScanner {
    void scan(Document &doc) override;
};

struct IMachine : IPrinter, IScanner { };

struct Machine : IMachine {
	 IPrinter&   m_printer;
    IScanner&   m_scanner;
    
    Machine(IPrinter &p, IScanner &s) : printer{p}, scanner{s} { }
    
    void print(Document &doc) override {
		printer.print(doc);
    }
    
    void scan(Document &doc) override {
		scanner.scan(doc);
    }
};
```

## Dependency Inversion Principle
```
High-level modules should not depend on low-level modules. Both should depend on abstractions (e.g. interfaces).
Abstractions should not depend on details. Details (concrete implementations) should depend on abstractions.
```

- нашите класове трябва да зависят от интерфейси или абстрактни класове, вместо от конкретни класове и функции
- всеки конкретен клас е добре да наследява някакъв интерфейс, за да се добавят лесно нови компоненти, които не зависят от имплементсцията на класа, а само от интерфейса

```c++
#include <iostream>
#include <memory>

using namespace std;

class EmailService {
public:
    virtual void send(const string& message) = 0;
    virtual ~EmailService() {} 
};

class SMTPService : public EmailService {
public:
    void send(const string& message) override {
        cout << "Sending email via SMTP: " << message << endl;
    }
};

class MockEmailService : public EmailService {
public:
    void send(const string& message) override {
        cout << "Mock sending email: " << message << endl;
    }
};

class EmailSender {
private:
    unique_ptr<EmailService> email_service;

public:
    EmailSender(unique_ptr<EmailService> service) : email_service(move(service)) {}

    void send_email(const string& message) {
        email_service->send(message);
    }
};

```
