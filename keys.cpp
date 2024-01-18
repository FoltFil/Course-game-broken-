struct Button_State {
	bool is_down;
	bool changed;
};

enum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_W,
	BUTTON_S,
	BUTTON_ENTER,
	BUTTON_ESC,




	BUTTON_COUNT,
};

enum Gamemode {
	GM_MENU,
	GM_GAMEPLAY,
	GM_WIN,
	GM_LOSE,
};

struct Input {
	Button_State buttons[BUTTON_COUNT];
};