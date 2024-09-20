#include "Tile.h"
#include <map>

// For aa sette labelfarge i henhold til hvor mange miner som er rundt
const std::map<int, TDT4102::Color> minesToColor{{0, TDT4102::Color::white},
												{1, TDT4102::Color::blue},
												{2, TDT4102::Color::red},
												{3, TDT4102::Color::dark_green},
												{4, TDT4102::Color::dark_magenta},
												{5, TDT4102::Color::dark_blue},
												{6, TDT4102::Color::dark_cyan},
												{7, TDT4102::Color::dark_red},
												{8, TDT4102::Color::gold}};


// For aa sette Tilelabel i henhold til state
const std::map<Cell, std::string> cellToSymbol{{Cell::closed, ""},
									 			{Cell::open, ""},
									 	  		{Cell::flagged, "|>"}};

Tile::Tile(TDT4102::Point pos, int size) : 
	Button({pos.x, pos.y}, 1.5*size, size, "") {
		setButtonColor(TDT4102::Color::silver);
	}

bool Tile::getIsMine(){
	return isMine;
}


bool Tile::setIsMine(){
	isMine = true;
	return isMine;
}

void Tile::open(){
	if(getState() == Cell::open or getState() == Cell::flagged){
		;
	}
	else if(getState() == Cell::closed){
		if(getIsMine() == 1){
			set_label("X");
			set_label_color(minesToColor.at(2));
		}
		else if(getIsMine() == 0){
			set_label("O");
			set_label_color(TDT4102::Color::white);
			state = Cell::open;
		}
	}
}

void Tile::flag(){
	if(getState() == Cell::flagged){
		state = Cell::closed;
		set_label(cellToSymbol.at(Cell::closed));
	}
	else{
		state = Cell::flagged;
		set_label(cellToSymbol.at(Cell::flagged));
		set_label_color(TDT4102::Color::black);

	}

}

void Tile::setAdjMines(int n){
	set_label(std::to_string(n));
	set_label_color(minesToColor.at(n));
}
