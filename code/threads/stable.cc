#include "stable.h"

STable::STable()
{
    this->bm = new BitMap(MAX_SEMAPHORE);
    for (int i = 0; i < MAX_SEMAPHORE; i++)
    {
        this->semTable[i] = NULL;
    }
}

STable::~STable()
{
    if (this->bm != NULL)
    {
        delete this->bm;
    }
    for (int i = 0; i < MAX_SEMAPHORE; i++)
    {
        if (this->semTable[i] != NULL)
        {
            delete this->semTable[i];
        }
    }
}

int STable::Create(char *name, int init)
{
    for (int i = 0; i < MAX_SEMAPHORE; i++)
    {
        if (bm->Test(i))
        {
            if (strcmp(name, semTable[i]->GetName()) == 0)
            {
                return -1;
            }
        }
    }
    int id = this->FindFreeSlot();

    if (id < 0)
    {
        return -1;
    }

    this->semTable[id] = new Sem(name, init);
    return 0;
}

int STable::Wait(char *name)
{
    for (int i = 0; i < MAX_SEMAPHORE; i++)
    {
        if (strcmp(name, semTable[i]->GetName()) == 0)
        {
            semTable[i]->Wait();
            return 0;
        }
    }
    printf("Khong ton tai semaphore\n");
    return -1;
}

int STable::Signal(char *name)
{
    for (int i = 0; i < MAX_SEMAPHORE; i++)
    {
        if (strcmp(name, semTable[i]->GetName()) == 0)
        {
            semTable[i]->Signal();
            return 0;
        }
    }
    printf("Khong ton tai semaphore\n");
    return -1;
    return 0;
}

int STable::FindFreeSlot()
{
    return this->bm->Find();
}
