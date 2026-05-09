#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "GameResult.h"
#include "PrizeCalculator.h"
using namespace std;

class Statistics {
private:
    // ── Chỉ số 1: Heatmap đường thắng ───────────
    int heatmap[5][5];

    // ── Chỉ số 2: Số may mắn ────────────────────
    int soLanThang[100];

    // ── Chỉ số 3: BCR ───────────────────────────
    int soLanTrenDuongThang[100];
    int soLanXuatHien[100];

    // ── Chỉ số 4: Thống kê vị trí X ─────────────
    // xTongPhieu[i][j]  : tổng số phiếu có X tại (i,j) qua tất cả ván
    // xSoLanThang[i][j] : trong đó bao nhiêu phiếu thắng
    int xTongPhieu[5][5];
    int xSoLanThang[5][5];

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
    vector<double>   loiNhuanMoiVan;

    // ── Điều kiện thắng ─────────────────────────
    map<string,int> winConditionCount;

    // ── Helpers ─────────────────────────────────
    void SapXep(int idx[], float val[], int n) const;
    void SapXep(int idx[], int   val[], int n) const;
    void inThanh(int val, int maxVal, int width = 20) const;
    void inKeDuong(char c = '-', int w = 55)          const;

public:
    Statistics(int numCards, const PrizeCalculator& prize);
    void Reset();
    void record(const GameResult& result);

    // ── Xuất chỉ số nhóm ────────────────────────
    void XuatHeatmap()                    const;
    void XuatSoMayMan(int top = 5)        const;
    void XuatBCR(int top = 5)             const;

    // ── Xuất thống kê vị trí X ──────────────────
    void XuatThongKeX()                   const; // ← MỚI

    // ── Xuất tài chính ──────────────────────────
    void printFinancialReport()           const;
    void printFrequencyTable()            const;

    // ── Xuất file CSV ───────────────────────────
    void exportFrequencyCSV(const string& filename) const;
    void exportProfitCSV   (const string& filename) const;

    // ── Tổng hợp ────────────────────────────────
    void printSummary()                   const;
};
