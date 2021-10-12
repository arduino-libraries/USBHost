# USBHost Library

*Compatible with Arduino Due only*

The USBHost library allows an Arduino Due board to appear as a USB host, enabling it to communicate with peripherals like USB mice and keyboards. USBHost does not support devices that are connected through USB hubs. This includes some keyboards that have an internal hub.

**NB:** The USBHost library and associated functions are experimental. While it is not likely the API will change in future releases, it is still under development.

**NB:** The USBHost library is distributed under the General Public License version 2 (GPL2) as published by the Free Software Foundation. Any sketch that uses the library needs to be open-sourced under the GPL2 as well.

## USBHost Class

USBHost is the base class for all calls that rely on USB host communication. When invoked, it initializes a USB controller. To declare it, use:

```
USBHost usb;
```
