#include "Particle.h"
#include "BeaconScanner.h"

SYSTEM_MODE(AUTOMATIC);

SerialLogHandler logHandler(LOG_LEVEL_INFO);

void setup()
{
}

void loop()
{
  static unsigned long scannedTime = 0;
  if (Particle.connected() && (millis() - scannedTime) > 1000)
  {
    Log.info("Scanning...");
    scannedTime = millis();

    Scanner.scan(1, SCAN_BTHOME || SCAN_THERMOPRO);

    Vector<BTHome> BTbeacons = Scanner.getBTHome();
    while (!BTbeacons.isEmpty())
    {
      BTHome beacon = BTbeacons.takeFirst();
      Log.info("BTHome Address: %s, Battery: %d, Button: %d, Window: %d, Rotation: %d", beacon.getAddress().toString().c_str(), beacon.getBatteryLevel(), beacon.getButtonEvent(), beacon.getWindowState(), beacon.getRotation());
    }

    Vector<ThermoPro> TPbeacons = Scanner.getThermoPro();
    while (!TPbeacons.isEmpty())
    {
      ThermoPro beacon = TPbeacons.takeFirst();
      Log.info("ThermoPro Address: %s, Temperature: %.1f C / %.1f F, Humidity: %u%%", beacon.getAddress().toString().c_str(), beacon.getTemperatureC(), beacon.getTemperatureF(), beacon.getHumidity());
    }
  }
}
