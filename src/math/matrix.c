#include <math/matrix.h>
#include <math/vector.h>
#include <math/math.h>
#include <string.h>
//Constant declaration

#define M3_IDENTITY \
{ \
	.Row0 = { .X = 1.0f, .Y = 0.0f, .Z = 0.0f }, \
	.Row1 = { .X = 0.0f, .Y = 1.0f, .Z = 0.0f }, \
	.Row2 = { .X = 0.0f, .Y = 0.0f, .Z = 1.0f } \
}

#define M3_ZERO \
{ \
	.Row0 = { .X = 0.0f, .Y = 0.0f, .Z = 0.0f }, \
	.Row1 = { .X = 0.0f, .Y = 0.0f, .Z = 0.0f }, \
	.Row2 = { .X = 0.0f, .Y = 0.0f, .Z = 0.0f } \
}

#define M4_IDENTITY \
{ \
	.Row0 = { .X = 1.0f, .Y = 0.0f, .Z = 0.0f, .W = 0.0f }, \
	.Row1 = { .X = 0.0f, .Y = 1.0f, .Z = 0.0f, .W = 0.0f }, \
	.Row2 = { .X = 0.0f, .Y = 0.0f, .Z = 1.0f, .W = 0.0f }, \
	.Row3 = { .X = 0.0f, .Y = 0.0f, .Z = 0.0f, .W = 1.0f } \
}

#define M4_ZERO \
{ \
	.Row0 = { .X = 0.0f, .Y = 0.0f, .Z = 0.0f, .W = 0.0f }, \
	.Row1 = { .X = 0.0f, .Y = 0.0f, .Z = 0.0f, .W = 0.0f }, \
	.Row2 = { .X = 0.0f, .Y = 0.0f, .Z = 0.0f, .W = 0.0f }, \
	.Row3 = { .X = 0.0f, .Y = 0.0f, .Z = 0.0f, .W = 0.0f } \
}

const Matrix3 M3_Identity = M3_IDENTITY;
const Matrix3 M3_Zero = M3_ZERO;
const Matrix4 M4_Identity = M4_IDENTITY;
const Matrix4 M4_Zero = M4_ZERO;

//Matrix3 public methods

float M3_Determinant(Matrix3 *mat)
{
	float 	m11 = mat->Row0.X, m12 = mat->Row0.Y, m13 = mat->Row0.Z,
    		m21 = mat->Row1.X, m22 = mat->Row1.Y, m23 = mat->Row1.Z,
    		m31 = mat->Row2.X, m32 = mat->Row2.Y, m33 = mat->Row2.Z;

    return m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32
         - m13 * m22 * m31 - m11 * m23 * m32 - m12 * m21 * m33;
}

Vector3 M3_MainDiagonal(Matrix3 *mat)
{
	return (Vector3){mat->Row0.X, mat->Row1.Y, mat->Row2.Z};
}

Vector3 M3_Column0(Matrix3 *mat)
{
	return (Vector3){mat->Row0.X, mat->Row1.X, mat->Row2.X};
}

Vector3 M3_Column1(Matrix3 *mat)
{
	return (Vector3){mat->Row0.Y, mat->Row1.Y, mat->Row2.Y};
}

Vector3 M3_Column2(Matrix3 *mat)
{
	return (Vector3){mat->Row0.Z, mat->Row1.Z, mat->Row2.Z};
}

void M3_CreateFromAxisAngle(Vector3 axis, float angle, Matrix3 *out)
{
    V3_Normalize(&axis);
    float axisX = axis.X, axisY = axis.Y, axisZ = axis.Z;

    float cos = Cos(-angle);
    float sin = Sin(-angle);
    float t = 1.0f - cos;

    float tXX = t * axisX * axisX,
    tXY = t * axisX * axisY,
    tXZ = t * axisX * axisZ,
    tYY = t * axisY * axisY,
    tYZ = t * axisY * axisZ,
    tZZ = t * axisZ * axisZ;

    float sinX = sin * axisX,
    sinY = sin * axisY,
    sinZ = sin * axisZ;

    *out = (Matrix3)
    {
    	.Row0.X = tXX + cos,
		.Row0.Y = tXY - sinZ,
		.Row0.Z = tXZ + sinY,
		.Row1.X = tXY + sinZ,
		.Row1.Y = tYY + cos,
		.Row1.Z = tYZ - sinX,
		.Row2.X = tXZ - sinY,
		.Row2.Y = tYZ + sinX,
		.Row2.Z = tZZ + cos
	};
}

void M3_CreateScale(Vector3 scale, Matrix3 *out)
{
	*out = M3_Zero;

	out->Row0.X = scale.X;
	out->Row1.Y = scale.Y;
	out->Row2.Z = scale.Z;
}

