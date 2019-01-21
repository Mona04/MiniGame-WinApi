#include "stdafx.h"
#include "MainGame.h"

/* 타이머 정리
	1 기본 프레임
	2 애니메이션 업데이트
	11 공격 후딜 홀짝으로 p1, p2 관리
	21 스킬 오브젝트 유효시간
	31 넉백
*/

#define skill_guhun 2

HRESULT MainGame::init()
{
	gameNode::init();

	map.Init(IDB_BACKGROUND, IDB_BLOCK);

	POINT cha_chip_from[Num_Char_Skin];
	POINT cha_chip_size[Num_Char_Skin];

	cha_chip_from[0] = { 0, 0 }; // 기본
	cha_chip_size[0] = { 90, 110 };
	cha_chip_from[1] = { 90, 0 };
	cha_chip_size[1] = { 90, 110 };

	cha_chip_from[2] = { 180, 0 };  // 이동
	cha_chip_size[2] = { 90, 110 };
	cha_chip_from[3] = { 270, 0 };
	cha_chip_size[3] = { 90, 110 };
	// 일반 90 110 공격 110 110  // 스킬 50 110   // 120 90  // 40 40

	cha_chip_from[4] = { 450, 0 };    // 점프 
	cha_chip_size[4] = { 90, 110 };
	cha_chip_from[5] = { 450, 0 };
	cha_chip_size[5] = { 90, 110 };

	cha_chip_from[6] = { 540, 0 };    // 쳐맞 1
	cha_chip_size[6] = { 90, 110 };
	cha_chip_from[7] = { 540, 0 };
	cha_chip_size[7] = { 90, 110 };

	cha_chip_from[8] = { 230, 110 };    // 쳐맞 2
	cha_chip_size[8] = { 90, 110 };
	cha_chip_from[9] = { 700, 700 };
	cha_chip_size[9] = { 110, 110 };

	cha_chip_from[10] = { 640, 0 };    // 점멸
	cha_chip_size[10] = { 90, 110 };
	cha_chip_from[11] = { 640, 0 };
	cha_chip_size[11] = { 90, 110 };

	cha_chip_from[12] = { 0, 110 };   // 공격 1
	cha_chip_size[12] = { 110, 110 };
	cha_chip_from[13] = { 110, 110 };
	cha_chip_size[13] = { 110, 110 };

	cha_chip_from[14] = { 360, 0 };   // 공격 2
	cha_chip_size[14] = { 90, 110 };
	cha_chip_from[15] = { 360, 0 };
	cha_chip_size[15] = { 90, 110 };

	RECT temp = { 600, WINSIZEY - 360, 600 + 90,  WINSIZEY - 360 + 110 };

	player1.Init(IDB_Byakuya, cha_chip_from, cha_chip_size, temp);

	temp = { 800, WINSIZEY - 360, 800 + 90,  WINSIZEY - 360 + 110 };

	player2.Init(IDB_Ichigo, cha_chip_from, cha_chip_size, temp);


	POINT ski_chip_from[Num_Skill_Skin];
	POINT ski_chip_size[Num_Skill_Skin];

	ski_chip_from[0] = { 700, 0 };
	ski_chip_size[0] = { 50, 50 };
	ski_chip_from[1] = { 700, 0 };
	ski_chip_size[1] = { 50, 50 };

	skill1[0].Init(IDB_Byakuya, ski_chip_from, ski_chip_size, 0, 101, 1000);

	ski_chip_from[0] = { 40, 220 };
	ski_chip_size[0] = { 50, 50 };
	ski_chip_from[1] = { 90, 220 };
	ski_chip_size[1] = { 50, 50 };

	skill1[1].Init(IDB_Byakuya, ski_chip_from, ski_chip_size, 2, 102, 5000);

	ski_chip_from[0] = { 700, 0 };
	ski_chip_size[0] = { 50, 50 };
	ski_chip_from[1] = { 700, 0 };
	ski_chip_size[1] = { 50, 50 };

	skill2[0].Init(IDB_Ichigo, ski_chip_from, ski_chip_size, 0, 111, 1000);

	ski_chip_from[0] = { 0, 220 };
	ski_chip_size[0] = { 50, 110 };
	ski_chip_from[1] = { 50, 220 };
	ski_chip_size[1] = { 50, 110 };

	skill2[1].Init(IDB_Ichigo, ski_chip_from, ski_chip_size, 1, 112, 2000);

	return S_OK;
}

void MainGame::release()
{
	gameNode::release();
	player1.Release();
	player2.Release();
	skill1[0].Release();
	skill2[0].Release();
	map.Release();
}

