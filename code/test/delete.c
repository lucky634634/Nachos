#include "syscall.h"
#include "copyright.h"
#define MaxLength 255
#define READ_ONLY 1
#define READ_WRITE 0

int main()
{
    char* filename = "text.txt";
    int fileId;
    Delete(filename);
    Halt();
}