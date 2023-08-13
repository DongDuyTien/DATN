#pragma once
#include "Text.h"
#include "Sprite2D.h"

class Notification : public Sprite2D
{
private:
	std::shared_ptr<Sprite2D>				m_bg;
	std::shared_ptr<Text>					m_text;
	float time;
public:
	Notification();
	~Notification();

	void Init();
	void Draw();
	void Update(float deltaTime);
	void Move(float fromX, float fromY, float toX, float toY);
};