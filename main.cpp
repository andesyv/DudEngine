#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Math/math.h"
#include "shader.h"
#include "mesh.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Setup shaders
	// -------------
	// PROJECT_DIR is a macro defined in the project settings for visual studio to point to the project base directory path
	ShaderManager::get().add(std::move(Shader{
		std::string{ PROJECT_DIR + std::string{"Shaders\\default.vert" } },
		std::string{ PROJECT_DIR + std::string{"Shaders\\default.frag" } }
		}.setName("default")));

	std::vector<Vertex> vertices{
		{{-0.5f, -0.5f, 0.f}, {0.f, 0.f, -1.f}, {0.f, 0.f} },
		{{0.5f, -0.5f, 0.f}, {0.f, 0.f, -1.f}, {1.f, 0.f} },
		{{0.5f, 0.5f, 0.f}, {0.f, 0.f, -1.f}, {1.f, 1.f} },
		{{-0.5f, -0.5f, 0.f}, {0.f, 0.f, -1.f}, {0.f, 0.f} },
		{{0.5f, 0.5f, 0.f}, {0.f, 0.f, -1.f}, {1.f, 1.f} },
		{{-0.5f, 0.5f, 0.f}, {0.f, 0.f, -1.f}, {0.f, 1.f} }
	};
	auto plane = new Mesh{vertices};
	auto plane2 = new Mesh{ vertices };

	// main render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// input
		// -----
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		plane->mMaterial.use();
		plane->draw();
		plane2->mMaterial.use();
		plane2->draw();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Deallocate resources
	delete plane;
	delete plane2;

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}