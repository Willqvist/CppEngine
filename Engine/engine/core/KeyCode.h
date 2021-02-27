#pragma once

#include <cstdint>
//code from https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/KeyCodes.h
namespace VoxEng
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
        GraveAccent         = 96,  /* ` */

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
#define VE_KEY_SPACE           ::VoxEng::KeyLock::Space
#define VE_KEY_APOSTROPHE      ::VoxEng::KeyLock::Apostrophe    /* ' */
#define VE_KEY_COMMA           ::VoxEng::KeyLock::Comma         /* , */
#define VE_KEY_MINUS           ::VoxEng::KeyLock::Minus         /* - */
#define VE_KEY_PERIOD          ::VoxEng::KeyLock::Period        /* . */
#define VE_KEY_SLASH           ::VoxEng::KeyLock::Slash         /* / */
#define VE_KEY_0               ::VoxEng::KeyLock::D0
#define VE_KEY_1               ::VoxEng::KeyLock::D1
#define VE_KEY_2               ::VoxEng::KeyLock::D2
#define VE_KEY_3               ::VoxEng::KeyLock::D3
#define VE_KEY_4               ::VoxEng::KeyLock::D4
#define VE_KEY_5               ::VoxEng::KeyLock::D5
#define VE_KEY_6               ::VoxEng::KeyLock::D6
#define VE_KEY_7               ::VoxEng::KeyLock::D7
#define VE_KEY_8               ::VoxEng::KeyLock::D8
#define VE_KEY_9               ::VoxEng::KeyLock::D9
#define VE_KEY_SEMICOLON       ::VoxEng::KeyLock::Semicolon     /* ; */
#define VE_KEY_EQUAL           ::VoxEng::KeyLock::Equal         /* = */
#define VE_KEY_A               ::VoxEng::KeyLock::A
#define VE_KEY_B               ::VoxEng::KeyLock::B
#define VE_KEY_C               ::VoxEng::KeyLock::C
#define VE_KEY_D               ::VoxEng::KeyLock::D
#define VE_KEY_E               ::VoxEng::KeyLock::E
#define VE_KEY_F               ::VoxEng::KeyLock::F
#define VE_KEY_G               ::VoxEng::KeyLock::G
#define VE_KEY_H               ::VoxEng::KeyLock::H
#define VE_KEY_I               ::VoxEng::KeyLock::I
#define VE_KEY_J               ::VoxEng::KeyLock::J
#define VE_KEY_K               ::VoxEng::KeyLock::K
#define VE_KEY_L               ::VoxEng::KeyLock::L
#define VE_KEY_M               ::VoxEng::KeyLock::M
#define VE_KEY_N               ::VoxEng::KeyLock::N
#define VE_KEY_O               ::VoxEng::KeyLock::O
#define VE_KEY_P               ::VoxEng::KeyLock::P
#define VE_KEY_Q               ::VoxEng::KeyLock::Q
#define VE_KEY_R               ::VoxEng::KeyLock::R
#define VE_KEY_S               ::VoxEng::KeyLock::S
#define VE_KEY_T               ::VoxEng::KeyLock::T
#define VE_KEY_U               ::VoxEng::KeyLock::U
#define VE_KEY_V               ::VoxEng::KeyLock::V
#define VE_KEY_W               ::VoxEng::KeyLock::W
#define VE_KEY_X               ::VoxEng::KeyLock::X
#define VE_KEY_Y               ::VoxEng::KeyLock::Y
#define VE_KEY_Z               ::VoxEng::KeyLock::Z
#define VE_KEY_LEFT_BRACKET    ::VoxEng::KeyLock::LeftBracket   /* [ */
#define VE_KEY_BACKSLASH       ::VoxEng::KeyLock::Backslash     /* \ */
#define VE_KEY_RIGHT_BRACKET   ::VoxEng::KeyLock::RightBracket  /* ] */
#define VE_KEY_GRAVE_ACCENT    ::VoxEng::KeyLock::GraveAccent   /* ` */
#define VE_KEY_WORLD_1         ::VoxEng::KeyLock::World1        /* non-US #1 */
#define VE_KEY_WORLD_2         ::VoxEng::KeyLock::World2        /* non-US #2 */

