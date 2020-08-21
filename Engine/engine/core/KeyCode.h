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
#define VE_KEY_SPACE           ::VoxEng::Key::Space
#define VE_KEY_APOSTROPHE      ::VoxEng::Key::Apostrophe    /* ' */
#define VE_KEY_COMMA           ::VoxEng::Key::Comma         /* , */
#define VE_KEY_MINUS           ::VoxEng::Key::Minus         /* - */
#define VE_KEY_PERIOD          ::VoxEng::Key::Period        /* . */
#define VE_KEY_SLASH           ::VoxEng::Key::Slash         /* / */
#define VE_KEY_0               ::VoxEng::Key::D0
#define VE_KEY_1               ::VoxEng::Key::D1
#define VE_KEY_2               ::VoxEng::Key::D2
#define VE_KEY_3               ::VoxEng::Key::D3
#define VE_KEY_4               ::VoxEng::Key::D4
#define VE_KEY_5               ::VoxEng::Key::D5
#define VE_KEY_6               ::VoxEng::Key::D6
#define VE_KEY_7               ::VoxEng::Key::D7
#define VE_KEY_8               ::VoxEng::Key::D8
#define VE_KEY_9               ::VoxEng::Key::D9
#define VE_KEY_SEMICOLON       ::VoxEng::Key::Semicolon     /* ; */
#define VE_KEY_EQUAL           ::VoxEng::Key::Equal         /* = */
#define VE_KEY_A               ::VoxEng::Key::A
#define VE_KEY_B               ::VoxEng::Key::B
#define VE_KEY_C               ::VoxEng::Key::C
#define VE_KEY_D               ::VoxEng::Key::D
#define VE_KEY_E               ::VoxEng::Key::E
#define VE_KEY_F               ::VoxEng::Key::F
#define VE_KEY_G               ::VoxEng::Key::G
#define VE_KEY_H               ::VoxEng::Key::H
#define VE_KEY_I               ::VoxEng::Key::I
#define VE_KEY_J               ::VoxEng::Key::J
#define VE_KEY_K               ::VoxEng::Key::K
#define VE_KEY_L               ::VoxEng::Key::L
#define VE_KEY_M               ::VoxEng::Key::M
#define VE_KEY_N               ::VoxEng::Key::N
#define VE_KEY_O               ::VoxEng::Key::O
#define VE_KEY_P               ::VoxEng::Key::P
#define VE_KEY_Q               ::VoxEng::Key::Q
#define VE_KEY_R               ::VoxEng::Key::R
#define VE_KEY_S               ::VoxEng::Key::S
#define VE_KEY_T               ::VoxEng::Key::T
#define VE_KEY_U               ::VoxEng::Key::U
#define VE_KEY_V               ::VoxEng::Key::V
#define VE_KEY_W               ::VoxEng::Key::W
#define VE_KEY_X               ::VoxEng::Key::X
#define VE_KEY_Y               ::VoxEng::Key::Y
#define VE_KEY_Z               ::VoxEng::Key::Z
#define VE_KEY_LEFT_BRACKET    ::VoxEng::Key::LeftBracket   /* [ */
#define VE_KEY_BACKSLASH       ::VoxEng::Key::Backslash     /* \ */
#define VE_KEY_RIGHT_BRACKET   ::VoxEng::Key::RightBracket  /* ] */
#define VE_KEY_GRAVE_ACCENT    ::VoxEng::Key::GraveAccent   /* ` */
#define VE_KEY_WORLD_1         ::VoxEng::Key::World1        /* non-US #1 */
#define VE_KEY_WORLD_2         ::VoxEng::Key::World2        /* non-US #2 */

