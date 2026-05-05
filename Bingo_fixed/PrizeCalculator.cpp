#include "PrizeCalculator.h"
#include <cmath>

PrizeCalculator::PrizeCalculator(double ticketPrice, double bonusMultiplier,
                                 double decayPercent, int decayInterval)
    : ticketPrice(ticketPrice), bonusMultiplier(bonusMultiplier),
      decayPercent(decayPercent), decayInterval(decayInterval)
{}

double PrizeCalculator::totalCollected(int numCards) const {
    return numCards * ticketPrice;
}

double PrizeCalculator::actualPrize(int numCards, int drawCount) const {
    double base      = bonusMultiplier * totalCollected(numCards);
    int    periods   = drawCount / decayInterval;
    double decayRate = 1.0 - (decayPercent / 100.0);
    return base * std::pow(decayRate, periods);
}

double PrizeCalculator::houseProfit(int numCards, int drawCount) const {
    return totalCollected(numCards) - actualPrize(numCards, drawCount);
}

double PrizeCalculator::getTicketPrice()     const { return ticketPrice; }
double PrizeCalculator::getBonusMultiplier() const { return bonusMultiplier; }
double PrizeCalculator::getDecayPercent()    const { return decayPercent; }
int    PrizeCalculator::getDecayInterval()   const { return decayInterval; }
