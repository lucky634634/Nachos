#ifndef PTABLE_H
#define PTABLE_H
#include "synch.h"
#include "bitmap.h"
#include "pcb.h"

#define MAX_PROCESS 10

class PTable
{
private:
    BitMap* bm; // danh dau cac vi tri da duoc su dung trong pcb
    PCB *pcb[MAX_PROCESS];
    int pSize;
    Semaphore *bmSem; // dung de ngan chan truong hop nap 2 tien trinh cung luc
public:
    // khoi tai size doi tuong PCB de luu size process. Gan gia tri ban dau la null
    // nho khoi tao bm va bmSem de su dung
    PTable(int size);
    ~PTable();                  // huy cac doi tuong da tao
    int ExecUpdate(char *name); // xu ly cho system call SC_Exec
    int ExitUpdate(int ec);     // xu ly cho system call SC_Exit
    int JoinUpdate(int id);     // xu ly cho system call SC_Join
    int GetFreeSlot();          // tim free slot de luu thong tin cho tien trinh moi
    bool IsExist(int pid);      // kiem tra ton tai ProcessId nay khong
    void Remove(int pid);       // khi tien trinh ket thuc, delete processId ra khoi mang quan ly no
    char *GetFileName(int id);  // tra ve ten cua tien trinh
};
#endif