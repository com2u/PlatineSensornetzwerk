#include <ESP8266WiFi.h>
//#include <Credentials.h>

/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com
*********/
volatile bool doInterrupt = false;
int waitCount = 0;
volatile int interruptCount = 1;
#define InterruptLED_PIN D7
#define InterruptMCP_PIN D0

#include <Wire.h>

struct Sensors {
    int array[3];
    int inputStatus[8];
    int inputCount[8];
    int inputLast[8];
    String inputName[8] = {"Radar","Audio","PIR","X1","X2","X3","X3","X5"};
    int noOfMQTTValues = 9;
    String header[14]       = {"Temp", "Preasure", "Humidity", "Gas", "Light", "Volt", "Radar","Audio","PIR","X","X", "X" ,"X", "X"};
    String measurement[14]  = { "0"  , "1",        "2",        "3",   "4"    , "5",    "6",   "7",   "8",    "9","10","11","12","13"    };

};

Sensors sensors;

void I2CScan(){
   byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++ ) 
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error==4) 
    {
      Serial.print("Unknow error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(1000);           // wait 5 seconds for next scan

}

void setup() {
  Wire.begin(D2, D1);
  Serial.begin(115200);
  Serial.println("\nI2C Scanner");
  I2CScan();
  initBME280();
  initBME680();
  initBH1750();
  initMCP();
  initLED();
  runLED(40,40,0,0,0,0);
  initWIFI();
  initMQTT();
  //initTime();
}



void loop() {
  runLED(40,0,0,0,0,40);
  delay(50);
  readBME680();
  delay(50);
  readBME280();
  delay(50);
  readBH1750();
  delay(50);
  Serial.print("Analog value:");
  sensors.measurement[5] = String(analogRead(A0));
  Serial.println(sensors.measurement[4]);
  delay(50);
  
  if (sendMQTT()){
    resetMCPCount();
    runLED(0,40,0,0,0,0);
  }
  for ( int i = 0; i < 5000; i++) {
    delay(60);
    handleMQTT();
    if (readMCP()){
      LEDStatus(sensors.inputStatus[0], sensors.inputStatus[1], sensors.inputStatus[2]);
    }
  }
  
  

  /*
    for ( int i = 0; i < 10; i++) {
    delay(500);
    if (doInterrupt) {
      delay(50);
      Serial.print(interruptCount);
      Serial.print("   ");
      //noInterrupts();
      readMCP();
      doInterrupt = false;
      digitalWrite(InterruptLED_PIN, HIGH);
      //interrupts();
      attachInterrupt(digitalPinToInterrupt(InterruptMCP_PIN), intARead, CHANGE);
    }
    }
  */

}
