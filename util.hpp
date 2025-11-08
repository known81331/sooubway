#pragma once

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

namespace Util {
template<typename T>
inline T lerp(const T& a, const T& b, float c) {
    return (1.f - c) * a + b*c;
}

template<typename T>
inline T lerpv2(const T& a, const T& b, float c) {
    return (T(1.f, 1.f) - T(c,c) ) * a + b*T(c,c);
}


template<typename T>
inline T rotate(const T& a, float r) {
    float c = cosf(r*(3.14159265358979323846f/180.f));
    float s = sinf(r*(3.14159265358979323846f/180.f));
    return T(
        a.x * c - a.y * s,
        a.x * s + a.y * c
    );
}

inline float dt() {
    static auto last = std::chrono::high_resolution_clock::now();
    auto now = std::chrono::high_resolution_clock::now();
    float delta = std::chrono::duration<float>(now - last).count();
    last = now;
    return delta;
}


}
