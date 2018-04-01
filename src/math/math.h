#pragma once
#include "Vector.h"

#define Abs(x) ((x) >= 0) ? (x) : (-x);
#define PI 3.1415926F
#define E 2.7182818F
#define sqrt2 1.414213562F
#ifndef _HUGE_ENUF
	#define _HUGE_ENUF  1e+300  // _HUGE_ENUF*_HUGE_ENUF must overflow
#endif

#define INFINITY   ((float)(_HUGE_ENUF * _HUGE_ENUF))
#define HUGE_VAL   ((double)INFINITY)
#define HUGE_VALF  ((float)INFINITY)
#define HUGE_VALL  ((long double)INFINITY)
#define NAN        ((float)(INFINITY * 0.0F))

Vector3 AngleToDirection(Vector3 v);

float Sin(float x);
float Cos(float x);
float Tan(float x);
float Asin(float x);
float Acos(float x);
float Atan(float x);
float Exp(float x);
float Exp2(float x);
float ExpE(float x);
float Log(float x);
float Log2(float x);
float Pow2(float base, float exp);
float PowE(float base, float exp);
float Sqrt(float x);
float InvSqrt(float x);
float fmodf(float x, float mod);
Vector3 Rotate(Vector3 left, Vector3 right);
Vector3 RotateConj(Vector3 left, Vector3 right);