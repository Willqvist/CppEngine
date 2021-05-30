namespace Ziti
{
    enum class MouseCode : unsigned int
    {
        // From glfw3.h
        Button0                = 0,
        Button1                = 1,
        Button2                = 2,
        Button3                = 3,
        Button4                = 4,
        Button5                = 5,
        Button6                = 6,
        Button7                = 7,

        ButtonLast             = Button7,
        ButtonLeft             = Button0,
        ButtonRight            = Button1,
        ButtonMiddle           = Button2
    };
}

#define VE_MOUSE_BUTTON_0      ::Ziti::Mouse::Button0
#define VE_MOUSE_BUTTON_1      ::Ziti::Mouse::Button1
#define VE_MOUSE_BUTTON_2      ::Ziti::Mouse::Button2
#define VE_MOUSE_BUTTON_3      ::Ziti::Mouse::Button3
#define VE_MOUSE_BUTTON_4      ::Ziti::Mouse::Button4
#define VE_MOUSE_BUTTON_5      ::Ziti::Mouse::Button5
#define VE_MOUSE_BUTTON_6      ::Ziti::Mouse::Button6
#define VE_MOUSE_BUTTON_7      ::Ziti::Mouse::Button7
#define VE_MOUSE_BUTTON_LAST   ::Ziti::Mouse::ButtonLast
#define VE_MOUSE_BUTTON_LEFT   ::Ziti::Mouse::ButtonLeft
#define VE_MOUSE_BUTTON_RIGHT  ::Ziti::Mouse::ButtonRight
#define VE_MOUSE_BUTTON_MIDDLE ::Ziti::Mouse::ButtonMiddle