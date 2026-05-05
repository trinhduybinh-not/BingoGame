#include "BingoGame.h"
#include <iostream>
using namespace std;
BingoGame::BingoGame(int soPhieu) : soPhieu(soPhieu) {
    for (int i = 0; i < soPhieu; i++)
        phieu.emplace_back(i);
}

GameResult BingoGame::play(bool verbose) {
    // ── Chuẩn bị ────────────────────────────────────
    tui.xao();
    for (auto& p : phieu) p.DatLai();

    GameResult result;
    result.winnerCardId = -1;
    result.drawCount    = 0;
    result.duLieuVan.daThang = false;
    result.duLieuVan.soLuot  = 0;

    // Khởi tạo DuLieuVan
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++) {
            result.duLieuVan.duongThang[i][j] = false;
            result.duLieuVan.bang[i][j]        = 0;
        }

    // ── Vòng bốc số ─────────────────────────────────
    while (!tui.hetSo()) {
        int so = tui.bocso();
        if (so == -1) break;

        result.sequence.push_back(so);
        result.drawCount++;

        if (verbose)
            std::cout << "  Lan " << result.drawCount
                      << " boc duoc so: " << so << "\n";

        for (auto& p : phieu) {
            p.DanhDau(so);

            if (p.KiemTraThang(dieuKien)) {
                result.winnerCardId = p.LayMaSo();
                result.duLieuVan.daThang = true;
                result.duLieuVan.soLuot  = result.drawCount;

                // Xác định đường thắng và ghi lại grid của phiếu thắng
                auto oThang = dieuKien.LayOThang(p);
                for (int i = 0; i < 5; i++)
                    for (int j = 0; j < 5; j++) {
                        result.duLieuVan.bang[i][j] = p.LaySo(i, j);
                        // Kiểm tra ô (i,j) có trong danh sách đường thắng không
                        for (auto& ot : oThang)
                            if (ot.first == i && ot.second == j)
                                result.duLieuVan.duongThang[i][j] = true;
                    }

                // Ghi tên điều kiện thắng (hàng hay cột)
                // Kiểm tra: nếu tất cả ô thắng cùng 1 hàng → ngang, ngược lại → dọc
                if (!oThang.empty()) {
                    int hang0 = oThang[0].first;
                    bool cungHang = true;
                    for (auto& ot : oThang)
                        if (ot.first != hang0) { cungHang = false; break; }
                    result.winConditionName = cungHang ? "Hang ngang (5 o)" : "Cot doc (5 o)";
                }

                if (verbose) {
                    std::cout << "\n  >>> BINGO! Phieu #" << p.LayMaSo()
                              << " thang sau " << result.drawCount << " lan boc! <<<\n";
                    p.HienThi(dieuKien);
                }
                return result;
            }
        }
    }
    return result; // không ai thắng
}
