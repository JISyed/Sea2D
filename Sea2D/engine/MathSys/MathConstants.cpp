#include "MathConstants.hpp"
#include <cmath>
#include <climits>
#include <cfloat>

namespace sea2d
{
    /// Not pie
    const float MathConstants::Pi = 3.1415926535f;
    
    /// (1/2) * Pi
    const float MathConstants::HalfPi = 1.5707963268f;
    
    /// (1/3) * Pi
    const float MathConstants::ThirdPi = 1.0471975512f;
    
    /// (1/4) * Pi
    const float MathConstants::FourthPi = 0.7853981633f;
    
    /// (1/8) * Pi
    const float MathConstants::EighthPi = 0.3926990816f;
    
    /// (2/3) * Pi
    const float MathConstants::TwoThirdPi = 2.0943951023f;
    
    /// (3/4) * Pi
    const float MathConstants::ThreeFourthPi = 2.3561944901f;
    
    /// Tau == 2 * Pi
    const float MathConstants::Tau = 6.2831853071f;

    /// Smallest floating point number
    const float MathConstants::Epsilon = 0.0001f;

    /// Constant to convert degrees to radians
    const float MathConstants::DegToRad = 0.0174532924f;

    /// Constant to convert radians to degrees
    const float MathConstants::RadToDeg = 57.29578f;

    /// Lowest floating point number
    const float MathConstants::fMin = -FLT_MAX;
    
    /// Largest floating point number
    const float MathConstants::fMax = FLT_MAX;

    /// 1 / sqrt(2)
    const float MathConstants::InvSqrtOf2 = 0.707106781188f;

    
    

    /// Lowest 32-bit integer
    const int MathConstants::iMin = INT_MIN;
    
    /// Largetst 32-bit integer
    const int MathConstants::iMax = INT_MAX;
}