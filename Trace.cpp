#include "Trace.h"
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

Trace::Trace (int pin, int num_of_pixels,int jump,int num_of_colors,float high_level, int phase=0,bool from_middle=0) {
   _pixels = Adafruit_NeoPixel(num_of_pixels, pin, NEO_GRB + NEO_KHZ800);
   _pixels.begin();
   _i = 0;
   _head_color = 0;
   _num_of_pixels = num_of_pixels;
   _jump = jump;
   _num_of_colors = num_of_colors;
   _phase = phase;
   _high_level = high_level;
   _from_middle=from_middle;
}

// ---------------------------
// advance
// ---------------------------
void Trace::advance(float s) {
  _i+=s;
  // when pixel_num get large the animation start to be slow, need to go back and keep the head_color 
  if (_i > _jump + _num_of_pixels-1 ) {
    _i -= _jump;
    _head_color = (_head_color+1)%_num_of_colors;        
  }
}

// ---------------------------
// draw
// ---------------------------
void Trace::draw() {
  int last_pixel;
  _pixels.clear();
   light_all_traces(_i,_high_level); 
   _pixels.show(); 
}

// ---------------------------
// light_all_traces
// ---------------------------
void Trace::light_all_traces (float i,float power) {
    int trace_num = 0;
    while (i >= 0 ) {     
     int color = (_head_color+trace_num)%_num_of_colors;
     if (_from_middle) {
      set_pixel(_num_of_pixels/2+i, color,power);
      set_pixel(_num_of_pixels/2-i, color,power);
     } else {       
       int led_ref = (int)(i+0.01);
       // Light the trace consider the sidtance from the real source (i)
       for (int led = led_ref -1 ; led < led_ref + 3; ++led) {  // light 2 leds before and 2 leds after the the main light
          float dist = 1 + abs(led-i);          
          float power_update = power / pow(dist,2);
          set_pixel(led,color,power_update); 
       }     
  
     }
      i-=_jump;     
      trace_num++;
   }
}

// ---------------------------
// set_pixel 
// ---------------------------
void Trace::set_pixel (int pixel_num,int color,float power) {
  int pixel_num_update = pixel_num - _phase; 
  if (pixel_num_update < 0) {
    return;
  }
  _pixels.setPixelColor(pixel_num_update, Wheel(color,power));         
}

// ---------------------------
// Wheel 
// ---------------------------
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// the level is how brigt will be tghe light (0 to 255).
uint32_t Trace::Wheel(byte color, float level) {
  Adafruit_NeoPixel pixels;
  if (level==0) return pixels.Color(0, 0, 0);
  //level=100;   
  float power;
 // Serial.println(color);
  if(color < _num_of_colors/3) {
     power=1.0*color/(_num_of_colors/3)*255;
     return pixels.Color(level*(255 - power), 0, level*power); 
  } else if(color < 2*_num_of_colors/3) {
      color -= _num_of_colors/3;
      power=1.0*color/(_num_of_colors/3)*255;
      return pixels.Color(0, level*power, level*(255 - power));
  } else {
     color -= 2*_num_of_colors/3;
     power=1.0*color/(_num_of_colors/3)*255;
     return pixels.Color(level*power, level*(255 - power), 0);
  }
}
