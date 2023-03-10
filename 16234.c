#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

typedef struct pos { //�� ������ ���� ����
	int row; //������ ��ġ�� ��
	int col; //������ ��ġ�� ��
	int people; //���� ������ �ִ� ����� ��
}pos;

pos queue[2500];
int N, L, R;
int map[50][50];
int visited[50][50];
int d_row[4] = { -1, 0, 1, 0 };
int d_col[4] = { 0, 1, 0, -1 };
int flag = 0; //�α� �̵��� �߻��ߴ����� ��Ÿ���� ��ǥ
int day = 0; //�� ���� ���������� ��Ÿ���� ����

void bfs(int row, int col) {
	int front, rear, cur_row, cur_col, cur_people, next_row, next_col, dir, diff;
	front = rear = -1;

	queue[++rear].row = row; queue[rear].col = col; queue[rear].people = map[row][col]; visited[row][col] = 1; //�ʱ� ��ġ�� queue�� �ֱ�
	while (front != rear) {
		cur_row = queue[++front].row; cur_col = queue[front].col; cur_people = queue[front].people; //queue���� ������ ��ġ ��������

		dir = 0;
		while (dir < 4) {
			next_row = cur_row + d_row[dir]; next_col = cur_col + d_col[dir++]; //4���� ���⿡ ���� ���� ��ǥ�� ����
			if (next_row < 0 || next_row >= N || next_col < 0 || next_col >= N) continue; //���� ���� ��ǥ�� ������ ����� �н�

			diff = (int)abs(map[next_row][next_col] - map[cur_row][cur_col]); //���� ������ ���� ��ǥ�� ������ �α� ���� diff�� ���

			if (diff >= L && diff <= R && visited[next_row][next_col] == 0) { //diff�� L�� R ������ ���̰� ���� �湮���� ���� ������� queue�� �ֱ�
				queue[++rear].row = next_row; queue[rear].col = next_col; queue[rear].people = map[next_row][next_col];
				visited[next_row][next_col] = 1;
			}
		}
	}

	int total = 0;
	if (rear != 0) { //rear�� 0�� �ƴ� ��, �� �α� �̵��� �Ͼ ���
		for (int i = 0; i <= rear; i++) {
			//printf("%d %d %d\n", i, queue[i].row, queue[i].col);
			total += queue[i].people;
		}
		total /= rear + 1; //total�� ������ ���� ������ �α� ���� ��� ���ؼ� ������ ������ ������(rear�� 0���� �����̴� 1�� ���ؼ� ������)
		for (int i = 0; i <= rear; i++) {
			map[queue[i].row][queue[i].col] = total; //�׸��� �ش� ������ ������ total ���� �ִ´�
		}
		flag = 1; //�α� �̵��� �Ͼ�ٴ� ǥ��
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

		if (flag == 0) break; //�α� �̵��� ���� ��� ���� ����

		else { //�α� �̵��� �ִ� ���
			day++; //��¥�� �Ϸ� �ø���
			flag = 0; //���� ������ ���� flag�� 0���� �����ϰ�

			for (int i = 0; i < N; i++) { //visited�� �ٽ� ����ϴ� 0���� �ʱ�ȭ�Ѵ�
				for (int j = 0; j < N; j++) {
					visited[i][j] = 0;
				}
			}
		}

	}

	printf("%d", day); //�α� �̵��� �� �̻� �Ͼ�� �ʾ� while loop�� �������� ������ day�� ����Ѵ�
}
