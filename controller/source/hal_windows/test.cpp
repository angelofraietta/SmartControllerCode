#include <stdio.h>


extern "C" bool __export SimulatorInitialise();

extern "C" void __export RestoreNVRAM();

int main()
{
  SimulatorInitialise();
  RestoreNVRAM();

  return 0;
}
