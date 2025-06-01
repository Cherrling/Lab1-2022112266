# Makefile for building and running unit tests

# 编译器设置
CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Google Test 库链接
GTEST_LIBS = -lgtest -lgtest_main -pthread

# 源文件目录
SRC_DIR = ../src
TEST_DIR = .

# 目标文件
TEST_TARGET = test_bridge

# 测试源文件
TEST_SOURCES = $(TEST_DIR)/test_bridge_words.cpp

# 默认目标
all: $(TEST_TARGET)

# 编译测试程序
$(TEST_TARGET): $(TEST_SOURCES) $(SRC_DIR)/bridge_words.cpp
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -o $@ $^ $(GTEST_LIBS)