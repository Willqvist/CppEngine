#pragma once

#include <cstdint>
//code from https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/KeyCodes.h
namespace Ziti
{
    typedef enum class KeyCode : unsigned int
    {
        // From glfw3.h
        Space               = 32,
        Apostrophe          = 39, /* ' */
        Comma               = 44, /* , */
        Minus               = 45, /* - */
        Period              = 46, /* . */
        Slash               = 47, /* / */

        D0                  = 48, /* 0 */
        D1                  = 49, /* 1 */
        D2                  = 50, /* 2 */
        D3                  = 51, /* 3 */
        D4                  = 52, /* 4 */
        D5                  = 53, /* 5 */
        D6                  = 54, /* 6 */
        D7                  = 55, /* 7 */
        D8                  = 56, /* 8 */
        D9                  = 57, /* 9 */

        Semicolon           = 59, /* ; */
        Equal               = 61, /* = */

        A                   = 65,
        B                   = 66,
        C                   = 67,
        D                   = 68,
        E                   = 69,
        F                   = 70,
        G                   = 71,
        H                   = 72,
        I                   = 73,
        J                   = 74,
        K                   = 75,
        L                   = 76,
        M                   = 77,
        N                   = 78,
        O                   = 79,
        P                   = 80,
        Q                   = 81,
        R                   = 82,
        S                   = 83,
        T                   = 84,
        U                   = 85,
        V                   = 86,
        W                   = 87,
        X                   = 88,
        Y                   = 89,
        Z                   = 90,

        LeftBracket         = 91,  /* [ */
        Backslash           = 92,  /* \ */
        RightBracket        = 93,  /* ] */
        GraZTAccent         = 96,  /* ` */

        World1              = 161, /* non-US #1 */
        World2              = 162, /* non-US #2 */

        /* Function keys */
        Escape              = 256,
        Enter               = 257,
        Tab                 = 258,
        Backspace           = 259,
        Insert              = 260,
        Delete              = 261,
        Right               = 262,
        Left                = 263,
        Down                = 264,
        Up                  = 265,
        PageUp              = 266,
        PageDown            = 267,
        Home                = 268,
        End                 = 269,
        CapsLock            = 280,
        ScrollLock          = 281,
        NumLock             = 282,
        PrintScreen         = 283,
        Pause               = 284,
        F1                  = 290,
        F2                  = 291,
        F3                  = 292,
        F4                  = 293,
        F5                  = 294,
        F6                  = 295,
        F7                  = 296,
        F8                  = 297,
        F9                  = 298,
        F10                 = 299,
        F11                 = 300,
        F12                 = 301,
        F13                 = 302,
        F14                 = 303,
        F15                 = 304,
        F16                 = 305,
        F17                 = 306,
        F18                 = 307,
        F19                 = 308,
        F20                 = 309,
        F21                 = 310,
        F22                 = 311,
        F23                 = 312,
        F24                 = 313,
        F25                 = 314,

        /* Keypad */
        KP0                 = 320,
        KP1                 = 321,
        KP2                 = 322,
        KP3                 = 323,
        KP4                 = 324,
        KP5                 = 325,
        KP6                 = 326,
        KP7                 = 327,
        KP8                 = 328,
        KP9                 = 329,
        KPDecimal           = 330,
        KPDivide            = 331,
        KPMultiply          = 332,
        KPSubtract          = 333,
        KPAdd               = 334,
        KPEnter             = 335,
        KPEqual             = 336,

        LeftShift           = 340,
        LeftControl         = 341,
        LeftAlt             = 342,
        LeftSuper           = 343,
        RightShift          = 344,
        RightControl        = 345,
        RightAlt            = 346,
        RightSuper          = 347,
        Menu                = 348
    } Key;
}

