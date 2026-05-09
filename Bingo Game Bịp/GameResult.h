#pragma once
#include <vector>
#include <string>
using namespace std;

// ─────────────────────────────────────────────
//  DuLieuVan: dữ liệu phiếu thắng trong 1 ván
// ─────────────────────────────────────────────
struct DuLieuVan {
    bool duongThang[5][5];
    int  bang[5][5];
    int  soLuot;
    bool daThang;
};

// ─────────────────────────────────────────────
//  ViTriX: vị trí ô X và kết quả của 1 phiếu
//  Dùng để thống kê: X ở đâu thì tỉ lệ thắng thấp nhất
// ─────────────────────────────────────────────
struct ViTriX {
    int  hang;      // hàng của X (0-4)
    int  cot;       // cột của X (0-4)
    bool daThang;   // phiếu này có thắng không
};

// ─────────────────────────────────────────────
//  GameResult: kết quả đầy đủ sau 1 ván chơi
// ─────────────────────────────────────────────
struct GameResult {
    // ── Kết quả game ────────────────────────
    int              winnerCardId;
    string           winConditionName;
    int              drawCount;
    vector<int>      sequence;

    // ── Dữ liệu phiếu thắng (heatmap/BCR) ──
    DuLieuVan        duLieuVan;

    // ── Vị trí X của TẤT CẢ phiếu trong ván ──
    // Dùng để tính: X ở (i,j) → tỉ lệ thắng bao nhiêu?
    vector<ViTriX>   viTriXMoiPhieu;

    // ── Tài chính ───────────────────────────
    double           totalCollected;
    double           prizePaid;
    double           houseProfit;
};
