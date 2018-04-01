#pragma once
#include "Vector.h"
#include <stdbool.h>

//Struct declarations

typedef struct Matrix3
{
	Vector3 Row0;
	Vector3 Row1;
	Vector3 Row2;
} Matrix3;

typedef struct Matrix4 
{
	Vector4 Row0;
	Vector4 Row1;
	Vector4 Row2;
	Vector4 Row3;
} Matrix4;

//Constant declaration

const Matrix3 M3_Identity;
const Matrix3 M3_Zero;
const Matrix4 M4_Identity;
const Matrix4 M4_Zero;

//Matrix3 public methods

void M3_CreateFromAxisAngle(Vector3 axis, float angle, Matrix3 *out);
void M3_CreateScale(Vector3 scale, Matrix3 *out);
Vector3 M3_MainDiagonal(Matrix3 *mat);
Vector3 M3_Column0(Matrix3 *mat);
Vector3 M3_Column1(Matrix3 *mat);
Vector3 M3_Column2(Matrix3 *mat);
float M3_Determinant(Matrix3 *mat);
void M3_Mult(Matrix3 *left, Matrix3 *right, Matrix3 *out);
bool M3_Invert(Matrix3 *mat, Matrix3 *out);
void M3_Transpose(Matrix3 *mat, Matrix3 *out);
bool M3_Equals(Matrix3 *left, Matrix3 *right);
int M3_ToString(Matrix3 *v, char *str);

//Matrix4 public methods

void M4_CreateTranslation(Vector3 translation, Matrix4 *out);
//void M4_CreateRotation(Quaternion rotation, Matrix4 *out);
void M4_CreateFromAxisAngle(Vector3 axis, float angle, Matrix4 *out);
void M4_CreateScale(Vector3 scale, Matrix4 *out);
void M4_CreateOrthographic(float left, float right, float bottom, float top, float zNear, float zFar, Matrix4 *out);
void M4_CreatePerspective(float fovy, float aspect, float zNear, float zFar, Matrix4 *out);
void M4_Translation(Matrix4 *mat, Vector3 *translation);
//void M4_Rotation(Matrix4 *mat, Quaternion *rotation);
void M4_Scale(Matrix4 *mat, Vector3 *scale);
Vector4 M4_Column0(Matrix4 *mat);
Vector4 M4_Column1(Matrix4 *mat);
Vector4 M4_Column2(Matrix4 *mat);
Vector4 M4_Column3(Matrix4 *mat);
float M4_Determinant(Matrix4 *mat);
void M4_Transposed(Matrix4 *mat, Matrix4 *out);
bool M4_Inverted(Matrix4 *mat, Matrix4 *out);
void M4_Mult(Matrix4 *left, Matrix4 *right, Matrix4 *out);
bool M4_Equals(Matrix4 *left, Matrix4 *right);
int M4_ToString(Matrix4 *mat, char *str);
