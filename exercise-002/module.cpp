#include "module.h"

#include <fmt/format.h>

/* .bss Segment */
int foo;
int foo2 = 0;

/* .data Segment */
int data = 45;
int data2 = 43;

/* .rodata Segment */

const int rodata = 45;
const int rodata2 = 43;

const int big_data_blob[] = {42,0xff};

/* CODE */
static int moduleCounter;
static int moduleValue = 123;

void printTwoValues(){
    printValueAndAddress("moduleCounter", &moduleCounter);
    printValueAndAddress("moduleValue", &moduleValue);
}

void printValueAndAddress(const char* name, int* value)
{
    fmt::print("[printValueAndAddress] {} = {}, address = {}\n",
               name,
               *value,
               fmt::ptr(value));
}
/* END CODE */

void doSomething(int value)
{
    value = value + 1;
    fmt::print("doSomething, value {}\n", value);
    fmt::print("doSomethingStatic, address of value {}\n", fmt::ptr(&value));
}

void doSomethingPtr(int* ptr)
{
    *ptr = *ptr + 1;
    fmt::print("doSomethingPtr, value {}\n", *ptr);
    /* fmt::print("doSomethingStatic, address of value {}\n", fmt::ptr(*ptr));*/
}

int* doReturnAPtr()
{
    int value = 4711;
    fmt::print("doReturnAPtr, value {}\n", value);
    /* 
     * This causes a warning and shall be avoided by all means
     * warning: address of stack memory associated with local variable 'value' returned [-Wreturn-stack-address]
     */
    return &value;
}

void doSomethingStatic()
{
    static int value = 56;
    value = value + 1;
    fmt::print("[doSomethingStatic] Value {}\n", value);
    fmt::print("[doSomethingStatic] Address of value {}\n", fmt::ptr(&value));
    
    int nonStaticValue = 56;
    nonStaticValue = nonStaticValue + 1;
    fmt::print("[doSomethingStatic] nonStaticValue {}\n", nonStaticValue);
    fmt::print("[doSomethingStatic] Address of nonStaticValue {}\n", fmt::ptr(&nonStaticValue));
}
