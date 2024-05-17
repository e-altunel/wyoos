
#ifndef INCLUDE_DRIVERS_DRIVER
#define INCLUDE_DRIVERS_DRIVER

namespace myos
{
namespace drivers
{

class Driver
{
public:
  Driver ();
  ~Driver ();

  virtual void Activate ();
  virtual int Reset ();
  virtual void Deactivate ();
};

class DriverManager
{
public:
  Driver *drivers[265];
  int numDrivers;

public:
  DriverManager ();
  void AddDriver (Driver *);

  void ActivateAll ();
};

}
}

#endif /* INCLUDE_DRIVERS_DRIVER */
