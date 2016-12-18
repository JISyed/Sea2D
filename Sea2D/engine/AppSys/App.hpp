//
//  App.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/7/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//
#ifndef App_S2D_hpp
#define App_S2D_hpp

#include "engine/DataTypes/Color.hpp"


//
// Forward Declares
//

/// Forward declare GLFW's window
class GLFWwindow;

namespace sea2d
{
    // Forward declare Time class
    class Time;
    
    // Forward declare ShaderRegistry
    class ShaderRegistry;
    
    // Forward declare MeshRegistry
    class MeshRegistry;
    
    // Forward declare TextureRegistry
    class TextureRegistry;
    
    // Forward declare SpriteRegistry
    class SpriteRegistry;
    
    // Forward declare BitmapFontRegistry
    class BitmapFontRegistry;
    
    // Forward declare CameraRegistry
    class CameraRegistry;
    
    // Forward declare RenderUnitRegistry
    class RenderUnitRegistry;
    
    // Forward declare EntityRegistry
    class EntityRegistry;
    
    // Forward declare SceneRegistry
    class SceneRegistry;
    
    namespace Input
    {
        // Forward declare Keyboard class
        class Keyboard;
        
        // Forward declare Mouse class
        class Mouse;
    }
}




//
// App Header
//

namespace sea2d
{
    /// The maintainer of the engine's runtime
    class App
    {
    public:
        
        //
        // Essentials
        //
        
        // Default Ctor
        App();
        
        // Destructor
        ~App();
        
        
        
        
        //
        // Methods
        //
        
        
        /// Run the App from start to finish. Only call once!
        void Run();
        
        
        
        
        //
        // Static Methods
        //
        
        /// Get the GLFW window pointer. Do NOT delete this pointer!
        static GLFWwindow* const GetGlfwWindow();
        
        /// Get the width of the App's window
        static unsigned int GetWindowWidth();
        
        /// Get the height of the App's window
        static unsigned int GetWindowHeight();
        
        /// Get the X position of the window on the desktop
        static int GetWindowX();
        
        /// Get the Y position of the window on the desktop (0 is top of screen)
        static int GetWindowY();
        
        /// Set the X position of the window on the desktop
        static void SetWindowPositionX(const int newX);
        
        /// Set the Y position of the window on the desktop
        static void SetWindowPositionY(const int newY);
        
        /// Set both the X and Y position of the window on the desktop at once
        static void SetWindowPosition(const int newX, const int newY);
        
        /// Set the clear color of the window's canvas (alpha doesn't do anything here)
        static void SetClearColor(const Color& newClearColor);
        
        /// Get the clear color of the window's canvas (alpha doesn't do anything here)
        static const Color GetClearColor();
        
        
        
    private:
        
        //
        // Data
        //
        
        Time* appTimeData;                      ///< Manages the time data of the app
        GLFWwindow* theWindow;                  ///< The only window of the App, made by GLFW
        Input::Keyboard* theKeyboard;           ///< The keyboard states managed by the app
        Input::Mouse* theMouse;                 ///< The mouse states managed by the app
        ShaderRegistry* shaderRegistry;         ///< Container for all shader
        MeshRegistry* meshRegistry;             ///< Container for all meshes
        TextureRegistry* textureRegistry;       ///< Container for all textures
        SpriteRegistry* spriteRegistry;         ///< Container for all sprites
        BitmapFontRegistry* bitmapFontRegistry; ///< Container for all fonts
        CameraRegistry* cameraRegistry;         ///< Container for all cameras
        RenderUnitRegistry* renderUnitRegistry; ///< Container for all RenderUnits
        EntityRegistry* entityRegistry;         ///< Container for all Entities
        SceneRegistry* sceneRegistry;           ///< Container for all Scenes
        Color clearColor;                       ///< The OpenGL canvas clear color
        unsigned int width;                     ///< The width of the App's window
        unsigned int height;                    ///< The height of the App's window
        int windowX;                            ///< The X position of the window on the desktop
        int windowY;                            ///< The Y position of the window on the desktop
        const char* title;                      ///< The text shown on the window's title bar
        
        
        
        
        
        //
        // Private Routines
        //
        
        /// Mostly concerned with window and graphics setup (before App::Setup())
        bool PreSetup();
        
        /// Initialize and setup various systems
        void Setup();
        
        /// The main loop of the App
        void Loop();
        
        /// The shutdown of various systems
        void Shutdown();
        
        /// Mostly concerned with window and graphics shutdown (after App::Shutdown())
        void PostShutdown();
        
        
        
        
        //
        // GLFW Events
        //
        
        /// Called when the GLFW window resizes (specific to pixel size)
        void OnFrameBufferResize(GLFWwindow* const window, const int newWidth, const int newHeight);
        
        /// Called when a key is pressed on the keyboard
        void OnKeyboardTriggered(GLFWwindow* const window, const int key, const int scancode, const int action, const int mods);
        
        /// Called when the scroll-wheel moves
        void OnScrollWheelMove(GLFWwindow* const window, const float hDelta, const float vDelta);
        
        /// Called when the window moves
        void OnWindowMove(GLFWwindow* const window, const int xPosition, const int yPosition);
        
        

        
        
        //
        // Statics
        //
        
        /// Private singleton access for App
        static App* s_appSingeton;
        
        /// Route GLFW framebuffer size callback into App
        static void callbackFramebufferSize(GLFWwindow* window, int newWidth, int newHeight);
        
        /// Route GLFW keyboard callback into App
        static void callbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
        
        /// Route GFLW scroll-wheel callback into App
        static void callbackScrollWheel(GLFWwindow* window, double xoffset, double yoffset);
        
        /// Route GLFW window move callback into App
        static void callbackWindowMove(GLFWwindow* window, int newX, int newY);
        
        
        
        
        //
        // Deleted Methods
        //
        
        // No Copy Ctor
        App(const App& other) = delete;
        
        // No Copy Assignment
        App& operator=(const App& rhs) = delete;
        
        // No Move Ctor
        App(App&& other) = delete;
        
        // No Move Assignment
        App& operator=(App&& rhs) = delete;
        
        
    };
}

#endif /* App_S2D_hpp */
