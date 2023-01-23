//토마토(골드 5) - 3차원
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct pos {
	int height;
	int row;
	int col;
	int day; //몇일 째인지
}pos;

int main() {
	int row, col, height, i, j, k;
	int target = 0; //아직 익지 않은 토마토(0으로 저장된 값)의 개수
	//case1: 초기값이 0이면 모든 토마토가 익은 상태로 0 출력
	//case2: 0이 아니었다가 0이 되면 while문 종료 & 최소날짜 출력
	//case3: 0이 아니었다가 0이 안되면 모두 익지는 못하는 상태로 -1 출력

	scanf("%d %d %d", &col, &row, &height);
	row += 2; col += 2; height += 2;
	int*** matrix = (int***)malloc(sizeof(int**) * height);
	int*** visited = (int***)malloc(sizeof(int**) * height);
	for (i = 0; i < height; i++) {
		matrix[i] = (int**)malloc(sizeof(int*) * row);
		visited[i] = (int**)malloc(sizeof(int*) * row);
	}
	for (i = 0; i < height; i++) {
		for (j = 0; j < row; j++) {
			matrix[i][j] = (int*)malloc(sizeof(int) * col);
			visited[i][j] = (int*)malloc(sizeof(int) * col);
		}
	}

	//초기 값 저장
	for (i = 0; i < height; i++) {
		for (j = 0; j < row; j++) {
			for (k = 0; k < col; k++) {
				//겉 테두리 -2로 처리해서 덮기
				if (i == 0 || i == height - 1 || j == 0 || j == row - 1 || k == 0 || k == col - 1) matrix[i][j][k] = -2;
				else {
					scanf("%d", &matrix[i][j][k]);
					if (matrix[i][j][k] == 0) target++; //익지 않은 토마토가 입력될 때마다 1개씩 증가
				}
				visited[i][j][k] = 0; //방문 안했으면 0, 방문했으면 1 (0으로 초기화)
			}
		}
	}

	pos* queue = (pos*)malloc(sizeof(pos) * (row - 2) * (col - 2) * (height - 2));
	int front, rear, cur_height, cur_row, cur_col, cur_day;
	front = rear = -1;

	//첫 시행에서 1인 지점을 queue에 add
	for (i = 1; i < height - 1; i++) {
		for (j = 1; j < row - 1; j++) {
			for (k = 1; k < col - 1; k++) {
				if (matrix[i][j][k] == 1) {
					visited[i][j][k] = 1; //해당 위치 방문 기록 남기기
					queue[++rear].height = i; queue[rear].row = j; queue[rear].col = k; queue[rear].day = 0;//해당 위치 queue에 add
				}
			}
		}
	}
	
	if (target == 0) { //애초에 익지 않은 토마토가 없는 상태 --> 저장될 때부터 모든 토마토가 익어있는 상태
		printf("0");
		return 0;
	}

	while (front != rear) { //queue가 빌 때까지 반복
		cur_height = queue[++front].height; cur_row = queue[front].row; cur_col = queue[front].col; cur_day = queue[front].day; //queue에서 새로운 위치 가져오기

		//6방향(위, 아래, 상, 하, 좌, 우)을 탐색하여 이동할 수 있는 곳의 토마토에 방문
		//방문기록 남기고, 토마토를 익은 토마토로 바꾸고, 익지 않은 토마토 개수 1개 줄이고, 해당 위치를 queue에 add
		if (matrix[cur_height][cur_row + 1][cur_col] == 0 && visited[cur_height][cur_row + 1][cur_col] == 0) { //상
			visited[cur_height][cur_row + 1][cur_col] = 1; //방문 기록 남기기
			matrix[cur_height][cur_row + 1][cur_col] = 1; //익은 토마토로 바꾸기
			target--; //익지 않은 토마토 1개 줄어듦
			queue[++rear].height = cur_height; queue[rear].row = cur_row + 1; queue[rear].col = cur_col; queue[rear].day = cur_day + 1; //해당 위치 queue에 add
		}
		if (matrix[cur_height][cur_row - 1][cur_col] == 0 && visited[cur_height][cur_row - 1][cur_col] == 0) { //하
			visited[cur_height][cur_row - 1][cur_col] = 1; //방문 기록 남기기
			matrix[cur_height][cur_row - 1][cur_col] = 1; //익은 토마토로 바꾸기
			target--; //익지 않은 토마토 1개 줄어듦
			queue[++rear].row = cur_row - 1; queue[rear].col = cur_col; queue[rear].height = cur_height; queue[rear].day = cur_day + 1; //해당 위치 queue에 add
		}
		if (matrix[cur_height][cur_row][cur_col + 1] == 0 && visited[cur_height][cur_row][cur_col + 1] == 0) { //우
			visited[cur_height][cur_row][cur_col + 1] = 1; //방문 기록 남기기
			matrix[cur_height][cur_row][cur_col + 1] = 1; //익은 토마토로 바꾸기
			target--; //익지 않은 토마토 1개 줄어듦
			queue[++rear].row = cur_row; queue[rear].col = cur_col + 1; queue[rear].height = cur_height; queue[rear].day = cur_day + 1; //해당 위치 queue에 add
		}
		if (matrix[cur_height][cur_row][cur_col - 1] == 0 && visited[cur_height][cur_row][cur_col - 1] == 0) { //좌
			visited[cur_height][cur_row][cur_col - 1] = 1; //방문 기록 남기기
			matrix[cur_height][cur_row][cur_col - 1] = 1; //익은 토마토로 바꾸기
			target--; //익지 않은 토마토 1개 줄어듦
			queue[++rear].row = cur_row; queue[rear].col = cur_col - 1; queue[rear].height = cur_height; queue[rear].day = cur_day + 1; //해당 위치 queue에 add
		}
		if (matrix[cur_height + 1][cur_row][cur_col] == 0 && visited[cur_height + 1][cur_row][cur_col] == 0) { //위
			visited[cur_height + 1][cur_row][cur_col] = 1; //방문 기록 남기기
			matrix[cur_height + 1][cur_row][cur_col] = 1; //익은 토마토로 바꾸기
			target--; //익지 않은 토마토 1개 줄어듦
			queue[++rear].row = cur_row; queue[rear].col = cur_col; queue[rear].height = cur_height + 1; queue[rear].day = cur_day + 1; //해당 위치 queue에 add
		}
		if (matrix[cur_height - 1][cur_row][cur_col] == 0 && visited[cur_height - 1][cur_row][cur_col] == 0) { //아래
			visited[cur_height - 1][cur_row][cur_col] = 1; //방문 기록 남기기
			matrix[cur_height - 1][cur_row][cur_col] = 1; //익은 토마토로 바꾸기
			target--; //익지 않은 토마토 1개 줄어듦
			queue[++rear].row = cur_row; queue[rear].col = cur_col; queue[rear].height = cur_height - 1; queue[rear].day = cur_day + 1; //해당 위치 queue에 add
		}
	}

	if (target != 0) { //queue가 빌 때까지 반복해도 익지 않은 토마토가 남아 있으면
		printf("-1");
	}
	else { //남은 토마토가 다 익은 상황
		printf("%d", cur_day); //queue에 있던 마지막 위치가 갖고 있는 day를 출력(최소 날짜)
	}
}