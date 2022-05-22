#include "Game.h"


Game::Game()
{
	srand(time(NULL));

	window_width = 1400;
	window_height = 850;

	isMenu = true;
	isIngame = false;
	isGameOver = false;
	gameStartup = true;

	window.create(VideoMode(window_width, window_height), L"思想不掉队 - 飞行棋");
}

Game::~Game() {}


void Game::Run()
{
	LoadMedia();
	window.setIcon(_icon.getSize().x, _icon.getSize().y, _icon.getPixelsPtr());
	while (window.isOpen())
	{
		Initialize();

		if (isMenu)
		{
			if(gameStartup)
				loading = false;
			else if (!gameStartup)
				loading = true;
			loadingfinish = 0;
			menuBgm.play();
			menuBgm.setLoop(true);
			menuBgm.setVolume(BgmVolume);
		}
		while (isMenu || loading)
		{
			DrawMenu();

			MenuInput();

			MenuLogic();
		}

		if (isIngame)
		{
			loading = true;
			loadingfinish = 0;
			ingameBgm.play();
			ingameBgm.setLoop(true);
			ingameBgm.setVolume(BgmVolume);
		}
		while (isIngame || loading)
		{
			DrawAll();

			Input();

			Logic();
		}
		
		if (isGameOver)
		{
			loading = true;
			loadingfinish = 0;
			overBgm.play();
			overBgm.setLoop(true);
			overBgm.setVolume(BgmVolume);
		}
		while (isGameOver || loading)
		{
			if (!checkout)
			{
				CheckOut();
				checkout = true;
			}
			DrawOver();

			OverInput();

			OverLogic();
		}
		overBgm.stop();
	}
}

void Game::Initialize()
{
	turn = A;

	_round = 1;
	dice_t = 0;
	BgmVolume = 30;
	toroll = false;
	DiceBegin = false;
	checkout = false;
	randOver = true;
	dice_stop = true;
	isGameOver = false;
	isGrowing = true;
	diceAuto = true;
	loading = false;
	loadingfinish = 0;

	btnRoll.Lock(false);
	btnRefuel.Lock(false);
	btnMenu.Lock(false);
	btnRestart.Lock(false);
	btnQuit.Lock(false);
	btnAuto.Lock(false);
	btnManual.Lock(false);
	
	player_A.Init();
	player_B.Init();
	InitMap();
	window.setFramerateLimit(60);
}

void Game::InitMap()
{
	// 地图格
	if (1) 
	{
		_MapPos[0] = { 1,1,1,DOWN };
		_MapPos[1] = { 1,2,2,DOWN };
		_MapPos[2] = { 1,3,3,DOWN };
		_MapPos[3] = { 1,4,4,DOWN };
		_MapPos[4] = { 1,5,5,DOWN };
		_MapPos[5] = { 1,6,6,DOWN };
		_MapPos[6] = { 1,7,7,DOWN };
		_MapPos[7] = { 1,8,8,DOWN };
		_MapPos[8] = { 1,9,9,DOWN };

		_MapPos[9] = { 1, 10, 10, RIGHT };

		_MapPos[10] = { 2,10,11,RIGHT };
		_MapPos[11] = { 3,10,12,RIGHT };
		_MapPos[12] = { 4,10,13,RIGHT };

		_MapPos[13] = { 5,10,14,UP };

		_MapPos[14] = { 5,9,15,UP };
		_MapPos[15] = { 5,8,16,UP };
		_MapPos[16] = { 5,7,17,UP };
		_MapPos[17] = { 5,6,18,UP };
		_MapPos[18] = { 5,5,19,UP };
		_MapPos[19] = { 5,4,20,UP };

		_MapPos[20] = { 5,3,21,RIGHT };

		_MapPos[21] = { 6,3,22,RIGHT };
		_MapPos[22] = { 7,3,23,RIGHT };
		_MapPos[23] = { 8,3,24,RIGHT };

		_MapPos[24] = { 9,3,25,DOWN };

		_MapPos[25] = { 9,4,26,DOWN };
		_MapPos[26] = { 9,5,27,DOWN };
		_MapPos[27] = { 9,6,28,DOWN };
		_MapPos[28] = { 9,7,29,DOWN };
		_MapPos[29] = { 9,8,30,DOWN };
		_MapPos[30] = { 9,9,31,DOWN };

		_MapPos[31] = { 9,10,32,RIGHT };

		_MapPos[32] = { 10,10,33,RIGHT };
		_MapPos[33] = { 11,10,34,RIGHT };
		_MapPos[34] = { 12,10,35,RIGHT };

		_MapPos[35] = { 13,10,36,UP };

		_MapPos[36] = { 13,9,37,UP };
		_MapPos[37] = { 13,8,38,UP };
		_MapPos[38] = { 13,7,39,UP };
		_MapPos[39] = { 13,6,40,UP };
		_MapPos[40] = { 13,5,41,UP };
		_MapPos[41] = { 13,4,42,UP };
		_MapPos[42] = { 13,3,43,UP };
		_MapPos[43] = { 13,2,44,UP };

		_MapPos[44] = { 13,1,45,LEFT };

		_MapPos[45] = { 12,1,46,LEFT };
		_MapPos[46] = { 11,1,47,LEFT };
		_MapPos[47] = { 10,1,48,LEFT };
		_MapPos[48] = { 9,1,49,LEFT };
		_MapPos[49] = { 8,1,50,LEFT };
		_MapPos[50] = { 7,1,51,LEFT };
		_MapPos[51] = { 6,1,52,LEFT };
		_MapPos[52] = { 5,1,53,LEFT };
		_MapPos[53] = { 4,1,54,LEFT };
		_MapPos[54] = { 3,1,55,LEFT };
		_MapPos[55] = { 2,1,56,LEFT };
		//_MapPos[56] = { 1,1,57,LEFT };
	}

	// 地图效果
	if (1)
	{
		for (int j = 0; j < POINT_PLUS_NUM; j++)
		{
			_MapPlusPos[j] = { 0,0,1,MAPFX::PLUS };
		}

		for (int j = 0; j < POINT_MINUS_NUM; j++)
		{
			_MapMinusPos[j] = { 0,0,1,MAPFX::MINUS };
		}

		int i;
		for (int j = 0; j < POINT_PLUS_NUM; j++)
		{
			i = ReFx();
			if (i == 1)
				j--;
			int x = _MapPos[i - 1].x;
			int y = _MapPos[i - 1].y;
			_MapPlusPos[j] = { x,y,i,MAPFX::PLUS };
		}
		for (int j = 0; j < POINT_MINUS_NUM; j++)
		{
			i = ReFx();
			if (i == 1)
				j--;
			int x = _MapPos[i - 1].x;
			int y = _MapPos[i - 1].y;
			_MapMinusPos[j] = { x,y,i,MAPFX::MINUS };
		}

		for (int j = 0; j < GAS_MINUS_NUM; j++)
		{
			i = rand() % MapLength;
			if (i == 1)
				j--;
			int x = _MapPos[i].x;
			int y = _MapPos[i].y;
			_MapDefuelPos[j] = { x,y,i + 1,MAPFX::DEFUEL };
		}

		for (int j = 0; j < 2; j++)
		{
			if (j == 0)
				i = rand() % MapLength;
			else
				i = (i + 25) % MapLength;
			if (i == 0 || i == 30)
				j --;
			int x = _MapPos[i].x;
			int y = _MapPos[i].y;
			_MapRefuelPos[j] = { x,y,i + 1,MAPFX::REFUEL };
		}

	}
}

