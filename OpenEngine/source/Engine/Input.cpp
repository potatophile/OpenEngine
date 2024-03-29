#include "Engine/Input.h"
#include "Engine/Game.h"
#include <iostream>

Input::Input()
{
    //assign the current keys by default
    KeyboardState = SDL_GetKeyboardState(NULL);
    MouseXDelta = MouseYDelta = 0;
    ScrollDelta = 0;
    MouseX = MouseY = 0;
}

void Input::ProcessInput()
{
    //reset the delta each frame
    MouseXDelta = MouseYDelta = 0;
    ScrollDelta = 0;

    //creating event for game loop to close when a key is pressed
    SDL_Event PollEvent;

    //while the loop is waiting for input
    while (SDL_PollEvent(&PollEvent)) {
        //checking what input was pressed
        switch (PollEvent.type) {
        case SDL_MOUSEBUTTONDOWN:
            //PollEvent.button.button gets the index of the mouse button pressed
            SetMouseButtonStates(PollEvent.button.button, true);
            break;
        case SDL_MOUSEBUTTONUP:
            SetMouseButtonStates(PollEvent.button.button, false);
            break;
        case SDL_MOUSEMOTION:
            OnMouseMove(PollEvent.motion);
            break;
        case SDL_MOUSEWHEEL:
            OnMouseScroll(PollEvent.wheel);
            break;
        case SDL_KEYDOWN:
            //update all the keys on the keyboard with up or down states
            KeyboardState = SDL_GetKeyboardState(NULL);
            break;
        case SDL_KEYUP:
            KeyboardState = SDL_GetKeyboardState(NULL);
            break;
        case SDL_QUIT:      //close button clicked
            Game::GetGameInstance().CloseApp();
            break;
        default:
            break;
        }
    }
}

bool Input::IsKeyDown(SDL_Scancode Key)
{
    //make sure the keyboard state is set
    if (KeyboardState == nullptr) {
        std::cout << "No keyboard state detected." << endl;
        return false;
    }

    //return the result of the key
	return static_cast<bool>(KeyboardState[Key]);
}

bool Input::IsMouseButtonDown(MouseButtons Button)
{
    return MouseButtonStates[Button];
}

void Input::ShowCursor(bool bVisibility)
{
    static SDL_bool bIsVisible = SDL_FALSE;

    //only run if the visibility of the cursor is opposite to what the input is asking for
    //if we turn off the cursor but its already off we dont need to turn it off
    //if the cursor is off and we ask for it to be on
    if (bVisibility && bIsVisible == SDL_TRUE) {
        bIsVisible = SDL_FALSE;
        SDL_SetRelativeMouseMode(bIsVisible);
    }
    //if the cursor is on and we ask for it to be off
    else if (!bVisibility && bIsVisible == SDL_FALSE) {
        bIsVisible = SDL_TRUE;
        SDL_SetRelativeMouseMode(bIsVisible);
    }
}

void Input::SetMouseButtonStates(Uint8 ButtonIndex, bool CurrentState)
{
    MouseButtonStates[ButtonIndex] = CurrentState;
}

void Input::OnMouseMove(SDL_MouseMotionEvent& MEvent)
{
    //the mouse postion
    MouseX = MEvent.x;
    MouseY = MEvent.y;

    //movement of the mouse based on the last position
    //the relative movement
    MouseXDelta += MEvent.xrel;
    MouseYDelta += MEvent.yrel;
}

void Input::OnMouseScroll(SDL_MouseWheelEvent& MEvent)
{
    //increase the delta relative to how much was scrolled
    ScrollDelta += MEvent.preciseY;
}
