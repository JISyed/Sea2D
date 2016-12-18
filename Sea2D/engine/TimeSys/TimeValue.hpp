//
//  TimeValue.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/12/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef TimeValue_hpp
#define TimeValue_hpp

#include <stdint.h>

namespace sea2d
{
    //
    // Enums
    //
    
    /// Represents one of the basic durations of time to set as a default value for a new TimeValue
    enum class TimeBasis : unsigned int
    {
        Zero,           ///< For constructing a Time of zero.
        Ntsc60Frame,    ///< For constructing one NTSC 60 hz frame of TimeValue.
        Ntsc30Frame,    ///< For constructing half of an NTSC 60 hz frame of TimeValue. */
        PalFrame,       ///< For constructing one PAL 50 hz frame of TimeValue.
        OneMillisecond, ///< For constructing one millisecond of TimeValue.
        OneSecond,      ///< For constructing one second of TimeValue.
        OneMinute,      ///< For constructing one minute of TimeValue.
        OneHour,        ///< For constructing one hour of TimeValue.
        TimeMin,        ///< For constructing the most <i>negative</i> TimeValue that can be represented.
        TimeMax,        ///< For constructing the most positive TimeValue that can be represented.
        InternalTick    ///< For constructing one internal tick defined by implementation
    };
    
    
    //
    // TimeValue class
    //
    
    /// Can represent either a point in time or a duration of time
    class TimeValue
    {
    public:
        
        
        //
        // Constructors / Destructors / Assignment
        //
        
        
        /// Default Ctor. Equal to TimeValue(TimeBasis::Zero)
        TimeValue();
        
        /**
         * Creates the specific amount of Time.
         *
         *  Example:
         *  @code const TimeValue ONE_SECOND( TimeBasis::OneSecond );@endcode
         */
        explicit TimeValue(const TimeBasis duration);
        
        /// Copy Ctor
        TimeValue(const TimeValue& rhs);
        
        /// Copy Assignment
        TimeValue& operator=(const TimeValue& rhs);
        
        /// Destrutor
        ~TimeValue();
        
        
        
        
        //
        // Friends
        //
        
        
        /**
         * @return  The product of the specified float and TimeValue.
         *
         * Example:
         *    @code  const TimeValue halfSecond = 0.5f * TimeValue(TimeBasis::OneSecond);
         */
        friend const TimeValue operator*(const float ratio, const TimeValue & rhs);
        
        /**
         * @return The product of the specified integer and TimeValue.
         *
         * Example:
         *    @code  const TimeValue fourMinutes = 4 * TimeValue(TimeBasis::OneSecond);
         */
        friend const TimeValue operator*(const int ratio, const TimeValue & rhs);

        /**
         * @return The product of the specified long integer and TimeValue.
         *
         * Example:
         *    @code  const TimeValue fourMinutes = 4 * TimeValue(TimeBasis::OneSecond);
         */
        friend const TimeValue operator*(const int64_t ratio, const TimeValue & rhs);

        
        
        
        
        //
        // Comparisons
        //
        
        
        
        /**
         *  @return  true, if this TimeValue is equal to the right-hand side.
         *
         *  Example:
         *   @code assert( TimeValue(TimeBasis::OneHour)   == 60 * TimeValue(TimeBasis::OneMinute) );
         *         assert( TimeValue(TimeBasis::OneMinute) == 60 * TimeValue(TimeBasis::OneSecond) );
         */
        bool operator==(const TimeValue& rhs) const;
        
        /**
         * @return  true, if this TimeValue is not equal to the right-hand side.
         */
        bool operator!=(const TimeValue& rhs) const;
        
        /**
         * @return  true, if this TimeValue is less than the right-hand side.
         *
         * Example:
         * @code bool exampleCheckUnder4Mins( const TimeValue t )
         *       {
         *           return( t < 4 * TimeValue(TimeBasis::OneMinute) );
         *       }
         */
        bool operator<(const TimeValue& rhs) const;
        
        /**
         * @return  true if this TimeValue is less or equal to the right-hand side
         */
        bool operator<=(const TimeValue& rhs) const;
        
        /**
         * @return  true if this TimeValue is greater than the right-hand side.
         */
        bool operator>(const TimeValue& rhs) const;
        
        /**
         * @return  true if this TimeValue is greather than or equal to
         *  the right-hand side.
         */
        bool operator>=(const TimeValue& rhs) const;
        
        
        
        
        
        
        
        //
        // Negation / Addition / Subtraction
        //
        
        
        /**
         * @return  A negative copy of this TimeValue.
         *
         * Example:
         * @code void neverFail( const TimeValue t )
         *       {
         *           assert( t + (-t) == TimeValue(TimeBasis::Zero) );
         *       }
         */
        const TimeValue operator-() const;
        
        /**
         * @return  The sum of this TimeValue and the right-hand side.
         *
         * Example:
         * @code void neverFail( const TimeValue t )
         *       {
         *           assert( t + t == 2 * t );
         *       }
         */
        const TimeValue operator+(const TimeValue& rhs) const;
        
