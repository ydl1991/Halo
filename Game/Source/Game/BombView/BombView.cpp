#include "BombView.h"

#include <ApplicationLayer/ApplicationLayer.h>
#include <ApplicationLayer/Audio/IAudio.h>
#include <Utils/Log.h>

BombView::BombView(std::shared_ptr<halo::GameUnit> pGameUnit)
	: IView{ pGameUnit }
	, m_pAudio(nullptr)
{
	
}

BombView::~BombView()
{
	
}

bool BombView::Init()
{
	auto pApp = halo::ApplicationLayer::Get();
	m_pGameLayer = pApp->GetGameLayer();

	// get system instances in the view
	m_pAudio = pApp->GetAudio();

	return true;
}