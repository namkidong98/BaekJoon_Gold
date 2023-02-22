//�� �μ��� �̵��ϱ�3 (��� 1)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define DAY 0
#define NIGHT 1

typedef struct pos {
	int row;
	int col;
	int time; //�̵��ϴµ� �ɸ� �ð��� ����
	int use; //���ݱ��� ��� ���� �ν������� ����
}pos;

int N, M, K;
int map[1001][1001];
int visited[1001][1001][11][2]; //ù��°�� row, �ι�°�� col, ����°�� �μ� ���� ����(use), �������� ������ �������� ��Ÿ��

int d_row[4] = { -1, 0, 1, 0 };
int d_col[4] = { 0, 1, 0, -1 };

void bfs() {
	pos queue[1001 * 1001 * 11 * 2];
	int front, rear, cur_row, cur_col, cur_time, cur_use, next_row, next_col, dir, today;
	front = rear = -1;

	queue[++rear].row = 0; queue[rear].col = 0; queue[rear].time = 1; queue[rear].use = 0; visited[0][0][0][DAY] = 1;

	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col; cur_time = queue[front].time; cur_use = queue[front].use;
		if ((cur_time % 2) == 0) today = NIGHT; //¦������ ����
		else today = DAY; //Ȧ������ ��

		if (cur_row == (N - 1) && cur_col == (M - 1)) break;

		dir = 0;
		while (dir < 4) {
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir++]; //����Ǵ� ���� ��ǥ�� ���

			if (next_row >= N || next_row < 0 || next_col >= M || next_col < 0 || cur_use > K) continue; //������ �ȵ����� �н�

			//case1: ���� ��� ���� 0�� �������� �̵� (�������ǿ��� �湮���� �ʾҴ�, ���� ���� ��� ���ϰ�)
			if (map[next_row][next_col] == 0 && visited[next_row][next_col][cur_use][DAY] == 0 && visited[next_row][next_col][cur_use][NIGHT] == 0) {
				queue[++rear].row = next_row; queue[rear].col = next_col; queue[rear].time = cur_time + 1; queue[rear].use = cur_use;
				visited[next_row][next_col][cur_use][today] = 1;
			}
			//case2: ���� �� && �μ� �� �ִ� �ѵ��� ������ ��, 1�� �������� ���� �μ��� �̵� (�������ǿ��� �湮���� �ʾҴ�)
			if (today == DAY && cur_use < K && map[next_row][next_col] == 1 && visited[next_row][next_col][cur_use + 1][today] == 0) {
				queue[++rear].row = next_row; queue[rear].col = next_col; queue[rear].time = cur_time + 1; queue[rear].use = cur_use + 1;
				visited[next_row][next_col][cur_use + 1][today] = 1;
			}
			//case3: ������ �ڸ����� �Ϸ� ���
			//������� 1: ������ ������ 2�� ����ϸ� ������ ��Ȳ�� �ݺ��Ǵ� �� �κ��� ������ �޾� ó���ؾ� �Ѵ�
			//������� 2: ���� �μ����� �ϴµ� ���̶� �� �μ��� ��� ���� �ƹ� ��� ���µ� ���� �ڸ����� �Ϸ� ����ϴ°� ť�� �������� ����ġ�� ť�� ����ȴ�
			if (today == NIGHT && cur_use < K && map[next_row][next_col] == 1 && visited[next_row][next_col][cur_use + 1][today] == 0) {
				queue[++rear].row = cur_row; queue[rear].col = cur_col; queue[rear].time = cur_time + 1; queue[rear].use = cur_use;
				visited[next_row][next_col][cur_use + 1][today] = 1;
			}
		}
	}

	if (cur_row == (N - 1) && cur_col == (M - 1)) printf("%d", cur_time); //��ǥ������ �����ϸ� �ҿ� �ð��� ���
	else printf("-1"); //�ƴϸ� -1�� ���
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