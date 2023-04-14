#ifndef STABLE_H
#define STABLE_H
#include "bitmap.h"
#include "sem.h"

#define MAX_SEMAPHORE 10

class STable
{
private:
    BitMap *bm;                   // quan ly slot trong
    Sem *semTable[MAX_SEMAPHORE]; // quan ly toi da 10 doi tuong sem
public:
    // Khoi tao size doi tuong Sem de quan ly 10 Semaphore. Gan gia tri ban dau la null
    STable();
    ~STable();
    int Create(char *name, int init); // Kiem tra Semaphore "name" chua ton tai thi tao Semaphore moi. Nguoc lai, bao loi
    int Wait(char *name);             // Neu ton tai Semaphore "name" thi goi this->P() de thuc thi
    int Signal(char *name);           // Neu ton tai Semaphore "name" thi goi this->V() de thuc thi
    int FindFreeSlot();         // Tim slot trong
};
#endif