// From glfw3.h
#define ZT_KEY_SPACE           ::Ziti::KeyLock::Space
#define ZT_KEY_APOSTROPHE      ::Ziti::KeyLock::Apostrophe    /* ' */
#define ZT_KEY_COMMA           ::Ziti::KeyLock::Comma         /* , */
#define ZT_KEY_MINUS           ::Ziti::KeyLock::Minus         /* - */
#define ZT_KEY_PERIOD          ::Ziti::KeyLock::Period        /* . */
#define ZT_KEY_SLASH           ::Ziti::KeyLock::Slash         /* / */
#define ZT_KEY_0               ::Ziti::KeyLock::D0
#define ZT_KEY_1               ::Ziti::KeyLock::D1
#define ZT_KEY_2               ::Ziti::KeyLock::D2
#define ZT_KEY_3               ::Ziti::KeyLock::D3
#define ZT_KEY_4               ::Ziti::KeyLock::D4
#define ZT_KEY_5               ::Ziti::KeyLock::D5
#define ZT_KEY_6               ::Ziti::KeyLock::D6
#define ZT_KEY_7               ::Ziti::KeyLock::D7
#define ZT_KEY_8               ::Ziti::KeyLock::D8
#define ZT_KEY_9               ::Ziti::KeyLock::D9
#define ZT_KEY_SEMICOLON       ::Ziti::KeyLock::Semicolon     /* ; */
#define ZT_KEY_EQUAL           ::Ziti::KeyLock::Equal         /* = */
#define ZT_KEY_A               ::Ziti::KeyLock::A
#define ZT_KEY_B               ::Ziti::KeyLock::B
#define ZT_KEY_C               ::Ziti::KeyLock::C
#define ZT_KEY_D               ::Ziti::KeyLock::D
#define ZT_KEY_E               ::Ziti::KeyLock::E
#define ZT_KEY_F               ::Ziti::KeyLock::F
#define ZT_KEY_G               ::Ziti::KeyLock::G
#define ZT_KEY_H               ::Ziti::KeyLock::H
#define ZT_KEY_I               ::Ziti::KeyLock::I
#define ZT_KEY_J               ::Ziti::KeyLock::J
#define ZT_KEY_K               ::Ziti::KeyLock::K
#define ZT_KEY_L               ::Ziti::KeyLock::L
#define ZT_KEY_M               ::Ziti::KeyLock::M
#define ZT_KEY_N               ::Ziti::KeyLock::N
#define ZT_KEY_O               ::Ziti::KeyLock::O
#define ZT_KEY_P               ::Ziti::KeyLock::P
#define ZT_KEY_Q               ::Ziti::KeyLock::Q
#define ZT_KEY_R               ::Ziti::KeyLock::R
#define ZT_KEY_S               ::Ziti::KeyLock::S
#define ZT_KEY_T               ::Ziti::KeyLock::T
#define ZT_KEY_U               ::Ziti::KeyLock::U
#define ZT_KEY_V               ::Ziti::KeyLock::V
#define ZT_KEY_W               ::Ziti::KeyLock::W
#define ZT_KEY_X               ::Ziti::KeyLock::X
#define ZT_KEY_Y               ::Ziti::KeyLock::Y
#define ZT_KEY_Z               ::Ziti::KeyLock::Z
#define ZT_KEY_LEFT_BRACKET    ::Ziti::KeyLock::LeftBracket   /* [ */
#define ZT_KEY_BACKSLASH       ::Ziti::KeyLock::Backslash     /* \ */
#define ZT_KEY_RIGHT_BRACKET   ::Ziti::KeyLock::RightBracket  /* ] */
#define ZT_KEY_GRAZT_ACCENT    ::Ziti::KeyLock::GraZTAccent   /* ` */
#define ZT_KEY_WORLD_1         ::Ziti::KeyLock::World1        /* non-US #1 */
#define ZT_KEY_WORLD_2         ::Ziti::KeyLock::World2        /* non-US #2 */

