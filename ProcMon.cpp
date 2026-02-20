//
// Created by KoTz on 18/02/2026.
//

#include "ProcMon.h"
#include <iostream>

ProcMon::ProcMon() {
    Handle = INVALID_HANDLE_VALUE;
    ProcessEnrty();
}

ProcMon::~ProcMon() {
    if (Handle != INVALID_HANDLE_VALUE) {
        CloseHandle(Handle);
    }
}

void ProcMon::Snapshot() {
    HANDLE get = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (get == INVALID_HANDLE_VALUE) {
         return;
    }
    Handle = get;
}

void ProcMon::ProcessEnrty() {
    pEntry.dwSize = sizeof(PROCESSENTRY32);
}


void ProcMon::Process(Sy & i) {

    Sy processes;

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
                pEntry.cntThreads});
              i = processes;
        }while (Process32Next(Handle, &pEntry));
}


void ProcMon::KillProcess(_VALUE_ id) {
  auto get = OpenProcess(PROCESS_TERMINATE, FALSE, id);
    if (get == NULL) {
        std::cout << GetLastError() << std::endl;
        return;
    }
    TerminateProcess(get,false);
    CloseHandle(get);
}

bool ProcMon::SearchName(std::string ExeAppName,std::string copy) {
    if (ExeAppName.empty() == false  && copy.empty() == false) {
        return ExeAppName.find(copy) != std::string::npos;
    }
    return false;
}

bool ProcMon::Search(NAME_Exe E, PID ID, Thread T) {
    if (E.AppName.empty() == false
        && E.Name.empty() == false) {
        return E.AppName.find(E.Name) !=
            std::string::npos && ID.pid == ID.id && T.thread == T.ThreadID;
    }
    return false;
}

PROCESSENTRY32 ProcMon::GetEntry() {
    return pEntry;
}

bool ProcMon::SearchID(DWORD id,ProcessList list) {
    return list.pid == id;
}
