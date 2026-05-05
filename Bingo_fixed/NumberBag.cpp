#include "NumberBag.h"
#include <algorithm>
#include <random>
#include <iostream>
using namespace std;
NumberBag::NumberBag() : n(0) {
    for (int i = 1; i <= 99; ++i) so.push_back(i);
    xao();
}

void NumberBag::xao() {
    random_device rd;
    mt19937 g(rd());
    shuffle(so.begin(), so.end(), g);
    n = 0;
}

int NumberBag::bocso() {
    // Fix lỗi: so.size() là unsigned, n là int → ép kiểu để so sánh đúng
    if (n >= static_cast<int>(so.size())) {
        cout << "Tui so da het!\n";
        return -1;
    }
    return so[n++];
}

vector<int> NumberBag::sodaboc() {
    return vector<int>(so.begin(), so.begin() + n);
}

bool NumberBag::hetSo() const {
    return n >= static_cast<int>(so.size());
}
