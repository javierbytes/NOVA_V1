#include "sensors.h"

// Objetos globales
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_BME280 bme;
Adafruit_ADS1115 ads;
RTC_DS3231 rtc;
MPU9250_WE mpu = MPU9250_WE(ADDR_MPU);
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

// ---------------------------------------------------
// Escaneo I2C
// ---------------------------------------------------
bool scanI2CDevices()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println(F("Escaneo I2C..."));
    display.display();

    byte error, address;
    int nDevices = 0;

    for (address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0)
        {
            display.printf("I2C: 0x%02X\n", address);
            nDevices++;
        }
    }

    if (nDevices == 0)
    {
        display.println(F("No se encontraron dispositivos"));
    }

    display.display();
    delay(1500);

    return nDevices > 0;
}

// ---------------------------------------------------
// Inicialización de sensores
// ---------------------------------------------------
bool initSensors()
{
    bool ok = true;
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println(F("Init Sensores..."));

    // BME280
    if (!bme.begin(ADDR_BME280))
    {
        display.println(F("BME280 FAIL"));
        ok = false;
    }
    else
        display.println(F("BME280 OK"));

    // ADS1115
    if (!ads.begin())
    {
        display.println(F("ADS1115 FAIL"));
        ok = false;
    }
    else
        display.println(F("ADS1115 OK"));

    // RTC
    if (!rtc.begin())
    {
        display.println(F("RTC FAIL"));
        ok = false;
    }
    else
        display.println(F("RTC OK"));

    // MPU9250
    if (!mpu.init())
    {
        display.println(F("MPU9250 FAIL"));
        ok = false;
    }
    else
        display.println(F("MPU9250 OK"));

    // Magnetómetro HMC5883
    if (!mag.begin())
    {
        display.println(F("HMC5883 FAIL"));
        ok = false;
    }
    else
        display.println(F("HMC5883 OK"));

    display.display();
    delay(1500);

    return ok;
}

// ---------------------------------------------------
// Verificar estado del RTC
// ---------------------------------------------------
bool checkRTC()
{
    if (rtc.lostPower())
    {
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println(F("RTC sin hora"));
        display.println(F("Ajustar manualmente"));
        display.display();
        return false;
    }
    return true;
}
