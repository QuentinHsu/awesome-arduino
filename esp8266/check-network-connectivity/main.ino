#include <ESP8266WiFi.h>
#include <U8g2lib.h>
#include <ESP8266HTTPClient.h>
#include <time.h>

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, D1, D2, U8X8_PIN_NONE);

const char *ssid = "your_ssid";
const char *password = "your_password";

unsigned long previousMillis = 0;
const long interval = 10000; // interval to check connectivity (10 seconds)

void setup()
{
  u8g2.begin();
  u8g2.enableUTF8Print();

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  configTime(8 * 3600, 0, "pool.ntp.org", "time.nist.gov"); // set timezone to GMT+8
  displaySSID();
}

void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    checkConnectivity();
  }
}

void displaySSID()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  char displayStr[64];
  sprintf(displayStr, "SSID: %s", WiFi.SSID().c_str()); // Combine the strings
  u8g2.drawStr(0, 10, displayStr);                      // Display the combined string
  u8g2.sendBuffer();
}

void checkConnectivity()
{
  WiFiClient baiduClient;
  WiFiClient googleClient;
  HTTPClient httpBaidu;
  HTTPClient httpGoogle;

  httpBaidu.begin(baiduClient, "http://www.baidu.com");
  httpGoogle.begin(googleClient, "http://www.google.com");

  httpBaidu.setTimeout(1000);  // 1 second timeout
  httpGoogle.setTimeout(1000); // 1 second timeout

  int httpCodeBaidu = httpBaidu.GET();
  int httpCodeGoogle = httpGoogle.GET();

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  char displayStr[64];
  sprintf(displayStr, "SSID: %s", WiFi.SSID().c_str());
  u8g2.drawStr(0, 10, displayStr);

  if (httpCodeBaidu > 0)
  {
    u8g2.drawStr(0, 25, "Baidu: Success");
  }
  else
  {
    u8g2.drawStr(0, 25, "Baidu: Failed");
  }

  if (httpCodeGoogle > 0)
  {
    u8g2.drawStr(0, 40, "Google: Success");
  }
  else
  {
    u8g2.drawStr(0, 40, "Google: Failed");
  }

  char timeBuffer[30];
  getFormattedTime(timeBuffer);
  u8g2.drawStr(0, 55, timeBuffer);
  u8g2.sendBuffer();

  httpBaidu.end();
  httpGoogle.end();
}

void getFormattedTime(char *buffer)
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }
  strftime(buffer, 30, "%Y-%m-%d %H:%M:%S", &timeinfo);
}