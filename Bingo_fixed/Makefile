CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = Bingo
SRCS   = main.cpp \
         NumberBag.cpp \
         BingoCard.cpp \
         WinCondition.cpp \
         BingoGame.cpp \
         PrizeCalculator.cpp \
         Statistics.cpp \
         Simulator.cpp \
         GridSearch.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
