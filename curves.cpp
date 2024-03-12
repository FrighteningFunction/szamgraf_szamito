#include "framework.h"
#include "stdio.h"
#include "stdlib.h"
#include <vector>
#include <math.h>

class Curve{
  protected:

  static std::vector<vec3> cps;

  public:

  void AddControlPoint(vec3 cp) { cps.push_back(cp); }

  virtual vec3 r(float t) = 0;

};

std::vector<vec3> Curve::cps;

class LagrangeCurve : public Curve{
std::vector<float> ts; // knots
  
float L(int i, float t) {
  float Li = 1.0f;
  for(int j = 0; j < cps.size(); j++)
  if (j != i) Li *= (t - ts[j])/(ts[i] - ts[j]);
  return Li;
}
  
public:
void AddControlPoint(vec3 cp) { 
  float ti = cps.size(); // or something better
  cps.push_back(cp); ts.push_back(ti);
}
  vec3 r(float t) {
  vec3 rt(0, 0, 0);
  for(int i = 0; i < cps.size(); i++) rt = rt + cps[i] * L(i,t);
		
  return rt;
  }
};

class BezierCurve : public Curve{

float B(int i, float t) {
  int n = cps.size()-1; // n+1 pts!
  float choose = 1;
  for(int j = 1; j <= i; j++) choose *= (float)(n-j+1)/j;
  return choose * pow(t, i) * pow(1-t, n-i);
}

public:
  
  vec3 r(float t) {
    vec3 rt(0, 0, 0);
    for(int i=0; i < cps.size(); i++) rt = rt + cps[i] * B(i,t);
    
    return rt;
  }

};

class CatmullRom : public Curve{ 
  std::vector<float> ts; // parameter (knot) values
  vec3 Hermite(vec3 p0, vec3 v0, float t0, vec3 p1, vec3 v1, float t1,
  float t) {
    vec3 a0 = p1;
    vec3 a1 = v0;
    vec3 a2 = 3*(p1-p0) / pow((t1-t0), 2) - (v1+2*v0)/(t1-t0);
    vec3 a3 = 2*(p0-p1) / pow((t1-t0), 3) - (v1+v0)/pow((t1-t0), 2);

    return a3*pow(t-t0, 3)+a2*pow(t-t0, 2)+a1*(t-t0)+a0;    
  }

  public:
  
  vec3 r(float t) {
    for(int i = 0; i < cps.size() - 1; i++) {
        if (ts[i] <= t && t <= ts[i+1]) {
            vec3 v0;
            if (i == 0) {
                v0 = (cps[i+1] - cps[i]) / (ts[i+1] - ts[i]);
            } else {
                v0 = ((cps[i+1] - cps[i]) / (ts[i+1] - ts[i]) + (cps[i] - cps[i-1]) / (ts[i] - ts[i-1])) * 0.5f;
            }

            vec3 v1;
            if (i >= cps.size() - 2) {
                v1 = (cps[i+1] - cps[i]) / (ts[i+1] - ts[i]);
            } else {
                v1 = ((cps[i+2] - cps[i+1]) / (ts[i+2] - ts[i+1]) + (cps[i+1] - cps[i]) / (ts[i+1] - ts[i])) * 0.5f;
            }

            return Hermite(cps[i], v0, ts[i], cps[i+1], v1, ts[i+1], t);
        }
    }

    return cps.back();
}

};

int main(void){
  printf("Choose a curve type:\n0 lagrange\n1 bezier\n2 catmull-rom");

  CatmullRom cr;
  LagrangeCurve lc;
  BezierCurve bc;

  int antwort;
    if (scanf("%d", &antwort) != 1) {
        printf("Invalid input. Please enter a number.\n");
    }

  printf("Now type 3 control points to add in x,y format:\n");
  vec3 cp1, cp2, cp3;

  scanf("%f,%f %f,%f %f,%f", &cp1.x, &cp1.y, &cp2.x, &cp2.y, &cp3.x, &cp3.y);
  cp1.z = 1;
  cp2.z = 1;
  cp3.z = 1;

  float t;
  printf("Now type the t parameter:\n");
  scanf("%f", &t);

  vec3 r;

  lc.AddControlPoint(cp1);
  lc.AddControlPoint(cp2);
  lc.AddControlPoint(cp3);

  switch(antwort){
    case 0:
      r = lc.r(t);
      break;
    case 1:
      r = bc.r(t);
      break;
    case 2:
      r = cr.r(t);
      break;
    default:
      printf("fatal error.\n");
      break;
  }

  printf("The r(t) value for you curve is: %f,%f", r.x, r.y);

  return 0;
}