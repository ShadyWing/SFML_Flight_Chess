#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include "map.h"
#include "player.h"
#include "Animation.h"
#include "button.h"



#define GRIDSIZE		75
#define SCALE			1.5
#define POINT_PLUS_NUM	5
#define POINT_MINUS_NUM	5
#define GAS_MINUS_NUM	3
#define POINT_NUM		15
#define ROLLINGTIME		10
#define LOADINGLENGTH	120
using namespace sf;

enum Turn { A, B, RAND };

class Game
{
public:
	Game();
	~Game();

	RenderWindow window;
	int window_width, window_height;

	int delta_x = 5;
	int delta_y = 22;
	int tick, _round, dice_t;
	int BgmVolume;
	bool isMenu, isIngame, isGameOver, gameStartup;
	bool toroll, DiceBegin, checkout, randOver, dice_stop, diceAuto;
	bool isGrowing;
	bool loading;
	int loadingfinish;
	Turn turn;
	
	SoundBuffer btnClickSoundBf;
	Sound btnClickSound;
	Music menuBgm, ingameBgm, overBgm;

	RectButton btnMainMenu[2], btnManual, btnAuto,
		btnRoll, btnRollstop, btnRand, btnCheckout,
		btnRefuel, btnMenu, btnRestart, btnQuit;
	Player player_A, player_B;
	Texture tMapBlock, tMapFx_plus, tMapFx_refuel,
		tMapFx_minus, tMapFx_defuel, tMenu,
		tIngame, tOvermenu, tTurn, dice[6], tCursor,
		tNowturnR, tNowturnB, tLoading, tIntro;
	Sprite spMapBlock, spMapFx_plus, spMapFx_refuel,
		spMapFx_minus, spMapFx_defuel, spMenu,
		spIngame, spOvermenu, spTurn, spCursor,
		spNowturnR, spNowturnB, spLoading, spIntro;
	Animation Dice;
	Font font;
	Text text;
	Image _icon;

	MapPos _MapPos[MapLength];
	MapFxPos _MapPlusPos[POINT_PLUS_NUM];
	MapFxPos _MapMinusPos[POINT_MINUS_NUM];
	MapFxPos _MapDefuelPos[GAS_MINUS_NUM];
	MapFxPos _MapRefuelPos[2];

	void Run();

	void Initialize();
	void LoadMedia();
	void InitMap();

	void DrawIntro();

	void DrawCursor();

	void DrawMenu();
	void MenuInput();
	void MenuLogic();
	void DrawOver();
	void OverInput();
	void OverLogic();

	void DrawAll();
	void DrawMap();
	void DrawFx();
	void DrawPlane();
	void DrawStatus();
	void DrawButtons();
	void DrawTurn(int _x, int _y);
	void DrawRefuel(int _x, int _y);
	void DrawScore(int _x, int _y);

	void LoadDice();
	void DrawDice(int _x, int _y);

	void CheckOut();
	void Input();
	const Vector2i GetMousePosition();

	void Logic();
	int ReFx();
};