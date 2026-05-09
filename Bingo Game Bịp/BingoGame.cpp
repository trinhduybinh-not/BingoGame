#include "BingoGame.h"
#include <iostream>
using namespace std;

BingoGame::BingoGame(int soPhieu) : soPhieu(soPhieu) {
    for (int i = 0; i < soPhieu; i++)
        phieu.emplace_back(i);
}

GameResult BingoGame::play(bool verbose) {
    tui.xao();
    for (auto& p : phieu) p.DatLai();

    GameResult result;
    result.winnerCardId      = -1;
    result.drawCount         = 0;
    result.duLieuVan.daThang = false;
    result.duLieuVan.soLuot  = 0;

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            result.duLieuVan.duongThang[i][j] = false;
            result.duLieuVan.bang[i][j]        = 0;
        }

    // ── Ghi vị trí X của từng phiếu ngay từ đầu ──────
    result.viTriXMoiPhieu.clear();
    for (auto& p : phieu) {
        ViTriX vx;
        vx.hang    = p.LayHangDacBiet();
        vx.cot     = p.LayCotDacBiet();
        vx.daThang = false;  // cập nhật sau khi biết kết quả
        result.viTriXMoiPhieu.push_back(vx);
    }

    // ── Vòng bốc số ───────────────────────────────────
    while (!tui.hetSo()) {
        int so = tui.bocso();
        if (so == -1) break;

        result.sequence.push_back(so);
        result.drawCount++;

        if (verbose)
            cout << "  Lan " << result.drawCount << " boc so: " << so << "\n";

        for (auto& p : phieu) {
            p.DanhDau(so);

            if (p.KiemTraThang(dieuKien)) {
                result.winnerCardId = p.LayMaSo();
                result.duLieuVan.daThang = true;
                result.duLieuVan.soLuot  = result.drawCount;

                // Đánh dấu phiếu thắng trong viTriXMoiPhieu
                result.viTriXMoiPhieu[p.LayMaSo()].daThang = true;

                auto oThang = dieuKien.LayOThang(p);
                for (int i = 0; i < 5; i++)
                    for (int j = 0; j < 5; j++) {
                        result.duLieuVan.bang[i][j] = p.LaySo(i, j);
                        for (auto& ot : oThang)
                            if (ot.first == i && ot.second == j)
                                result.duLieuVan.duongThang[i][j] = true;
                    }

                if (!oThang.empty()) {
                    int hang0     = oThang[0].first;
                    bool cungHang = true;
                    for (auto& ot : oThang)
                        if (ot.first != hang0) { cungHang = false; break; }
                    result.winConditionName = cungHang
                        ? "Hang ngang (5 o)" : "Cot doc (5 o)";
                }

                if (verbose) {
                    cout << "\n  >>> BINGO! Phieu #" << p.LayMaSo()
                         << " thang sau " << result.drawCount << " lan! <<<\n";
                    p.HienThi(dieuKien);
                }
                return result;
            }
        }
    }
    return result;
}
