/*
 * Vive Tracker Example
 *
 * Shows how to send button
 */

// Require vive tracker controller library
#include <ViveTrackerController.h>

// Initialize USB Host Controller
USBHost usb;

// Attach vive tracker controller to USB
ViveTrackerController tracker(usb);


void setup() {
	Serial.begin(115200);
	Serial.println("Program started");
	delay(200);
}


void loop() {
	tracker.Task(); // Process usb and vive tracker controller tasks
	if (tracker.isConnected()) {
		// Send accessory state to vive tracker.
		uint8_t buttons = VIVETRACKER_BUTTON_GRIP | VIVETRACKER_BUTTON_MENU;
		int16_t padX = 1234;
		int16_t padY = -333;
		uint8_t trigger = 200;
		uint16_t batteryLevel = 0;
		tracker.setTrackerStatus(buttons, padX, padY, trigger, batteryLevel);
	}
	delay(300);
}