void M3_Mult(Matrix3 *left, Matrix3 *right, Matrix3 *out)
{
	float   lM11 = left->Row0.X, lM12 = left->Row0.Y, lM13 = left->Row0.Z,
            lM21 = left->Row1.X, lM22 = left->Row1.Y, lM23 = left->Row1.Z,
            lM31 = left->Row2.X, lM32 = left->Row2.Y, lM33 = left->Row2.Z,
            rM11 = right->Row0.X, rM12 = right->Row0.Y, rM13 = right->Row0.Z,
            rM21 = right->Row1.X, rM22 = right->Row1.Y, rM23 = right->Row1.Z,
            rM31 = right->Row2.X, rM32 = right->Row2.Y, rM33 = right->Row2.Z;
            
    *out = (Matrix3)
    {
    	.Row0.Y = ((lM11 * rM12) + (lM12 * rM22)) + (lM13 * rM32),
	    .Row0.Z = ((lM11 * rM13) + (lM12 * rM23)) + (lM13 * rM33),
	    .Row0.X = ((lM11 * rM11) + (lM12 * rM21)) + (lM13 * rM31),
	    .Row1.Y = ((lM21 * rM12) + (lM22 * rM22)) + (lM23 * rM32),
	    .Row1.X = ((lM21 * rM11) + (lM22 * rM21)) + (lM23 * rM31),
	    .Row1.Z = ((lM21 * rM13) + (lM22 * rM23)) + (lM23 * rM33),
	    .Row2.X = ((lM31 * rM11) + (lM32 * rM21)) + (lM33 * rM31),
	    .Row2.Y = ((lM31 * rM12) + (lM32 * rM22)) + (lM33 * rM32),
	    .Row2.Z = ((lM31 * rM13) + (lM32 * rM23)) + (lM33 * rM33),
	};
}

bool M3_Invert(Matrix3 *mat, Matrix3 *out)
{
    int colIdx[] = { 0, 0, 0 };
    int rowIdx[] = { 0, 0, 0 };
    int pivotIdx[] = { -1, -1, -1 };
    
    //TODO: Optimize with pointer cast or something
    float inverse[3][3] = {{mat->Row0.X, mat->Row0.Y, mat->Row0.Z},
        {mat->Row1.X, mat->Row1.Y, mat->Row1.Z},
        {mat->Row2.X, mat->Row2.Y, mat->Row2.Z}};
    
    int icol = 0;
    int irow = 0;
    for (int i = 0; i < 3; i++)
    {
        float maxPivot = 0.0f;
        for (int j = 0; j < 3; j++)
        {
            if (pivotIdx[j] != 0)
            {
                for (int k = 0; k < 3; ++k)
                {
                    if (pivotIdx[k] == -1)
                    {
                        float absVal = Abs(inverse[j][k]);
                        if (absVal > maxPivot)
                        {
                            maxPivot = absVal;
                            irow = j;
                            icol = k;
                        }
                    }
                    else if (pivotIdx[k] > 0)
                    {
                        return false;
                    }
                }
            }
        }
        
        pivotIdx[icol]++;
        
        if (irow != icol)
        {
            for (int k = 0; k < 3; ++k)
            {
                float f = inverse[irow][k];
                inverse[irow][k] = inverse[icol][k];
                inverse[icol][k] = f;
            }
        }
        
        rowIdx[i] = irow;
        colIdx[i] = icol;
        
        float pivot = inverse[icol][icol];
        
        if (pivot == 0.0f)
        {
            return false;
        }
        
        float oneOverPivot = 1.0f / pivot;
        inverse[icol][icol] = 1.0f;
        for (int k = 0; k < 3; ++k)
            inverse[icol][k] *= oneOverPivot;
        
        for (int j = 0; j < 3; ++j)
        {
            if (icol != j)
            {
                float f = inverse[j][icol];
                inverse[j][icol] = 0.0f;
                for (int k = 0; k < 3; ++k)
                    inverse[j][k] -= inverse[icol][k] * f;
            }
        }
    }
    
    for (int j = 2; j >= 0; --j)
    {
        int ir = rowIdx[j];
        int ic = colIdx[j];
        for (int k = 0; k < 3; ++k)
        {
            float f = inverse[k][ir];
            inverse[k][ir] = inverse[k][ic];
            inverse[k][ic] = f;
        }
    }
    
    //TODO: If inverse points to mat this shouldn't be necessary
    *out = (Matrix3)
    {
    	.Row0.X = inverse[0][0],
	    .Row0.Y = inverse[0][1],
	    .Row0.Z = inverse[0][2],
	    .Row1.X = inverse[1][0],
	    .Row1.Y = inverse[1][1],
	    .Row1.Z = inverse[1][2],
	    .Row2.X = inverse[2][0],
	    .Row2.Y = inverse[2][1],
	    .Row2.Z = inverse[2][2],
	};

	return true;
}

void M3_Transpose(Matrix3 *mat, Matrix3 *out)
{
	out->Row0 = M3_Column0(mat);
	out->Row1 = M3_Column1(mat);
	out->Row2 = M3_Column2(mat);
}

bool M3_Equals(Matrix3 *left, Matrix3 *right)
{
	return memcmp(left, right, sizeof(Matrix3)) == 0;
}

int M3_ToString(Matrix3 *v, char *str)
{
	char *start = str;
	str += V3_ToString(str, v->Row0);
	str += V3_ToString(str, v->Row1);
	str += V3_ToString(str, v->Row2);

	return (int)(str - start);
}
