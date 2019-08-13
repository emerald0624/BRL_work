#define SELPIN1 10 //Selection Pin 
#define SELPIN2 11 //Selection Pin 
#define DATAOUT 75//MOSI 
#define DATAIN 74//MISO 
#define SPICLOCK 76//Clock 
int readvalue;
const int R0 = 500; // Trust Resistance value
const float factor[11] = {134.7277965, 187.0270571, 155.7659395, 218.3626418, 157.1815681, 164.3437955, 145.1582451, 167.1407023, 134.5570137, 223.7073385, 120};

String str = "";

int t1;
int t2;
int n_test = 20;
const int imax = 12;
unsigned int value[imax];
unsigned int val0[imax];
float resist[imax - 1];
float resist0[imax - 1];
float force[imax - 1];
void setup() {
  //set pin modes
  pinMode(SELPIN1, OUTPUT);
  pinMode(SELPIN2, OUTPUT);
  pinMode(DATAOUT, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(SPICLOCK, OUTPUT);
  //disable device to start with
  digitalWrite(SELPIN1, HIGH);
  digitalWrite(SELPIN2, HIGH);
  digitalWrite(DATAOUT, LOW);
  digitalWrite(SPICLOCK, LOW);

  Serial.begin(115200);
  for (int i = 0; i < imax; i++) {
    resist0[i] = 0;
  }


  for (int ii = 0; ii < n_test; ii++) {
    for (int i = 0; i < imax; i++) {
      if (i < 8) {
        digitalWrite(SELPIN1, LOW);
        value[i] = read_adc(i);
        digitalWrite(SELPIN1, HIGH);
      }
      else {
        digitalWrite(SELPIN2, LOW);
        value[i] = read_adc(i - 8);
        digitalWrite(SELPIN2, HIGH);

      }
    }
    for (int i = 1; i < imax; i++) {
      resist0[i - 1] = resist0[i - 1] + R0 * float(value[i]) / float(value[0] - value[i]) / float(n_test);
    }
  }

  t1 = micros();
}


int read_adc(int channel) {
  int adcvalue = 0;
  byte commandbits = B11000000; //command bits - start, mode, chn (3), dont care (3)

  //allow channel selection
  commandbits |= ((channel) << 3);

  //digitalWrite(selpin, LOW); //Select adc
  // setup bits to be written
  for (int i = 7; i >= 3; i--) {
    digitalWrite(DATAOUT, commandbits & 1 << i);
    //cycle clock
    digitalWrite(SPICLOCK, HIGH);
    digitalWrite(SPICLOCK, LOW);
  }

  digitalWrite(SPICLOCK, HIGH);   //ignores 2 null bits
  digitalWrite(SPICLOCK, LOW);
  digitalWrite(SPICLOCK, HIGH);
  digitalWrite(SPICLOCK, LOW);

  //read bits from adc
  for (int i = 11; i >= 0; i--) {
    adcvalue += digitalRead(DATAIN) << i;
    //cycle clock
    digitalWrite(SPICLOCK, HIGH);
    digitalWrite(SPICLOCK, LOW);
  }
  //Serial.println(adcvalue);
  //digitalWrite(selpin, HIGH); //turn off device
  return adcvalue;
}


void loop() {
  for (int i = 0; i < imax; i++) {
    value[i] = 0;
  }
  for (int k = 0; k < 20; k++) {
    for (int i = 0; i < imax; i++) {
      if (i < 8) {
        digitalWrite(SELPIN1, LOW);
        val0[i] = read_adc(i);
        digitalWrite(SELPIN1, HIGH);
      }
      else {
        digitalWrite(SELPIN2, LOW);
        val0[i] = read_adc(i - 8);
        digitalWrite(SELPIN2, HIGH);

      }
      value[i] = value[i] + val0[i];
    }
  }
  for (int i = 0; i < imax; i++) {
    value[i] = value[i] / 20;
  }
  for (int i = 1; i < imax; i++) {
    resist[i - 1] = R0 * float(value[i]) / float(value[0] - value[i]);
    force[i - 1] = factor[i - 1] * (1 / resist[i - 1] - 1 / resist0[i - 1]);
  }
  str = "";
  //  delay(10);
  //    t2 = micros();
  //    int delt = 1000000 / (t2 - t1);
  //    t1 = t2;
  Serial.print(force[0] + force[1] + force[2]);
  Serial.print(',');
  Serial.println(force[10]);
  //  Serial.println(str);
}
