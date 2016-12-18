//
//  Keyboard.cpp
//  Sea2D
//
//  Created by Jibran Syed on 4/23/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#include "Keyboard.hpp"
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
        Keyboard* Keyboard::singetonInstance = nullptr;
        
        
        
        //
        // Methods
        //
        
        Keyboard::Keyboard()
        {
            for (int i = 0; i < S2D_TOTAL_KEYS; i++)
            {
                this->prevKeyState[i] = 0;
                this->currKeyState[i] = 0;
            }
            
            // Register the singleton pointer (only Game should be calling the constructor)
            assert(Keyboard::singetonInstance == nullptr);
            Keyboard::singetonInstance = this;
        }
        
        Keyboard::~Keyboard()
        {
            assert(Keyboard::singetonInstance != nullptr);
            Keyboard::singetonInstance = nullptr;
        }
        
        
        
        
        void Keyboard::UpdateStates()
        {
            for (int k = S2D_FIRST_KEY_VALUE; k < S2D_TOTAL_KEYS; k++)
            {
                this->prevKeyState[k] = this->currKeyState[k];
                this->currKeyState[k] = (char) glfwGetKey(App::GetGlfwWindow(), k);
            }
        }
        
        
        
        
        // STATIC
        const bool Keyboard::GetKey(const Input::Key key)
        {
            if (Keyboard::singetonInstance->currKeyState[static_cast<int>(key)] == GLFW_PRESS)
            {
                return true;
            }
            
            return false;
        }
        
        // STATIC
        const bool Keyboard::GetKeyDown(const Input::Key key)
        {
            const int keyCode = static_cast<int>(key);
            const char currState = Keyboard::singetonInstance->currKeyState[keyCode];
            
            if (currState == GLFW_PRESS && singetonInstance->prevKeyState[keyCode] != GLFW_PRESS)
            {
                return true;
            }
            
            return false;
        }
        
        // STATIC
        const bool Keyboard::GetKeyUp(const Input::Key key)
        {
            const int keyCode = static_cast<int>(key);
            const char currState = Keyboard::singetonInstance->currKeyState[keyCode];
            
            if (currState == GLFW_RELEASE && singetonInstance->prevKeyState[keyCode] != GLFW_RELEASE)
            {
                return true;
            }
            
            return false;
        }
    }
}