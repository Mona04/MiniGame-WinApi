#pragma once
#include "Map.h"
#include "Util.h"

#define gravity 2.51

class Object
{
protected:
	RECT _rc;
	double _vertical_v;
	double _horizontal_v;
	int _is_air;

public:
	inline RECT get_RC() { return _rc; }
	inline void set_RC(RECT var) { _rc = var; }

	inline double get_vertical_v() { return _vertical_v; }
	inline void set_vertical_v(double var) { _vertical_v = var; }

	inline double get_horizontal_v() { return _horizontal_v; }
	inline void set_horizontal_v(int var) { _horizontal_v = var; }

	inline int get_is_air() { return _is_air; }
	inline void set_is_air(int var) { _is_air = var; }

	inline void MoveLeft() { _rc.left -= 1; _rc.right -= 1; }
	inline void MoveUp() { _rc.top -= 1; _rc.bottom -= 1; }
	inline void MoveRight() { _rc.left += 1; _rc.right += 1; }
	inline void MoveDown() { _rc.top += 1; _rc.bottom += 1; }

	virtual void _Move(int var) {
		switch (var) {
		case 0:
			MoveLeft(); break;
		case 1:
			MoveUp(); break;
		case 2:
			MoveRight(); break;
		case 3:
			MoveDown(); break;
		}
	};

	void Obj_Init(RECT in_rc, int in_vertical_v, int in_horizontal_v, int in_is_air);

	void Object_Engine(Map* in_map);
	void Graviate_Object(Map* in_map);

};
