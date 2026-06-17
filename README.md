[![Arduino CI](https://img.shields.io/static/v1?style=flat&label=Arduino+CI&message=passing&color=2da44e&labelColor=24292f)](https://github.com/ripred/fANSI/actions/workflows/arduino_test_runner.yml)
[![Arduino-lint](https://img.shields.io/static/v1?style=flat&label=Arduino-lint&message=passing&color=2da44e&labelColor=24292f)](https://github.com/ripred/fANSI/actions/workflows/arduino-lint.yml)
[![JSON check](https://img.shields.io/static/v1?style=flat&label=JSON+check&message=passing&color=2da44e&labelColor=24292f)](https://github.com/ripred/fANSI/actions/workflows/jsoncheck.yml)
[![Arduino Library Manager](https://img.shields.io/static/v1?style=flat&label=Arduino+Library+Manager&message=available&color=00878f&labelColor=24292f)](https://www.ardu-badge.com/fANSI)
[![Release](https://img.shields.io/static/v1?style=flat&label=Release&message=fANSI-v1.1&color=8250df&labelColor=24292f)](https://github.com/ripred/fANSI/releases/latest)
[![License](https://img.shields.io/static/v1?style=flat&label=License&message=MIT&color=0969da&labelColor=24292f)](https://github.com/ripred/fANSI/blob/main/LICENSE)
[![Stars](https://img.shields.io/static/v1?style=flat&label=Stars&message=5&color=bf8700&labelColor=24292f)](https://github.com/ripred/fANSI/stargazers)
[![Forks](https://img.shields.io/static/v1?style=flat&label=Forks&message=0&color=6f42c1&labelColor=24292f)](https://github.com/ripred/fANSI/network/members)

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
