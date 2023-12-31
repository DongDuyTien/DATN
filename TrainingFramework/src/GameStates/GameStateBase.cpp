/*
#include "GSIntro.h"
#include "GSMenu.h"
*/
#include "GSPlay.h"
#include "GSIntro.h"
#include "GSMenu.h"
#include "GSGuide.h"
#include "GSLevel.h"
#include "GSShop.h"
#include "GSSetting.h"

#include "GameStatebase.h"

GameStateBase::GameStateBase(StateType stateType) : m_stateType(stateType)
{}

std::shared_ptr<GameStateBase> GameStateBase::CreateState(StateType stt)
{
	std::shared_ptr<GameStateBase> gs = nullptr;
	switch (stt)
	{
	case StateType::STATE_INVALID:
		break;
	case StateType::STATE_INTRO:
		gs = std::make_shared<GSIntro>();
		break;
	case StateType::STATE_MENU:
		gs = std::make_shared<GSMenu>();
		break;
	case StateType::STATE_GUIDE:
		gs = std::make_shared<GSGuide>();
		break;
	case StateType::STATE_SETTING:
		gs = std::make_shared<GSSetting>();
		break;
	case StateType::STATE_SHOP:
		gs = std::make_shared<GSShop>();
		break;
	case StateType::STATE_LEVEL:
		gs = std::make_shared<GSLevel>();
		break;
	case StateType::STATE_PLAY:
		gs = std::make_shared<GSPlay>();
		break;
	default:
		break;
	}
	return gs;
}

StateType GameStateBase::GetGameStateType()
{
	return m_stateType;
}