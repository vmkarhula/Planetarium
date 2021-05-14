#include "PlanetariumApp.h"


#include <iostream>

PlanetariumApp::PlanetariumApp():
    m_Renderer(nullptr),
    m_MainWindow(nullptr),
    m_MainScene(nullptr){


}

bool PlanetariumApp::Init(){

	if (!glfwInit())
		return false;

    glfwSetErrorCallback(ErrorCallbacks::GLFW_ErrorCallback);

    m_Renderer = new Renderer();
    
    m_MainWindow = m_Renderer->GetWindowHandle();
   
    if (!m_MainWindow) {

        std::cerr << "Error, GLFW WIndow handle could not be acquired! \n";
    }

    m_MainScene = new Scene(Scene::Preset::basic, m_Renderer);

    AppInfo::PrintOpenGLInfo();
    AppInfo::PrintInputDeviceInfo();

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

void PlanetariumApp::I_MouseButton(GLFWwindow* window, int button, int action, int mods)
{

}

void PlanetariumApp::I_MousePosition(GLFWwindow* window, double mouseX, double mouseY)
{
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

void AppInfo::PrintOpenGLInfo()
{

    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    printf("GL VENDOR:			%s\n", vendor);
    printf("GL RENDERER:			%s\n", renderer);
    printf("GL VERSION (string):		%s\n", version);
    printf("GL VERSION (integer):		%i.%i\n", major, minor);
    printf("GLSL VERSION:			%s\n", glslVersion);

}

void AppInfo::PrintInputDeviceInfo()
{
    if (glfwRawMouseMotionSupported() == GL_TRUE) {
        printf("Raw mouse motion is supported!\n");
    }
}

void InputCallbacks::I_MouseButtonForwarder(GLFWwindow* window, int button, int action, int mods)
{
    PlanetariumApp* app = reinterpret_cast<PlanetariumApp*>(glfwGetWindowUserPointer(window));
    if (app) {

        app->I_MouseButton(window, button, action, mods);
    }
}

void InputCallbacks::I_MousePositionForwarder(GLFWwindow* window, double xpos, double ypos)
{
    PlanetariumApp* app = reinterpret_cast<PlanetariumApp*>(glfwGetWindowUserPointer(window));
    if (app) {

        app->I_MousePosition(window, xpos, ypos);
    }
}
