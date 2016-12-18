//
//  simd_declaration.h
//  Sea2D
//
//  Created by Jibran Syed on 4/19/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef simd_declaration_h
#define simd_declaration_h




//
// User Ajustable Flags
//

/// Switch to enable or disable SIMD types (1 or 0 respectively)
#define S2D_USE_SIMD 1








// Include SIMD if enabled
#if S2D_USE_SIMD
    #include <xmmintrin.h>
    #include <smmintrin.h>
#endif

#endif /* simd_declaration_h */
