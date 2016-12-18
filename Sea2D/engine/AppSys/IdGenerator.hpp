//
//  IdGenerator.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/12/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef IdGenerator_hpp
#define IdGenerator_hpp

namespace sea2d
{
    /// Generates incrementing IDs of type uint. Not a singleton; needs to be constructed
    class IdGenerator
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        IdGenerator();
        
        /// Value Ctor
        explicit IdGenerator(const unsigned int startingValue);
        
        /// Copy Ctor
        IdGenerator(const IdGenerator& other);
        
        /// Copy Assignment
        IdGenerator& operator=(const IdGenerator& rhs);
        
        /// Destructor
        ~IdGenerator();
        
        
        //
        // Methods
        //
        
        /// Generate a new ID and return it. Will return a value between 1 and 4294967295 (man uint32)
        const unsigned int MakeNewId();
        
        
    private:
        
        //
        // Data
        //
        
        unsigned int currentId;     ///< The current value that will be pre-incremented and returned
        
    };
}

#endif /* IdGenerator_hpp */
