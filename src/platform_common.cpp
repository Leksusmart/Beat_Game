struct Button_State {
	bool isDown;
	bool changed;
};

enum {
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_ESCAPE,
	BUTTON_W,
	BUTTON_S,
	BUTTON_A,
	BUTTON_D,

	BUTTON_COUNT, // Should be the last item
};

struct Input {
	Button_State buttons[BUTTON_COUNT];
};