
#ifndef INCLUDE_MEMORYMANAGEMENT
#define INCLUDE_MEMORYMANAGEMENT

#include <common/types.h>

namespace myos
{

struct MemoryChunk
{
  MemoryChunk *next;
  MemoryChunk *prev;
  bool allocated;
  common::size_t size;
};

class MemoryManager
{

protected:
  MemoryChunk *first;

public:
  static MemoryManager *activeMemoryManager;

  MemoryManager (common::size_t first, common::size_t size);
  ~MemoryManager ();

  void *malloc (common::size_t size);
  void free (void *ptr);
};
}

#ifdef __INTELLISENSE__
#  pragma diag_suppress 351
#endif

void *operator new (unsigned size);
void *operator new[] (unsigned size);

// placement new
void *operator new (unsigned size, void *ptr);
void *operator new[] (unsigned size, void *ptr);

#ifdef __INTELLISENSE__
#  pragma diag_default 351
#endif

void operator delete (void *ptr);
void operator delete[] (void *ptr);

#endif /* INCLUDE_MEMORYMANAGEMENT */