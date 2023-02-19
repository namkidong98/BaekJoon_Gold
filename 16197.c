//�� ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct _pos {
	int a_row;
	int a_col;
	int b_row;
	int b_col;
	int time;
}pos;

int ROW, COL;
char temp[21][21] = { 0, };
int map[20][20] = { 0, };
pos start;
int d_row[4] = { -1, 0, 1, 0 };
int d_col[4] = { 0, 1, 0 ,-1 };

void move() {
	pos queue[1000000];
	int front, rear, a_row, a_col, b_row, b_col, cur_time, next_a_row, next_a_col, next_b_row, next_b_col, dir;
	front = rear = -1;

	queue[++rear].a_row = start.a_row; queue[rear].a_col = start.a_col;
	queue[rear].b_row = start.b_row; queue[rear].b_col = start.b_col; queue[rear].time = start.time;
	while (front != rear) {
		a_row = queue[++front].a_row; a_col = queue[front].a_col;
		b_row = queue[front].b_row; b_col = queue[front].b_col; cur_time = queue[front].time;

		if (cur_time >= 10) break;

		dir = 0;
		while (dir < 4) {
			next_a_row = a_row + d_row[dir]; next_a_col = a_col + d_col[dir];
			if (next_a_row < ROW && next_a_row >= 0 && next_a_col < COL && next_a_col >= 0) {
				if (map[next_a_row][next_a_col] == 1) { //���̶� �̵� ���ϸ� ���� ��ġ�� ���� ��ġ�� ����
					next_a_row = a_row; next_a_col = a_col;
				}
			}
			
			next_b_row = b_row + d_row[dir]; next_b_col = b_col + d_col[dir];
			if (next_b_row < ROW && next_b_row >= 0 && next_b_col < COL && next_b_col >= 0) {
				if (map[next_b_row][next_b_col] == 1) { //���̶� �̵� ���ϸ� ���� ��ġ�� ���� ��ġ�� ����
					next_b_row = b_row; next_b_col = b_col;
				}
			}
			
			dir++;

			//�� �� ��� ó���� ���� ��ġ��� queue�� �߰����� �ʱ�
			if (next_a_row == a_row && next_a_col == a_col && next_b_row == b_row && next_b_col == b_col) continue;

			//�� �� ��� �ٴڿ� ������ ��쵵 queue�� �߰����� �ʱ�
			if ((next_a_row >= ROW || next_a_row < 0 || next_a_col >= COL || next_a_col < 0) && (next_b_row >= ROW || next_b_row < 0 || next_b_col >= COL || next_b_col < 0)) continue;

			//�� �� ��� map �ȿ� �ִ� ���� queue�� �߰��ϱ�
			else if ((next_a_row < ROW && next_a_row >= 0 && next_a_col < COL && next_a_col >= 0) && (next_b_row < ROW && next_b_row >= 0 && next_b_col < COL && next_b_col >= 0)) {
				queue[++rear].a_row = next_a_row;
				queue[rear].a_col = next_a_col;
				queue[rear].b_row = next_b_row;
				queue[rear].b_col = next_b_col;
				queue[rear].time = cur_time + 1;
			}

			//������ ���� �� �� �ϳ��� ������ ���
			else {
				printf("%d", cur_time + 1);
				return;
			}
		}
	}
	printf("-1");
}

int main() {
	int count = 0;
	scanf("%d %d", &ROW, &COL);
	for (int i = 0; i < ROW; i++) {
		scanf("%s", &temp[i]);
	}
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (temp[i][j] == '.') map[i][j] = 0;
			if (temp[i][j] == '#') map[i][j] = 1;
			if (temp[i][j] == 'o') { //�� ������ ��쿡�� ��ġ�� ����
				map[i][j] = 2;
				if (count == 0) {
					start.a_row = i;
					start.a_col = j;
					count++;
				}
				else {
					start.b_row = i;
					start.b_col = j;
					start.time = 0;
				}
			}
		}
	}
	
	move();
}