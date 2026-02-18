//
// Created by KoTz on 18/02/2026.
//

#include "ProcMon.h"

#include <iostream>
#include <ostream>




ProcMon::ProcMon() {
    Snapshot();
    ProcessEnrty();
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


Sy ProcMon::Process() {

    std::vector<ProcessList> processes;

    if (!Process32First(Handle, &pEntry)) {
        CloseHandle(Handle);
        return Sy{};
    }
    do {
         processes.push_back(ProcessList{
             pEntry.th32ProcessID,
             pEntry.szExeFile,
             pEntry.cntThreads});
    }while (Process32Next(Handle, &pEntry));

    return processes;
}


void ProcMon::updateProcess() {
    std::vector<ProcessList> processes;
    while (Process32First(Handle, &pEntry)) {
        Snapshot ();
        ProcessEnrty();
        do {
            processes.push_back(ProcessList{
           pEntry.th32ProcessID,
           pEntry.szExeFile,
           pEntry.cntThreads});

            for (auto process : processes) {
                std::cout << process.name << std::endl;
            }

        }while (Process32Next(Handle, &pEntry));

        processes.clear();
    }
}