#pragma once

class Scene
{
private:
    bool mIsRunning;
public:
    Scene(/* args */);
    void init();
    void start();
    virtual void update(float deltaTime) = 0;
    void imgui();
};
