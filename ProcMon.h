//
// Created by KoTz on 18/02/2026.
//

#ifndef UNTITLED8_PROCMON_H
#define UNTITLED8_PROCMON_H

#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>

class ProcessList {
public :
     DWORD pid;
     std::string nome;
     DWORD numThreads;

    ProcessList(DWORD pid,std::string nome,DWORD num) {
        this->pid=pid;
        this->nome=nome;
        this->numThreads=num;
    }
};
typedef std::vector<ProcessList> Sy;

class ProcMon
    {
        private :
            HANDLE Handle;
            PROCESSENTRY32 pEntry;
private :
        void  Snapshot ();
        void  ProcessEnrty();
public :
            Sy Process();
    ProcMon ();

};



#endif //UNTITLED8_PROCMON_H