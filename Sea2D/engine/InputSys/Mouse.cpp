//
//  Mouse.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/23/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Mouse.hpp"
#include <GLFW/glfw3.h>
#include <cassert>
#include "engine/AppSys/App.hpp"

namespace sea2d
{
    namespace Input
    {
        //
        // Static Data
        //
        
        Mouse* Mouse::singetonInstance = nullptr;
        
        
        
        
        //
        // Methods
        //
        
        Mouse::Mouse() :
            //prevWheelState(0),    // <- NOT SUPPORTED YET
            currentCursorMode(MouseCursorMode::Normal)
        {
            for (int b = 0; b < S2D_TOTAL_MOUSE_BUTTONS; b++)
            {
                this->prevButtonState[b] = 0;
            }
            
            glfwSetInputMode(App::GetGlfwWindow(), GLFW_CURSOR, (int)this->currentCursorMode);
            
            assert(Mouse::singetonInstance == nullptr);
            Mouse::singetonInstance = this;
        }
        
        Mouse::~Mouse()
        {
            assert(Mouse::singetonInstance != nullptr);
            Mouse::singetonInstance = nullptr;
        }
        
        
        
        
        
        
        
        void Mouse::UpdateStates()
        {
            for (int b = 0; b < S2D_TOTAL_MOUSE_BUTTONS; b++)
            {
                this->prevButtonState[b] = (char)glfwGetMouseButton(App::GetGlfwWindow(), b);
            }
            
            // NOT SUPPORTED YET
            //this->prevWheelState = glfwGetMouseWheel(App::GetGlfwWindow());
        }
        
        
        
        
        
        
        
        // STATIC
        const bool Mouse::GetButton(const Input::MouseButton button)
        {
            if (glfwGetMouseButton(App::GetGlfwWindow(), static_cast<int>(button)))
            {
                return true;
            }
            
            return false;
        }
        
        // STATIC
        const bool Mouse::GetButtonDown(const Input::MouseButton button)
        {
            const int buttonCode = static_cast<int>(button);
            const char currState = (char)glfwGetMouseButton(App::GetGlfwWindow(), buttonCode);
            
            if (currState == GLFW_PRESS && singetonInstance->prevButtonState[buttonCode] != GLFW_PRESS)
            {
                return true;
            }
            
            return false;
        }
        
        // STATIC
        const bool Mouse::GetButtonUp(const Input::MouseButton button)
        {
            const int buttonCode = static_cast<int>(button);
            const char currState = (char)glfwGetMouseButton(App::GetGlfwWindow(), buttonCode);
            
            if (currState == GLFW_RELEASE && singetonInstance->prevButtonState[buttonCode] != GLFW_RELEASE)
            {
                return true;
            }
            
            return false;
        }
        
        
        
        
        
        
        
        
        // STATIC
        void Mouse::GetMousePosition(float& x, float& y)
        {
            double ix = 0;
            double iy = 0;
            
            glfwGetCursorPos(App::GetGlfwWindow(), &ix, &iy);
            
            x = (float)ix;
            y = (float)iy;
        }
        
        // STATIC
        void Mouse::GetMousePosition(int& x, int& y)
        {
            double ix = 0;
            double iy = 0;
            
            glfwGetCursorPos(App::GetGlfwWindow(), &ix, &iy);
            
            x = (int)ix;
            y = (int)iy;
        }
        
        
        // STATIC
        const int Mouse::GetMousePositionXi()
        {
            double ix = 0;
            double iy = 0;
            
            glfwGetCursorPos(App::GetGlfwWindow(), &ix, &iy);
            
            iy;
            return (int)ix;
        }
        
        // STATIC
        const int Mouse::GetMousePositionYi()
        {
            double ix = 0;
            double iy = 0;
            
            glfwGetCursorPos(App::GetGlfwWindow(), &ix, &iy);
            
            ix;
            return (int)iy;
        }
        
        
        // STATIC
        const float Mouse::GetMousePositionXf()
        {
            double ix = 0;
            double iy = 0;
            
            glfwGetCursorPos(App::GetGlfwWindow(), &ix, &iy);
            
            iy;
            return (float)ix;
        }
        
        // STATIC
        const float Mouse::GetMousePositionYf()
        {
            double ix = 0;
            double iy = 0;
            
            glfwGetCursorPos(App::GetGlfwWindow(), &ix, &iy);
            
            ix;
            return (float)iy;
        }
        
        
        
        
        
        
        
        // STATIC
        const float Mouse::GetPositionNormalizedX()
        {
            const float xPos = Mouse::GetMousePositionXf();
            const float width = (float) App::GetWindowWidth();
            
            return xPos / width;
        }
        
        // STATIC
        const float Mouse::GetPositionNormalizedY()
        {
            const float yPos = Mouse::GetMousePositionYf();
            const float height = (float) App::GetWindowHeight();
            
            return yPos / height;
        }
        
        
        
        
        
        
        
        // NOT SUPPORTED YET
        // STATIC
        /*
        const int Mouse::GetMouseWheel()
        {
            return glfwGetMouseWheel(App::GetGlfwWindow());
        }
        //*/
        
        // NOT SUPPORTED YET
        // STATIC
        // Gets the relative change in the mouse wheel per frame
        /*
        const int Mouse::GetMouseWheelDelta()
        {
            const int currMouseWheel = glfwGetMouseWheel(App::GetGlfwWindow());
            return currMouseWheel - Mouse::singetonInstance->prevWheelState;
        }
        //*/
        
        
        
        
        
        
        
        // STATIC
        /// Set the current mouse cursor mode (like hidden, locked, etc)
        void Mouse::SetMouseCursorMode(MouseCursorMode newMode)
        {
            Mouse::singetonInstance->currentCursorMode = newMode;
            glfwSetInputMode(App::GetGlfwWindow(), GLFW_CURSOR, (int)newMode);
        }
        
        // STATIC
        /// Inquire the current mouse cursor mode
        const MouseCursorMode Mouse::GetMouseCursorMode()
        {
            return Mouse::singetonInstance->currentCursorMode;
        }
        
        
    }
}