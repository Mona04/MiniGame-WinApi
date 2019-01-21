#include "stdafx.h"
#include "KeyManager.h"


HRESULT KeyManager::init()
{
	for (int i = 0; i < KEYMAX; i++) {
		this->getKeyUp().set(i, false);
		this->getKeyDown().set(i, false);
	}
	return S_OK;
}

void KeyManager::release() {}

bool KeyManager::isOnceKeyDown(int key)
{
	// 0x8000 이전엔 눌려진 적 없고 호출된 시점에는 눌려져 있는 상태
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);

	return false;
}

bool KeyManager::isOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->setKeyUp(key, true);
	}
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, false);
			return TRUE;
		}
	}
	return false;

}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;
	else return false;
}
bool KeyManager::isToggleKey(int key)
{
	// 0x0001 이전에 호출된 적이 있고 키가 눌러져 있지 않은 상태
	if (GetAsyncKeyState(key) & 0x0001) return true;
	else return false;
}

KeyManager::KeyManager()
{}


KeyManager::~KeyManager()
{}
