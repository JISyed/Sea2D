//
//  App.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/7/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "App.hpp"

#include "engine/AppSys/DebugGuarantee.hpp"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "engine/InputSys/Keyboard.hpp"
#include "engine/InputSys/Mouse.hpp"
#include "engine/TimeSys/Time.hpp"

#include "engine/GraphicsSys/ShaderRegistry.hpp"
#include "engine/GraphicsSys/MeshRegistry.hpp"
#include "engine/GraphicsSys/TextureRegistry.hpp"
#include "engine/SpriteSys/SpriteRegistry.hpp"
#include "engine/CameraSys/CameraRegistry.hpp"
#include "engine/GraphicsSys/RenderUnitRegistry.hpp"
#include "engine/SceneSys/Entities/EntityRegistry.hpp"
#include "engine/SceneSys/Scenes/SceneRegistry.hpp"
#include "engine/SpriteSys/BitmapFontRegistry.hpp"

#include <iostream>



//
// App options
//

#define S2D_WINDOW_WIDTH        (640u)
#define S2D_WINDOW_HEIGHT       (480u)
#define S2D_WINDOW_TITLE        "Sea2D - Testing"
#define S2D_GL_MAJOR_VER        3
#define S2D_GL_MINOR_VER        3
#define S2D_WINDOW_RESIZES      false
#define S2D_CANVAS_COLOR        0.55f, 0.55f, 0.55f
#define S2D_ENABLE_DEPTH_TEST   true


namespace sea2d
{
    /// Private singleton access for App
    App* App::s_appSingeton = nullptr;
    
    
    
    //
    // Methods
    //
    
    
    
    // Default Ctor
    App::App() :
        appTimeData(nullptr),
        theWindow(nullptr),
        theKeyboard(nullptr),
        theMouse(nullptr),
        shaderRegistry(nullptr),
        meshRegistry(nullptr),
        textureRegistry(nullptr),
        spriteRegistry(nullptr),
        bitmapFontRegistry(nullptr),
        cameraRegistry(nullptr),
        renderUnitRegistry(nullptr),
        entityRegistry(nullptr),
        sceneRegistry(nullptr),
        clearColor(S2D_CANVAS_COLOR, 1.0f),
        width(S2D_WINDOW_WIDTH),
        height(S2D_WINDOW_HEIGHT),
        windowX(0),
        windowY(0),
        title(S2D_WINDOW_TITLE)
    {
        guarantee_that(App::s_appSingeton == nullptr, "App ctor: There can only be one instance");
        App::s_appSingeton = this;
    }
    
    
    // Dtor
    App::~App()
    {
        guarantee_that(App::s_appSingeton != nullptr, "App dtor: Singeton instance does not exist!");
        App::s_appSingeton = nullptr;
    }
    
    
    
    
    
    
    
