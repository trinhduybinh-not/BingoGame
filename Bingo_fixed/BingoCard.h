#pragma once
#include <vector>
using namespace std;
class WinCondition;

// ══════════════════════════════════════════════════════
//  OOP: ENCAPSULATION
//  (Đổi tên từ Bingocard → BingoCard cho nhất quán)
//
//  Bảng 5×5: 24 số ngẫu nhiên (1–99) + 1 ô đặc biệt X
//  Ô X không thể đánh dấu và hàng/cột chứa X
//  không được tính là Bingo.
// ══════════════════════════════════════════════════════
class BingoCard {
private:
    int              bang[5][5];        // -1 = ô X, >0 = số
    bool             DaDanhDau[5][5];   // đã được đánh dấu chưa
    int              MaSo;
    int              HangDB, CotDB;     // toạ độ ô đặc biệt X
    int              HangTrong, CotTrong;
    vector<int> DSS;

public:
    explicit BingoCard(int maSo = 0);

    // ── Getters ─────────────────────────────────────
    int  LayMaSo()                     const { return MaSo; }
    int  LaySo(int hang, int cot)      const { return bang[hang][cot]; }
    bool DaDanhDauChua(int hang, int cot) const { return DaDanhDau[hang][cot]; }
    int  LayHangDacBiet()              const { return HangDB; }
    int  LayCotDacBiet()               const { return CotDB; }

    // ── Hành vi ─────────────────────────────────────
    void TaoBang();
    bool DanhDau(int so);
    bool KiemTraThang(const WinCondition& dk) const;
    void HienThi(const WinCondition& dk)       const;
    void DatLai();
};
