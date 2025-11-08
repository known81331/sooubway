
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
#include <queue>

#define IMGUI_DEFINE_MATH_OPERATORS

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"


#include "util.hpp"

void TexWrap_init() ;
unsigned TexWrap_createUncompressedTexture(const std::string &filePath);

struct vec2 {
    vec2() = default;
    ~vec2() = default;
    vec2(float _x, float _y) : x(_x), y(_y) {};
    float x, y;
};

struct vec4 {
    float x, y, z, w;
};

struct MetroStation {
    int x, y;

    int shape;
};


struct MetroLine {
    std::string name;
    uint64_t color;
    std::vector<vec2> path_points;
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
    
    for (auto& line : lines) {
        drawLine(line);
    }

    if (!paused)
        time += Util::dt();
}

void MetroGame::drawLine(const MetroLine& line) {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    for (size_t i = 1; i < line.path_points.size(); i++) {
        vec2 a = line.path_points[i-1];
        vec2 b = line.path_points[i];

        draw_list->AddLine(ImVec2(a.x, a.y), ImVec2(b.x, b.y), IM_COL32((line.color >> 24) & 0xFF,(line.color >> 16) & 0xFF, (line.color >> 8) & 0xFF, 0xFF), 8.0f);
    }
}

void MetroGame::drawStation(const MetroStation& station) {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
}


MetroGame game = {};

void MetroDEBUG() {

    ImGui::Begin("METRO DEBUG");

    if ( ImGui::Button("Add Line") ) {
        MetroLine line;
        line.name = "Line " + std::to_string(game.lines.size()+1);
        line.color = 0xFF0000FF >> (game.lines.size()*8);
        line.path_points.push_back(vec2(100.f + game.lines.size()*50.f, 100.f));
        line.path_points.push_back(vec2(300.f + game.lines.size()*50.f, 300.f));
        game.lines.push_back(line);
    }

    for (auto& line : game.lines) {
        if ( ImGui::CollapsingHeader(line.name.data()) ) {
            int i = 0;
            for (auto& point : line.path_points) {
                ImGui::DragFloat2( ("Point " + std::to_string(i)).data(), &point.x);
                i++;
            }
            if ( ImGui::Button("Add Point") ) {
                line.path_points.push_back(vec2(400.f, 400.f));
            }
        }
    }

    ImGui::End();
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