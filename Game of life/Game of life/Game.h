#pragma once
#include <vector>
#include <sstream>


using namespace std;


class Game
{
private:
	vector<bool> grid;
	int x;
	int y;
	int chance;
	bool manual;
public:
	Game();
	Game(int chance);
	Game(int height, int width);
	Game(int height, int width, int chance);

	int get_chance();
	void set_chance(int chance);

	bool get_state(int x, int y);
	void set_state(int x, int y, bool state);

	bool menu();
	bool start();
	bool step();
};

