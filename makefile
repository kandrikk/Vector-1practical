CXX = g++
MAIN_TARGET = main
TEST_TARGET = vector_test
SRC = src/Vector.cpp
FLAGS = -L. -lVectorTest

all: $(MAIN_TARGET) $(TEST_TARGET)

# Основная компиляция без флагов
$(MAIN_TARGET): $(SRC)
	$(CXX) -o $(MAIN_TARGET) $(SRC)

# Компиляция тестовой версии с флагами
$(TEST_TARGET): $(SRC)
	$(CXX) -o $(TEST_TARGET) $(SRC) $(FLAGS)

# Запуск основной версии
run: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Запуск тестовой версии
test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(MAIN_TARGET) $(TEST_TARGET)

.PHONY: all run test clean

