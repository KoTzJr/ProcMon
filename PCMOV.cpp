//
// Created by KoTz on 18/02/2026.
//

#include "PCMOV.h"
#include <iostream>

ProcMon::PCMOV::PCMOV() {
    Handle = INVALID_HANDLE_VALUE;
    ProcessEnrty();
}

ProcMon::PCMOV::~PCMOV() {
    if (Handle != INVALID_HANDLE_VALUE) {
        CloseHandle(Handle);
    }
}
void ProcMon::PCMOV::Snapshot() {
    HANDLE get = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (get == INVALID_HANDLE_VALUE) {
         return;
    }
    Handle = get;
}

void ProcMon::PCMOV::ProcessEnrty() {

    pEntry.dwSize = sizeof(PROCESSENTRY32);
}

double ProcMon::PCMOV::MemoryRAM(DWORD id) {

    HANDLE Hand;
    PROCESS_MEMORY_COUNTERS pm = {};
    Hand = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE,id);
    if (GetProcessMemoryInfo(Hand,&pm,sizeof(PROCESS_MEMORY_COUNTERS)) != 0) {
        CloseHandle(Hand);
        return (double)pm.WorkingSetSize / (1024 * 1024);
    }
    if (Hand != NULL) {
        CloseHandle(Hand);
    }
    return 0.0;
}

void ProcMon::PCMOV::ProcessPrint(VecPCMOV & processes) {
        if (Handle != INVALID_HANDLE_VALUE) {
            CloseHandle(Handle);
            Handle = INVALID_HANDLE_VALUE;
        }
        Snapshot();

        if (Handle == INVALID_HANDLE_VALUE) {
            return;
        }

        if (!Process32First(Handle, &pEntry)) {
            CloseHandle(Handle);
            Handle = INVALID_HANDLE_VALUE;
            return;
        }

        do {
            if (pEntry.th32ProcessID != 0) {
                // std::cout << CPU(pEntry.th32ProcessID) << "\n";
            }
            // Converter WCHAR para std::string
            char exeName[MAX_PATH];
            WideCharToMultiByte(CP_ACP, 0, pEntry.szExeFile, -1, exeName, MAX_PATH, NULL, NULL);
            
            processes.push_back(ProcessList(
                      pEntry.th32ProcessID,
                      std::string(exeName),
                      pEntry.cntThreads,
                      MemoryRAM(pEntry.th32ProcessID),
                      URL_Process_Exe(pEntry.th32ProcessID)));
        }while (Process32Next(Handle, &pEntry));
}

str ProcMon::PCMOV::URL_Process_Exe(DWORD id) {
    WCHAR buffer[MAX_PATH];
    DWORD value = MAX_PATH;
    HANDLE ts;
    str nome_local = "";
    ts = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE,  id);
    if (QueryFullProcessImageName(ts, 0, buffer, &value) != 0) {
        // Converter WCHAR para std::string
        char path[MAX_PATH];
        WideCharToMultiByte(CP_ACP, 0, buffer, -1, path, MAX_PATH, NULL, NULL);
        nome_local = path;
        CloseHandle(ts);
        return nome_local;
    }
    if (ts != NULL) {
        CloseHandle(ts);
    }
    return "";
}

double ProcMon::PCMOV::CPU(DWORD id) {

     HANDLE Hand;
     ULARGE_INTEGER  kernel1{},user1{},kernel2{},user2{};
      FILETIME criar{},saida{},kernel{},user{};
     Hand = OpenProcess(PROCESS_QUERY_INFORMATION,FALSE,id);

     if (Hand ==INVALID_HANDLE_VALUE) {
         std::cout << GetLastError() << std::endl;
     }

    kernel1.LowPart = kernel.dwLowDateTime;
    kernel1.HighPart = kernel.dwHighDateTime;

    user1.LowPart = user.dwLowDateTime;
    user1.HighPart = user.dwHighDateTime;

    if  (GetProcessTimes(Hand,&criar,&saida,&kernel,&user) == false) {
        CloseHandle(Hand);
        return 0;
    }

    kernel2.LowPart = kernel.dwLowDateTime;
    kernel2.HighPart = kernel.dwHighDateTime;
    user2.LowPart = user.dwLowDateTime;
    user2.HighPart = user.dwHighDateTime;

    _sleep(1000);

   if (GetProcessTimes(Hand,&criar,&saida,&kernel,&user) == false) {
       CloseHandle(Hand);
       return 0;
   };

    double value = (kernel2.QuadPart + user2.QuadPart) - (kernel1.QuadPart + user1.QuadPart);
    return value / 10000000.0;;
}

ProcMon::VecPCMOV ProcMon::PCMOV::Process(){

    VecPCMOV obj;
    ProcessPrint(obj);
    return obj;
}
void ProcMon::PCMOV::Process(VecPCMOV & item) {
    ProcessPrint(item);
}
void ProcMon::PCMOV::KillProcess(DWValue id) {
  auto get = OpenProcess(PROCESS_TERMINATE, FALSE, id);
    if (get == NULL) {
        std::cout << GetLastError() << std::endl;
        return;
    }
    TerminateProcess(get,false);
    CloseHandle(get);
}

bool ProcMon::PCMOV::SearchNameAppExe(ProcMon::AppNameExe ExeAppName) {
    if (ExeAppName.name_exe_name.empty() == false  && ExeAppName.Name_.empty() == false) {
        return ExeAppName.name_exe_name.find(ExeAppName.Name_) != std::string::npos;
    }
    return false;
}

bool ProcMon::PCMOV::Search(ProcMon::AppNameExe E, ProcMon::PID ID, ProcMon::Thread T) {
    if (E.name_exe_name.empty() == false
        && E.Name_.empty() == false) {
        return E.name_exe_name.find(E.Name_) !=
            std::string::npos && ID.pid == ID.id && T.thread == T.ThreadID;
    }
    return false;
}

PROCESSENTRY32 ProcMon::PCMOV::GetEntry() {
    return pEntry;
}

bool ProcMon::PCMOV::SearchID(DWORD id,ProcessList list) {
    return list.pid == id;
}
