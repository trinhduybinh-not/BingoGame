#include "SoCategory.h"
#include <cmath>

// ─────────────────────────────────────────────
//  Hàm chung: lấy tất cả số 1–99 thuộc nhóm
// ─────────────────────────────────────────────
std::vector<int> SoCategory::laySoThuocNhom() const {
    std::vector<int> ds;
    for (int x = 1; x <= 99; x++)
        if (thuocNhom(x)) ds.push_back(x);
    return ds;
}

// ─────────────────────────────────────────────
//  SoNguyenTo
// ─────────────────────────────────────────────
bool SoNguyenTo::thuocNhom(int x) const {
    if (x < 2) return false;
    for (int i = 2; i * i <= x; i++)
        if (x % i == 0) return false;
    return true;
}

// ─────────────────────────────────────────────
//  SoDoiXung (palindrome trong 1–99)
//  1 chữ số (1–9): luôn đối xứng
//  2 chữ số: chục == đơn vị (11, 22, ..., 99)
// ─────────────────────────────────────────────
bool SoDoiXung::thuocNhom(int x) const {
    if (x < 10) return true;
    return (x / 10) == (x % 10);
}

// ─────────────────────────────────────────────
//  SoFibonacci
//  x là Fibonacci ⟺ 5x²+4 hoặc 5x²-4 là số chính phương
// ─────────────────────────────────────────────
bool SoFibonacci::thuocNhom(int x) const {
    auto isSquare = [](long long n) -> bool {
        if (n < 0) return false;
        long long s = (long long)std::sqrt((double)n);
        return s * s == n || (s + 1) * (s + 1) == n;
    };
    return isSquare(5LL * x * x + 4) || isSquare(5LL * x * x - 4);
}

// ─────────────────────────────────────────────
//  SoChinhPhuong
// ─────────────────────────────────────────────
bool SoChinhPhuong::thuocNhom(int x) const {
    int s = (int)std::sqrt((double)x);
    return s * s == x;
}
