//적록색약 (골드5)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct pos {
	int row;
	int col;
}pos;

int	row, col;
int visited[101][101];
char map[101][101];

void bfs(int start_row, int start_col) {
	int front, rear, cur_row, cur_col, next_row, next_col, dir;
	pos queue[10000];
	int d_row[4] = { -1, 0, 1, 0 };
	int d_col[4] = { 0, 1, 0 ,-1 };
	char target = map[start_row][start_col]; //해당 지점의 RGB값
	front = rear = -1;

	queue[++rear].row = start_row; queue[rear].col = start_col; visited[start_row][start_col] = 1; //시작 지점 입력
	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col; //queue에서 위치 가져오기

		dir = 0;
		while (dir < 4) { //4방향을 탐색
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir]; //예상되는 좌표 갱신
			if (next_row >= 0 && next_row < row && next_col >= 0 && next_col < col) { //예상되는 좌표가 map의 범위 안에 있다면
				if (visited[next_row][next_col] == 0 && map[next_row][next_col] == target) { //그리고 방문되지 않았고 시작 지점과 같은 RGB값이면
					queue[++rear].row = next_row; //queue에 추가하고 방문 기록 남기기
					queue[rear].col = next_col;
					visited[next_row][next_col] = 1;
				}
			}
			dir++; //다음 방향 탐색
		}
	}
}

int main() {
	int count = 0;
	scanf("%d", &row); col = row;
	for (int i = 0; i < row; i++) {
		scanf("%s", &map[i]);
	}

	//원래 map을 가지고 bfs해서 구역의 개수 구하기
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (visited[i][j] == 0) {
				bfs(i, j);
				count++;
			}
		}
	}
	printf("%d ", count);

	//다음 시행을 위한 초기화 및 map에서 green을 red로 변환(적록색맹의 경우)
	count = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			visited[i][j] = 0;
			if (map[i][j] == 'G') map[i][j] = 'R';
		}
	}

	//적록색맹인 경우의 map을 가지고 bfs해서 구역의 개수 구하기
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (visited[i][j] == 0) {
				bfs(i, j);
				count++;
			}
		}
	}
	printf("%d", count);
}