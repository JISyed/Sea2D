//
//  Mouse.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/23/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef Mouse_hpp
#define Mouse_hpp

#include <GLFW/glfw3.h>

namespace sea2d
{
    namespace Input
    {
        //
        // Enums
        //
        
        /// Represents every usable mouse button (up to 8 buttons)
        enum class MouseButton
        {
            B1 = GLFW_MOUSE_BUTTON_1,   ///< Also left button
            B2 = GLFW_MOUSE_BUTTON_2,   ///< Also right button
            B3 = GLFW_MOUSE_BUTTON_3,   ///< Also middle button
            
            B4 = GLFW_MOUSE_BUTTON_4,
            B5 = GLFW_MOUSE_BUTTON_5,
            B6 = GLFW_MOUSE_BUTTON_6,
            B7 = GLFW_MOUSE_BUTTON_7,
            B8 = GLFW_MOUSE_BUTTON_8,
            
            Left = GLFW_MOUSE_BUTTON_LEFT,
            Right = GLFW_MOUSE_BUTTON_RIGHT,
            Middle = GLFW_MOUSE_BUTTON_MIDDLE
        };
        
        /// Represents different states of the mouse cursor
        enum class MouseCursorMode
        {
            Normal = GLFW_CURSOR_NORMAL,    ///< Cursor is visible and can move
            Hidden = GLFW_CURSOR_HIDDEN,    ///< Cursor can move but is hidden in the window
            Locked = GLFW_CURSOR_DISABLED   ///< Cursor is locked into the window and is hidden
        };
        
        /// Values the represent the range of mouse buttons (used for button iteration)
        enum S2D_MOUSE_BUTTON_RANGE
        {
            // The total number of mouse buttons supported by GLFW
            S2D_TOTAL_MOUSE_BUTTONS = GLFW_MOUSE_BUTTON_LAST + 1
        };
        
        
        
        
        //
        // The Mouse Class
        //
        
        /// Used to inquire user input from the mouse
        class Mouse
        {
        public:
            
            //
            // Ctor / Dtor
            //
            
            /// Only the App class should be calling the constructor
            Mouse();
            
            /// Dtor
            ~Mouse();
            
            
            
            //
            // Methods
            //
            
            /// Only the Game class should update states
            void UpdateStates();
            
            
            
            
            //
            // Static Methods
            //
            
            /// Returns true if the button is down at anytime
            static const bool GetButton(const Input::MouseButton button);
            
            /// Returns true if the button was pressed down at that moment (holding does not count)
            static const bool GetButtonDown(const Input::MouseButton button);
            
            /// Returns true if the button was released at that moment (having been pressed down the previous frame)
            static const bool GetButtonUp(const Input::MouseButton button);
            
            
            
            
            /// Gets the mouse in screen space (inout floats)
            static void GetMousePosition(float& x, float& y);
            
            /// Gets the mouse in screen space (inout ints)
            static void GetMousePosition(int& x, int& y);
            
            /// Gets the X position of the mouse as an int
            static const int GetMousePositionXi();
            
            /// Gets the Y position of the mouse as an int
            static const int GetMousePositionYi();
            
            /// Gets the X position of the mouse as a float
            static const float GetMousePositionXf();
            
            /// Gets the Y position of the mouse as a float
            static const float GetMousePositionYf();
            
            
            
            /// Returned normalized X position of the mouse (resolution independent)
            static const float GetPositionNormalizedX();
            
            /// Returned normalized Y position of the mouse (resolution independent)
            static const float GetPositionNormalizedY();
            
            
            // NOT SUPPORTED YET
            /// Gets absolute state of the mouse wheel
            //static const int GetMouseWheel();
            
            // NOT SUPPORTED YET
            /// Gets the relative change in the mouse wheel per frame
            //static const int GetMouseWheelDelta();
            
            
            
            /// Set the current mouse cursor mode (like hidden, locked, etc)
            static void SetMouseCursorMode(MouseCursorMode newMode);
            
            /// Inquire the current mouse cursor mode
            static const MouseCursorMode GetMouseCursorMode();
            
            
            
        private:
            
            //
            // Data
            //
            
            char prevButtonState[S2D_TOTAL_MOUSE_BUTTONS];  ///< The pressed state of every mouse button
            
            // NOT SUPPORTED YET
            //int prevWheelState;                             ///< Previous position of the mouse wheel
            
            MouseCursorMode currentCursorMode;              ///< Current mouse cursor state
            
            
            
            //
            // Static Data
            //
            
            static Mouse* singetonInstance;         ///< Only one Mouse
            
            
            
            
            
            //
            // Deleted Methods
            //
            
            /// No copy ctor
            Mouse(const Mouse& other) = delete;
            
            /// No copy assignment
            Mouse& operator=(const Mouse& other) = delete;
            
            /// No move ctor
            Mouse(Mouse&& other) = delete;
            
            /// No move assignment
            Mouse& operator=(Mouse&& other) = delete;
        };
    }
}
#endif /* Mouse_hpp */
