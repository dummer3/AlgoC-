#ifndef MAP_HPP
#define MAP_HPP

#include <fstream>
#include <iomanip>
#include <iostream>

// Definition of ascii color
const std::string COLOR_BACK_DEF = "\x1b[m";
const std::string COLOR_BACK_BLACK = "\x1b[40m";
const std::string COLOR_BACK_RED = "\x1b[41m";
const std::string COLOR_BACK_GREEN = "\x1b[42m";
const std::string COLOR_BACK_YELLOW = "\x1b[43m";
const std::string COLOR_BACK_BLUE = "\x1b[44m";
const std::string COLOR_BACK_MAGENTA = "\x1b[45m";
const std::string COLOR_BACK_CYAN = "\x1b[46m";
const std::string COLOR_BACK_WHITE = "\x1b[47m";

const std::string COLOR_DEF = "\x1b[m";
const std::string COLOR_BLACK = "\x1b[30m";
const std::string COLOR_RED = "\x1b[31m";
const std::string COLOR_GREEN = "\x1b[32m";
const std::string COLOR_YELLOW = "\x1b[33m";
const std::string COLOR_BLUE = "\x1b[34m";
const std::string COLOR_MAGENTA = "\x1b[35m";
const std::string COLOR_CYAN = "\x1b[36m";
const std::string COLOR_WHITE = "\x1b[37m";

// Simple class to represent our map;
class Map {

private:
  int width;
  int height;
  int **tiles; // Our map representation

public:
  // Constructor, from a file
  Map(std::string file);

  // print with color
  void printMap() const;

  // print only the number
  void print() const;

  // simple getter and setter
  int getWidth() const { return width; }
  int getHeight() const { return height; }
  int getTile(std::pair<int, int> pos) const {
    return tiles[pos.first][pos.second];
  }
  void changeTile(std::pair<int, int> pos, int value) {
    tiles[pos.first][pos.second] = value;
  }
};

#endif
