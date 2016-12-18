#ifndef ENGINE_MATH_MATRIX_H
#define ENGINE_MATH_MATRIX_H

#include "simd_declaration.hpp"
#include "Align16.hpp"
#include "Vector4.hpp"

namespace sea2d
{
    /// Used in underlying graphics system
    namespace math3d
    {
        //
        // Matrix Enums
        //
        
        /// Type to declare an identity matrix
        enum Identity_t
        {
            /// Declare an identity matrix
            IdentityMatrix
        };
        
        /// Type to declare a zero matrix
        enum Zero_t
        {
            /// Declare a zero matrix
            ZeroMatrix
        };
        
        /// Type to declare an X-Rotational Matrix
        enum RotX_t
        {
            /// Declare an X-Rotational Matrix
            RotationMatrixX
        };
        
        /// Type to declare a Y-Rotational Matrix
        enum RotY_t
        {
            /// Declare a Y-Rotational Matrix
            RotationMatrixY
        };
        
        /// Type to declare a Z-Rotational Matrix
        enum RotZ_t
        {
            /// Declare a Z-Rotational Matrix
            RotationMatrixZ
        };
        
        /// Used to declare a orientation matrix (given a forward and up direction)
        enum class Orientation
        {
            Normal, ///< Orientate normally given a forward and up direction
            Inverse ///< Invert the orientation given a forward an up direction
        };
        
        /// Type to declare a Translation Matrix
        enum Trans_t
        {
            /// Declare a Translation Matrix
            TranslationMatrix
        };
        
        /// Type to declare a Scale Matrix
        enum Scale_t
        {
            /// Declare a Scale Matrix
            ScaleMatrix
        };
        
        /// Use to refer to one of four rows of a Matrix4x4
        enum class Row : unsigned int
        {
            r0 = 0u,    ///< First (Top) Row
            r1,         ///< Second Row
            r2,         ///< Third Row
            r3          ///< Fourth (Bottom) Fow
        };
        
        
        
        //
        // Matrix Class
        //
        
        /// A row-major 4x4 Matrix (note that OpenGL is column-major)
        class Matrix4x4;
        
        // Matrix4x4 Class Header (macro obsures documentation)
        class S2D_BEGIN_ALIGNED(Matrix4x4, 16) final : public Align16
        {
        public:

            //
            // Big Four
            //

            /// Default Ctor (No Initialization!)
            explicit Matrix4x4();

            /// Destructor
            ~Matrix4x4();

            /// Copy Ctor
            Matrix4x4(const Matrix4x4& rhs);

            /// Assignment Overload
            Matrix4x4& operator=(const Matrix4x4& rhs);



            //
            // Other Constructors
            //


            /// Multi-Vector Constructor
            Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3);

            /// Ctor for Zero matrix
            explicit Matrix4x4(const Zero_t declareZero);

            /// Ctor for Identity matrix
            explicit Matrix4x4(const Identity_t declareIdentity);
            

            /// Translation Matrix ctor (floats)
            Matrix4x4(const Trans_t declareTranslation, const float x, const float y, const float z);

            /// Translation Matrix ctor (Vector4)
            Matrix4x4(const Trans_t declareTranslation, const Vector4& translation);

            /// Scale Matrix ctor
            Matrix4x4(const Scale_t declareScale, const float x, const float y, const float z);
            /// Scale Matrix ctor
            Matrix4x4(const Scale_t declareScale, const Vector4& scaling);

            /// X Rotation Matrix ctor (angle in radians)
            Matrix4x4(const RotX_t declareRotationX, const float angle);
            
            /// Y Rotation Matrix ctor (angle in radians)
            Matrix4x4(const RotY_t declareRotationY, const float angle);

            /// Z Rotation Matrix ctor (angle in radians)
            Matrix4x4(const RotZ_t declareRotationZ, const float angle);
            
            /// Orientation Ctor
            Matrix4x4(const Orientation orientationType, const Vector4& dofForward, const Vector4& up);




            //
            // Getters
            //
            
            /// Indexer
            const float operator[](const unsigned int idx) const;
            

            /// Get a row from the matrix as a vector
            const Vector4 get(const Row row) const;


            /// Function based getter
            const float m0() const;
            /// Function based getter
            const float m1() const;
            /// Function based getter
            const float m2() const;
            /// Function based getter
            const float m3() const;
            /// Function based getter
            const float m4() const;
            /// Function based getter
            const float m5() const;
            /// Function based getter
            const float m6() const;
            /// Function based getter
            const float m7() const;
            /// Function based getter
            const float m8() const;
            /// Function based getter
            const float m9() const;
            /// Function based getter
            const float m10() const;
            /// Function based getter
            const float m11() const;
            /// Function based getter
            const float m12() const;
            /// Function based getter
            const float m13() const;
            /// Function based getter
            const float m14() const;
            /// Function based getter
            const float m15() const;

            /// Read-only pointer access
            const float* const getFloatPointer() const;



            //
            // Setters
            //
            
            /// Non-const Indexer
            float& operator[](const unsigned int idx);


