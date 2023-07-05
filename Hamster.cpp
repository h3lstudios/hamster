#include <iostream>
#include <Windows.h>

int main()
{
    const std::string separator = "---------------------------";
    const std::string logo = "HAMSTER";
    bool enableMovement = true; // Start with mouse movement enabled
    bool leftButtonDown = false; // Start with the left mouse button up
    bool rightButtonDown = false; // Start with the right mouse button up

    std::cout << logo << std::endl;
    std::cout << separator << std::endl;
    std::cout << "Use the arrow keys to move the mouse." << std::endl;
    std::cout << "Press '-' to simulate a left mouse button click or hold it down to hold the button." << std::endl;
    std::cout << "Press '=' to simulate a right mouse button click or hold it down to hold the button." << std::endl;

    while (true)
    {
        int x = 0, y = 0;

        if (enableMovement) // Check if mouse movement is enabled
        {
            if (GetAsyncKeyState(VK_UP) & 0x8000) // Move the mouse up when the up arrow is pressed
                y -= 10; // Increase the amount of movement
            if (GetAsyncKeyState(VK_DOWN) & 0x8000) // Move the mouse down when the down arrow is pressed
                y += 10; // Increase the amount of movement
            if (GetAsyncKeyState(VK_LEFT) & 0x8000) // Move the mouse left when the left arrow is pressed
                x -= 10; // Increase the amount of movement
            if (GetAsyncKeyState(VK_RIGHT) & 0x8000) // Move the mouse right when the right arrow is pressed
                x += 10; // Increase the amount of movement

            // Get the current position of the mouse
            POINT p;
            GetCursorPos(&p);

            // Add the desired movement to the current position
            p.x += x;
            p.y += y;

            // Move the mouse to the new position
            SetCursorPos(p.x, p.y);
        }

        if (GetAsyncKeyState(VK_OEM_MINUS) & 0x8000) // Simulate a left mouse button press or hold the button down
        {
            if (!leftButtonDown)
            {
                mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                leftButtonDown = true;
            }
        }
        else // Simulate a left mouse button release
        {
            if (leftButtonDown)
            {
                mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                leftButtonDown = false;
            }
        }

        if (GetAsyncKeyState(VK_OEM_PLUS) & 0x8000) // Simulate a right mouse button press or hold the button down
        {
            if (!rightButtonDown)
            {
                mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
                rightButtonDown = true;
            }
        }
        else // Simulate a right mouse button release
        {
            if (rightButtonDown)
            {
                mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                rightButtonDown = false;
            }
        }

        Sleep(16); // Sleep for a short period to avoid excessive CPU usage
    }

    return 0;
}