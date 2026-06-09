// wake_hid.h -- a minimal boot-protocol HID interface whose ONLY job is to make the device a host-recognized
// USB wake source.
//
// Every mode already advertises remote-wakeup in its config descriptor (the Adafruit core sets
// TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP), so the device is *armed* to wake the host. But hosts only *honor* a
// remote-wakeup resume signal from an allow-listed input device class -- a HID keyboard/mouse. Windows
// (especially under Modern Standby) ignores the wake from a bare gamepad / vendor / composite presentation
// even though it's armed. Exposing a boot keyboard interface puts the device in that allow-list. It never
// sends reports -- the actual wake is the device-level USBDevice.remoteWakeup() resume signal driven from
// rf_link.cpp; this interface only changes how the host classifies us.
//
// NOT used in puck (Steam) mode: that composite (CDC + 4 puck HID + WebUSB) already consumes all 7 of the
// nRF52840's data IN endpoints, leaving no room for another interface. (Puck mode already wakes on Linux/Deck;
// giving it a wake interface on Windows would require freeing an endpoint -- see ARCHITECTURE.md.)
#pragma once

void wakeHidBegin();   // register the boot-keyboard wake interface (call from setup() for clean modes)
