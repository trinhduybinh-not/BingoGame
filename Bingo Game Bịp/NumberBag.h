#pragma once
#include <vector>
#include "SoCategory.h"


class NumberBag {
private:
    std::vector<int>    so;
    std::vector<double> trongSo;  // trongSo[i] = trọng số số (i+1)
    int                 n;

public:
    NumberBag();

    // POLYMORPHISM: nhận SoCategory* → tự gọi thuocNhom()
    void apDungNhom(const SoCategory* cat, double trongSoNhom);

    void             resetTrongSo();
    void             xao();
    int              bocso();
    std::vector<int> sodaboc();
    bool             hetSo() const;
};
