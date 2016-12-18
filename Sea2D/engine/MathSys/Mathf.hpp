#ifndef ENGINE_MATHF_H
#define ENGINE_MATHF_H
#include "MathConstants.hpp"

namespace sea2d
{
    /// Floating Point Math Operations
    class Mathf
    {
    public:

        /// Checks if two numbers 'a' and 'b' are approxamentally equal
        static const bool Approx(const float a, const float b, const float accuracy = MathConstants::Epsilon);

        /// Return the absolute value of the given number
        static const float Abs(const float n);

        /// Return the smaller of two given numbers (if they are equal, b will be returned)
        static const float Min(const float a, const float b);

        /// Return the larger of two given numbers (if they are equal, b will be returned)
        static const float Max(const float a, const float b);

        /// Raise the given number to the given power
        static const float Pow(const float number, const float exponent);

        /// Clamp a number between min and max
        static const float Clamp(const float number, const float min, const float max);

        /// Clamp a number between 0.0f and 1.0f
        static const float Clamp01(const float number);

        /// Convert a value existing on an old range into a value in a new range
        static const float Remap(const float oldValue, const float oldRangeMin, const float oldRangeMax, const float newRangeMin, const float newRangeMax);

        /// Convert a value existing on the old range [0, 1] into a value in a new range
        static const float RemapFrom01(const float oldValue, const float newRangeMin, const float newRangeMax);

        /// Convert a value existing on an old range into a value in the new range [0, 1]
        static const float RemapTo01(const float oldValue, const float oldRangeMin, const float oldRangeMax);

        /// Linearly interpolate a value between values a and b given a normalized weight factor t
        static const float Lerp(const float a, const float b, const float t);

        /// Calculate the middle value between two values 'a' and 'b'
        static const float Middle(const float a, const float b);

        /// Perform 3rd order smoothstep interpolation of a value between 0 and 1. Uses 3x^2 - 2x^3
        static const float Smoothstep3rd(const float n);

        /// Perform 3rd order smoothstep interpolation of a value between the given interval. Will normalize. Uses 3x^2 - 2x^3
        static const float Smoothstep3rd(const float n, const float intervalMin, const float intervalMax);

        /// Perform Perlin's 5th order smoothstep interpolation of a value between 0 and 1. Uses 6x^5 - 15x^4 + 10x^3
        static const float Smoothstep5th(const float n);

        /// Perform Perlin's 5th order smoothstep interpolation of a value between the given interval. Will normalize. Uses 6x^5 - 15x^4 + 10x^3
        static const float Smoothstep5th(const float n, const float intervalMin, const float intervalMax);

        /// Perform McDonald's 7th order smoothstep interpolation of a value between 0 and 1. Uses -20x^7 + 70x^6 - 84x^5 + 35x^4
        static const float Smoothstep7th(const float n);

        /// Perform McDonald's 7th order smoothstep interpolation of a value between the given interval. Will normalize. Uses -20x^7 + 70x^6 - 84x^5 + 35x^4
        static const float Smoothstep7th(const float n, const float intervalMin, const float intervalMax);

        /// Returns -1 if n < 0, otherwise returns 1
        static const float Polarity(const float n);

        /// Rounds up the given number to the next greatest integer value (returns float)
        static const float Ceilingf(const float n);

        /// Rounds up the given number to the next greatest integer value (returns int)
        static const int Ceilingi(const float n);

        /// Rounds down the given number to the next smallest integer value (returns float)
        static const float Floorf(const float n);

        /// Rounds down the given number to the next smallest integer value (returns int)
        static const int Floori(const float n);

        /// Rounds a given number up if half-way to the next number,
        /// or down if less than half way from the previous number (returns float)
        static const float Roundf(const float n);

        /// Rounds a given number up if half-way to the next number,
        /// or down if less than half way from the previous number (returns int)
        static const int Roundi(const float n);

        /// Returns the natural logarithm of a given number (using the number e)
        static const float Ln(const float n);

        /// Returns the base-2 logarithm of a given number
        static const float Log2(const float n);

        /// Returns the base-10 logarithm of a given number
        static const float Log10(const float n);

        /// Returns the square root of the given number (negative inputs return 0)
        static const float Sqrt(const float n);

        /// Returns the sine of the given angle (in radians)
        static const float Sin(const float angle);

        /// Returns the cosine of the given angle (in radians)
        static const float Cos(const float angle);

        /// Returns the tangent of the given angle (in radians)
        static const float Tan(const float angle);

        /// Returns the arc-sine of the given ratio (will return in radians)
        static const float Arcsin(const float ratio);

        /// Returns the arc-cosine of the given ratio (will return in radians)
        static const float Arccos(const float ratio);

        /// Returns the arc-tangent of the given ratio (will return in radians)
        static const float Arctan(const float ratio);

        /// Returns the arc-tangent of the given the x and y component (cannot be both 0) (will return in radians)
        static const float Arctan(const float x, const float y);

        /// Take a float from 0f to 1f, and make it a byte between 0x00 and 0xFF (clamping is NOT done here!)
        static const unsigned char FloatToUByte(const float f);
    };
}
#endif