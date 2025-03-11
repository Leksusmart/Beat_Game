#include <vector>
#include <algorithm>

internal void
fillScreen(unsigned int color) {
	unsigned int* pixel = (unsigned int*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}

float render_scale = 1;
int minx, miny, maxx, maxy;// Значения рабочей области
int lastScreenHeight = render_state.height;
int lastScreenWidth = render_state.width;

internal void initScreenVariables() {
	if (render_state.height == lastScreenHeight
		&& render_state.width == lastScreenWidth)return;
	else {
		lastScreenHeight = render_state.height;
		lastScreenWidth = render_state.width;
	}
	// Вычисляем координаты рабочей области
	if (static_cast<float>(render_state.width) / render_state.height < 16.f / 9) {// Широта наименьшая
		render_scale = static_cast<float>(render_state.width) / 1920;
	}
	else if (static_cast<float>(render_state.width) / render_state.height > 16.f / 9) {// Высота наименьшая
		render_scale = static_cast<float>(render_state.height) / 1080;
	}
	// Масштабируем
	maxx = static_cast<int>(1920 * render_scale);
	maxy = static_cast<int>(1080 * render_scale);

	// Полосы с краёв
	minx = (render_state.width - maxx) / 2;
	miny = (render_state.height - maxy) / 2;
	maxx += minx;
	maxy += miny;

	// Устанавливаем в границы окна
	minx = clamp(0, minx, render_state.width);
	miny = clamp(0, miny, render_state.height);
	maxx = clamp(0, maxx, render_state.width);
	maxy = clamp(0, maxy, render_state.height);
}
internal void drawRect(int x0, int y0, int width, int height, unsigned int color) {
	initScreenVariables();
	// Масштабируем
	x0 = static_cast<int>(x0 * render_scale);
	y0 = static_cast<int>(y0 * render_scale);
	width = static_cast<int>(width * render_scale);
	height = static_cast<int>(height * render_scale);

	// Сдвиг для полос с краёв экрана
	x0 += minx;
	y0 += miny;
	width += x0;
	height += y0;

	// Устанавливаем в границы окна
	x0 = clamp(0, x0, maxx);
	y0 = clamp(0, y0, maxy);
	width = clamp(0, width, maxx);
	height = clamp(0, height, maxy);
	// Отрисовываем
	for (int y = y0; y < height; y++) {
		unsigned int* pixel = (unsigned int*)render_state.memory + static_cast<int>(x0) + y * render_state.width;
		for (int x = x0; x < width; x++) {
			*pixel++ = color;
		}
	}
}
internal void drawLine(int x0, int y0, int x1, int y1, unsigned int color) {
	x0 += minx;
	x1 += minx;
	y0 += miny;
	y1 += miny;

	int dx = x1 - x0;
	int dy = y1 - y0;
	int abs_dx = std::abs(dx);
	int abs_dy = std::abs(dy);
	int sx = (dx > 0) ? 1 : -1;
	int sy = (dy > 0) ? 1 : -1;
	int err = abs_dx - abs_dy;

	while (true) {
		// Проверка на выход за границы
		if (x0 >= 0 && x0 < maxx && y0 >= 0 && y0 < maxy) {
			unsigned int* pixel = (unsigned int*)render_state.memory + x0 + y0 * render_state.width;
			*pixel = color; // Заливаем пиксель цветом
		}

		if (x0 == x1 && y0 == y1) break; // Если достигли конца линии
		int err2 = err * 2;
		if (err2 > -abs_dy) {
			err -= abs_dy;
			x0 += sx;
		}
		if (err2 < abs_dx) {
			err += abs_dx;
			y0 += sy;
		}
	}
}
internal void drawCustomRect(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3, unsigned int color) {
	initScreenVariables();
	// Масштабируем
	x0 = static_cast<int>(x0 * render_scale);
	y0 = static_cast<int>(y0 * render_scale);
	x1 = static_cast<int>(x1 * render_scale);
	y1 = static_cast<int>(y1 * render_scale);
	x2 = static_cast<int>(x2 * render_scale);
	y2 = static_cast<int>(y2 * render_scale);
	x3 = static_cast<int>(x3 * render_scale);
	y3 = static_cast<int>(y3 * render_scale);

	// Сдвиг для полос с краёв экрана
	x0 += minx;
	x1 += minx;
	x2 += minx;
	x3 += minx;
	y0 += miny;
	y1 += miny;
	y2 += miny;
	y3 += miny;

	// Устанавливаем в границы окна
	x0 = clamp(0, x0, maxx);
	x1 = clamp(0, x1, maxx);
	x2 = clamp(0, x2, maxx);
	x3 = clamp(0, x3, maxx);
	y0 = clamp(0, y0, maxy);
	y1 = clamp(0, y1, maxy);
	y2 = clamp(0, y2, maxy);
	y3 = clamp(0, y3, maxy);

	// Находим минимальные и максимальные координаты Y
	int minY = y0;
	int maxY = y0;
	if (y1 < minY) {
		minY = y1;
	}
	if (y1 > maxY) {
		maxY = y1;
	}

	if (y2 < minY) {
		minY = y2;
	}
	if (y2 > maxY) {
		maxY = y2;
	}

	if (y3 < minY) {
		minY = y3;
	}
	if (y3 > maxY) {
		maxY = y3;
	}

	for (int y = minY; y <= maxY; y++) {
		std::vector<int> intersections;

		// Находим пересечения с границами четырехугольника
		auto checkIntersection = [&](int x0, int y0, int x1, int y1) {
			if ((y0 <= y && y1 > y) || (y0 > y && y1 <= y)) {
				int x = x0 + (y - y0) * (x1 - x0) / (y1 - y0);
				intersections.push_back(x);
			}
			};

		checkIntersection(x0,y0, x1,y1);
		checkIntersection(x1,y1, x2,y2);
		checkIntersection(x2,y2, x3,y3);
		checkIntersection(x3,y3, x0,y0);

		// Сортируем пересечения
		std::sort(intersections.begin(), intersections.end());

		// Заливаем цветом между парами пересечений
		for (size_t i = 0; i < intersections.size(); i += 2) {
			if (i + 1 < intersections.size()) {
				int x0 = intersections[i];
				int x1 = intersections[i + 1];
				for (int x = x0; x <= x1; x++) {
					// Проверка на выход за границы
					if (x >= 0 && x < maxx && y >= 0 && y < maxy) {
						unsigned int* pixel = (unsigned int*)render_state.memory + x + y * render_state.width;
						*pixel = color;
					}
				}
			}
		}
	}
}
internal void drawEllipse(int centerX, int centerY, int radiusX, int radiusY, unsigned int color) {
	initScreenVariables();
	// Масштабируем
	centerX = static_cast<int>(centerX * render_scale);
	centerY = static_cast<int>(centerY * render_scale);
	radiusX = static_cast<int>(radiusX * render_scale);
	radiusY = static_cast<int>(radiusY * render_scale);

	// Сдвиг для полос с краёв экрана
	centerX += minx;
	centerY += miny;

	// Устанавливаем в границы окна
	centerX = clamp(0, centerX, maxx);
	centerY = clamp(0, centerY, maxy);

	// Оптимизация: предварительный расчет квадратов радиусов
	const float radiusXSquared = static_cast<float>(radiusX * radiusX);
	const float radiusYSquared = static_cast<float>(radiusY * radiusY);

	for (int y = -radiusY; y <= radiusY; ++y) {
		for (int x = -radiusX; x <= radiusX; ++x) {
			// Проверка, находится ли точка внутри эллипса
			if ((x * x * radiusYSquared + y * y * radiusXSquared) <= (radiusXSquared * radiusYSquared)) {
				int drawX = centerX + x;
				int drawY = centerY + y;

				// Отрисовка
				if (drawX >= 0 && drawX < maxx && drawY >= 0 && drawY < maxy) {
					unsigned int* pixel = (unsigned int*)render_state.memory + drawX + drawY * render_state.width;
					*pixel = color;
				}
			}
		}
	}
}