#include "Engine.h"
#include "Input.h"

int Engine::fps;

Engine::Engine(Window *window, double frameRate) : m_Window(window), m_frameTime(1.0f / frameRate), m_isRunning(false)
{
    cout << "Silly engine constructed" << endl;
    init();
}

Engine::~Engine() {
    cleanUp();
}

void Engine::init()
{
    cout << "initializing Silly engine!" << endl;
    // do something
}

void Engine::start()
{
    if (m_isRunning)
    {
        return;
    }

    run();
}

void Engine::run()
{
    m_isRunning = true;

    double prevTime = glfwGetTime();
    double unprocessedTime = 0;
    double frameCounter = 0;
    int frames = 0;
    Input input(m_Window->getWindow());

    while (m_isRunning)
    {

        if(input.getKeyPressed(KeyCode::esc)) {
            glfwSetWindowShouldClose(m_Window->getWindow(), true);
        }

        bool render = false;
        double startTime = glfwGetTime();
        double elapsedTime = startTime - prevTime;
        prevTime = startTime;

        unprocessedTime += elapsedTime;
        frameCounter += elapsedTime;

        if (frameCounter >= 1.0)
        {
            // Set FPS to frame count
            fps = frames;
            // Clear frame count
            frames = 0;
            // Clear frameCounter
            frameCounter = 0;

            // Print FPS to Terminal
            std::cout << fps << std::endl;
        }

        while(unprocessedTime > m_frameTime) {
            render = true;
            if(m_Window->shouldClose())
                this->stop();
            
            this->input((float) m_frameTime);
            this->update((float) m_frameTime);

            unprocessedTime -= m_frameTime;
        }

        if(render) {
            //do render things here
            this->render();
            frames++;
        } else {
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }

    cleanUp();
}

void Engine::stop() {
    if(!m_isRunning)
        return;

    m_isRunning = false;
}

void Engine::input(float delta) {
    //glfw pooling events here
}

void Engine::update(float delta) {
    //update game content here
    Input::update(delta);
    // m_Window->poolEvents();
}

void Engine::render(/*will be adding render engine later*/) {
    m_Window->clear();
    m_Window->swapBuffers();
}

void Engine::cleanUp(){
    m_Window->destroy();
}