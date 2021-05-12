#include "PlanetariumApp.h"


#include <iostream>

PlanetariumApp::PlanetariumApp():
    m_Renderer(nullptr),
    m_MainWindow(nullptr),
    m_MainScene(nullptr){


}

bool PlanetariumApp::Init()
       {

	if (!glfwInit())
		return false;

    glfwSetErrorCallback(ErrorCallbacks::GLFW_ErrorCallback);

    m_Renderer = new Renderer();
    
    m_MainWindow = m_Renderer->GetWindowHandle();
   
    if (!m_MainWindow) {

        std::cerr << "Error, GLFW WIndow handle could not be acquired! \n";
    }

    m_MainScene = new Scene(Scene::Preset::basic, m_Renderer);

    return true; 
}


void PlanetariumApp::Run() {
    
    m_PrevTick = glfwGetTime();

    while (!glfwWindowShouldClose(m_MainWindow))
    {

        // Read input & update the world state
        glfwPollEvents();
        double currTick = glfwGetTime();
        m_DeltaTime = currTick - m_PrevTick;
        m_PrevTick = currTick;
        m_MainScene->Update(m_DeltaTime);
        

        // Render
        m_Renderer->BeginFrame();
        m_MainScene->GetRenderRequests(m_Renderer);
        m_Renderer->RenderFrame();
    }

    glfwTerminate();

}



void ErrorCallbacks::GLFW_ErrorCallback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void GLAPIENTRY ErrorCallbacks::Callback_OpenGL_Error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    if (severity > GL_DEBUG_SEVERITY_NOTIFICATION) {
        fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
            (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
    }
}