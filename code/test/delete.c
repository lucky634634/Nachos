#include "syscall.h"
#include "copyright.h"
#define MaxLength 255

int main()
{
    char *filename = "text.txt";
    int fileId;
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
        fileId = Open(filename, 1);
        Delete(filename);
    }

    Halt();
}