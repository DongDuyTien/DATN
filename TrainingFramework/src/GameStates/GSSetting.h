#pragma once
#include "GameStateBase.h"
#include "GameButton.h"
#include "GameStateMachine.h"

class GSSetting :
	public GameStateBase
{
public:
	GSSetting();
	~GSSetting();

	void	Init() override;
	void	Exit() override;
	void	Pause() override;
	void	Resume() override;

	void	HandleEvents() override;
	void	HandleKeyEvents(int key, bool bIsPressed) override;
	void	HandleTouchEvents(float x, float y, bool bIsPressed) override;
	void	HandleMouseMoveEvents(float x, float y) override;
	void	Update(float deltaTime) override;
	void	Draw() override;

private:
	std::shared_ptr<Sprite2D>					m_background;
	std::vector<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<Text>>			m_listText;
	std::vector<std::shared_ptr<Sprite2D>>		m_listSprite2D;
};

