#include "Cell.h"

std::map<int, std::string> Cell::imageMap = {
    {0, "../img/TileZero.bmp"},
    {2, "../img/TileTwo.bmp"},
    {4, "../img/TileFour.bmp"},
    {8, "../img/TileEight.bmp"},
    {16, "../img/TileSixteen.bmp"},
    {32, "../img/TileThirtyTwo.bmp"},
    {64, "../img/TileSixtyFour.bmp"},
    {128, "../img/TileOneHundred.bmp"},
    {256, "../img/TileTwoHundred.bmp"},
    {512, "../img/TileFiveHundred.bmp"},
    {1024, "../img/TileOneHundred.bmp"},
    {2048, "../img/TileTwoHundred.bmp"},
};

void Cell::display() const {
    std::cout << value << "\t";
}

int Cell::getValue() const {
    return value;
}

void Cell::setValue(int val) {
    value = val;
}

bool Cell::isEmpty() const {
    return value == 0;
}