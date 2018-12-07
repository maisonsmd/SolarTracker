
//cac chan cam bien
#define SENSOR_TOP_LEFT			A1
#define SENSOR_TOP_RIGHT		A2
#define SENSOR_BOTTOM_LEFT		A0
#define SENSOR_BOTTOM_RIGHT		A3

//cac chan dieu khien dong co
#define VERTICAL_IN1			2
#define VERTICAL_IN2			3
#define HORIZONTAL_IN1			4
#define HORIZONTAL_IN2			5

//di chuyen len
void MoveUp() {
	digitalWrite(VERTICAL_IN1, LOW);
	digitalWrite(VERTICAL_IN2, HIGH);
}
//di chuyen xuong
void MoveDown() {
	digitalWrite(VERTICAL_IN2, LOW);
	digitalWrite(VERTICAL_IN1, HIGH);
}
//quay sang trai
void MoveLeft() {
	digitalWrite(HORIZONTAL_IN1, LOW);
	digitalWrite(HORIZONTAL_IN2, HIGH);
}
//quay sang phai
void MoveRight() {
	digitalWrite(HORIZONTAL_IN2, LOW);
	digitalWrite(HORIZONTAL_IN1, HIGH);
}
//dung truc doc
void StopVertical() {
	digitalWrite(VERTICAL_IN1, LOW);
	digitalWrite(VERTICAL_IN2, LOW);
}
//dung truc ngang
void StopHorizontal() {
	digitalWrite(HORIZONTAL_IN1, LOW);
	digitalWrite(HORIZONTAL_IN2, LOW);
}

void setup() {
	Serial.begin(115200);
	//khai bao cac chan dieu khien dong co la dau ra
	pinMode(VERTICAL_IN1, OUTPUT);
	pinMode(VERTICAL_IN2, OUTPUT);
	pinMode(HORIZONTAL_IN1, OUTPUT);
	pinMode(HORIZONTAL_IN2, OUTPUT);
}

void loop() {
	//doc cac cam bien va nhan ti le de cac cam bien ve cung gia tri
	float topLeftValue = analogRead(SENSOR_TOP_LEFT)  * 0.979;
	float topRightValue = analogRead(SENSOR_TOP_RIGHT) * 1;
	float bottomLeftValue = analogRead(SENSOR_BOTTOM_LEFT)*0.945;
	float bottomRightValue = analogRead(SENSOR_BOTTOM_RIGHT)*1.022;

	//in ra man hinh
	Serial.print(topLeftValue, 0);
	Serial.print('\t');
	Serial.print(topRightValue, 0);
	Serial.print('\t');
	Serial.print(bottomLeftValue, 0);
	Serial.print('\t');
	Serial.print(bottomRightValue, 0);
	Serial.println('\t');

	//gia tri trung binh cua cac phia
	float leftAverage = (topLeftValue + bottomLeftValue) / 2.0;
	float rightAverage = (topRightValue + bottomRightValue) / 2.0;
	float topAverage = (topLeftValue + topRightValue) / 2.0;
	float bottomAverage = (bottomLeftValue + bottomRightValue) / 2.0;

	//so sanh va dieu khien dong co
	if (leftAverage > rightAverage * 1.2 + 100) {
		MoveRight();
		Serial.print("RIGHT");
	}
	else if (rightAverage > leftAverage * 1.2 + 100) {
		MoveLeft();
		Serial.print("LEFT");
	}
	else {
		StopHorizontal();
		Serial.print("STOP");
	}

	Serial.print('\t');

	if (topAverage > bottomAverage * 1.2 + 100) {
		MoveDown();
		Serial.print("DOWN");
	} else if (bottomAverage > topAverage * 1.2 + 100) {
		MoveUp();
		Serial.print("UP");
	} else {
		StopVertical();
		Serial.print("STOP");
	}

	Serial.println();
	
	delay(100);
}