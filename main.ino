#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define DHT_PIN 4
#define DHT_TYPE DHT11
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const char* WIFI_SSID = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

DHT dht(DHT_PIN, DHT_TYPE);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
WebServer server(80);

float temperature = NAN;
float humidity = NAN;

void readSensors() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
}

String htmlPage() {
  String page = "<!doctype html><html><head><meta charset='utf-8'>";
  page += "<meta name='viewport' content='width=device-width,initial-scale=1'>";
  page += "<title>ESP32 Environmental Monitor</title></head><body>";
  page += "<h1>ESP32 Environmental Monitor</h1>";
  page += "<p>Temperature: " + String(temperature, 1) + " &deg;C</p>";
  page += "<p>Humidity: " + String(humidity, 1) + " %</p>";
  page += "<p>Status: ONLINE</p></body></html>";
  return page;
}

void updateDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("ENVIRONMENT");
  display.setCursor(0, 22);
  display.printf("Temp: %.1f C\n", temperature);
  display.setCursor(0, 38);
  display.printf("Hum : %.1f %%\n", humidity);
  display.display();
}

void setup() {
  Serial.begin(115200);
  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed");
    while (true) delay(1000);
  }

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    readSensors();
    server.send(200, "text/html", htmlPage());
  });
  server.begin();
}

void loop() {
  static unsigned long lastRead = 0;

  if (millis() - lastRead >= 2000) {
    lastRead = millis();
    readSensors();

    if (!isnan(temperature) && !isnan(humidity)) {
      updateDisplay();
      Serial.printf("Temperature: %.1f C | Humidity: %.1f %%\n",
                    temperature, humidity);
    }
  }

  server.handleClient();
}
