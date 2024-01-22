#include "Map.hpp"

Map::Map(std::string file) {

  std::fstream my_file;
  my_file.open(file, std::ios::in);

  if (my_file) {
    my_file >> height;
    height += 2; // we add 2 more lines for the border (top and bottom)
    my_file >> width;
    width += 2; // same

    // creation of the map
    tiles = new int *[height];

    // We fill the content of the tile
    for (int i = 1; i < height - 1; i++) {
      tiles[i] = new int[width];

      // at the same time, we place the left and right border
      tiles[i][0] = 1;
      tiles[i][width - 1] = 1;

      for (int j = 1; j < width - 1; j++)
        my_file >> tiles[i][j];
    }

    // we finish with the top and bottom border
    tiles[0] = new int[width];
    tiles[height - 1] = new int[width];
    for (int j = 0; j < width; j++) {
      tiles[0][j] = 1;
      tiles[height - 1][j] = 1;
    }
  }
}

void Map::printMap() const {

  std::cout << "   ";
  for (int i = 0; i < width; i++)
    std::cout << std::setw(3) << i;
  std::cout << std::endl;

  // For every tile
  for (int y = 0; y < height; y++) {
    std::cout << std::setw(3) << y << " ";
    for (int x = 0; x < width; x++) {

      // Choose the correct background colorBack
      std::string colorBack;
      int tile = tiles[y][x];

      switch (tile) {
      case 0:
        colorBack = COLOR_BACK_BLACK;
        break;
      case 1:
        colorBack = COLOR_BACK_WHITE;
        break;
      case 2:
        colorBack = COLOR_BACK_CYAN;
        break;
      case 3:
        colorBack = COLOR_BACK_BLUE;
        break;
      default:
        colorBack = COLOR_BACK_RED;
      }
      // Print the tile!
      std::cout << colorBack << "   " << COLOR_BACK_DEF;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void Map::print() const {

  // For every tile
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {

      // Print the tile!
      std::cout << "|" << tiles[x][y] << "|";
    }
    std::cout << std::endl;
  }
  // Place the map on the terminal correctly
  std::cout << std::endl;
}
