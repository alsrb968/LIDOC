/*
	Name:		bizcon.ino
	Created:	19-08-15 ¿ÀÈÄ 2:20:57
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
#define NUMPIXELS 4

HX711 mHX711;
//SoftwareSerial mHM10(BLUETOOTH_RX_PIN, BLUETOOTH_TX_PIN);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_LED_PIN, NEO_GRB + NEO_KHZ800);

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
	if (mHX711.is_ready()) {
		long reading = mHX711.read();
		reading /= 10000;


		Serial.print("HX711 reading: ");
		//mHM10.print("HX711 reading: ");
		Serial.println(reading);
		//mHM10.write(reading);
		//mHM10.write("\n");
		int num = 0;
		if (reading < 21) num = 0;
		else if (reading < 22) num = 1;
		else if (reading < 23) num = 2;
		else if (reading < 24) num = 3;
		else num = 4;
		for (int index = 0; index <= NUMPIXELS; index++) {
			if (index <= num) pixels.setPixelColor(index, pixels.Color(255, 255, 255));
			else pixels.setPixelColor(index, pixels.Color(0, 0, 0));
			pixels.show();
		}
	}
	else {
		Serial.println("HX711 not found.");
		//mHM10.println("HX711 not found.");
	}

	delay(300);
}
