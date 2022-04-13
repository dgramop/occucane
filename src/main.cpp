#include <Arduino.h>
#include <Wire.h>
#include <VL53L0X.h>

const static int TX = 8;
const static int RX = 9;

int rightshift_log(long duration) {
	int lg = 0;
	while(duration > 0) {
		duration >>= 1;
		lg++;
	}
	

	return lg;
}

VL53L0X sensor;

const int MOTOR = A2;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
	pinMode(TX, OUTPUT);
	pinMode(RX, INPUT);
	pinMode(MOTOR, OUTPUT);

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
}

void delay_with_alarm(int time, int threshold) {
	Serial.print("long wait for");
	Serial.print(time);
	if(time < 50) {
		Serial.print("skip loop");
		delay(time);
		return;
	}
	while(time > 0) {
		time -= 50;
		delay(50);
		int reading = sensor.readRangeContinuousMillimeters();
		Serial.print("\nin loop got");
		Serial.print(reading);

		if(reading < threshold || (threshold == -1 && reading*0.1 < time)) {
			Serial.print("early exit");
			return;
		}

	}
}

void loop()
{
	int reading = sensor.readRangeContinuousMillimeters();
	//delay_with_alarm(10000);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

	digitalWrite(MOTOR, HIGH);
	delay(25);
	digitalWrite(MOTOR, LOW);
		//reading -= 200; //subtract 20cm
	Serial.print(reading);
	if(reading > 8000) {
		Serial.print("long wait");
		//delay_with_alarm(10000, 800);
		delay(500);

	}
	Serial.print("MM");
	reading = 0.1*reading;
	delay_with_alarm(reading, -1);

  Serial.println();
}
