CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = reservation_system

SRCS = main.cpp \
       Resource.cpp ResourceManager.cpp \
       Reservation.cpp ReservationManager.cpp \
       WaitingQueue.cpp CancellationStack.cpp \
       ReportManager.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) *.o