void Game::LoadMedia()
{
	_icon.loadFromFile("data/image/icon/icon.png");

	btnClickSoundBf.loadFromFile("data/audio/btn_click.ogg");

	btnClickSound.setBuffer(btnClickSoundBf);

	ingameBgm.openFromFile("data/audio/ingamebgm.ogg");
	menuBgm.openFromFile("data/audio/menubgm.ogg");
	overBgm.openFromFile("data/audio/overbgm.ogg");

	// 字体
	if (!font.loadFromFile("data/Fonts/zpix.ttf"))
		std::cout << "字体没有找到" << std::endl;
	text.setFont(font);
	
	// 加载组件
	btnMainMenu[0].setTex("data/image/components/btnMainMenu_255_82.png", 255, 82);
	btnMainMenu[1].setTex("data/image/components/btnMainMenu_255_82.png", 255, 82);
	btnRoll.setTex("data/image/components/btn_roll_341_118.png", 323, 103, 9, 7);
	btnRollstop.setTex("data/image/components/btn_rollstop_341_118.png", 323, 103, 9, 7);
	btnManual.setTex("data/image/components/btn_manual_107_67.png", 91, 51, 8, 8);
	btnAuto.setTex("data/image/components/btn_auto_107_67.png", 91, 51, 8, 8);
	btnRand.setTex("data/image/components/btn_rand_341_118.png", 323, 103, 9, 7);
	btnCheckout.setTex("data/image/components/btn_checkout_341_118.png", 323, 103, 9, 7);
	btnRefuel.setTex("data/image/components/btn_refuel_341_118.png", 323, 98, 9, 10, 4);
	btnMenu.setTex("data/image/components/btn_menu_216_116.png", 200, 100, 8, 8);
	btnRestart.setTex("data/image/components/btn_restart_216_166.png", 200, 100, 8, 8);
	btnQuit.setTex("data/image/components/btn_quit_216_166.png", 200, 100, 8, 8);
	if (!tTurn.loadFromFile("data/image/components/turn_201_180.png"))
		std::cout << "data/image/components/turn_201_90.png NOT FOUND" << std::endl;
	player_A.setTex("data/image/player_1.png");
	player_B.setTex("data/image/player_2.png");

	// 加载骰子
	LoadDice();

	if (!tNowturnR.loadFromFile("data/image/nowturnR.png"))
		std::cout << "nowturnR素材没找到" << std::endl;
	if (!tNowturnB.loadFromFile("data/image/nowturnB.png"))
		std::cout << "nowturnB素材没找到" << std::endl;
	if (!tCursor.loadFromFile("data/image/cursor.png"))
		std::cout << "cursor素材没有找到" << std::endl;
	if (!tMapBlock.loadFromFile("data/image/block.png"))
		std::cout << "block素材没有找到" << std::endl;
	if (!tMapFx_plus.loadFromFile("data/image/plus.png"))
		std::cout << "plus素材没有找到" << std::endl;
	if (!tMapFx_minus.loadFromFile("data/image/minus.png"))
		std::cout << "minus素材没有找到" << std::endl;
	if (!tMapFx_defuel.loadFromFile("data/image/defuel.png"))
		std::cout << "defuel素材没有找到" << std::endl;
	if (!tMapFx_refuel.loadFromFile("data/image/refuelblock.png"))
		std::cout << "refuelblock素材没有找到" << std::endl;
	if (!tMenu.loadFromFile("data/image/Mainmenu.png"))
		std::cout << "menu素材没有找到" << std::endl;
	if (!tIngame.loadFromFile("data/image/Ingame.png"))
		std::cout << "Ingameblue素材没有找到" << std::endl;
	if (!tOvermenu.loadFromFile("data/image/overmenu.png"))
		std::cout << "overmenu素材没有找到" << std::endl;
	if (!tLoading.loadFromFile("data/image/loading.png"))
		std::cout << "loading素材没有找到" << std::endl;
	spLoading.setColor(Color(spLoading.getColor().r, spLoading.getColor().g, spLoading.getColor().b, 0));
	if (!tIntro.loadFromFile("data/image/intro.png"))
		std::cout << "intro素材没有找到" << std::endl;

	spCursor.setTexture(tCursor);
	spMapBlock.setTexture(tMapBlock);
	spMapFx_plus.setTexture(tMapFx_plus);
	spMapFx_minus.setTexture(tMapFx_minus);
	spMapFx_defuel.setTexture(tMapFx_defuel);
	spMenu.setTexture(tMenu);
	spIngame.setTexture(tIngame);
	spOvermenu.setTexture(tOvermenu);
	spTurn.setTexture(tTurn);
	spMapFx_refuel.setTexture(tMapFx_refuel);
	spNowturnR.setTexture(tNowturnR);
	spNowturnB.setTexture(tNowturnB);
	spLoading.setTexture(tLoading);
	spIntro.setTexture(tIntro);

	spMapBlock.setOrigin(GRIDSIZE / 2, GRIDSIZE / 2);
	spMapFx_plus.setOrigin(tMapFx_plus.getSize().x / 2, tMapFx_plus.getSize().y / 2);
	spMapFx_minus.setOrigin(tMapFx_minus.getSize().x / 2, tMapFx_minus.getSize().y / 2);
	spMapFx_defuel.setOrigin(tMapFx_defuel.getSize().x / 2, tMapFx_defuel.getSize().y / 2);
	spMapFx_refuel.setOrigin(tMapFx_refuel.getSize().x / 2, tMapFx_refuel.getSize().y / 2);
	spNowturnR.setOrigin(tNowturnR.getSize().x / 2, tNowturnR.getSize().y / 2);
	spNowturnB.setOrigin(tNowturnB.getSize().x / 2, tNowturnB.getSize().y / 2);

}

