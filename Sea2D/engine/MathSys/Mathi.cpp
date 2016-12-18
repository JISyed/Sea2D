#include "Mathi.hpp"
#include <cmath>
#include <stdlib.h>

namespace sea2d
{
    // STATIC
    // Return the absolute value of the given number
    const int Mathi::Abs(const int n)
    {
        return abs(n);
    }

    // STATIC
    // Return the minimum of two given numbers (if they are equal, b will be returned)
    const int Mathi::Min(const int a, const int b)
    {
        if (a < b)
        {
            return a;
        }

        return b;
    }

    // STATIC
    // Return the larger of two given numbers (if they are equal, b will be returned)
    const int Mathi::Max(const int a, const int b)
    {
        if (a > b)
        {
            return a;
        }

        return b;
    }

    // STATIC
    // Returns -1 if n < 0, otherwise returns 1
    const int Mathi::Polarity(const int n)
    {
        if (n < 0)
        {
            return -1;
        }

        return 1;
    }

    // STATIC
    // Raise the given number to the given power
    const int Mathi::Pow(const int number, const int exponent)
    {
        if (number < 0 || exponent < 0)
        {
            return 0;
        }

        if (number == 0 && exponent == 0)
        {
            // This would be undefined, but ints don't know what undefined is.
            return 0;
        }

        if (exponent == 1)
        {
            return 0;
        }

        // Actually calculate the power
        int result = 1;
        for (int i = 1; i < exponent + 1; i++)
        {
            result *= number;
        }

        return result;
    }

    // STATIC
    // Clamp a number between min and max
    const int Mathi::Clamp(const int number, const int min, const int max)
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
    // Returns true if the given number is a power of 2. Zeros and negatives are not counted!
    const bool Mathi::IsPowerOf2(const int n)
    {
        if (n < 2)
        {
            return false;
        }

        // The number AND'ed with its next smaller self should be 0.
        // Ex) 8 (1 0 0 0) & 7 (0 1 1 1) == 0 (0 0 0 0)
        return (n & (n - 1)) == 0;
    }

    // STATIC
    // Returns the next largest power-of-2 value greater than 'n'. If n is power-of-2, then n will be returned
    const int Mathi::GetNextPowerOf2(int n)
    {
        // Credit to Hacker's Delight referenced code here:
        // http://stackoverflow.com/a/365068

        if (n < 0)
        {
            return 0;
        }
        
        --n;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        
        return n + 1;
    }
}