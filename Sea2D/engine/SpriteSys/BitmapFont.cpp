//
//  BitmapFont.cpp
//  Sea2D
//
//  Created by Jibran Syed on 6/7/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "BitmapFont.hpp"
#include "engine/AppSys/DebugGuarantee.hpp"
#include "SpriteRegistry.hpp"
#include "engine/GraphicsSys/TextureRegistry.hpp"
#include "engine/AppSys/ResourceUtility.hpp"
#include <yaml-cpp/yaml.h>
#include <cstdio>
#include "engine/AppSys/IdGenerator.hpp"


//
// Sprite YAML Options
//

#define S2D_FONT_GLYPHS_YML_BASE_KEY    "Glyphs"
#define S2D_FONT_TEXTURE_YAML_KEY       "TextureName"


namespace sea2d
{
    //
    // Statics
    //
    
    static IdGenerator s_idGen;
    
    
    
    // Ctor
    BitmapFont::BitmapFont(const char* const fontDefinitionFile) :
        id(s_idGen.MakeNewId()),
        glyphMap(),
        name(),
        texture(nullptr)
    {
        // Try to open the YAML file containing the font definition
        const std::string filePath = ResouceUtility::GetFullPathForFileName(fontDefinitionFile);
        FILE* yamlFileHandle = std::fopen(filePath.c_str(), "r");
        guarantee_that(yamlFileHandle != nullptr, "Font could not find YAML definition file!");
        
        if(yamlFileHandle != nullptr)
        {
            // Close the test file stream
            std::fclose(yamlFileHandle);
            
            // Open the font definition as a YAML file
            YAML::Node yamlRoot = YAML::LoadFile(filePath);
            const YAML::Node& glyphs = yamlRoot[S2D_FONT_GLYPHS_YML_BASE_KEY];
            
            // Get the texture for this font
            const YAML::Node& textureNameNode = yamlRoot[S2D_FONT_TEXTURE_YAML_KEY];
            std::string textureName = textureNameNode.as<std::string>();
            Texture* const fontTexture = TextureRegistry::Find(textureName.c_str());
            guarantee_that(fontTexture != nullptr, "Could not find the texture associated to a font!");
            this->texture = fontTexture;
            
            // Texture name is font name
            this->name = fontTexture->GetName();
            
            // Create a new sprite for every glyph listed in this YAML file
            const unsigned int NumOfGlyphsToExtract = (unsigned int) glyphs.size();
            for(unsigned int i = 0; i < NumOfGlyphsToExtract; i++)
            {
                // Get the current glyph node
                const YAML::Node& currGlyph = glyphs[i]["Glyph"];
                
                // Get glyphs character
                const char glyphChar = currGlyph["Character"].as<char>();
                
                // The image frame associated with this glyph
                ImageFrame** spriteFrames = new ImageFrame*[1];
                const unsigned int currFrameIdx = (unsigned int) currGlyph["ImageFrame"].as<int>();
                ImageFrame* currFrame = fontTexture->GetImageFrame(currFrameIdx);
                spriteFrames[0] = currFrame;
                
                // Create sprite and add to regirstry (this font object doesn't manage glyphs!)
                Sprite* const newSpriteGlyph = new Sprite(currFrame->GetName(), 1, spriteFrames, nullptr, fontTexture);
                SpriteRegistry::Add(newSpriteGlyph);
                
                // Add sprite into glyph lookup table
                this->glyphMap.AddSorted(newSpriteGlyph, (int) glyphChar);
            }
            
        }
    }
    
    // Dtor
    BitmapFont::~BitmapFont()
    {
        // Clear glyph list (not NOT delete sprites, registry needs to do that)
        this->glyphMap.Clear();
    }
    
    
    
    /// Get the glyph sprite given the character it represents
    Sprite* const BitmapFont::GetGlyphSprite(const char glyphCharacter) const
    {
        return this->glyphMap.FindById((int) glyphCharacter);
    }
    
    
    /// Get the unique ID for this font
    const unsigned BitmapFont::GetId() const
    {
        return this->id;
    }
    
    /// Get the name of this font
    const StringFixed& BitmapFont::GetName() const
    {
        return this->name;
    }
    
    /// Get the texture for this font
    Texture* const BitmapFont::GetTexture()
    {
        return this->texture;
    }
    
}