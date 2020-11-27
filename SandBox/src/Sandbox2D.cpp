#include "Sandbox2D.h"
#include <imgui/imgui.h>

#include "glm/gtc/type_ptr.hpp"

static const uint32_t s_MapWidth = 24;
static const char* s_MapTiles =
"WWWWWWWWWWWWWWWWWWWWWWWW"
"WWWWWWDDDDDDWWWWWWWWWWWW"
"WWWWWDDDDDDDDWWWWWWWWWWW"
"WWWWDDDDDDDDDDWWWWWWWWWW"
"WWWDDDDDDDDDDDDWWWWWWWWW"
"WWWDDDDDDDDDDDDDWWWWWWWW"
"WWWDDDDDWWWDDDDDDWWWWWWW"
"WWWDDDDDWWWDDDDDDDWWWWWW"
"WWWDDDDDDDDDDDDDDDWWWWWW"
"WWWWDDDDDDDDDDDDDWWWWWWW"
"WWWWWDDDDDDDDDDDWWWWWWWW"
"WWWWWWDDDDDDDDDWWWWWWWWW"
"WWWWWWWDDDDDDDWWWWWWWWWW"
"WWWWWWWWWWWWWWWWWWWWWWWW";

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");

	m_SpriteSheet = Hazel::Texture2D::Create("assets/game/textures/RPGpack_sheet_2X.png");

	m_MapWidth = s_MapWidth;
	m_MapHeight = strlen(s_MapTiles) / m_MapWidth;
	
	m_TextureBarrel = Hazel::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 9, 1 }, { 128, 128 });
	s_TextureMap['D'] = Hazel::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 6, 11 }, { 128, 128 });
	s_TextureMap['W'] = Hazel::SubTexture2D::CreateFromCoords(m_SpriteSheet, { 11, 11 }, { 128, 128 });

	m_Particle.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_Particle.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_Particle.SizeBegin = 0.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Velocity = { 0.0f, 0.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0.0f, 0.0f };
}

void Sandbox2D::OnDetach()
{
	// Shutdown here
}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	//Update
	m_CameraController.OnUpdate(ts);

	//Render
	Hazel::Renderer2D::ResetStats();

	{
		Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Hazel::RenderCommand::Clear();
	}
#if 1
	{
		//m_ParticleSystem.OnUpdate(ts);

		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Hazel::Renderer2D::DrawRotatedQuad({ 0.0f, -0.5f }, { 0.8f, 0.8f }, 45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
		Hazel::Renderer2D::DrawQuad({ 0.5f, 0.5f }, { 0.5f, 0.5f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Hazel::Renderer2D::DrawQuad({ 1.0f, -1.0f}, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		Hazel::Renderer2D::DrawRotatedQuad({ -0.5f, -0.5f }, { 2.0f, 2.0f }, rotation, m_CheckerboardTexture, 20.0f);
		Hazel::Renderer2D::EndScene();
		
		Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.5f};
				Hazel::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			}
		}
		//m_ParticleSystem.OnRender();
		Hazel::Renderer2D::EndScene();

		//if (Hazel::Input::IsMouseButtonPressed(HZ_MOUSE_BUTTON_LEFT))
		//{
		//	auto [x, y] = Hazel::Input::GetMousePosition();
		//	auto width = Hazel::Application::Get().GetWindow().GetWidth();
		//	auto height = Hazel::Application::Get().GetWindow().GetHeight();
		//
		//	auto bounds = m_CameraController.GetBounds();
		//	auto pos = m_CameraController.GetCamera().GetPosition();
		//	x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		//	y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		//	m_Particle.Position = { x + pos.x, y + pos.y };
		//	for (int i = 0; i < 5; i++)
		//		m_ParticleSystem.Emit(m_Particle);
		//}
	}
#endif
#if 0
	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	
	for (uint32_t y = 0; y < m_MapHeight; y++)
	{
		for (uint32_t x = 0; x < m_MapWidth; x++)
		{
			char tileType = s_MapTiles[x + y * m_MapWidth];
			Hazel::Ref<Hazel::SubTexture2D> texture;
			if (s_TextureMap.find(tileType) != s_TextureMap.end())
				texture = s_TextureMap[tileType];
			else
				texture = m_TextureBarrel;
			Hazel::Renderer2D::DrawQuad({ x - m_MapWidth/2.0,-(y - m_MapHeight/2.0) }, { 1, 1 }, texture);
		}
	}
#endif

	Hazel::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	auto stats = Hazel::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
}