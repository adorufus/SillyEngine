#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Framebuffer
{
private:
    int mWidth, mHeight;
    unsigned int mFbo;
    unsigned int mRbo;
    unsigned int mTexture;

    
public:
    Framebuffer(int width, int height);
    // ~Framebuffer();
    void init();
    void bind();
    void unbind();
    unsigned int getRenderbuffer();
    unsigned int getFramebuffer();
    unsigned int getTextureId();
    void deleteFramebuffer();
};


