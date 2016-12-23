# SoftSerialTX
Software Serial, transmit-only, e.g., for serial displays

Sometimes, you just want to transmit serial data, and you don't need to receive. Like with a serial LCD.

This is basically SoftwareSerial but without the receive stuff. So no pin interrupts to potentially conflict
with other libraries and (maybe) take up extra space.

Should be a drop in replacement for SoftwareSerial
