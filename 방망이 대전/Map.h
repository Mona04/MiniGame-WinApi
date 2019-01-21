#pragma once
#define Total_Block 200

class Map
{
private:
	HBITMAP block_chip, background_chip, o_chip;
	RECT blo_chip_rc[Total_Block];
	int block_size;

public:
	void Init(int, int);
	void Show(HDC);
	void Release();

	inline RECT get_blo_rc(int var) { return blo_chip_rc[var]; }

	Map();
	~Map();
};

