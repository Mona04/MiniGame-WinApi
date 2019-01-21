#pragma once
#include "gameNode.h"
#include "Player.h"
#include "Map.h"
#include "Skill.h"

class MainGame : public gameNode
{
private :
	Map map;
	Player player1;
	Player player2;
	Skill* skill1 = new Skill[10];
	Skill* skill2 = new Skill[10];

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	virtual void animate();
	virtual void timer_update(int);
	
	void Player_Move(Player* player,Skill* skill ,int*, int );

	MainGame();
	~MainGame();
};

