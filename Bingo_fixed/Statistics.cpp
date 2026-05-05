#include "Statistics.h"
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;
// ─────────────────────────────────────────────
//  Constructor & Reset
// ─────────────────────────────────────────────
Statistics::Statistics(int numCards, const PrizeCalculator& prize)
    : tongSoVan(0), tongSoLuot(0), soVanCoNguoiThang(0),
      numCards(numCards), prize(prize),
      tongThu(0), tongThuong(0), tongLoiNhuan(0),
      loiNhuanMin(1e18), loiNhuanMax(-1e18)
{
    Reset();
}

void Statistics::Reset() {
    tongSoVan = tongSoLuot = soVanCoNguoiThang = 0;
    tongThu = tongThuong = tongLoiNhuan = 0;
    loiNhuanMin =  1e18;
    loiNhuanMax = -1e18;
    loiNhuanMoiVan.clear();
    winConditionCount.clear();

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            heatmap[i][j] = 0;

    for (int i = 0; i < 100; i++) {
        soLanThang[i]          = 0;
        soLanTrenDuongThang[i] = 0;
        soLanXuatHien[i]       = 0;
    }
    for (int i = 1; i <= 99; i++) freq[i] = 0;
}

// ─────────────────────────────────────────────
//  record() — ghi nhận 1 ván chơi
// ─────────────────────────────────────────────
void Statistics::record(const GameResult& result) {
    tongSoVan++;
    tongSoLuot += result.drawCount;
    const DuLieuVan& d = result.duLieuVan;

    if (d.daThang) {
        soVanCoNguoiThang++;
        winConditionCount[result.winConditionName]++;

        // Cập nhật heatmap, soLanThang, BCR từ phiếu thắng
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                int so = d.bang[i][j];

                // Chỉ số 1: heatmap
                if (d.duongThang[i][j]) heatmap[i][j]++;

                if (so <= 0) continue; // bỏ qua ô X (= -1) và ô trống (= 0)

                // Chỉ số 2: số may mắn — chỉ đếm ô trên đường thắng
                if (d.duongThang[i][j]) soLanThang[so]++;

                // Chỉ số 3 BCR — tần số mẫu số
                soLanXuatHien[so]++;

                // Chỉ số 3 BCR — tần số tử số
                if (d.duongThang[i][j]) soLanTrenDuongThang[so]++;
            }
        }
    }

    // Tần suất số được bốc
    for (int so : result.sequence)
        if (so >= 1 && so <= 99) freq[so]++;

    // Tài chính
    tongThu       += result.totalCollected;
    tongThuong    += result.prizePaid;
    tongLoiNhuan  += result.houseProfit;
    if (result.houseProfit < loiNhuanMin) loiNhuanMin = result.houseProfit;
    if (result.houseProfit > loiNhuanMax) loiNhuanMax = result.houseProfit;
    loiNhuanMoiVan.push_back(result.houseProfit);
}

// ─────────────────────────────────────────────
//  Helpers
// ─────────────────────────────────────────────
void Statistics::SapXep(int idx[], float val[], int n) const {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (val[idx[i]] < val[idx[j]]) swap(idx[i], idx[j]);
}
void Statistics::SapXep(int idx[], int val[], int n) const {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (val[idx[i]] < val[idx[j]]) swap(idx[i], idx[j]);
}
void Statistics::inThanh(int val, int maxVal, int width) const {
    int filled = (maxVal > 0) ? (val * width / maxVal) : 0;
    for (int i = 0; i < filled;  i++) cout << "\033[32m█\033[0m";
    for (int i = filled; i < width; i++) cout << "░";
}
void Statistics::inKeDuong(char c, int w) const {
    for (int i = 0; i < w; i++) cout << c;
    cout << "\n";
}

// ─────────────────────────────────────────────
//  Chỉ số 1: Heatmap
// ─────────────────────────────────────────────
void Statistics::XuatHeatmap() const {
    cout << "\n== CHI SO 1: HEATMAP O (hang x cot) ==\n";
    cout << "   (so lan o do nam tren duong thang)\n";
    cout << "      [0]   [1]   [2]   [3]   [4]\n";

    int maxH = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (heatmap[i][j] > maxH) maxH = heatmap[i][j];

    int hangMax = 0, cotMax = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (heatmap[i][j] > heatmap[hangMax][cotMax])
                { hangMax = i; cotMax = j; }

    for (int i = 0; i < 5; i++) {
        cout << "  [" << i << "]";
        for (int j = 0; j < 5; j++) {
            if (i == hangMax && j == cotMax)
                cout << "\033[32m" << setw(6) << heatmap[i][j] << "\033[0m";
            else
                cout << setw(6) << heatmap[i][j];
        }
        cout << "\n";
    }
    cout << "=> Nen dat X vao o (" << hangMax << "," << cotMax
              << ") - xuat hien " << heatmap[hangMax][cotMax] << " lan tren duong thang\n";
}

// ─────────────────────────────────────────────
//  Chỉ số 2: Số may mắn
// ─────────────────────────────────────────────
void Statistics::XuatSoMayMan(int soLuongTop) const {
    cout << "\n== CHI SO 2: TOP " << soLuongTop << " SO MAY MAN ==\n";
    cout << "   (so hay xuat hien o phieu thang)\n";
    inKeDuong('-', 40);

    int tmp[100]; // copy để tránh vi phạm const
    for (int i = 0; i < 100; i++) tmp[i] = soLanThang[i];

    int idx[99];
    for (int i = 0; i < 99; i++) idx[i] = i + 1;
    SapXep(idx, tmp, 99);

    for (int t = 0; t < soLuongTop && t < 99; t++)
        cout << "  " << (t+1) << ". So " << setw(3) << idx[t]
                  << " — " << tmp[idx[t]] << " lan\n";
}

// ─────────────────────────────────────────────
//  Chỉ số 3: BCR
// ─────────────────────────────────────────────
void Statistics::XuatBCR(int soLuongTop) const {
    cout << "\n== CHI SO 3: BINGO CONTRIBUTION RATE (BCR) ==\n";
    cout << "   BCR = so lan tren duong thang / tong lan xuat hien\n";
    cout << "   BCR cao = so co gia tri chien thuat cao\n";
    inKeDuong('-', 50);

    float bcr[100] = {};
    for (int so = 1; so <= 99; so++)
        if (soLanXuatHien[so] > 0)
            bcr[so] = (float)soLanTrenDuongThang[so] / soLanXuatHien[so] * 100.0f;

    int idx[99];
    for (int i = 0; i < 99; i++) idx[i] = i + 1;
    SapXep(idx, bcr, 99);

    for (int t = 0; t < soLuongTop && t < 99; t++)
        cout << "  " << (t+1) << ". So " << setw(3) << idx[t]
                  << " — BCR: " << fixed << setprecision(1)
                  << bcr[idx[t]] << "%\n";
}

// ─────────────────────────────────────────────
//  Tần suất số 1–99
// ─────────────────────────────────────────────
void Statistics::printFrequencyTable() const {
    int maxF = 0;
    for (auto& [k,v] : freq) maxF = max(maxF, v);

    cout << "\n";
    inKeDuong('=', 60);
    cout << "  BANG TAN SUAT SO (tong " << tongSoVan << " van)\n";
    inKeDuong('=', 60);
    cout << left
              << setw(6)  << "  So"
              << setw(12) << "  Tan suat"
              << setw(10) << "  Ti le%"
              << "  Bieu do\n";
    inKeDuong('-', 60);

    for (auto& [num, cnt] : freq) {
        double ratio = tongSoVan > 0 ? 100.0 * cnt / tongSoVan : 0;
        cout << "  " << right << setw(3) << num
                  << "  "              << setw(9) << cnt
                  << "  "              << setw(5) << fixed
                                       << setprecision(1) << ratio << "%  ";
        inThanh(cnt, maxF, 18);
        cout << "\n";
    }
    inKeDuong('=', 60);
}

// ─────────────────────────────────────────────
//  Báo cáo tài chính
// ─────────────────────────────────────────────
void Statistics::printFinancialReport() const {
    if (tongSoVan == 0) return;

    double avgThu     = tongThu      / tongSoVan;
    double avgThuong  = tongThuong   / tongSoVan;
    double avgLoiNhuan= tongLoiNhuan / tongSoVan;
    double tiSuat     = tongThu > 0 ? tongLoiNhuan / tongThu * 100.0 : 0;

    int vanLoi = 0, vanLo = 0;
    for (double p : loiNhuanMoiVan) {
        if (p >= 0) vanLoi++; else vanLo++;
    }

    cout << "\n";
    inKeDuong('=', 55);
    cout << "  BAO CAO TAI CHINH NHA CAI — " << tongSoVan << " VAN\n";
    inKeDuong('=', 55);
    cout << "  Gia ve (n)         : " << fixed << setprecision(0)
              << prize.getTicketPrice() << " dong\n";
    cout << "  He so thuong (b)   : " << setprecision(2)
              << prize.getBonusMultiplier() << "x\n";
    cout << "  Giam thuong (x/k)  : "
              << prize.getDecayPercent() << "% moi "
              << prize.getDecayInterval() << " lan boc\n";
    inKeDuong('-', 55);
    cout << "  Tong thu           : " << setprecision(0)
              << tongThu      << " dong\n";
    cout << "  Tong tra thuong    : " << tongThuong   << " dong\n";
    cout << "  Tong loi nhuan     : ";
    if (tongLoiNhuan >= 0)
        cout << "\033[32m+" << tongLoiNhuan << " dong\033[0m\n";
    else
        cout << "\033[31m"  << tongLoiNhuan << " dong (LO!)\033[0m\n";
    cout << "  Ti suat loi nhuan  : ";
    if (tiSuat >= 0)
        cout << "\033[32m+" << setprecision(2) << tiSuat << "%\033[0m\n";
    else
        cout << "\033[31m"  << tiSuat << "%\033[0m\n";
    inKeDuong('-', 55);
    cout << "  TB moi van — Thu   : " << setprecision(0) << avgThu    << " dong\n";
    cout << "  TB moi van — Thuong: " << avgThuong  << " dong\n";
    cout << "  TB moi van — Loi   : ";
    if (avgLoiNhuan >= 0)
        cout << "\033[32m+" << avgLoiNhuan << "\033[0m dong\n";
    else
        cout << "\033[31m"  << avgLoiNhuan << "\033[0m dong\n";
    cout << "  Loi nhuan cao nhat : \033[32m+" << loiNhuanMax << "\033[0m dong\n";
    cout << "  Loi nhuan thap nhat: ";
    if (loiNhuanMin >= 0)
        cout << "\033[32m+" << loiNhuanMin << "\033[0m dong\n";
    else
        cout << "\033[31m"  << loiNhuanMin << "\033[0m dong\n";
    inKeDuong('-', 55);
    cout << "  Van nha cai loi    : " << vanLoi << "/" << tongSoVan
              << " (" << setprecision(1) << (100.0*vanLoi/tongSoVan) << "%)\n";
    cout << "  Van nha cai lo     : " << vanLo  << "/" << tongSoVan
              << " (" << (100.0*vanLo/tongSoVan) << "%)\n";
    inKeDuong('=', 55);

    if (tiSuat > 10)
        cout << "  => Cau hinh rat CO LOI cho nha cai\n";
    else if (tiSuat > 0)
        cout << "  => Nha cai co loi nhe, xem xet tang b de hap dan hon\n";
    else
        cout << "  => Nha cai THUA LO! Can giam b hoac tang x/giam k\n";
}

// ─────────────────────────────────────────────
//  Tổng hợp
// ─────────────────────────────────────────────
void Statistics::printSummary() const {
    inKeDuong('*', 55);
    cout << "  KET QUA MO PHONG — " << tongSoVan << " VAN\n";
    inKeDuong('*', 55);

    int soLuotTB = tongSoVan > 0 ? tongSoLuot / tongSoVan : 0;
    cout << "  So van da chay     : " << tongSoVan << "\n";
    cout << "  So luot boc TB/van : " << soLuotTB  << "\n";
    cout << "  Van co nguoi thang : " << soVanCoNguoiThang << "\n";

    printFinancialReport();
    XuatHeatmap();
    XuatSoMayMan(5);
    XuatBCR(5);
}
