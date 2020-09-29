#include <math/math.h>
#include <stdbool.h>
#include <stdint.h>

typedef union
{
    uint_fast32_t u;
    int_fast32_t i;
    float f;
} trans;

Vector3 AngleToDirection(Vector3 v)
{
	float sp = Sin(v.X * PI / 180.0f);
	float sy = Sin(v.Y * PI / 180.0f);
	float cy = Cos(v.Y * PI / 180.0f);
    return V3_Normalized((Vector3){sy, sp, cy});
}

static float Cos_52(float x)
{
    const float c1 = 0.9999932946f;
    const float c2 = -0.4999124376f;
    const float c3 = 0.0414877472f;
    const float c4 = -0.0012712095f;

    register float x2 = x * x;
    return (c1 + x2 * (c2 + x2 * (c3 + c4 * x2))); 
}

static float Cotg_52(float x)
{
    const float c1 = -0.332930053f;
    const float c2 = -0.0242168088f;

    register float x2 = x * x;
    return (1.0f / x + x * (c1 + c2 * x2));
}

static float Tan_52(float x)
{
    const float c1 = 0.334961658f;
    const float c2 = 0.11806635f;
    const float c3 = 0.092151584f;

    register float x2 = x * x;
    return (x * (1 + x2 * (c1 + x2 * (c2 + c3 * x2))));
}

static float Atan_66(float x)
{
    const float c1 = 1.6867629106f;
    const float c2 = 0.4378497304f;
    const float c3 = 1.6867633134f;

    register float x2 = x * x;
    return (x * (c1 + x2 * c2) / (c3 + x2));
} 

static float Exp_52(float x)
{
    const float c1 = 0.496879224f;
    const float c2 = 0.190809553f;

    return (1 + x * (1 + x * (c1 + x * c2)));
}

float Sin(float x)
{
	bool sign = true;
	if (x < 0)
	{
   		x = -x;
		sign = false;
	}
	if (x >= 2.0f * PI) x = fmodf(x, 2.0f * PI);
	if (x < PI) x -= PI / 2.0f;
	else
	{
		x -= 3.0f * PI / 2.0f;
		sign = !sign;
	}
	return (sign) ? Cos_52(x) : -Cos_52(x);
}

float Cos(float x)
{
    bool sign = true;
    x = Abs(x);
    if (x >= PI * 2.0f) x = fmodf(x, 2.0f * PI);
    if (x <= PI / 2.0f) ;
    else if (x <= (3.0f * PI / 2.0f))
    {
        x -= PI;
        sign = false;
    }
    else x -= 2.0f * PI;
    return (sign) ? Cos_52(x) : -Cos_52(x);
}

float Tan(float x)
{
    bool sign = true;
    if (x < 0.0f)
    {
        x = -x;
        sign = false;
    }
    if (x >= PI) fmodf(x, PI);
    if (x < PI / 4.0f) return (sign) ? Tan_52(x) : -Tan_52(x);
    if (x < PI / 2.0f) return (sign) ? Cotg_52(PI / 2.0f - x) : -Cotg_52(PI / 2.0f - x);
    if (x < 3.0f * PI / 4.0f) return (sign) ? -Cotg_52(-PI / 2.0f + x) : Cotg_52(-PI / 2.0f + x);
    else return (sign) ? Tan_52(x - PI) : -Tan_52(x - PI);
}

float Asin(float x)
{
    register float isqrt = InvSqrt(1 - x * x);
    return Atan(x*isqrt);
}

float Acos(float x)
{
    register float pid2 = PI / 2.0f;
    register float asin = Asin(x);
    return pid2 - asin;
}

float Atan(float x)
{
    const float tantwelfthpi = 0.2679491924f;
    const float tansixthpi = 0.5773502691f;
    bool sign = false;
    bool complement = false, region = false;

    if (x < 0)
    {
        x = -x;
        sign = true;
        // arctan(-x)=-arctan(x)
    }
    if (x > 1.0)
    {
        x = 1 / x;
        // keep arg between 0 and 1
        complement = true;
    }
    if (x > tantwelfthpi)
    {
        x = (x - tansixthpi) / (1 + tansixthpi * x); // reduce arg to under tan(pi/12)
        region = true;
    }
    x = Atan_66(x);
    // run the approximation
    if (region) x += PI/6;
    // correct for region we're in
    if (complement) x = PI/2 - x;
    // correct for 1/x if we did that
    if (sign) x = -x;
    // correct for negative arg
    return (x);
}

float Exp(float x)
{
    const float CC = 1 / 0.6931471805f;
    const float C = 0.6931471805f;
    int n;
    
    if (x <= C && x >= -C) return Exp_52(x);
    else
    {
        n = (int)(x * CC);
        x = x - (n * C);
        return (n >= 0) ? (1 << n) * Exp_52(x) : Exp_52(x) / (1 << -n);
    }
}

float Exp2(float x)
{
    int integer = (int)x;
    register float decims;

    if(x >= 0.0f)
    {
        decims = x - integer;
    }
    else if(x > -1.0f)
    {
        const float c4 = 0.99827523678536475868f;
        const float c5 = 0.66600757248763093147f;
        const float c6 = 0.16859471730958379345f;

        decims = c4 + x * (c5 + x * c6);
        return decims;
    }
    else
    {
        decims = x - (--integer);
    }
    
    integer <<= 23;

    const float c1 = 1.0017247632146352413f;
    const float c2 = 0.65763627573692668916f;
    const float c3 = 0.33718943461916758689f;

    decims = c1 + decims * (c2 + decims * c3);
    trans conv;
    conv.f = decims;
    conv.i += integer;

    return conv.f;
}

