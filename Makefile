CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2

TARGET = imobiliaria

SRCS = main.cpp corretor.cpp cliente.cpp imovel.cpp distancia.cpp agendamento.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)