
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

#define IMHEXCOL(x)  IM_COL32((x >> 24) & 0xFF,(x >> 16) & 0xFF, (x >> 8) & 0xFF, 0xFF)

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

struct MetroCart {
    int capacity, max_capacity;
    float speed;
};

struct MetroStation {
    std::string name;
    int x, y;
    int shape;
};

struct MetroLine {
    std::string name;
    uint64_t color;
    std::vector<vec2> path_points;
    std::deque<MetroCart> carts;
};


class MetroGame {
public:
    void create();
    void begin();
    void frame();
    void inputFrame();

    void drawLine(const MetroLine& line);
    void drawStation(const MetroStation& station);
    void drawHUD();

    std::vector<MetroLine> lines;
    std::vector<MetroStation> stations;

    std::string name;
    unsigned texture_bg;

    float time;

    bool paused;

    struct {
        int selected_line;

        bool build_active;
    } input;

};


void MetroGame::create() {
    
}

void MetroGame::inputFrame() {
    ImGuiIO& io = ImGui::GetIO();

    if (io.MouseClicked[0]) {
        ImGui::Text("Mouse Down");

        if (input.build_active || true) {
            if (input.selected_line < lines.size())
            {
                float sx = Util::snapToGrid(io.MousePos.x);
                float sy = Util::snapToGrid(io.MousePos.y);
                lines[input.selected_line].path_points.push_back( vec2(sx, sy) );
            }
            input.build_active = false;
        }
        else {
            input.build_active = true;
        }
    }
}

void MetroGame::frame() {
    
    MetroGame::inputFrame();

    for (auto& line : lines) {
        drawLine(line);
    }

    for (auto& station : stations) {
        drawStation(station);
    }

    if (!paused)
        time += Util::dt();
}

void MetroGame::drawLine(const MetroLine& line) {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    for (size_t i = 1; i < line.path_points.size(); i++) {
        vec2 a = line.path_points[i-1];
        vec2 b = line.path_points[i];

        draw_list->AddLine(ImVec2(a.x, a.y), ImVec2(b.x, b.y),, 8.0f);
    }
}

void MetroGame::drawStation(const MetroStation& station) {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    draw_list->AddCircleFilled(ImVec2(station.x, station.y), 12.0f, IM_COL32(255, 255, 255, 255));

    draw_list->AddText(ImVec2(station.x, station.y + 16.f), IM_COL32(0,0,0,255), station.name.data());
}

void MetroGame::drawHUD() {
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    for (int i = 0; i < lines.size(); i++) {
        if (i == input.selected_line)
            draw_list->AddCircleFilled(ImVec2(100.f, 100.f), 50.f, IMHEXCOL(lines[i].color), 32);
        else
            draw_list->AddCircle(ImVec2(100.f, 100.f), 50.f, IMHEXCOL(lines[i].color), 32, 4.0f);
    }
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

    if (ImGui::Button("Add Station")) {
        MetroStation station;
        station.x = 200 + game.stations.size()*30;
        station.y = 200 + game.stations.size()*30;
        station.shape = 0;
        station.name.resize(256);
        game.stations.push_back(station);
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

    for (auto& station : game.stations) {
        if ( ImGui::CollapsingHeader( ("Station " + std::to_string((uint64_t)&station)).data() ) ) {
            ImGui::InputText("name", station.name.data(), 256);

            ImGui::DragInt("x", &station.x);
            ImGui::DragInt("y", &station.y);
            ImGui::DragInt("shape", &station.shape);
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
    game.drawHUD();

    MetroDEBUG();

}