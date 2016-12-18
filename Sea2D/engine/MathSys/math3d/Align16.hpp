#ifndef ALIGN_16_H
#define ALIGN_16_H

#include <stddef.h>
#include <mm_malloc.h>

// Define aligned malloc and free
#if defined(__APPLE__) || defined(__linux__)
    #define S2D_ALIGNED_MALLOC  _mm_malloc
    #define S2D_ALIGNED_FREE    _mm_free
#elif defined(_WIN32)
    #define S2D_ALIGNED_MALLOC  _aligned_malloc
    #define S2D_ALIGNED_FREE    _aligned_free
#endif

// Define align specifiers : http://www.gamedev.net/page/resources/_/technical/general-programming/practical-cross-platform-simd-math-r3068
#if defined( _WIN32 )
    #define S2D_BEGIN_ALIGNED(name, alignment)     __declspec(align(alignment)) name
    #define S2D_END_ALIGNED(name, alignment)
#elif defined( __APPLE__ ) || defined( __linux__ )
    #define S2D_BEGIN_ALIGNED(name, alignment)     name
    #define S2D_END_ALIGNED(name, alignment)       __attribute__((aligned(alignment)))
#endif

namespace sea2d
{
    /// Inherit from this to get 16 byte alignment in the heap
	class Align16
	{
	public:
		void *operator new(size_t size)
		{
            void *p = S2D_ALIGNED_MALLOC(size, 16);
			return p;
		}

        void *operator new[] (size_t size)
		{
            void *p = S2D_ALIGNED_MALLOC(size, 16);
			return p;
		}

        void operator delete(void *p)
		{
            S2D_ALIGNED_FREE(p);
		}

		void operator delete[] (void *p)
		{
            S2D_ALIGNED_FREE(p);
		}
	};
}

#endif