float ExpE(float x)
{
    const float CC = 1 / 0.6931471805F;
    const float C = 0.6931471805F;

    int integer = (int)(x * CC);
    float decims = x - (integer * C);

    if (x >= 0.0f)
    {
        decims = x - integer;
    }
    else if (x > -1.0f)
    {
        const float c4 = 0.99827523678536475868f;
        const float c5 = 0.66600757248763093147f;
        const float c6 = 0.16859471730958379345f;

        decims = c4 + x * (c5 + x * c6);
        return decims;
    }
    else
    {
        decims = x - (--integer);
    }

    integer <<= 23;

    const float c1 = 1.0017247632146352413f;
    const float c2 = 0.65763627573692668916f;
    const float c3 = 0.33718943461916758689f;

    decims = c1 + decims * (c2 + decims * c3);
    trans conv;
    conv.f = decims;
    conv.i += integer;

    return conv.f;
}

float Log(float x)
{
    const float ln2 = 0.693147180559945f;

    if (x <= 0)
    {
        if (x == 0)
        {
            return -INFINITY;
        }
        else return NAN;
    }

    const uint32_t and = ((1u << 23) - 1u);
    const uint32_t mask = (127u - 7u) << 23;

    if (x <= 0)
    {
        if (x == 0)
        {
            return -INFINITY;
        }
        else return 0;
    }

    if (x >= 0.78 && x <= 1.23)
    {
        const float c6 = 0.252546478879892266f;
        const float c7 = -1.0f;
        const float c8 = 4.90676795844667343f;
        const float c9 = 0.491762797020593502f;
        const float c10 = c6 * c7;

        float e = c8 + x;
        float f = c9 + x;
        float d = x * c6 + c10;

        e /= f;

        return d * e;
    }

    trans conv, mant;
    conv.f = x;

    int exp = (int)(conv.u >> 23) - 127 + 7;
    mant.u = ((conv.u & and) | mask);
    x = mant.f;

    const float c1 = 22.1948922659374917f;
    const float c2 = -0.1679107289545606155f;
    const float c3 = 0.01039357194620784662f;
    const float c4 = 0.00552078332627026822f;
    const float c5 = c1 * c2;

    float b = c3 + x;
    float c = c4 + x;
    float a = x * c1 + c5;

    b /= c;
    x = a * b;

    return exp * ln2 + x;
}

float Log2(float x)
{
    const uint32_t and = ((1u << 23) - 1u);
    const uint32_t mask = (127u - 11u) << 23;

    if (x <= 0)
    {
        if (x == 0)
        {
            return -INFINITY;
        }
        else return 0;
    }

    if (x >= 0.78 && x <= 1.23)
    {
        const float c6 = 0.36434755267399f;
        const float c7 = -1.0f;
        const float c8 = 4.9067679584467f;
        const float c9 = 0.49176279702059f;
        const float c10 = c6 * c7;

        float e = c8 + x;
        float f = c9 + x;
        float d = x * c6 + c10;

        e /= f;

        return d * e;
    }

    trans conv, mant;
    conv.f = x;

    int exp = (int)(conv.u >> 23) - 127 + 11;
    mant.u = ((conv.u & and) | mask);
    x = mant.f;

    const float c1 = 512.979642165297071f;
    const float c2 = -0.01815607722238334008f;
    const float c3 = 0.0005225865642748271363f;
    const float c4 = 0.000344607794408429563f;
    const float c5 = c1 * c2;
    
    float b = c3 + x;
    float c = c4 + x;
    float a = x * c1 + c5;

    b /= c;
    x = a * b;

    return exp + x;
}

float Pow2(float base, float exp)
{
    if (base == 2) return Exp2(exp);
    else return Exp2(Log2(base) * exp);
}

float PowE(float base, float exp)
{
    if (base == E) return Exp(exp);
    else return Exp(Log(base) * exp);
}

float Sqrt(float x)
{
    return 1.0f / InvSqrt(x);
    
    //Code ends here

    trans val_int;
    val_int.f = x;

    val_int.i -= 1 << 23; /* Subtract 2^m. */
    val_int.i >>= 1; /* Divide by 2. */
    val_int.i += 1 << 29; /* Add ((b + 1) / 2) * 2^m. */

    return val_int.f; /* Interpret again as float */
}

float InvSqrt(float x)
{
    float xhalf = 0.5f * x;
    trans i;
    i.f = x;              // Read bits as integer.
    i.i = 0x5f375a86 - (i.i >> 1);      // Make an initial guess for Newton-Raphson approximation
    x = i.f;                // Convert bits back to float
    x = x * (1.5f - xhalf * x * x); // Perform left single Newton-Raphson step.
    return x;
}

float fmodf(float x, float mod)
{
	int i = (int)(x / mod);
	float f = x - i * mod;
	if ((x < 0.0f) != (mod < 0.0f))
		f -= mod;
	return f;
}
