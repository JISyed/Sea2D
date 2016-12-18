//
//  Vector2.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/20/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Vector2.hpp"
#include "engine/MathSys/FloatComparisonUtil.hpp"
#include "engine/MathSys/Mathf.hpp"


namespace sea2d
{
    //
    // Statics
    //
    
    const Vector2 Vector2::Zero(0.0f, 0.0f);
    const Vector2 Vector2::One(1.0f, 1.0f);
    const Vector2 Vector2::Right(1.0f, 0.0f);
    const Vector2 Vector2::Up(0.0f, 1.0f);
    const Vector2 Vector2::Left(-1.0f, 0.0f);
    const Vector2 Vector2::Down(0.0f, -1.0f);
    
    
    
    //
    // Methods
    //
    
    // Default Ctor
    Vector2::Vector2() :
        _x(0.0f),
        _y(0.0f)
    {
    }
    
    // Copy Ctor
    Vector2::Vector2(const Vector2& other) :
        _x(other._x),
        _y(other._y)
    {
    }
    
    // Copy Assignment Overload
    Vector2& Vector2::operator=(const Vector2& rhs)
    {
        if(this != &rhs)
        {
            this->_x = rhs._x;
            this->_y = rhs._y;
        }
        
        return *this;
    }
    
    // Dtor
    Vector2::~Vector2()
    {
    }
    
    /// Multi Float Ctor
    Vector2::Vector2(const float newX, const float newY) :
        _x(newX),
        _y(newY)
    {
    }
    
    /// Ctor for setting both X and Y with same value
    Vector2::Vector2(const float xy) :
        _x(xy),
        _y(xy)
    {
    }
    
    /// Read only getter
    const float Vector2::x() const
    {
        return this->_x;
    }
    
    /// Read only getter
    const float Vector2::y() const
    {
        return this->_y;
    }
    
    /// Writable setter/getter reference
    float& Vector2::x()
    {
        return this->_x;
    }
    
    /// Writable setter/getter reference
    float& Vector2::y()
    {
        return this->_y;
    }
    
    /// Set both X and Y
    void Vector2::set(const float newX, const float newY)
    {
        this->_x = newX;
        this->_y = newY;
    }
    
    
    /// Dot product of two Vector2's
    const float Vector2::dot(const Vector2& other) const
    {
        return (this->_x * other._x) + (this->_y * other._y);
    }
    
    /// Do the scalar 2D cross product of two 2D vectors.
    /// http://stackoverflow.com/questions/243945/calculating-a-2d-vectors-cross-product
    const float Vector2::scalarCross(const Vector2& other) const
    {
        return (this->_x * other._y) - (this->_y * other._x);
    }
    
    /// Normalize this vector
    void Vector2::normalize()
    {
        const float magnSqr = this->magnitudeSquare();
        if (FloatComparisonUtil::isZero(magnSqr))
        {
            // Cannot normalize a zero vector
            return;
        }
        const float magn = Mathf::Sqrt(magnSqr);
        
        this->_x /= magn;
        this->_y /= magn;
    }
    
    /// Get a normalized version of this vector
    const Vector2 Vector2::getNormalized() const
    {
        const float magnSqr = this->magnitudeSquare();
        if (FloatComparisonUtil::isZero(magnSqr))
        {
            // Cannot normalize a zero vector
            return Vector2(0.0f);
        }
        const float magn = Mathf::Sqrt(magnSqr);
        
        return Vector2(this->_x / magn, this->_y / magn);
    }
    
    /// Get the length of this vector
    const float Vector2::magnitude() const
    {
        return Mathf::Sqrt(this->magnitudeSquare());
    }
    
    /// Get the squared length of this vector (faster than non-squared)
    const float Vector2::magnitudeSquare() const
    {
        return (this->_x * this->_x) + (this->_y * this->_y);
    }
    
    /// Get the angle (in radians) between this vector and the given other vector
    const float Vector2::getAngle(const Vector2& other) const
    {
        const float lhsVectMagnSq = this->magnitudeSquare();
        const float rhsVectMagnSq = other.magnitudeSquare();
        
        if (FloatComparisonUtil::isZero(lhsVectMagnSq) || FloatComparisonUtil::isZero(rhsVectMagnSq))
        {
            // Cannot get an angle for a zero vector
            return 0.0f;
        }
        return Mathf::Arccos(this->dot(other) / (Mathf::Sqrt(lhsVectMagnSq) * Mathf::Sqrt(rhsVectMagnSq)));
    }
    
    /// Return a perpendicular vector -90 degrees from this vector
    const Vector2 Vector2::getPerpendicular() const
    {
        return Vector2(this->_y, -(this->_x));
    }
    
