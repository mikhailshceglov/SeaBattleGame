# TARGET = ./main
# CXX = g++

# SRC_DIR = ./src/
# INCLUDE_DIR = ./include/
# BIN_DIR = ./bin/
# TEST_DIR = ./test/
# TEST_BIN_DIR = ./test_bin/

# CXXFLAGS = -I$(INCLUDE_DIR) -std=c++17

# SRC = $(wildcard $(SRC_DIR)*.cpp)  # Находим все .cpp файлы в папке src

# # Меняем расширение на .o и кладем в bin
# OBJ = $(patsubst $(SRC_DIR)%.cpp, $(BIN_DIR)%.o, $(SRC))

# all : create_bin_dir $(TARGET)

# # Правило для компиляции .cpp файлов в .o
# $(BIN_DIR)%.o : $(SRC_DIR)%.cpp $(INCLUDE_DIR)*.h
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Правило для линковки объектных файлов в исполняемый файл
# $(TARGET) : $(OBJ)
# 	$(CXX) $(OBJ) -o $@

# # Создание папки bin, если её нет
# create_bin_dir :
# 	@mkdir -p $(BIN_DIR)

# # Добавление цели для тестов
# test: create_test_bin test_bin/test_field test_bin/test_ship test_bin/test_shipManager
# 	./test_bin/test_field
# 	./test_bin/test_ship
# 	./test_bin/test_shipManager

# # Создание папки test_bin, если её нет
# create_test_bin:
# 	@mkdir -p $(TEST_BIN_DIR)

# # Компиляция каждого теста
# test_bin/test_field.o: test/test_field.cpp
# 	g++ -std=c++11 -I$(INCLUDE_DIR) -c test/test_field.cpp -o test_bin/test_field.o

# test_bin/test_field: test_bin/test_field.o
# 	g++ -std=c++11 -o test_bin/test_field test_bin/test_field.o -lgtest_main -lgtest -pthread

# test_bin/test_ship.o: test/test_ship.cpp
# 	g++ -std=c++11 -I$(INCLUDE_DIR) -c test/test_ship.cpp -o test_bin/test_ship.o

# test_bin/test_ship: test_bin/test_ship.o
# 	g++ -std=c++11 -o test_bin/test_ship test_bin/test_ship.o -lgtest_main -lgtest -pthread

# test_bin/test_shipManager.o: test/test_shipManager.cpp
# 	g++ -std=c++11 -I$(INCLUDE_DIR) -c test/test_shipManager.cpp -o test_bin/test_shipManager.o

# test_bin/test_shipManager: test_bin/test_shipManager.o
# 	g++ -std=c++11 -o test_bin/test_shipManager test_bin/test_shipManager.o -lgtest_main -lgtest -pthread

# clean:
# 	@rm -f $(TARGET)
# 	@rm -rf $(BIN_DIR) $(TEST_BIN_DIR)
# 	@rm -f test_bin/test_field test_bin/test_ship test_bin/test_shipManager

# GUI
TARGET = ./main
CXX = g++

SRC_DIR = ./src/
INCLUDE_DIR = ./include/
BIN_DIR = ./bin/
TEST_DIR = ./test/
TEST_BIN_DIR = ./test_bin/
IMGUI_DIR = ./imgui/

CXXFLAGS = -I$(INCLUDE_DIR) -I$(IMGUI_DIR) -I$(IMGUI_DIR)backends -std=c++17
LDFLAGS = -lglfw -lGL -lGLEW -ldl


# Находим все .cpp файлы в папке src
SRC = $(wildcard $(SRC_DIR)*.cpp)

# Добавляем файлы ImGui
IMGUI_SRC = $(IMGUI_DIR)imgui.cpp $(IMGUI_DIR)imgui_draw.cpp $(IMGUI_DIR)imgui_widgets.cpp $(IMGUI_DIR)imgui_tables.cpp \
            $(IMGUI_DIR)backends/imgui_impl_glfw.cpp $(IMGUI_DIR)backends/imgui_impl_opengl3.cpp

# Меняем расширение на .o и кладем в bin
OBJ = $(patsubst $(SRC_DIR)%.cpp, $(BIN_DIR)%.o, $(SRC)) $(patsubst $(IMGUI_DIR)%.cpp, $(BIN_DIR)%.o, $(IMGUI_SRC))

all : $(TARGET)

# Создание исполняемого файла
$(TARGET) : $(OBJ) | $(BIN_DIR)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

# Правило для компиляции .cpp файлов в .o
$(BIN_DIR)%.o : $(SRC_DIR)%.cpp | $(BIN_DIR)
	@mkdir -p $(dir $@) # Автоматически создаем каталог, если его нет
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Компиляция ImGui файлов в объектные
$(BIN_DIR)%.o : $(IMGUI_DIR)%.cpp | $(BIN_DIR)
	@mkdir -p $(dir $@) # Автоматически создаем каталог, если его нет
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Создание каталога bin, если он отсутствует
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Добавление цели для тестов
test: create_test_bin test_bin/test_field test_bin/test_ship test_bin/test_shipManager
	./test_bin/test_field
	./test_bin/test_ship
	./test_bin/test_shipManager

# Создание папки test_bin, если её нет
create_test_bin:
	@mkdir -p $(TEST_BIN_DIR)

# Компиляция каждого теста
test_bin/test_field.o: test/test_field.cpp | $(TEST_BIN_DIR)
	$(CXX) -std=c++11 -I$(INCLUDE_DIR) -c $< -o $@

test_bin/test_field: test_bin/test_field.o
	$(CXX) -std=c++11 -o $@ $< -lgtest_main -lgtest -pthread

test_bin/test_ship.o: test/test_ship.cpp | $(TEST_BIN_DIR)
	$(CXX) -std=c++11 -I$(INCLUDE_DIR) -c $< -o $@

test_bin/test_ship: test_bin/test_ship.o
	$(CXX) -std=c++11 -o $@ $< -lgtest_main -lgtest -pthread

test_bin/test_shipManager.o: test/test_shipManager.cpp | $(TEST_BIN_DIR)
	$(CXX) -std=c++11 -I$(INCLUDE_DIR) -c $< -o $@

test_bin/test_shipManager: test_bin/test_shipManager.o
	$(CXX) -std=c++11 -o $@ $< -lgtest_main -lgtest -pthread

# Очистка сгенерированных файлов
clean:
	@rm -f $(TARGET)
	@rm -rf $(BIN_DIR) $(TEST_BIN_DIR)
	@rm -f test_bin/test_field test_bin/test_ship test_bin/test_shipManager