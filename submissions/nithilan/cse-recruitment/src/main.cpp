#include <Arduino.h>
#include <lwgps/lwgps.h>

#define ARDUINO_GPS_RX 0
#define ARDUINO_GPS_TX 1

// The GPS module L86 GNSS defaults to 9600 baud
#define GPS_BAUD_RATE 9600

// Use hardware UART on pins 0/1 for GPS.
#define gpsPort Serial1

static lwgps_t gps;

// This is the hardware serial port on pins 0/1.
#define SerialMonitor Serial

void setup()
{
    gpsPort.begin(GPS_BAUD_RATE);
    SerialMonitor.begin(9600);
    lwgps_init(&gps);
}

void loop()
{
    while (gpsPort.available())
    {
        char c = static_cast<char>(gpsPort.read());

        if (lwgps_process(&gps, &c, 1))
        {
            SerialMonitor.print("Latitude: ");
            SerialMonitor.print(gps.latitude, 6);
            SerialMonitor.println(" degrees");

            SerialMonitor.print("Longitude: ");
            SerialMonitor.print(gps.longitude, 6);
            SerialMonitor.println(" degrees");

            SerialMonitor.print("Altitude: ");
            SerialMonitor.print(gps.altitude, 2);
            SerialMonitor.println(" meters");
            SerialMonitor.println();
        }
    }
}