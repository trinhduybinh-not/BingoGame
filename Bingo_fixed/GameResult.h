#pragma once
#include <vector>
#include <string>
using namespace std;
// ─────────────────────────────────────────────
//  DuLieuVan: dữ liệu của phiếu thắng trong 1 ván
//  Dùng cho Statistics heatmap/BCR (của nhóm)
// ─────────────────────────────────────────────
struct DuLieuVan {
    bool duongThang[5][5];  // ô nào nằm trên đường thắng
    int  bang[5][5];        // giá trị ô của phiếu thắng
    int  soLuot;            // số lần bốc trong ván
    bool daThang;           // có người thắng không
};

// ─────────────────────────────────────────────
//  GameResult: kết quả đầy đủ sau 1 ván chơi
//  Bao gồm cả DuLieuVan để Statistics xử lý
// ─────────────────────────────────────────────
struct GameResult {
    // ── Kết quả game ────────────────────────
    int              winnerCardId;       // -1 nếu không ai thắng
    string      winConditionName;   // "Hang ngang" hay "Cot doc"
    int              drawCount;          // tổng số lần bốc
    vector<int> sequence;           // thứ tự các số được bốc

    // ── Dữ liệu phiếu thắng (cho heatmap/BCR) ──
    DuLieuVan        duLieuVan;

    // ── Tài chính ───────────────────────────
    double           totalCollected;
    double           prizePaid;
    double           houseProfit;
};
