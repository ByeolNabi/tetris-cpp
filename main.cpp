#include <fcntl.h>
#include <termios.h>  // 터미널 입력 모드 변경
#include <unistd.h>

#include <chrono>   // sleep_for 반복 주기를 위해서
#include <cstdlib>  // system 함수 사용
#include <iostream>
#include <thread>  // sleep_for를 위해
#include <vector>

#include "tetromino_shapes.h"

using namespace std;

// 터미널에서 비차단 입력 처리
void setNonBlockingInput() {
  termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag &= ~(ICANON | ECHO);  // 캐논 모드, 에코 끄기
  tcsetattr(STDIN_FILENO, TCSANOW, &term);

  // 비차단 모드 설정
  int flags = fcntl(STDIN_FILENO, F_GETFL);
  fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void resetInput() {
  termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag |= (ICANON | ECHO);  // 캐논 모드, 에코 켜기
  tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void clearFrame() {
  // 화면 지우기 (Mac/Linux)
  system("clear");
}

void draw_tetromino(vector<vector<char>>& b, int y, int x,
                    vector<vector<int>> ttrmn) {
  if (y > 18) {
    return;
  }
  for (int i = 0; i < ttrmn[0].size(); ++i) {
    b[y - 1][x + i] = 0;
  }
  for (int r = 0; r < ttrmn.size(); ++r) {
    for (int c = 0; c < ttrmn[0].size(); ++c) {
      b[r + y][c + x] = ttrmn[r][c];
    }
  }
}

void print_board(vector<vector<char>>& b, char last_key) {
  for (auto row : b) {
    for (auto col : row) {
      printf("%2d", col);
    }
    printf("\n");
  }
  // 입력한 마지막 키를 보드 아래에 출력
  cout << "\nLast Key Pressed: " << last_key << endl;
}

void board_init(vector<vector<char>>& board) {
  for (auto i : {0, 21}) {
    for (int j = 0; j < 12; ++j) {
      board[i][j] = -1;
    }
  }

  for (auto i : {0, 11}) {
    for (int j = 0; j < 22; ++j) {
      board[j][i] = -1;
    }
  }
}

int main() {
  setNonBlockingInput();  // 비차단 입력 설정

  vector<vector<char>> board(22, vector<char>(12));
  board_init(board);
  char last_key = ' ';  // 마지막 입력된 키
  int crt_x = 5;
  int crt_y = 4;

  for (int i = 0; i < 20; ++i) {  // 20 프레임만 루핑
    clearFrame();

    // 비차단 입력 체크 (버퍼에 있는 모든 키를 처리하고 마지막 키만 저장)
    char c;
    ssize_t n;
    // 버퍼에 남아 있는 키 모두 읽어오기
    while ((n = read(STDIN_FILENO, &c, 1)) > 0) {
      last_key = c;  // 마지막으로 읽은 키 저장
    }
    if (c == 67) {
      crt_x += 1;
      draw_tetromino(board, crt_y, crt_x, S_SHAPE);
      clearFrame();
      print_board(board, last_key);

    } else if (c == 68) {
      crt_x -= 1;
      draw_tetromino(board, crt_y, crt_x, S_SHAPE);
      clearFrame();
      print_board(board, last_key);
    }
    crt_y += 1;
    draw_tetromino(board, crt_y, crt_x, S_SHAPE);
    c = 0;

    print_board(board, last_key);
    printf("\n");

    std::this_thread::sleep_for(std::chrono::milliseconds(500));  // 0.5초 대기
  }

  resetInput();  // 입력 모드 리셋
  return 0;
}
