// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#pragma comment(lib, "msimg32.lib")

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <bitset>
#include <math.h>
#include <vector>

// TODO: reference additional headers your program requires here
#include "Resource.h"
#include "singletonBase.h"
#include "KeyManager.h"
#include "backBuffer.h"
#include "MainGame.h"

#include "방망이 대전.h"
#include "Map.h"
#include "Player.h"
#include "Skill.h"
#include "Util.h"

extern HWND hWnd;
extern HINSTANCE hInst;
extern POINT _ptMouse;

#define KEYMANAGER KeyManager::getSingleton()

#define WINSIZEX 1240 
#define WINSIZEY 600


