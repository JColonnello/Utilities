#pragma once
#include <stdbool.h>
#define DllExport _declspec(dllexport)

//Structs declarations

typedef struct Vector2
{
	float X;
	float Y;	
} Vector2;

typedef struct Vector3
{
	float X;
	float Y;
	float Z;
} Vector3;

typedef struct Vector4
{
	float X;
	float Y;
	float Z;
	float W;
} Vector4;

//Constant declarations

const Vector4 V_UnitX;
const Vector4 V_UnitY;
const Vector4 V_UnitZ;
const Vector4 V_UnitW;
const Vector4 V_One;
const Vector4 V_Zero;

//Vector2 public methods

Vector2 V2_Add(Vector2 x, Vector2 y);
Vector2 V2_Sub(Vector2 x, Vector2 y);
Vector2 V2_Opposed(Vector2 v);
Vector2 V2_Mult(Vector2 x, float y);
Vector2 V2_Div(Vector2 x, float y);
float V2_Length(Vector2 v);
float V2_LengthSquared(Vector2 v);
float V2_InvLength(Vector2 v);
void V2_Normalize(Vector2 *v);
Vector2 V2_Normalized(Vector2 v);
float V2_Dot(Vector2 left, Vector2 right);
float V2_Cross(Vector2 left, Vector2 right);
bool V2_Equals(Vector2 x, Vector2 y);
void V2_ToString(char *str, Vector2 v);
Vector2 V2_Rotate(Vector2 left, Vector2 right);
Vector2 V2_RotateConj(Vector2 left, Vector2 right);

//Vector3 public methods

Vector3 V3_Add(Vector3 x, Vector3 y);
Vector3 V3_Sub(Vector3 x, Vector3 y);
Vector3 V3_Opposed(Vector3 v);
Vector3 V3_Mult(Vector3 v, float y);
Vector3 V3_Div(Vector3 v, float y);
float V3_Length(Vector3 v);
float V3_LengthSquared(Vector3 v);
float V3_InvLength(Vector3 v);
void V3_Normalize(Vector3 *v);
Vector3 V3_Normalized(Vector3 v);
float V3_Dot(Vector3 left, Vector3 right);
Vector3 V3_Cross(Vector3 left, Vector3 right);
bool V3_Equals(Vector3 x, Vector3 y);
int V3_ToString(char *str, Vector3 v);
Vector3 V3_Rotate(Vector3 left, Vector3 right);
Vector3 V3_RotateConj(Vector3 left, Vector3 right);

//Vector4

Vector4 V4_Add(Vector4 x, Vector4 y);
Vector4 V4_Sub(Vector4 x, Vector4 y);
Vector4 V4_Opposed(Vector4 v);
Vector4 V4_Mult(Vector4 v, float y);
Vector4 V4_Div(Vector4 v, float y);
float V4_Length(Vector4 v);
float V4_LengthSquared(Vector4 v);
float V4_InvLength(Vector4 v);
void V4_Normalize(Vector4 *v);
Vector4 V4_Normalized(Vector4 v);
float V4_Dot(Vector4 left, Vector4 right);
bool V4_Equals(Vector4 x, Vector4 y);
int V4_ToString(char *str, Vector4 v);
