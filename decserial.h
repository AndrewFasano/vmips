/* Headers for DZ11-based DEC 5000/200 serial chip emulation.
   Copyright 2003 Brian R. Gaeke.

This file is part of VMIPS.

VMIPS is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

VMIPS is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with VMIPS; if not, write to the Free Software Foundation, Inc.,
59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#ifndef _DECSERIAL_H_
#define _DECSERIAL_H_

class Clock;
#include "devicemap.h"
#include "terminalcontroller.h"
#include "decserialreg.h"

class DECSerialDevice : public DeviceMap, public DeviceInt,
                        public TerminalController {
  static const int KEYBOARD_POLL_NS = 100;
  static const int KEYBOARD_REPOLL_NS = 100;
  static const int DISPLAY_READY_DELAY_NS = 100;
  void master_clear ();
  uint32 csr, rbuf, lpr, tcr, msr;
  bool keyboard_interrupt_enable;
  bool display_interrupt_enable;
 public:
  DECSerialDevice (Clock *clock) throw ();
  virtual ~DECSerialDevice() throw ();
  uint32 fetch_word (uint32 offset, int mode, DeviceExc *client);
  void store_word (uint32 offset, uint32 data, DeviceExc *client);
  const char *descriptor_str () const { return "DECstation 5000/200 DZ11 Serial"; }

  /* Call the routines in TerminalController and then assert or
     deassert the appropriate interrupt. */
  virtual void ready_display (int line) throw();
  virtual void unready_display (int line, char data)
      throw (std::bad_alloc);
  virtual void unready_keyboard (int line) throw();
protected:
  virtual void ready_keyboard (int line) throw();
};

#endif /* _DECSERIAL_H_ */
