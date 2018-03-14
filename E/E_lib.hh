#pragma once

static void setup();

#ifdef __linux__

// This class is a solution to avoid 2 libraries to define an entrypoint with
// the same symbol name.
// When loading a library with dependencies, if the loaded library and its
// dependencies has entrypoint with identical symbol then the entrypoint of the
// loaded library will override the ones of its dependencies
//
// So the solution consist of the use of the mangling.
// To make this work you need to EXPLICITELY instantiate this template with
// anything you want, preferably with the class that library instatiate
template <typename ...>
struct EntryPointWrapper
{
  __attribute__((constructor))
  static void entrypoint()
  {
    setup();
  }
};

#elif _WIN32
#include <Windows.h>

// Empty because windows has its own entrypoint function for dll
// This is here to avoid compilation error (compatibility with Linux)
template <typename ...>
struct EntryPointWrapper {};

BOOL WINAPI DllMain(IN HINSTANCE handle, IN DWORD reason, IN LPVOID reserved)
{
  switch (reason)
  {
  case DLL_PROCESS_ATTACH:
    setup();
    break;
  case DLL_PROCESS_DETACH:
  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
  default:
    break;
  }
  return TRUE;
}
#endif
