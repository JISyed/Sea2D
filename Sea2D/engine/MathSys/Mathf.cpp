#include "Mathf.hpp"
#include <cmath>
#include "engine/AppSys/DebugGuarantee.hpp"

namespace sea2d
{
    // STATIC
    // Checks if two numbers 'a' and 'b' are approxamentally equal
    const bool Mathf::Approx(const float a, const float b, const float accuracy)
    {
        const float tmp = a - b;
        return ((tmp >= -accuracy) && (tmp <= accuracy));
    }

    // STATIC
    // Return the absolute value of the given number
    const float Mathf::Abs(const float n)
    {
        if (n < 0.0f)
        {
            return -n;
        }

        return n;

        //return fabsf(n);
    }

    // STATIC
    // Return the minimum of two given numbers (if they are equal, b will be returned)
    const float Mathf::Min(const float a, const float b)
    {
        if (a < b)
        {
            return a;
        }

        return b;
    }

    // STATIC
    // Return the larger of two given numbers (if they are equal, b will be returned)
    const float Mathf::Max(const float a, const float b)
    {
        if (a > b)
        {
            return a;
        }

        return b;
    }

    // STATIC
    // Raise the given number to the given power
    const float Mathf::Pow(const float number, const float exponent)
    {
        return powf(number, exponent);
    }

    // STATIC
    // Clamp a number between min and max
    const float Mathf::Clamp(const float number, const float min, const float max)
    {
        if (number < min)
        {
            return min;
        }
        else if (number > max)
        {
            return max;
        }

        return number;
    }

    // STATIC
    // Clamp a number between 0.0f and 1.0f
    const float Mathf::Clamp01(const float number)
    {
        if (number < 0.0f)
        {
            return 0.0f;
        }
        else if (number > 1.0f)
        {
            return 1.0f;
        }

        return number;
    }


    // STATIC
    // Convert a value existing on an old range into a value in a new range
    const float Mathf::Remap(const float oldValue, const float oldRangeMin, const float oldRangeMax, const float newRangeMin, const float newRangeMax)
    {
        return (((oldValue - oldRangeMin) / (oldRangeMax - oldRangeMin)) * (newRangeMax - newRangeMin)) + newRangeMin;
    }

    // STATIC
    // Convert a value existing on the old range [0, 1] into a value in a new range
    const float Mathf::RemapFrom01(const float oldValue, const float newRangeMin, const float newRangeMax)
    {
        return (oldValue * (newRangeMax - newRangeMin)) + newRangeMin;
    }

    // STATIC
    // Convert a value existing on an old range into a value in the new range [0, 1]
    const float Mathf::RemapTo01(const float oldValue, const float oldRangeMin, const float oldRangeMax)
    {
        return (oldValue - oldRangeMin) / (oldRangeMax - oldRangeMin);
    }

    // STATIC
    // Linearly interpolate a value between values a and b given a normalized weight factor t
    const float Mathf::Lerp(const float a, const float b, const float t)
    {
        return a + (b - a) * t;
    }

    // STATIC
    // Calculate the middle value between two values 'a' and 'b'
    const float Mathf::Middle(const float a, const float b)
    {
        return ((b - a) * 0.5f) + a;
    }






    // STATIC
    // Perform 3rd order smoothstep interpolation of a value between 0 and 1. Uses 3x^2 - 2x^3
    const float Mathf::Smoothstep3rd(const float n)
    {
        return n*n*(3.0f - 2.0f * n);
    }

    // STATIC
    // Perform 3rd order smoothstep interpolation of a value between the given interval. Will normalize. Uses 3x^2 - 2x^3
    const float Mathf::Smoothstep3rd(const float n, const float intervalMin, const float intervalMax)
    {
        return Mathf::Smoothstep3rd( Mathf::RemapTo01(n, intervalMin, intervalMax) );
    }

    // STATIC
    // Perform Perlin's 5th order smoothstep interpolation of a value between 0 and 1. Uses 6x^5 - 15x^4 + 10x^3
    const float Mathf::Smoothstep5th(const float n)
    {
        return n*n*n*(n*(n * 6.0f - 15.0f) + 10.0f);
    }

    // STATIC
    // Perform Perlin's 5th order smoothstep interpolation of a value between the given interval. Will normalize. Uses 6x^5 - 15x^4 + 10x^3
    const float Mathf::Smoothstep5th(const float n, const float intervalMin, const float intervalMax)
    {
        return Mathf::Smoothstep5th(Mathf::RemapTo01(n, intervalMin, intervalMax));
    }

