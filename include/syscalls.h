
#ifndef INCLUDE_SYSCALLS
#define INCLUDE_SYSCALLS

#ifndef INCLUDE_SYSCALLS
#define INCLUDE_SYSCALLS

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <multitasking.h>

namespace myos
{

class SyscallHandler : public hardwarecommunication::InterruptHandler
{

public:
  enum Syscall
  {
    PRINTF
  };

  SyscallHandler (hardwarecommunication::InterruptManager *interruptManager,
                  myos::common::uint8_t InterruptNumber);
  ~SyscallHandler ();

  virtual myos::common::uint32_t HandleInterrupt (myos::common::uint32_t esp);
};

void sysprintf (char *);

void printf (char *);

}

#endif /* INCLUDE_SYSCALLS */
