#include <iostream>
#include <string>
using namespace std;

/*
Фабричный метод (Factory Method) — порождающий шаблон проектирования, предоставляющий подклассам интерфейс для создания экземпляров некоторого класса.
В момент создания наследники могут определить, какой класс инстанциировать. Иными словами, фабрика делегирует создание объектов наследникам родительского класса.
Это позволяет использовать в коде программы не специфические классы, а манипулировать абстрактными объектами на более высоком уровне.
Фабричный метод  определяет интерфейс для создания объекта, но оставляет подклассам решение о том, какой класс инстанциировать.

Применимость:
-  	классу заранее неизвестно, объекты каких подклассов ему нужно создавать.
-  	класс спроектирован так, чтобы объекты, которые он создаёт, специфицировались подклассами.
-  	класс делегирует свои обязанности одному из нескольких вспомогательных подклассов, и планируется локализовать знание о том, какой класс принимает эти обязанности на себя.

Достоинство:
Фабричные методы избавляют проектировщика от необходимости встраивать в код зависящие от приложения классы. Код имеет дело только с интерфейсом
класса Product, поэтому он может работать с любыми определенными пользователями классами конкретных продуктов.
Недостаток:
Потенциальный недостаток фабричного метода состоит в том, что клиентам, возможно, придется создавать подкласс класса Creator для создания лишь одного объекта ConcreteProduct.
*/

//продукт (PC) определяет интерфейс объектов, создаваемых фабричным методом
class PC abstract
{
protected:
    string box = "";
    string processor = "";
    string mainboard = "";
    string hdd = "";
    string memory = "";
public:
    virtual void SetBox() = 0;
    virtual void SetProcessor() = 0;
    virtual void SetMainBoard() = 0;
    virtual void SetHdd() = 0;
    virtual void SetMemory() = 0;
    void ShowPC()
    {
        cout << "Box: " + box + "\nProcessor: " + processor + "\nMainBoard: " + mainboard + "\nHDD: " + hdd + "\nMemory: " + memory;
        cout << "\n\n";
    }
};

// Конкретный продукт реализует интерфейс Product (в нашем случае, PC)
class OfficePC : public PC
{
public:
    void SetBox()override
    {
        box = "BlackBox";
    }
    void SetProcessor()override
    {
        processor = "AMD Athlon II X4 840 (3.1 GHz)";
    }
    void SetMainBoard()override
    {
        mainboard = "AMD A58 FCH (Bolton D2)";
    }
    void SetHdd()override
    {
        hdd = "Seagate Desktop HDD 7200.12 500GB";
    }
    void SetMemory()override
    {
        memory = "4 Gb DDR3-1600 MHz";
    }
};

// Конкретный продукт реализует интерфейс Product (в нашем случае, PC)

class HomePC : public PC
{
public:
    void SetBox()override
    {
        box = "SilverBox";
    }
    void SetProcessor()override
    {
        processor = "Intel Core i7-4790 (3.6 GHz)";
    }
    void SetMainBoard()override
    {
        mainboard = "Intel B85";
    }
    void SetHdd()override
    {
        hdd = "Western Digital Elements 1.5TB";
    }
    void SetMemory()override
    {
        memory = "16 GB DDR3-1600";
    }
};
class GamingPC : public PC {
public:
    void SetBox() override {
        box = "BanannaBox";
    }
    void SetProcessor() override {
        processor = "Intel Cire i9-14900k (4,9 GHz)";
    }
    void SetMainBoard() override {
        mainboard = "AsusRockStrix 560B";
    }
    void SetHdd() override {
        hdd = "M2 kingston 512";
    }
    void SetMemory() override {
        memory = "HyperX 64 DDR5-5600";
    }
};
// создатель объявляет фабричный метод, возвращающий объект типа Product.
class Creator abstract
{
public:
    virtual PC* FactoryMethod() = 0;
};

// конкретный создатель переопределяет фабричный метод, возвращающий объект ConcreteProduct.
class CreatorHomePC : public Creator
{
public:
    PC* FactoryMethod() override
    {
        PC* pc = new HomePC();
        pc->SetBox();
        pc->SetProcessor();
        pc->SetMainBoard();
        pc->SetMemory();
        pc->SetHdd();
        return pc;
    }
};

// конкретный создатель переопределяет фабричный метод, возвращающий объект ConcreteProduct.
class CreatorOfficePC : public Creator
{
public:
    PC* FactoryMethod()override
    {
        PC* pc = new OfficePC();
        pc->SetBox();
        pc->SetProcessor();
        pc->SetMainBoard();
        pc->SetMemory();
        pc->SetHdd();
        return pc;
    }
};

class CreatorGamingPC : public Creator
{
public:
    PC* FactoryMethod()override
    {
        PC* pc = new GamingPC();
        pc->SetBox();
        pc->SetProcessor();
        pc->SetMainBoard();
        pc->SetMemory();
        pc->SetHdd();
        return pc;
    }
};

// Паттерн позволяет использовать в клиентском коде программы не специфические классы, а манипулировать абстрактными объектами на более высоком уровне.
void Factory(Creator** creators, int size)
{
    // Создатель «полагается» на свои подклассы в определении фабричного метода, который будет возвращать экземпляр подходящего конкретного продукта.
    for (int i = 0; i < size; i++)
    {
        PC* pc = creators[i]->FactoryMethod();
        pc->ShowPC();
    }
}

void main()
{
    Creator* creators[3];
    creators[0] = new CreatorHomePC();
    creators[1] = new CreatorOfficePC();
    creators[2] = new CreatorGamingPC();
    Factory(creators, 3);
}
