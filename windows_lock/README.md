Digispark (ATtiny85) "Windows Lock" demo
=======================================

Libraries
---------

This minimal example uses [V-USB](http://www.obdev.at/vusb/) firmware-only USB driver.

Pinouts
-------

|Function|ATtiny pin|
|--------|----------|
|  LED   |  7 (PB1) |
| USB D+ |  3 (PB4) |
| USB D- |  2 (PB3) |

[Digispark schematic](https://s3.amazonaws.com/digispark/DigisparkSchematicFinal.pdf)

![ATtiny85 pinout](https://github.com/nabilbendafi/Digispark/blob/master/attiny85.png)
(Source: [Atmel ATtiny85 datasheet](http://www.atmel.com/images/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf))

Code explanation
---------------
In usbconfig.h define USB D+ and USB D- connections
```
#define USB_CFG_IOPORTNAME      B
#define USB_CFG_DMINUS_BIT      3
#define USB_CFG_DPLUS_BIT       4
```

Our device will be seen as a keyboard
|  Product ID  |  Vendor ID  | Description
|--------------|-------------|------------------
|10203 (0x27db)|5824 (0x16c0)| For USB Keyboards
```
#define  USB_CFG_VENDOR_ID       0xc0, 0x16
#define  USB_CFG_DEVICE_ID       0xdb, 0x27
```

[USB HID Key codes](http://www.usb.org/developers/hidpage/Hut1_12v2.pdf)

Compilation
-----------

GNU C compiler (cross compiler for avr) [4.8.1+Atmel3.4.5-1]

```
cd windows_lock
make
```

References
----------
* http://codeandlife.com/2012/06/18/usb-hid-keyboard-with-v-usb
