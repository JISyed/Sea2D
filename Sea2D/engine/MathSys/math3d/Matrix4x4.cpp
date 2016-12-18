#include "Matrix4x4.hpp"
#include "engine/MathSys/FloatComparisonUtil.hpp"
#include <math.h>
#include "engine/AppSys/DebugGuarantee.hpp"
#include <utility>

namespace sea2d
{
    namespace math3d
    {
        //
        // C Prototypes
        //
        
        #if S2D_USE_SIMD
            /// SIMD inverse implementation from:
            /// ftp://download.intel.com/design/PentiumIII/sml/24504301.pdf
            void sse_inverse_mat4x4(float *const src);
        #endif
        
        
        //
        // Big four
        //
        
        
        // Default Ctor (No Initialzation!)
        Matrix4x4::Matrix4x4()
        {
        }

        // Destructor
        Matrix4x4::~Matrix4x4()
        {
        }

        // Copy Ctor
        Matrix4x4::Matrix4x4(const Matrix4x4& rhs) :
            _v0(rhs._v0),
            _v1(rhs._v1),
            _v2(rhs._v2),
            _v3(rhs._v3)
        {
        }

        // Assignment Overload
        Matrix4x4& Matrix4x4::operator=(const Matrix4x4& rhs)
        {
            if (this == &rhs)
            {
                return *this;
            }

            this->_v0 = rhs._v0;
            this->_v1 = rhs._v1;
            this->_v2 = rhs._v2;
            this->_v3 = rhs._v3;

            return *this;
        }

        // Multi-Vector Constructor
        Matrix4x4::Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3) :
            _v0(v0),
            _v1(v1),
            _v2(v2),
            _v3(v3)
        {
        }

        // Ctor for Zero matrix
        Matrix4x4::Matrix4x4(const Zero_t declareZero) :
            _v0(0.0f),
            _v1(0.0f),
            _v2(0.0f),
            _v3(0.0f)
        {
            declareZero;
        }
        
        // Ctor for Identity matrix
        Matrix4x4::Matrix4x4(const Identity_t declareIdentity) :
        _v0(1.0f, 0.0f, 0.0f, 0.0f),
        _v1(0.0f, 1.0f, 0.0f, 0.0f),
        _v2(0.0f, 0.0f, 1.0f, 0.0f),
        _v3(0.0f, 0.0f, 0.0f, 1.0f)
        {
            declareIdentity;
        }
        
        #if S2D_USE_SIMD
            // PRIVATE
            // Multi-__m128's constructor
            Matrix4x4::Matrix4x4(const __m128& vm0, const __m128& vm1, const __m128& vm2, const __m128& vm3) :
                _v0(vm0),
                _v1(vm1),
                _v2(vm2),
                _v3(vm3)
            {
            }
        #endif

        // Translation Matrix ctor
        Matrix4x4::Matrix4x4(const Trans_t declareTranslation, const float x, const float y, const float z) :
            _v0(1.0f, 0.0f, 0.0f, 0.0f),
            _v1(0.0f, 1.0f, 0.0f, 0.0f),
            _v2(0.0f, 0.0f, 1.0f, 0.0f),
            _v3(x, y, z, 1.0f)
        {
            declareTranslation;
        }

        Matrix4x4::Matrix4x4(const Trans_t declareTranslation, const Vector4& translation) :
            _v0(1.0f, 0.0f, 0.0f, 0.0f),
            _v1(0.0f, 1.0f, 0.0f, 0.0f),
            _v2(0.0f, 0.0f, 1.0f, 0.0f),
            _v3(translation)
        {
            declareTranslation;
        }


        // Scale Matrix ctor
        Matrix4x4::Matrix4x4(const Scale_t declareScale, const float x, const float y, const float z) :
            _v0(x, 0.0f, 0.0f, 0.0f),
            _v1(0.0f, y, 0.0f, 0.0f),
            _v2(0.0f, 0.0f, z, 0.0f),
            _v3(0.0f, 0.0f, 0.0f, 1.0f)
        {
            declareScale;
        }

        Matrix4x4::Matrix4x4(const Scale_t declareScale, const Vector4& scaling) :
            _v0(scaling.x(), 0.0f, 0.0f, 0.0f),
            _v1(0.0f, scaling.y(), 0.0f, 0.0f),
            _v2(0.0f, 0.0f, scaling.z(), 0.0f),
            _v3(0.0f, 0.0f, 0.0f, 1.0f)
        {
            declareScale;
        }


        // X Rotation Matrix ctor (angle in radians)
        Matrix4x4::Matrix4x4(const RotX_t declareRotationX, const float angle)
        {
            this->set(declareRotationX, angle);
        }
        
