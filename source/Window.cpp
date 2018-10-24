#include <exception>
#include <string>
#include <map>


#include "Window.h"
#include "Common.h"
#include "Vectors.h"
#include "Game.h"
#include "Graphics.h"
#include "Log.h"


using namespace std;

map<GLFWwindow*, Window*> allWindows;

void glfwErrorCallback(int len, const char* message)
{
	Log::Error << "GLFW:" << message << endl;
}

/// GLFW callbacks
void glfwWindowCloseCallback(GLFWwindow* window)
{
	if (nullptr == window)
		return;

	auto it = allWindows.find(window);

	//glfwDestroyWindow(window);

	if (end(allWindows) != it)
		Game::Instance->Delete(it->second);
}

void Window::Close()
{

}


Window::Window(const string& title, int width, int height) : GameObject(title)
{
	/// cyan
	ClearColor = Vector4(0, 0, 0, 1);
//    ClearColor = Vector4(1,0,1,1);

	Initialize(title, width, height);
	m_graphics = new class Graphics();

	allWindows[m_window] = this;
}


Window::~Window()
{
	//if (nullptr != m_window)
	//	glfwDestroyWindow(m_window);

	if (nullptr != m_graphics)
		delete m_graphics;
}


void Window::OnPreUpdate(const GameTime& time)
{
	glfwPollEvents();
}

void Window::OnPreRender(const GameTime& time)
{
    Log::Info << "Window::OnPreRender\n";
	check_gl_error();

	Activate();

    gl::ClearColor(1,0,1,1);
//	gl::ClearColor(ClearColor.x, ClearColor.y, ClearColor.z, ClearColor.w);
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	check_gl_error();
}

void Window::OnPostRender(const GameTime& time)
{
	Log::Info << "Window::OnPostRender - glfwSwapBuffers\n";
	glfwSwapBuffers(m_window);

	check_gl_error();
}


/// initialize a GLFW window
void Window::Initialize(const string& title, int width, int height)
{
    if (nullptr != m_window)
    {
        Log::Error << "Window already initialized.\n";
        return;
    }

    if (!glfwInit())
    {
        Log::Error << "Could not initialize GLFW\n";
        exit(EXIT_FAILURE);
    }


	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1); // ,GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_DEPTH_BITS, 16);


	/// enable multisampling on a 4x4 grid (for full-screen anti-aliasing)
	glfwWindowHint(GLFW_SAMPLES, 4);
	m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (!m_window)
	{
		glfwTerminate();
        Log::Error << "Could not create window\n";
        exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window);
	glfwSetErrorCallback(glfwErrorCallback);

	if (!gl::sys::LoadFunctions())
	{
		glfwTerminate();
        Log::Error << "Could not initialize OpenGL extensions\n";
		exit(EXIT_FAILURE);
	}

	glfwGetFramebufferSize(m_window, &width, &height);

	gl::Viewport(0, 0, width, height);
	gl::Enable(gl::MULTISAMPLE);

	m_width = width;
	m_height = height;

	/// callbacks
	glfwSetWindowCloseCallback(m_window, glfwWindowCloseCallback);
}

