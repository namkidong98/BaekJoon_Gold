//연구소(골드4)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct pos {
	int row;
	int col;
}pos;

int row, col; //map의 행과 열을 저장
int** map;
int** visited; //bfs에서 사용될 변수로 해당 좌표가 방문되었는지를 저장
int max = 0; //안전 지역의 최대 값을 저장하는 변수(이 문제의 최종 답)
int front, rear;
pos* queue;
int d_row[4] = { 1, 0, -1, 0 }; //4방향을 행을 기준으로
int d_col[4] = { 0, 1, 0, -1 }; //4방향을 열을 기준으로
int num_of_one = 0; //map에서 1인 지점의 개수

void clear();
void choose(int count, int cur_row, int cur_col);
void bfs();
void count(int num_of_two);

int main() {
	scanf("%d %d", &row, &col);
	map = (int**)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++) map[i] = malloc(sizeof(int) * col);
	visited = (int**)malloc(sizeof(int*) * row);
	for (int i = 0; i < row; i++) visited[i] = malloc(sizeof(int) * col);
	queue = (pos*)malloc(sizeof(pos) * row * col);
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) num_of_one++;
			visited[i][j] = 0;
		}
	}
	choose(0, 0, 0); //0개의 벽이 골라진 상황, 시작 지점은 0행, 0열

	printf("%d", max);
}

void choose(int count, int cur_row, int cur_col) {
	if (count == 3) { //3개의 벽을 세웠을 때
		bfs(); //그 상황에서 바이러스를 bfs로 퍼트리고 안전 영역의 최대를 계산
		clear(); //visited를 다음 시행을 위해 초기화
	}
	else {
		for (int i = cur_row; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if (i == cur_row && j < cur_col) continue; //그냥 j = cur_col으로 하니깐 배제되는 케이스들이 있었음(cur_row가 증가하면 j=0부터 따져야함)
				if (map[i][j] == 0 && count < 3) {
					map[i][j] = 1; //벽 세우기
					choose(count + 1, i, j);
					map[i][j] = 0; //재귀가 끝나고 나올 때 원상복구
				}
			}
		}
	}
}

void bfs() {
	int cur_row, cur_col, next_row, next_col, dir;
	int num_of_two;
	front = rear = -1;

	//초기부터 2인 지점(바이러스가 있는 지점) queue에 넣기
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (map[i][j] == 2) {
				queue[++rear].row = i;
				queue[rear].col = j;
				visited[i][j] = 1;
			}
		}
	}

	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col;

		dir = 0;
		while (dir < 4) { //4가지 방향에 따라
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir]; //예상되는 다음 좌표를 갱신하고
			if (next_row < row && next_row >= 0 && next_col < col && next_col >= 0) { //그 좌표가 map의 범위 안에 들어오고
				if (visited[next_row][next_col] == 0 && map[next_row][next_col] == 0) { //map에서 빈칸에 해당하고 아직 방문되지 않은 곳이면
					visited[next_row][next_col] = 1; //방문 기록을 남기고
					queue[++rear].row = next_row; queue[rear].col = next_col; //해당 좌표를 queue에 넣기
				}
			}
			dir++; //다음 방향 따지기
		}
	}

	num_of_two = rear + 1; //rear에는 0부터 rear까지 queue에 들어간 좌표들의 개수가 남는다 0부터니깐 1을 더하면 map에서 2인 지점의 총 개수를 의미한다
	count(num_of_two);
}

void count(int num_of_two) {
	int total = row * col; //전체 좌표의 개수를 구하고
	int count = total - num_of_two - (num_of_one + 3); //1의 개수(기존 1의 개수 + 새로 세운 벽의 개수 3개), 2의 개수를 모두 빼면, 해당 시행의 0의 개수
	if (count > max) max = count; //그 0의 개수(즉 안전 영역의 개수)가 최대보다 더 크면 갱신
}

void clear() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			visited[i][j] = 0;
		}
	}
}