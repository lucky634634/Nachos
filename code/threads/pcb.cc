#include "pcb.h"
#include "utility.h"
#include "system.h"
#include "thread.h"
#include "addrspace.h"

PCB::PCB(int id)
{
    joinSem = new Semaphore("JoinSem", 0);
    exitSem = new Semaphore("ExitSem", 0);
    mutex = new Semaphore("Mutex", 1);

    exitCode = 0;
    numWait = 0;

    if (id == 0)
    {
        this->parentID = -1;
    }
    else
    {
        this->parentID = currentThread->GetId();
    }
    thread = NULL;
}

PCB::~PCB()
{
    delete joinSem;
    delete exitSem;
    delete mutex;
    if (thread != NULL)
    {
        thread->FreeSpace();
        thread->Finish();
    }
}

int PCB::Exec(char *filename, int pid)
{
    mutex->P();
    thread = new Thread(filename);
    if (thread == NULL)
    {
        printf("Not enough space\n");
        mutex->V();
        return -1;
    }
    thread->SetId(pid);
    parentID = currentThread->GetId();
    thread->Fork(StartProcess, pid);
    mutex->V();
    return pid;
}

int PCB::GetId()
{
    return thread->GetId();
}

int PCB::GetNumWait()
{
    return this->numWait;
}

void PCB::JoinWait()
{
    joinSem->P();
}

void PCB::ExitWait()
{
    exitSem->P();
}

void PCB::JoinRelease()
{
    joinSem->V();
}

void PCB::ExitRelease()
{
    exitSem->V();
}

void PCB::IncNumWait()
{
    mutex->P();
    numWait++;
    mutex->V();
}

void PCB::DecNumWait()
{
    mutex->P();
    if (numWait > 0)
    {
        numWait--;
    }
    mutex->V();
}

void PCB::SetExitCode(int ec)
{
    this->exitCode = ec;
}

int PCB::GetExitCode()
{
    return exitCode;
}

void PCB::SetFileName(char *fn)
{
    strcpy(fileName, fn);
}

char *PCB::GetFileName()
{
    return this->fileName;
}

void StartProcess(int id)
{
    char *filename = pTable->GetFileName(id);
    AddrSpace *space;
    OpenFile *executable = fileSystem->Open(filename);
    if (executable == NULL)
    {
        printf("Can't open file %s\n", filename);
        return;
    }
    space = new AddrSpace(executable);
    if (space == NULL)
    {
        printf("Can't create addrSpace\n");
        return;
    }
    currentThread->space = space;
    currentThread->space->InitRegisters(); // set the initial register values
    currentThread->space->RestoreState();  // load page table register

    machine->Run(); // jump to the user program
    ASSERT(FALSE);  // machine->Run never returns;
                    // the address space exits
                    // by doing the syscall "exit"
}