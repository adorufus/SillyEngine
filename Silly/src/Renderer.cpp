//
// Created by Oktaviano on 02/01/24.
//

#include "Renderer.h"

Renderer::Renderer(){}

void Renderer::init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
}

void Renderer::render() {
    Window::clear();
}

void Renderer::destroy() {}
