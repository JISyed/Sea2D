#include "FloatComparisonUtil.hpp"

namespace sea2d
{
    // STATIC
	bool FloatComparisonUtil::isEqual(const float a, const float b, const float epsilon)
	{
		const float tmp = a - b;
		return ((tmp >= -epsilon) && (tmp <= epsilon));
	}
    
    // STATIC
	bool FloatComparisonUtil::isNotEqual(const float a, const float b, const float epsilon)
	{
		const float tmp = a - b;
		return ((tmp < -epsilon) || (tmp > epsilon));
	}
    
    // STATIC
	bool FloatComparisonUtil::isOne(const float a, const float epsilon)
	{
		const float tmp = a - 1.0f;
		return ((tmp >= -epsilon) && (tmp <= epsilon));
	}

    // STATIC
	bool FloatComparisonUtil::isNonZero(const float a, const float epsilon)
	{
		return ((a < -epsilon) || (a > epsilon));
	}

    // STATIC
	bool FloatComparisonUtil::isZero(const float a, const float epsilon)
	{
		return ((a >= -epsilon) && (a <= epsilon));
	}

}