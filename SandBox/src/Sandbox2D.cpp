#include "Sandbox2D.h"

#include "ImGui/imgui.h"
#include "glm/gtc/type_ptr.hpp"

#include "Sort.h"

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
	Sort::Init();
	//m_RanSanMoi.InitGame();
}

void Sandbox2D::OnAttach()
{
	m_CheckerboardTexture = Hazel::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Hazel::Timestep ts)
{
	//Update
	m_CameraController.OnUpdate(ts);
	//Render
	Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Hazel::RenderCommand::Clear();

	Hazel::Renderer2D::BeginScene(m_CameraController.GetCamera());
	//Hazel::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	//Hazel::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	//Hazel::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture);
	Sort::Quick3(0, 199);
	Hazel::Renderer2D::EndScene();


	//Sort::QuickSort(0, 199);
	//if (a) {
	//	Sort::HeapSort();
	//	a = false;
	//}
	//Sort::Draw();
	//if (a)
	//{
	//	Sort::MergeSort(0, 199);
	//	a = false;
	//}
	//Sort::Draw();
	//m_RanSanMoi.Run(ts, m_CameraController.GetCamera());
	//Sort::Run(ts);
	//Sort::BubbleSort(ts);
	//Sort::SelectionSort(ts);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
	m_CameraController.OnEvent(e);
	//m_RanSanMoi.OnEvent(e);
}