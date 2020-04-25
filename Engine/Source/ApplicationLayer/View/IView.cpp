#include "IView.h"

#include <GameLayer/GameUnit/GameUnit.h>

using halo::IView;

IView::IView(std::shared_ptr<halo::GameUnit> pGameUnit)
	: m_pGameLayer{ nullptr }
	, m_pOwner{ pGameUnit }
	, m_listIndex{ }
{
	
}

IView::~IView()
{
	
}