/* Function keys */
#define ZT_KEY_ESCAPE          ::Ziti::KeyLock::Escape
#define ZT_KEY_ENTER           ::Ziti::KeyLock::Enter
#define ZT_KEY_TAB             ::Ziti::KeyLock::Tab
#define ZT_KEY_BACKSPACE       ::Ziti::KeyLock::Backspace
#define ZT_KEY_INSERT          ::Ziti::KeyLock::Insert
#define ZT_KEY_DELETE          ::Ziti::KeyLock::Delete
#define ZT_KEY_RIGHT           ::Ziti::KeyLock::Right
#define ZT_KEY_LEFT            ::Ziti::KeyLock::Left
#define ZT_KEY_DOWN            ::Ziti::KeyLock::Down
#define ZT_KEY_UP              ::Ziti::KeyLock::Up
#define ZT_KEY_PAGE_UP         ::Ziti::KeyLock::PageUp
#define ZT_KEY_PAGE_DOWN       ::Ziti::KeyLock::PageDown
#define ZT_KEY_HOME            ::Ziti::KeyLock::Home
#define ZT_KEY_END             ::Ziti::KeyLock::End
#define ZT_KEY_CAPS_LOCK       ::Ziti::KeyLock::CapsLock
#define ZT_KEY_SCROLL_LOCK     ::Ziti::KeyLock::ScrollLock
#define ZT_KEY_NUM_LOCK        ::Ziti::KeyLock::NumLock
#define ZT_KEY_PRINT_SCREEN    ::Ziti::KeyLock::PrintScreen
#define ZT_KEY_PAUSE           ::Ziti::KeyLock::Pause
#define ZT_KEY_F1              ::Ziti::KeyLock::F1
#define ZT_KEY_F2              ::Ziti::KeyLock::F2
#define ZT_KEY_F3              ::Ziti::KeyLock::F3
#define ZT_KEY_F4              ::Ziti::KeyLock::F4
#define ZT_KEY_F5              ::Ziti::KeyLock::F5
#define ZT_KEY_F6              ::Ziti::KeyLock::F6
#define ZT_KEY_F7              ::Ziti::KeyLock::F7
#define ZT_KEY_F8              ::Ziti::KeyLock::F8
#define ZT_KEY_F9              ::Ziti::KeyLock::F9
#define ZT_KEY_F10             ::Ziti::KeyLock::F10
#define ZT_KEY_F11             ::Ziti::KeyLock::F11
#define ZT_KEY_F12             ::Ziti::KeyLock::F12
#define ZT_KEY_F13             ::Ziti::KeyLock::F13
#define ZT_KEY_F14             ::Ziti::KeyLock::F14
#define ZT_KEY_F15             ::Ziti::KeyLock::F15
#define ZT_KEY_F16             ::Ziti::KeyLock::F16
#define ZT_KEY_F17             ::Ziti::KeyLock::F17
#define ZT_KEY_F18             ::Ziti::KeyLock::F18
#define ZT_KEY_F19             ::Ziti::KeyLock::F19
#define ZT_KEY_F20             ::Ziti::KeyLock::F20
#define ZT_KEY_F21             ::Ziti::KeyLock::F21
#define ZT_KEY_F22             ::Ziti::KeyLock::F22
#define ZT_KEY_F23             ::Ziti::KeyLock::F23
#define ZT_KEY_F24             ::Ziti::KeyLock::F24
#define ZT_KEY_F25             ::Ziti::KeyLock::F25

/* Keypad */
#define ZT_KEY_KP_0            ::Ziti::KeyLock::KP0
#define ZT_KEY_KP_1            ::Ziti::KeyLock::KP1
#define ZT_KEY_KP_2            ::Ziti::KeyLock::KP2
#define ZT_KEY_KP_3            ::Ziti::KeyLock::KP3
#define ZT_KEY_KP_4            ::Ziti::KeyLock::KP4
#define ZT_KEY_KP_5            ::Ziti::KeyLock::KP5
#define ZT_KEY_KP_6            ::Ziti::KeyLock::KP6
#define ZT_KEY_KP_7            ::Ziti::KeyLock::KP7
#define ZT_KEY_KP_8            ::Ziti::KeyLock::KP8
#define ZT_KEY_KP_9            ::Ziti::KeyLock::KP9
#define ZT_KEY_KP_DECIMAL      ::Ziti::KeyLock::KPDecimal
#define ZT_KEY_KP_DIVIDE       ::Ziti::KeyLock::KPDivide
#define ZT_KEY_KP_MULTIPLY     ::Ziti::KeyLock::KPMultiply
#define ZT_KEY_KP_SUBTRACT     ::Ziti::KeyLock::KPSubtract
#define ZT_KEY_KP_ADD          ::Ziti::KeyLock::KPAdd
#define ZT_KEY_KP_ENTER        ::Ziti::KeyLock::KPEnter
#define ZT_KEY_KP_EQUAL        ::Ziti::KeyLock::KPEqual

#define ZT_KEY_LEFT_SHIFT      ::Ziti::KeyLock::LeftShift
#define ZT_KEY_LEFT_CONTROL    ::Ziti::KeyLock::LeftControl
#define ZT_KEY_LEFT_ALT        ::Ziti::KeyLock::LeftAlt
#define ZT_KEY_LEFT_SUPER      ::Ziti::KeyLock::LeftSuper
#define ZT_KEY_RIGHT_SHIFT     ::Ziti::KeyLock::RightShift
#define ZT_KEY_RIGHT_CONTROL   ::Ziti::KeyLock::RightControl
#define ZT_KEY_RIGHT_ALT       ::Ziti::KeyLock::RightAlt
#define ZT_KEY_RIGHT_SUPER     ::Ziti::KeyLock::RightSuper
#define ZT_KEY_MENU            ::Ziti::KeyLock::Menu