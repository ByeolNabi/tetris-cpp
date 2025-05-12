#ifndef TETROMINO_SHAPES_H
#define TETROMINO_SHAPES_H

#include <vector>

const std::vector<std::vector<int>> I_SHAPE = {{1, 1, 1, 1}};
const std::vector<std::vector<int>> J_SHAPE = {{1, 1, 1}, {0, 0, 1}};
const std::vector<std::vector<int>> L_SHAPE = {{1, 1, 1}, {1, 0, 0}};
const std::vector<std::vector<int>> O_SHAPE = {{1, 1}, {1, 1}};
const std::vector<std::vector<int>> S_SHAPE = {{0, 1, 1}, {1, 1, 0}};
const std::vector<std::vector<int>> T_SHAPE = {{1, 1, 1}, {0, 1, 0}};
const std::vector<std::vector<int>> Z_SHAPE = {{1, 1, 0}, {0, 1, 1}};

#endif  // TETROMINO_SHAPES_H