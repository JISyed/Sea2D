//
//  BitmapTextRenderUnit.hpp
//  Sea2D
//
//  Created by Jibran Syed on 6/8/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef BitmapTextRenderUnit_hpp
#define BitmapTextRenderUnit_hpp

#include "RenderUnit.hpp"
#include "engine/SpriteSys/BitmapFont.hpp"
#include "engine/MathSys/Vector2.hpp"

namespace sea2d
{
    // Foward declare Mehs
    class Mesh;
    
    /// A RenderUnit that draws a textured mesh
    class BitmapTextRenderUnit final : public RenderUnit
    {
    public:
        
        //
        // Essentials
        //
        
        /// Ctor
        BitmapTextRenderUnit(Shader* const newShader, BitmapFont* const newFont, const StringFixed& initialText);
        
        /// Destructor
        virtual ~BitmapTextRenderUnit();
        
        
        //
        // Methods
        //
        
        /// Get the font used for this render unit
        BitmapFont* const GetFont();
        
        
        /// Change the font used for rendering. Do not call while in render loop!
        void ChangeFont(BitmapFont* const newFont);
        
        /// Change the text being displayed
        void ChangeText(const char* const newText);
        
        /// Change the width scale of this font renderer
        void ChangeWidthScale(const float newWidthScale);
        
        
    protected:
        
        
        /// Setup render state, such as binding data or setting uniforms (called before OnDraw())
        virtual void OnBeforeDraw() override;
        
        /// Perform actual draw call (or multiple if needed)
        virtual void OnDraw() override;
        
        
        
    private:
        
        //
        // Data
        //
        
        StringFixed text;                   ///< Text to render
        BitmapFont* font;                   ///< The font used by this render unit
        Mesh* mesh;                         ///< Should be Quad
        float textWidthScale;               ///< The scale of the text's Entity
        
        
        //
        // Private Methods
        //
        
        /// Draws a single font glyph given the character to draw and x displacement
        void DrawSingleGlyph(Sprite* const glyphSprite, const float xDisplacement);
        
        
        
        
        //
        // Deleted Methods
        //
        
        /// No Default Ctor
        BitmapTextRenderUnit() = delete;
        
    };
}
#endif /* BitmapTextRenderUnit_hpp */
