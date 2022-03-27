#include <Arduino.h>

const static int MOTOR = 7;
const static int TX = 8;
const static int RX = 9;

void setup() {
	pinMode(MOTOR, OUTPUT);
	pinMode(TX, OUTPUT);
	pinMode(RX, INPUT);
	Serial.begin(115200);
}

void loop() {
	digitalWrite(TX, LOW);
	delayMicroseconds(2);
	digitalWrite(TX, HIGH);
	delayMicroseconds(10);
	digitalWrite(TX, LOW);

	long duration = pulseIn(RX, HIGH);
	duration *= 344;
	duration /= 10000;

	Serial.print("Estimated Distance ");
	Serial.print(duration);
	Serial.println(" cm");


	digitalWrite(MOTOR, HIGH);
	delay(500);

	digitalWrite(MOTOR, LOW);
	delay(500);

	delay(1000);


}
