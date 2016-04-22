Digispark (ATtiny85) Sample code
====================================

Collection of projects for Digispark (ATtiny85), to be used for educational purpose.

- [Blink](https://github.com/nabilbendafi/Digispark/tree/master/blink)

Compilation
-----------

All samples have been successfully built on GNU C compiler (cross compiler for avr) [4.8.1+Atmel3.4.5-1] , under Linux

```shell
cd blink
make
```

Upload
------

After compilation, [micronucleus](https://github.com/Bluebie/micronucleus) to upload .hex to Digispark

```micronucleus project.hex```
