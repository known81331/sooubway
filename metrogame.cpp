
#include <vector>
#include <span>
#include <deque>
#include <utility>
#include <cstdint>
#include <string>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <chrono>

#include "util.hpp"

void TexWrap_init() ;
unsigned TexWrap_createUncompressedTexture(const std::string &filePath);


struct MetroStation {
    int x, y;

    int shape;
};

struct MetroLine {
    std::string name;
    uint64_t color;
    std::vector<MetroStation&> enrouted_stations;
};


class MetroGame {
public:
    void create();
    void begin();
    void frame();

    void drawLine(const MetroLine& line);
    void drawStation(const MetroStation& station);

    std::vector<MetroLine> lines;
    std::vector<MetroStation> stations;

    float time;

    bool paused;
};


void MetroGame::create() {
    
}

void MetroGame::frame() {
    
    if (!paused)
        time += Util::dt();
}

void MetroGame::drawLine(const MetroLine& line) {
    
}

void MetroGame::drawStation(const MetroStation& station) {
    
}


MetroGame game = {};

void MetroDEBUG() {

}

void BrowserController_render() {

    static bool init = false;
    if (!init) {
        TexWrap_init();
        game.create();
        init = true;
    }

    game.frame();

    MetroDEBUG();

}