#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

typedef struct pos { //각 국가에 대한 정보
	int row; //국가가 위치한 행
	int col; //국가가 위치한 열
	int people; //현재 국가에 있는 사람의 수
}pos;

pos queue[2500];
int N, L, R;
int map[50][50];
int visited[50][50];
int d_row[4] = { -1, 0, 1, 0 };
int d_col[4] = { 0, 1, 0, -1 };
int flag = 0; //인구 이동이 발생했는지를 나타내는 지표
int day = 0; //몇 일이 지났는지를 나타내는 변수

void bfs(int row, int col) {
	int front, rear, cur_row, cur_col, cur_people, next_row, next_col, dir, diff;
	front = rear = -1;

	queue[++rear].row = row; queue[rear].col = col; queue[rear].people = map[row][col]; visited[row][col] = 1; //초기 위치를 queue에 넣기
	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col; cur_people = queue[front].people; //queue에서 국가의 위치 가져오기

		dir = 0;
		while (dir < 4) {
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir++]; //4가지 방향에 대해 예상 좌표를 갱신
			if (next_row < 0 || next_row >= N || next_col < 0 || next_col >= N) continue; //만약 예상 좌표가 범위를 벗어나면 패스

			diff = (int)abs(map[next_row][next_col] - map[cur_row][cur_col]); //현재 국가와 예상 좌표의 국가의 인구 차를 diff로 계산

			if (diff >= L && diff <= R && visited[next_row][next_col] == 0) { //diff가 L과 R 사이의 값이고 아직 방문되지 않은 국가라면 queue에 넣기
				queue[++rear].row = next_row; queue[rear].col = next_col; queue[rear].people = map[next_row][next_col];
				visited[next_row][next_col] = 1;
			}
		}
	}

	int total = 0;
	if (rear != 0) { //rear이 0이 아닌 것, 즉 인구 이동이 일어난 경우
		for (int i = 0; i <= rear; i++) {
			//printf("%d %d %d\n", i, queue[i].row, queue[i].col);
			total += queue[i].people;
		}
		total /= rear + 1; //total에 국경이 열린 국가의 인구 수를 모두 더해서 국가의 개수로 나눈다(rear은 0부터 시작이니 1을 더해서 나눈다)
		for (int i = 0; i <= rear; i++) {
			map[queue[i].row][queue[i].col] = total; //그리고 해당 지점에 결정된 total 값을 넣는다
		}
		flag = 1; //인구 이동이 일어났다는 표시
	}
}

int main() {
	scanf("%d %d %d", &N, &L, &R);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
		}
	}

	while (1) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (visited[i][j] == 0) {
					bfs(i, j);
				}
			}
		}

		if (flag == 0) break; //인구 이동이 없는 경우 시행 종료

		else { //인구 이동이 있는 경우
			day++; //날짜를 하루 늘리고
			flag = 0; //다음 시행을 위해 flag을 0으로 갱신하고

			for (int i = 0; i < N; i++) { //visited를 다시 써야하니 0으로 초기화한다
				for (int j = 0; j < N; j++) {
					visited[i][j] = 0;
				}
			}
		}

	}

	printf("%d", day); //인구 이동이 더 이상 일어나지 않아 while loop을 나왔으면 지나간 day를 출력한다
}
