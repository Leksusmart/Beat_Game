#include <vector>
#define isDown(b) input->buttons[b].isDown
#define pressed(b) (input->buttons[b].isDown && input->buttons[b].changed)
#define released(b) (!input->buttons[b].isDown && input->buttons[b].changed)

bool once = true;
struct obj {
	float width;
	float height;
	int line;
};
std::vector <obj*> arr1;
std::vector <obj*> arr2;
std::vector <obj*> arr3;
std::vector <obj*> arr4;

internal void objects(float deltaTime);

internal void
simulate_game(Input* input, float deltaTime) {

	if (once) {
		once = false;
	}
	if (isDown(BUTTON_ESCAPE)) {
		running = false;
	}
	fillScreen(0x000000);
	drawRect(0, 0, 1920, 1080, 0x111111);

	drawCustomRect(0, 0, 220, 1080, 1700, 1080, 1920, 0, 0x555511);

	// Декорации
	drawCustomRect(479, 0, 559, 1080, 560, 1080, 480, 0, 0xFFFFFF);
	drawCustomRect(959, 0, 959, 1080, 961, 1080, 961, 0, 0xFFFFFF);
	drawCustomRect(1438, 0, 1328, 1080, 1331, 1080, 1441, 0, 0xFFFFFF);
	drawCustomRect(67, 330, 68, 332, 1920 - 68, 332, 1920 - 67, 330, 0xFFFFFF);
	drawEllipse(300, 440, 30, 20, 0x111111);
	drawEllipse(735, 440, 30, 20, 0x111111);
	drawEllipse(1185, 440, 30, 20, 0x111111);
	drawEllipse(1620, 440, 30, 20, 0x111111);

	// Кнопки и их тени
	if (isDown(BUTTON_1)) {
		drawEllipse(240, 110, 131, 102, 0x111111);// Тень
		drawEllipse(240, 112, 130, 100, 0x771111);// Кнопка

		for (int i = 0; i < arr1.size(); ++i) {
			if (arr1[i]->height - 100 < 440) {
				arr1.erase(arr1.begin() + i);
				--i;
			}
		}
	}
	else {
		drawEllipse(240, 110, 131, 110, 0x111111);// Тень
		drawEllipse(240, 120, 130, 100, 0x771111);// Кнопка
	}
	if (isDown(BUTTON_2)) {
		drawEllipse(720, 110, 131, 102, 0x111111);// Тень
		drawEllipse(720, 112, 130, 100, 0x771111);// Кнопка
		for (int i = 0; i < arr2.size(); ++i) {
			if (arr2[i]->height - 100 < 440) {
				arr2.erase(arr2.begin() + i);
				--i;
			}
		}
	}
	else {
		drawEllipse(720, 110, 131, 110, 0x111111);// Тень
		drawEllipse(720, 120, 130, 100, 0x771111);// Кнопка
	}
	if (isDown(BUTTON_3)) {
		drawEllipse(1200, 110, 131, 102, 0x111111);// Тень
		drawEllipse(1200, 112, 130, 100, 0x771111);// Кнопка
		for (int i = 0; i < arr3.size(); ++i) {
			if (arr3[i]->height - 100 < 440) {
				arr3.erase(arr3.begin() + i);
				--i;
			}
		}
	}
	else {
		drawEllipse(1200, 110, 131, 110, 0x111111);// Тень
		drawEllipse(1200, 120, 130, 100, 0x771111);// Кнопка
	}
	if (isDown(BUTTON_4)) {
		drawEllipse(1680, 110, 131, 102, 0x111111);// Тень
		drawEllipse(1680, 112, 130, 100, 0x771111);// Кнопка
		for (int i = 0; i < arr4.size(); ++i) {
			if (arr4[i]->height - 100 < 440) {
				arr4.erase(arr4.begin() + i);
				--i;
			}
		}
	}
	else {
		drawEllipse(1680, 110, 131, 110, 0x111111);// Тень
		drawEllipse(1680, 120, 130, 100, 0x771111);// Кнопка
	}

	// Объекты
	objects(deltaTime);
	int maxSize = static_cast<int>(arr4.size());
	if (arr1.size() > maxSize)maxSize = static_cast<int>(arr1.size());
	if (arr2.size() > maxSize)maxSize = static_cast<int>(arr2.size());
	if (arr3.size() > maxSize)maxSize = static_cast<int>(arr3.size());

	for (int i = 0; i < maxSize; ++i) {
		bool deleted = false;
		if (i < arr1.size() && arr1[i]->height < 440) {
			arr1.erase(arr1.begin() + i);
			deleted = true;
		}
		if (i < arr2.size() && arr2[i]->height < 440) {
			arr2.erase(arr2.begin() + i);
			deleted = true;
		}
		if (i < arr3.size() && arr3[i]->height < 440) {
			arr3.erase(arr3.begin() + i);
			deleted = true;
		}
		if (i < arr4.size() && arr4[i]->height < 440) {
			arr4.erase(arr4.begin() + i);
			deleted = true;
		}
		if(deleted)
			--i;
	}
}
internal void createObj() {
	obj* temp = new obj{};
	temp->line = (rand() % 4) + 1;
	temp->height = 1080;

	if (temp->line == 1) {
		temp->width = 390;
		arr1.push_back(temp);
	}
	else if (temp->line == 2) {
		temp->width = 765;
		arr2.push_back(temp);
	}
	else if (temp->line == 3) {
		temp->width = 1145;
		arr3.push_back(temp);
	}
	else if (temp->line == 4) {
		temp->width = 1515;
		arr4.push_back(temp);
	}
}
internal void objects(float deltaTime) {
	int speed = 3;
	for (auto& obj : arr1) {
		obj->width -= speed * deltaTime * 7;
		obj->height -= speed * deltaTime * 50;
		drawEllipse(static_cast<int>(obj->width), static_cast<int>(obj->height), 150, 100, 0xFFFFFF);
	}
	for (auto& obj : arr2) {
		obj->width -= speed * deltaTime * 2;
		obj->height -= speed * deltaTime * 50;
		drawEllipse(static_cast<int>(obj->width), static_cast<int>(obj->height), 150, 100, 0xFFFFFF);
	}
	for (auto& obj : arr3) {
		obj->width -= speed * deltaTime * -2;
		obj->height -= speed * deltaTime * 50;
		drawEllipse(static_cast<int>(obj->width), static_cast<int>(obj->height), 150, 100, 0xFFFFFF);
	}
	for (auto& obj : arr4) {
		obj->width -= speed * deltaTime * -7;
		obj->height -= speed * deltaTime * 50;
		drawEllipse(static_cast<int>(obj->width), static_cast<int>(obj->height), 150, 100, 0xFFFFFF);
	}
	if (static_cast<int>(deltaTime*100000) % 20 == 0) {
		createObj();
	}
}