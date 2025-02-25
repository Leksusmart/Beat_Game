#define isDown(b) input->buttons[b].pressed
#define pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define released(b) (!input->buttons[b].isDown && input->buttons[b].changed)

internal void
simulate_game(Input* input, float deltaTime) {
	clearScreen(0xff5500);

}