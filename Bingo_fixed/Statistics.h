#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include "GameResult.h"
#include "PrizeCalculator.h"
using namespace std;
// ══════════════════════════════════════════════════════
//  OOP: ENCAPSULATION
//
//  Statistics tổng hợp 3 chỉ số của nhóm
//  + báo cáo tài chính nhà cái.
//
//  Fix lỗi gốc:
//  - Bỏ "using namespace std" khỏi header
//  - Chuyển data thành private (đúng Encapsulation)
//  - Thêm record(GameResult&) để Simulator gọi được
// ══════════════════════════════════════════════════════
class Statistics {
private:
    // ── Chỉ số 1: Heatmap ───────────────────────
    int heatmap[5][5];         // ô nào hay nằm trên đường thắng

    // ── Chỉ số 2: Số may mắn ────────────────────
    int soLanThang[100];       // số nào hay xuất hiện ở ván thắng

    // ── Chỉ số 3: BCR ───────────────────────────
    int soLanTrenDuongThang[100];
    int soLanXuatHien[100];

    // ── Thống kê chung ──────────────────────────
    int tongSoVan;
    int tongSoLuot;
    int soVanCoNguoiThang;
    int numCards;

    // ── Tần suất số 1–99 ────────────────────────
    map<int,int> freq;

    // ── Tài chính ───────────────────────────────
    PrizeCalculator  prize;
    double           tongThu;
    double           tongThuong;
    double           tongLoiNhuan;
    double           loiNhuanMin;
    double           loiNhuanMax;
    vector<double> loiNhuanMoiVan;

    // ── Điều kiện thắng ─────────────────────────
    map<string,int> winConditionCount;

    // ── Helpers ─────────────────────────────────
    void SapXep(int idx[], float  val[], int n) const;
    void SapXep(int idx[], int    val[], int n) const;
    void inThanh(int val, int maxVal, int width = 20) const;
    void inKeDuong(char c = '-', int w = 55)          const;

public:
    Statistics(int numCards, const PrizeCalculator& prize);

    void Reset();

    // Nhận kết quả 1 ván (gọi từ Simulator)
    void record(const GameResult& result);

    // ── Xuất chỉ số nhóm ────────────────────────
    void XuatHeatmap()                                   const;
    void XuatSoMayMan(int soLuongTop = 5)               const;
    void XuatBCR(int soLuongTop = 5)                    const;

    // ── Xuất tài chính ──────────────────────────
    void printFinancialReport()                          const;

    // ── Xuất tần suất (1–99) ────────────────────
    void printFrequencyTable()                           const;

    // ── Tổng hợp tất cả ─────────────────────────
    void printSummary()                                  const;
};
