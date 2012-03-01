#include "cValve.h"

/// Creates a valve object without setting the pins and closed state (false). This is necessary for the rooms.
cValve::cValve(void)
{
  _iPinOpen=0;
  _iPinClose=0;
  _bState = false;
}

/// Creates a valve object with pin setting, the initial state is close.
/** Creates a valve object with pin setting. The Valve is initialized with a closed state. */
cValve::cValve(int iPinOpen, int iPinClose)
{
  cValve::setPinOpen(iPinOpen);
  cValve::setPinClose(iPinClose);
  
  _bState = false;
}

/// Creates a valve object with pin setting and an initial state.
cValve::cValve(int iPinOpen, int iPinClose, boolean bState)
{
  cValve::setPinOpen(iPinOpen);
  cValve::setPinClose(iPinClose);
  
  _bState = bState;
}

/// Sets the state of the Valve and executes the run function of the valve.
void cValve::set(boolean bState)
{
  _bState = bState;
  
  cValve::run();
}

/// Sets the _PinOpen. This is necessary for the rooms, where the constructor cannot initialize the pins.
void cValve::setPinOpen(int iPinOpen)
{
  _iPinOpen = iPinOpen;
  pinMode(_iPinOpen, OUTPUT);
  
  cValve::run();
}

/// Sets the _PinClose. This is necessary for the rooms, where the constructor cannot initialize the pins.
void cValve::setPinClose(int iPinClose)
{
  _iPinClose = iPinClose;
  pinMode(_iPinClose, OUTPUT);
  
  cValve::run();
}

/// Reads the state of the valve.
/** \return True = open, False = closed. */
boolean cValve::get(void)
{
  return _bState;
}

/// Executes the state of the valve (opens or closes it).
/** If the state of the valve is true, it shall be opened, if it is false, it is going to be closed*/
void cValve::run(void)
{
  if(_bState==true)
  {
    digitalWrite(_iPinOpen, LOW); // Valve gets openedPinValveWarmWaterOpen
  }
  else
  {
    digitalWrite(_iPinOpen, HIGH); // Valve gets closed
  }
}
