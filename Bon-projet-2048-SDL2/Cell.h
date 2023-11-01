class Cell {
private:
	int value;

public:
	SDL_Color color;

	static std::map<int, SDL_Color> colorMap;

	static std::map<int, std::string> imageMap;

	Cell() : value(0), color({ 255, 255, 255, 255 }) {}

	void display() const;

	int getValue() const;

	void setValue(int val);

	bool isEmpty() const;
};