void Game::DrawIntro()
{
	if (spIntro.getColor().a == 255 && !loading)
		loadingfinish++;
	if (spIntro.getColor().a > 0 && loading)
		spIntro.setColor(Color(spIntro.getColor().r, spIntro.getColor().g, spIntro.getColor().b, spIntro.getColor().a - 15));
	window.draw(spIntro);
	if (spIntro.getColor().a <= 0)
	{
		loading = false;
		gameStartup = false;
		loadingfinish = 0;
	}
}

void Game::DrawCursor()
{
	if (GetMousePosition().x > 0 && GetMousePosition().y > 0 && GetMousePosition().x < window_width && GetMousePosition().y < window_height)
	{
		window.setMouseCursorVisible(false);
		spCursor.setPosition(GetMousePosition().x, GetMousePosition().y);
		window.draw(spCursor);
	}
	else
	{
		window.setMouseCursorVisible(true);
	}
}

void Game::DrawMenu()
{
	window.clear();

	window.draw(spMenu);

	// 按钮
	btnMainMenu[0].RectButton::setPosition(144, 435);
	window.draw(btnMainMenu[0].getSprite());

	btnMainMenu[1].RectButton::setPosition(144, 520);
	window.draw(btnMainMenu[1].getSprite());

	int offset = 0;
	int chsize = 40;
	text.setCharacterSize(chsize);
	text.setFillColor(Color(0, 0, 0, 180));
	text.setStyle(Text::Regular);

	// 文字
	text.setPosition(160, 450 + offset);
	text.setString(L"开始游戏"); window.draw(text);
	offset += 80;
	text.setPosition(160, 450 + offset);
	text.setString(L"退出"); window.draw(text);
	offset += 80;

	// loading in
	if (loading && isMenu && !gameStartup)
	{
		if (spLoading.getColor().a > 0)
			spLoading.setColor(Color(spLoading.getColor().r, spLoading.getColor().g, spLoading.getColor().b, spLoading.getColor().a - 15));
		window.draw(spLoading);
		if (spLoading.getColor().a <= 0)
			loading = false;
	}

	// loading out
	if (loading && !isMenu && !gameStartup)
	{
		if(spLoading.getColor().a < 255)
			spLoading.setColor(Color(spLoading.getColor().r, spLoading.getColor().g, spLoading.getColor().b, spLoading.getColor().a+15));
		window.draw(spLoading);
		if (spLoading.getColor().a >= 255)
		{
			loadingfinish += 1;
			menuBgm.stop();
		}
	}

	DrawCursor();

	if (gameStartup)
		DrawIntro();

	window.display();
}

void Game::MenuInput()
{
	Event event;
	window.pollEvent(event);
	if (event.type == Event::Closed) 
	{
		isMenu = false;
		window.close();
	}

	// + / - 音量控制
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Add)
		BgmVolume += 5;
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Subtract)
		BgmVolume -= 5;

	// 主菜单 按钮
	if (btnMainMenu[0].updateStatus(GetMousePosition(), event))
	{
		btnClickSound.play();
		isMenu = false;
		isIngame = true;
		loading = true;

		btnMainMenu[0].Lock(true);
		btnMainMenu[1].Lock(true);
	}
	if (btnMainMenu[1].updateStatus(GetMousePosition(), event))
	{
		btnClickSound.play();
		menuBgm.stop();
		isMenu = false;
		window.close();
	}

}

