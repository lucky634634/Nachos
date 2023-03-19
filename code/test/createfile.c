#include "syscall.h"
#include "copyright.h"

int main()
{
    char *filename = "text.txt";

    // Create a file;
    if (CreateFile(filename) == -1)
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
    // Exit(2);
    Halt();
}