        // Y Rotation Matrix ctor (angle in radians)
        Matrix4x4::Matrix4x4(const RotY_t declareRotationY, const float angle)
        {
            this->set(declareRotationY, angle);
        }
        
        // Z Rotation Matrix ctor (angle in radians)
        Matrix4x4::Matrix4x4(const RotZ_t declareRotationZ, const float angle)
        {
            this->set(declareRotationZ, angle);
        }
        
        // Orientation Ctor
        Matrix4x4::Matrix4x4(const Orientation orientationType, const Vector4& dofForward, const Vector4& up)
        {
            this->set(orientationType, dofForward, up);
        }





        /// Indexer
        const float Matrix4x4::operator[](const unsigned int idx) const
        {
            guarantee_that(idx < 16, "Matrix: Indexer out of range!");
            
            return this->_elements[idx];
        }
        
        /// Non-const Indexer
        float& Matrix4x4::operator[](const unsigned int idx)
        {
            guarantee_that(idx < 16, "Matrix: Indexer out of range!");
            
            return this->_elements[idx];
        }
        


        // Get a row from the matrix as a vector
        const Vector4 Matrix4x4::get(const Row row) const
        {
            //Vector4* vPtr = (Vector4*) this;
            //vPtr = vPtr + (unsigned int)row;
            //return *vPtr;

            return *(((Vector4*)&this->_v0) + ((unsigned int)row));
        }

        // Multi-vector setter
        void Matrix4x4::set(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3)
        {
            this->_v0 = v0;
            this->_v1 = v1;
            this->_v2 = v2;
            this->_v3 = v3;
        }


        // Row setter
        void Matrix4x4::set(const Row row, const Vector4& rowValues)
        {
            //Vector4* vPtr = (Vector4*) this;
            //vPtr = vPtr + (unsigned int)row;
            //*vPtr = rowValues;

            *(((Vector4*)&this->_v0) + ((unsigned int)row)) = rowValues;
        }


        // Set to zero matrix
        void Matrix4x4::set(const Zero_t declareZero)
        {
            declareZero;
            
            this->_v0 = Vector4(0.0f);
            this->_v1 = Vector4(0.0f);
            this->_v2 = Vector4(0.0f);
            this->_v3 = Vector4(0.0f);
        }
        
        // Set to identity matrix
        void Matrix4x4::set(const Identity_t declareIdentity)
        {
            declareIdentity;
            
            this->_v0 = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
            this->_v1 = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
            this->_v2 = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
            this->_v3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
        }
        
        
        // Translation matrix setter (three floats)
        void Matrix4x4::set(const Trans_t declareTranslation, const float x, const float y, const float z)
        {
            declareTranslation;
            this->_v0 = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
            this->_v1 = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
            this->_v2 = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
            this->_v3 = Vector4(x, y, z, 1.0f);
        }

        // Translation matrix setter (one Vector4)
        void Matrix4x4::set(const Trans_t declareTranslation, const Vector4& translation)
        {
            declareTranslation;
            this->_v0 = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
            this->_v1 = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
            this->_v2 = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
            this->_v3 = translation;
        }

        // Scale matrix setter (three floats)
        void Matrix4x4::set(const Scale_t declareScale, const float x, const float y, const float z)
        {
            declareScale;
            this->_v0 = Vector4(x, 0.0f, 0.0f, 0.0f);
            this->_v1 = Vector4(0.0f, y, 0.0f, 0.0f);
            this->_v2 = Vector4(0.0f, 0.0f, z, 0.0f);
            this->_v3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
        }

        // Scale matrix setter (one Vector4)
        void Matrix4x4::set(const Scale_t declareScale, const Vector4& scaling)
        {
            declareScale;
            this->_v0 = Vector4(scaling.x(), 0.0f, 0.0f, 0.0f);
            this->_v1 = Vector4(0.0f, scaling.y(), 0.0f, 0.0f);
            this->_v2 = Vector4(0.0f, 0.0f, scaling.z(), 0.0f);
            this->_v3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
        }

        // X Rotation matrix (angle in radians)
        void Matrix4x4::set(const RotX_t declareRotationX, const float angle)
        {
            declareRotationX;
            
            const float cosAngle = cosf(angle);
            const float sinAngle = sinf(angle);
            
            this->_v0 = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
            this->_v1 = Vector4(0.0f, cosAngle, sinAngle, 0.0f);
            this->_v2 = Vector4(0.0f, -sinAngle, cosAngle, 0.0f);
            this->_v3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
        }
        
        // Y Rotation matrix (angle in radians)
        void Matrix4x4::set(const RotY_t declareRotationY, const float angle)
        {
            declareRotationY;
            
            const float cosAngle = cosf(angle);
            const float sinAngle = sinf(angle);
            
            this->_v0 = Vector4(cosAngle, 0.0f, -sinAngle, 0.0f);
            this->_v1 = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
            this->_v2 = Vector4(sinAngle, 0.0f, cosAngle, 0.0f);
            this->_v3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
        }
        
