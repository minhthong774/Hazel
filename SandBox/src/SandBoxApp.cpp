#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <imgui/imgui.h>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Sandbox2D.h"
#include "Rocket/GameLayer.h"

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
		//PushLayer(new GameLayer());
	};
	~Sandbox()
	{
	}
};
Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}