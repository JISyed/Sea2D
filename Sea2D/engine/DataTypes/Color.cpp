//
//  Color.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/24/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Color.hpp"
#include "engine/MathSys/Mathf.hpp"

namespace sea2d
{
    //
    // Statics
    //
    
    const Color Color::White(1.0f, 1.0f, 1.0f, 1.0f);
    const Color Color::Black(0.0f, 0.0f, 0.0f, 1.0f);
    const Color Color::Red(1.0f, 0.0f, 0.0f, 1.0f);
    const Color Color::Orange(1.0f, 0.5f, 0.0f, 1.0f);
    const Color Color::Yellow(1.0f, 1.0f, 0.0f, 1.0f);
    const Color Color::Green(0.0f, 1.0f, 0.0f, 1.0f);
    const Color Color::Cyan(0.0f, 1.0f, 1.0f, 1.0f);
    const Color Color::Blue(0.0f, 0.0f, 1.0f, 1.0f);
    const Color Color::Purple(0.5f, 0.0f, 1.0f, 1.0f);
    const Color Color::Magenta(1.0f, 0.0f, 1.0f, 1.0f);
    
    
    
    //
    // Methods
    //
    
    Color::Color() :
        _r(0.0f),
        _g(0.0f),
        _b(0.0f),
        _a(1.0f)
    {
    }
    
    
    Color::Color(float red, float green, float blue, float alpha) :
        _r(Mathf::Clamp01(red)),
        _g(Mathf::Clamp01(green)),
        _b(Mathf::Clamp01(blue)),
        _a(Mathf::Clamp01(alpha))
    {
    }
    
    
    Color::Color(const Color& rhs) :
        _r(rhs._r),
        _g(rhs._g),
        _b(rhs._b),
        _a(rhs._a)
    {
    }
    
    
    Color::~Color()
    {
    }
    
    
    Color& Color::operator=(const Color& rhs)
    {
        if (this == &rhs)
        {
            return *this;
        }
        
        this->_r = rhs._r;
        this->_g = rhs._g;
        this->_b = rhs._b;
        this->_a = rhs._a;
        
        return *this;
    }
    
    
    
    
    
    
    const float Color::r() const
    {
        return this->_r;
    }
    
    const float Color::g() const
    {
        return this->_g;
    }
    
    const float Color::b() const
    {
        return this->_b;
    }
    
    const float Color::a() const
    {
        return this->_a;
    }
    
    
    
    
    
    
    
    void Color::SetRed(const float red)
    {
        this->_r = Mathf::Clamp01(red);
    }
    
    void Color::SetGreen(const float green)
    {
        this->_g = Mathf::Clamp01(green);
    }
    
    void Color::SetBlue(const float blue)
    {
        this->_b = Mathf::Clamp01(blue);
    }
    
    void Color::SetAlpha(const float alpha)
    {
        this->_a = Mathf::Clamp01(alpha);
    }
    
    void Color::Set(const float red, const float green, const float blue, const float alpha)
    {
        this->_r = Mathf::Clamp01(red);
        this->_g = Mathf::Clamp01(green);
        this->_b = Mathf::Clamp01(blue);
        this->_a = Mathf::Clamp01(alpha);
    }
    
    
    
    
    const float* const Color::GetRawData() const
    {
        return &(this->_r);
    }
}