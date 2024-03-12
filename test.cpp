#include "framework.h"
#include "stdio.h"
#include "stdlib.h"
#include <vector>

class BezierCurve {
std::vector<vec3> cps; // control pts 

float B(int i, float t) {
  int n = cps.size()-1; // n+1 pts!
  float choose = 1;
  for(int j = 1; j <= i; j++) choose *= (float)(n-j+1)/j;
  return choose * pow(t, i) * pow(1-t, n-i);
}

public:
  void AddControlPoint(vec3 cp) { cps.push_back(cp); }
  
  vec3 r(float t) {
    vec3 rt(0, 0, 0);
    for(int i=0; i < cps.size(); i++) rt = rt + cps[i] * B(i,t);
    
    return rt;
  }
}

class CatmullRom {
  std::vector<vec3> cps; // control points 
  std::vector<float> ts; // parameter (knot) values
  vec3 Hermite(vec3 p0, vec3 v0, float t0, vec3 p1, vec3 v1, float t1,
  float t) {
    
  }
  public:
  
  void AddControlPoint(vec3 cp, float t) { … }
  
  vec3 r(float t) {
    for(int i = 0; i < cps.size() - 1; i++)
      if (ts[i] <= t && t <= ts[i+1]) {
      vec3 v0 = …, v1 = …;
      return Hermite(cps[i], v0, ts[i],cps[i+1], v1, ts[i+1], t);
      }
  }
};