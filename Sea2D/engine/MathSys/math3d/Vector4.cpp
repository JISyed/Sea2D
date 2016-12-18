#include "Vector4.hpp"
#include "Matrix4x4.hpp"
#include "engine/MathSys/FloatComparisonUtil.hpp"
#include <math.h>

namespace sea2d
{
    
    namespace math3d
    {
        // Big four

        // Default Ctor (0,0,0,1)
        Vector4::Vector4() :
            _x(0.0f),
            _y(0.0f),
            _z(0.0f),
            _w(1.0f)
        {
        }

        // Destructor
        Vector4::~Vector4()
        {
        }

        // Copy Ctor
        Vector4::Vector4(const Vector4& rhs) :
            _x(rhs._x),
            _y(rhs._y),
            _z(rhs._z),
            _w(rhs._w)
        {
        }

        // Assignment Overload
        Vector4& Vector4::operator=(const Vector4& rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }

            this->_x = rhs._x;
            this->_y = rhs._y;
            this->_z = rhs._z;
            this->_w = rhs._w;

            return *this;
        }



        // Multi-float Ctor
        Vector4::Vector4(const float x, const float y, const float z, const float w) :
            _x(x),
            _y(y),
            _z(z),
            _w(w)
        {
        }

        // Ctor for setting all elements to the same value
        Vector4::Vector4(const float xyzw) :
            _x(xyzw),
            _y(xyzw),
            _z(xyzw),
            _w(xyzw)
        {
        }

        
        #if S2D_USE_SIMD
            // Ctor for __m128
            Vector4::Vector4(const __m128 m) :
                _m(m)
            {
            }
        #endif



        // Function-based getters
        const float Vector4::x() const
        {
            return this->_x;
        }

        // Function-based getters
        const float Vector4::y() const
        {
            return this->_y;
        }

        // Function-based getters
        const float Vector4::z() const
        {
            return this->_z;
        }

        // Function-based getters
        const float Vector4::w() const
        {
            return this->_w;
        }

        /// Read-only pointer access
        const float* const Vector4::getFloatPointer() const
        {
            return &(this->_x);
        }
        


        // Function-based setters
        float& Vector4::x()
        {
            return this->_x;
        }

        // Function-based setters
        float& Vector4::y()
        {
            return this->_y;
        }

        // Function-based setters
        float& Vector4::z()
        {
            return this->_z;
        }

        // Function-based setters
        float& Vector4::w()
        {
            return this->_w;
        }


        // Multi-float setter
        void Vector4::set(const float x, const float y, const float z, const float w)
        {
            this->_x = x;
            this->_y = y;
            this->_z = z;
            this->_w = w;
        }

        // Vector4 based setter
        void Vector4::set(const Vector4& other)
        {
            this->operator=(other);
        }


        // Vector2 based setter
        void Vector4::set(const sea2d::Vector2& other)
        {
            this->_x = other.x();
            this->_y = other.y();
        }
        



        // Dot product
        const float Vector4::dot3d(const Vector4& rhs) const
        {
            // ax*bx + ay*by + az*bz

            return (this->_x * rhs._x) + (this->_y * rhs._y) + (this->_z * rhs._z);
        }

        // Cross product
        const Vector4 Vector4::cross3d(const Vector4& rhs) const
        {
            // [(ay*bz - az*by), - (ax*bz - az*bx), (ax*by - ay*bx)]

            return Vector4(
                (this->_y *  rhs._z) - (this->_z * rhs._y),
                (this->_x * -rhs._z) + (this->_z * rhs._x),
                (this->_x *  rhs._y) - (this->_y * rhs._x)
            );
        }


        // Normalize yourself
        void Vector4::normalize3d()
        {
            const float magnSqr = this->magnitudeSquare3d();
            if (FloatComparisonUtil::isZero(magnSqr))
            {
                // Cannot normalize a zero vector
                return;
            }
            const float magn = sqrtf(magnSqr);

            this->_x /= magn;
            this->_y /= magn;
            this->_z /= magn;
        }


        // Get a normalized version of this vector
        const Vector4 Vector4::getNormalized3d() const
        {
            const float magnSqr = this->magnitudeSquare3d();
            if (FloatComparisonUtil::isZero(magnSqr))
            {
                // Cannot normalize a zero vector
                return Vector4();
            }
            const float magn = sqrtf(magnSqr);

            return Vector4(this->_x / magn, this->_y / magn, this->_z / magn);
        }


        // Get the absolute length of the vector
        const float Vector4::magnitide3d() const
        {
            return sqrtf(this->magnitudeSquare3d());
        }


        // Get the squared-length of the vector (faster than Vector4::mag())
        const float Vector4::magnitudeSquare3d() const
        {
            return (this->_x * this->_x) + (this->_y * this->_y) + (this->_z * this->_z);
        }


        // Get the angle (in radians) between this vector and the rhs vector
        const float Vector4::getAngle3d(const Vector4& rhs) const
        {
            const float lhsVectMagnSq = this->magnitudeSquare3d();
            const float rhsVectMagnSq = rhs.magnitudeSquare3d();

            if (FloatComparisonUtil::isZero(lhsVectMagnSq) || FloatComparisonUtil::isZero(rhsVectMagnSq))
            {
                // Cannot get an angle for a zero vector
                return 0.0f;
            }
            return acosf(this->dot3d(rhs) / (sqrtf(lhsVectMagnSq) * sqrtf(rhsVectMagnSq)));
        }







        // Is this vector equal to the other?
        const bool Vector4::isEqual(const Vector4& other, const float floatTolerance) const
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