    /// Run the App from start to finish. Only call once!
    void App::Run()
    {
        // Create the time class
        this->appTimeData = new Time();
        
        #ifdef DEBUG
            std::cout << "Sea2D -> Loading OpenGL..." << std::endl;
        #endif
        
        if(!this->PreSetup())
        {
            return;
        }
        
        
        
        #ifdef DEBUG
            std::cout << "Sea2D -> Setting up..." << std::endl;
        #endif
        
        this->Setup();
        
        #ifdef DEBUG
            std::cout << "Sea2D -> Start main loop..." << std::endl;
        #endif
        
        this->Loop();
        
        #ifdef DEBUG
            std::cout << "Sea2D -> App shutting down..." << std::endl;
        #endif
        
        this->Shutdown();
        
        this->PostShutdown();
        
        
        #ifdef DEBUG
            std::cout << "Sea2D -> App finished." << std::endl;
            std::cout << "    Running Time: " << Time::GetTimeFromStartInSeconds() << " seconds" << std::endl;
        #endif
        
        // Destroy the time class
        delete this->appTimeData;
    }
    
    
    
    
    
    
    /// Mostly concerned with window and graphics setup
    bool App::PreSetup()
    {
        #ifdef DEBUG
            TimeMeasurer timer;
            timer.Start();
        #endif
        
        
        
        
        
        /* ******* Windowing ******* */
        
        // Initialize GLFW itself
        if(!glfwInit())
        {
            guarantee_that(false, "GLFW Initialization failed");
            return false;
        }
        
        // Setup properties for the window
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, S2D_GL_MAJOR_VER);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, S2D_GL_MINOR_VER);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Absolutly needed in OS X, otherwise GL version becomes 2.1
        glfwWindowHint(GLFW_RESIZABLE, S2D_WINDOW_RESIZES ? GL_TRUE : GL_FALSE);
        
        #ifdef DEBUG
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        #endif
        
        
        
        // Initialize the window for GLFW
        this->theWindow = glfwCreateWindow((int)this->width, (int)this->height, this->title, NULL, NULL);
        if(this->theWindow == nullptr)
        {
            glfwTerminate();
            guarantee_that(false, "Window creation failed (GLFW)");
            return false;
        }
        
        // Make the OpenGL context of this window the current context
        glfwMakeContextCurrent(this->theWindow);
        
        // Get window data
        glfwGetWindowPos(this->theWindow, &this->windowX, &this->windowY);
        
        // Setup callbacks
        glfwSetFramebufferSizeCallback(this->theWindow, App::callbackFramebufferSize);
        glfwSetKeyCallback(this->theWindow, App::callbackKeyboard);
        glfwSetScrollCallback(this->theWindow, App::callbackScrollWheel);
        glfwSetWindowPosCallback(this->theWindow, App::callbackWindowMove);
        
        
        
        
        
        /* ******* OpenGL ******* */
        
        // Setup OpenGL runtime calls with GL3W
        if(gl3wInit() < 0)
        {
            glfwTerminate();
            guarantee_that(false, "GL3W initialization failed (OpenGL setup)");
            return false;
        }
        
        // Print out some info about the graphics drivers
        #ifdef DEBUG
            std::cout << "    OpenGL version:   " << glGetString(GL_VERSION) << std::endl;
            std::cout << "    GLSL version:     " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
            std::cout << "    Vendor:           " << glGetString(GL_VENDOR) << std::endl;
            std::cout << "    Renderer:         " << glGetString(GL_RENDERER) << std::endl;
        #endif
        
        // Setup the clear color for the OpenGL "canvas"
        glClearColor(this->clearColor.r(), this->clearColor.g(), this->clearColor.b(), 1.0f);
        
        // Enable alpha blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        // Enable depth test
        #if S2D_ENABLE_DEPTH_TEST
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
        #endif
        
        // Enable Culling
        glDisable(GL_CULL_FACE);      // Culling must be disabled for flipped sprites to show up!
        glFrontFace(GL_CW);           // Vertex winding
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Fill polygons (no lines)
        
        
        
        
        
        /* ***** Other Engine Systems ***** */
        
        // Create the keyboard and mouse
        this->theKeyboard = new Input::Keyboard();
        this->theMouse = new Input::Mouse();

        
        // Create the registries to manage graphics objects
        this->shaderRegistry = new ShaderRegistry();
        this->meshRegistry = new MeshRegistry();
        this->textureRegistry = new TextureRegistry();
        this->spriteRegistry = new SpriteRegistry();
        this->bitmapFontRegistry = new BitmapFontRegistry();
        this->cameraRegistry = new CameraRegistry();
        this->renderUnitRegistry = new RenderUnitRegistry();
        this->entityRegistry = new EntityRegistry();
        this->sceneRegistry =  new SceneRegistry();
        
        
        #ifdef DEBUG
            TimeValue elapsed = timer.GetElapsedTime();
            std::cout << "    Elapsed: " << elapsed / TimeValue(TimeBasis::OneMillisecond) << " ms" << std::endl;
        #endif
        
        return true;
    }
    
    
    
    
    
    
    
    
    /// Initialize and setup various systems done after App construction
    void App::Setup()
    {
        #ifdef DEBUG
            TimeMeasurer timer;
            timer.Start();
        #endif
        
        
        
        // Load all the shaders
        this->shaderRegistry->Load();
        
        // Load all the meshes
        this->meshRegistry->Load();
        
        // Load all the textues
        this->textureRegistry->Load();
        
        // Load all sprites
        this->spriteRegistry->Load();
        
        // Load all fonts
        this->bitmapFontRegistry->Load();
        
        // Load all the cameras
        this->cameraRegistry->Load();
        
        // Load whatever is needed for RenderUnits
        this->renderUnitRegistry->Load();
        
        // Load whatever is needed for Entities
        this->entityRegistry->Load();
        
        // Load all Scene loaders
        this->sceneRegistry->Load();
        
        
        // Load first scene by default
        Scene* const firstScene = SceneRegistry::Find(1);
        guarantee_that(firstScene != nullptr, "The scene system must have at least 1 scene managed in the SceneRegistry");
        firstScene->Load();
        
        
        
        #ifdef DEBUG
            TimeValue elapsed = timer.GetElapsedTime();
            std::cout << "    Elapsed: " << elapsed / TimeValue(TimeBasis::OneMillisecond) << " ms" << std::endl;
        #endif
    }
    
    
    
    
    
    
    
    /// The main loop of the App
    void App::Loop()
    {
        #ifdef DEBUG
            /// Frame Counter for Testing Time System
            int timeTally = 0;
        #endif
        
        // Actually loop
        while (!glfwWindowShouldClose(this->theWindow))
        {
            //
            // UPDATE
            //
            
            
            
            // Load new scene if requested (scene loading ideally is rare event)
            this->sceneRegistry->LoadNewSceneIfRequested(this->entityRegistry);
            
            
            
            // Time Update
            this->appTimeData->Update();
            
            #ifdef DEBUG
                // Testing the Time system
                timeTally++;
                if(timeTally > 200)
                {
                    timeTally = 0;
                    std::cout << std::endl << "    System Time:  " << Time::GetTimeFromStartInSeconds()  << " seconds" << std::endl;
                    std::cout << "    Delta Time:   " << Time::GetDeltaTimeInSeconds() << " seconds" << std::endl;
                    std::cout << "    Frame Count:  " << Time::GetFrameCount() << std::endl;
                }
            #endif
            
            
            
            // Input Update
            this->theKeyboard->UpdateStates();
            this->theMouse->UpdateStates();
            
            
            
            // Game update
            this->entityRegistry->Update();
            
            
            
            
            
            //
            // DRAW
            //
            
            // Clear render buffer
            #if S2D_ENABLE_DEPTH_TEST
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            #else
                glClear(GL_COLOR_BUFFER_BIT);
            #endif
            

            // Draw world for every camera
            for(auto camItr = this->cameraRegistry->GetIterator(); camItr.IsDone() == false; camItr.Next())
            {
                Camera* const currCam = camItr.CurrentItem();
                
                // Only draw if the camera is active
                if(currCam->IsActive())
                {
                    // Set the viewport of this camera
                    const CameraViewport& viewportData = currCam->GetViewportData();
                    glViewport(viewportData.originX, viewportData.originY, viewportData.width, viewportData.height);
                    
                    // Draw the world
                    this->renderUnitRegistry->Draw(currCam);
                }
            }
            
            // Swap buffers
            glfwSwapBuffers(this->theWindow);
            glfwPollEvents();
        }
    }
    
    
    
    
    /// The shutdown of various systems before the App's destructor
    void App::Shutdown()
    {
        #ifdef DEBUG
            TimeMeasurer timer;
            timer.Start();
        #endif
        
        
        this->entityRegistry->Unload();
        this->sceneRegistry->Unload();
        this->renderUnitRegistry->Unload();
        this->cameraRegistry->Unload();
        this->bitmapFontRegistry->Unload();
        this->spriteRegistry->Unload();
        this->textureRegistry->Unload();
        this->meshRegistry->Unload();
        this->shaderRegistry->Unload();
        
        
        #ifdef DEBUG
            TimeValue elapsed = timer.GetElapsedTime();
            std::cout << "    Elapsed: " << elapsed / TimeValue(TimeBasis::OneMillisecond) << " ms" << std::endl;
        #endif
    }
    
    
    
    
    /// Mostly concerned with window and graphics shutdown (after App::Shutdown())
    void App::PostShutdown()
    {
        delete this->sceneRegistry;
        delete this->entityRegistry;
        delete this->renderUnitRegistry;
        delete this->cameraRegistry;
        delete this->bitmapFontRegistry;
        delete this->spriteRegistry;
        delete this->textureRegistry;
        delete this->meshRegistry;
        delete this->shaderRegistry;
        
        delete this->theMouse;
        delete this->theKeyboard;
        
        glfwTerminate();
    }
    
    
    
    
    
    
    // STATIC
    /// Get the GLFW window pointer. Do NOT delete this pointer!
    GLFWwindow* const App::GetGlfwWindow()
    {
        return App::s_appSingeton->theWindow;
    }
    
    // STATIC
    /// Get the width of the App's window
    unsigned int App::GetWindowWidth()
    {
        return App::s_appSingeton->width;
    }
    
    // STATIC
    /// Get the height of the App's window
    unsigned int App::GetWindowHeight()
    {
        return App::s_appSingeton->height;
    }
    
    // STATIC
    /// Get the X position of the window on the desktop
    int App::GetWindowX()
    {
        return App::s_appSingeton->windowX;
    }
    
    // STATIC
    /// Get the Y position of the window on the desktop
    int App::GetWindowY()
    {
        return App::s_appSingeton->windowY;
    }
    
    // STATIC
    /// Set the X position of the window on the desktop
    void App::SetWindowPositionX(const int newX)
    {
        glfwSetWindowPos(App::GetGlfwWindow(), newX, App::GetWindowY());
    }
    
    // STATIC
    /// Set the Y position of the window on the desktop
    void App::SetWindowPositionY(const int newY)
    {
        glfwSetWindowPos(App::GetGlfwWindow(), App::GetWindowX(), newY);
    }
    
    // STATIC
    /// Set both the X and Y position of the window on the desktop at once
    void App::SetWindowPosition(const int newX, const int newY)
    {
        glfwSetWindowPos(App::GetGlfwWindow(), newX, newY);
    }
    
    // STATIC
    /// Set the clear color of the window's canvas
    void App::SetClearColor(const Color& newClearColor)
    {
        App::s_appSingeton->clearColor = newClearColor;
        const Color& c = App::s_appSingeton->clearColor;
        glClearColor(c.r(), c.g(), c.b(), 1.0f);
    }
    
    // STATIC
    /// Get the clear color of the window's canvas
    const Color App::GetClearColor()
    {
        return App::s_appSingeton->clearColor;
    }
    
    
    
    
    //
    // GLFW Events
    //
    
    
    /// Called when the GLFW window resizes (specific to pixel size)
    void App::OnFrameBufferResize(GLFWwindow *const window, const int newWidth, const int newHeight)
    {
        // Not used
        window;
        
        this->width = (unsigned int) newWidth;
        this->height = (unsigned int) newHeight;
        
        glViewport(0, 0, newWidth, newHeight);
    }
    
    
    /// Called when a key is pressed on the keyboard
    void App::OnKeyboardTriggered(GLFWwindow *const window, const int key, const int scancode, const int action, const int mods)
    {
        // Not used
        window;
        //key;
        scancode;
        //action;
        mods;
        
        if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }
    
    /// Called when the scroll-wheel moves
    void App::OnScrollWheelMove(GLFWwindow *const window, const float hDelta, const float vDelta)
    {
        // Not used
        window;
        hDelta;
        vDelta;
    }
    
    /// Called when the window moves
    void App::OnWindowMove(GLFWwindow* const window, const int xPosition, const int yPosition)
    {
        window;
        this->windowX = xPosition;
        this->windowY = yPosition;
    }
    
    
    
    
    
    
    //
    // GLFW Static Callback Routing
    //
    
    
    // STATIC
    /// Route GLFW framebuffer size callback into App
    void App::callbackFramebufferSize(GLFWwindow* window, int newWidth, int newHeight)
    {
        App::s_appSingeton->OnFrameBufferResize(window, newWidth, newHeight);
    }
    
    // STATIC
    /// Route GLFW keyboard callback into App
    void App::callbackKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        App::s_appSingeton->OnKeyboardTriggered(window, key, scancode, action, mods);
    }
    
    // STATIC
    /// Route GFLW scroll-wheel callback into App
    void App::callbackScrollWheel(GLFWwindow* window, double xoffset, double yoffset)
    {
        App::s_appSingeton->OnScrollWheelMove(window, (float)xoffset, (float)yoffset);
    }
    
    // STATIC
    /// Route GLFW window move callback into App
    void App::callbackWindowMove(GLFWwindow* window, int newX, int newY)
    {
        App::s_appSingeton->OnWindowMove(window, newX, newY);
    }
    
    
    
    
    
}