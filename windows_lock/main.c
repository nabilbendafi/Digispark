// main.c
// 
// A simple desktop locker program for ATtiny85 (Digispark clone)
// Led connected on PB1
//

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "oddebug.h"        /* This is also an example for using debug macros */

#include "usbdrv/usbdrv.h"

PROGMEM const char usbHidReporterDescriptor[63] =
{
	// keybrd.hid example from http://www.usb.org/developers/hidpage/dt2_4.zip
	0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
	0x09, 0x06,                    // USAGE (Keyboard)
	0xa1, 0x01,                    // COLLECTION (Application)
	0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
	0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
	0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
	0x75, 0x01,                    //   REPORT_SIZE (1)
	0x95, 0x08,                    //   REPORT_COUNT (8)
	0x81, 0x02,                    //   INPUT (Data,Var,Abs)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x81, 0x03,                    //   INPUT (Cnst,Var,Abs)
	0x95, 0x05,                    //   REPORT_COUNT (5)
	0x75, 0x01,                    //   REPORT_SIZE (1)
	0x05, 0x08,                    //   USAGE_PAGE (LEDs)
	0x19, 0x01,                    //   USAGE_MINIMUM (Num Lock)
	0x29, 0x05,                    //   USAGE_MAXIMUM (Kana)
	0x91, 0x02,                    //   OUTPUT (Data,Var,Abs)
	0x95, 0x01,                    //   REPORT_COUNT (1)
	0x75, 0x03,                    //   REPORT_SIZE (3)
	0x91, 0x03,                    //   OUTPUT (Cnst,Var,Abs)
	0x95, 0x06,                    //   REPORT_COUNT (6)
	0x75, 0x08,                    //   REPORT_SIZE (8)
	0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
	0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
	0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
	0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
	0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
	0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
	0xc0                           // END_COLLECTION
};

typedef struct {
	uint8_t modifier;
	uint8_t reserved;
	uint8_t keycode[6];
} keyboard_report_t;

static keyboard_report_t keyboard_report;
static uchar idleRate; // repeat rate for keyboards

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
	usbRequest_t *rq = (void *)data; /* cast to structured data for parsing */

	/* The following requests are never used. But since they are required by
	 * the specification, we implement them in this example.
	 */
	if ((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS) {	/* class request type */
		/* wValue: ReportType (highbyte), ReportID (lowbyte) */
		if(rq->bRequest == USBRQ_HID_GET_REPORT){
			/* we only have one report type, so don't look at wValue */
			usbMsgPtr = (void *)&keyboard_report;
			keyboard_report.modifier = 0;
			keyboard_report.keycode[0] = 0;
			return sizeof(keyboard_report);
		} else if(rq->bRequest == USBRQ_HID_GET_IDLE) {
			usbMsgPtr = &idleRate;
			return 1;
		} else if(rq->bRequest == USBRQ_HID_SET_IDLE) {
			idleRate = rq->wValue.bytes[1];
		}
	} else {
		/* no vendor specific requests implemented */
	}
	return 0; /* default for not implemented requests: return no data back to host */
}

int main (void)
{
	uchar i = 0;

	wdt_enable(WDTO_1S); /* enable 1s watchdog */

	usbInit(); /* enable USB stack */

	usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */

	while (--i) {             /* fake USB disconnect for > 250 ms */
		wdt_reset();
		_delay_ms(1);
	}

	usbDeviceConnect();    

	// Enable interrupts
	sei();

	// set PB1 to be output
	DDRB |= (1 << PB1);

	while (1) {

		wdt_reset();

		// press keys Win+l
		keyboard_report.modifier = 0xE3; // modifier keys - "Windows" key
		keyboard_report.reserved = 0x00; // reserved
		keyboard_report.keycode[0] = 0x0F; // keycode for 'l' letter
		keyboard_report.keycode[1] = 0x00;
		keyboard_report.keycode[2] = 0x00;
		keyboard_report.keycode[3] = 0x00;
		keyboard_report.keycode[4] = 0x00;
		keyboard_report.keycode[5] = 0x00;

		// send keyboard report
		if (usbInterruptIsReady())
			usbSetInterrupt((void *)&keyboard_report, sizeof(keyboard_report));
		usbPoll();

		_delay_ms(250);
	}
 
	return 1; // Never reach under normal execution
}
