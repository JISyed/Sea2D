//
//  Keyboard.hpp
//  Sea2D
//
//  Created by Jibran Syed on 4/23/16.
//  Copyright © 2016 Jishenaz. All rights reserved.
//

#ifndef Keyboard_hpp
#define Keyboard_hpp

#include <GLFW/glfw3.h>

namespace sea2d
{
    namespace Input
    {
        //
        // Enums
        //
        
        
        /// Represents every usable key on the keyboard
        enum class Key
        {
            /* Printable keys (based off ISO 8859-1) */
            
            Space = GLFW_KEY_SPACE,
            Apostrophe = GLFW_KEY_APOSTROPHE,	/* ' */
            Comma = GLFW_KEY_COMMA,				/* , */
            Minus = GLFW_KEY_MINUS,				/* - */
            Period = GLFW_KEY_PERIOD,			/* . */
            Slash = GLFW_KEY_SLASH,				/* / */
            Number0 = GLFW_KEY_0,
            Number1 = GLFW_KEY_1,
            Number2 = GLFW_KEY_2,
            Number3 = GLFW_KEY_3,
            Number4 = GLFW_KEY_4,
            Number5 = GLFW_KEY_5,
            Number6 = GLFW_KEY_6,
            Number7 = GLFW_KEY_7,
            Number8 = GLFW_KEY_8,
            Number9 = GLFW_KEY_9,
            Semicolon = GLFW_KEY_SEMICOLON,		/* ; */
            Equal = GLFW_KEY_EQUAL,				/* = */
            A = GLFW_KEY_A,
            B = GLFW_KEY_B,
            C = GLFW_KEY_C,
            D = GLFW_KEY_D,
            E = GLFW_KEY_E,
            F = GLFW_KEY_F,
            G = GLFW_KEY_G,
            H = GLFW_KEY_H,
            I = GLFW_KEY_I,
            J = GLFW_KEY_J,
            K = GLFW_KEY_K,
            L = GLFW_KEY_L,
            M = GLFW_KEY_M,
            N = GLFW_KEY_N,
            O = GLFW_KEY_O,
            P = GLFW_KEY_P,
            Q = GLFW_KEY_Q,
            R = GLFW_KEY_R,
            S = GLFW_KEY_S,
            T = GLFW_KEY_T,
            U = GLFW_KEY_U,
            V = GLFW_KEY_V,
            W = GLFW_KEY_W,
            X = GLFW_KEY_X,
            Y = GLFW_KEY_Y,
            Z = GLFW_KEY_Z,
            BracketLeft = GLFW_KEY_LEFT_BRACKET,	/* [ */
            BackSlash = GLFW_KEY_BACKSLASH,			/* \ */
            BracketRight = GLFW_KEY_RIGHT_BRACKET,	/* ] */
            GraveAccent = GLFW_KEY_GRAVE_ACCENT,	/* ` */
            WorldKey1 = GLFW_KEY_WORLD_1,		/* non-US #1 */
            WorldKey2 = GLFW_KEY_WORLD_2,		/* non-US #2 */
            
            /* Function keys */
            
