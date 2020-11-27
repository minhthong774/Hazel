#include "RanSanMoi.h"
#include <ctime>

#include "Hazel/Renderer/Renderer2D.h"
RanSanMoi::RanSanMoi()
{
	snake[100];
	snakeLength;
	direction;
	food;
	isempty[400];
	empty[400];
	size;
	runTime = 0.0f;
	block = false;
	dead;
}
void RanSanMoi::InitGame()
{
	for (int i = 0; i < 400; i++)
	{
		isempty[i] = true;
	}
	size = 397;
	snakeLength = 3;

	snake[0].x = 2;
	snake[0].y = 0;
	isempty[0] = false;

	snake[1].x = 1;
	snake[1].y = 0;
	isempty[1] = false;

	snake[2].x = 0;
	snake[2].y = 0;
	isempty[2] = false;

	direction.x = 1;
	direction.y = 0;

	int count = 0;
	for (int i = 0; i < 400; i++)
	{
		if (isempty[i])
		{
			empty[count] = i;
			count++;
		}
	}

	dead = false;

	CreateFood();
}

void RanSanMoi::CreateFood()
{
	srand(time(NULL));
	int res = rand() % (size-0+1)+0;
	food.x = empty[res] % 20;
	food.y = empty[res] / 20;
}

void RanSanMoi::OnEvent(Hazel::Event& e)
{
	Hazel::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(RanSanMoi::OnKeyPressedEvent));
}

bool RanSanMoi::OnKeyPressedEvent(Hazel::KeyPressedEvent& e)
{
	if (!block)
	{
		uint32_t keyCode = e.GetKeyCode();

		if (keyCode == HZ_KEY_UP && direction.y != -1)
		{
			direction.x = 0;
			direction.y = 1;
		}
		else if (keyCode == HZ_KEY_DOWN && direction.y != 1)
		{
			direction.x = 0;
			direction.y = -1;
		}

		if (keyCode == HZ_KEY_LEFT && direction.x != 1)
		{
			direction.x = -1;
			direction.y = 0;
		}
		else if (keyCode == HZ_KEY_RIGHT && direction.x != -1)
		{
			direction.x = 1;
			direction.y = 0;
		}
	}

	block = true;

	return false;
}

void RanSanMoi::Run(Hazel::Timestep& ts, const Hazel::OrthographicCamera& camera)
{
	Draw(camera);
	runTime += ts.GetSecond();
	if (runTime > 0.1f && !dead)
	{
		block = false;
		runTime = 0;
		if (snake[0].x + direction.x == food.x && snake[0].y + direction.y == food.y)
		{
			snakeLength++;

			food.x0 = food.x;
			food.y0 = food.y;

			CreateFood();

			size--;
		}
		else
		{
			int duoi = snake[snakeLength-1].x * snake[snakeLength-1].y;
			isempty[duoi] = true;
		}
		for (int i = 0; i < snakeLength; ++i)
		{
			if (i == 0)
			{
				if (snake[0].x + direction.x > 19 || snake[0].y + direction.y > 19 ||
					snake[0].x + direction.x < 0 || snake[0].y + direction.y < 0)
				{
					dead = true;
					break;
				}
				snake[i].x0 = snake[i].x;
				snake[i].y0 = snake[i].y;

				snake[i].x += direction.x;
				snake[i].y += direction.y;

				int dau = snake[i].x * snake[i].y;
				isempty[dau] = false;
			}
			else
			{
				snake[i].x0 = snake[i].x;
				snake[i].y0 = snake[i].y;

				snake[i].x = snake[i - 1].x0;
				snake[i].y = snake[i - 1].y0;

				if (snake[i].x == snake[0].x && snake[i].y == snake[0].y)
					dead = true;
			}
		}

		int count = 0;
		for (int i = 0; i < 400; i++)
		{
			if (isempty[i])
			{
				empty[count] = i;
				count++;
			}
		}

	}
}

void RanSanMoi::DrawPoint(int x, int y, const glm::vec4& color)
{
	Hazel::Renderer2D::DrawQuad({ x * 0.053f - 0.5f, y * 0.053f - 0.5f }, { 0.05f, 0.05f }, color);
}

void RanSanMoi::Draw(const Hazel::OrthographicCamera& camera)
{
	Hazel::Renderer2D::BeginScene(camera);

	for(int x=0;x<20;x++)
		for (int y = 0; y < 20; y++)
		{
			DrawPoint(x, y, glm::vec4{ 0.2f, 0.3f, 0.8f, 1.0f });
		}

	for (int i = 1; i < snakeLength; i++)
	{
		DrawPoint(snake[i].x, snake[i].y, glm::vec4{ 0.5f, 0.8f, 0.3f, 1.0f });
	}
	DrawPoint(snake[0].x, snake[0].y, glm::vec4{ 0.8f, 0.3f, 0.2f, 1.0f });


	DrawPoint(food.x, food.y, glm::vec4{ 0.2f, 0.8f, 0.3f, 1.0f });

	Hazel::Renderer2D::EndScene();
}
