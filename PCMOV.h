//
// Created by KoTz on 18/02/2026.
//

#ifndef UNTITLED8_PROCMON_H
#define UNTITLED8_PROCMON_H

#include <string>
#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include <psapi.h>


typedef std::string str;


namespace ProcMon {

    class info {
         public :
             DWORD pid;
             str name;
             DWORD numThreads;
             DWORD MemRam;
    };

    class ProcessList {
    public :
         DWORD pid;
         str name;
         DWORD numThreads;
         DWORD MemRam;
         str local;
        ProcessList(DWORD pid,std::string name,DWORD num,double RAM,str local) {
            this->pid=pid;
            this->name=name;
            this->numThreads=num;
            this->MemRam=RAM;
            this->local = local;
        }
    };
    struct AppNameExe {
        str name_exe_name;
        str Name_;
    };
    struct PID {
        DWORD id;
        DWORD pid;
    };

    struct Thread {
        DWORD thread;
        DWORD ThreadID;
    };

    typedef std::vector<ProcessList> VecPCMOV;
    typedef DWORD DWValue;

    class PCMOV
    {
    private :
        HANDLE Handle;
        PROCESSENTRY32 pEntry;
    private :
            void  Snapshot ();
            void  ProcessEnrty();
            void ProcessPrint(VecPCMOV & processes);
            str local (DWORD id);
            PROCESSENTRY32 GetEntry();
            double MemoryRAM(DWORD id);
    public :
            void Process(VecPCMOV & item);
            VecPCMOV Process();
            PCMOV ();
           ~PCMOV();
           static  bool Search (ProcMon::AppNameExe Exe,ProcMon::PID ID,ProcMon::Thread T);
           static  bool SearchID(DWValue id,ProcessList list);
           static  bool SearchNameAppExe(ProcMon::AppNameExe);
           void KillProcess(DWValue id);
    };
}

#endif //UNTITLED8_PROCMON_H