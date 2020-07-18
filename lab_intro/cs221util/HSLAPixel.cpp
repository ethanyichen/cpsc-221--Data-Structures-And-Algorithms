#include "HSLAPixel.h"

namespace cs221util {
HSLAPixel::HSLAPixel(){
 h = 40;
 s = 0;
 l = 1;
 a = 1;
} 

HSLAPixel::HSLAPixel(double h_, double s_, double l_){
 h = h_;
 s = s_;
 l = l_;
}

HSLAPixel::HSLAPixel(double h_, double s_, double l_, double a_){
 h = h_;
 s = s_;
 l = l_;
 a = a_;
 }
}