/* Function keys */
#define VE_KEY_ESCAPE          ::VoxEng::Key::Escape
#define VE_KEY_ENTER           ::VoxEng::Key::Enter
#define VE_KEY_TAB             ::VoxEng::Key::Tab
#define VE_KEY_BACKSPACE       ::VoxEng::Key::Backspace
#define VE_KEY_INSERT          ::VoxEng::Key::Insert
#define VE_KEY_DELETE          ::VoxEng::Key::Delete
#define VE_KEY_RIGHT           ::VoxEng::Key::Right
#define VE_KEY_LEFT            ::VoxEng::Key::Left
#define VE_KEY_DOWN            ::VoxEng::Key::Down
#define VE_KEY_UP              ::VoxEng::Key::Up
#define VE_KEY_PAGE_UP         ::VoxEng::Key::PageUp
#define VE_KEY_PAGE_DOWN       ::VoxEng::Key::PageDown
#define VE_KEY_HOME            ::VoxEng::Key::Home
#define VE_KEY_END             ::VoxEng::Key::End
#define VE_KEY_CAPS_LOCK       ::VoxEng::Key::CapsLock
#define VE_KEY_SCROLL_LOCK     ::VoxEng::Key::ScrollLock
#define VE_KEY_NUM_LOCK        ::VoxEng::Key::NumLock
#define VE_KEY_PRINT_SCREEN    ::VoxEng::Key::PrintScreen
#define VE_KEY_PAUSE           ::VoxEng::Key::Pause
#define VE_KEY_F1              ::VoxEng::Key::F1
#define VE_KEY_F2              ::VoxEng::Key::F2
#define VE_KEY_F3              ::VoxEng::Key::F3
#define VE_KEY_F4              ::VoxEng::Key::F4
#define VE_KEY_F5              ::VoxEng::Key::F5
#define VE_KEY_F6              ::VoxEng::Key::F6
#define VE_KEY_F7              ::VoxEng::Key::F7
#define VE_KEY_F8              ::VoxEng::Key::F8
#define VE_KEY_F9              ::VoxEng::Key::F9
#define VE_KEY_F10             ::VoxEng::Key::F10
#define VE_KEY_F11             ::VoxEng::Key::F11
#define VE_KEY_F12             ::VoxEng::Key::F12
#define VE_KEY_F13             ::VoxEng::Key::F13
#define VE_KEY_F14             ::VoxEng::Key::F14
#define VE_KEY_F15             ::VoxEng::Key::F15
#define VE_KEY_F16             ::VoxEng::Key::F16
#define VE_KEY_F17             ::VoxEng::Key::F17
#define VE_KEY_F18             ::VoxEng::Key::F18
#define VE_KEY_F19             ::VoxEng::Key::F19
#define VE_KEY_F20             ::VoxEng::Key::F20
#define VE_KEY_F21             ::VoxEng::Key::F21
#define VE_KEY_F22             ::VoxEng::Key::F22
#define VE_KEY_F23             ::VoxEng::Key::F23
#define VE_KEY_F24             ::VoxEng::Key::F24
#define VE_KEY_F25             ::VoxEng::Key::F25

/* Keypad */
#define VE_KEY_KP_0            ::VoxEng::Key::KP0
#define VE_KEY_KP_1            ::VoxEng::Key::KP1
#define VE_KEY_KP_2            ::VoxEng::Key::KP2
#define VE_KEY_KP_3            ::VoxEng::Key::KP3
#define VE_KEY_KP_4            ::VoxEng::Key::KP4
#define VE_KEY_KP_5            ::VoxEng::Key::KP5
#define VE_KEY_KP_6            ::VoxEng::Key::KP6
#define VE_KEY_KP_7            ::VoxEng::Key::KP7
#define VE_KEY_KP_8            ::VoxEng::Key::KP8
#define VE_KEY_KP_9            ::VoxEng::Key::KP9
#define VE_KEY_KP_DECIMAL      ::VoxEng::Key::KPDecimal
#define VE_KEY_KP_DIVIDE       ::VoxEng::Key::KPDivide
#define VE_KEY_KP_MULTIPLY     ::VoxEng::Key::KPMultiply
#define VE_KEY_KP_SUBTRACT     ::VoxEng::Key::KPSubtract
#define VE_KEY_KP_ADD          ::VoxEng::Key::KPAdd
#define VE_KEY_KP_ENTER        ::VoxEng::Key::KPEnter
#define VE_KEY_KP_EQUAL        ::VoxEng::Key::KPEqual

#define VE_KEY_LEFT_SHIFT      ::VoxEng::Key::LeftShift
#define VE_KEY_LEFT_CONTROL    ::VoxEng::Key::LeftControl
#define VE_KEY_LEFT_ALT        ::VoxEng::Key::LeftAlt
#define VE_KEY_LEFT_SUPER      ::VoxEng::Key::LeftSuper
#define VE_KEY_RIGHT_SHIFT     ::VoxEng::Key::RightShift
#define VE_KEY_RIGHT_CONTROL   ::VoxEng::Key::RightControl
#define VE_KEY_RIGHT_ALT       ::VoxEng::Key::RightAlt
#define VE_KEY_RIGHT_SUPER     ::VoxEng::Key::RightSuper
#define VE_KEY_MENU            ::VoxEng::Key::Menu