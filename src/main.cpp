#include <Arduino.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

const int lightSensorPin = 1; 
float alpha = 0.1; 
int sensorValue = 0;
float emaValue = 0.0; 
bool firstRead = true; 

void setup() {
    Serial.begin(115200);

    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);

    tft.setCursor(0, 30);
    tft.print("Lux : ");
    tft.setCursor(0, 60);
    tft.print("EMA : ");
}

void loop() {
    sensorValue = analogRead(lightSensorPin);

    if (firstRead) {
        emaValue = sensorValue;
        firstRead = false;
    } else {
        emaValue = alpha * sensorValue + (1 - alpha) * emaValue;
    }

    Serial.print("Lux : ");
    Serial.println(sensorValue);
    Serial.print("EMA : ");
    Serial.println(emaValue);


    tft.fillRect(50, 30, 100, 20, TFT_BLACK);
    tft.fillRect(50, 60, 100, 20, TFT_BLACK); 

    tft.setCursor(50, 30);
    tft.print(sensorValue);
    tft.setCursor(50, 60);
    tft.print((int)emaValue); 

    delay(100);
}
