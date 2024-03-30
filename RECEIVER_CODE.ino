#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 

#define OLED_RESET     -1
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int ENA = 3;
int ENB = 9;
int MotorA1 = 4;
int MotorA2 = 5;
int MotorB1 = 6;
int MotorB2 = 7;

RF24 radio(8, 10);

const byte address[6] = "00001";

struct data {
  int xAxis;
  int yAxis;

};
data receive_data;

void setup() {
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(0,address);
radio.setPALevel(RF24_PA_MIN);
radio.setDataRate(RF24_250KBPS);
radio.startListening();
pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(MotorA1, OUTPUT);
pinMode(MotorA2, OUTPUT);
pinMode(MotorB1, OUTPUT);
pinMode(MotorB2, OUTPUT);

if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println("SSD1306 allocation failed");
}
else {
    Serial.println("Connected to OLED Screen Successfully");
}
}

int s = 40;
void loop() {
  while(radio.available()) {
    OLED.clearDisplay();
    OLED.setTextColor(WHITE, BLACK);
    OLED.setCursor(0, 25);
    OLED.setTextSize(2);
    
    radio.read(&receive_data, sizeof(data));
    Serial.print("recived yAxis: ");
    Serial.print(receive_data.yAxis);
    Serial.print("   recived xAxis: ");
    Serial.println(receive_data.xAxis);
    //Note : ʌ stand for forward v stand for backward N stand for neutral
    //Turn Right
    //ʌ v
    //ʌ v
    if(receive_data.yAxis > s) {
      digitalWrite(MotorA1, LOW);
      digitalWrite(MotorA2, HIGH);
      digitalWrite(MotorB1, HIGH);
      digitalWrite(MotorB2, LOW);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
      OLED.print(">>>>>>>>>>");
      //Turn Left
      //v ʌ
      //v ʌ
}   else if(receive_data.yAxis < (-1)*s) {
      digitalWrite(MotorA1, HIGH);
      digitalWrite(MotorA2, LOW);
      digitalWrite(MotorB1, LOW);
      digitalWrite(MotorB2, HIGH);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
      OLED.print("<<<<<<<<<<");
      //Reverse
      //v v
      //v v
} else if(receive_data.xAxis < (-1)*s){
      digitalWrite(MotorA1, HIGH);
      digitalWrite(MotorA2, LOW);
      digitalWrite(MotorB1, HIGH);
      digitalWrite(MotorB2, LOW);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
      OLED.print("VVVVVVVVVV");
      // Forward
      // ʌ ʌ
      // ʌ ʌ
} else if(receive_data.xAxis > s){
      digitalWrite(MotorA1, LOW);
      digitalWrite(MotorA2, HIGH);
      digitalWrite(MotorB1, LOW);
      digitalWrite(MotorB2, HIGH);
      analogWrite(ENA, 150);
      analogWrite(ENB, 150);
      OLED.print("^^^^^^^^^^");
      //Neutral
      // N N
      // N N
}  else {
      digitalWrite(MotorA1, LOW);
      digitalWrite(MotorA2, LOW);
      digitalWrite(MotorB1, LOW);
      digitalWrite(MotorB2, LOW);
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);
      OLED.print("Neutral ;)");
  }
 }
 OLED.display();
}