void Game::MenuLogic()
{
	if (loadingfinish == LOADINGLENGTH + 120 && gameStartup)
		loading = true;
	if (loadingfinish == LOADINGLENGTH && !gameStartup)
	{
		loading = false;
		btnMainMenu[0].Lock(false);
		btnMainMenu[1].Lock(false);
	}
}

void Game::DrawOver()
{
	window.clear();
	spOvermenu.setPosition(0, 0);
	window.draw(spOvermenu);

	int chsize = 60;
	text.setCharacterSize(chsize);
	text.setFillColor(Color(255, 255, 255, 255));
	text.setStyle(Text::Bold);
	text.setOrigin(0, 0);

	std::stringstream _score;
	_score << player_A.GetScore();
	text.setPosition(700,  375);
	text.setFillColor(Color(0, 0, 255, 255));
	text.setString(_score.str()); window.draw(text);
	_score.str("");

	_score << player_B.GetScore();
	text.setPosition(700, 475);
	text.setFillColor(Color(255, 0, 0, 255));
	text.setString(_score.str()); window.draw(text);

	text.setCharacterSize(70);
	if (player_A.GetScore() < player_B.GetScore())
	{
		text.setPosition(245, 550);
		text.setFillColor(Color(255, 0, 0, 255));
		text.setString(L"恭喜红色方胜利！"); window.draw(text);
	}
	else if (player_A.GetScore() > player_B.GetScore())
	{
		text.setPosition(245, 550);
		text.setFillColor(Color(0, 0, 255, 255));
		text.setString(L"恭喜蓝色方胜利！"); window.draw(text);
	}
	else
	{
		text.setPosition(285, 550);
		text.setFillColor(Color(255, 255, 255, 255));
		text.setString(L"双方对局平局！"); window.draw(text);
	}

	// 重新开始 按钮
	btnRestart.RectButton::setPosition(250, 660);
	window.draw(btnRestart.getSprite());

	// 退出 按钮
	btnQuit.RectButton::setPosition(630, 660);
	window.draw(btnQuit.getSprite());

	// loading in
	if (loading && isGameOver)
	{
		if (spLoading.getColor().a > 0)
			spLoading.setColor(Color(spLoading.getColor().r, spLoading.getColor().g, spLoading.getColor().b, spLoading.getColor().a - 15));
		window.draw(spLoading);
		if (spLoading.getColor().a <= 0)
		{
			loading = false;
		}
	}

	// loading out
	if (loading && !isGameOver)
	{
		if (spLoading.getColor().a < 255)
			spLoading.setColor(Color(spLoading.getColor().r, spLoading.getColor().g, spLoading.getColor().b, spLoading.getColor().a + 15));
		window.draw(spLoading);
		if (spLoading.getColor().a >= 255)
		{
			loadingfinish += 1;
			overBgm.stop();
		}
	}

	DrawCursor();

	window.display();
}

void Game::OverInput()
{
	btnRestart.Lock(false);
	btnQuit.Lock(false);

	Event event;
	window.pollEvent(event);

	if (event.type == Event::Closed)
	{
		isGameOver = false;
		window.close();
	}

	// + / - 音量控制
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Add)
		BgmVolume += 5;
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Subtract)
		BgmVolume -= 5;


	// 获取点击坐标
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		std::cout << "点击坐标（" << Vector2f(GetMousePosition()).x << ", " << Vector2f(GetMousePosition()).y << "）" << std::endl;
	}

	// 重新开始按钮
	if (btnRestart.updateStatus(GetMousePosition(), event))
	{
		spLoading.setColor(Color(spLoading.getColor().r, spLoading.getColor().g, spLoading.getColor().b, 0));
		btnClickSound.play();
		isGameOver = false;
		isIngame = true;
		loading = true;

		btnRestart.Lock(true);
		btnQuit.Lock(true);
	}
	
	// 退出按钮
	if (btnQuit.updateStatus(GetMousePosition(), event))
	{
		btnClickSound.play();
		overBgm.stop();
		isGameOver = false;
		window.close();
	}

}

void Game::OverLogic()
{
	if (loadingfinish == LOADINGLENGTH)
	{
		loading = false;
		btnRestart.Lock(false);
		btnQuit.Lock(false);
	}
}

void Game::DrawAll()
{
	window.clear();

	DrawMap();

	DrawStatus();

	DrawButtons();

	DrawPlane();

	// loading in
	if (loading && isIngame)
	{
		if (spLoading.getColor().a > 0)
			spLoading.setColor(Color(spLoading.getColor().r, spLoading.getColor().g, spLoading.getColor().b, spLoading.getColor().a - 15));
		window.draw(spLoading);
		if (spLoading.getColor().a <= 0)
		{
			loading = false;
		}
	}

	// loading out
	if (loading && !isIngame)
	{
		if (spLoading.getColor().a < 255)
			spLoading.setColor(Color(spLoading.getColor().r, spLoading.getColor().g, spLoading.getColor().b, spLoading.getColor().a + 15));
		window.draw(spLoading);
		if (spLoading.getColor().a >= 255)
		{
			loadingfinish += 1;
			ingameBgm.stop();
		}
	}

	DrawCursor();

	window.display();
}