        // Z Rotation matrix (angle in radians)
        void Matrix4x4::set(const RotZ_t declareRotationZ, const float angle)
        {
            declareRotationZ;
            
            const float cosAngle = cosf(angle);
            const float sinAngle = sinf(angle);
            
            this->_v0 = Vector4(cosAngle, sinAngle, 0.0f, 0.0f);
            this->_v1 = Vector4(-sinAngle, cosAngle, 0.0f, 0.0f);
            this->_v2 = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
            this->_v3 = Vector4(0.0f, 0.0f, 0.0f, 1.0f);
        }
        
        // Orientation setter
        void Matrix4x4::set(const Orientation orientationType, const Vector4& dofForward, const Vector4& oldUp)
        {


            // Calculate the corrected up
            const Vector4 up((dofForward.cross3d(oldUp.cross3d(dofForward))));
            const Vector4 upNorm = up.getNormalized3d();

            Vector4 orientX(up.cross3d(dofForward));
            orientX.normalize3d();
            orientX.w() = 0.0f;

            Vector4 orientY(upNorm);
            orientY.w() = 0.0f;

            Vector4 orientZ(dofForward);
            orientZ.normalize3d();
            orientZ.w() = 0.0f;

            this->_v0 = orientX;
            this->_v1 = orientY;
            this->_v2 = orientZ;
            this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);

