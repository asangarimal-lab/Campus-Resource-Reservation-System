CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = reservation_system
TEST_TARGET = queue_stack_tests.out
HEADERS = $(wildcard *.h)

SRCS = main.cpp \
       Resource.cpp ResourceManager.cpp \
       Reservation.cpp ReservationManager.cpp \
       WaitingQueue.cpp CancellationStack.cpp \
       ReportManager.cpp

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

.PHONY: all test clean

$(TEST_TARGET): tests/QueueStackTests.cpp $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -I. -o $(TEST_TARGET) tests/QueueStackTests.cpp $(filter-out main.cpp,$(SRCS))

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe $(TEST_TARGET) *.o