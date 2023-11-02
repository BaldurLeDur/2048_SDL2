#include "Cell.h"

std::map<int, SDL_Color> Cell::colorMap = {
        {0, {255, 255, 255, 255}},
        {2, {255, 255, 179, 255}},
        {4, {255, 204, 102, 255}},
        {8, {255, 204, 102, 255}},
        {16, {255, 102, 0, 255}},
        {32, {255, 80, 80, 255}},
        {64, {255, 51, 0, 255}},
        {128, {255, 0, 0, 255}},
        {256, {204, 0, 0, 255}},
        {512, {204, 0, 102, 255}},
        {1024, {255, 0, 102, 255}},
        {2048, {204, 0, 255, 255}},
};

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