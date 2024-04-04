/* 3.2 实验： 研究C++的对象模型 */

/*
1、定义一个类，其中有静态数据成员、各种类型非静态数据成员（含字符指针），
    甚至包括引用（可选），静态和非静态成员函数（含分配空间的构造函数、析构函数）。
2、定义全局对象、main函数中局部对象、另一个被main调用的外部函数func中定义局部对象
    （可以是形参）、main函数中动态创建对象，每种对象至少2个。观察、分析各种对象地址。
3、输出对象中各个静态与非静态数据成员的值、地址、对象的存储空间大小等信息。
    由此理解对象的本质、静态数据成员是本类对象共享一份拷贝等问题。此外，应观察对齐现象。
4、（可选）输出对象的每个字节，以揭示引用的实现方法。
5、对于上述各种对象，输出静态、非静态成员函数地址，以及main、func等外部函数的地址，并分析。
    要求采用合理方法，避免编译器提出警告。

注意：本题作为实验报告内容，要求有代码、注释、结果截图及分析。
以班为单位统一收，电子版，发我的邮箱libaohong32@163.com
*/

#include <iostream>
#include <cstring>

class MyClass {
public:
    static int staticData;
    int nonStaticData;
    char* charPointer;
    int& refData;

    MyClass() : refData(nonStaticData) {
        charPointer = new char[10];
        strcpy(charPointer, "Example");
    }

    MyClass(int value) : refData(nonStaticData) {
        nonStaticData = value;
        charPointer = new char[10];
        strcpy(charPointer, "Example");
    }

    ~MyClass() {
        delete[] charPointer;
    }

    static void staticFunction() {
        std::cout << "Static function called" << std::endl;
    }

    void nonStaticFunction() {
        std::cout << "Non-static function called" << std::endl;
    }
};

int MyClass::staticData = 0;

void externalFunction(MyClass obj) {
    std::cout << "External function called" << std::endl;
}
    MyClass globalObj;
int main() {
    // Global object

    std::cout << "Global object address: " << &globalObj << std::endl;

    // Local object in main
    MyClass localObj(10);
    std::cout << "Local object in main address: " << &localObj << std::endl;

    // Call external function with local object as argument
    externalFunction(localObj);

    // Dynamic object creation
    MyClass* dynamicObj = new MyClass;
    std::cout << "Dynamic object address: " << dynamicObj << std::endl;

    // Output member values, addresses, and sizes
    std::cout << "Static data member value: " << MyClass::staticData << std::endl;
    std::cout << "Non-static data member value: " << localObj.nonStaticData << std::endl;
    std::cout << "Character pointer value: " << localObj.charPointer << std::endl;
    std::cout << "Reference data member value: " << localObj.refData << std::endl;

    std::cout << "Size of MyClass object: " << sizeof(MyClass) << std::endl;

    // Output addresses of member functions
    std::cout << "Address of static function: " << &MyClass::staticFunction << std::endl;
    std::cout << "Address of non-static function: " << &(localObj.nonStaticFunction) << std::endl;
    std::cout << "Address of main function: " << (void*)main << std::endl;
    std::cout << "Address of external function: " << (void*)externalFunction << std::endl;

    delete dynamicObj;
    return 0;
}