#pragma once
#include <vector>
#include <utility>
using namespace std;
class BingoCard;

// ══════════════════════════════════════════════════════
//  OOP: ABSTRACTION (lớp điều kiện thắng)
//
//  Giữ nguyên thiết kế của nhóm (concrete class),
//  chỉ đổi tham chiếu từ Bingocard → BingoCard.
// ══════════════════════════════════════════════════════
class WinCondition {
public:
    // Kiểm tra phiếu có thắng không
    bool Check(const BingoCard& card) const;

    // Trả về danh sách toạ độ các ô trên đường thắng (để hiển thị)
    vector<pair<int,int>> LayOThang(const BingoCard& card) const;
};