            if (orientationType == Orientation::Inverse)
            {
                this->transpose();
            }
        }






        // Function based getters
        const float Matrix4x4::m0() const
        {
            return this->_m0;
        }

        const float Matrix4x4::m1() const
        {
            return this->_m1;
        }

        const float Matrix4x4::m2() const
        {
            return this->_m2;
        }

        const float Matrix4x4::m3() const
        {
            return this->_m3;
        }

        const float Matrix4x4::m4() const
        {
            return this->_m4;
        }

        const float Matrix4x4::m5() const
        {
            return this->_m5;
        }

        const float Matrix4x4::m6() const
        {
            return this->_m6;
        }

        const float Matrix4x4::m7() const
        {
            return this->_m7;
        }

        const float Matrix4x4::m8() const
        {
            return this->_m8;
        }

        const float Matrix4x4::m9() const
        {
            return this->_m9;
        }

        const float Matrix4x4::m10() const
        {
            return this->_m10;
        }

        const float Matrix4x4::m11() const
        {
            return this->_m11;
        }

        const float Matrix4x4::m12() const
        {
            return this->_m12;
        }

        const float Matrix4x4::m13() const
        {
            return this->_m13;
        }

        const float Matrix4x4::m14() const
        {
            return this->_m14;
        }

        const float Matrix4x4::m15() const
        {
            return this->_m15;
        }

        /// Read-only pointer access
        const float* const Matrix4x4::getFloatPointer() const
        {
            return this->_elements;
        }


        // Function based setters
        float& Matrix4x4::m0()
        {
            return this->_m0;
        }

        float& Matrix4x4::m1()
        {
            return this->_m1;
        }

        float& Matrix4x4::m2()
        {
            return this->_m2;
        }

        float& Matrix4x4::m3()
        {
            return this->_m3;
        }

        float& Matrix4x4::m4()
        {
            return this->_m4;
        }

        float& Matrix4x4::m5()
        {
            return this->_m5;
        }

        float& Matrix4x4::m6()
        {
            return this->_m6;
        }

        float& Matrix4x4::m7()
        {
            return this->_m7;
        }

        float& Matrix4x4::m8()
        {
            return this->_m8;
        }

        float& Matrix4x4::m9()
        {
            return this->_m9;
        }

        float& Matrix4x4::m10()
        {
            return this->_m10;
        }

        float& Matrix4x4::m11()
        {
            return this->_m11;
        }

        float& Matrix4x4::m12()
        {
            return this->_m12;
        }

        float& Matrix4x4::m13()
        {
            return this->_m13;
        }

        float& Matrix4x4::m14()
        {
            return this->_m14;
        }

        float& Matrix4x4::m15()
        {
            return this->_m15;
        }




        // Unary + operator
        const Matrix4x4 Matrix4x4::operator+() const
        {
            return *this;
        }

        // Unary - operator
        const Matrix4x4 Matrix4x4::operator-() const
        {
            return Matrix4x4(*this * -1.0f);
        }




        // Scalar multiplication
        const Matrix4x4 Matrix4x4::operator*(const float scalarRhs) const
        {
            #if S2D_USE_SIMD
                const __m128 scalarBlock = _mm_set_ps1(scalarRhs);
                return Matrix4x4(
                    _mm_mul_ps(this->_v0.getConstM(), scalarBlock),
                    _mm_mul_ps(this->_v1.getConstM(), scalarBlock),
                    _mm_mul_ps(this->_v2.getConstM(), scalarBlock),
                    _mm_mul_ps(this->_v3.getConstM(), scalarBlock)
                );
            #else
                return Matrix4x4(this->_v0 * scalarRhs, this->_v1 * scalarRhs, this->_v2 * scalarRhs, this->_v3 * scalarRhs);
            #endif
        }

        // Scalar multiplication
        Matrix4x4& Matrix4x4::operator*=(const float scalarRhs)
        {
            #if S2D_USE_SIMD
                const __m128 scalarBlock = _mm_set_ps1(scalarRhs);

                //__m128 result = _mm_mul_ps(vector, scalar);
                this->_v0.getMRef() = _mm_mul_ps(this->_v0.getConstM(), scalarBlock);
                this->_v1.getMRef() = _mm_mul_ps(this->_v1.getConstM(), scalarBlock);
                this->_v2.getMRef() = _mm_mul_ps(this->_v2.getConstM(), scalarBlock);
                this->_v3.getMRef() = _mm_mul_ps(this->_v3.getConstM(), scalarBlock);
            #else
                this->_v0 *= scalarRhs;
                this->_v1 *= scalarRhs;
                this->_v2 *= scalarRhs;
                this->_v3 *= scalarRhs;
            #endif
            
            return *this;
        }

        // FRIEND
        // Scalar multiplication
        const Matrix4x4 operator*(const float scalarLhs, const Matrix4x4& matRhs)
        {
            #if S2D_USE_SIMD
                const __m128 scalarBlock = _mm_set_ps1(scalarLhs);
                return Matrix4x4(
                    _mm_mul_ps(matRhs._v0.getConstM(), scalarBlock),
                    _mm_mul_ps(matRhs._v1.getConstM(), scalarBlock),
                    _mm_mul_ps(matRhs._v2.getConstM(), scalarBlock),
                    _mm_mul_ps(matRhs._v3.getConstM(), scalarBlock)
                );
            #else
                return Matrix4x4(matRhs._v0 * scalarLhs, matRhs._v1 * scalarLhs, matRhs._v2 * scalarLhs, matRhs._v3 * scalarLhs);
            #endif
        }



        // Matrix addition
        const Matrix4x4 Matrix4x4::operator+(const Matrix4x4& rhs) const
        {
            #if S2D_USE_SIMD
                return Matrix4x4(
                    _mm_add_ps(this->_v0.getConstM(), rhs._v0.getConstM()),
                    _mm_add_ps(this->_v1.getConstM(), rhs._v1.getConstM()),
                    _mm_add_ps(this->_v2.getConstM(), rhs._v2.getConstM()),
                    _mm_add_ps(this->_v3.getConstM(), rhs._v3.getConstM())
                );
            #else
                return Matrix4x4(this->_v0 + rhs._v0, this->_v1 + rhs._v1, this->_v2 + rhs._v2, this->_v3 + rhs._v3);
            #endif
        }

        Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& rhs)
        {
            #if S2D_USE_SIMD
                this->_v0.getMRef() = _mm_add_ps(this->_v0.getConstM(), rhs._v0.getConstM());
                this->_v1.getMRef() = _mm_add_ps(this->_v1.getConstM(), rhs._v1.getConstM());
                this->_v2.getMRef() = _mm_add_ps(this->_v2.getConstM(), rhs._v2.getConstM());
                this->_v3.getMRef() = _mm_add_ps(this->_v3.getConstM(), rhs._v3.getConstM());
            #else
                this->_v0 += rhs._v0;
                this->_v1 += rhs._v1;
                this->_v2 += rhs._v2;
                this->_v3 += rhs._v3;
            #endif
            
            return *this;
        }

        // Matrix subtraction
        const Matrix4x4 Matrix4x4::operator-(const Matrix4x4& rhs) const
        {
            #if S2D_USE_SIMD
                return Matrix4x4(
                      _mm_sub_ps(this->_v0.getConstM(), rhs._v0.getConstM()),
                      _mm_sub_ps(this->_v1.getConstM(), rhs._v1.getConstM()),
                      _mm_sub_ps(this->_v2.getConstM(), rhs._v2.getConstM()),
                      _mm_sub_ps(this->_v3.getConstM(), rhs._v3.getConstM())
                );
            #else
                return Matrix4x4(this->_v0 - rhs._v0, this->_v1 - rhs._v1, this->_v2 - rhs._v2, this->_v3 - rhs._v3);
            #endif
        }

        Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& rhs)
        {
            #if S2D_USE_SIMD
                this->_v0.getMRef() = _mm_sub_ps(this->_v0.getConstM(), rhs._v0.getConstM());
                this->_v1.getMRef() = _mm_sub_ps(this->_v1.getConstM(), rhs._v1.getConstM());
                this->_v2.getMRef() = _mm_sub_ps(this->_v2.getConstM(), rhs._v2.getConstM());
                this->_v3.getMRef() = _mm_sub_ps(this->_v3.getConstM(), rhs._v3.getConstM());
            #else
                this->_v0 -= rhs._v0;
                this->_v1 -= rhs._v1;
                this->_v2 -= rhs._v2;
                this->_v3 -= rhs._v3;
            #endif
            
            return *this;
        }





        // Check if the matrix is equal to another matrix
        const bool Matrix4x4::isEqual(const Matrix4x4& other, float floatTolerance) const
        {
            // Leave if Row0 is not equal
            if (!this->_v0.isEqual(other._v0, floatTolerance))
            {
                return false;
            }

            // Leave if Row1 is not equal
            if (!this->_v1.isEqual(other._v1, floatTolerance))
            {
                return false;
            }

            // Leave if Row2 is not equal
            if (!this->_v2.isEqual(other._v2, floatTolerance))
            {
                return false;
            }

            // Leave if Row3 is not equal
            if (!this->_v3.isEqual(other._v3, floatTolerance))
            {
                return false;
            }

            // If you're here, all the rows are equal
            return true;
        }

        const bool Matrix4x4::isIdentity(float floatTolerance) const
        {
            static Matrix4x4 MatIdentity(IdentityMatrix);
            
            return this->isEqual(MatIdentity, floatTolerance);
        }





        // Matrix Multiplication
        const Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs) const
        {
            return Matrix4x4(
                this->_v0 * rhs,
                this->_v1 * rhs,
                this->_v2 * rhs,
                this->_v3 * rhs
                );
        }

        Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& rhs)
        {
            this->_v0 *= rhs;
            this->_v1 *= rhs;
            this->_v2 *= rhs;
            this->_v3 *= rhs;

            return *this;
        }






        // Calculate the determinant of the Matrix
        const float Matrix4x4::determinant() const
        {
            // Old fashioned way :(
            return (_m0*_m5*_m10*_m15) + (_m0*_m6*_m11*_m13) + (_m0*_m7*_m9*_m14)
                + (_m1*_m4*_m11*_m14) + (_m1*_m6*_m8*_m15) + (_m1*_m7*_m10*_m12)
                + (_m2*_m4*_m9*_m15) + (_m2*_m5*_m11*_m12) + (_m2*_m7*_m8*_m13)
                + (_m3*_m4*_m10*_m13) + (_m3*_m5*_m8*_m14) + (_m3*_m6*_m9*_m12)
                - (_m0*_m5*_m11*_m14) - (_m0*_m6*_m9*_m15) - (_m0*_m7*_m10*_m13)
                - (_m1*_m4*_m10*_m15) - (_m1*_m6*_m11*_m12) - (_m1*_m7*_m8*_m14)
                - (_m2*_m4*_m11*_m13) - (_m2*_m5*_m8*_m15) - (_m2*_m7*_m9*_m12)
                - (_m3*_m4*_m9*_m14) - (_m3*_m5*_m10*_m12) - (_m3*_m6*_m8*_m13)
                ;
        }

        // Transpose yourself
        Matrix4x4& Matrix4x4::transpose()
        {
            #if S2D_USE_SIMD
                _MM_TRANSPOSE4_PS(
                    this->_v0.getMRef(),
                    this->_v1.getMRef(),
                    this->_v2.getMRef(),
                    this->_v3.getMRef()
                );
            #else
                std::swap(this->_m1, this->_m4);
                std::swap(this->_m2, this->_m8);
                std::swap(this->_m3, this->_m12);
                std::swap(this->_m6, this->_m9);
                std::swap(this->_m7, this->_m13);
                std::swap(this->_m11, this->_m14);
            #endif
            
            return *this;
        }

        // Get the Transpose of this matrix
        const Matrix4x4 Matrix4x4::getTranspose() const
        {
            #if S2D_USE_SIMD
                Matrix4x4 transposedCopy(*this);

                _MM_TRANSPOSE4_PS(
                    transposedCopy._v0.getMRef(),
                    transposedCopy._v1.getMRef(),
                    transposedCopy._v2.getMRef(),
                    transposedCopy._v3.getMRef()
                );

                return transposedCopy;
            #else
                const Vector4 nv0(this->_m0, this->_m4, this->_m8, this->_m12);
                const Vector4 nv1(this->_m1, this->_m5, this->_m9, this->_m13);
                const Vector4 nv2(this->_m2, this->_m6, this->_m10, this->_m14);
                const Vector4 nv3(this->_m3, this->_m7, this->_m11, this->_m15);
                
                return Matrix4x4(nv0, nv1, nv2, nv3);
            #endif
        }




        // Inverse yourself
        Matrix4x4& Matrix4x4::invert()
        {
            // Leave if the determinant is 0
            const float determinent = this->determinant();
            if (FloatComparisonUtil::isZero(determinent))
            {
                guarantee_that(FloatComparisonUtil::isZero(determinent) == false, "Matrix: Cannot invert a matrix with a 0 determinant");
                return *this;
            }
            
            #if S2D_USE_SIMD
                // Using SIMD version of inverse
                sse_inverse_mat4x4((float*)this);
            #else
                const float nm0 = _m6*_m11*_m13 - _m7*_m10*_m13 + _m7*_m9*_m14 - _m5*_m11*_m14 - _m6*_m9*_m15 + _m5*_m10*_m15;
                const float nm1 = _m3*_m10*_m13 - _m2*_m11*_m13 - _m3*_m9*_m14 + _m1*_m11*_m14 + _m2*_m9*_m15 - _m1*_m10*_m15;
                const float nm2 = _m2*_m7*_m13 - _m3*_m6*_m13 + _m3*_m5*_m14 - _m1*_m7*_m14 - _m2*_m5*_m15 + _m1*_m6*_m15;
                const float nm3 = _m3*_m6*_m9 - _m2*_m7*_m9 - _m3*_m5*_m10 + _m1*_m7*_m10 + _m2*_m5*_m11 - _m1*_m6*_m11;
                
                const float nm4 = _m7*_m10*_m12 - _m6*_m11*_m12 - _m7*_m8*_m14 + _m4*_m11*_m14 + _m6*_m8*_m15 - _m4*_m10*_m15;
                const float nm5 = _m2*_m11*_m12 - _m3*_m10*_m12 + _m3*_m8*_m14 - _m0*_m11*_m14 - _m2*_m8*_m15 + _m0*_m10*_m15;
                const float nm6 = _m3*_m6*_m12 - _m2*_m7*_m12 - _m3*_m4*_m14 + _m0*_m7*_m14 + _m2*_m4*_m15 - _m0*_m6*_m15;
                const float nm7 = _m2*_m7*_m8 - _m3*_m6*_m8 + _m3*_m4*_m10 - _m0*_m7*_m10 - _m2*_m4*_m11 + _m0*_m6*_m11;
                
                const float nm8 = _m5*_m11*_m12 - _m7*_m9*_m12 + _m7*_m8*_m13 - _m4*_m11*_m13 - _m5*_m8*_m15 + _m4*_m9*_m15;
                const float nm9 = _m3*_m9*_m12 - _m1*_m11*_m12 - _m3*_m8*_m13 + _m0*_m11*_m13 + _m1*_m8*_m15 - _m0*_m9*_m15;
                const float nm10 = _m1*_m7*_m12 - _m3*_m5*_m12 + _m3*_m4*_m13 - _m0*_m7*_m13 - _m1*_m4*_m15 + _m0*_m5*_m15;
                const float nm11 = _m3*_m5*_m8 - _m1*_m7*_m8 - _m3*_m4*_m9 + _m0*_m7*_m9 + _m1*_m4*_m11 - _m0*_m5*_m11;
                
                const float nm12 = _m6*_m9*_m12 - _m5*_m10*_m12 - _m6*_m8*_m13 + _m4*_m10*_m13 + _m5*_m8*_m14 - _m4*_m9*_m14;
                const float nm13 = _m1*_m10*_m12 - _m2*_m9*_m12 + _m2*_m8*_m13 - _m0*_m10*_m13 - _m1*_m8*_m14 + _m0*_m9*_m14;
                const float nm14 = _m2*_m5*_m12 - _m1*_m6*_m12 - _m2*_m4*_m13 + _m0*_m6*_m13 + _m1*_m4*_m14 - _m0*_m5*_m14;
                const float nm15 = _m1*_m6*_m8 - _m2*_m5*_m8 + _m2*_m4*_m9 - _m0*_m6*_m9 - _m1*_m4*_m10 + _m0*_m5*_m10;
                
                const float invDet = 1.0f / this->determinant();
                
                this->_m0 = nm0 * invDet;
                this->_m1 = nm1 * invDet;
                this->_m2 = nm2 * invDet;
                this->_m3 = nm3 * invDet;
                this->_m4 = nm4 * invDet;
                this->_m5 = nm5 * invDet;
                this->_m6 = nm6 * invDet;
                this->_m7 = nm7 * invDet;
                this->_m8 = nm8 * invDet;
                this->_m9 = nm9 * invDet;
                this->_m10 = nm10 * invDet;
                this->_m11 = nm11 * invDet;
                this->_m12 = nm12 * invDet;
                this->_m13 = nm13 * invDet;
                this->_m14 = nm14 * invDet;
                this->_m15 = nm15 * invDet;
            #endif
            
            return *this;
        }

        // Get the inverse of this matrix
        const Matrix4x4 Matrix4x4::getInverse() const
        {
            // Leave if the determinant is 0
            const float determinent = this->determinant();
            if (FloatComparisonUtil::isZero(determinent))
            {
                guarantee_that(FloatComparisonUtil::isZero(determinent) == false, "Matrix: Cannot invert a matrix with a 0 determinant");
                return Matrix4x4(*this);
            }

            #if S2D_USE_SIMD
                // Using SIMD version of inverse
                Matrix4x4 inverseCopy(*this);
                sse_inverse_mat4x4((float*)&inverseCopy);

                return inverseCopy;
            #else
                const float nm0 = _m6*_m11*_m13 - _m7*_m10*_m13 + _m7*_m9*_m14 - _m5*_m11*_m14 - _m6*_m9*_m15 + _m5*_m10*_m15;
                const float nm1 = _m3*_m10*_m13 - _m2*_m11*_m13 - _m3*_m9*_m14 + _m1*_m11*_m14 + _m2*_m9*_m15 - _m1*_m10*_m15;
                const float nm2 = _m2*_m7*_m13 - _m3*_m6*_m13 + _m3*_m5*_m14 - _m1*_m7*_m14 - _m2*_m5*_m15 + _m1*_m6*_m15;
                const float nm3 = _m3*_m6*_m9 - _m2*_m7*_m9 - _m3*_m5*_m10 + _m1*_m7*_m10 + _m2*_m5*_m11 - _m1*_m6*_m11;
                
                const float nm4 = _m7*_m10*_m12 - _m6*_m11*_m12 - _m7*_m8*_m14 + _m4*_m11*_m14 + _m6*_m8*_m15 - _m4*_m10*_m15;
                const float nm5 = _m2*_m11*_m12 - _m3*_m10*_m12 + _m3*_m8*_m14 - _m0*_m11*_m14 - _m2*_m8*_m15 + _m0*_m10*_m15;
                const float nm6 = _m3*_m6*_m12 - _m2*_m7*_m12 - _m3*_m4*_m14 + _m0*_m7*_m14 + _m2*_m4*_m15 - _m0*_m6*_m15;
                const float nm7 = _m2*_m7*_m8 - _m3*_m6*_m8 + _m3*_m4*_m10 - _m0*_m7*_m10 - _m2*_m4*_m11 + _m0*_m6*_m11;
                
                const float nm8 = _m5*_m11*_m12 - _m7*_m9*_m12 + _m7*_m8*_m13 - _m4*_m11*_m13 - _m5*_m8*_m15 + _m4*_m9*_m15;
                const float nm9 = _m3*_m9*_m12 - _m1*_m11*_m12 - _m3*_m8*_m13 + _m0*_m11*_m13 + _m1*_m8*_m15 - _m0*_m9*_m15;
                const float nm10 = _m1*_m7*_m12 - _m3*_m5*_m12 + _m3*_m4*_m13 - _m0*_m7*_m13 - _m1*_m4*_m15 + _m0*_m5*_m15;
                const float nm11 = _m3*_m5*_m8 - _m1*_m7*_m8 - _m3*_m4*_m9 + _m0*_m7*_m9 + _m1*_m4*_m11 - _m0*_m5*_m11;
                
                const float nm12 = _m6*_m9*_m12 - _m5*_m10*_m12 - _m6*_m8*_m13 + _m4*_m10*_m13 + _m5*_m8*_m14 - _m4*_m9*_m14;
                const float nm13 = _m1*_m10*_m12 - _m2*_m9*_m12 + _m2*_m8*_m13 - _m0*_m10*_m13 - _m1*_m8*_m14 + _m0*_m9*_m14;
                const float nm14 = _m2*_m5*_m12 - _m1*_m6*_m12 - _m2*_m4*_m13 + _m0*_m6*_m13 + _m1*_m4*_m14 - _m0*_m5*_m14;
                const float nm15 = _m1*_m6*_m8 - _m2*_m5*_m8 + _m2*_m4*_m9 - _m0*_m6*_m9 - _m1*_m4*_m10 + _m0*_m5*_m10;
                
                const float invDet = 1.0f / this->determinant();
            
                const Vector4 nv0(nm0 * invDet,  nm1 * invDet,  nm2 * invDet,  nm3 * invDet);
                const Vector4 nv1(nm4 * invDet,  nm5 * invDet,  nm6 * invDet,  nm7 * invDet);
                const Vector4 nv2(nm8 * invDet,  nm9 * invDet,  nm10 * invDet, nm11 * invDet);
                const Vector4 nv3(nm12 * invDet, nm13 * invDet, nm14 * invDet, nm15 * invDet);
                
                return Matrix4x4(nv0, nv1, nv2, nv3);
            #endif
        }

        
        
        
        
        
        
        
        
        
        
        
        #if S2D_USE_SIMD
            // SIMD inverse implementation from:
            // ftp://download.intel.com/design/PentiumIII/sml/24504301.pdf
            void sse_inverse_mat4x4(float *const src)
            {
                __m128 minor0, minor1, minor2, minor3;
                __m128 row0, row1, row2, row3;
                __m128 det, tmp1;

                // These 4 lines were added to prevent uninitialize warnings
                const __m128 zeroM = _mm_set_ps1(0.0f);
                tmp1 = zeroM;
                row1 = zeroM;
                row3 = zeroM;

                tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src)), (__m64*)(src + 4));
                row1 = _mm_loadh_pi(_mm_loadl_pi(row1, (__m64*)(src + 8)), (__m64*)(src + 12));
                row0 = _mm_shuffle_ps(tmp1, row1, 0x88);
                row1 = _mm_shuffle_ps(row1, tmp1, 0xDD);
                tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src + 2)), (__m64*)(src + 6));
                row3 = _mm_loadh_pi(_mm_loadl_pi(row3, (__m64*)(src + 10)), (__m64*)(src + 14));
                row2 = _mm_shuffle_ps(tmp1, row3, 0x88);
                row3 = _mm_shuffle_ps(row3, tmp1, 0xDD);
                // -----------------------------------------------
                tmp1 = _mm_mul_ps(row2, row3);
                tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
                minor0 = _mm_mul_ps(row1, tmp1);
                minor1 = _mm_mul_ps(row0, tmp1);
                tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
                minor0 = _mm_sub_ps(_mm_mul_ps(row1, tmp1), minor0);
                minor1 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor1);
                minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);
                // -----------------------------------------------
                tmp1 = _mm_mul_ps(row1, row2);
                tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
                minor0 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor0);
                minor3 = _mm_mul_ps(row0, tmp1);
                tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
                minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, tmp1));
                minor3 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor3);
                minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);
                // -----------------------------------------------
                tmp1 = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
                tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
                row2 = _mm_shuffle_ps(row2, row2, 0x4E);
                minor0 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor0);
                minor2 = _mm_mul_ps(row0, tmp1);
                tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
                minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, tmp1));
                minor2 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor2);
                minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);
                // -----------------------------------------------
                tmp1 = _mm_mul_ps(row0, row1);
                tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
                minor2 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor2);
                minor3 = _mm_sub_ps(_mm_mul_ps(row2, tmp1), minor3);
                tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
                minor2 = _mm_sub_ps(_mm_mul_ps(row3, tmp1), minor2);
                minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, tmp1));
                // -----------------------------------------------
                tmp1 = _mm_mul_ps(row0, row3);
                tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
                minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, tmp1));
                minor2 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor2);
                tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
                minor1 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor1);
                minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, tmp1));
                // -----------------------------------------------
                tmp1 = _mm_mul_ps(row0, row2);
                tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
                minor1 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor1);
                minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, tmp1));
                tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);
                minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, tmp1));
                minor3 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor3);
                // -----------------------------------------------
                det = _mm_mul_ps(row0, minor0);
                det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
                det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);
                tmp1 = _mm_rcp_ss(det);
                det = _mm_sub_ss(_mm_add_ss(tmp1, tmp1), _mm_mul_ss(det, _mm_mul_ss(tmp1, tmp1)));
                det = _mm_shuffle_ps(det, det, 0x00);
                minor0 = _mm_mul_ps(det, minor0);
                _mm_storel_pi((__m64*)(src), minor0);
                _mm_storeh_pi((__m64*)(src + 2), minor0);
                minor1 = _mm_mul_ps(det, minor1);
                _mm_storel_pi((__m64*)(src + 4), minor1);
                _mm_storeh_pi((__m64*)(src + 6), minor1);
                minor2 = _mm_mul_ps(det, minor2);
                _mm_storel_pi((__m64*)(src + 8), minor2);
                _mm_storeh_pi((__m64*)(src + 10), minor2);
                minor3 = _mm_mul_ps(det, minor3);
                _mm_storel_pi((__m64*)(src + 12), minor3);
                _mm_storeh_pi((__m64*)(src + 14), minor3);
            }
        #endif
        
    }
}