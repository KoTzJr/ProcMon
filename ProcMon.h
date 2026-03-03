//
// Created by KoTz on 18/02/2026.
//

#ifndef UNTITLED8_PROCMON_H
#define UNTITLED8_PROCMON_H

#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>


typedef std::string str;
class ProcessList {
public :
     DWORD pid;
     str name;
     DWORD numThreads;

    ProcessList(DWORD pid,std::string name,DWORD num) {
        this->pid=pid;
        this->name=name;
        this->numThreads=num;
    }
};
struct Name_exe {
    str AppName;
    str Name;
};
struct PID {
    DWORD id;
    DWORD pid;
};

struct Thread {
    DWORD thread;
    DWORD ThreadID;
};
typedef std::vector<ProcessList> ListProcess;
typedef DWORD DWValue;

class ProcMon
    {
        private :
            HANDLE Handle;
            PROCESSENTRY32 pEntry;
private :
        void  Snapshot ();
        void  ProcessEnrty();
public :
        void Process(ListProcess & item);
        ProcMon ();
        ~ProcMon();
        PROCESSENTRY32 GetEntry();
        static  bool Search (Name_exe E,PID ID,Thread T);
        static  bool SearchID(DWValue id,ProcessList list);
        static  bool SearchName(str ExeAppName,str obj);
        void KillProcess(DWValue id);

};



#endif //UNTITLED8_PROCMON_H