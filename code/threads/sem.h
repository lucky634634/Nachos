#ifndef SEM_H
#define SEM_H
#include "thread.h"
#include "synch.h"
class Sem
{
private:
    char name[50];
    Semaphore *sem; // tap semaphore de quan ly
public:
    // khoi tao doi tuong Sem. Gan gia tri ban dau la null
    // nho khoi tao bm su dung
    Sem(char *na, int i);
    ~Sem();         // huy cac doi tuong ta tao
    void Wait();    // thuc hien thao tac cho
    void Signal();  // thuc hien thao tac giai phong semaphore
    chat *GeName(); // tra ve ten cua semaphore
};
#endif