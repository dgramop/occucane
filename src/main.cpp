#include <Arduino.h>

const static int MOTOR = 7;
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

void pulses(int count) {
	if(count < 1) count = 1; //minmum one vibration, even for close stuff
	if(count > 10) count = 10; //minmum one vibration, even for close stuff

	Serial.print("haptics: ");
	Serial.print(count);
	Serial.println(" pulses");

	for(int i=0; i < count; i++) {
		digitalWrite(MOTOR, HIGH);
		delay(50);

		digitalWrite(MOTOR, LOW);
		delay(50);
	}
}

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
	long distance = (duration*344)/10000;

	Serial.print("distance: ");
	Serial.print(distance);
	Serial.print(" duration: ");
	Serial.print(duration);
	Serial.println(" cm");

	int computed = rightshift_log(distance - 30 > 1 ? distance - 30 : 1);
	Serial.print(" computed log: ");
	Serial.print(computed);

	int num_pulses = 20/computed;
	pulses(num_pulses); // between 5 and one pulses

	delay(200);
}
