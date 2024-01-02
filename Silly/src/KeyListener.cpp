#include "KeyListener.h"
#include "Input.h"
#include "Window.h"

float mvSpeed = 1.5f;


KeyListener::KeyListener(Camera camera) : mDeltaTime(-1.0f), mEditorCamera(camera)
{

}

void KeyListener::process_input(Window *window)
{

    Input input(window->getWindow());

    if (input.getKeyPressed(KeyCode::esc))
    {
        glfwSetWindowShouldClose(window->getWindow(), true);
    }

    // float camSpeed = mvSpeed * deltaTime;

    if (input.getKeyPressed(KeyCode::SHIFT))
    {
        mvSpeed = 3.5f;
    }
    else
    {
        mvSpeed = 1.5f;
    }

    if (input.getKeyPressed(KeyCode::W))
    {
        getCamera().ProcessKeyboard(FORWARD, getDeltaTime());
    }
    if (input.getKeyPressed(KeyCode::S))
    {
        getCamera().ProcessKeyboard(BACKWARD, getDeltaTime());
    }

    if (input.getKeyPressed(KeyCode::A))
    {
        getCamera().ProcessKeyboard(LEFT, getDeltaTime());
    }

    if (input.getKeyPressed(KeyCode::D))
    {
        getCamera().ProcessKeyboard(RIGHT, getDeltaTime());
    }

    if (input.getKeyPressed(KeyCode::Q))
    {
        getCamera().ProcessKeyboard(DOWN, getDeltaTime());
    }

    if (input.getKeyPressed(KeyCode::E))
    {
        getCamera().ProcessKeyboard(UP, getDeltaTime());
    }
}

Camera KeyListener::getCamera(){
    return mEditorCamera;
}

float KeyListener::getDeltaTime()
{
    return mDeltaTime;
}

void KeyListener::setDeltaTime(float deltaTime)
{
    mDeltaTime = deltaTime;
}