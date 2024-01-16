#include "Map.hpp"
#include "f_stack.hpp"
#include "p_queue.hpp"
#include <fstream>
#include <iostream>

#define DEBUG 0

// Class to save pathfinding information
class Content {
public:
  std::pair<int, int> position; // position on the map (x & y axis)
  int weight;                   // the actual cost (how much to reach this tile)
  int prediction;               // prediction to go to the end
                                // = weight + distance min to reach the end
  std::pair<int, int> parent;   // the tile before this one ((-1,-1) for start)

  // Constructor
  Content(std::pair<int, int> p = {-1, -1}, int w = 0, int h = 0,
          std::pair<int, int> parent = {-1, -1})
      : position(p), weight(w), prediction(h), parent(parent){};

  // operator to compare (we compare the weight)
  bool operator<(const Content &other) const { return weight < other.weight; }
  bool operator<=(const Content &other) const { return weight <= other.weight; }
  bool operator==(const Content &other) const {
    return position == other.position;
  }
};

// Functor to compare two content on our priority_queue
// For the priority_queue, we want to get the tile that look the most promising
// So, the prediction
class comparator {
public:
  bool operator()(const Content &c1, const Content &c2) const {
    return c2.prediction < c1.prediction;
  }
};

// Function to obtain the distance between to tile
int dist(std::pair<int, int> start, std::pair<int, int> end) {
  return std::abs(start.first - end.first) +
         std::abs(start.second - end.second);
}

void retracePath(Map map, f_stack<Content> closedList, Content lastTile,
                 std::pair<int, int> start, int pathColor) {

  std::pair<int, int> saveLastTilePos = lastTile.position;

  // We try to find the next tile from our path
  // It's the parent of our our lastTile
  std::pair<int, int> parent = lastTile.parent;

  // Until we haven't reached the start tile
  while (parent != start) {

    // We search the next tile inside our closedList stack
    do {
      lastTile = closedList.top();
      closedList.pop();

      // This color is just to highlight the tile looked by A*
      map.changeTile(lastTile.position, 2);
    } while (lastTile.position != parent);

    // We find the parent tile
    // so we redo this, with the parent of this new tile
    map.changeTile(lastTile.position, pathColor);
    parent = lastTile.parent;
  }

  // Color the start tile
  map.changeTile(parent, pathColor);

  // Color the last tile of our path
  // We need to save it in the case of the end is not reachable from the start
  // In this case, the lastTile is also contains inside the closedList, so it
  // will be rewrite with the "color" 2;
  map.changeTile(saveLastTilePos, pathColor);
}

// The A* Algorithm
int A(Map &map, std::pair<int, int> start, std::pair<int, int> end) {

  bool find = false;

  // List of tile we have to analyse
  p_queue<Content, comparator, std::vector<Content>> openList;

  // We place the start tile first
  openList.push(Content{start, 0, dist(start, end), {-1, -1}});

  // Stack of tile we had analyse
  // This stack avoid the algorithm to execute a second time a tile
  f_stack<Content> closedList;

  // The closest tiles we find from the end
  // This variable will be useful if the end tile is not reachable from the
  // start
  Content closest{start, 0, dist(start, end), {-1, -1}};

  // function to analyse adjacent tiles
  // actual is the tile to analyse
  // ngh_pos is the tile to analyse
  auto helloNeighbor = [&](Content &parent, std::pair<int, int> ngh_pos) {
    std::pair<int, int> parent_pos = parent.position;

    // Look if the tiles is inside the map or empty
    if (ngh_pos.second < map.getWidth() - 1 && ngh_pos.second > 0 &&
        ngh_pos.first < map.getHeight() - 1 && ngh_pos.first > 0 &&
        map.getTile(ngh_pos) != 1) {

      // Create the content associate to this tiles
      Content neighbor(ngh_pos, parent.weight + 1,
                       parent.weight + 1 + dist(ngh_pos, end), parent_pos);

      // If this tiles is interesting, we save it.
      if (!(closedList.find(neighbor) || openList.find(neighbor))) {
        openList.push(neighbor);

        if (DEBUG) {
          std::cout << "add (" << neighbor.position.first << ";"
                    << neighbor.position.second << ")" << std::endl
                    << "weight " << neighbor.weight << std::endl
                    << "prediction " << neighbor.prediction << std::endl
                    << std::endl;
          map.changeTile(neighbor.position, 2);
          map.printMap();
        }

        // If it's the best actual tiles , we save it inside the closest
        // variable
        if (dist(end, neighbor.position) < closest.prediction) {
          closest = {neighbor.position, neighbor.weight,
                     dist(end, neighbor.position), neighbor.parent};
        }
      }
    }
  };

  // While we have tiles to analyse
  while (!find && !openList.empty()) {

    // We take the most promising tile
    Content actual = openList.top();
    // and remove it
    openList.pop();

    if (DEBUG) {
      std::cout << "use (" << actual.position.first << ";"
                << actual.position.second << ")" << std::endl
                << "weight " << actual.weight << std::endl
                << "prediction " << actual.prediction << std::endl
                << std::endl;

      map.changeTile(actual.position, 3);
    }

    // If we find the objectif
    if (actual.position == end) {
      closest = actual;
      find = true;
    }
    // Else, we continue our search
    else {
      // for each near nodes
      helloNeighbor(actual,
                    {actual.position.first, actual.position.second - 1});
      helloNeighbor(actual,
                    {actual.position.first, actual.position.second + 1});
      helloNeighbor(actual,
                    {actual.position.first - 1, actual.position.second});
      helloNeighbor(actual,
                    {actual.position.first + 1, actual.position.second});
      closedList.push(actual);
    }
  }

  // In this case, we can't go to the end tile, so we choose to follow the
  // closest tile instead
  retracePath(map, closedList, closest, start, find ? 3 : 4);
  return 1;
}

int main() {
  Map map("test.txt");
  A(map, std::pair<int, int>(12, 12), std::pair<int, int>(5, 6));
  map.printMap();
  return 0;
}
