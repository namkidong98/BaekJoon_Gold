//벽 부수고 이동하기 2(골드3)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct pos {
	int row;
	int col;
	int time;
	int use;
}pos;

int N, M, K;
int map[1001][1001];
int visited[1001][1001][11];

void bfs() {
	int d_row[4] = { -1, 0, 1, 0 };
	int d_col[4] = { 0, 1, 0 ,-1 };
	pos queue[1001 * 1001 * 11];
	int front, rear, cur_row, cur_col, cur_time, cur_use, dir, next_row, next_col;
	front = rear = -1;

	//시작 부분을 queue에 더하기
	queue[++rear].row = 0; queue[rear].col = 0; queue[rear].time = 1; queue[rear].use = 0; visited[0][0][0] = 1;

	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col; cur_time = queue[front].time; cur_use = queue[front].use; //queue에서 위치 가져오기

		if ((cur_row == N - 1) && (cur_col == M - 1)) break; //종점에 도착하면 while loop 종료

		dir = 0;
		while (dir < 4) { //4가지 방향에 대한 탐색
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir]; //예상가는 다음 좌표를 갱신

			if (next_row < N && next_row >= 0 && next_col < M && next_col >= 0 && cur_use <= K) { //map의 범위 안에 있고
				if (map[next_row][next_col] == 0 && visited[next_row][next_col][cur_use] == 0) { //map이 0이라 이동할 수 있고 방문한 적이 없으면
					//queue에 추가
					queue[++rear].row = next_row; queue[rear].col = next_col;
					queue[rear].time = cur_time + 1; queue[rear].use = cur_use;
					visited[next_row][next_col][cur_use] = 1;
				}
				else if (map[next_row][next_col] == 1 && cur_use < K && visited[next_row][next_col][cur_use + 1] == 0) { //이동할 수 없는 곳이지만 벽을 아직 더 부술 수 있고 방문한 적이 없는 곳이면
					//queue에 추가
					queue[++rear].row = next_row; queue[rear].col = next_col;
					queue[rear].time = cur_time + 1; queue[rear].use = cur_use + 1;
					visited[next_row][next_col][cur_use + 1] = 1;
				}
			}

			dir++; //방향 바꾸기
		}

	}

	if ((cur_row == N - 1) && (cur_col == M - 1)) printf("%d", cur_time);
	else printf("-1");

}

int main() {
	char temp[1001][1001];
	scanf("%d %d %d", &N, &M, &K);
	
	for (int i = 0; i < N; i++) {
		scanf("%s", temp[i]);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (temp[i][j] == '0') map[i][j] = 0;
			if (temp[i][j] == '1') map[i][j] = 1;
		}
	}

	bfs();
}