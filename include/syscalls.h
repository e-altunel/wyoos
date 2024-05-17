
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
  SyscallHandler (hardwarecommunication::InterruptManager *interruptManager,
                  myos::common::uint8_t InterruptNumber);
  ~SyscallHandler ();

  virtual myos::common::uint32_t HandleInterrupt (myos::common::uint32_t esp);
};

}

#endif /* INCLUDE_SYSCALLS */
