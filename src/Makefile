CC = g++
CFLAGS = -Wall -Wextra -std=c++17 
LDFLAGS =
INCLUDE_DIRS = -I./List -I./Map -I./Queue -I./Set -I./Stack -I./Vector
LIB_DIRS =
LIBS =

SRCS = $(wildcard List/*.cpp) $(wildcard Map/*.cpp) $(wildcard Queue/*.cpp) $(wildcard Set/*.cpp) $(wildcard Stack/*.cpp) $(wildcard Vector/*.cpp)
OBJS = $(SRCS:.cpp=.o)

TARGET = libs21_containers.a

all: $(TARGET)

$(TARGET): $(OBJS)
	ar rcs $@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f test_runner

test:
	g++ -o test_runner tests/*.cpp -lgtest -lpthread
	./test_runner

s21_container:
	cp $(TARGET) /usr/local/lib
	cp -r ./ /usr/local/include/s21_containers

uninstall:
	rm /usr/local/lib/$(TARGET)
	rm -rf /usr/local/include/s21_containers

.PHONY: all clean test install uninstall
