//
//  StringFixed.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/10/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "StringFixed.hpp"
#include <cstring>
#include "engine/AppSys/DebugGuarantee.hpp"

//
// Macros
//


//// String options

// Number of chars in a string (MUST be multiple of S2D_STR_BLOCK_SIZE)
#define S2D_STR_CHAR_LEN  64



//// Macros derived from string length

// Size of a "block" of characters, that makes up the buffer of data
#define S2D_STR_BLOCK_SIZE  (sizeof(sea2d::StringFixed::CharBlock_t))

// Number of blocks in the string data buffer
#define S2D_STR_BLOCK_TALLY  (S2D_STR_CHAR_LEN / S2D_STR_BLOCK_SIZE)

// The index of the last character in the buffer (if accessed as char*)
#define S2D_STR_LAST_CHAR_IDX  (S2D_STR_CHAR_LEN - 1)


//
// StringFixed Implementation
//

namespace sea2d
{
    // Default Ctor
    StringFixed::StringFixed() :
        charBuffer(nullptr),
        len(0)
    {
        this->charBuffer = new CharBlock_t[S2D_STR_BLOCK_TALLY];
        
        #if DEBUG
            this->debugReadCharString = (const char*) this->charBuffer;
        #endif
        
        this->Clear();
    }
    
    // C-String Ctor
    StringFixed::StringFixed(const char* const newCString) :
        charBuffer(nullptr),
        len(0)
    {
        guarantee_that(newCString != nullptr, "Constuction a fixed string with nullptr!");
        
        this->charBuffer = new CharBlock_t[S2D_STR_BLOCK_TALLY];
        
        #if DEBUG
            this->debugReadCharString = (const char*) this->charBuffer;
        #endif
        
        this->Clear();
        this->Set(newCString);
    }
    
    // Copy Ctor
    StringFixed::StringFixed(const StringFixed& other) :
        charBuffer(0),
        len(other.len)
    {
        this->charBuffer = new CharBlock_t[S2D_STR_BLOCK_TALLY];
        
        #if DEBUG
            this->debugReadCharString = (const char*) this->charBuffer;
        #endif
        
        for(unsigned int i = 0; i < S2D_STR_BLOCK_TALLY; ++i)
        {
            this->charBuffer[i] = other.charBuffer[i];
        }
    }
    
    // Copy Assignment Overload
    StringFixed& StringFixed::operator=(const StringFixed& rhs)
    {
        if(this == &rhs)
        {
            return *this;
        }
        
        this->Set(rhs);
        
        return *this;
    }
    
    // Dtor
    StringFixed::~StringFixed()
    {
        delete [] this->charBuffer;
    }
    
    
    
    
    /// Set this string object with a C string
    void StringFixed::Set(const char *const newCString)
    {
        guarantee_that(newCString != nullptr, "Setting a fixed string with nullptr!");
        
        char* charAccess = (char*) this->charBuffer;
        const size_t newStrLen = std::strlen(newCString) + 1;
        
        size_t finalStrLen = newStrLen;
        if(newStrLen > S2D_STR_CHAR_LEN)
        {
            finalStrLen = S2D_STR_CHAR_LEN;
        }
        
        this->Clear();
        
        std::memcpy(charAccess, newCString, finalStrLen);
        charAccess[S2D_STR_LAST_CHAR_IDX] = '\0';
        this->len = (unsigned int) finalStrLen;
    }
    
    
    
    /// Set this string object with another string object
    void StringFixed::Set(const StringFixed& otherString)
    {
        for(unsigned int i = 0; i < S2D_STR_BLOCK_TALLY; ++i)
        {
            this->charBuffer[i] = otherString.charBuffer[i];
        }
        this->len = otherString.len;
    }
    
    
    
    /// Clears the characters in the string and makes it empty
    void StringFixed::Clear()
    {
        for(unsigned int i = 0; i < S2D_STR_BLOCK_TALLY; ++i)
        {
            this->charBuffer[i] = 0;
        }
        this->len = 0;
    }
    
    
    
    
    /// Get this string as pure C string
    const char* const StringFixed::GetCString() const
    {
        return (const char*) this->charBuffer;
    }
    
    
    
    /// Get the length of this string (including null terminating character)
    const unsigned int StringFixed::GetLength() const
    {
        return this->len;
    }
    
    
    
    /// Given an index, access the string character-by-character
    const char StringFixed::operator[](const unsigned int index) const
    {
        guarantee_that(index < this->len, "Fixed String indexer: Out of bounds!");
        
        const char* const charAccess = (const char*) this->charBuffer;
        return charAccess[index];
    }
    
    
    
    /// Compare this string with another string object
    const bool StringFixed::operator==(const StringFixed& otherString) const
    {
        bool isEqual = true;
        
        for(unsigned int i = 0; i < S2D_STR_BLOCK_TALLY; ++i)
        {
            if(this->charBuffer[i] != otherString.charBuffer[i])
            {
                isEqual = false;
                break;
            }
        }
        
        return isEqual;
    }
    
    
    
    /// Compare this string with a C string
    const bool StringFixed::operator==(const char* const cstring) const
    {
        guarantee_that(cstring != nullptr, "Comparing a fixed string to nullptr!");
        
        const char* const charAccess = (const char*) this->charBuffer;
        
        if(charAccess[0] == cstring[0])
        {
            if(std::strcmp(charAccess, cstring) == 0)
            {
                return true;
            }
        }
        
        return false;
    }
    
    
    
    /// Compare this string with another string object
    const bool StringFixed::operator!=(const StringFixed& otherString) const
    {
        return !this->operator==(otherString);
    }
    
    
    
    /// Compare this string with a C string
    const bool StringFixed::operator!=(const char* const cstring) const
    {
        return !this->operator==(cstring);
    }
    
    
    
    
}
