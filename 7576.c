//�丶��(��� 5)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct pos {
	int row;
	int col;
	int day; //���� °����
}pos;

int main() {
	int row, col, i, j;
	int target = 0; //���� ���� ���� �丶��(0���� ����� ��)�� ����
	//case1: �ʱⰪ�� 0�̸� ��� �丶�䰡 ���� ���·� 0 ���
	//case2: 0�� �ƴϾ��ٰ� 0�� �Ǹ� while�� ���� & �ּҳ�¥ ���
	//case3: 0�� �ƴϾ��ٰ� 0�� �ȵǸ� ��� ������ ���ϴ� ���·� -1 ���

	scanf("%d %d", &col, &row);
	row += 2; col += 2;
	int** matrix = (int**)malloc(sizeof(int*) * row);
	for (i = 0; i < row; i++) matrix[i] = (int*)malloc(sizeof(int) * col);
	int** visited = (int**)malloc(sizeof(int*) * row);
	for (i = 0; i < row; i++) visited[i] = (int*)malloc(sizeof(int) * col);

	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			//�� �׵θ� -2�� ó���ؼ� ����
			if (i == 0 || i == row - 1 || j == 0 || j == col - 1) matrix[i][j] = -2;
			else {
				scanf("%d", &matrix[i][j]);
				if (matrix[i][j] == 0) target++; //���� ���� �丶�䰡 �Էµ� ������ 1���� ����
			}
			visited[i][j] = 0; //�湮 �������� 0, �湮������ 1 (0���� �ʱ�ȭ)
		}
	}
	
	pos* queue = (pos*)malloc(sizeof(pos) * (row - 2) * (col - 2));
	int front, rear, cur_row, cur_col, cur_day;
	front = rear = -1;

	//ù ���࿡�� 1�� ������ queue�� add
	for (i = 1; i < row - 1; i++) {
		for (j = 1; j < col - 1; j++) {
			if (matrix[i][j] == 1) {
				visited[i][j] = 1; //�ش� ��ġ �湮 ��� �����
				queue[++rear].row = i; queue[rear].col = j; queue[rear].day = 0;//�ش� ��ġ queue�� add
			}
		}
	}

	if (target == 0) { //���ʿ� ���� ���� �丶�䰡 ���� ���� --> ����� ������ ��� �丶�䰡 �;��ִ� ����
		printf("0");
		return 0;
	}

	while (front != rear) { //queue�� �� ������ �ݺ�
		cur_row = queue[++front].row; cur_col = queue[front].col; cur_day = queue[front].day; //queue���� ���ο� ��ġ ��������

		//4������ Ž���Ͽ� �̵��� �� �ִ� ���� �丶�信 �湮
		//�湮��� �����, �丶�並 ���� �丶��� �ٲٰ�, ���� ���� �丶�� ���� 1�� ���̰�, �ش� ��ġ�� queue�� add
		if (matrix[cur_row + 1][cur_col] == 0 && visited[cur_row + 1][cur_col] == 0) {
			visited[cur_row + 1][cur_col] = 1; //�湮 ��� �����
			matrix[cur_row + 1][cur_col] = 1; //���� �丶��� �ٲٱ�
			target--; //���� ���� �丶�� 1�� �پ��
			queue[++rear].row = cur_row + 1; queue[rear].col = cur_col; queue[rear].day = cur_day + 1; //�ش� ��ġ queue�� add
		}
		if (matrix[cur_row - 1][cur_col] == 0 && visited[cur_row - 1][cur_col] == 0) {
			visited[cur_row - 1][cur_col] = 1; //�湮 ��� �����
			matrix[cur_row - 1][cur_col] = 1; //���� �丶��� �ٲٱ�
			target--; //���� ���� �丶�� 1�� �پ��
			queue[++rear].row = cur_row - 1; queue[rear].col = cur_col; queue[rear].day = cur_day + 1; //�ش� ��ġ queue�� add
		}
		if (matrix[cur_row][cur_col + 1] == 0 && visited[cur_row][cur_col + 1] == 0) {
			visited[cur_row][cur_col + 1] = 1; //�湮 ��� �����
			matrix[cur_row][cur_col + 1] = 1; //���� �丶��� �ٲٱ�
			target--; //���� ���� �丶�� 1�� �پ��
			queue[++rear].row = cur_row; queue[rear].col = cur_col + 1; queue[rear].day = cur_day + 1; //�ش� ��ġ queue�� add
		}
		if (matrix[cur_row][cur_col - 1] == 0 && visited[cur_row][cur_col - 1] == 0) {
			visited[cur_row][cur_col - 1] = 1; //�湮 ��� �����
			matrix[cur_row][cur_col - 1] = 1; //���� �丶��� �ٲٱ�
			target--; //���� ���� �丶�� 1�� �پ��
			queue[++rear].row = cur_row; queue[rear].col = cur_col - 1; queue[rear].day = cur_day + 1; //�ش� ��ġ queue�� add
		}
	}

	if (target != 0) { //queue�� �� ������ �ݺ��ص� ���� ���� �丶�䰡 ���� ������
		printf("-1");
	}
	else { //���� �丶�䰡 �� ���� ��Ȳ
		printf("%d", cur_day); //queue�� �ִ� ������ ��ġ�� ���� �ִ� day�� ���(�ּ� ��¥)
	}

	//���� �Ҵ�Ǿ��� �޸� ����
	for (i = 0; i < row; i++) {
		free(matrix[i]);
		free(visited[i]);
	}
	free(matrix); free(visited); free(queue);
}