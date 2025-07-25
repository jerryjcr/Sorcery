CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -g `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(SRCS:.cc=.o)
EXEC = sorcery

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(EXEC)

.PHONY: all clean
