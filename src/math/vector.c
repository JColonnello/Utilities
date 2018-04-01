#include "Vector.h"
#include "Math.h"
#include <stdio.h>

#define V_UNITX { .X = 1.0f, .Y = 0.0f, .Z = 0.0f, .W = 0.0f }
#define V_UNITY { .X = 0.0f, .Y = 1.0f, .Z = 0.0f, .W = 0.0f }
#define V_UNITZ { .X = 0.0f, .Y = 0.0f, .Z = 1.0f, .W = 0.0f }
#define V_UNITW { .X = 0.0f, .Y = 0.0f, .Z = 0.0f, .W = 1.0f }
#define V_ONE { .X = 1.0f, .Y = 1.0f, .Z = 1.0f, .W = 1.0f }
#define V_ZERO { .X = 0.0f, .Y = 0.0f, .Z = 0.0f, .W = 0.0f }

const Vector4 V_UnitX = V_UNITX;
const Vector4 V_UnitY = V_UNITY;
const Vector4 V_UnitZ = V_UNITZ;
const Vector4 V_UnitW = V_UNITW;
const Vector4 V_One = V_ONE;
const Vector4 V_Zero = V_ZERO;

//Vector2

Vector2 V2_Add(Vector2 x, Vector2 y)
{
	return (Vector2){x.X + y.X, x.Y + y.Y};
}

Vector2 V2_Sub(Vector2 x, Vector2 y)
{
	return (Vector2){x.X - y.X, x.Y - y.Y};
}

Vector2 V2_Opposed(Vector2 v)
{
	return (Vector2){-v.X, -v.Y};
}

Vector2 V2_Mult(Vector2 x, float y)
{
	return (Vector2){x.X * y, x.Y * y};
}

Vector2 V2_Div(Vector2 x, float y)
{
	float inv = 1.0f / y;
	return (Vector2){x.X * inv, x.Y * inv};
}

float V2_Length(Vector2 v)
{
	return Sqrt(v.X * v.X + v.Y * v.Y);
}

float V2_LengthSquared(Vector2 v)
{
	return v.X * v.X + v.Y * v.Y;
}

float V2_InvLength(Vector2 v)
{
	return InvSqrt(v.X * v.X + v.Y * v.Y);
}

void V2_Normalize(Vector2 *v)
{
	float scale = V2_InvLength(*v);
	v->X *= scale;
	v->Y *= scale;
}

Vector2 V2_Normalized(Vector2 v)
{
	return V2_Mult(v, V2_InvLength(v));
}

float V2_Dot(Vector2 left, Vector2 right)
{
	return left.X * right.X + left.Y * right.Y;
}

float V2_Cross(Vector2 left, Vector2 right)
{
	return left.X * right.Y - left.Y * right.X;
}

bool V2_Equals(Vector2 x, Vector2 y)
{
	return (x.X == y.X) && (x.Y == y.Y);
}

void V2_ToString(char *str, Vector2 v)
{
	sprintf(str, "(%f, %f)", v.X, v.Y);
}

Vector2 V2_Rotate(Vector2 left, Vector2 right)
{
    return (Vector2){left.X * right.X - left.Y * right.Y,
    			  left.X * right.Y + left.Y * right.X};
}

Vector2 V2_RotateConj(Vector2 left, Vector2 right)
{
    return (Vector2){left.X * right.X + left.Y * right.Y,
    			  left.Y * right.X - left.X * right.Y};
}

//Vector3

Vector3 V3_Add(Vector3 x, Vector3 y)
{
	return (Vector3){x.X + y.X, x.Y + y.Y, x.Z + y.Z};
}

Vector3 V3_Sub(Vector3 x, Vector3 y)
{
	return (Vector3){x.X - y.X, x.Y - y.Y, x.Z - y.Z};
}

Vector3 V3_Opposed(Vector3 v)
{
	return (Vector3){-v.X, -v.Y, -v.Z};
}

Vector3 V3_Mult(Vector3 v, float y)
{
	return (Vector3){v.X * y, v.Y * y, v.Z * y};
}

