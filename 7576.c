//토마토(골드 5)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct pos {
	int row;
	int col;
	int day; //몇일 째인지
}pos;

int main() {
	int row, col, i, j;
	int target = 0; //아직 익지 않은 토마토(0으로 저장된 값)의 개수
	//case1: 초기값이 0이면 모든 토마토가 익은 상태로 0 출력
	//case2: 0이 아니었다가 0이 되면 while문 종료 & 최소날짜 출력
	//case3: 0이 아니었다가 0이 안되면 모두 익지는 못하는 상태로 -1 출력

	scanf("%d %d", &col, &row);
	row += 2; col += 2;
	int** matrix = (int**)malloc(sizeof(int*) * row);
	for (i = 0; i < row; i++) matrix[i] = (int*)malloc(sizeof(int) * col);
	int** visited = (int**)malloc(sizeof(int*) * row);
	for (i = 0; i < row; i++) visited[i] = (int*)malloc(sizeof(int) * col);

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			//겉 테두리 -2로 처리해서 덮기
			if (i == 0 || i == row - 1 || j == 0 || j == col - 1) matrix[i][j] = -2;
			else {
				scanf("%d", &matrix[i][j]);
				if (matrix[i][j] == 0) target++; //익지 않은 토마토가 입력될 때마다 1개씩 증가
			}
			visited[i][j] = 0; //방문 안했으면 0, 방문했으면 1 (0으로 초기화)
		}
	}
	
	pos* queue = (pos*)malloc(sizeof(pos) * (row - 2) * (col - 2));
	int front, rear, cur_row, cur_col, cur_day;
	front = rear = -1;

	//첫 시행에서 1인 지점을 queue에 add
	for (i = 1; i < row - 1; i++) {
		for (j = 1; j < col - 1; j++) {
			if (matrix[i][j] == 1) {
				visited[i][j] = 1; //해당 위치 방문 기록 남기기
				queue[++rear].row = i; queue[rear].col = j; queue[rear].day = 0;//해당 위치 queue에 add
			}
		}
	}

	if (target == 0) { //애초에 익지 않은 토마토가 없는 상태 --> 저장될 때부터 모든 토마토가 익어있는 상태
		printf("0");
		return 0;
	}

	while (front != rear) { //queue가 빌 때까지 반복
		cur_row = queue[++front].row; cur_col = queue[front].col; cur_day = queue[front].day; //queue에서 새로운 위치 가져오기

		//4방향을 탐색하여 이동할 수 있는 곳의 토마토에 방문
		//방문기록 남기고, 토마토를 익은 토마토로 바꾸고, 익지 않은 토마토 개수 1개 줄이고, 해당 위치를 queue에 add
		if (matrix[cur_row + 1][cur_col] == 0 && visited[cur_row + 1][cur_col] == 0) {
			visited[cur_row + 1][cur_col] = 1; //방문 기록 남기기
			matrix[cur_row + 1][cur_col] = 1; //익은 토마토로 바꾸기
			target--; //익지 않은 토마토 1개 줄어듦
			queue[++rear].row = cur_row + 1; queue[rear].col = cur_col; queue[rear].day = cur_day + 1; //해당 위치 queue에 add
		}
		if (matrix[cur_row - 1][cur_col] == 0 && visited[cur_row - 1][cur_col] == 0) {
			visited[cur_row - 1][cur_col] = 1; //방문 기록 남기기
			matrix[cur_row - 1][cur_col] = 1; //익은 토마토로 바꾸기
			target--; //익지 않은 토마토 1개 줄어듦
			queue[++rear].row = cur_row - 1; queue[rear].col = cur_col; queue[rear].day = cur_day + 1; //해당 위치 queue에 add
		}
		if (matrix[cur_row][cur_col + 1] == 0 && visited[cur_row][cur_col + 1] == 0) {
			visited[cur_row][cur_col + 1] = 1; //방문 기록 남기기
			matrix[cur_row][cur_col + 1] = 1; //익은 토마토로 바꾸기
			target--; //익지 않은 토마토 1개 줄어듦
			queue[++rear].row = cur_row; queue[rear].col = cur_col + 1; queue[rear].day = cur_day + 1; //해당 위치 queue에 add
		}
		if (matrix[cur_row][cur_col - 1] == 0 && visited[cur_row][cur_col - 1] == 0) {
			visited[cur_row][cur_col - 1] = 1; //방문 기록 남기기
			matrix[cur_row][cur_col - 1] = 1; //익은 토마토로 바꾸기
			target--; //익지 않은 토마토 1개 줄어듦
			queue[++rear].row = cur_row; queue[rear].col = cur_col - 1; queue[rear].day = cur_day + 1; //해당 위치 queue에 add
		}
	}

	if (target != 0) { //queue가 빌 때까지 반복해도 익지 않은 토마토가 남아 있으면
		printf("-1");
	}
	else { //남은 토마토가 다 익은 상황
		printf("%d", cur_day); //queue에 있던 마지막 위치가 갖고 있는 day를 출력(최소 날짜)
	}

	//동적 할당되었던 메모리 해제
	for (i = 0; i < row; i++) {
		free(matrix[i]);
		free(visited[i]);
	}
	free(matrix); free(visited); free(queue);
}