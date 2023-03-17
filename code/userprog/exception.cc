// exception.cc
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "filesys.h"
#define MaxFileLength 255

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2.
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions
//	are in machine.h.
//----------------------------------------------------------------------

char *User2System(int virtAddr, int limit)
{
    int i;
    int oneChar;
    char *kernelBuf = NULL;
    kernelBuf = new char[limit + 1]; // Need for terminal string
    if (kernelBuf == NULL)
    {
        return kernelBuf;
    }
    memset(kernelBuf, 0, limit + 1);

    for (i = 0; i < limit; i++)
    {
        machine->ReadMem(virtAddr + i, 1, &oneChar);
        kernelBuf[i] = (char)oneChar;

        if (oneChar == 0)
            break;
    }
    return kernelBuf;
}

int System2User(int virtAddr, int len, char *buffer)
{
    if (len < 0)
        return -1;
    if (len == 0)
        return len;
    int i = 0;
    int oneChar = 0;
    do
    {
        oneChar = (int)buffer[i];
        machine->WriteMem(virtAddr + i, 1, oneChar);
        i++;
    } while (i < len && oneChar != 0);
    return i;
}

void IncreasePC()
{
    machine->registers[PrevPCReg] = machine->registers[PCReg];
    machine->registers[PCReg] = machine->registers[NextPCReg];
    machine->registers[NextPCReg] += 4;
}

void ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    switch (which)
    {
    case NoException:
        interrupt->Halt();
        return;

    case SyscallException:
        switch (type)
        {
        case SC_Halt:
        {
            DEBUG('a', "Shutdown, initiated by user program.\n");
            printf("\n\nShutdown, initiated by user program\n");
            interrupt->Halt();
            break;
        }

        case SC_Exit:
        {
            int code = machine->ReadRegister(4);
            DEBUG('a', "Exit with code %d\n", code);
            printf("\nExit with code %d\n", code);
            currentThread->Finish();
            IncreasePC();
            break;
        }

        case SC_Exec:
        {
            break;
        }

        case SC_Join:
        {
            break;
        }

        case SC_Create:
        {
            int virtAddr;
            char *filename;

            DEBUG('a', "\nSC_Create call ...");
            DEBUG('a', "\nReading virtual address of filename");

            virtAddr = machine->ReadRegister(4);
            DEBUG('a', "\nReading filename.");
            filename = User2System(virtAddr, MaxFileLength + 1);
            if (filename == NULL)
            {
                printf("\nNot enough memory in system");
                DEBUG('a', "\nNot enough memory in system");
                machine->WriteRegister(2, -1);
                delete[] filename;
                return;
            }
            DEBUG('a', "\nFinish reading filename.");

            if (!fileSystem->Create(filename, 0))
            {
                printf("\nError create file '%s'", filename);
                machine->WriteRegister(2, -1);
                delete[] filename;
                return;
            }
            machine->WriteRegister(2, 0);
            IncreasePC();
            delete[] filename;
            break;
        }

        case SC_Open:
        {
            int virtAddr = machine->ReadRegister(4);
            int type = machine->ReadRegister(5);
            char *filename;

            if (fileSystem->size >= 10)
            {
                machine->WriteRegister(2, -1);
                delete[] filename;
                return;
            }
            filename = User2System(virtAddr, MaxFileLength + 1);

            if (strcmp(filename, "stdin") == 0)
            {
                printf("Stdin mode\n");
                machine->WriteRegister(2, 0);
                delete[] filename;
                return;
            }

            if (strcmp(filename, "stdout") == 0)
            {
                printf("Stdout mode\n");
                machine->WriteRegister(2, 1);
                delete[] filename;
                return;
            }

            int nextSlot = fileSystem->size;
            fileSystem->openFiles[nextSlot] = fileSystem->Open(filename);
            if (fileSystem->openFiles[nextSlot] != NULL)
            {
                printf("\nOpen file '%s' successfully", filename);
                fileSystem->size++;
                machine->WriteRegister(2, nextSlot);
            }
            else
            {
                printf("\nCan not open file '%s'", filename);
                machine->WriteRegister(2, -1);
            }

            delete[] filename;
            IncreasePC();
            break;
        }

        case SC_Write:
        {
            break;
        }

        case SC_Close:
        {
            break;
        }

        case SC_Fork:
        {
            break;
        }

        case SC_Yield:
        {
            break;
        }

        case SC_Print:
        {
            int virtAddr;
            char *string;
            virtAddr = machine->ReadRegister(4);
            string = User2System(virtAddr, MaxFileLength + 1);

            printf(string);
            IncreasePC();
            delete[] string;
            break;
        }
        }
        break;

    case PageFaultException:
    {
        printf("\nNo valid translation found.\n");
        ASSERT(FALSE);
        break;
    }

    case ReadOnlyException:
    {
        printf("\nWrite attempted to page marked \"read only\".\n");
        ASSERT(FALSE);
        break;
    }

    case BusErrorException:
    {
        printf("\nTranslation resulted in an invalid physical address\n");
        ASSERT(FALSE);
        break;
    }

    case AddressErrorException:
    {
        printf("\nUnaligned reference or one that was beyond the end of the address space.\n");
        ASSERT(FALSE);
        break;
    }

    case OverflowException:
    {
        printf("\nInteger overflow in add or sub.\n");
        ASSERT(FALSE);
        break;
    }

    case IllegalInstrException:
    {
        printf("\nUnimplemented or reserved instr.\n");
        ASSERT(FALSE);
        break;
    }

    case NumExceptionTypes:
    {
        printf("\nNumber Exception Types error.\n");
        ASSERT(FALSE);
        break;
    }
    default:
        printf("\nUnexpected user mode exception (%d %d)", which, type);
        interrupt->Halt();
        break;
    }
}