#include "wake_hid.h"
#include <Adafruit_TinyUSB.h>

// A bog-standard boot keyboard descriptor. We never send a report on it; it exists purely so the host
// enumerates a "HID-compliant keyboard" child and grants the device wake-from-sleep privileges.
static const uint8_t WAKE_HID_DESC[] = { TUD_HID_REPORT_DESC_KEYBOARD() };
static Adafruit_USBD_HID g_wakeHid;

void wakeHidBegin(){
  g_wakeHid.setBootProtocol(HID_ITF_PROTOCOL_KEYBOARD);   // boot keyboard = the canonical wake device class
  g_wakeHid.setStringDescriptor("OpenPuck Wake");
  g_wakeHid.setReportDescriptor(WAKE_HID_DESC, sizeof WAKE_HID_DESC);
  g_wakeHid.setPollInterval(10);
  g_wakeHid.begin();
}
