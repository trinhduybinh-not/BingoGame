#include "NumberBag.h"
#include <algorithm>
#include <random>
#include <cmath>
#include <iostream>

static std::mt19937 rng{ std::random_device{}() };

NumberBag::NumberBag() : n(0) {
    for (int i = 1; i <= 99; i++) so.push_back(i);
    trongSo.assign(99, 1.0);
    xao();
}

// ─────────────────────────────────────────────
//  apDungNhom — POLYMORPHISM:
//  Gọi cat->thuocNhom(x) → runtime dispatch
//  đến đúng lớp con (NguyenTo, Fibonacci, ...)
// ─────────────────────────────────────────────
void NumberBag::apDungNhom(const SoCategory* cat, double trongSoNhom) {
    if (!cat) return;
    for (int x = 1; x <= 99; x++)
        if (cat->thuocNhom(x))
            trongSo[x - 1] = std::max(0.01, trongSoNhom);
}

void NumberBag::resetTrongSo() {
    trongSo.assign(99, 1.0);
}

// ─────────────────────────────────────────────
//  Xáo có trọng số (Efraimidis-Spirakis)
// ─────────────────────────────────────────────
void NumberBag::xao() {
    std::uniform_real_distribution<double> dist(1e-9, 1.0);
    std::vector<std::pair<double, int>> pq;
    pq.reserve(99);
    for (int i = 0; i < 99; i++) {
        double u        = dist(rng);
        double priority = -std::log(u) / trongSo[i];
        pq.push_back({ priority, i + 1 });
    }
    std::sort(pq.begin(), pq.end());
    for (int i = 0; i < 99; i++) so[i] = pq[i].second;
    n = 0;
}

int NumberBag::bocso() {
    if (n >= (int)so.size()) {
        std::cout << "Tui so da het!\n";
        return -1;
    }
    return so[n++];
}

std::vector<int> NumberBag::sodaboc() {
    return std::vector<int>(so.begin(), so.begin() + n);
}

bool NumberBag::hetSo() const {
    return n >= (int)so.size();
}