    /// Rotate this vector by a given angle (in radians)
    void Vector2::rotate(const float angle)
    {
        const float C = Mathf::Cos(angle);
        const float S = Mathf::Sin(angle);
        
        const float newX = (this->x() * C) - (this->y() * S);
        const float newY = (this->x() * S) + (this->y() * C);
        
        this->set(newX, newY);
    }
    
    /// Get a rotated vector of this one by a given angle (in radians)
    const Vector2 Vector2::getRotated(const float angle) const
    {
        //Vector2 result(0.0f, 0.0f);
        
        const float C = Mathf::Cos(angle);
        const float S = Mathf::Sin(angle);
        
        //result.x() = (this->x() * C) - (this->y() * S);
        //result.y() = (this->x() * S) + (this->y() * C);
        
        return Vector2((this->x() * C) - (this->y() * S) ,
                       (this->x() * S) + (this->y() * C) ) ;
    }
    
    
    
    
    /// Is this vector equal to the other?
    const bool Vector2::isEqual(const Vector2& other, const float floatTolerance) const
    {
        // If the X's are not the same
        if (FloatComparisonUtil::isNotEqual(this->_x, other._x, floatTolerance))
        {
            // Cannot be equal vectors
            return false;
        }
        
        // If the Y's are not the same
        if (FloatComparisonUtil::isNotEqual(this->_y, other._y, floatTolerance))
        {
            // Cannot be equal vectors
            return false;
        }
        
        // If you're here, the vectors were equal enough
        return true;
    }
    
    /// Is this vector a Zero vector?
    const bool Vector2::isZero(const float floatTolerance) const
    {
        // If the X's are not the same
        if (!FloatComparisonUtil::isZero(this->_x, floatTolerance))
        {
            // Cannot be equal vectors
            return false;
        }
        
        // If the Y's are not the same
        if (!FloatComparisonUtil::isZero(this->_y, floatTolerance))
        {
            // Cannot be equal vectors
            return false;
        }
        
        // If you're here, the vectors were equal enough
        return true;
    }
    
    
    
    
    /// Unary + operator overload
    const Vector2 Vector2::operator+() const
    {
        return Vector2(this->_x, this->_y);
    }
    
    /// Unary - operator overload
    const Vector2 Vector2::operator-() const
    {
        return Vector2(-(this->_x), -(this->_y));
    }
    
    
    
    
    /// Add two vectors together
    const Vector2 Vector2::operator+(const Vector2& rhs) const
    {
        return Vector2(this->_x + rhs._x, this->_y + rhs._y);
    }
    
    /// Add two vectors together
    Vector2& Vector2::operator+=(const Vector2& rhs)
    {
        this->_x += rhs._x;
        this->_y += rhs._y;
        
        return *this;
    }
    
    

    
    /// Subtract two vectors together
    const Vector2 Vector2::operator-(const Vector2& rhs) const
    {
        return Vector2(this->_x - rhs._x, this->_y - rhs._y);
    }
    
    /// Subtract two vectors together
    Vector2& Vector2::operator-=(const Vector2& rhs)
    {
        this->_x -= rhs._x;
        this->_y -= rhs._y;
        
        return *this;
    }
    
    
    
    

    
    /// Scalar multiplication
    const Vector2 Vector2::operator*(const float scalarRhs) const
    {
        return Vector2(this->_x * scalarRhs, this->_y * scalarRhs);
    }
    
    /// Scalar multiplication
    Vector2& Vector2::operator*=(const float scalarRhs)
    {
        this->_x *= scalarRhs;
        this->_y *= scalarRhs;
        
        return *this;
    }
    
    // FRIEND
    /// Scalar multiplication
    const Vector2 operator*(const float scalarLhs, const Vector2& vectRhs)
    {
        return Vector2(vectRhs._x * scalarLhs, vectRhs._y * scalarLhs);
    }
    
    

    /// Scalar division
    const Vector2 Vector2::operator/(const float scalarRhs) const
    {
        return Vector2(this->_x / scalarRhs, this->_y / scalarRhs);
    }
    
    /// Scalar division
    Vector2& Vector2::operator/=(const float scalarRhs)
    {
        this->_x /= scalarRhs;
        this->_y /= scalarRhs;
        
        return *this;
    }
    
    
    
    
  
    
    // STATIC
    /// Linerarly interpolate between vector a and b given a normalized value t
    void Vector2::Lerp(Vector2& out, const Vector2& a, const Vector2& b, const float t)
    {
        /// lerpVect = (1-t)*a + t*b
        out = (a*(1 - t)) + (b*t);
    }
    
}