void Game::DrawMap()
{
	window.draw(spIngame);

	if (turn == A) 
		spTurn.setTextureRect(IntRect(0, 0, 201, 180));
	else if (turn == B) 
		spTurn.setTextureRect(IntRect(0, 180, 201, 180));
	else if (turn == RAND && !dice_t) 
		spTurn.setTextureRect(IntRect(0, 360, 201, 180));
	spTurn.setPosition(434, 291);
	window.draw(spTurn);

	for (int i = 0; i < MapLength; i++)
	{
		spMapBlock.setPosition(_MapPos[i].x * GRIDSIZE + delta_x, _MapPos[i].y * GRIDSIZE + delta_y);
		window.draw(spMapBlock);
	}

	DrawFx();
}

void Game::DrawFx()
{
	// REFUEL
	for (int j = 0; j < 2; j++)
	{
		int x = _MapPos[_MapRefuelPos[j].index - 1].x;
		int y = _MapPos[_MapRefuelPos[j].index - 1].y;
		spMapFx_refuel.setPosition(x * GRIDSIZE + delta_x, y * GRIDSIZE + delta_y);
		window.draw(spMapFx_refuel);
	}
	
	// PLUS
	for (int j = 0; j < POINT_PLUS_NUM; j++)
	{
		int x = _MapPos[_MapPlusPos[j].index - 1].x;
		int y = _MapPos[_MapPlusPos[j].index - 1].y;
		spMapFx_plus.setPosition(x * GRIDSIZE + delta_x, y * GRIDSIZE + delta_y);
		window.draw(spMapFx_plus);
	}

	// MINUS
	for (int j = 0; j < POINT_MINUS_NUM; j++)
	{
		int x = _MapPos[_MapMinusPos[j].index - 1].x;
		int y = _MapPos[_MapMinusPos[j].index - 1].y;
		spMapFx_minus.setPosition(x * GRIDSIZE + delta_x, y * GRIDSIZE + delta_y);
		window.draw(spMapFx_minus);
	}

	// DEFUEL
	for (int j = 0; j < GAS_MINUS_NUM; j++)
	{
		int x = _MapPos[_MapDefuelPos[j].index - 1].x;
		int y = _MapPos[_MapDefuelPos[j].index - 1].y;
		spMapFx_defuel.setPosition(x * GRIDSIZE + delta_x, y * GRIDSIZE + delta_y);
		window.draw(spMapFx_defuel);
	}
}

void Game::DrawPlane()
{
	// 画 A飞机 蓝色
	int _x = _MapPos[player_A.GetPos() - 1].x * GRIDSIZE + delta_x;
	int _y = _MapPos[player_A.GetPos() - 1].y * GRIDSIZE + delta_y;
	int rotate = _MapPos[player_A.GetPos() - 1].rotate;
	player_A.setPosition(_x, _y);
	player_A.setRotation(rotate);
	if (turn == A)
	{
		spNowturnB.setPosition(player_A.spPlane.getPosition());
		spNowturnB.setRotation(spNowturnB.getRotation() + 1);
		if (spNowturnB.getScale().x > 1.25)
			isGrowing = false;
		else if (spNowturnB.getScale().x < 0.95)
			isGrowing = true;
		if (isGrowing)
		{
			spNowturnB.setScale(spNowturnB.getScale().x + 0.005, spNowturnB.getScale().y + 0.005);
		}
		else if (!isGrowing)
		{
			spNowturnB.setScale(spNowturnB.getScale().x - 0.005, spNowturnB.getScale().y - 0.005);
		}
		window.draw(spNowturnB);
	}
	window.draw(player_A.spPlane);

	// 画 B飞机 红色
	_x = _MapPos[player_B.GetPos() - 1].x * GRIDSIZE + delta_x;
	_y = _MapPos[player_B.GetPos() - 1].y * GRIDSIZE + delta_y;
	rotate = _MapPos[player_B.GetPos() - 1].rotate;
	player_B.setPosition(_x, _y);
	player_B.setRotation(rotate);
	if (turn == B)
	{
		spNowturnR.setPosition(player_B.spPlane.getPosition());
		spNowturnR.setRotation(spNowturnR.getRotation() + 1);
		if (spNowturnR.getScale().x > 1.25)
			isGrowing = false;
		else if (spNowturnR.getScale().x < 0.95)
			isGrowing = true;
		if (isGrowing)
		{
			spNowturnR.setScale(spNowturnR.getScale().x + 0.005, spNowturnR.getScale().y + 0.005);
		}
		else if (!isGrowing)
		{
			spNowturnR.setScale(spNowturnR.getScale().x - 0.005, spNowturnR.getScale().y - 0.005);
		}
		window.draw(spNowturnR);
	}
	window.draw(player_B.spPlane);
}

void Game::DrawStatus()
{
	DrawScore(1245, 64);

	DrawRefuel(800,660);

	DrawTurn(205, 597);

	DrawDice(1165, 370);
}

void Game::DrawTurn(int _x, int _y)
{
	text.setCharacterSize(30);
	text.setFillColor(Color(255, 255, 255, 255));
	text.setStyle(Text::Bold);
	text.setOrigin(0, 0);

	std::stringstream _score;
	_score << _round;
	text.setPosition(_x, _y);
	text.setString(_score.str()); window.draw(text);
	_score.str("");

	if (player_A._randEventSubject == -1) 
	{
		text.setCharacterSize(22);
		text.setPosition(_x - 42, _y + 82);
		text.setFillColor(Color(255, 255, 255, 255));
		text.setString(L"未到十回合"); window.draw(text);
		return;
	}
	
	text.setCharacterSize(14);
	text.setPosition(_x - 10, _y + 80);
	text.setOutlineThickness(1);
	text.setOutlineColor(Color(0, 0, 255, 255));
	switch (player_A._randEventSubject)
	{
	case 0:
		text.setString(L"变化油量"); window.draw(text);
		break;
	case 1:
		text.setString(L"随机传送"); window.draw(text);
		break;
	default:break;
	}

	text.setPosition(_x -10, _y + 100);
	text.setOutlineThickness(1);
	text.setOutlineColor(Color(255, 0, 0, 255));
	switch (player_B._randEventSubject)
	{
	case 0:
		text.setString(L"变化油量"); window.draw(text);
		break;
	case 1:
		text.setString(L"随机传送"); window.draw(text);
		break;
	default:break;
	}

	text.setOutlineThickness(0);
}

