//
//  Color.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/24/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef Color_hpp
#define Color_hpp

namespace sea2d
{
    /// Represents normalized color values in the RBGA format
    class Color
    {
    public:
        
        //
        // Big Four
        //
        
        /// Default Ctor {0,0,0,1}
        Color();
        
        /// Specialized Ctor
        Color(float red, float green, float blue, float alpha = 1.0f);
        
        /// Copy Ctor
        Color(const Color& rhs);
        
        /// Dtor
        ~Color();
        
        /// Copy Assignment
        Color& operator=(const Color& rhs);
        
        
        
        
        //
        // Getters
        //
        
        /// Get the red value
        const float r() const;
        /// Get the green value
        const float g() const;
        /// Get the blue value
        const float b() const;
        /// Get the alpha value
        const float a() const;
        
        /// Get raw color data starting at red. Used with OpenGL calls
        const float* const GetRawData() const;
        
        
        
        //
        // Setters
        //
        
        /// Set the red value
        void SetRed(const float red);
        /// Set the green value
        void SetGreen(const float green);
        /// Set the blue value
        void SetBlue(const float blue);
        /// Set the alpha value
        void SetAlpha(const float alpha);
        
        /// Set all color values at once
        void Set(const float red, const float green, const float blue, const float alpha = 1.0f);
        
        
        
        //
        // Predefined Colors
        //
        
        static const Color White;
        static const Color Black;
        static const Color Red;
        static const Color Orange;
        static const Color Yellow;
        static const Color Green;
        static const Color Cyan;
        static const Color Blue;
        static const Color Purple;
        static const Color Magenta;
        
        
        
    private:
        
        //
        // Data
        //
        
        float _r;   ///< Red
        float _g;   ///< Green
        float _b;   ///< Blue
        float _a;   ///< Alpha (for Opacity)
        
        
        
        //
        // Deleted Methods
        //
        
        /// No move ctor
        Color(Color&& other) = delete;
        
        /// No move assignment
        Color& operator=(Color&& other) = delete;
    };
}
#endif /* Color_hpp */
