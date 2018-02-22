#include <Trace.h>
#define PIN 2
#define NUM_OF_PIXELS 20
#define JUMP 6
#define NUM_OF_COLORS 10
#define PHASE 0
#define FROM_MIDDLE 0
#define HIGHLEVEL 0.4
    // pin - the pin that the strip connected to
    // num_of_pixels - num of led in the strip
    // jump - the distance between two traces heads
    // num_of_colors - num of colors that will be in the traces
    // high_level - max power 0-1
    // phase - give phase (delay) to the trace .Default:0  
    // from_middle - if the trace will start from the middle. Default:0

Trace trace(PIN,NUM_OF_PIXELS,JUMP,NUM_OF_COLORS,HIGHLEVEL,PHASE,FROM_MIDDLE);

void setup() {  
   Serial.begin(9600); 
}

void loop() {
  trace.draw();
  trace.advance(0.1);
  
  delay(10);
}
