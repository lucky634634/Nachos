#include "syscall.h"

int main()
{
    int pingID;
    int pongID;
    pingID = Exec("./test/ping");
    pongID = Exec("./test/pong");
    Join(pingID);
    Join(pongID);
}