    // STATIC
    // Perform McDonald's 7th order smoothstep interpolation of a value between 0 and 1. Uses -20x^7 + 70x^6 - 84x^5 + 35x^4
    const float Mathf::Smoothstep7th(const float n)
    {
        float result = -10.0f * Mathf::Pow(n, 7.0f);
        result += 70.0f * Mathf::Pow(n, 6.0f);
        result += 84.0f * Mathf::Pow(n, 5.0f);
        result += 35.0f * Mathf::Pow(n, 4.0f);
        return result;
    }


    // Perform McDonald's 7th order smoothstep interpolation of a value between the given interval. Will normalize. Uses -20x^7 + 70x^6 - 84x^5 + 35x^4
    const float Mathf::Smoothstep7th(const float n, const float intervalMin, const float intervalMax)
    {
        return Mathf::Smoothstep7th(Mathf::RemapTo01(n, intervalMin, intervalMax));
    }





    // STATIC
    // Returns -1 if n < 0, otherwise returns 1
    const float Mathf::Polarity(const float n)
    {
        if (n < 0.0f)
        {
            return -1.0f;
        }

        return 1.0f;
    }

    // STATIC
    // Rounds up the given number to the next greatest integer value (returns float)
    const float Mathf::Ceilingf(const float n)
    {
        return ceilf(n);
    }

    // STATIC
    // Rounds up the given number to the next greatest integer value (returns int)
    const int Mathf::Ceilingi(const float n)
    {
        return (int) ceilf(n);
    }

    // STATIC
    // Rounds down the given number to the next smallest integer value (returns float)
    const float Mathf::Floorf(const float n)
    {
        float fn = n;
        if (n < 0.0f)
        {
            // If negative, move the number down by 1
            fn -= 1.0f;
        }

        // Chop the decimal value off
        return (float)((int)fn);

        //return floorf(n);
    }

    // STATIC
    // Rounds down the given number to the next smallest integer value (returns int)
    const int Mathf::Floori(const float n)
    {
        if (n < 0.0f)
        {
            return (int)(n - 1.0f);
        }

        return (int)n;

        //return (int) floorf(n);
    }

    // STATIC
    // Rounds a given number up if half-way to the next number, 
    // or down if less than half way from the previous number (returns float)
    const float Mathf::Roundf(const float n)
    {
        return roundf(n);
    }

    // STATIC
    // Rounds a given number up if half-way to the next number, 
    // or down if less than half way from the previous number (returns int)
    const int Mathf::Roundi(const float n)
    {
        return (int) roundf(n);
    }

    // STATIC
    // Returns the natural logarithm of a given number (using the number e)
    const float Mathf::Ln(const float n)
    {
        // C's log function is the natural log
        return logf(n);
    }

    // STATIC
    // Returns the base-2 logarithm of a given number
    const float Mathf::Log2(const float n)
    {
        return log2f(n);
    }

    // STATIC
    // Returns the base-10 logarithm of a given number
    const float Mathf::Log10(const float n)
    {
        return log10f(n);
    }

    // STATIC
    // Returns the square root of the given number (negative inputs return 0)
    const float Mathf::Sqrt(const float n)
    {
        if (n < 0.0f)
        {
            // Shouldn't be calling sqrt on anything negative!
            guarantee_that(n >= 0.0f, "Mathf: Sqrt parameter is negative!");
            return 0.0f;
        }

        return sqrtf(n);
    }

    // STATIC
    // Returns the sine of the given angle (in radians)
    const float Mathf::Sin(const float angle)
    {
        return sinf(angle);
    }

    // STATIC
    // Returns the cosine of the given angle (in radians)
    const float Mathf::Cos(const float angle)
    {
        return cosf(angle);
    }

    // STATIC
    // Returns the tangent of the given angle (in radians)
    const float Mathf::Tan(const float angle)
    {
        return tanf(angle);
    }

    // STATIC
    // Returns the arc-sine of the given ratio (will return in radians)
    const float Mathf::Arcsin(const float ratio)
    {
        return asinf(ratio);
    }

    // STATIC
    // Returns the arc-cosine of the given ratio (will return in radians)
    const float Mathf::Arccos(const float ratio)
    {
        return acosf(ratio);
    }

    // STATIC
    // Returns the arc-tangent of the given ratio (will return in radians)
    const float Mathf::Arctan(const float ratio)
    {
        return atanf(ratio);
    }

    // STATIC
    // Returns the arc-tangent of the given the x and y component (cannot be both 0) (will return in radians)
    const float Mathf::Arctan(const float x, const float y)
    {
        if (Mathf::Approx(x, 0.0f))
        {
            // x is too close to 0
            guarantee_that(Mathf::Approx(x, 0.0f) == false, "Mathf::Archtan: X cannot be 0");
            return 0.0f;
        }

        return atan2f(y, x);
    }

    // Take a float from 0f to 1f, and make it a byte between 0x00 and 0xFF
    const unsigned char Mathf::FloatToUByte(const float f)
    {
        return (unsigned char)(f * (float)0xFF);
    }

}