            Escape = GLFW_KEY_ESCAPE,
            F1 = GLFW_KEY_F1,
            F2 = GLFW_KEY_F2,
            F3 = GLFW_KEY_F3,
            F4 = GLFW_KEY_F4,
            F5 = GLFW_KEY_F5,
            F6 = GLFW_KEY_F6,
            F7 = GLFW_KEY_F7,
            F8 = GLFW_KEY_F8,
            F9 = GLFW_KEY_F9,
            F10 = GLFW_KEY_F10,
            F11 = GLFW_KEY_F11,
            F12 = GLFW_KEY_F12,
            F13 = GLFW_KEY_F13,
            F14 = GLFW_KEY_F14,
            F15 = GLFW_KEY_F15,
            F16 = GLFW_KEY_F16,
            F17 = GLFW_KEY_F17,
            F18 = GLFW_KEY_F18,
            F19 = GLFW_KEY_F19,
            F20 = GLFW_KEY_F20,
            F21 = GLFW_KEY_F21,
            F22 = GLFW_KEY_F22,
            F23 = GLFW_KEY_F23,
            F24 = GLFW_KEY_F24,
            F25 = GLFW_KEY_F25,
            ArrowUp = GLFW_KEY_UP,
            ArrowDown = GLFW_KEY_DOWN,
            ArrowLeft = GLFW_KEY_LEFT,
            ArrowRight = GLFW_KEY_RIGHT,
            ShiftLeft = GLFW_KEY_LEFT_SHIFT,
            ShiftRight = GLFW_KEY_RIGHT_SHIFT,
            ControlLeft = GLFW_KEY_LEFT_CONTROL,
            ControlRight = GLFW_KEY_RIGHT_CONTROL,
            AltLeft = GLFW_KEY_LEFT_ALT,
            AltRight = GLFW_KEY_RIGHT_ALT,
            Tab = GLFW_KEY_TAB,
            Enter = GLFW_KEY_ENTER,
            Backspace = GLFW_KEY_BACKSPACE,
            Insert = GLFW_KEY_INSERT,
            ForwardDelete = GLFW_KEY_DELETE,
            PageUp = GLFW_KEY_PAGE_UP,
            PageDown = GLFW_KEY_PAGE_DOWN,
            Home = GLFW_KEY_HOME,
            End = GLFW_KEY_END,
            Keypad0 = GLFW_KEY_KP_0,
            Keypad1 = GLFW_KEY_KP_1,
            Keypad2 = GLFW_KEY_KP_2,
            Keypad3 = GLFW_KEY_KP_3,
            Keypad4 = GLFW_KEY_KP_4,
            Keypad5 = GLFW_KEY_KP_5,
            Keypad6 = GLFW_KEY_KP_6,
            Keypad7 = GLFW_KEY_KP_7,
            Keypad8 = GLFW_KEY_KP_8,
            Keypad9 = GLFW_KEY_KP_9,
            KeypadDivide = GLFW_KEY_KP_DIVIDE,
            KeypadMultiply = GLFW_KEY_KP_MULTIPLY,
            KeypadSubtract = GLFW_KEY_KP_SUBTRACT,
            KeypadAdd = GLFW_KEY_KP_ADD,
            KeypadDecimalPoint = GLFW_KEY_KP_DECIMAL,
            KeypadEqual = GLFW_KEY_KP_EQUAL,
            KeypadEnter = GLFW_KEY_KP_ENTER,
            NumberLock = GLFW_KEY_NUM_LOCK,
            CapsLock = GLFW_KEY_CAPS_LOCK,
            ScrollLock = GLFW_KEY_SCROLL_LOCK,
            PrintScreen = GLFW_KEY_PRINT_SCREEN,
            Pause = GLFW_KEY_PAUSE,
            SuperLeft = GLFW_KEY_LEFT_SUPER,
            SuperRight = GLFW_KEY_RIGHT_SUPER,
            Menu = GLFW_KEY_MENU
        };
        
        
        
        
        /// Values the represent the range of keys (used for key iteration)
        enum S2D_KEY_RANGE
        {
            /// The total number of keys supported by GLFW
            S2D_TOTAL_KEYS = GLFW_KEY_LAST + 1,
            /// The index of the first key (keys before this are invalid keys)
            S2D_FIRST_KEY_VALUE = GLFW_KEY_SPACE
        };
        
        
        
        
        
        //
        // The Keyboard Class
        //
        
        
        /// Used to inquire user input from the keyboard
        class Keyboard
        {
        public:
            
            //
            // Ctor / Dtor
            //
            
            /// Only the App class should be calling the constructor
            Keyboard();
            
            /// Dtor
            ~Keyboard();
            
            
            //
            // Methods
            //
            
            /// Only the Game class should update states
            void UpdateStates();
            
            
            //
            // Static Methods
            //
            
            /// Returns true if the key is down at anytime
            static const bool GetKey(const Input::Key key);
            
            /// Returns true if the key was pressed down at that moment (holding does not count)
            static const bool GetKeyDown(const Input::Key key);
            
            /// Returns true if the key was released at that moment (having been pressed down the previous frame)
            static const bool GetKeyUp(const Input::Key key);
            
            
            
            
        private:
            
            //
            // Data
            //
            
            char currKeyState[S2D_TOTAL_KEYS];  ///< The current state of every key
            char prevKeyState[S2D_TOTAL_KEYS];  ///< The pressed state of every key
            
            
            
            
            //
            // Static Data
            //
            
            static Keyboard* singetonInstance;  ///< Only one Keyboard
            
            
            
            //
            // Deleted Methods
            //
            
            /// No copy ctor
            Keyboard(const Keyboard& other) = delete;
            
            /// No copy assignment
            Keyboard& operator=(const Keyboard& other) = delete;
            
            /// No move ctor
            Keyboard(Keyboard&& other) = delete;
            
            /// No move assignment
            Keyboard& operator=(Keyboard&& other) = delete;
        };
    }
}
#endif /* Keyboard_hpp */
