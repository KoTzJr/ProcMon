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
     std::string name;
     DWORD numThreads;

    ProcessList(DWORD pid,std::string nome,DWORD num) {
        this->pid=pid;
        this->name=nome;
        this->numThreads=num;
    }
};
struct NAME_Exe {
    std::string AppName;
    std::string Name;
};
struct PID {
    DWORD id;
    DWORD pid;
};

struct Thread {
    DWORD thread;
    DWORD ThreadID;
};
typedef std::vector<ProcessList> Sy;
typedef DWORD _VALUE_;

class ProcMon
    {
        private :
            HANDLE Handle;
            PROCESSENTRY32 pEntry;
private :
        void  Snapshot ();
        void  ProcessEnrty();
public :
        void Process(Sy & i);
        ProcMon ();
        ~ProcMon();
        PROCESSENTRY32 GetEntry();
        bool Search (NAME_Exe E,PID ID,Thread T);
        static bool SearchID(_VALUE_ id,ProcessList list);
        bool SearchName(std::string ExeAppName,std::string obj);
        void KillProcess(_VALUE_ id);

};



#endif //UNTITLED8_PROCMON_H