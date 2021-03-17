//code from https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/MouseCodes.h
namespace VoxEng
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

#define VE_MOUSE_BUTTON_0      ::VoxEng::Mouse::Button0
#define VE_MOUSE_BUTTON_1      ::VoxEng::Mouse::Button1
#define VE_MOUSE_BUTTON_2      ::VoxEng::Mouse::Button2
#define VE_MOUSE_BUTTON_3      ::VoxEng::Mouse::Button3
#define VE_MOUSE_BUTTON_4      ::VoxEng::Mouse::Button4
#define VE_MOUSE_BUTTON_5      ::VoxEng::Mouse::Button5
#define VE_MOUSE_BUTTON_6      ::VoxEng::Mouse::Button6
#define VE_MOUSE_BUTTON_7      ::VoxEng::Mouse::Button7
#define VE_MOUSE_BUTTON_LAST   ::VoxEng::Mouse::ButtonLast
#define VE_MOUSE_BUTTON_LEFT   ::VoxEng::Mouse::ButtonLeft
#define VE_MOUSE_BUTTON_RIGHT  ::VoxEng::Mouse::ButtonRight
#define VE_MOUSE_BUTTON_MIDDLE ::VoxEng::Mouse::ButtonMiddle