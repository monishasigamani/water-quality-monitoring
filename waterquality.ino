#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include "DHT.h"

// Define pins
#define DHTPIN 15
#define DHTTYPE DHT22

#define PH_PIN 34       // Potentiometer 1
#define TURB_PIN 35     // Potentiometer 2
#define TDS_PIN 32      // Potentiometer 3

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

// Objects
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();

  // OLED initialization
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("OLED not found"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Water Quality System");
  display.display();
  delay(2000);
}

void loop() {
  // Read DHT22 data
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read potentiometers
  int phValue = analogRead(PH_PIN);
  int turbValue = analogRead(TURB_PIN);
  int tdsValue = analogRead(TDS_PIN);

  // Convert to simulated sensor readings
  float ph = map(phValue, 0, 4095, 0, 14);           // 0–14 pH
  float turbidity = map(turbValue, 0, 4095, 0, 100);  // 0–100 NTU
  float tds = map(tdsValue, 0, 4095, 0, 1000);        // 0–1000 ppm

  // Clear display
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("WATER QUALITY MONITOR");
  display.println("----------------------");

  // Display sensor data
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.print("Hum : ");
  display.print(humidity);
  display.println(" %");

  display.print("pH  : ");
  display.println(ph, 1);

  display.print("Turb: ");
  display.print(turbidity, 1);
  display.println(" NTU");

  display.print("TDS : ");
  display.print(tds, 1);
  display.println(" ppm");

  display.display();

  // Print to serial monitor
  Serial.println("------ Water Quality ------");
  Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println(" %");
  Serial.print("pH: "); Serial.println(ph);
  Serial.print("Turbidity: "); Serial.print(turbidity); Serial.println(" NTU");
  Serial.print("TDS: "); Serial.print(tds); Serial.println(" ppm");
  Serial.println("----------------------------");

  delay(2000);
}
