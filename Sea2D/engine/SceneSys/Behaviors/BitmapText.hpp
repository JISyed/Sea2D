//
//  BitmapText.hpp
//  Sea2D
//
//  Created by Jibran Syed on 6/8/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef BitmapText_hpp
#define BitmapText_hpp

#include "Behavior.hpp"
#include "engine/SpriteSys/BitmapFont.hpp"
#include "engine/GraphicsSys/Shader.hpp"
#include "engine/GraphicsSys/BitmapTextRenderUnit.hpp"

namespace sea2d
{
    /// Behavior that draws text with a BitmapFont
    class BitmapText final : public Behavior
    {
    public:
        
        //
        // Essentials
        //
        
        /// Default Ctor
        BitmapText();
        
        /// Destructor
        virtual ~BitmapText();
        
        /// Get the identity unique to this behavior type. Defined in BehaviorIdentity enum
        virtual const BehaviorIdentity GetBehaviorIdentity() const override;
        
        
        
        //
        // Additonal Methods
        //
        
        
        /// Will this render behavior draw in the render loop?
        const bool WillDraw() const;
        
        /// Set whether this render behavior will draw or not
        void SetDrawFlag(const bool willDraw);
        
        /// Get the tint color of this render behavior
        const Color& GetTintColor() const;
        
        /// Set the tint color of this render behavior
        void SetTintColor(const Color& newTintColor);
        
        
        /// Get the current shader of this render unit
        Shader* const GetShader();
        
        /// Change the shader of this render unit
        void ChangeShader(Shader* const newShader);
        
        
        /// Get the BitmapFont used in this renderer
        BitmapFont* const GetBitmapFont() const;
        
        /// Change the BitmapFont used in this renderer
        void ChangeBitmapFont(BitmapFont* const differentBitmapFont);
        
        /// Change text to render
        void ChangeText(const char* const newText);
        
        
        
    protected:
        
        
        //
        // Events
        //
        
        /// Called when the Behavior is added to an Entity (called after constructor)
        virtual void OnStart() override;
        
        /// Called every iteration of the game loop
        virtual void OnUpdate() override;
        
        /// Called whene the Behavior is removed from an Entity (called before destructor)
        virtual void OnDestroy() override;
        
        
    private:
        
        //
        // Data
        //
        
        BitmapTextRenderUnit* renderUnit;
        
        
        
    };
}
#endif /* BitmapText_hpp */
