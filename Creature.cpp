#include "Creature.h"

using namespace std;

Creature::Creature() {
    c_x = c_y = 0;
}

Creature::Creature(int x, int y) {
    c_x = x;
    c_y = y;
}

Creature::~Creature() {
}

void Creature::showInfo() {
	cout << "Position: (" << c_x << "," << c_y << ")" << endl;
	cout << "Fitness: " << fitness << endl;
	cout << "Damage: " << damage << endl;
	cout << "Health: " << health << endl;
	cout << "Speed: " << speed << endl;
	cout << "Energy Level: " << energy << endl;

}

void Creature::move(int dx, int dy) {
	c_x += dx;
	c_y += dy;
	cout << "Moving by (" << dx << "," << dy << ")" << endl;
	energy -= 1;
}

