#include "Framebuffer.h"
#include <cassert>

Framebuffer::Framebuffer(int width, int height) : mWidth(width), mHeight(height)
{
    
}

void Framebuffer::init() {
    

    glGenFramebuffers(1, &mFbo);
    
    glBindFramebuffer(GL_FRAMEBUFFER, mFbo);

    //create framebuffer texture;
    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture, 0);

    //render buffer store depth info

    glGenRenderbuffers(1, &mRbo);
    glBindBuffer(GL_RENDERBUFFER, mRbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mRbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        assert(false && "ERROR::GL FRAMBUFFER::Framebuffer is not complete!");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
}

void Framebuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::deleteFramebuffer() {
    glDeleteRenderbuffers(1, &mRbo);
    glDeleteFramebuffers(1, &mFbo);
}

unsigned int Framebuffer::getFramebuffer() {
    return mFbo;
}

unsigned int Framebuffer::getRenderbuffer() {
    return mRbo;
}

unsigned int Framebuffer::getTextureId() {
    return mTexture;
}
