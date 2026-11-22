#include<stdio.h>
#include<limits.h>
#include<stdbool.h>

// #if CHAR_MIN == 0
//     #pragma message("char is unsigned")
// #else
//     #pragma message("char is signed")
// #endif

//x86 /x86_64 (Windows ,Linux,macOS):Usually signed.
//ARM /ARM_64 (Linux,embedded systems,Raspberry Pi): Usually unsigned 

//Macro to inspect the exact type of an expression at compile time 
#define GET_TYPE(x) _Generic((x), char: "char", int: "int", short: "short" , unsigned short: "unsigned short" ,unsigned int: "unsigned int" ,default: "other")

int main()
{
    bool is_char_signed = 0;
    if (is_char_signed = (CHAR_MIN < 0))
    {
        printf("char is signed (CHAR_MIN = %d)\n", CHAR_MIN);
    }
    else
    {
        printf("char is Unsigned (CHAR_MIN = %d)\n", CHAR_MIN);
    }
    
    //over here we are promoting the char data CHAR_MIN to the integer 
    //so by then first we typecast the -1 to char which is integer 
    //over here we don't know how system will take this since if 
    //it is signed minimum value in system for char is the -ve or if it 
    //is unsigned the minimum value is +ve

    printf("char :                   %zu bytes\n",sizeof(char));
    printf("int :                    %zu bytes\n",sizeof(int));
    printf("short :                  %zu bytes\n",sizeof(short));
    printf("unsigned :               %zu bytes\n",sizeof(unsigned));

    if (INT_MAX >= USHRT_MAX)
        printf("Yes : int can represent every unsigned short (USHRT_MAX = %u), (INT_MAX = %d)",USHRT_MAX,INT_MAX);
    else
        printf("No int cannot represet all unsigned short values \n");


    printf("demonstrating the char promotions\r\n");
    char a = 'a',b = 'b';

    printf("Type of a: %s (size of %zu bytes)\n",GET_TYPE(a),sizeof(a));
    printf("Type of a + b: %s (size: %zu bytes)\n",GET_TYPE(a+b),sizeof(a+b));
    printf("Sum: %d\n", a+b);


    printf("demonstrating same with the short\r\n");
    short d = 23,e = 24;
    
    printf("Type of d: %s (size of %zu bytes)\n",GET_TYPE(d),sizeof(d));
    printf("Type of d+e: %s (size: %zu bytes)\n",GET_TYPE(d+e),sizeof(d+e));
    printf("Type of d*e: %s (size: %zu bytes)\n",GET_TYPE(d*e),sizeof(d*e));

    printf("Demonstrating the unsigned short promotion\r\n");

    unsigned short v1 = 9, v2 = 6;
    printf("Type of v1: %s (size of %zu bytes)\n",GET_TYPE(v1),sizeof(v1));
    printf("Type of v1+v2: %s (size: %zu bytes)\n",GET_TYPE(v1+v2),sizeof(v1+v2));


    //Why Both Operands Must Be Promoted First

    //Hardware Architecture: Most modern CPUs do not have dedicated arithmetic instructions 
    //for 8-bit (char) or 16-bit (short) registers; their Arithmetic Logic Units (ALUs) operate natively on 32-bit or 64-bit registers (int).
    //Preventing Intermediate Overflow: Consider char a = 100, b = 100;. 
    //A signed 8-bit char can only hold values up to 127. If a and b were added as chars first and promoted afterward, 100 + 100 would overflow to -56 before becoming an int. 
    //By promoting both operands to int before adding, 100 + 100 safely computes 200.
    //happens with all char,short,unsigned short Every small integer type—bool, char, signed char, unsigned char, short, and unsigned short—gets 
    //promoted to int before addition on standard modern systems.

    printf("Demonstrate mixed signed/unsigned operations\n");
    int v4 = -90;
    unsigned int v5 = 89;

    printf("Type of v4 and v5 respectively %s and %s\r\n",GET_TYPE(v4),GET_TYPE(v5));
    printf("Type of v4+v5 %s ",GET_TYPE(v4+v5));
    printf("result is %u",v4+v5);
    printf("to mitigate this conversion which created the incorrect solutions\r\n");
    printf("cast unsigned interger as long long result is %lld\r\n",(long long)v5 + v4);
    //General rule for arithmetic in coding both should have same sign datatype like both 
    //should ether signed or unsigned.

    printf("Demonstrating a surprising comparision\r\n");
    if(-1 < 1U)//convert it to long long means 1LL for correct result
    {
        printf("1 is greater than -1\r\n");
    }
    else
    {
        printf("-1 is greater than 1\r\n");
    }
    return 0;
    //Same general rule which was related to the srithmetic operation while comparing too
    //-1 is get converted into UINT_MAX value since while comparision cpu converted both into 
    //unsigned int

}


