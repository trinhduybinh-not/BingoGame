#pragma once

class PrizeCalculator {
private:
    double ticketPrice;      // n: giá 1 tờ phiếu
    double bonusMultiplier;  // b: thưởng = b × tổng thu
    double decayPercent;     // x: giảm x% sau mỗi k lần bốc
    int    decayInterval;    // k: khoảng cách giảm thưởng

public:
    PrizeCalculator(double ticketPrice,
                    double bonusMultiplier,
                    double decayPercent,
                    int    decayInterval);

    // Tổng tiền thu từ người chơi
    double totalCollected(int numCards)               const;

    // Tiền thưởng thực tế sau khi áp dụng giảm theo drawCount
    double actualPrize(int numCards, int drawCount)   const;

    // Lợi nhuận nhà cái = tổng thu - thưởng thực
    double houseProfit(int numCards, int drawCount)   const;

    // Getters để Statistics có thể in thông số
    double getTicketPrice()     const;
    double getBonusMultiplier() const;
    double getDecayPercent()    const;
    int    getDecayInterval()   const;
};