void Game::DrawRefuel(int _x, int _y)
{
	CircleShape a;
	a.setFillColor(Color(255, 200, 0, 255));
	a.setRadius(4);

	// 蓝色剩余补充次数
	for (int i = 0; i < player_A.refuelchance; i++)
	{
		a.setPosition(_x + 35 * i, _y);
		window.draw(a);
	}

	// 红色剩余补充次数
	for (int i = 0; i < player_B.refuelchance; i++)
	{
		a.setPosition(_x + 35 * i, _y + 40);
		window.draw(a);
	}
}

void Game::DrawScore(int _x, int _y)
{
	RectangleShape a;
	a.setFillColor(Color(255, 200, 0, 255));
	a.setSize(Vector2f(player_A.GetGas(), 3));
	a.setPosition(_x, _y + 130);
	window.draw(a);
	a.setSize(Vector2f(player_B.GetGas(), 3));
	a.setPosition(_x, _y + 180);
	window.draw(a);

	int offset = 0;
	int chsize = 28;
	text.setCharacterSize(chsize);
	text.setFillColor(Color(255, 255, 255, 255));
	text.setStyle(Text::Bold);
	text.setOrigin(0, 0);

	// 蓝方分数
	std::stringstream ss;
	ss << player_A.GetScore();
	text.setPosition(_x, _y + offset);
	text.setString(ss.str()); window.draw(text); ss.str("");
	offset += 1.78 * chsize;

	// 红方分数
	ss << player_B.GetScore();
	text.setPosition(_x, _y + offset);
	text.setString(ss.str()); window.draw(text); ss.str("");
	offset += 1.78 * chsize;
	
	// 蓝方油量
	ss << player_A.GetGas();
	text.setPosition(_x, _y + offset);
	text.setString(ss.str()); window.draw(text); ss.str("");
	offset += 1.78 * chsize;

	// 红方油量
	ss << player_B.GetGas();
	text.setPosition(_x, _y + offset);
	text.setString(ss.str()); window.draw(text); ss.str("");
	offset += 1.78 * chsize;
}

void Game::DrawButtons() 
{
	// 切换手动自动
	if (!diceAuto)
	{
		btnManual.RectButton::setPosition(1297, 539);
		window.draw(btnManual.getSprite());
	}
	else if (diceAuto)
	{
		btnAuto.RectButton::setPosition(1297, 539);
		window.draw(btnAuto.getSprite());
	}

	// rand 按钮
	if (_round % 10 == 0 && _round != 1 && !dice_t)
	{
		btnRefuel.Enable(false);
		btnRand.RectButton::setPosition(1064, 605);
		window.draw(btnRand.getSprite());
	}

	// checkout 按钮
	else if (isGameOver)
	{
		btnCheckout.RectButton::setPosition(1064, 605);
		window.draw(btnCheckout.getSprite());
	}

	// 骰子 按钮
	else if (dice_stop)
	{
		btnRoll.RectButton::setPosition(1064, 605);
		window.draw(btnRoll.getSprite());
	}
	else if (!dice_stop)
	{
		btnRollstop.RectButton::setPosition(1064, 605);
		window.draw(btnRollstop.getSprite());
	}

	// 补充燃料 按钮
	btnRefuel.RectButton::setPosition(1064, 732);
	window.draw(btnRefuel.getSprite());

	// 返回主页 按钮
	btnMenu.RectButton::setPosition(432, 484);
	window.draw(btnMenu.getSprite());

	// 重新开始 按钮
	btnRestart.RectButton::setPosition(432, 597);
	window.draw(btnRestart.getSprite());

	// 退出 按钮
	btnQuit.RectButton::setPosition(432, 710);
	window.draw(btnQuit.getSprite());
}

void Game::LoadDice()
{
	std::stringstream ss;
	// 加载动画序列
	for (int i = 1; i < 7; i++) 
	{
		ss << "data/image/dice/dice_" << i << ".png";
		dice[i - 1].loadFromFile(ss.str());
		ss.str("");
	}

	// 绑定动画序列
	Dice.bindFrames(dice, sizeof(dice) / sizeof(dice[0]));
}

void Game::DrawDice(int _x, int _y)
{
	Dice.setPosition(_x, _y);

	// 静止时
	if (!toroll && !DiceBegin)
	{
		Dice.stop(0);
		window.draw(Dice);
	}
	// 旋转时
	else if (toroll && (!dice_stop || diceAuto))
	{
		Dice.play();
		window.draw(Dice);
		dice_t++;
	}
	else
	{
		if (turn == B)
		{
			Dice.stop(player_A.dicePoint - 1);
			window.draw(Dice);
		}
		else
		{
			Dice.stop(player_B.dicePoint - 1);
			window.draw(Dice);
		}
	}
}

