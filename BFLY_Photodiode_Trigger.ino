const int DIODEPIN = A7;
const int CAMWAVEPIN = 2;
/*
#include "DHT.h"
#define DHTPIN 11
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);
*/
const int LOWBOUND = 150;
const int HIGHBOUND = 400;
// peaks are approx 900
const int FRAMERATE = 25;
int lastBrightness = 0;

void setup() {
  // initializes pins:
  Serial.begin(19200);
  pinMode(DIODEPIN, INPUT);
  pinMode(CAMWAVEPIN, OUTPUT);

  // dht.begin();
}

void loop() {
  // read photodiode pin
  int brightness = analogRead(DIODEPIN);
  /*
  Serial.print(brightness);
  Serial.print("     ");
  Serial.println(lastBrightness);
  */
  /*
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();

  if (not isnan(hum) && not isnan(temp)) {
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println("%");
  }
  */

  // triggers if the photodiode value is 1) decreasing and 2) below the arc threshold 
  if (brightness <= lastBrightness && brightness <= HIGHBOUND && lastBrightness > LOWBOUND) {
    // pseudo PWM signal to trigger the FLIR BFLY S
    Serial.println("Photo Taken");
    digitalWrite(CAMWAVEPIN, HIGH);
    delay(500 / FRAMERATE);
    digitalWrite(CAMWAVEPIN, LOW);
    delay(500 / FRAMERATE);
  }
  lastBrightness = brightness;
}