            // If the Z's are not the same
            if (FloatComparisonUtil::isNotEqual(this->_z, other._z, floatTolerance))
            {
                // Cannot be equal vectors
                return false;
            }


            // If you're here, the vectors were equal enough
            return true;
        }

        // Is this vector a Zero vector?
        const bool Vector4::isZero(const float floatTolerance) const
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

            // If the Z's are not the same
            if (!FloatComparisonUtil::isZero(this->_z, floatTolerance))
            {
                // Cannot be equal vectors
                return false;
            }

            // If you're here, the vectors were equal enough
            return true;
        }




        // Unary + operator overload
        const Vector4 Vector4::operator+() const
        {
            return Vector4(this->_x, this->_y, this->_z);
        }

        // Unary - operator overload
        const Vector4 Vector4::operator-() const
        {
            return Vector4(-_x, -_y, -_z);
        }





        // Add two vectors together
        const Vector4 Vector4::operator+(const Vector4& rhs) const
        {
            return Vector4(
                this->_x + rhs._x,
                this->_y + rhs._y,
                this->_z + rhs._z
            );
        }

        Vector4& Vector4::operator+=(const Vector4& rhs)
        {
            this->_x += rhs._x;
            this->_y += rhs._y;
            this->_z += rhs._z;
            this->_w = 1.0f;

            return *this;
        }

        // Subtract two vectors together
        const Vector4 Vector4::operator-(const Vector4& rhs) const
        {
            return Vector4(
                this->_x - rhs._x,
                this->_y - rhs._y,
                this->_z - rhs._z
            );
        }

        Vector4& Vector4::operator-=(const Vector4& rhs)
        {
            this->_x -= rhs._x;
            this->_y -= rhs._y;
            this->_z -= rhs._z;
            this->_w = 1.0f;

            return *this;
        }



        // Scalar multiplication
        const Vector4 Vector4::operator*(const float scalarRhs) const
        {
            return Vector4(this->_x * scalarRhs, this->_y * scalarRhs, this->_z * scalarRhs);
        }

        // Scalar multiplication
        Vector4& Vector4::operator*=(const float scalarRhs)
        {
            this->_x *= scalarRhs;
            this->_y *= scalarRhs;
            this->_z *= scalarRhs;
            this->_w = 1.0f;

            return *this;
        }

        // FRIEND
        // Scalar multiplication
        const Vector4 operator*(const float scalarLhs, const Vector4& vectRhs)
        {
            return Vector4(vectRhs._x * scalarLhs, vectRhs._y * scalarLhs, vectRhs._z * scalarLhs);
        }


        // Scalar division
        const Vector4 Vector4::operator/(const float scalarRhs) const
        {
            return Vector4(this->_x / scalarRhs, this->_y / scalarRhs, this->_z / scalarRhs);
        }

        // Scalar division
        Vector4& Vector4::operator/=(const float scalarRhs)
        {
            this->_x /= scalarRhs;
            this->_y /= scalarRhs;
            this->_z /= scalarRhs;
            this->_w = 1.0f;

            return *this;
        }








        #if S2D_USE_SIMD
            // Get the __m128 member
            const __m128 Vector4::getM() const
            {
                return this->_m;
            }

            // Setter for the __m128 member
            __m128& Vector4::getMRef()
            {
                return this->_m;
            }

            // Ref getter for __m128 member
            const __m128& Vector4::getConstM() const
            {
                return this->_m;
            }
        #endif





        // Vector4 by Matrix4x4 multiplication
        const Vector4 Vector4::operator*(const Matrix4x4& matRhs) const
        {
            Vector4 answer(0.0f);

            answer.increment(matRhs.get(Row::r0).getScaled(this->_x));
            answer.increment(matRhs.get(Row::r1).getScaled(this->_y));
            answer.increment(matRhs.get(Row::r2).getScaled(this->_z));
            answer.increment(matRhs.get(Row::r3).getScaled(this->_w));

            return answer;
        }

        Vector4& Vector4::operator*=(const Matrix4x4& matRhs)
        {
            const Vector4 copy = *this;
            this->set(0.0f, 0.0f, 0.0f, 0.0f);

            this->increment(matRhs.get(Row::r0).getScaled(copy._x));
            this->increment(matRhs.get(Row::r1).getScaled(copy._y));
            this->increment(matRhs.get(Row::r2).getScaled(copy._z));
            this->increment(matRhs.get(Row::r3).getScaled(copy._w));

            return *this;
        }



        // Scale every element of the vector, even W
        const Vector4 Vector4::getScaled(const float scalar) const
        {
            return Vector4(this->_x * scalar, this->_y * scalar, this->_z * scalar, this->_w * scalar);
        }

        Vector4& Vector4::scale(const float scalar)
        {
            this->_x *= scalar;
            this->_y *= scalar;
            this->_z *= scalar;
            this->_w *= scalar;

            return *this;
        }


        // Add every element of one vector upon another, even W
        const Vector4 Vector4::add(const Vector4& other) const
        {
            return Vector4(
                this->_x + other._x,
                this->_y + other._y,
                this->_z + other._z,
                this->_w + other._w
            );
        }

        Vector4& Vector4::increment(const Vector4& other)
        {
            this->_x += other._x;
            this->_y += other._y;
            this->_z += other._z;
            this->_w += other._w;

            return *this;
        }
        
        
        
        
        // STATIC
        void Vector4::Lerp(Vector4 &out, const Vector4 &a, const Vector4 &b, const float t)
        {
            /// lerpVect = (1-t)*a + t*b
            out = (a*(1 - t)) + (b*t);
        }
    }
}
