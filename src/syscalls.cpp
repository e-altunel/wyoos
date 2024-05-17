#include <syscalls.h>


using namespace myos;
using namespace myos::common;
using namespace myos::hardwarecommunication;

SyscallHandler::SyscallHandler (InterruptManager *interruptManager,
                                uint8_t InterruptNumber)
    : InterruptHandler (interruptManager,
                        InterruptNumber
                            + interruptManager->HardwareInterruptOffset ())

SyscallHandler::SyscallHandler (InterruptManager *interruptManager,
                                uint8_t InterruptNumber)
    : InterruptHandler (interruptManager,
                        InterruptNumber
                            + interruptManager->HardwareInterruptOffset ())
{
}

SyscallHandler::~SyscallHandler () {}

uint32_t
SyscallHandler::HandleInterrupt (uint32_t esp)
{
  CPUState *cpu = (CPUState *)esp;

  switch (cpu->eax)
  {
  case PRINTF:
    printf ((char *)cpu->ebx);
    break;

  default:
    break;
  }

  return esp;
}

void
myos::sysprintf (char *str)
{
  asm ("int $0x80" : : "a"(SyscallHandler::PRINTF), "b"(str));
}

void
myos::printf (char *str)
{
  static uint16_t *VideoMemory = (uint16_t *)0xb8000;

  static uint8_t x = 0, y = 0;

  for (int i = 0; str[i] != '\0'; ++i)
  {
    switch (str[i])
    {
    case '\n':
      x = 0;
      y++;
      break;
    default:
      VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | str[i];
      x++;
      break;
    }

    if (x >= 80)
    {
      x = 0;
      y++;
    }

    if (y >= 25)
    {
      for (y = 0; y < 25; y++)
        for (x = 0; x < 80; x++)
          VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | ' ';
      x = 0;
      y = 0;
    }
  }
}
