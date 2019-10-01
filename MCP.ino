#include "Adafruit_MCP23017.h"
// Basic pin reading and pullup test for the MCP23017 I/O expander
// public domain!

// Connect pin #12 of the expander to Analog 5 (i2c clock)
// Connect pin #13 of the expander to Analog 4 (i2c data)
// Connect pins #15, 16 and 17 of the expander to ground (address selection)
// Connect pin #9 of the expander to 5V (power)
// Connect pin #10 of the expander to ground (common ground)
// Connect pin #18 through a ~10kohm resistor to 5V (reset pin, active low)

// Input #0 is on pin 21 so connect a button or switch from there to ground

Adafruit_MCP23017 mcp;




void initMCP() {
  mcp.begin(0x27);      // use default address 0
  mcp.pinMode(0, OUTPUT);
  mcp.pinMode(1, OUTPUT);
  mcp.pinMode(2, OUTPUT);
  mcp.pinMode(3, OUTPUT);
  mcp.pinMode(4, OUTPUT);
  mcp.pinMode(5, OUTPUT);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(7, OUTPUT);
  mcp.pinMode(8, INPUT);
  mcp.pinMode(9, INPUT);
  mcp.pinMode(10, INPUT);
  mcp.pinMode(11, INPUT);
  mcp.pinMode(12, INPUT);
  mcp.pinMode(13, INPUT);
  mcp.pinMode(14, INPUT);
  mcp.pinMode(15, INPUT);

  mcp.pullUp(8, LOW);
  mcp.pullUp(9, LOW);
  mcp.pullUp(10, LOW);
  mcp.pullUp(11, LOW);
  mcp.pullUp(12, LOW);
  mcp.pullUp(13, LOW);
  mcp.pullUp(14, LOW);
  mcp.pullUp(15, LOW);

  mcp.setupInterruptPin(8, CHANGE);
  mcp.setupInterruptPin(9, CHANGE);
  mcp.setupInterruptPin(10, CHANGE);
  mcp.setupInterruptPin(11, CHANGE);
  mcp.setupInterruptPin(12, CHANGE);
  mcp.setupInterruptPin(13, CHANGE);
  mcp.setupInterruptPin(14, CHANGE);
  mcp.setupInterruptPin(15, CHANGE);
  
  //mcp.setupInterrupts(true, false, LOW);

  pinMode(InterruptLED_PIN, OUTPUT);  // use the p13 LED as debugging
  digitalWrite(InterruptMCP_PIN, HIGH);
  //pinMode(InterruptMCP_PIN, INPUT_PULLUP);
  //mcp.readGPIOAB();
  //attachInterrupt(digitalPinToInterrupt(InterruptMCP_PIN), intARead, CHANGE);
  Serial.print("Interrupt Attached to GPIO ");
  Serial.println(InterruptMCP_PIN);
  
}
//portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void intARead() {
  noInterrupts();
  //portENTER_CRITICAL_ISR(&mux);
  doInterrupt = true;
  interruptCount++;
  digitalWrite(InterruptLED_PIN, LOW);
  //portEXIT_CRITICAL_ISR(&mux);
  interrupts();
  
}




void resetMCP(){
      mcp.readGPIOAB();
}

void resetMCPCount(){
   for (int i = 0; i < 8; i++) {
      sensors.inputCount[i] = 0;
   }
}

boolean readMCP(){
  boolean changed = false;
   for (int i = 0; i < 8; i++) {
    sensors.inputStatus[i] = mcp.digitalRead(8+i);
    if (sensors.inputStatus[i] != sensors.inputLast[i]) {
      sensors.inputLast[i] = sensors.inputStatus[i];
      sensors.inputCount[i]++;
      changed = true;
      //String header[] = {"Temp", "Preasure", "Humidity", "Gas", "Light", "Volt", "PIR","Radar","Audio"};
      //String value[]  = { "0"  , "1",        "2",        "3",   "4"    , "5",    "6",   "7",   "8"    };

      if (i == 0) {
        // Radar
        sensors.measurement[6] = String(sensors.inputCount[i]);
      } else if (i == 1) {
        // PIR
        sensors.measurement[7] = String(sensors.inputCount[i]);
      } else if (i == 2) {
        // Audio
        sensors.measurement[8] = String(sensors.inputCount[i]);
      } else if (i == 3) {
        // Ausio
        sensors.measurement[9] = String(sensors.inputCount[i]);
      } else if (i == 4) {
        // Ausio
        sensors.measurement[10] = String(sensors.inputCount[i]);
      } else if (i == 5) {
        // Ausio
        sensors.measurement[11] = String(sensors.inputCount[i]);
      } else if (i == 6) {
        // Ausio
        sensors.measurement[12] = String(sensors.inputCount[i]);
      } else if (i == 7) {
        // Ausio
        sensors.measurement[13] = String(sensors.inputCount[i]);
     
      }
      
      Serial.print(sensors.inputName[i]);
      Serial.print("  ");
      Serial.println(sensors.inputCount[i]);
    }
   }
   if (changed == true) {
   for (int i = 0; i < 8; i++) {
    Serial.print(sensors.inputStatus[i]);
   }
   Serial.println();
   }
   return changed;
}




