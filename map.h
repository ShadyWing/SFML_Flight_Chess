
#define MapLength 56

enum eDirection { UP = -90, DOWN = 90, LEFT = -180, RIGHT = 0 };

struct MapPos 
{
	int x, y;
	int index;
	int rotate;
};

enum MAPFX { PLUS, MINUS, DEFUEL, REFUEL };

struct MapFxPos
{
	int x, y;
	int index;
	int rotate;
	MAPFX Fx;
};