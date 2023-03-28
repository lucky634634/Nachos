#ifndef PCB_H
#define PCB_H
#include "thread.h"
#include "synch.h"

class PCB
{
private:
    Semaphore *joinSem; // semaphore cho qua trinh join
    Semaphore *exitSem; // semaphore cho qua trinh exit
    Semaphore *multex;  // semapore cho qua trinh truy xuat doc quyen
    int exitCode;
    int numWait; // so tien trinh da join

public:
    int parentID; // ID cua tien trinh cha
    PCB();
    PCB(int id); // constructor
    ~PCB();      // destructor

    // nap chuong trinh co ten luu trong bien filename va processId la pid
    int Exec(char *filename, int pid); // Tao 1 thread moi co ten la filename va process la pid
    int GetId();                       // tra ve ProcessId cua tien trinh goi thuc hien
    int GetNumWait();                  // tra ve so luong tien trinh cho
    void JoinWait();                   // Tien trinh cha doi tien trinh con ket thuc
    void ExitWait();                   // Tien trinh con ket thuc
    void JoinRelease();                // bao cho tien trinh cha thuc thi tiep
    void ExitRelease();                // cho phep tien trinh con ket thuc

    void IncNumWait(); // Tang so tien trinh cho
    void DecNumWait(); // Giam so tien trinh cho

    void SetExitCode(int ec); // Dat exitCode cua tien trinh
    int GetExitCode();        // Tra ve exitcode

    void SetFileName(char *fn); // Dat ten cua tien trinh
    char *GetFileName();        // Tra ve ten cua tien trinh
};

#endif