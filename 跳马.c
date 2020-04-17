#include<stdio.h>
#include<string.h>
#define N 5
int map[N][N];
int count = 1;                  // 解法数
int flag = 0;
int main() {
  memset(map, 0, sizeof(map));
  void visit(int x, int y, int n);
  int start_x, start_y;
  printf("请输入起始坐标\n");
  scanf("%d", &start_x);
  scanf("%d",&start_y);
  map[start_x][start_y] = 1;
  if (start_x >= N || start_x <= -1 || start_y >= N || start_y <= -1) {
    printf("非法输入\n");
    return 0;
  }
  visit(start_x, start_y, 1);
  if (flag == 0)
    printf("无解");
getchar();
getchar();
}
void visit(int x, int y, int n) {
  map[x][y] = n;
  int i, j;
  if (n == N * N) {
    printf("第%d种解法\n", count);
    for (i = 0; i < N; i++) {
      for (j = 0; j < N; j++)
        printf("%3d", map[i][j]);
      printf("\n");
    }
    count++;
    flag = 1;
  }
  if (x >= 2 && y >= 1 && map[x - 2][y - 1] == 0) {
    visit(x - 2, y - 1, n + 1);
  }
  if (x >= 1 && y >= 2 && map[x - 1][y - 2] == 0) {
    visit(x - 1, y - 2, n + 1);
  }
      if (x <= N - 2 && y >= 2 && map[x + 1][y - 2] == 0) {
    visit(x + 1, y - 2, n + 1);
  }
  if (x <= N - 3 && y >= 1 && map[x + 2][y - 1] == 0) {
    visit(x + 2, y - 1, n + 1);
  }
  if (x <= N - 3 && y <= N - 2 && map[x + 2][y + 1] == 0) {
    visit(x + 2, y + 1, n + 1);
  }
  if (x <= N - 2 && y <= N - 3 && map[x + 1][y + 2] == 0) {
    visit(x + 1, y + 2, n + 1);
  }
  if (x >= 1 && y <= N - 3 && map[x - 1][y + 2] == 0) {
    visit(x - 1, y + 2, n + 1);
  }

  if (x >= 2 && y <= N - 2 && map[x - 2][y + 1] == 0) {
    visit(x - 2, y + 1, n + 1);
      }
  map[x][y] = 0;
}
