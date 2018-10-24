#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <set>
#include <map>

#include "Common.h"
#include "Vectors.h"
#include "GameObject.h"
#include "Graphics.h"

class Game;
class Window : public GameObject
{
	friend class ResourceManager;
	friend class Game;

public:
	Game* Game = nullptr;
	Vector4 ClearColor;

	Window() : Window("window.unknown", 1280, 720)
	{

	}

	Window(const std::string& title, int width = 1280, int height = 720);

	~Window();

	void Close();

	bool Closing()
	{
		m_closing |= (0 != glfwWindowShouldClose(m_window));

		return m_closing;
	}

	bool IsDestroyed()
	{
		return m_destroyed;
	}

	void Activate()
	{
		glfwMakeContextCurrent(m_window);
	}

	void Deactivate()
	{
		glfwMakeContextCurrent(0);
	}

	bool IsActive()
	{
		return glfwGetCurrentContext() == m_window;
	}

	void OnPreUpdate(const GameTime& time) override;

	void OnPreRender(const GameTime& time) override;

	void OnPostRender(const GameTime& time) override;

protected:
	class Graphics& Graphics()
	{
		return *m_graphics;
	}

private:
	GLFWwindow* m_window = nullptr;
	bool m_closing = false;
	bool m_destroyed = false;

	class Graphics* m_graphics;

	size_t m_width;
	size_t m_height;

	void DoUpdate(const GameTime& time);
	void DoRender(const GameTime& time);

	void Initialize(const std::string& title, int width, int height);
};

#endif

