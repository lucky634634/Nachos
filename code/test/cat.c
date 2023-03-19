#include "syscall.h"
#include "copyright.h"
#define MaxLength 255
#define READ_ONLY 1
#define READ_WRITE 0

int main()
{
    int stdin, stdout;
    char buff[MaxLength]; 
    int len;
    char content[MaxLength];
    int fileID;
    int fileSize;
    
    stdin = Open("stdin", 0);
    stdout = Open("Stdout", 1);
    if (stdin != -1 && stdout != -1)
    {
        Write("Please input filename: ", MaxLength, stdout);
        len = Read(buff, MaxLength, stdin);
        if (len == -1)
        {
            print("Error reading file name\n");
        }
        else
        {
            fileID = Open(buff, READ_ONLY);
            if (fileID == -1)
            {
                print("Error opening file\n");
            }
            else
            {
                // Get the length of the file
                fileSize = Seek(-1, fileID);
                if (fileSize == -1)
                {
                    print("Cannot read file\n");
                }
                else
                {
                    // Seek to the opening of the file and get the content
                    Seek(0, fileID);
                    Read(content, fileSize, fileID);
                    print("The content of the file is:\n");
                    print(content);
                    Close(fileID);
                }
            }
        }
    }
    Halt();
}