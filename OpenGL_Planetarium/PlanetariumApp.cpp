#include "PlanetariumApp.h"

#include "DearIMGui/imgui.h"
#include "DearIMGui/imgui_impl_glfw.h"
#include "DearIMGui/imgui_impl_opengl3.h"

#include <iostream>

PlanetariumApp::PlanetariumApp():
    m_Renderer(nullptr),
    m_MainWindow(nullptr),
    m_MainScene(nullptr),
    m_InputHandler(nullptr),
    m_EventQueue(nullptr),
    m_DeltaTime(0.0),
    m_PrevTick(0.0){

}

// TODO: Move to smart pointers where ever appropriate
PlanetariumApp::~PlanetariumApp()
{
    delete(m_Renderer);
    delete(m_EventQueue);
    delete(m_MainScene);
    delete(m_InputHandler);

    if (m_MainWindow)
        glfwDestroyWindow(m_MainWindow);

}


bool PlanetariumApp::Init(){

	if (!glfwInit())
		return false;

    glfwSetErrorCallback(ErrorCallbacks::GLFW_ErrorCallback);

    m_Renderer = new Renderer();
    
    m_MainWindow = m_Renderer->GetWindowHandle();
   
    if (!m_MainWindow) {

        std::cerr << "Error, GLFW Window handle could not be acquired! \n";
    }

    m_MainScene = new Scene(Scene::Preset::basic, m_Renderer);
    
    AppInfo::PrintOpenGLInfo();
    AppInfo::PrintInputDeviceInfo();


    m_EventQueue = new EventQueue();

    // Input setup
    m_InputHandler = new InputHandler(m_EventQueue);

    // User  pointer for forwarding input to the app class 
    glfwSetWindowUserPointer(m_MainWindow, (void*)this);
    
    // Keyboard
    glfwSetKeyCallback(m_MainWindow, InputCallbacks::I_KeyPressForwarder);
    
    // Mouse
    glfwSetMouseButtonCallback(m_MainWindow, InputCallbacks::I_MouseButtonForwarder);
    glfwSetCursorPosCallback(m_MainWindow, InputCallbacks::I_MousePositionForwarder);
    glfwSetScrollCallback(m_MainWindow, InputCallbacks::I_MouseScrollForwarder);


    // Set up Dear ImGui

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_MainWindow, true);
    ImGui_ImplOpenGL3_Init("#version 130");

   

    return true; 
}


void PlanetariumApp::Run() {
    
    m_PrevTick = glfwGetTime();

    while (!glfwWindowShouldClose(m_MainWindow))
    {

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Read input & update the world state
        glfwPollEvents();
        double currTick = glfwGetTime();
        m_DeltaTime = currTick - m_PrevTick;
        m_PrevTick = currTick;
        m_MainScene->Update(m_DeltaTime, m_EventQueue);
    
        // Render
        m_Renderer->BeginFrame();
        m_MainScene->GetRenderRequests(m_Renderer);
        m_Renderer->RenderFrame();
    }

    glfwTerminate();

}

void PlanetariumApp::I_MouseButton(GLFWwindow* window, int button, int action, int mods)
{
    m_InputHandler->RegisterMouseClick(window, button, action, mods);
}

void PlanetariumApp::I_MousePosition(GLFWwindow* window, double mouseX, double mouseY)
{
    m_InputHandler->RegisterMouseMove(window, mouseX, mouseY);
}

void PlanetariumApp::I_KeyPress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    m_InputHandler->RegisterKeypress(window, key, scancode, action, mods);
}

void PlanetariumApp::I_MouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    m_InputHandler->RegisterMouseScroll(window, xoffset, yoffset);
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

// This is mostly borrowed from the OpenGL Shader Cookbook by David Wolff
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


// Input callbacks use window user pointer to receiver the app instance memory address
// and then use the API to pass the input info. 
// This trick is fairly standard in windows enviroment at least, as far as I can tell. 
// Here GLFW provides a bit more OS agnostic version of the window user pointer implementation.  

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

void InputCallbacks::I_MouseScrollForwarder(GLFWwindow* window, double xoffset, double yoffset)
{
    PlanetariumApp* app = reinterpret_cast<PlanetariumApp*>(glfwGetWindowUserPointer(window));
    if (app) {

        app->I_MouseScroll(window, xoffset, yoffset);
    }
}

void InputCallbacks::I_KeyPressForwarder(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    PlanetariumApp* app = reinterpret_cast<PlanetariumApp*>(glfwGetWindowUserPointer(window));
    if (app) {

        app->I_KeyPress(window, key, scancode, action, mods);
    }

}
