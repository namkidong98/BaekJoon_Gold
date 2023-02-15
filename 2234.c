//성곽 (골드 3)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* node_pointer;
typedef struct node {
	int row;
	int col;
	int group_num;
	node_pointer link[4]; //0은 위쪽, 1은 오른쪽, 2는 아래쪽, 3은 왼쪽
}room;

typedef struct pos {
	int row;
	int col;
}pos;

node_pointer** map;
int group_room_num[2500];
int** visited;
int ROW, COL; //전체 성의 행, 열을 저장하는 변수
int count = 0; //성에 있는 방의 개수를 저장하는 변수
int max = 0; //최대 방의 크기를 저장하는 변수, 나중에는 두 방을 합쳐 최대 방의 크기를 저장하는데 사용


void bfs(int row, int col) {
	pos queue[2500];
	node_pointer ptr;
	int front, rear, cur_row, cur_col, next_row, next_col, dir;
	front = rear = -1;

	queue[++rear].row = row; queue[rear].col = col; //초기 위치 add queue
	map[row][col]->group_num = count; visited[row][col] = 1;
	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col;
		ptr = map[cur_row][cur_col];
		ptr->group_num = count;

		for (dir = 0; dir < 4; dir++) {
			if (map[cur_row][cur_col]->link[dir] != NULL) { //해당 방향으로 연결된 방이 있다면
				next_row = map[cur_row][cur_col]->link[dir]->row;
				next_col = map[cur_row][cur_col]->link[dir]->col;
				if (visited[next_row][next_col] == 0) { //그리고 해당 방이 아직 방문되지 않았다면
					queue[++rear].row = next_row;
					queue[rear].col = next_col;
					visited[next_row][next_col] = 1;
				}
			}
		}
	}

	group_room_num[count] = rear + 1;
	if (group_room_num[count] > max) max = group_room_num[count];
	count++;
}

int main() {
	int number, result;
	node_pointer temp;

	scanf("%d %d", &COL, &ROW);
	map = (node_pointer**)malloc(sizeof(node_pointer*) * ROW);
	for (int i = 0; i < ROW; i++) map[i] = (node_pointer*)malloc(sizeof(node_pointer) * COL);
	visited = (int**)malloc(sizeof(int*) * ROW);
	for (int i = 0; i < ROW; i++) visited[i] = (int*)malloc(sizeof(int) * COL);

	//입력 받기 전에 row, col에 맞춰 방 만들고 좌표 저장 및 초기화
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			temp = (node_pointer)malloc(sizeof(room));
			temp->row = i; temp->col = j; //기본 좌표 저장
			for (int k = 0; k < 4; k++) temp->link[k] = NULL; temp->group_num = -1; //초기화
			map[i][j] = temp;
			visited[i][j] = 0; //방문 기록 초기화
		}
	}

	//입력 값을 받아서 각 방마다 4방향에 대한 벽 여부를 저장
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			scanf("%d", &number);
			number = 15 - number;

			if (number >= 8) { //아래쪽 벽이 없는 경우
				if (i + 1 < ROW) {
					map[i][j]->link[2] = map[i + 1][j];
				}
				number -= 8;
			}
			if (number >= 4) { //오른쪽에 벽이 없는 경우
				if (j + 1 < COL) {
					map[i][j]->link[1] = map[i][j + 1];
				}
				number -= 4;
			}
			if (number >= 2) { //위쪽에 벽이 없는 경우
				if (i - 1 >= 0) {
					map[i][j]->link[0] = map[i - 1][j];
				}
				number -= 2;
			}
			if (number >= 1) { //왼쪽에 벽이 없는 경우
				if (j - 1 >= 0) {
					map[i][j]->link[3] = map[i][j - 1];
				}
				number -= 1;
			}

			if (number != 0) { //오류 처리
				fprintf(stderr, "Error in input");
				exit(1);
			}
		}
	}

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (visited[i][j] == 0) { //해당 지점이 방문되지 않았다면
				bfs(i, j); //해당 지점을 기준으로 bfs 실행
			}
		}
	}
	printf("%d\n%d\n", count, max); //성곽 내에 총 방의 개수(서로 연결되지 않은 집합의 개수)와 최대 방의 넓이
	
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (i - 1 >= 0) { //위쪽
				if (map[i][j]->group_num != map[i - 1][j]->group_num) { //다른 그룹과 접하면
					result = group_room_num[map[i][j]->group_num] + group_room_num[map[i - 1][j]->group_num];
					if (result > max) max = result;
				}
			}
			if (j + 1 < COL) { //오른쪽
				if (map[i][j]->group_num != map[i][j + 1]->group_num) { //다른 그룹과 접하면
					result = group_room_num[map[i][j]->group_num] + group_room_num[map[i][j + 1]->group_num];
					if (result > max) max = result;
				}
			}
			if (i + 1 < ROW) { //아래쪽
				if (map[i][j]->group_num != map[i + 1][j]->group_num) { //다른 그룹과 접하면
					result = group_room_num[map[i][j]->group_num] + group_room_num[map[i + 1][j]->group_num];
					if (result > max) max = result;
				}
			}
			if (j - 1 >= 0) { //왼쪽
				if (map[i][j]->group_num != map[i][j - 1]->group_num) { //다른 그룹과 접하면
					result = group_room_num[map[i][j]->group_num] + group_room_num[map[i][j - 1]->group_num];
					if (result > max) max = result;
				}
			}
		}
	}
	printf("%d", max);

}