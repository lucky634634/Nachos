#include "syscall.h"
#include "copyright.h"

int main()
{
    char *filename = "text.txt";

    // Create a file;
    if (Create(filename) == -1)
    {
        // Error
        print("\nCreate file ");
        print(filename);
        print(" fail");
    }
    else
    {
        // Success
        print("\nCreate file ");
        print(filename);
        print(" successfully\n");
    }
    Open("text1.txt", 1);
    Close(2);
    // Exit(2);
    Halt();
}