#include "syscall.h"
#include "copyright.h"
#define MaxLength 255
#define READ_ONLY 1
#define READ_WRITE 0

int main()
{
    int stdin, stdout, len;
    char fileName[MaxLength];
    char content[MaxLength];
    int fileID;
    int fileSize;

    stdin = Open("stdin", 0);
    stdout = Open("stdout", 1);
    if (stdin != -1 && stdout != -1)
    {
        Write("Please input filename 1: ", MaxLength, stdout);
        len = Read(fileName, MaxLength, stdin);
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
                    // Read content of file 1
                    Seek(0, fileID);
                    Read(content, fileSize, fileID);
                    Close(fileID);
                    Write("Please input filename 2: ", MaxLength, stdout);
                    len = Read(fileName, MaxLength, stdin);
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
                            Write("", MaxLength, fileID);
                            Write(content, fileSize, fileID);
                            Write("Copy successfully", MaxLength, stdout);
                            Close(fileID);
                        }
                    }
                }
            }
        }
    }
    Halt();
}