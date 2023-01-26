//ġŲ ���(��� 5, ���Ʈ����, ��Ʈ��ŷ)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int row;
	int col;
	int d; //distance
}home;

typedef struct {
	int use; //0�̸� ���, 1�̸� ����
	int row;
	int col;
}shop;

int N, M; int MIN = 250000; //���� ġŲ�Ÿ��� �ּڰ�
home* house; int h_num = 0;
shop* chicken; int c_num = 0;
int** map;

void calculate() { //������ ġŲ������ ��ġ�� ������� ������ ġŲ �Ÿ��� ����ϴ� �Լ�
	int total = 0; //������ ġŲ �Ÿ��� �����ϴ� ����
	int min = 0; int distance;

	for (int i = 0; i < h_num; i++) { //������ ������
		min = 250000;
		for (int j = 0; j < c_num; j++) { //������ ġŲ�������� �Ÿ��� ���ؼ� ����
			if (chicken[j].use == 0) continue; //����� ġŲ���� �ǳʶ�
			distance = abs(house[i].row - chicken[j].row) + abs(house[i].col - chicken[j].col);
			if (distance < min) min = distance;
		}
		house[i].d = min; //�ش� ���� �ּ� ġŲ �Ÿ�
	}

	for (int i = 0; i < h_num; i++) {
		total += house[i].d;
	}

	if (total < MIN) MIN = total; //���� �ּڰ����� �ش� map ��� ������ ġŲ �Ÿ��� ������ �ּڰ��� ����
}

void choose(int count, int recent) { //count: ���־� �ϴ� ġŲ�� ����
	if (count == 0) {
		calculate();
	}

	for (int i = recent; i < c_num; i++) {
		if (count > 0 && chicken[i].use != 0) {
			chicken[i].use = 0; //����� ������ ����
			choose(count - 1, i); //��Ͱ� ������ count - 1 ���� ���ϰ� ���� ĭ���� �Ѿ�� ��
			chicken[i].use = 1; //�ش� ���࿡�� ������� �����ߴ� ���Ը� ���󺹱��ϱ� = ��� �Լ��� �������� ������ �ߴ� ��ȭ(52������)�� ���
		}
	}
}

int main() {
	scanf("%d %d", &N, &M);
	map = (int**)malloc(sizeof(int*) * N);
	for (int i = 0; i < N; i++) map[i] = (int*)malloc(sizeof(int) * N);
	house = (home*)malloc(sizeof(home) * N * 2); //���� 2N�� ���� �ʴ´�
	chicken = (shop*)malloc(sizeof(shop) * 13); //ġŲ���� M�̻� 13�����̴�
	
	//������ ������ �޾ƿͼ� ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &map[i][j]);
			if (map[i][j] == 1) { //���� ������ ����
				house[h_num].row = i;
				house[h_num++].col = j;
			}
			if (map[i][j] == 2) { //ġŲ���� ������ ����
				chicken[c_num].row = i;
				chicken[c_num].col = j;
				chicken[c_num++].use = 1; //���Ǵ� ������ �ʱ�ȭ
			}
		}
	}

	choose(c_num - M, 0); //ġŲ���� ���� �Լ�
	printf("%d", MIN);
}