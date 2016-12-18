//
//  StringFixed.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef StringFixed_hpp
#define StringFixed_hpp

#include <stdint.h>

namespace sea2d
{
    /// A simple C string wrapper that has max of 64 character (actually 63 + null char). Used mostly for resource and object names
    class StringFixed
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        StringFixed();
        
        /// C-String Ctor
        StringFixed(const char* const newCString);
        
        /// Copy Ctor
        StringFixed(const StringFixed& other);
        
        /// Copy Assignment
        StringFixed& operator=(const StringFixed& rhs);
        
        /// Destructor
        ~StringFixed();
        
        
        
        //
        // Methods
        //
        
        /// Set this string object with a C string
        void Set(const char* const newCString);
        
        /// Set this string object with another string object
        void Set(const StringFixed& otherString);
        
        /// Clears the characters in the string and makes it empty
        void Clear();
        
        /// Get this string as pure C string
        const char* const GetCString() const;
        
        /// Get the length of this string (including null terminating character)
        const unsigned int GetLength() const;
        
        /// Given an index, access the string character-by-character
        const char operator[](const unsigned int index) const;
        
        /// Compare this string with another string object
        const bool operator==(const StringFixed& otherString) const;
        
        /// Compare this string with a C string
        const bool operator==(const char* const cstring) const;
        
        /// Compare this string with another string object
        const bool operator!=(const StringFixed& otherString) const;
        
        /// Compare this string with a C string
        const bool operator!=(const char* const cstring) const;
        
        
        
    private:
        
        //
        // Typedefs
        //
        
        // uint64_t holds 8 chars
        /// A block of characters (for faster string writting) (should be unsigned)
        typedef uint64_t CharBlock_t;
        
        
        
        //
        // Data
        //
        
        CharBlock_t* charBuffer;    ///< Raw buffer for string data
        unsigned int len;           ///< The length of the string in chars (includes null terminator char)
        
        #if DEBUG
            const char* debugReadCharString;    ///< DEBUG: To read the string in the debugger. Do NOT use in implementation code!
        #endif
    };
}
#endif /* StringFixed_hpp */
