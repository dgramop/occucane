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

void pulses(int count) {
	
	Serial.print("haptics: ");
	Serial.print(count);
	Serial.println(" pulses");


/*	for(int i=0; i < count; i++) {
		digitalWrite(MOTOR, HIGH);
		delay(50);

		digitalWrite(MOTOR, LOW);
		delay(50);
	}*/
}

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

void loop()
{
	int reading = sensor.readRangeContinuousMillimeters();
  Serial.print(reading);
  if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

	digitalWrite(MOTOR, HIGH);
	delay(75);
	digitalWrite(MOTOR, LOW);
	reading -= 200; //subtract 20cm
	reading = 0.25*reading;
	delay(reading > 0 ? (reading < 900 ? reading : 900): 1);

  Serial.println();
}
