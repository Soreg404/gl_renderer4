#pragma once

namespace glr {

	class Window {

		GLFWwindow *context = nullptr;

		int wW = 0, wH = 0, wWh = 0, wHh = 0;
		const char *title = "";

		double lastTimestamp = 0, frameTime = 0;


	public:

		Window() = delete;
		Window(int W, int H, const char *title);
		~Window();

		void create();
		bool shouldClose() const;
		void shouldClose(bool setShouldClose);

		unsigned frameActions = 0;
		void frame();

		inline float fftime() const { return static_cast<float>(frameTime); }
		inline double dftime() const { return frameTime; }

		inline int key(int k) const { return glfwGetKey(context, k); }


		inline GLFWwindow *getContext() const { return context; };

		inline Renderer createRenderer() { return Renderer(this); }

		glm::dvec2 curpos() const;

		void setSize(int W, int H);
		void setTitle(const char *title);
		inline int getW() const { return wW; };
		inline int getH() const { return wH; };
		inline int getWh() const { return wWh; };
		inline int getHh() const { return wHh; };

	};

}