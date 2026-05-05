#pragma once
#include <vector>
using namespace std;
class NumberBag {
private:
    vector<int> so;   // danh sách số 1–99 đã xáo
    int              n;    // vị trí rút hiện tại

public:
    NumberBag();
    void             xao();       // xáo lại để chơi ván mới
    int              bocso();     // rút 1 số, trả -1 nếu hết
    vector<int> sodaboc();   // các số đã rút
    bool             hetSo() const;
};