void MainGame::update()
{
	gameNode::update();

	if (KEYMANAGER->isOnceKeyDown('R')) {
		this->init();
	}
	if (player1.get_hp_bar() <= 0 || player2.get_hp_bar() <= 0) {
		this->init();
	}

	RECT player_rc = player1.get_RC();
	if (player_rc.left < 0 || player_rc.top < 0 || player_rc.right > WINSIZEX || player_rc.bottom > WINSIZEY)
		this->init();
	player_rc = player2.get_RC();
	if (player_rc.left < 0 || player_rc.top < 0 || player_rc.right > WINSIZEX || player_rc.bottom > WINSIZEY)
		this->init();
	
	int tmp_key1[10] = { 'A', 'W', 'D', 'S', 'F', 'G'};
	Player_Move(&player1, skill1, tmp_key1, 11);
	int tmp_key2[10] = { VK_LEFT, VK_UP, VK_RIGHT, VK_DOWN, 0xBF, 0xBE };
	Player_Move(&player2, skill2, tmp_key2, 12);

	int Is_attacked;

	for (int i = 0; i < skill_guhun; i++) {
		if (player1.get_is_invincible() == 1)
			break;
		Is_attacked = player1.Is_attacked(21, 1000, skill2[i].get_RC(), i, player2.get_cur_dir());
		if (Is_attacked) {
			skill2[i].Deativate(skill2[i].get_timer_id());
			if (i == 1) {
				player1.Start_invincible(31, 3000);
			}
		}
	}

	for (int i = 0; i < skill_guhun; i++) {
		if (player2.get_is_invincible() == 1)
			break;
		Is_attacked = player2.Is_attacked(22, 1000, skill1[i].get_RC(), i, player1.get_cur_dir());
		if (Is_attacked) {
			skill1[i].Deativate(skill1[i].get_timer_id());
			if (i == 1) {
				player2.Start_invincible(32, 3000);
			}
		}
	}

	player1.Object_Engine(&map);
	player2.Object_Engine(&map);

	for (int i = 0; i < skill_guhun; i++) {
		skill1[i].Object_Engine(&map);
		skill2[i].Object_Engine(&map);
	}

	player1.air_change_status();
	player2.air_change_status();

	player1.Graviate_Object(&map);
	if (player1.get_is_air() == 0) {
		player1.set_is_jump(0);
	}
	player2.Graviate_Object(&map);
	if (player2.get_is_air() == 0) {
		player2.set_is_jump(0);
	}

}

void MainGame::render(HDC hdc)
{
	HDC backDC = this->getBackBuffer()->getMemDC();
	PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	TCHAR tmp[100];

	RECT temp = player1.get_RC();

	map.Show(backDC);

	player1.Show(backDC);
	player2.Show(backDC);

	HBRUSH brush = CreateSolidBrush(RGB(255, 100, 100));
	temp = { 0, 0, 5 * player1.get_hp_bar(), 50 };
	Rectangle(backDC, 0, 0, 5 * player1.get_hp_bar(), 50);
	FillRect(backDC, &temp, brush);
	
	temp = { WINSIZEX - 5 * player2.get_hp_bar(), 0, WINSIZEX, 50 };
	Rectangle(backDC, WINSIZEX - 5*player2.get_hp_bar(), 0, WINSIZEX, 50);
	FillRect(backDC, &temp, brush);

	DeleteObject(brush);

	for (int i = 0; i < skill_guhun; i++) {
		skill1[i].Show(backDC);
		skill2[i].Show(backDC);
	}

	swprintf(tmp, sizeof(tmp), TEXT("pt : %d, %d, cur_status : %d, %d %d %f %f"), 
		_ptMouse.x, _ptMouse.y, player2.get_cur_status(), player2.get_is_jump(), player2.get_is_air(),
	player2.get_vertical_v(), player2.get_horizontal_v());
	TextOut(backDC, 0, 0, tmp, wcslen(tmp));


	this->getBackBuffer()->render(hdc, 0, 0);
}

void MainGame::animate()
{
	player1.change_status();
	player2.change_status();
	
	for (int i = 0; i < skill_guhun; i++) {
		skill1[i].change_status(&player2);
		skill2[i].change_status(&player1);
	}
}

void MainGame::timer_update(int var)
{
	switch (var) {
	case 11:
		player1.End_Skill(11);
		break;
	case 12:
		player2.End_Skill(12);
		break;
	case 21:
		player1.End_attacked(21);
		break;
	case 22:
		player2.End_attacked(22);
		break;
	case 31:
		player1.End_invincible(31);
		break;
	case 32:
		player2.End_invincible(32);
		break;
	default:
		for (int i = 0; i < skill_guhun; i++) {
			skill1[i].Deativate(var);
			skill2[i].Deativate(var);
		}
		break;
	}
}


void MainGame::Player_Move(Player* player, Skill* skill, int* key_set, int timer_id)
{
	if (player->get_is_attacked() == 0) {
		if (player->get_do_skill() == 1 && player->get_is_air() == 1)
		{
			if (KEYMANAGER->isStayKeyDown(key_set[0])) {
				player->Move(0);
			}
			if (KEYMANAGER->isStayKeyDown(key_set[2])) {
				player->Move(2);
			}
			if (KEYMANAGER->isOnceKeyUp(key_set[0]) || KEYMANAGER->isOnceKeyUp(key_set[2])) {
				player->Stop();
			}
		}
		else if (player->get_do_skill() == 1 && player->get_is_air() == 0) {
			player->Stop();
		}
		else if (player->get_do_skill() == 0) {

			for (int i = 0; i < 4; i++) {
				if (KEYMANAGER->isStayKeyDown(key_set[i])) {
					player->Move(i);
				}
			}
			if (KEYMANAGER->isOnceKeyUp(key_set[0]) || KEYMANAGER->isOnceKeyUp(key_set[2])) {
				player->Stop();
			}
			if (KEYMANAGER->isOnceKeyDown(key_set[4])) {
				player->Start_Skill(timer_id, 1000);
				int weapon = player->get_cur_weapon();
				skill[weapon].Activate(player->get_RC(), player->get_cur_dir());
			}
			if (KEYMANAGER->isOnceKeyDown(key_set[5])) {
				player->change_weapon();
			}
		}
	}

}


MainGame::MainGame()
{
}


MainGame::~MainGame()
{
	delete[] skill1;
	delete[] skill2;
}
