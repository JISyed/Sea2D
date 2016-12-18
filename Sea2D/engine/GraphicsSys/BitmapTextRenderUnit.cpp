//
//  BitmapTextRenderUnit.cpp
//  Sea2D
//
//  Created by Jibran Syed on 6/8/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "BitmapTextRenderUnit.hpp"
#include "MeshRegistry.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include "engine/SpriteSys/Sprite.hpp"

namespace sea2d
{
    // Default Ctor
    BitmapTextRenderUnit::BitmapTextRenderUnit(Shader* const newShader, BitmapFont* const newFont, const StringFixed& initialText) :
        RenderUnit(newShader),
        text(initialText),
        font(newFont),
        mesh(nullptr),
        textWidthScale(1.0f)
    {
        static const unsigned int QuadMeshId = MeshRegistry::Find("Quad")->GetId();
        this->mesh = MeshRegistry::Find(QuadMeshId);
        
        guarantee_that(newShader != nullptr, "New RenderUnit cannot take in null shader!");
        guarantee_that(newFont != nullptr, "New RenderUnit cannot take in null font!");
    }
    
    // VIRTUAL
    // Dtor
    BitmapTextRenderUnit::~BitmapTextRenderUnit()
    {
    }
    
    
    
    /// Get the font used for this render unit
    BitmapFont* const BitmapTextRenderUnit::GetFont()
    {
        return this->font;
    }
    
    
    /// Change the font used for rendering. Do not call while in render loop!
    void BitmapTextRenderUnit::ChangeFont(BitmapFont* const newFont)
    {
        guarantee_that(newFont != nullptr, "Changing font, but being given a null font!");
        
        this->font = newFont;
    }
    
    /// Change the text being displayed
    void BitmapTextRenderUnit::ChangeText(const char* const newText)
    {
        guarantee_that(newText != nullptr, "Changine text, but its null!");
        
        this->text = newText;
    }
    
    /// Change the width scale of this font renderer
    void BitmapTextRenderUnit::ChangeWidthScale(const float newWidthScale)
    {
        this->textWidthScale = newWidthScale;
    }
    
    
    // VIRTUAL OVERRIDE
    /// Setup render state, such as binding data or setting uniforms (called before OnDraw())
    void BitmapTextRenderUnit::OnBeforeDraw()
    {
        
        this->mesh->MakeActive();
        this->font->GetTexture()->MakeActive();
        
//        
//        
//        
//        Rect normalizedDimensions = this->sprite->operator[](this->animator->GetCurrentFrameIndex())->GetNormalizedDimensions();
//        
//        // This weird calculation is needed to translate the texture's origin to OpenGL's origin (top-left vs. bottom-left)
//        normalizedDimensions.origin.y() = 1.0f - normalizedDimensions.origin.y() - normalizedDimensions.height;
//        
//        this->GetShader()->SetUniform("spriteRectUV", normalizedDimensions);
    }
    
    // VIRTUAL OVERRIDE
    /// Perform actual draw call (or multiple if needed)
    void BitmapTextRenderUnit::OnDraw()
    {
        //glDrawElements(GL_TRIANGLES, this->mesh->GetNumberOfTriangles() * 3, GL_UNSIGNED_INT, 0);
        
        
        
        
        float xDisplacer = 0.0f;
        float currentGlyphWidth = 0.0f;
        float scaledGlyphIncrementer = 0.0f;
        
        const unsigned int textLen = this->text.GetLength() - 1;
        for(unsigned int c = 0; c < textLen; c++)
        {
            Sprite* glyphSprite = this->font->GetGlyphSprite(this->text[c]);
            if(glyphSprite == nullptr)
            {
                continue;
            }
            
            const Rect pixelDimensions = glyphSprite->operator[](0)->GetPixelDimensions();
            currentGlyphWidth = pixelDimensions.width;
            
            scaledGlyphIncrementer = (currentGlyphWidth * 0.58f) * this->textWidthScale;
            xDisplacer += scaledGlyphIncrementer;
            
            this->DrawSingleGlyph(glyphSprite, xDisplacer);
            
            xDisplacer += scaledGlyphIncrementer;
        }
    }
    
    
    /// Draws a single font glyph given the character to draw and x displacement
    void BitmapTextRenderUnit::DrawSingleGlyph(Sprite* const glyphSprite, const float xDisplacement)
    {
        Rect normalizedDimensions = glyphSprite->operator[](0)->GetNormalizedDimensions();
        
        // This weird calculation is needed to translate the texture's origin to OpenGL's origin (top-left vs. bottom-left)
        normalizedDimensions.origin.y() = 1.0f - normalizedDimensions.origin.y() - normalizedDimensions.height;
        
        const Rect pixelDimens = glyphSprite->operator[](0)->GetPixelDimensions();
        const Vector2 glyphScaling = Vector2(pixelDimens.width, pixelDimens.height);
        
        this->GetShader()->SetUniform("spriteRectUV", normalizedDimensions);
        this->GetShader()->SetUniform("xDisplacement", xDisplacement / glyphScaling.x());
        this->GetShader()->SetUniform("glyphScale", glyphScaling);
        
        glDrawElements(GL_TRIANGLES, this->mesh->GetNumberOfTriangles() * 3, GL_UNSIGNED_INT, 0);
    }
    
}