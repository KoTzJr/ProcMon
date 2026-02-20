#include <iostream>
#include "ProcMon.h"
int main() {

    ProcMon teste;

        Sy get;
        teste.Process(get);
        for (auto & i : get) {
            std::cout << "PID: "     << i.pid  << "\t"
                 << "Threads: " << i.numThreads  << "\t"
                 << "Nome: "    << i.name << "\n";
        }

    return 0;
}