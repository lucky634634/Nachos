#include "syscall.h"
#include "copyright.h"
#define MaxLength 255

int main()
{
    int len;
    char fileName[MaxLength];
    char *content;
    int fileID;
    int fileSize;

    Write("Please input filename 1: ", MaxLength, ConsoleOutput);
    len = Read(fileName, MaxLength, ConsoleInput);
    if (len == -1)
    {
        print("Error reading file name 1\n");
    }
    else
    {
        fileID = Open(fileName, READ_ONLY);
        if (fileID == -1)
        {
            print("Error opening file\n");
        }
        else
        {
            fileSize = Seek(-1, fileID);
            if (fileSize == -1)
            {
                print("Cannot read file\n");
            }
            else
            {
                // file is empty
                if (fileSize == -2)
                {
                    fileSize = 0;
                }
                else
                {
                    fileSize++;
                }
                // Read content of file 1
                Seek(0, fileID);
                Read(content, fileSize, fileID);
                CloseFile(fileID);
                print(content);
                Write("Please input filename 2: ", MaxLength, ConsoleOutput);
                len = Read(fileName, MaxLength, ConsoleInput);
                if (len == -1)
                {
                    print("Error reading file name 2\n");
                }
                else
                {
                    fileID = Open(fileName, READ_WRITE);
                    if (fileID == -1)
                    {
                        print("Error opening file\n");
                    }
                    else
                    {
                        // Write content to file 2
                        Seek(0, fileID);
                        Write("", 0, fileID);
                        Write(content, fileSize, fileID);
                        Write("Copy successfully", MaxLength, ConsoleOutput);
                        CloseFile(fileID);
                    }
                }
            }
        }
    }

    Halt();
}