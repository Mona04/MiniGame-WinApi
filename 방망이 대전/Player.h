#pragma once
#include "Object.h"

#define Num_Char_Skin 20

using namespace std;

class Player : public Object
{
private:
	HBITMAP character_chip, o_chip;	
	POINT cha_chip_from[Num_Char_Skin];
	POINT cha_chip_size[Num_Char_Skin];
	
	int cur_status;
	int cur_dir;

	int walk_p;
	int jump_p;

	int is_jump;

	SYSTEMTIME past_st, cur_st;

	int do_skill;
	int cur_weapon;
	int all_weapon;

	int is_attacked;
	int is_invincible;

	int hp_bar;

public:
	void Init(int name, POINT* from, POINT*size, RECT);
	void Show(HDC);
	void Release();

	void Move(int var);

	void Start_Skill(int timer_id, int timer_t);
	void End_Skill(int timer_id);

	int Is_attacked(int timer_id, int timer_t, RECT in_rc, int att_type, int in_dir);
	void End_attacked(int timer_id);
	void Start_invincible(int timer_id, int timer_t);
	void End_invincible(int timer_id);

	inline void Stop() { 
		if ( get_is_air() == 0  && get_do_skill() == 0)
			cur_status = 0 + cur_status % 2;
		set_horizontal_v(0);
	}

	inline void air_change_status() {
		if (do_skill == 0 && is_attacked == 0) {
			if (get_is_air() == 1)
				cur_status = 4 + cur_status % 2;
			else if (get_is_air() == 0 && cur_status / 2 == 2)
				cur_status = 0 + cur_status % 2;
		}
	}

	inline void change_status() {
		if (cur_status % 2 == 0) cur_status += 1;
		else if (do_skill == 1) {
			if (cur_status % 2 == 0)
				cur_status += 1;
		}
		else cur_status -= 1;
	}

	inline int get_cur_status() { return cur_status; }
	inline void set_cur_status(int var) { cur_status = var; }

	inline int get_cur_dir() { return cur_dir; }
	inline void set_cur_dir(int var) { cur_dir = var; }

	inline int get_walk_p() { return walk_p; }

	inline int get_is_jump() { return is_jump; }
	inline void set_is_jump(int var) { is_jump = var; }

	inline int get_do_skill() { return do_skill; }
	inline void set_do_skill(int var) { do_skill = var; }

	inline int get_cur_weapon() { return cur_weapon; }
	inline void set_cur_weapon(int var) { cur_weapon = var; }

	inline int get_is_attacked() { return is_attacked; }
	inline void set_is_attacked(int var) { is_attacked = var; }

	inline int get_is_invincible() { return is_invincible; }
	inline void set_is_invincible(int var) { is_invincible = var; }

	inline int get_hp_bar() { return hp_bar; }
	inline void set_hp_bar(int var) { hp_bar = var; }

	inline void change_weapon() { cur_weapon = (cur_weapon + 1) % all_weapon;}



	Player();
	~Player();

};

