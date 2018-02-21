#pragma once

class GLFWwindow;

class App
{
public:
	App();
	~App();

	void init();
	void run();

private:
	int m_height = 720;
	int m_width = 1080;

	GLFWwindow* m_window;

};

