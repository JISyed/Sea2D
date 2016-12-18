//
//  BitmapFont.hpp
//  Sea2D
//
//  Created by Jibran Syed on 6/7/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef BitmapFont_hpp
#define BitmapFont_hpp

#include "Sprite.hpp"
#include "engine/GraphicsSys/Texture.hpp"
#include "engine/DataTypes/LinkedList.hpp"
#include "engine/DataTypes/StringFixed.hpp"

namespace sea2d
{
    /// A collection of sprites that represent a glyph for a font
    class BitmapFont
    {
    public:
        
        //
        // Essentials
        //
        
        // Ctor
        BitmapFont(const char* const fontDefinitionFile);
        
        // Destructor
        ~BitmapFont();
        
        
        //
        // Methods
        //
        
        /// Get the glyph sprite given the character it represents (returns nullptr if glyph not avaliable)
        Sprite* const GetGlyphSprite(const char glyphCharacter) const;
        
        /// Get the unique ID for this font
        const unsigned GetId() const;
        
        /// Get the name of this font
        const StringFixed& GetName() const;
        
        /// Get the texture for this font
        Texture* const GetTexture();
        
        
    private:
        
        //
        // Data
        //
        
        unsigned int id;                ///< The unique ID of this font
        LinkedList<Sprite> glyphMap;    ///< The map of glyphs for the font
        StringFixed name;               ///< The name of this font
        Texture* texture;               ///< The texture containing the glyphs
        
        
        //
        // Deleted Methods
        //
        
        // No Default Ctor
        BitmapFont() = delete;
        
        // No Copy Ctor
        BitmapFont(const BitmapFont& other) = delete;
        
        // No Copy Assignment
        BitmapFont& operator=(const BitmapFont& rhs) = delete;
        
    };
}
#endif /* BitmapFont_hpp */