void Game::Input()
{
	Event event;
	window.pollEvent(event);
	if (event.type == Event::Closed) 
	{
		isIngame = false;
		window.close();
	}
		
	// 获取点击坐标
	if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
	{
		std::cout << "点击坐标（" << Vector2f(GetMousePosition()).x << ", " << Vector2f(GetMousePosition()).y << "）" << std::endl;
	}

	// + / - 音量控制
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Add)
		BgmVolume += 5;
	if (event.type == Event::KeyPressed && event.key.code == Keyboard::Subtract)
		BgmVolume -= 5;

	// Auto按钮
	// Manual按钮
	if (btnAuto.updateStatus(GetMousePosition(), event) && diceAuto)
	{
		btnClickSound.play();
		diceAuto = false;
	}
	else if (btnManual.updateStatus(GetMousePosition(), event) && !diceAuto)
	{
		btnClickSound.play();
		diceAuto = true;
	}
		
	// rand按钮
	if (_round % 10 == 0 && _round != 1 && btnRand.updateStatus(GetMousePosition(), event))
	{
		btnClickSound.play();

		player_A._randEventSubject = -1;
		player_B._randEventSubject = -1;

		randOver = false;
		_round++;
		turn = A;

		// 随机事件
		randOver = true;
		player_A.changescore = true;
		player_B.changescore = true;
		player_A.changegas = true;
		player_B.changegas = true;

		player_A._randEventSubject = rand() % 2;
		player_B._randEventSubject = rand() % 2;
		switch (player_A._randEventSubject)
		{
		case 0:
			player_A._randEventType = rand() % 2;
			player_A.GasChange(player_A._randEventType);
			break;
		case 1:
			player_A.ChangePos();
		default:
			break;
		}
		switch (player_B._randEventSubject)
		{
		case 0:
			player_B._randEventType = rand() % 2;
			player_B.GasChange(player_B._randEventType);
			break;
		case 1:
			player_B.ChangePos();
		default:
			break;
		}

	}

	// checkout按钮
	else if (isGameOver && btnCheckout.updateStatus(GetMousePosition(), event))
	{
		btnClickSound.play();
		isIngame = false;
		loading = true;

		spLoading.setColor(Color(spLoading.getColor().r, spLoading.getColor().g, spLoading.getColor().b, 0));
		btnMenu.Lock(true);
		btnRestart.Lock(true);
		btnQuit.Lock(true);
		btnAuto.Lock(true);
		btnManual.Lock(true);
		btnRoll.Lock(true);
		btnRand.Lock(true);
		btnRefuel.Lock(true);
		btnRollstop.Lock(true);
	}

	// 停止骰子按钮
	else if (btnRollstop.updateStatus(GetMousePosition(), event) && !dice_stop)
	{
		btnClickSound.play();
		dice_stop = true;
	}
	
	// 投骰子按钮
	else if (btnRoll.updateStatus(GetMousePosition(), event) && _round % 10 !=0)
	{
		btnClickSound.play();

		btnRoll.Lock(true);
		btnRefuel.Lock(true);
		btnManual.Lock(true);
		btnAuto.Lock(true);

		if (!diceAuto) 
		{
			dice_stop = false;
			dice_t = ROLLINGTIME;
		}

		player_A._randEventSubject = -1;
		player_B._randEventSubject = -1;
		toroll = true;
		DiceBegin = true;
		if (turn == A)
			player_A.Roll();
		else if (turn == B)
		{
			player_B.Roll();
			randOver = false;
		}
	}

	// 补充燃料按钮
	if (btnRefuel.updateStatus(GetMousePosition(), event))
	{
		btnClickSound.play();
		if (turn == A && player_A.refuelchance && player_A.GetGas() <= 60)
		{
			player_A._randEventSubject = -1;
			player_B._randEventSubject = -1;
			turn = B;
			player_A.Refuel();
		}
		else if (turn == B && player_B.refuelchance && player_B.GetGas() <= 60)
		{
			player_A._randEventSubject = -1;
			player_B._randEventSubject = -1;
			turn = A;
			player_B.Refuel();
			_round++;
		}
	}

	// 返回主页按钮
	if (btnMenu.updateStatus(GetMousePosition(), event))
	{
		btnClickSound.play();
		isIngame = false;
		isMenu = true;
		loading = true;

		spLoading.setColor(Color(spLoading.getColor().r, spLoading.getColor().g, spLoading.getColor().b, 0));
		btnMenu.Lock(true);
		btnRestart.Lock(true);
		btnQuit.Lock(true);
		btnAuto.Lock(true);
		btnManual.Lock(true);
		btnRoll.Lock(true);
		btnRand.Lock(true);
		btnRefuel.Lock(true);
		btnRollstop.Lock(true);
	}

	// 重新开始按钮
	if (btnRestart.updateStatus(GetMousePosition(), event))
	{
		btnClickSound.play();
		Initialize();
	}
		
	// 退出按钮
	if (btnQuit.updateStatus(GetMousePosition(), event))
	{
		btnClickSound.play();
		ingameBgm.stop();
		ingameBgm.stop();
		isIngame = false;
		window.close();
	}
}

const Vector2i Game::GetMousePosition()
{
	Vector2i mPoint;
	mPoint = Mouse::getPosition(window);
	mPoint.x /= ((float)window.getSize().x / window_width);
	mPoint.y /= ((float)window.getSize().y / window_height);
	return mPoint;
}

