// FinalProject.cpp

#include <SFML/Graphics.hpp>

#define HEIGHT 108
#define WIDTH 192
#define CELLS 16000

using namespace sf;

int array1[109][193], array2[109][193];
int cI = 0, first = 1, selector = 1, size = 10;

//Generates the initial cells
void cellI() {
	for (int i = 1; i <= CELLS; i++) {
		int x = rand() % 192 + 1;
		int y = rand() % 108 + 1;
		array1[y][x] = 1;
	}
}

//Generates the next generation of cells
void gen1(int i, int j) {
	int neighbors = 0;
	if (array1[i - 1][j - 1] == 1) {
		neighbors++;
	}
	if (array1[i - 1][j] == 1) {
		neighbors++;
	}
	if (array1[i - 1][j + 1] == 1) {
		neighbors++;
	}
	if (array1[i][j - 1] == 1) {
		neighbors++;
	}
	if (array1[i][j + 1] == 1) {
		neighbors++;
	}
	if (array1[i + 1][j - 1] == 1) {
		neighbors++;
	}
	if (array1[i + 1][j] == 1) {
		neighbors++;
	}
	if (array1[i + 1][j + 1] == 1) {
		neighbors++;
	}
	//Rules
	if (array1[i][j] == 1) {
		if (neighbors < 2) {
			array2[i][j] = 0;
		}
		else if (neighbors == 2 || neighbors == 3) {
			array2[i][j] = 1;
		}
		else if (neighbors > 3) {
			array2[i][j] = 0;
		}
	}
	else if (array1[i][j] == 0) {
		if (neighbors == 3) {
			array2[i][j] = 1;
		}
	}
}

void gen2(int i, int j) {
	int neighbors = 0;
	if (array2[i - 1][j - 1] == 1) {
		neighbors++;
	}
	if (array2[i - 1][j] == 1) {
		neighbors++;
	}
	if (array2[i - 1][j + 1] == 1) {
		neighbors++;
	}
	if (array2[i][j - 1] == 1) {
		neighbors++;
	}
	if (array2[i][j + 1] == 1) {
		neighbors++;
	}
	if (array2[i + 1][j - 1] == 1) {
		neighbors++;
	}
	if (array2[i + 1][j] == 1) {
		neighbors++;
	}
	if (array2[i + 1][j + 1] == 1) {
		neighbors++;
	}
	//Rules
	if (array2[i][j] == 1) {
		if (neighbors < 2) {
			array1[i][j] = 0;
		}
		else if (neighbors == 2 || neighbors == 3) {
			array1[i][j] = 1;
		}
		else if (neighbors > 3) {
			array1[i][j] = 0;
		}
	}
	else if (array2[i][j] == 0) {
		if (neighbors == 3) {
			array1[i][j] = 1;
		}
	}
}

int main() {
	RenderWindow window(VideoMode(1920, 1080), "Final Project");
	window.setFramerateLimit(60);
	Texture t1;
	t1.loadFromFile("Images/orange.png");
	Sprite O(t1);

	while (window.isOpen()) {
		Event e;
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) {
				window.close();
			}
		}
		//initiate game
		if (cI == 0) {
			cellI();
			cI = 1;
		}

		window.clear(Color::White);

		for (int i = 1; i <= HEIGHT; i++) {
			for (int j = 1; j <= WIDTH; j++) {
				if (first == 1) {
					first = 0;
					if (selector == 1) {
						gen1(i, j);
					}
					else if (selector == 2) {
						gen2(i, j);
					}
				}
			}
		}

		if (selector == 1) {
			selector = 2;
			for (int i = 1; i <= HEIGHT; i++) {
				for (int j = 1; j <= WIDTH; j++) {
					array1[i][j] = 0;
				}
			}
		}
		else
		{
			selector = 1;
			for (int i = 1; i <= HEIGHT; i++) {
				for (int j = 1; j <= WIDTH; j++) {
					array2[i][j] = 0;
				}
			}
		}

		if (selector == 1) {
			for (int i = 1; i <= HEIGHT; i++) {
				for (int j = 1; j <= WIDTH; j++) {
					if (array1[i][j] == 1) {
						O.setPosition(j * size, i * size);
						window.draw(O);
					}
				}
			}
		}
		else {
			for (int i = 1; i <= HEIGHT; i++) {
				for (int j = 1; j <= WIDTH; j++) {
					if (array2[i][j] == 1) {
						O.setPosition(j * size, i * size);
						window.draw(O);
					}
				}
			}
		}
	}
}