Vector3 V3_Div(Vector3 v, float y)
{
	float inv = 1.0f / y;
	return (Vector3){v.X * inv, v.Y * inv, v.Z * inv};
}

float V3_Length(Vector3 v)
{
	return Sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
}

float V3_LengthSquared(Vector3 v)
{
	return v.X * v.X + v.Y * v.Y + v.Z * v.Z;
}

float V3_InvLength(Vector3 v)
{
	return InvSqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
}

void V3_Normalize(Vector3 *v)
{
	float scale = V3_InvLength(*v);
	v->X *= scale;
	v->Y *= scale;
	v->Z *= scale;
}

Vector3 V3_Normalized(Vector3 v)
{
	return V3_Mult(v, V3_InvLength(v));
}

float V3_Dot(Vector3 left, Vector3 right)
{
    return left.X * right.X + left.Y * right.Y + left.Z * right.Z;
}

Vector3 V3_Cross(Vector3 left, Vector3 right)
{
    return (Vector3){left.Y * right.Z - left.Z * right.Y,
        		  left.Z * right.X - left.X * right.Z,
        		  left.X * right.Y - left.Y * right.X};
}

bool V3_Equals(Vector3 x, Vector3 y)
{
    return x.X == y.X && x.Y == y.Y && x.Z == y.Z;
}

int V3_ToString(char *str, Vector3 v)
{
	return sprintf(str, "(%f, %f, %f)", v.X, v.Y, v.Z);
}

Vector3 V3_Rotate(Vector3 left, Vector3 right)
{
    return (Vector3){left.X * right.X - left.Y * right.Y - left.Z * right.Z,
    			  left.Y * right.X + left.X * right.Y,
    			  left.Z * right.X + left.X * right.Z};
}

Vector3 V3_RotateConj(Vector3 left, Vector3 right)
{
    return (Vector3){left.X * right.X + left.Y * right.Y + left.Z * right.Z,
				  left.Y * right.X - left.X * right.Y,
				  left.Z * right.X - left.X * right.Z};
}

//Vector4

Vector4 V4_Add(Vector4 x, Vector4 y)
{
    return (Vector4){x.X + y.X, x.Y + y.Y, x.Z + y.Z, x.W + y.W};
}
Vector4 V4_Sub(Vector4 x, Vector4 y)
{
    return (Vector4){x.X - y.X, x.Y - y.Y, x.Z - y.Z, x.W - y.W};
}

Vector4 V4_Opposed(Vector4 v)
{
	return (Vector4){-v.X, -v.Y, -v.Z, -v.W};
}
Vector4 V4_Mult(Vector4 v, float y)
{
    return (Vector4){v.X * y, v.Y * y, v.Z * y, v.W * y};
}

Vector4 V4_Div(Vector4 v, float y)
{
	float inv = 1.0f / y;
    return (Vector4){v.X * inv, v.Y * inv, v.Z * inv, v.W * inv};
}

float V4_Length(Vector4 v)
{
	return Sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z + v.W * v.W);
}

float V4_LengthSquared(Vector4 v)
{
	return v.X * v.X + v.Y * v.Y + v.Z * v.Z + v.W * v.W;
}

float V4_InvLength(Vector4 v)
{
	return InvSqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z + v.W * v.W);
}

void V4_Normalize(Vector4 *v)
{
	float scale = V4_InvLength(*v);
	v->X *= scale;
	v->Y *= scale;
	v->Z *= scale;
	v->W *= scale;
}

Vector4 V4_Normalized(Vector4 v)
{
	return V4_Mult(v, V4_InvLength(v));
}

float V4_Dot(Vector4 left, Vector4 right)
{
    return left.X * right.X + left.Y * right.Y + left.Z * right.Z + left.W * right.W;
}

bool V4_Equals(Vector4 x, Vector4 y)
{
	return x.X == y.X && x.Y == y.Y && x.Z == y.Z && x.W == y.W;
}

int V4_ToString(char *str, Vector4 v)
{
	return sprintf(str, "{%f, %f, %f, %f}", v.X, v.Y, v.Z, v.W);
}