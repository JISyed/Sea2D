#ifndef ENGINE_MATHI_H
#define ENGINE_MATHI_H

namespace sea2d
{
    /// Integer Math Operations
    class Mathi
    {
    public:

        /// Return the absolute value of the given number
        static const int Abs(const int n);

        /// Return the smaller of two given numbers (if they are equal, b will be returned)
        static const int Min(const int a, const int b);

        /// Return the larger of two given numbers (if they are equal, b will be returned)
        static const int Max(const int a, const int b);

        /// Returns -1 if n < 0, otherwise returns 1
        static const int Polarity(const int n);

        /// Raise the given number to the given power (negative numbers not accepted; returns 0)
        static const int Pow(const int number, const int exponent);

        /// Clamp a number between min and max
        static const int Clamp(const int number, const int min, const int max);

        /// Returns true if the given number is a power of 2. Zeros and negatives are not counted!
        static const bool IsPowerOf2(const int n);

        /// Returns the next largest power-of-2 value greater than 'n'. If n is power-of-2, then n will be returned. Negatives will return 0.
        static const int GetNextPowerOf2(int n);
    };
}
#endif