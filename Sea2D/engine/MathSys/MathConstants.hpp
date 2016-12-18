#ifndef ENGINE_MATH_CONSTANTS_H
#define ENGINE_MATH_CONSTANTS_H

namespace sea2d
{
    /// A collection of important numerical constants
    class MathConstants
    {
    public:

        //
        // Float Constants
        //
        
        static const float Pi;				///< Ratio of circumferance of circle to its diameter
        static const float HalfPi;          ///< (1/2) * Pi
        static const float ThirdPi;         ///< (1/3) * Pi
        static const float FourthPi;        ///< (1/4) * Pi
        static const float EighthPi;        ///< (1/8) * Pi
        static const float TwoThirdPi;      ///< (2/3) * Pi
        static const float ThreeFourthPi;   ///< (3/4) * Pi
        static const float Tau;				///< Tau == 2 * Pi
        static const float Epsilon;			///< Smallest floating point number before zero
        static const float DegToRad;		///< Constant to convert degrees to radians
        static const float RadToDeg;		///< Constant to convert radians to degrees
        static const float fMin;			///< Lowest floating point number
        static const float fMax;			///< Largest floating point number
        static const float InvSqrtOf2;		///< 1 / sqrt(2)
        static const float e;				///< Base of natural logarithm

        
        //
        // Int Constants
        //
        
        static const int iMin;				///< Lowest 32-bit integer
        static const int iMax;				///< Largetst 32-bit integer
    };
}
#endif