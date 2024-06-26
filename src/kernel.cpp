
#include <common/types.h>
#include <drivers/ata.h>
#include <drivers/driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <gdt.h>
#include <hardwarecommunication/interrupts.h>
#include <memorymanagement.h>
#include <multitasking.h>
#include <syscalls.h>

// #define GRAPHICSMODE

using namespace myos;
using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;

void
printfHex (uint8_t key)
{
  char *foo = "00";
  char *hex = "0123456789ABCDEF";
  foo[0] = hex[(key >> 4) & 0xF];
  foo[1] = hex[key & 0xF];
  printf (foo);
  char *foo = "00";
  char *hex = "0123456789ABCDEF";
  foo[0] = hex[(key >> 4) & 0xF];
  foo[1] = hex[key & 0xF];
  printf (foo);
}

void
printfHex16 (uint16_t key)

void
printfHex16 (uint16_t key)
{
  printfHex ((key >> 8) & 0xFF);
  printfHex (key & 0xFF);
  printfHex ((key >> 8) & 0xFF);
  printfHex (key & 0xFF);
}

void
printfHex32 (uint32_t key)

void
printfHex32 (uint32_t key)
{
  printfHex ((key >> 24) & 0xFF);
  printfHex ((key >> 16) & 0xFF);
  printfHex ((key >> 8) & 0xFF);
  printfHex (key & 0xFF);
  printfHex ((key >> 24) & 0xFF);
  printfHex ((key >> 16) & 0xFF);
  printfHex ((key >> 8) & 0xFF);
  printfHex (key & 0xFF);
}

class PrintfKeyboardEventHandler : public KeyboardEventHandler
{
public:
  void
  OnKeyDown (char c)
  {
    char *foo = " ";
    foo[0] = c;
    printf (foo);
  }
  void
  OnKeyDown (char c)
  {
    char *foo = " ";
    foo[0] = c;
    printf (foo);
  }
};

class MouseToConsole : public MouseEventHandler
{
  int8_t x, y;

  int8_t x, y;

public:
  MouseToConsole ()
  {
    uint16_t *VideoMemory = (uint16_t *)0xb8000;
    x = 40;
    y = 12;
    VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0x0F00) << 4
                              | (VideoMemory[80 * y + x] & 0xF000) >> 4
                              | (VideoMemory[80 * y + x] & 0x00FF);
  }

  virtual void
  OnMouseMove (int xoffset, int yoffset)
  {
    static uint16_t *VideoMemory = (uint16_t *)0xb8000;
    VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0x0F00) << 4
                              | (VideoMemory[80 * y + x] & 0xF000) >> 4
                              | (VideoMemory[80 * y + x] & 0x00FF);
  MouseToConsole ()
  {
    uint16_t *VideoMemory = (uint16_t *)0xb8000;
    x = 40;
    y = 12;
    VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0x0F00) << 4
                              | (VideoMemory[80 * y + x] & 0xF000) >> 4
                              | (VideoMemory[80 * y + x] & 0x00FF);
  }

  virtual void
  OnMouseMove (int xoffset, int yoffset)
  {
    static uint16_t *VideoMemory = (uint16_t *)0xb8000;
    VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0x0F00) << 4
                              | (VideoMemory[80 * y + x] & 0xF000) >> 4
                              | (VideoMemory[80 * y + x] & 0x00FF);

    x += xoffset;
    if (x >= 80)
      x = 79;
    if (x < 0)
      x = 0;
    y += yoffset;
    if (y >= 25)
      y = 24;
    if (y < 0)
      y = 0;

    VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0x0F00) << 4
                              | (VideoMemory[80 * y + x] & 0xF000) >> 4
                              | (VideoMemory[80 * y + x] & 0x00FF);
  }
};

void
taskA ()
{
  while (true)
    sysprintf ("A");
}

void
taskB ()
void
taskB ()
{
  while (true)
    sysprintf ("B");
  while (true)
    sysprintf ("B");
}

typedef void (*constructor) ();
typedef void (*constructor) ();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void
callConstructors ()

extern "C" void
callConstructors ()
{
  for (constructor *i = &start_ctors; i != &end_ctors; i++)
    (*i) ();
  for (constructor *i = &start_ctors; i != &end_ctors; i++)
    (*i) ();
}

extern "C" void
kernelMain (const void *multiboot_structure, uint32_t /*multiboot_magic*/)
extern "C" void
kernelMain (const void *multiboot_structure, uint32_t /*multiboot_magic*/)
{
  printf ("Hello World! - Emirhan Altunel2 \n");

  GlobalDescriptorTable gdt;

  uint32_t *memupper = (uint32_t *)(((size_t)multiboot_structure) + 8);
  size_t heap = 10 * 1024 * 1024;
  MemoryManager memoryManager (heap, (*memupper) * 1024 - heap - 10 * 1024);

  printf ("heap: 0x");
  printfHex ((heap >> 24) & 0xFF);
  printfHex ((heap >> 16) & 0xFF);
  printfHex ((heap >> 8) & 0xFF);
  printfHex ((heap) & 0xFF);

  void *allocated = memoryManager.malloc (1024);
  printf ("\nallocated: 0x");
  printfHex (((size_t)allocated >> 24) & 0xFF);
  printfHex (((size_t)allocated >> 16) & 0xFF);
  printfHex (((size_t)allocated >> 8) & 0xFF);
  printfHex (((size_t)allocated) & 0xFF);
  printf ("\n");

  TaskManager taskManager;

  Task task1 (&gdt, taskA);
  Task task2 (&gdt, taskB);
  taskManager.AddTask (&task1);
  taskManager.AddTask (&task2);

  InterruptManager interrupts (0x20, &gdt, &taskManager);
  SyscallHandler syscalls (&interrupts, 0x80);

  printf ("Initializing Hardware, Stage 1\n");

  DriverManager drvManager;

  PrintfKeyboardEventHandler kbhandler;
  KeyboardDriver keyboard (&interrupts, &kbhandler);

  drvManager.AddDriver (&keyboard);

  MouseToConsole mousehandler;
  MouseDriver mouse (&interrupts, &mousehandler);

  drvManager.AddDriver (&mouse);

  printf ("Initializing Hardware, Stage 2\n");
  drvManager.ActivateAll ();

  printf ("Initializing Hardware, Stage 3\n");

  interrupts.Activate ();

  printf ("\n\n\n\n");

  while (1)
    ;
}
