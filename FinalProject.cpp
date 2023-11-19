// FinalProject.cpp

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int height = 600;
int width = 800;
int cells = 4800;
int init = 0;

int t = 0;
bool G1[80][60];
bool G2[80][60];

void generate() {
	for (int i = 0; i < cells; i++) {
		int x = rand() % 80;
		int y = rand() % 60;
		G1[x][y] = 1;
	}
}

void drawGrid(RenderWindow& window) {
	for (int x = 0; x < 80; x++) {
		for (int y = 0; y < 60; y++) {
			if (G1[x][y] == 1) {
				RectangleShape cell(Vector2f(10, 10));
				cell.setPosition(x * 10, y * 10);
				cell.setFillColor(Color::Black);
				window.draw(cell);
			}
		}
	}
}

int neighbors(bool G[80][60], int x, int y) {
	int neighbors = 0;
	if (G[x + 1][y] == 1) {
		neighbors++;
	}
	if (G[x - 1][y] == 1) {
		neighbors++;
	}
	if (G[x][y + 1] == 1) {
		neighbors++;
	}
	if (G[x][y - 1] == 1) {
		neighbors++;
	}
	if (G[x + 1][y + 1] == 1) {
		neighbors++;
	}
	if (G[x + 1][y - 1] == 1) {
		neighbors++;
	}
	if (G[x - 1][y + 1] == 1) {
		neighbors++;
	}
	if (G[x - 1][y - 1] == 1) {
		neighbors++;
	}
	return neighbors;
}

bool rule(int n, bool lod, int x, int y) {
	if (lod == 1) {
		if (n < 2) {
			return false;
		}
		else if (n == 2 || n == 3) {
			return true;
		}
		else if (n > 3) {
			return false;
		}
	}
	else {
		if (n == 3) {
			return true;
		}
		else {
			return false;
		}
	}
}

void update(bool G1[80][60], bool G2[80][60]) {
	for (int x = 0; x < 80; x++) {
		for (int y = 0; y < 60; y++) {
			G2[x][y] = rule(neighbors(G1, x, y), G1[x][y], x, y);
		}
	}
	for (int x = 0; x < 80; x++) {
		for (int y = 0; y < 60; y++) {
			bool temp = G1[x][y];
			G1[x][y] = G2[x][y];
			G2[x][y] = temp;
		}
	}
}


int main() {
	RenderWindow window(VideoMode(1920, 1080), "Final Project");
	window.setFramerateLimit(30);

	while (true) {
		if (init == 0) {
			generate();
			init = 1;
		}
		else {
			update(G1,G2);
			drawGrid(window);
		}
		window.clear(Color::White);
	}
}