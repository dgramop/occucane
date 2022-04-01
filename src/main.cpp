#include <Arduino.h>

const static int MOTOR = 7;
const static int TX = 8;
const static int RX = 9;

// offset of pulses to add/subtract
const static int LOG_OFFSET = 1; 

// the number of centimeters to subtract from the distance
const static int DISTANCE_OFFSET = 10; //specified in cm

int rightshift_log(long duration) {
	int lg = 0;
	while(duration > 0) {
		duration >>= 1;
		lg++;
	}
	

	return lg;
}

void pulses(int count) {
	
	Serial.print("haptics: ");
	Serial.print(count);
	Serial.println(" pulses");

	digitalWrite(MOTOR, HIGH);
	delay(count);

	digitalWrite(MOTOR, LOW);

/*	for(int i=0; i < count; i++) {
		digitalWrite(MOTOR, HIGH);
		delay(50);

		digitalWrite(MOTOR, LOW);
		delay(50);
	}*/
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
	long distance = (duration*344)/5000;

	Serial.print("distance: ");
	Serial.print(distance);
	Serial.print(" duration: ");
	Serial.print(duration);
	Serial.println(" cm");

	int computed = rightshift_log(distance - DISTANCE_OFFSET > 1 ? distance - DISTANCE_OFFSET : 1);
	Serial.print(" computed log: ");
	Serial.print(computed);
	
	//we want between 7 and 2

	int num_pulses = 500/(computed + LOG_OFFSET > 0 ? computed + LOG_OFFSET : 1);
	if(num_pulses < 1) num_pulses = 1; //minmum one vibration, even for close stuff
	if(num_pulses > 1000) num_pulses = 1000; //maximum vibration

	pulses(num_pulses); // between 5 and one pulses

	delay(100);
}
