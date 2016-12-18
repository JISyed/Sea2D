//
//  Vector2.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/20/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef Vector2_hpp
#define Vector2_hpp
#include "engine/MathSys/MathConstants.hpp"

namespace sea2d
{
    /// Row Major 2-Element Vector
    class Vector2
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor {0,0}
        Vector2();
        
        /// Copy Ctor
        Vector2(const Vector2& other);
        
        /// Copy Assignment
        Vector2& operator=(const Vector2& rhs);
        
        /// Destructor
        ~Vector2();
        
        /// Multi Float Ctor
        Vector2(const float newX, const float newY);
        
        /// Ctor for setting both X and Y with same value
        explicit Vector2(const float xy);
        
        
        
        //
        // Getters
        //
        
        /// Read only getter
        const float x() const;
        
        /// Read only getter
        const float y() const;
        
        
        
        //
        // Setters
        //
        
        /// Writable setter/getter reference
        float& x();
        
        /// Writable setter/getter reference
        float& y();
        
        /// Set both X and Y
        void set(const float newX, const float newY);
        
        
        
        //
        // Vector 2D Exclusive Operators
        //
        
        /// Dot product of two Vector2's
        const float dot(const Vector2& other) const;
        
        /// Do the scalar 2D cross product of two 2D vectors.
        /// Yes this is a thing: http://stackoverflow.com/questions/243945/calculating-a-2d-vectors-cross-product
        const float scalarCross(const Vector2& other) const;
        
        /// Normalize this vector
        void normalize();
        
        /// Get a normalized version of this vector
        const Vector2 getNormalized() const;
        
        /// Get the length of this vector
        const float magnitude() const;
        
        /// Get the squared length of this vector (faster than non-squared)
        const float magnitudeSquare() const;
        
        /// Get the angle (in radians) between this vector and the given other vector
        const float getAngle(const Vector2& other) const;
        
        /// Return a perpendicular vector -90 degrees from this vector
        const Vector2 getPerpendicular() const;
        
        /// Rotate this vector by a given angle (in radians)
        void rotate(const float angle);
        
        /// Get a rotated vector of this one by a given angle (in radians)
        const Vector2 getRotated(const float angle) const;
        
        
        
        //
        // Comparison
        //
        
        /// Is this vector equal to the other?
        const bool isEqual(const Vector2& other, const float floatTolerance = MathConstants::Epsilon) const;
        
        /// Is this vector a Zero vector?
        const bool isZero(const float floatTolerance = MathConstants::Epsilon) const;
        
        
        
        //
        // Unary operators
        //
        
        /// Unary + operator overload
        const Vector2 operator+() const;
        
        /// Unary - operator overload
        const Vector2 operator-() const;
        
        
        
        //
        // Vector addition
        //
        
        /// Add two vectors together
        const Vector2 operator+(const Vector2& rhs) const;
        
        /// Add two vectors together
        Vector2& operator+=(const Vector2& rhs);
       
        
        //
        // Vector subtraction
        //
        
        /// Subtract two vectors together
        const Vector2 operator-(const Vector2& rhs) const;
        
        /// Subtract two vectors together
        Vector2& operator-=(const Vector2& rhs);
        
        
        
        
        //
        // Scalar multiplication
        //
        
        /// Scalar multiplication
        const Vector2 operator*(const float scalarRhs) const;
        
        /// Scalar multiplication
        Vector2& operator*=(const float scalarRhs);
        
        /// Scalar multiplication
        friend const Vector2 operator*(const float scalarLhs, const Vector2& vectRhs);
        
        
        //
        // Scalar division
        //
        
        /// Scalar division
        const Vector2 operator/(const float scalarRhs) const;
        
        /// Scalar division
        Vector2& operator/=(const float scalarRhs);
        
        
        
        
        //
        // Static Operators
        //
        
        /// Linerarly interpolate between vector a and b given a normalized value t
        static void Lerp(Vector2& out, const Vector2& a, const Vector2& b, const float t);
        
        
        
        
        //
        // Constants
        //
        
        static const Vector2 Zero;      ///< Zero vector
        static const Vector2 One;       ///< All elements are 1.0f
        static const Vector2 Right;     ///< Right vector in world space
        static const Vector2 Up;        ///< Up vector in world space
        static const Vector2 Left;      ///< Left vector in world space
        static const Vector2 Down;      ///< Down vector in world space
        
        
    private:
        
        //
        // Data
        //
        
        float _x;    ///< The X Component
        float _y;    ///< The Y Component
        
    };
}

#endif /* Vector2_hpp */
