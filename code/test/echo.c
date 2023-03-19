#include "syscall.h"
#include "copyright.h"
#define MaxLength 255

int main()
{
    int stdin, stdout;
    char buff[MaxLength]; 
    int len;
    
    stdin = Open("stdin", 0);
    stdout = Open("stdout", 1);
    if (stdin != -1 && stdout != -1)
    {
        Write("Please write something: ", MaxLength, stdout);
        //Read string from stdin and write it down in stdout
        len = Read(buff, MaxLength, stdin);
        if (len != -1)
        {
            print("Input string: ");
            print(buff);
            print("\n");
        }
    }
    Halt();
}