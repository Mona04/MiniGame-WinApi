#pragma once
#include "Object.h"

#define Num_Skill_Skin 20

using namespace Util;

class Skill : public Object
{
private:
	HBITMAP skill_chip, o_chip;
	POINT ski_chip_from[Num_Skill_Skin];
	POINT ski_chip_size[Num_Skill_Skin];

	int origin_width;
	int origin_height;

	int is_on;
	int type;
	int timer_id;
	int timer_t;
	int cur_dir;
	int cur_status;

public:

	void Init(int name, POINT*, POINT*, int type, int timer_id, int timer_t);
	int Show(HDC);
	void Release();

	void Activate(RECT player_rc, int player_dir);
	void Deativate(int in_id);

	inline int get_width() { return origin_width; }
	inline int get_height() { return origin_height; }
	inline void set_dir(int var) { cur_dir = var; }
	inline int get_timer_id() { return timer_id; }

	void change_status(Object* enemy);

	Skill();
	~Skill();
};