        /**
         * @return  The difference between this TimeValue and the right-hand side.
         *
         * Example:
         * @code void neverFail( const TimeValue t )
         *       {
         *           assert( t - t == TimeValue(TimeBasis::Zero) );
         *       }
         */
        const TimeValue operator-(const TimeValue& rhs) const;
        
        /**
         * Adds the right-hand side to this TimeValue.
         *
         * @return  This TimeValue.
         *
         *  Example:
         *  @code void zeroOutTime( TimeValue& t )
         *        {
         *            t += (-t);
         *            assert( TimeValue(TimeBasis::Zero) == t );
         *        }
         */
        TimeValue& operator+=(const TimeValue& rhs);
        
        /**
         * Subtracts the right-hand side from this TimeValue.
         *
         * @return  This TimeValue.
         *
         *  Example:
         *  @code  void zeroOutTime( TimeValue& t )
         *         {
         *             t -= t;
         *             assert( TimeValue(TimeBasis::Zero) == t );
         *         }
         */
        TimeValue& operator-=(const TimeValue& rhs);
        
        
        
        
        
        
        
        //
        // Multiplication
        //
        
        
        /**
         * @return  The product of this TimeValue and the specified float.
         *
         * Example:
         *  @code  const TimeValue halfSecond = TimeValue(TimeBasis::OneSecond) * 0.5f;
         */
        const TimeValue operator*(const float ratio) const;
        
        /**
         * @return  The product of this TimeValue and the specified integer.
         *
         *  Example:
         *  @code  const TimeValue fourMinutes = TimeValue(TimeBasis::OneMinute) * 4;
         */
        const TimeValue operator*(const int ratio) const;
        
        /**
         * Multiplies this TimeValue by the specified float.
         *
         * @return  This TimeValue.
         *
         * Example:
         * @code   void decayTime( TimeValue& t )
         *         {
         *             t *= 0.95f;
         *         }
         */
        TimeValue& operator*=(const float ratio);
        
        /**
         * Multiplies this Time by the specified integer.
         *
         * @return  This TimeValue.
         *
         * Example:
         * @code   void doubleTime( TimeValue& t )
         *         {
         *             t *= 2;
         *         }
         */
        TimeValue& operator*=(const int ratio);
        
        
        
        
        
        
        
        
        
        //
        // Division
        //
        
        
        /**
         * @return  The ratio of this TimeValue divided by the denominator TimeValue.
         *
         * @remark  Note that dividing by TimeBasis::Zero is undefined.
         */
        float operator/(const TimeValue& denominator) const;
        
        /**
         * @return  The result of dividing this TimeValue and by the
         * specified float.
         *
         * @remark  Note that dividing by zero is undefined.
         */
        const TimeValue operator/(const float denominator) const;
        
        /**
         * @return  The result of dividing this TimeValue by the
         * specified integer.
         *
         * @remark  Note that dividing by zero is undefined.
         */
        const TimeValue operator/(const int denominator) const;
        
        /**
         * Divides this TimeValue by the specified float.
         *
         * @return  This TimeValue.
         *
         * @remark  Note that dividing by zero is undefined.
         */
        TimeValue& operator/=(const float denominator);
        
        /**
         * Divides this TimeValue by the specified integer.
         *
         * @return  This TimeValue.
         *
         * @remark  Note that dividing by zero is undefined.
         */
        TimeValue& operator/=(const int denominator);
        
        
        
        
        
        
        
        //
        // Quotient / Remainder
        //
        
        
        /**
         * @return   The truncated, integral division of the
         * numerator and denominator.  In other words,
         * the result of the division is rounded down to the nearest
         * integer.
         *
         * @remark  Note that dividing by TimeValue(TimeBasis::Zero) is undefined.
         */
        static int quotient(const TimeValue& numerator, const TimeValue& denominator);
        
        /**
         * @return  The remainder of dividing the numerator into the
         * denominator.  This is the equivalent of a modulus operation.
         *
         * @remark  Note that dividing by TimeValue(TimeBasis::Zero) is undefined.
         */
        static const TimeValue remainder(const TimeValue& numerator, const TimeValue& denominator);
        
        
        
        
        //
        // Other Operators
        //
        
        /// Get the time in a readable format given a time basis. (Zero, TimeMin, and TimeMax are invalid parameters)
        const float GetReadableTime(const TimeBasis timeBasis) const;
        
        /// Get the time in a readable format given a time basis. (Zero, TimeMin, and TimeMax are invalid parameters) (Need to pass in an int to get the remaining time in a smaller format)
        const int GetReadableTime(const TimeBasis timeBasis, int& inOutRemainderTime) const;
        
        
    private:
        
        //
        // Private Typedefs
        //
        
        /// Internal representation of time keeping (must be signed)
        typedef int64_t Representation;
        
        
        //
        // Data
        //
        
        /// Internal time value (as int64)
        Representation internalTime;
        
        
        //
        // Private Routines
        //
        
        /// Private Representation Ctor
        explicit TimeValue(const Representation rawTime);
        
        
    };
}
#endif /* TimeValue_hpp */
