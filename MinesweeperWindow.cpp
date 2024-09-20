#include "MinesweeperWindow.h"
#include <iostream>
#include <random>

MinesweeperWindow::MinesweeperWindow(int x, int y, int width, int height, int mines, const string &title) : 
	// Initialiser medlemsvariabler, bruker konstruktoren til AnimationWindow-klassen
	AnimationWindow{x, y, width * cellSize, (height + 1) * cellSize, title},
	width{width}, height{height}, mines{mines}
{
	// Legg til alle tiles i vinduet
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			tiles.emplace_back(new Tile{ Point{j * cellSize, i * cellSize}, cellSize});
			tiles.back()->setCallback(std::bind(&MinesweeperWindow::cb_click, this));

			auto temp = tiles.back().get();
			add(*temp); 
		}
	}
	int c = 0;	
	while(c != mines){
		std::random_device rd;
    	std::default_random_engine generator(rd());
		std::uniform_int_distribution<int> distribution(0, width*height);
		int bang = distribution(generator);
		int pos = distribution(generator);
		if(bang = 10 && tiles.at(pos) -> getIsMine() == 0){
			tiles.at(pos) -> setIsMine();
			c++;
		}
		else{
			;
		}
	}
}

vector<Point> MinesweeperWindow::adjacentPoints(Point xy) const {
	vector<Point> points;
	for (int di = -1; di <= 1; ++di) {
		for (int dj = -1; dj <= 1; ++dj) {
			if (di == 0 && dj == 0) {
				continue;
			}

			Point neighbour{ xy.x + di * cellSize,xy.y + dj * cellSize };
			if (inRange(neighbour)) {
				points.push_back(neighbour);
			}
		}
	}
	return points;
}

void MinesweeperWindow::openTile(Point xy) {
	if(at(xy) -> getState() == Cell::open){
		return;
	}
	else{
		at(xy) -> open();
		if(at(xy) -> getIsMine() == 0){
			win++;
			if(win == (height*width)-mines){
				loss = 1;
				std::cout << "Well done!" << std::endl;
			}
			at(xy) -> setAdjMines(countMines(adjacentPoints(xy)));
			for(int i = 0; i < adjacentPoints(xy).size(); i++){
				if(countMines(adjacentPoints(xy)) == 0 && at(adjacentPoints(xy).at(i)) -> getIsMine() == 0){
					openTile(adjacentPoints(xy).at(i));
					}
			}
		}
		else if(at(xy) -> getIsMine() == 1){
			loss = 1;
		}

	}
	return;
}

void MinesweeperWindow::flagTile(Point xy) {
	at(xy) -> flag();
}

//Kaller openTile ved venstreklikk og flagTile ved hoyreklikk
void MinesweeperWindow::cb_click() {
	if(loss == 0){

	Point xy{this->get_mouse_coordinates()};
	//std::cout << xy.x << " " << xy.y <<": " << xy.x / (cellSize) + (xy.y / cellSize) * width<<"\n";

	if (!inRange(xy)) {
		return;
	}
	if (this->is_left_mouse_button_down()) {
		openTile(xy);
	}
	else if(this->is_right_mouse_button_down()){
		flagTile(xy);
	}
	}
}

int MinesweeperWindow::countMines(vector<Point> points){
	int c = 0;
	for(int i = 0; i < points.size(); i++){
		if(at(points.at(i)) -> getIsMine() == 1){
			c++;
		}
		else{
			;
		}
	}
	return c;																					
}
