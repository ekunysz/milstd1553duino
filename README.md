# MIL-STD-1553 Logical Layer Implementation

This project provides a Arduino lightweight software implementation of the MIL-STD-1553 data bus protocol, focusing only on the logical layer. It abstracts the physical transport layer, allowing communication over interfaces such as I²C or UART, making it adaptable to different embedded platforms.

Current tested with:
BC: Arduino Uno
RT: Arduino Nano

The implementation includes two main roles:
-------------------------------------------

Bus Controller (BC) – responsible for sending commands and managing communication.

Remote Terminal (RT) – responds to commands and provides data exchange.

Features
--------

Abstraction of the transport layer (easily switch between I²C, UART, or others).

Core MIL-STD-1553 command structure (e.g., Transmit/Receive Data).

Lightweight design suitable for resource-constrained devices such as Arduino boards.

Modular library organization:

BC/ – Bus Controller logic.

RT/ – Remote Terminal logic.

transport/ – configurable transport drivers.

Status
------

This is a simplified, non-physical implementation of MIL-STD-1553, intended to experiment with its command/response logic and validate protocol handling without specialized hardware.

Changelog
---------
| Date | Version | Description                                                     |
|250824|   0.0.1 | Functional version, only implement "Command Word (CW) BC to RT" |
