#include <Arduino.h>
#include <Wire.h>
#include "sensors.h"

// put function declarations here:

void setup()
{
  Wire.begin();
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, ADDR_OLED))
  {
    Serial.println(F("Error inicializando OLED"));
    for (;;)
      ;
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("Inicio..."));
  display.display();

  // Escaneo I2C
  scanI2CDevices();

  // Inicializar sensores
  initSensors();

  // Verificar RTC
  checkRTC(); // put your setup code here, to run once:
}

void loop()
{
}

// put function definitions here:
