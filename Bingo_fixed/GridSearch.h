#pragma once
#include "PrizeCalculator.h"
#include "BingoGame.h"
#include "GameResult.h"
#include <vector>
#include <string>
using namespace std;
// ══════════════════════════════════════════════════════
//  GridSearch — quét toàn bộ tổ hợp (b, x, k) để tìm
//  vùng nhà cái luôn lời / luôn lỗ / trung gian.
//  Kết quả xuất ra CSV để vẽ biểu đồ bên ngoài.
// ══════════════════════════════════════════════════════

// Kết quả cho 1 tổ hợp tham số
struct GridPoint {
    double b;           // hệ số thưởng
    double x;           // % giảm thưởng
    int    k;           // khoảng giảm (số lần bốc)

    double avgProfit;   // lợi nhuận trung bình / ván
    double minProfit;   // lợi nhuận thấp nhất (ván xấu nhất)
    double maxProfit;   // lợi nhuận cao nhất
    double profitRate;  // tỉ suất lợi nhuận % = profit / revenue
    double lossRate;    // % ván nhà cái bị lỗ
    // Phân loại kết quả
    // "LUON LOI"  : minProfit > 0 (mọi ván đều lời)
    // "LUON LO"   : maxProfit < 0 (mọi ván đều lỗ)
    // "TRUNG GIAN": có ván lời, có ván lỗ
    string zone;
};

class GridSearch {
private:
    int    numGames;   // số ván mô phỏng mỗi tổ hợp
    int    numCards;
    double ticketPrice;

    // Chạy nhanh N ván với 1 PrizeCalculator, trả về GridPoint
    GridPoint runOne(double b, double x, int k) const;

public:
    GridSearch(int numGames, int numCards, double ticketPrice);

    // Quét toàn bộ tổ hợp b × x × k
    vector<GridPoint> run(
        // Dải giá trị b
        double bMin, double bMax, double bStep,
        // Dải giá trị x (% giảm)
        double xMin, double xMax, double xStep,
        // Dải giá trị k (khoảng giảm)
        vector<int> kValues
    ) const;

    // Xuất toàn bộ kết quả ra file CSV
    static void exportCSV(const vector<GridPoint>& results,
                          const string& filename);

    // In tóm tắt ra terminal
    static void printSummary(const vector<GridPoint>& results);
};