/* Function keys */
#define VE_KEY_ESCAPE          ::VoxEng::KeyLock::Escape
#define VE_KEY_ENTER           ::VoxEng::KeyLock::Enter
#define VE_KEY_TAB             ::VoxEng::KeyLock::Tab
#define VE_KEY_BACKSPACE       ::VoxEng::KeyLock::Backspace
#define VE_KEY_INSERT          ::VoxEng::KeyLock::Insert
#define VE_KEY_DELETE          ::VoxEng::KeyLock::Delete
#define VE_KEY_RIGHT           ::VoxEng::KeyLock::Right
#define VE_KEY_LEFT            ::VoxEng::KeyLock::Left
#define VE_KEY_DOWN            ::VoxEng::KeyLock::Down
#define VE_KEY_UP              ::VoxEng::KeyLock::Up
#define VE_KEY_PAGE_UP         ::VoxEng::KeyLock::PageUp
#define VE_KEY_PAGE_DOWN       ::VoxEng::KeyLock::PageDown
#define VE_KEY_HOME            ::VoxEng::KeyLock::Home
#define VE_KEY_END             ::VoxEng::KeyLock::End
#define VE_KEY_CAPS_LOCK       ::VoxEng::KeyLock::CapsLock
#define VE_KEY_SCROLL_LOCK     ::VoxEng::KeyLock::ScrollLock
#define VE_KEY_NUM_LOCK        ::VoxEng::KeyLock::NumLock
#define VE_KEY_PRINT_SCREEN    ::VoxEng::KeyLock::PrintScreen
#define VE_KEY_PAUSE           ::VoxEng::KeyLock::Pause
#define VE_KEY_F1              ::VoxEng::KeyLock::F1
#define VE_KEY_F2              ::VoxEng::KeyLock::F2
#define VE_KEY_F3              ::VoxEng::KeyLock::F3
#define VE_KEY_F4              ::VoxEng::KeyLock::F4
#define VE_KEY_F5              ::VoxEng::KeyLock::F5
#define VE_KEY_F6              ::VoxEng::KeyLock::F6
#define VE_KEY_F7              ::VoxEng::KeyLock::F7
#define VE_KEY_F8              ::VoxEng::KeyLock::F8
#define VE_KEY_F9              ::VoxEng::KeyLock::F9
#define VE_KEY_F10             ::VoxEng::KeyLock::F10
#define VE_KEY_F11             ::VoxEng::KeyLock::F11
#define VE_KEY_F12             ::VoxEng::KeyLock::F12
#define VE_KEY_F13             ::VoxEng::KeyLock::F13
#define VE_KEY_F14             ::VoxEng::KeyLock::F14
#define VE_KEY_F15             ::VoxEng::KeyLock::F15
#define VE_KEY_F16             ::VoxEng::KeyLock::F16
#define VE_KEY_F17             ::VoxEng::KeyLock::F17
#define VE_KEY_F18             ::VoxEng::KeyLock::F18
#define VE_KEY_F19             ::VoxEng::KeyLock::F19
#define VE_KEY_F20             ::VoxEng::KeyLock::F20
#define VE_KEY_F21             ::VoxEng::KeyLock::F21
#define VE_KEY_F22             ::VoxEng::KeyLock::F22
#define VE_KEY_F23             ::VoxEng::KeyLock::F23
#define VE_KEY_F24             ::VoxEng::KeyLock::F24
#define VE_KEY_F25             ::VoxEng::KeyLock::F25

/* Keypad */
#define VE_KEY_KP_0            ::VoxEng::KeyLock::KP0
#define VE_KEY_KP_1            ::VoxEng::KeyLock::KP1
#define VE_KEY_KP_2            ::VoxEng::KeyLock::KP2
#define VE_KEY_KP_3            ::VoxEng::KeyLock::KP3
#define VE_KEY_KP_4            ::VoxEng::KeyLock::KP4
#define VE_KEY_KP_5            ::VoxEng::KeyLock::KP5
#define VE_KEY_KP_6            ::VoxEng::KeyLock::KP6
#define VE_KEY_KP_7            ::VoxEng::KeyLock::KP7
#define VE_KEY_KP_8            ::VoxEng::KeyLock::KP8
#define VE_KEY_KP_9            ::VoxEng::KeyLock::KP9
#define VE_KEY_KP_DECIMAL      ::VoxEng::KeyLock::KPDecimal
#define VE_KEY_KP_DIVIDE       ::VoxEng::KeyLock::KPDivide
#define VE_KEY_KP_MULTIPLY     ::VoxEng::KeyLock::KPMultiply
#define VE_KEY_KP_SUBTRACT     ::VoxEng::KeyLock::KPSubtract
#define VE_KEY_KP_ADD          ::VoxEng::KeyLock::KPAdd
#define VE_KEY_KP_ENTER        ::VoxEng::KeyLock::KPEnter
#define VE_KEY_KP_EQUAL        ::VoxEng::KeyLock::KPEqual

#define VE_KEY_LEFT_SHIFT      ::VoxEng::KeyLock::LeftShift
#define VE_KEY_LEFT_CONTROL    ::VoxEng::KeyLock::LeftControl
#define VE_KEY_LEFT_ALT        ::VoxEng::KeyLock::LeftAlt
#define VE_KEY_LEFT_SUPER      ::VoxEng::KeyLock::LeftSuper
#define VE_KEY_RIGHT_SHIFT     ::VoxEng::KeyLock::RightShift
#define VE_KEY_RIGHT_CONTROL   ::VoxEng::KeyLock::RightControl
#define VE_KEY_RIGHT_ALT       ::VoxEng::KeyLock::RightAlt
#define VE_KEY_RIGHT_SUPER     ::VoxEng::KeyLock::RightSuper
#define VE_KEY_MENU            ::VoxEng::KeyLock::Menu