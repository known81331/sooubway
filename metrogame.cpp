
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

void TexWrap_init() ;
unsigned TexWrap_createUncompressedTexture(const std::string &filePath);

void BrowserController_render() {

    static bool init = false;
    if (!init) {
        TexWrap_init();
        init = true;
    }

}