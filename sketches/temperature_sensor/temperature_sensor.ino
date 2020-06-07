
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#define SUN 0
#define SUN_CLOUD  1
#define CLOUD 2
#define RAIN 3
#define THUNDER 4

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

uint8_t temperature = 10;
long pressure = 0;
long altitude = 0;

void getSensorMeasurements() {
  //TODO get some measurement values from the sensor
}

void drawWeatherSymbol(u8g2_uint_t x, u8g2_uint_t y, uint8_t symbol) {
  switch(symbol) {
    case SUN:
      u8g2.setFont(u8g2_font_open_iconic_weather_6x_t);
      u8g2.drawGlyph(x, y, 69); 
      break;
    case SUN_CLOUD:
      u8g2.setFont(u8g2_font_open_iconic_weather_6x_t);
      u8g2.drawGlyph(x, y, 65); 
      break;
    case CLOUD:
      u8g2.setFont(u8g2_font_open_iconic_weather_6x_t);
      u8g2.drawGlyph(x, y, 64); 
      break;
    case RAIN:
      u8g2.setFont(u8g2_font_open_iconic_weather_6x_t);
      u8g2.drawGlyph(x, y, 67); 
      break;
    case THUNDER:
      u8g2.setFont(u8g2_font_open_iconic_embedded_6x_t);
      u8g2.drawGlyph(x, y, 67);
      break;      
  }
}

void drawWeather(uint8_t symbol, int degree) {
  drawWeatherSymbol(0, 48, symbol);
  u8g2.setFont(u8g2_font_logisoso32_tf);
  u8g2.setCursor(48+3, 42);
  u8g2.print(degree);
  u8g2.print("°C");   // requires enableUTF8Print()
}

void drawMeasurements(int temperature, long pressure, long altitude) {
  u8g2.clearBuffer();
  
  uint8_t symbol;
  
  long hPa = pressure / 100;
  if (hPa < 970) {
    symbol = THUNDER;
  }
  else if (hPa  < 990) {
    symbol = RAIN;
  }
  else if (hPa  < 1010) {
    symbol = CLOUD;
  }
  else if (hPa  < 1025) {
    symbol = SUN_CLOUD;
  }
  else {
    symbol = SUN;
  }

  drawWeather(symbol, temperature);

  int pressureDigits = 0;
  long tmp = hPa;
  while (tmp > 0) {
    pressureDigits++;
    tmp /= 10;
  }
  
  u8g2.setFont(u8g2_font_6x10_mf);
  u8g2.setCursor(10 + (4 - pressureDigits) * 6, 63);
  u8g2.print(hPa);
  u8g2.print(" hPa");

  int altitudeDigits = 0;
  tmp = altitude;
  while (tmp > 0) {
    altitudeDigits++;
    tmp /= 10;
  }

  u8g2.setCursor(85 + (4 - altitudeDigits) * 6, 63);
  u8g2.print(altitude);
  u8g2.print(" m");

  u8g2.sendBuffer();
}

void setup() {
  u8g2.begin();  
  u8g2.enableUTF8Print();
}

void loop(void) {
  //getSensorMeasurements();

  temperature = 20;
  pressure = 95000;
  altitude = 5;
  drawMeasurements(temperature, pressure, altitude);
  delay(3000);

  temperature = 22;
  pressure = 97500;
  altitude = 42;
  drawMeasurements(temperature, pressure, altitude);
  delay(3000);

  temperature = 25;
  pressure = 100000;
  altitude = 230;
  drawMeasurements(temperature, pressure, altitude);
  delay(3000);
  
  temperature = 20;
  pressure = 101500;
  altitude = 1020;
  drawMeasurements(temperature, pressure, altitude);
  delay(3000);
  
  temperature = 20;
  pressure = 104000;
  altitude = 1020;
  drawMeasurements(temperature, pressure, altitude);
  delay(3000);
}
