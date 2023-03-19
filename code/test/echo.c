#include "syscall.h"
#include "copyright.h"
#define MaxLength 255

int main()
{
    char buff[MaxLength];
    int len;

    Write("Please write something: ", MaxLength, ConsoleOutput);
    // Read string from stdin and write it down in stdout
    len = Read(buff, MaxLength, ConsoleInput);
    if (len != -1)
    {
        print("Input string: ");
        print(buff);
        print("\n");
    }

    Halt();
}