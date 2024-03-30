#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define x_out A0
#define y_out A1
RF24 radio(10,9);
int xbase_arr[42];
int ybase_arr[42];
int xbase = 0;
int ybase = 0;
const byte address[6] = "00001";
struct data{
  int xAxis;
  int yAxis;

};
data send_data;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  int i = 0;
  while (i < 42)
  {
    xbase_arr[i] = analogRead(x_out);
    ybase_arr[i] = analogRead(y_out);
    i++;
  }
  
  int n_x = sizeof(xbase_arr) / sizeof(xbase_arr[0]);
  int n_y = sizeof(ybase_arr) / sizeof(ybase_arr[0]);
  xbase = average(xbase_arr, n_x);
  ybase = average(xbase_arr, n_y);
  Serial.print("Xbase : ");
  Serial.print(xbase);
  Serial.print("   Ybase : ");
  Serial.println(ybase);
}

void loop() {
  send_data.xAxis = xbase - analogRead(x_out);
  send_data.yAxis = ybase - analogRead(y_out);
  radio.write(&send_data, sizeof(data));
  Serial.print("X-Axis : ");
  Serial.print(send_data.xAxis);
  Serial.print("   Y-Axis : ");
  Serial.println(send_data.yAxis);
}

int average(int a[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];

    return sum / n;
}
