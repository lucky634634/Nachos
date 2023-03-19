#include "syscall.h"
#include "copyright.h"
#define MaxLength 255
#define READ_ONLY 1
#define READ_WRITE 0

int main()
{
    char buff[MaxLength];
    int len;
    char content[MaxLength];
    int fileID;
    int eof;

    Write("Please input filename: ", MaxLength, ConsoleOutput);
    len = Read(buff, MaxLength, ConsoleInput);
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
            // Get end of file
            eof = Seek(-1, fileID);
            if (eof == -1)
            {
                print("Cannot read file\n");
            }
            else if (eof == -2)
            {
                Close(fileID);
            }
            else
            {
                // Seek to the opening of the file and get the content
                Seek(0, fileID);
                Read(content, eof + 1, fileID);
                print("The content of the file is:\n");
                print(content);
                print("\n");
                Close(fileID);
            }
        }
    }

    Halt();
}