#ifndef Trace_h
#define Trace_h
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
class Trace
{
  public:
    // pin - the pin that the strip connected to
    // num_of_pixels - num of led in the strip
    // jump - the distance between two traces heads
    // num_of_colors - num of colors that will be in the traces
    // high_level - max power 0-1
    // phase - give phase (delay) to the trace  
    Trace(int pin, int num_of_pixels, int jump, int num_of_colors,float high_level,int phase=0,bool from_middle=0);
    void advance(float s);    
    void draw();
  private:
    Adafruit_NeoPixel _pixels;
    void light_all_traces(float i,float power);
    void set_pixel (int pixel_num,int color,float power);
    uint32_t Wheel(byte color, float level);

    int _num_of_pixels;
    float _i;
    bool _from_middle;
    int _jump;
    int _num_of_colors;
    int _head_color;
    int _phase;
    float _high_level;


};
#endif
