/*
https://www.hackster.io/microst/thermometer-diode-based-524613
  Thermometer based on 1n4148 silicon diode used as temperature sensor.The thermometer is based on the diode characteristic that the increase of the temperature its forward voltage (VF) is lowered by 2,2mV / ° C.
Fixing the value of Vf = VF0 at ambient temperature t0, the temperature value
t is calculated with the following formula:

t= t0 - [vf(t)- vf0]* K

with K = 1 / 2,2mV

The value of Vf (t) = dtemp -vf0 is obtained by averaging values of 1024 by acquiring as many vf values

The result of t is shown on the serial monitor
*/


// set pin numbers:

const int in = A0;          // used to bias the diode  anode
const int t0 = 20.3;
const float vf0 = 573.44;
// variables will change:

int i;
double dtemp, dtemp_avg, t;
double voltageref = 1076.50;
float t1;  
int measurements = 500;

void setup() {
  analogReference(INTERNAL);  // http://tronixstuff.com/2013/12/12/arduino-tutorials-chapter-22-aref-pin/
  Serial.begin(9600);
  pinMode(in, INPUT_PULLUP);            // set the  pin IN with npull up to bias the diode

}

void loop() {
  dtemp_avg = 0;
  for (i = 0; i < measurements; i++) {
    float vf = analogRead(A0) * (voltageref / 1023.00);
    //Serial.println(vf);
    dtemp = (vf - vf0) * 0.4545454;
    dtemp_avg = dtemp_avg + dtemp;
    delay(1);
  }
  t = t0 - dtemp_avg / measurements;
  if (t < 0) t = t1;
  else
  t1 = t;
  Serial.print("temperature in Celcius degree)   = " );
  Serial.println(t);
  
  delay (1000);

}
