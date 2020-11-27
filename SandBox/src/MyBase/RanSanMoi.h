#pragma once

#include "Hazel/Core/KeyCode.h"
#include "Hazel/Core/TimeStep.h"
#include "Hazel/Core/Input.h"
#include "glm/glm.hpp"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/KeyEvent.h"

#include "Hazel/Renderer/OrthographicCameraController.h"

class Point
{
public:
	glm::vec2 ToVec2() { return { (float)x * 0.055f-0.5f,(float)y * 0.055f-0.5f }; }
public:
	int x, y;
	int x0, y0;
};

class RanSanMoi
{
public:
	RanSanMoi();
	~RanSanMoi() {};

	void InitGame();

	void OnEvent(Hazel::Event& e);
	bool OnKeyPressedEvent(Hazel::KeyPressedEvent& e);

	void CreateFood();
	void DrawPoint(int x, int y, const glm::vec4& color);
	void Draw(const Hazel::OrthographicCamera& camera);

	void Run(Hazel::Timestep& ts, const Hazel::OrthographicCamera& camera);

protected:
	Point snake[100];
	int snakeLength;
	Point direction;
	Point food;
	bool isempty[400];
	int empty[400];
	int size;
	float runTime = 0.0f;
	bool block = false;
	bool dead;
};