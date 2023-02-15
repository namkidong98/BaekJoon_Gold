//���� (��� 3)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* node_pointer;
typedef struct node {
	int row;
	int col;
	int group_num;
	node_pointer link[4]; //0�� ����, 1�� ������, 2�� �Ʒ���, 3�� ����
}room;

typedef struct pos {
	int row;
	int col;
}pos;

node_pointer** map;
int group_room_num[2500];
int** visited;
int ROW, COL; //��ü ���� ��, ���� �����ϴ� ����
int count = 0; //���� �ִ� ���� ������ �����ϴ� ����
int max = 0; //�ִ� ���� ũ�⸦ �����ϴ� ����, ���߿��� �� ���� ���� �ִ� ���� ũ�⸦ �����ϴµ� ���


void bfs(int row, int col) {
	pos queue[2500];
	node_pointer ptr;
	int front, rear, cur_row, cur_col, next_row, next_col, dir;
	front = rear = -1;

	queue[++rear].row = row; queue[rear].col = col; //�ʱ� ��ġ add queue
	map[row][col]->group_num = count; visited[row][col] = 1;
	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col;
		ptr = map[cur_row][cur_col];
		ptr->group_num = count;

		for (dir = 0; dir < 4; dir++) {
			if (map[cur_row][cur_col]->link[dir] != NULL) { //�ش� �������� ����� ���� �ִٸ�
				next_row = map[cur_row][cur_col]->link[dir]->row;
				next_col = map[cur_row][cur_col]->link[dir]->col;
				if (visited[next_row][next_col] == 0) { //�׸��� �ش� ���� ���� �湮���� �ʾҴٸ�
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

	//�Է� �ޱ� ���� row, col�� ���� �� ����� ��ǥ ���� �� �ʱ�ȭ
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			temp = (node_pointer)malloc(sizeof(room));
			temp->row = i; temp->col = j; //�⺻ ��ǥ ����
			for (int k = 0; k < 4; k++) temp->link[k] = NULL; temp->group_num = -1; //�ʱ�ȭ
			map[i][j] = temp;
			visited[i][j] = 0; //�湮 ��� �ʱ�ȭ
		}
	}

	//�Է� ���� �޾Ƽ� �� �渶�� 4���⿡ ���� �� ���θ� ����
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			scanf("%d", &number);
			number = 15 - number;

			if (number >= 8) { //�Ʒ��� ���� ���� ���
				if (i + 1 < ROW) {
					map[i][j]->link[2] = map[i + 1][j];
				}
				number -= 8;
			}
			if (number >= 4) { //�����ʿ� ���� ���� ���
				if (j + 1 < COL) {
					map[i][j]->link[1] = map[i][j + 1];
				}
				number -= 4;
			}
			if (number >= 2) { //���ʿ� ���� ���� ���
				if (i - 1 >= 0) {
					map[i][j]->link[0] = map[i - 1][j];
				}
				number -= 2;
			}
			if (number >= 1) { //���ʿ� ���� ���� ���
				if (j - 1 >= 0) {
					map[i][j]->link[3] = map[i][j - 1];
				}
				number -= 1;
			}

			if (number != 0) { //���� ó��
				fprintf(stderr, "Error in input");
				exit(1);
			}
		}
	}

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (visited[i][j] == 0) { //�ش� ������ �湮���� �ʾҴٸ�
				bfs(i, j); //�ش� ������ �������� bfs ����
			}
		}
	}
	printf("%d\n%d\n", count, max); //���� ���� �� ���� ����(���� ������� ���� ������ ����)�� �ִ� ���� ����
	
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (i - 1 >= 0) { //����
				if (map[i][j]->group_num != map[i - 1][j]->group_num) { //�ٸ� �׷�� ���ϸ�
					result = group_room_num[map[i][j]->group_num] + group_room_num[map[i - 1][j]->group_num];
					if (result > max) max = result;
				}
			}
			if (j + 1 < COL) { //������
				if (map[i][j]->group_num != map[i][j + 1]->group_num) { //�ٸ� �׷�� ���ϸ�
					result = group_room_num[map[i][j]->group_num] + group_room_num[map[i][j + 1]->group_num];
					if (result > max) max = result;
				}
			}
			if (i + 1 < ROW) { //�Ʒ���
				if (map[i][j]->group_num != map[i + 1][j]->group_num) { //�ٸ� �׷�� ���ϸ�
					result = group_room_num[map[i][j]->group_num] + group_room_num[map[i + 1][j]->group_num];
					if (result > max) max = result;
				}
			}
			if (j - 1 >= 0) { //����
				if (map[i][j]->group_num != map[i][j - 1]->group_num) { //�ٸ� �׷�� ���ϸ�
					result = group_room_num[map[i][j]->group_num] + group_room_num[map[i][j - 1]->group_num];
					if (result > max) max = result;
				}
			}
		}
	}
	printf("%d", max);

}