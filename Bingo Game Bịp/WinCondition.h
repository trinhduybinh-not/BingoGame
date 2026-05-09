#pragma once
#include <vector>
#include <utility>
using namespace std;
class BingoCard;

class WinCondition {
public:
    // Kiểm tra phiếu có thắng không
    bool Check(const BingoCard& card) const;

    // Trả về danh sách toạ độ các ô trên đường thắng (để hiển thị)
    vector<pair<int,int>> LayOThang(const BingoCard& card) const;
};
