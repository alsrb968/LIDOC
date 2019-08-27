/*
	Name:		bizcon.ino
	Created:	19-08-15 오후 2:20:57
	Author:		Kang Minkyu
*/

// the setup function runs once when you press reset or power the board
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <HX711.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
const int BLUETOOTH_RX_PIN = 7;
const int BLUETOOTH_TX_PIN = 8;
const int NEOPIXEL_LED_PIN = 5;
const int BUZZER_PIN = 6;
#define NUMPIXELS 4

HX711 mHX711;
//SoftwareSerial mHM10(BLUETOOTH_RX_PIN, BLUETOOTH_TX_PIN);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_LED_PIN, NEO_GRB + NEO_KHZ800);

long getPressure() {
	long pressure = -1;
	if (mHX711.is_ready()) {
		pressure = mHX711.read();
		pressure /= 10000;
	}
	else {
		Serial.println("HX711 not found.");
	}
	return pressure;
}

void setStripLed(int cnt) {
	for (int i = 0; i < NUMPIXELS; i++) {
		if (i < cnt) {
			switch (i)
			{
			case 0:
				pixels.setPixelColor(i, pixels.Color(255, 0, 0));
				break;
			case 1:
				pixels.setPixelColor(i, pixels.Color(255, 0, 0));
				break;
			case 2:
				pixels.setPixelColor(i, pixels.Color(255, 255, 0));
				break;
			case 3:
				pixels.setPixelColor(i, pixels.Color(0, 255, 0));
				break;
			}
		}
		else {
			pixels.setPixelColor(i, pixels.Color(0, 0, 0));
		}
		pixels.show();
	}
}

void setup() {
	Serial.begin(9600);
	mHX711.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
	//mHM10.begin(9600);
	pixels.begin();
}

// the loop function runs over and over again until power down or reset
void loop() {
	/*if (mHM10.available()) {
		Serial.write(mHM10.read());
	}
	if (Serial.available()) {
		mHM10.write(Serial.read());
	}*/
	long reading = getPressure();
	if (reading > 0) {

		Serial.print("HX711 reading: ");
		//mHM10.print("HX711 reading: ");
		Serial.println(reading);
		//mHM10.write(reading);
		//mHM10.write("\n");

		if (reading <= 20) {
			setStripLed(0);
			noTone(BUZZER_PIN);
		}
		else if (reading <= 21) {
			setStripLed(1);
			noTone(BUZZER_PIN);
		}
		else if (reading <= 22) {
			setStripLed(2);
			noTone(BUZZER_PIN);
		}
		else if (reading <= 23) {
			setStripLed(3);
			noTone(BUZZER_PIN);
		}
		else {
			setStripLed(4);
			tone(BUZZER_PIN, 1000);
		}
	}
	delay(300);
}
