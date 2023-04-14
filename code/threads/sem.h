#ifndef SEM_H
#define SEM_H
#include "thread.h"
#include "synch.h"
#define MaxFileLength 255
class Sem
{
private:
    char name[MaxFileLength];
    Semaphore *sem; // tap semaphore de quan ly
public:
    // khoi tao doi tuong Sem. Gan gia tri ban dau la null
    // nho khoi tao bm su dung
    Sem(char *na, int i);
    ~Sem();          // huy cac doi tuong ta tao
    void Wait();     // thuc hien thao tac cho
    void Signal();   // thuc hien thao tac giai phong semaphore
    char *GetName(); // tra ve ten cua semaphore
};
#endif