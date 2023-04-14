#include "ptable.h"
#include "openfile.h"
#include "system.h"

PTable::PTable(int size)
{
    int i;
    pSize = size;
    bm = new BitMap(size);
    bmSem = new Semaphore("BMSem", 1);
    for (i = 0; i < MAX_PROCESS; i++)
    {
        pcb[i] = NULL;
    }
    bm->Mark(0);
    pcb[0] = new PCB(0);
    pcb[0]->parentID = -1;
}

PTable::~PTable()
{
    delete bm;
    delete bmSem;
    for (int i = 0; i < MAX_PROCESS; i++)
    {
        delete pcb[i];
    }
}

int PTable::ExecUpdate(char *name)
{
    bmSem->P();

    if (strcmp(name, currentThread->getName()) == 0)
    {
        printf("Process tries to execute itself\n");
        bmSem->V();
        return -1;
    }

    int id = GetFreeSlot();
    if (id < 0)
    {
        printf("Not enough space\n");
        bmSem->V();
        return -1;
    }
    pcb[id] = new PCB(id);
    pcb[id]->SetFileName(name);

    pcb[id]->parentID = currentThread->GetId();
    int pid = pcb[id]->Exec(name, id);

    bmSem->V();
    return pid;
}

int PTable::ExitUpdate(int ec)
{
    int id = currentThread->GetId();
    if (id == 0)
    {
        currentThread->FreeSpace();
        interrupt->Halt();
        return 0;
    }

    if (IsExist(id) == false)
    {
        printf("This id '%d' is not exist", id);
        return -1;
    }

    pcb[id]->SetExitCode(ec);
    pcb[pcb[id]->parentID]->DecNumWait();

    pcb[id]->JoinRelease();
    pcb[id]->ExitWait();

    Remove(id);
    return ec;
}

int PTable::JoinUpdate(int id)
{
    if (id < 0 || id > 9)
    {
        printf("Unavailable process\n");
        return -1;
    }

    if (pcb[id] == NULL)
    {
        printf("Unavailable process\n");
        return -1;
    }

    if (currentThread->GetId() != pcb[id]->parentID)
    {
        printf("Process tries to join not parent process\n");
        return -1;
    }

    pcb[pcb[id]->parentID]->IncNumWait();
    pcb[id]->JoinWait();
    int exitCode = pcb[id]->GetExitCode();

    pcb[id]->ExitRelease();
    return exitCode;
}

int PTable::GetFreeSlot()
{
    return bm->Find();
}

bool PTable::IsExist(int pid)
{
    if (pid < 0 || pid > 9)
    {
        return false;
    }
    return bm->Test(pid);
}

void PTable::Remove(int pid)
{
    bm->Clear(pid);
    if (pcb[pid] != NULL)
    {
        delete pcb[pid];
    }
}

char *PTable::GetFileName(int id)
{
    return pcb[id]->GetFileName();
}