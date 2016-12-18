//
//  DebugGurarantee.hpp
//  Sea2D
//
//  Serves as a wrapped replacement to asserts, with no C function pollution
//  And better error printing
//
//  Created by Jibran Syed on 4/24/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef cpp_s2d_DebugGuarantee_hpp
#define cpp_s2d_DebugGuarantee_hpp



#ifdef NDEBUG
    /// Does nothing in release
    #define guarantee_that(CONDITION, ERROR_MESSAGE) ((void)0)
#else
    /// Error checking with assertions
    #define guarantee_that(CONDITION, ERROR_MESSAGE) (s2d_guarantee_assertion(CONDITION, #CONDITION, ERROR_MESSAGE, __FILE__, __LINE__))
#endif

namespace sea2d
{
    /// Assert error message will fire off if the condition is false (does nothing in release)
    void s2d_guarantee_assertion(const bool condition, const char* const conditionExpression, const char* const errorMessage, const char* const filePath, const unsigned int lineNumber);
}

#endif /* cpp_s2d_DebugGuarantee_hpp */