void Game::Logic()
{
	ingameBgm.setVolume(BgmVolume);

	for (int i = 0; i < 2; i++)
	{
		if (player_A.GetPos() == _MapRefuelPos[i].index && player_A.changescore)
		{
			if (player_A.refuelchance < 4)
				player_A.refuelchance++;
			_MapRefuelPos[i].index = rand() % MapLength;
		}
		if (player_B.GetPos() == _MapRefuelPos[i].index && player_B.changescore)
		{
			if (player_B.refuelchance < 4)
				player_B.refuelchance++;
			_MapRefuelPos[i].index = rand() % MapLength;
		}
	}

	for (int i = 0; i < POINT_PLUS_NUM; i++)
	{
		if (player_A.GetPos() == _MapPlusPos[i].index && player_A.changescore)
		{
			player_A.AddScore(2);
			_MapPlusPos[i].index = ReFx();
			
		}
		if (player_B.GetPos() == _MapPlusPos[i].index && player_B.changescore)
		{
			player_B.AddScore(2);
			_MapPlusPos[i].index = ReFx();
		}
	}

	for (int i = 0; i < POINT_MINUS_NUM; i++)
	{
		if (player_A.GetPos() == _MapMinusPos[i].index && player_A.changescore)
		{
			player_A.AddScore(-1);
			_MapMinusPos[i].index = ReFx();
		}
		if (player_B.GetPos() == _MapMinusPos[i].index && player_B.changescore)
		{
			player_B.AddScore(-1);
			_MapMinusPos[i].index = ReFx();
		}
	}

	for (int i = 0; i < GAS_MINUS_NUM; i++)
	{
		if (player_A.GetPos() == _MapDefuelPos[i].index && player_A.changegas)
		{
			player_A.SubGas(8);
		}
		if (player_B.GetPos() == _MapDefuelPos[i].index && player_B.changegas)
		{
			player_B.SubGas(8);
		}
	}

	if (player_A.GetPos() == player_B.GetPos() && (player_A.changegas || player_B.changegas))
	{
		if(turn == A)
			player_A.SubGas(10);
		if(turn == B)
			player_B.SubGas(10);
	}

	player_A.changescore = false;
	player_B.changescore = false;
	player_A.changegas = false;
	player_B.changegas = false;

	// 按钮状态
	if (turn == A && player_A.refuelchance)
	{
		btnRefuel.Enable(true);
		if (player_A.GetGas() > 60)
			btnRefuel.Enable(false);
	}
	else if(turn == A && !player_A.refuelchance)
		btnRefuel.Enable(false);

	if (turn == B && player_B.refuelchance)
	{
		btnRefuel.Enable(true);
		if (player_B.GetGas() > 60)
			btnRefuel.Enable(false);
	}
	else if (turn == B && !player_B.refuelchance)
		btnRefuel.Enable(false);

	// 骰子旋转结束
	if (dice_t >= ROLLINGTIME)
		dice_t = ROLLINGTIME;
	if (dice_t >= ROLLINGTIME && dice_stop)
	{
		toroll = false;
		dice_t = 0;
		btnRoll.Lock(false);
		btnRefuel.Lock(false);
		btnManual.Lock(false);
		btnAuto.Lock(false);
		if (turn == A) {
			player_A.changescore = true;
			player_A.changegas = true;
			player_A.Move(player_A.dicePoint);
			switch (player_A.dicePoint)
			{
			case 1:
			case 2:
				player_A.SubGas(1);
				break;
			case 3:
			case 4:
			case 5:
				player_A.SubGas(3);
				break;
			case 6:
				player_A.SubGas(5);
				break;
			default:break;
			}
			turn = B;
		}
		else if (turn == B) {
			player_B.changescore = true;
			player_B.changegas = true;
			player_B.Move(player_B.dicePoint);
			switch (player_B.dicePoint)
			{
			case 1:
			case 2:
				player_B.SubGas(1);
				break;
			case 3:
			case 4:
			case 5:
				player_B.SubGas(3);
				break;
			case 6:
				player_B.SubGas(5);
				break;
			default:break;
			}
			turn = A;
			_round++;
		}
		if (_round % 10 == 0 && _round != 1)
			turn = RAND;
	}

	// 判断游戏结束
	if (player_A.GetGas() <= 0 || player_B.GetGas() <= 0)
	{
		btnMenu.Lock(true);
		btnRestart.Lock(true);
		btnQuit.Lock(true);
		btnRefuel.Enable(false);
		btnAuto.Lock(true);
		btnManual.Lock(true);
		isGameOver = true;
	}

	if (loadingfinish == LOADINGLENGTH)
	{
		loading = false;

		btnMenu.Lock(false);
		btnRestart.Lock(false);
		btnQuit.Lock(false);
		btnAuto.Lock(false);
		btnManual.Lock(false);
		btnRoll.Lock(false);
		btnRand.Lock(false);
		btnRefuel.Lock(false);
		btnRollstop.Lock(false);
	}
}

// 不重合 重新生成道具 
int Game::ReFx()
{
	int k;
	while (1)
	{
		bool failed = false;
		k = rand() % MapLength;
		for (int j = 0; j < POINT_PLUS_NUM; j++)
		{
			if (k == _MapPlusPos[j].index)
			{
				failed = true;
				break;
			}
		}
		for (int j = 0; j < POINT_MINUS_NUM && !failed; j++)
		{
			if (k == _MapMinusPos[j].index)
			{
				failed = true;
				break;
			}
		}
		if (k == player_A.GetPos())
			failed = true;
		if (k == player_B.GetPos())
			failed = true;
		if (failed)
			continue;
		break;
	}
	return k;
}

void Game::CheckOut()
{
	player_A.AddScore(player_A.GetGas() / 15);
	player_B.AddScore(player_B.GetGas() / 15);
}