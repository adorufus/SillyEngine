#include "Scene.h"
#include <iostream>

using namespace std;

Scene::Scene(/* args */)
{
}

void Scene::init()
{
    cout << "Initializing Scene" << endl;
}

void Scene::start()
{
    cout << "Starting Scene" << endl;
}

void Scene::imgui()
{

    cout << "Showing the IMGUI into the Scene" << endl;
}