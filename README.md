<p align="center">
  <img src="img/ProcMon.png" alt="ProcMon" width="1000">
</p>


<h1> Oque é ProcMon ?</h1>

É uma biblioteca para monitorar o sistema na execução de programas no sistema operacional.

<h2> Como usar ? </h2>


```cpp
#include <iostream>
#include "ProcMon.h"
int main() {
 ProcMon process {};
  for (auto & i : process.Process()) {
        std::cout << "PID: "     << i.pid  << "\t"
                  << "Threads: " << i.numThreads  << "\t"
                  << "Nome: "    << i.name << "\n";
  }
    return 0;
}
 
