/*
SoftSerialTx.h (based on SoftwareSerial) -
Multi-instance software serial library for Arduino/Wiring
-- Conversion to transmit-only to avoid pin interrupt conflicts,
   Michael Shimniok (www.bot-thoughts.com)
-- Interrupt-driven receive and other improvements by ladyada
   (http://ladyada.net)
-- Tuning, circular buffer, derivation from class Print/Stream,
   multi-instance support, porting to 8MHz processors,
   various optimizations, PROGMEM delay tables, inverse logic and
   direct port writing by Mikal Hart (http://www.arduiniana.org)
-- Pin change interrupt macros by Paul Stoffregen (http://www.pjrc.com)
-- 20MHz processor support by Garrett Mace (http://www.macetech.com)
-- ATmega1280/2560 support by Brett Hagman (http://www.roguerobotics.com/)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

The latest version of this library can always be found at http://github.com/shimniok.
*/

#ifndef SoftSerialTx_h
#define SoftSerialTx_h

#include <inttypes.h>
#include <Stream.h>

/******************************************************************************
* Definitions
******************************************************************************/

#ifndef GCC_VERSION
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

class SoftSerialTx : public Stream
{
private:
  // per object data
  uint8_t _transmitBitMask;
  volatile uint8_t *_transmitPortRegister;

  // Expressed as 4-cycle delays (must never be 0!)
  uint16_t _tx_delay;

  uint16_t _buffer_overflow:1;
  uint16_t _inverse_logic:1;

  // static data
  static SoftSerialTx *active_object;

  // private methods
  void setTX(uint8_t transmitPin);

  // Return num - sub, or 1 if the result would be < 1
  static uint16_t subtract_cap(uint16_t num, uint16_t sub);

  // private static method for timing
  static inline void tunedDelay(uint16_t delay);

public:
  // public methods
  SoftSerialTx(uint8_t transmitPin, bool inverse_logic = false);
  ~SoftSerialTx();
  void begin(long speed);
  void end() { return; };
  bool overflow() { bool ret = _buffer_overflow; if (ret) _buffer_overflow = false; return ret; }
  int peek() { return EOF; };

  virtual size_t write(uint8_t byte);
  virtual int read() { return EOF; };
  virtual int available() { return 0; };
  virtual void flush();
  operator bool() { return true; }

  using Print::write;
};

// Arduino 0012 workaround
#undef int
#undef char
#undef long
#undef byte
#undef float
#undef abs
#undef round

#endif
