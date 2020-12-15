#include "module.h"

#include <iostream>

#ifdef _DEBUG
#define DEBUG_FLAG 1
#else
#define DEBUG_FLAG 0
#endif
#ifdef NDEBUG
#define NDEBUG_FLAG 1
#else
#define NDEBUG_FLAG 0
#endif

int f() {
  std::cout << "f: DEBUG_FLAG=" << DEBUG_FLAG << " NDEBUG_FLAG=" << NDEBUG_FLAG << std::endl;
  return 999;
}