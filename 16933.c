//벽 부수고 이동하기3 (골드 1)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define DAY 0
#define NIGHT 1

typedef struct pos {
	int row;
	int col;
	int time; //이동하는데 걸린 시간을 저장
	int use; //지금까지 몇개의 벽을 부쉈는지를 저장
}pos;

int N, M, K;
int map[1001][1001];
int visited[1001][1001][11][2]; //첫번째는 row, 두번째는 col, 세번째는 부순 벽의 개수(use), 마지막은 낮인지 밤인지를 나타냄

int d_row[4] = { -1, 0, 1, 0 };
int d_col[4] = { 0, 1, 0, -1 };

void bfs() {
	pos queue[1001 * 1001 * 11 * 2];
	int front, rear, cur_row, cur_col, cur_time, cur_use, next_row, next_col, dir, today;
	front = rear = -1;

	queue[++rear].row = 0; queue[rear].col = 0; queue[rear].time = 1; queue[rear].use = 0; visited[0][0][0][DAY] = 1;

	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col; cur_time = queue[front].time; cur_use = queue[front].use;
		if ((cur_time % 2) == 0) today = NIGHT; //짝수날은 저녁
		else today = DAY; //홀수날은 낮

		if (cur_row == (N - 1) && cur_col == (M - 1)) break;

		dir = 0;
		while (dir < 4) {
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir++]; //예상되는 다음 좌표를 계산

			if (next_row >= N || next_row < 0 || next_col >= M || next_col < 0 || cur_use > K) continue; //범위에 안들어오면 패스

			//case1: 낮밤 상관 없이 0인 공간으로 이동 (동일조건에서 방문하지 않았던, 낮과 밤은 고려 안하고)
			if (map[next_row][next_col] == 0 && visited[next_row][next_col][cur_use][DAY] == 0 && visited[next_row][next_col][cur_use][NIGHT] == 0) {
				queue[++rear].row = next_row; queue[rear].col = next_col; queue[rear].time = cur_time + 1; queue[rear].use = cur_use;
				visited[next_row][next_col][cur_use][today] = 1;
			}
			//case2: 낮일 때 && 부술 수 있는 한도가 남았을 때, 1인 공간으로 벽을 부수고 이동 (동일조건에서 방문하지 않았던)
			if (today == DAY && cur_use < K && map[next_row][next_col] == 1 && visited[next_row][next_col][cur_use + 1][today] == 0) {
				queue[++rear].row = next_row; queue[rear].col = next_col; queue[rear].time = cur_time + 1; queue[rear].use = cur_use + 1;
				visited[next_row][next_col][cur_use + 1][today] = 1;
			}
			//case3: 동일한 자리에서 하루 대기
			//고려사항 1: 동일한 곳에서 2번 대기하면 동일한 상황이 반복되니 이 부분은 조건을 달아 처리해야 한다
			//고려사항 2: 벽을 부수려고 하는데 밤이라서 못 부수는 경우 말고 아무 상관 없는데 동일 자리에서 하루 대기하는게 큐에 더해지면 지나치게 큐가 낭비된다
			if (today == NIGHT && cur_use < K && map[next_row][next_col] == 1 && visited[next_row][next_col][cur_use + 1][today] == 0) {
				queue[++rear].row = cur_row; queue[rear].col = cur_col; queue[rear].time = cur_time + 1; queue[rear].use = cur_use;
				visited[next_row][next_col][cur_use + 1][today] = 1;
			}
		}
	}

	if (cur_row == (N - 1) && cur_col == (M - 1)) printf("%d", cur_time); //목표지점에 도착하면 소요 시간을 출력
	else printf("-1"); //아니면 -1을 출력
}

int main() {
	char temp[1001][1001];
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; i++) {
		scanf("%s", temp[i]);
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (temp[i][j] == '1') map[i][j] = 1;
			else if (temp[i][j] == '0') map[i][j] = 0;
		}
	}

	bfs();
}