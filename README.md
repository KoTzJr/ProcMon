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
```
O Resultado da Saida
```cpp
PID: 21736      Threads: 2      Nome: ApplicationFrameHost.exe
PID: 21744      Threads: 42     Nome: SystemSettings.exe
PID: 22432      Threads: 3      Nome: WmiApSrv.exe
PID: 5704       Threads: 9      Nome: msedge.exe
PID: 8296       Threads: 1      Nome: RuntimeBroker.exe
PID: 22780      Threads: 9      Nome: steamwebhelper.exe
PID: 2028       Threads: 107    Nome: firefox.exe
PID: 20088      Threads: 2      Nome: crashhelper.exe
```

## Requisitos
- C++20
- MSVC and MIGW



