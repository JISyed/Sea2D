#ifndef ENGINE_MATH_VECT4_H
#define ENGINE_MATH_VECT4_H

#include "engine/MathSys/Vector2.hpp"
#include "engine/MathSys/MathConstants.hpp"
#include "simd_declaration.hpp"
#include "Align16.hpp"


namespace sea2d
{
    /// Used in underlying graphics system
    namespace math3d
    {
        // forward declare Matrix4x4
        class Matrix4x4;
        
        
        
        /// Row-major 4 element Vector
        class Vector4;
        
        // Vector4 Class Header (macro obscures documentation)
        class S2D_BEGIN_ALIGNED(Vector4, 16) final : public Align16
        {
        public:


            //
            // Big Four
            //

            /// Default Ctor (0,0,0,1)
            explicit Vector4();

            /// Destructor
            ~Vector4();

            /// Copy Ctor
            Vector4(const Vector4& rhs);

            /// Assignment Overload
            Vector4& operator=(const Vector4& rhs);


            //
            // Other Constructors
            //

            /// Multi-float Ctor
            Vector4(const float x, const float y, const float z, const float w = 1.0f);

            /// Ctor for setting all elements to the same value
            explicit Vector4(const float xyzw);
            
            #if S2D_USE_SIMD
                /// Ctor for __m128 (Only Matrix4x4 should use this!)
                explicit Vector4(const __m128 m);
            #endif


            //
            // Getters
            //

            /// Function-based getter for x
            const float x() const;
            /// Function-based getter for y
            const float y() const;
            /// Function-based getter for z
            const float z() const;
            /// Function-based getter for w
            const float w() const;

            /// Read-only pointer access
            const float* const getFloatPointer() const;


            //
            // Setters
            //

            /// Function-based setter for x
            float& x();
            /// Function-based setter for y
            float& y();
            /// Function-based setter for z
            float& z();
            /// Function-based setter for w
            float& w();


            /// Multi-float setter
            void set(const float x, const float y, const float z, const float w = 1.0f);

            /// Vector4 based setter
            void set(const Vector4& other);
            
            /// Vector2 based setter
            void set(const Vector2& other);





            //
            // Vector 3D exclusive operations
            //


            /// Dot product of the 3d portion of this Vector4
            const float dot3d(const Vector4& rhs) const;

            /// Cross product of the 3d portion of this Vector4
            const Vector4 cross3d(const Vector4& rhs) const;

            /// Normalize the 3d portion of this Vector4
            void normalize3d();

            /// Get a normalized version of the 3d portion of this vector
            const Vector4 getNormalized3d() const;

            /// Get the absolute length of the vector
            const float magnitide3d() const;

            /// Get the squared-length of the vector (faster than Vector4::magnitide3d())
            const float magnitudeSquare3d() const;

            /// Get the angle (in radians) between this vector and the rhs vector (3d portions of those vectors)
            const float getAngle3d(const Vector4& rhs) const;



            //
            // Vector comparison
            //

            /// Is this vector equal to the other?
            const bool isEqual(const Vector4& other, const float floatTolerance = MathConstants::Epsilon) const;

            /// Is this vector a Zero vector?
            const bool isZero(const float floatTolerance = MathConstants::Epsilon) const;



            //
            // Unary operators
            //

            /// Unary + operator overload
            const Vector4 operator+() const;

            /// Unary - operator overload
            const Vector4 operator-() const;




            //
            // Vector addition
            //

            /// Add two vectors together
            const Vector4 operator+(const Vector4& rhs) const;

            /// Add two vectors together
            Vector4& operator+=(const Vector4& rhs);




            //
            // Vector subtraction
            //

            /// Subtract two vectors together
            const Vector4 operator-(const Vector4& rhs) const;

            /// Subtract two vectors together
            Vector4& operator-=(const Vector4& rhs);




            //
            // Scalar multiplication
            //

            /// Scalar multiplication
            const Vector4 operator*(const float scalarRhs) const;

            /// Scalar multiplication
            Vector4& operator*=(const float scalarRhs);

            /// Scalar multiplication
            friend const Vector4 operator*(const float scalarLhs, const Vector4& vectRhs);


            //
            // Scalar division
            //

            /// Scalar division
            const Vector4 operator/(const float scalarRhs) const;

            /// Scalar division
            Vector4& operator/=(const float scalarRhs);



            #if S2D_USE_SIMD
                //
                // __m128 Accessors
                //

                /// Get the __m128 member (Only Matrix4x4 should use this!)
                const __m128 getM() const;

                /// Setter for the __m128 member (Only Matrix4x4 should use this!)
                __m128& getMRef();

                /// Ref getter for __m128 member (Only Matrix4x4 should use this!)
                const __m128& getConstM() const;
            #endif



            //
            // Matrix multiplication (v*M)
            //

            /// Vector4 by Matrix4x4 multiplication
            const Vector4 operator*(const Matrix4x4& matRhs) const;

            /// Vector4 by Matrix4x4 multiplication
            Vector4& operator*=(const Matrix4x4& matRhs);




            //
            // Full Vector Scaling
            //

            /// Scale every element of the vector, even W
            const Vector4 getScaled(const float scalar) const;

            /// Scale every element of the vector, even W
            Vector4& scale(const float scalar);



            //
            // Full Vector Addition
            // 

            /// Add every element of one vector upon another, even W
            const Vector4 add(const Vector4& other) const;

            /// Add every element of one vector upon another, even W
            Vector4& increment(const Vector4& other);


            
            //
            // Static Operators
            //
            
            /// Linerarly interpolate between vector a and b given a normalized value t
            static void Lerp(Vector4 &out, const Vector4 &a, const Vector4 &b, const float t);


        private:

            //
            // Data
            //
            
            #pragma clang diagnostic push
            #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
            #pragma clang diagnostic ignored "-Wnested-anon-types"
                union
                {
                    #if S2D_USE_SIMD
                        __m128	_m; ///< SIMD 16-byte data block for whole vector
                    #endif
                    
                    struct
                    {
                        float _x;   ///< The X component
                        float _y;   ///< The Y component
                        float _z;   ///< The Z component
                        float _w;   ///< The W component
                    };
                };
            #pragma clang diagnostics pop
            
        } S2D_END_ALIGNED(Vector4, 16);	// end of Vector4
    }
}
#endif