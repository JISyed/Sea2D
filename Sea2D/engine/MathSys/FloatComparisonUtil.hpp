#ifndef ENGINE_MATH_FLOAT_COMPARISON_UTIL_H
#define ENGINE_MATH_FLOAT_COMPARISON_UTIL_H

#include "MathConstants.hpp"

namespace sea2d
{
	/// Float comparison utility functions
	class FloatComparisonUtil
	{
	public:
		/// f1 == f2
        static bool isEqual(const float a, const float b, const float epsilon = MathConstants::Epsilon);
		
		/// f1 != f2
		static bool isNotEqual(const float a, const float b, const float epsilon = MathConstants::Epsilon);
		
		/// f1 == 1.0f
		static bool isOne(const float a, const float epsilon = MathConstants::Epsilon);
		
		/// f1 != 0.0f
		static bool isNonZero(const float a, const float epsilon = MathConstants::Epsilon);
		
		/// f1 == 0.0f
		static bool isZero(const float a, const float epsilon = MathConstants::Epsilon);
	};
}
#endif