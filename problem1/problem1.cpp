#include<iostream>
#include<type_traits>
#include <climits>


#define GET_TYPE(x)  _Generic((x), char: "char", int: "int",default: "other")

template <typename T>
constexpr std::string_view get_type() {
    using BaseType = std::decay_t<T>;
    if constexpr (std::is_same_v<BaseType, int>) return "int";
    else if constexpr (std::is_same_v<BaseType, unsigned int>) return "unsigned int";
    else if constexpr (std::is_same_v<BaseType, long long>) return "long long";
    else return "other";
}

int main()
{
    
    using namespace std;
    if constexpr (std :: is_signed_v<char>) {
        cout << "Plain char is sighed\n";
    }
    else{
        cout << "Plain char is unsigned\n";
    }

    cout << "char:                  " << sizeof(char)  << " bytes\n";
    cout << "int:                   " << sizeof(int)   << " bytes\n";
    cout << "short:                 " << sizeof(short) << " bytes\n";
    cout << "unsigned:              " << sizeof(unsigned int)  << " bytes\n";

    if constexpr (INT_MAX >= USHRT_MAX) {
        cout << "Yes: int can represent every unsigned short\n";
    } else {
        cout << "No: int cannot represent all unsigned short values\n";
    }

    cout << "Determining the char promotions\r\n";

    char a = 'a',b = 'b';
    auto c = a+b;
    cout << "Size of a: " << sizeof(a) << " bytes\n";
    cout << "Size of (a+b): " << sizeof(a+b) <<  " bytes\n";  

    if (is_same_v<decltype(a + b),int>)
    {
        cout << "Type used during addition: int\n";
    }

    cout << "sum " << c << "\n";

    cout << "Demostrating the short promotions\r\n";
    short d = 34,e = 90;
    auto f = d + e;
    auto g = d * e;
    cout << "Size of d: " << sizeof(d) << "bytes\n";
    cout << "Size of (d+e): " << sizeof(d+e) << " bytes\n";

    if (is_same_v<decltype(d+e),int>)
    {
        cout << "Type used during addition: int\n";
    }
    
    cout << "sum " << f << "\n";
    
    cout << "Size of (d*e): " << sizeof(d*e) << " bytes\n";

    if (is_same_v<decltype(d*e),int>)
    {
        cout << "Type used during multiplication: int\n";
    }

    cout << "multiplication " << g << "\n";


    cout << "Demonstrating the unsigned short promotions\r\n";

    unsigned short v1 = 9 ,v2 = 7;
    auto v3 = v1 + v2;

    cout << "Size of v1: " << sizeof(v1) << "bytes\n";
    cout << "Size of (v1+v2): " << sizeof(v1+v2) << "bytes\n";
     
    if (is_same_v<decltype(v1+v2),int>)
    {
        cout << "Type used during addition: int\n";
    }

    cout << "sum " << v3 << "\n";

    cout << "Size of (v1*v2): " << sizeof(v1*v2) << " bytes \n";

    if (is_same_v<decltype(v1*v2),int>)
    {
        cout << "Type used during multiplication: int\n";
    }
    cout << "multiplication " << v1*v2 << endl;
    cout << "Demonstrating the signed/unsigned operations\r\n";

    std::cout << "Demonstrate mixed signed/unsigned operations\n";
    int v4 = -90;
    unsigned int v5 = 89;

    std::cout << "Type of v4 and v5 respectively " << get_type<decltype(v4)>() 
              << " and " << get_type<decltype(v5)>() << "\r\n";
    std::cout << "Type of v4+v5 " << get_type<decltype(v4 + v5)>() << " ";
    std::cout << "result is " << (v4 + v5) << "\n";
    std::cout << "To mitigate this conversion which created the incorrect solutions\r\n";
    std::cout << "cast unsigned integer as long long result is " 
              << (static_cast<long long>(v5) + v4) << "\r\n";
    
    // General rule for arithmetic in coding: both should have the same sign datatype 
    // (either both signed or both unsigned).

    std::cout << "Demonstrating a surprising comparison\r\n";
    if (-1 < 1U) // convert to 1LL (or use std::cmp_less in C++20) for correct result
    {
        std::cout << "1 is greater than -1\r\n";
    }
    else
    {
        std::cout << "-1 is greater than 1\r\n";
    }
    
    return 0;
}