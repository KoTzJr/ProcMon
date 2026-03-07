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

double ProcMon::PCMOV::MemoryRAM(DWORD id ) {

    HANDLE Hand;
    PROCESS_MEMORY_COUNTERS pm = {};
    Hand = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE,id);
    if (GetProcessMemoryInfo(Hand,&pm,sizeof(PROCESS_MEMORY_COUNTERS)) == true) {
        return (double)pm.WorkingSetSize / (1024 * 1024);
    }
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
            processes.push_back(ProcessList{
                pEntry.th32ProcessID,
                std::string(pEntry.szExeFile),
                pEntry.cntThreads,
                     MemoryRAM(pEntry.th32ProcessID),
                     local(pEntry.th32ProcessID)});
        }while (Process32Next(Handle, &pEntry));
}

str ProcMon::PCMOV::local(DWORD id) {
    char buffer[MAX_PATH];
    DWORD value = MAX_PATH;
    HANDLE ts;
    str nome_local = "";
    ts = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE,  id);
    if (QueryFullProcessImageName(ts,0,buffer,&value) == true) {
        nome_local = buffer;
        return nome_local;
    }
    return "";
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
