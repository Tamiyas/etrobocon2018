#ifndef __BLOCK_AREA__
#define __BLOCK_AREA__

#include <cstdint>
#include <list>
#include <map>
#include <memory>

enum struct GameColor { UNKNOWN, RED, YELLOW, BLUE, GREEN };

class ColorBlock {
 public:
  ColorBlock(GameColor color_) : color(color_) {}
  GameColor color = GameColor::UNKNOWN;
};

class ColorBlockPlace {
 public:
  ColorBlockPlace(GameColor color_, std::int8_t place_cord_)
    : color(color_), place_cord(place_cord_)
  {
  }
  std::shared_ptr<ColorBlock> block;
  std::map<std::string, std::shared_ptr<ColorBlockPlace>> black_line;
  GameColor getColor() { return color; }
  std::int8_t getPlaceCord() { return place_cord; }

 private:
  GameColor color = GameColor::UNKNOWN;
  std::int8_t place_cord = -1;
};

class BlockArea {
 public:
  // void calculateFirstCord();

 private:
  std::unique_ptr<std::weak_ptr<ColorBlockPlace>> colorBlockPlaces;
  std::int16_t first_cord;
  std::list<ColorBlockPlace> waitTransportBlock;
  std::int8_t finishColorBlockNum = 0;
};

#endif