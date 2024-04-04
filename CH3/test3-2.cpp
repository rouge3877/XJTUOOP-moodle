/* 3.2 实验： 研究C++的对象模型 */

// 1、定义一个类，其中有静态数据成员、各种类型非静态数据成员（含字符指针），甚至包括引用（可选），
//     静态和非静态成员函数（含分配空间的构造函数、析构函数）。
// 2、定义全局对象、main函数中局部对象、另一个被main调用的外部函数func中定义局部对象（可以是形参）、
//     main函数中动态创建对象，每种对象至少2个。观察、分析各种对象地址。
// 3、输出对象中各个静态与非静态数据成员的值、地址、对象的存储空间大小等信息。由此理解对象的本质、
//     静态数据成员是本类对象共享一份拷贝等问题。此外，应观察对齐现象。
// 4、（可选）输出对象的每个字节，以揭示引用的实现方法。
// 5、对于上述各种对象，输出静态、非静态成员函数地址，以及main、func等外部函数的地址，并分析。
//     要求采用合理方法，避免编译器提出警告。

#include <iostream>

class MyClass {
public:
    // Static data members
    static int staticInt;
    static double staticDouble;
    static char staticChar;

    // Non-static data members
    int intVar;
    double doubleVar;
    char* charPtr;
    int& intRef;

    // Constructor
    MyClass(int i, double d, char* c, int& ref) : intVar(i), doubleVar(d), charPtr(c), intRef(ref) {}

    // Destructor
    ~MyClass() {}

    // Member functions
    void printValues() {
        std::cout << "intVar: " << intVar << ", Address: " << &intVar << std::endl;
        std::cout << "doubleVar: " << doubleVar << ", Address: " << &doubleVar << std::endl;
        std::cout << "charPtr: " << charPtr << ", Address: " << static_cast<void*>(charPtr) << std::endl;
        std::cout << "intRef: " << intRef << ", Address: " << &intRef << std::endl;
    }

    static void staticFunction() {
        std::cout << "Static Function Address: " << &staticFunction << std::endl;
    }

    void nonStaticFunction() {
        std::cout << "Non-Static Function Address: ";
        
    }
};

// Static member initialization
int MyClass::staticInt = 10;
double MyClass::staticDouble = 3.14;
char MyClass::staticChar = 'A';

// External function
void externalFunction() {
    std::cout << "External Function Address: " << &externalFunction << std::endl;
}

int main() {
    int x = 5;
    int y = 10;
    char str[] = "Hello";

    // Global object
    MyClass globalObj(1, 2.5, str, x);
    globalObj.printValues();

    // Local objects in main
    MyClass localObj1(3, 4.5, str, y);
    localObj1.printValues();

    // Local objects in external function
    externalFunction();

    // Dynamic objects
    MyClass* dynamicObj1 = new MyClass(6, 7.5, str, x);
    dynamicObj1->printValues();
    MyClass* dynamicObj2 = new MyClass(8, 9.5, str, y);
    dynamicObj2->printValues();

    // Call static and non-static member functions
    MyClass::staticFunction();
    globalObj.nonStaticFunction();

    // Cleanup
    delete dynamicObj1;
    delete dynamicObj2;

    return 0;
}
