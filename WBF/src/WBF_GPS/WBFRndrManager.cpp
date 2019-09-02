#include "stdafx.h"
#include "WBFRndrManager.h"
#include "WBFRndrBase.h"


IWBFRndrManager::IWBFRndrManager() 
	: m_pRndr(nullptr)
{
}

IWBFRndrManager::~IWBFRndrManager()
{
}

void IWBFRndrManager::GLInit()
{
	m_pRndr->GLInit();
}

void IWBFRndrManager::GLDraw()
{
	m_pRndr->GLDraw();
}