            /// Multi-vector setter
            void set(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3);

            /// Row setter
            void set(const Row row, const Vector4& rowValues);

            /// Set to zero matrix
            void set(const Zero_t declareZero);
            
            /// Set to identity matrix
            void set(const Identity_t declareIdentiry);

            /// Translation matrix setter (three floats)
            void set(const Trans_t declareTranslation, const float x, const float y, const float z);

            /// Translation matrix setter (one Vector4)
            void set(const Trans_t declareTranslation, const Vector4& translation);

            /// Scale matrix setter (three floats)
            void set(const Scale_t declareScale, const float x, const float y, const float z);

            /// Scale matrix setter (one Vector4)
            void set(const Scale_t declareScale, const Vector4& scaling);

            /// X Rotation matrix (angle in radians)
            void set(const RotX_t declareRotationX, const float angle);
            
            /// Y Rotation matrix (angle in radians)
            void set(const RotY_t declareRotationY, const float angle);

            /// Z Rotation matrix (angle in radians)
            void set(const RotZ_t declareRotationZ, const float angle);
            
            /// Orientation setter
            void set(const Orientation orientationType, const Vector4& dofForward, const Vector4& up);




            /// Function based setter
            float& m0();
            /// Function based setter
            float& m1();
            /// Function based setter
            float& m2();
            /// Function based setter
            float& m3();
            /// Function based setter
            float& m4();
            /// Function based setter
            float& m5();
            /// Function based setter
            float& m6();
            /// Function based setter
            float& m7();
            /// Function based setter
            float& m8();
            /// Function based setter
            float& m9();
            /// Function based setter
            float& m10();
            /// Function based setter
            float& m11();
            /// Function based setter
            float& m12();
            /// Function based setter
            float& m13();
            /// Function based setter
            float& m14();
            /// Function based setter
            float& m15();





            //
            // Unary operators
            //

            /// Unary + operator
            const Matrix4x4 operator+() const;

            /// Unary - operator
            const Matrix4x4 operator-() const;





            //
            // Scalar multiplication
            //

            /// Scalar multiplication
            const Matrix4x4 operator*(const float scalarRhs) const;
            /// Scalar multiplication
            Matrix4x4& operator*=(const float scalarRhs);
            /// Scalar multiplication
            friend const Matrix4x4 operator*(const float scalarLhs, const Matrix4x4& matRhs);



            //
            // Matrix addition
            //

            /// Matrix addition
            const Matrix4x4 operator+(const Matrix4x4& rhs) const;
            /// Matrix addition
            Matrix4x4& operator+=(const Matrix4x4& rhs);



            //
            // Matrix subtraction
            //

            /// Matrix subtraction
            const Matrix4x4 operator-(const Matrix4x4& rhs) const;
            /// Matrix subtraction
            Matrix4x4& operator-=(const Matrix4x4& rhs);




            //
            // Matrix comparison
            //

            /// Check if the matrix is equal to another matrix
            const bool isEqual(const Matrix4x4& other, float floatTolerance = MathConstants::Epsilon) const;
            /// Check if the matrix is an identity matrix
            const bool isIdentity(float floatTolerance = MathConstants::Epsilon) const;



            //
            // Matrix by Matrix multipication
            //

            /// Matrix Multiplication
            const Matrix4x4 operator*(const Matrix4x4& rhs) const;
            /// Matrix Multiplication
            Matrix4x4& operator*=(const Matrix4x4& rhs);



            //
            // Matrix exclusive operations
            //

            /// Calculate the determinant of the Matrix
            const float determinant() const;

            /// Transpose this matrix
            Matrix4x4& transpose();

            /// Get the Transpose of this matrix
            const Matrix4x4 getTranspose() const;

            /// Invert this matrix
            Matrix4x4& invert();

            /// Get the inverse of this matrix
            const Matrix4x4 getInverse() const;



        private:

            //
            // Private helper routines
            //

            
            #if S2D_USE_SIMD
                /// Multi-__m128's constructor
                Matrix4x4(const __m128& vm0, const __m128& vm1, const __m128& vm2, const __m128& vm3);
            #endif
            
            
            
            
            //
            // Data
            //
            
            #pragma clang diagnostic push
            #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
            #pragma clang diagnostic ignored "-Wnested-anon-types"
                union
                {
                    struct
                    {
                        Vector4 _v0;	/// First row
                        Vector4 _v1;	/// Second row
                        Vector4 _v2;	/// Third row
                        Vector4 _v3;	/// Fourth row
                    };

                    struct
                    {
                        float _m0;
                        float _m1;
                        float _m2;
                        float _m3;
                        float _m4;
                        float _m5;
                        float _m6;
                        float _m7;
                        float _m8;
                        float _m9;
                        float _m10;
                        float _m11;
                        float _m12;
                        float _m13;
                        float _m14;
                        float _m15;
                    };
                    
                    float _elements[16];
                };
            #pragma clang diagnostic pop
            
        } S2D_END_ALIGNED(Matrix4x4, 16);// end of Matrix4x4
    }
}
#endif