#define isDown(b) input->buttons[b].pressed
#define pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define released(b) (!input->buttons[b].isDown && input->buttons[b].changed)

bool once = true;

internal void
simulate_game(Input* input, float deltaTime) {
    if (once) {
        once = false;
    }
    drawRect(0, 0, 1920, 1080, 0x111111);
    drawRect(0, 0, 960, 540, 0xFFFFFF);
    
    drawCustomRect(0, 0, 1920, 0, 1800, 1080, 120, 1080, 0x880000);

    drawEllipse(960, 540, 250, 250, 0x228822);

}