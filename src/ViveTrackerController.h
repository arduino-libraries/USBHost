/*
 * ViveTrackerController.h
 *
 *  Created on: 05.04.2017
 *      Author: matzman
 */

#ifndef VIVETRACKERCONTROLLER_H_
#define VIVETRACKERCONTROLLER_H_

#include <hidboot.h>


/* Vive Tracker Button Bitmasks */
#define VIVETRACKER_BUTTON_TRIGGER       (1 << 0)
#define VIVETRACKER_BUTTON_GRIP          (1 << 1)
#define VIVETRACKER_BUTTON_MENU          (1 << 2)
#define VIVETRACKER_BUTTON_SYSTEM        (1 << 3)
#define VIVETRACKER_BUTTON_PADTRIGGERED  (1 << 4)
#define VIVETRACKER_BUTTON_PADTOUCHED    (1 << 5)


/*
 * The format of the USB HID feature reports is unfortunately not correct in HTC's documentation.
 * Fortunately Peter S. Hollander was able to find out the correct format of the feature reports,
 * and he was kind enough to share the details on his blog: 
 * http://www.talariavr.com/blog/vive-tracker-initial-documentation/
 */

/**
 * \struct Vive Tracker Feature Report 0xB3
 */
struct __attribute__((__packed__)) ViveTrackerFeatureReportB3 {
	uint8_t address = 0xB3;
	uint8_t payloadSize = 3;
	uint8_t hostType;
	uint8_t chargeEnable;
	uint8_t osType;
	ViveTrackerFeatureReportB3(uint8_t hostType = 3, uint8_t chargeEnable = 0, uint8_t osType = 0)
		: hostType(hostType), chargeEnable(chargeEnable), osType(osType) {}
};

/**
 * \struct Vive Tracker Feature Report 0xB4
 */
struct __attribute__((__packed__)) ViveTrackerFeatureReportB4 {
	uint8_t address = 0xB4;
	uint8_t payloadSize = 10;
	uint8_t tagIndex = 0;
	uint8_t buttons;
	int16_t padX;
	int16_t padY;
	uint16_t trigger;
	uint16_t batteryLevel;
	ViveTrackerFeatureReportB4(uint8_t buttons = 0, int16_t padX = 0, int16_t padY = 0, uint16_t trigger = 0, uint16_t batteryLevel = 0)
		: buttons(buttons), padX(padX), padY(padY), trigger(trigger), batteryLevel(batteryLevel) {}
} ;

/**
 * \class Customized HID Boot definition for Vive Tracker
 */
class ViveTrackerBoot : public HIDBoot<HID_PROTOCOL_NONE, HID_NONE_SUBCLASS> {
public:
	using HIDBoot<HID_PROTOCOL_NONE, HID_NONE_SUBCLASS>::HIDBoot;

	virtual uint32_t Init(uint32_t parent, uint32_t port, uint32_t lowspeed) override {
		auto retval = HIDBoot<HID_PROTOCOL_NONE, HID_NONE_SUBCLASS>::Init(parent, port, lowspeed);
		if (!retval) {
			_isConnected = true;
		}
		return retval;
	}

	virtual uint32_t Release() override {
		auto retval = HIDBoot<HID_PROTOCOL_NONE, HID_NONE_SUBCLASS>::Release();
		if (!retval) {
			_isConnected = false;
		}
		return retval;
	}

	virtual uint32_t Poll() override {
		return 0; // The Vive Controller does not send any data
	}

	bool isConnected() {
		return _isConnected;
	}

private:
	bool _isConnected = false;
};


/**
 * \class Vive Tracker Controller
 *
 * Represents the public API for the Vive Tracker
 */
class ViveTrackerController {
public:
	ViveTrackerController(USBHost &usb) : usb(usb), hostTracker(&usb) {}

	/**
	 * Returns whether a vive tracker is connected and initialized.
	 */
	bool isConnected() {
		return hostTracker.isConnected() && _isInitialized;
	}

	/**
	 * Sends the accessory state to the vive tracker.
	 *
	 * Regarding the trigger parameter: HTC's documentations states that a 16-bit value is used to represent the trigger.
	 * But the current firmware only uses an 8-bit value.
	 *
     * \param buttons Bitmask representing the pressed buttons.
     * \param padX X-axis of the trackpad (from -32768 to 32767)
     * \param padY Y-axis of the trackpad (from -32768 to 32767)
     * \param trigger Trigger state (from 0 to 255)
     * \param batteryLevel Currently not used, should be set to 0.
     * \param lowspeed USB device speed.
     *
     * \return 0 on success, error code otherwise.
	 */
	uint32_t setTrackerStatus(uint8_t buttons = 0, int16_t padX = 0, int16_t padY = 0, uint8_t trigger = 0, uint16_t batteryLevel = 0) {
		if (isConnected()) {
			ViveTrackerFeatureReportB4 report(buttons, padX, padY, trigger << 8, batteryLevel);
			return hostTracker.SetReport(0, 2, 3, 0, sizeof(ViveTrackerFeatureReportB4), (uint8_t*)&report);
		}
		return -1;
	}

	/**
	 * Process usb and vive tracker controller tasks.
	 *
	 * Should be repeatedly called in the main-loop.
	 */
	void Task() {
		usb.Task();
		if (hostTracker.isConnected() && !_isInitialized && _initConnection() == 0) {
			_isInitialized = true;
		} else if (!hostTracker.isConnected()) {
			_isInitialized = false;
		}
	}

private:
	USBHost &usb;
	ViveTrackerBoot hostTracker;
	bool _isInitialized = false;

	uint32_t _initConnection(uint8_t hostType = 3, uint8_t chargeEnable = 0, uint8_t osType = 0) {
		ViveTrackerFeatureReportB3 report(hostType, chargeEnable, osType);
		return hostTracker.SetReport(0, 2, 3, 0, sizeof(ViveTrackerFeatureReportB3), (uint8_t*)&report);
	}
};


#endif /* VIVETRACKERCONTROLLER_H_ */
