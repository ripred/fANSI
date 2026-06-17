[![Arduino CI](https://flat.badgen.net/badge/Arduino%20CI/passing/2da44e?labelColor=24292f)](https://github.com/ripred/fANSI/actions/workflows/arduino_test_runner.yml)
[![Arduino-lint](https://flat.badgen.net/badge/Arduino-lint/passing/2da44e?labelColor=24292f)](https://github.com/ripred/fANSI/actions/workflows/arduino-lint.yml)
[![JSON check](https://flat.badgen.net/badge/JSON%20check/passing/2da44e?labelColor=24292f)](https://github.com/ripred/fANSI/actions/workflows/jsoncheck.yml)
[![Arduino Library Manager](https://flat.badgen.net/badge/Arduino%20Library%20Manager/available/00878f?labelColor=24292f)](https://www.ardu-badge.com/fANSI)
[![Release](https://flat.badgen.net/badge/Release/fANSI-v1.1/8250df?labelColor=24292f)](https://github.com/ripred/fANSI/releases/latest)
[![License](https://flat.badgen.net/badge/License/MIT/0969da?labelColor=24292f)](https://github.com/ripred/fANSI/blob/main/LICENSE)
[![Stars](https://flat.badgen.net/badge/Stars/5/bf8700?labelColor=24292f)](https://github.com/ripred/fANSI/stargazers)
[![Forks](https://flat.badgen.net/badge/Forks/0/6f42c1?labelColor=24292f)](https://github.com/ripred/fANSI/network/members)

fANSI Library

This library allows you to send ANSI control sequences to a PC, Mac, or Linux
machine simply by sending to the Arduino Serial port.

You can view the output in any terminal or console window on any operating system
that supports ANSI escape sequences.

Includes support for 4-bit, 6-bit, and full 24-bit color support in common
terminal window output from any microcontroller that can output serial data
at 9600 N81. Which is pretty much every one.

Includes support for cursor on/off, cursor positioning, erasing to end-of-display
or to end-of-line, alternate screen buffers, borders, and more!

To display the output from the Arduino or other MCU just copy from the COM port or device to your console output:

```
ripred$ ls /dev/cu.usb*
/dev/cu.usbserial-0001
ripred$
ripred$
ripred$ cat /dev/cu.usbserial-0001 
```
![ANSIexample.png](ANSIexample.png)
