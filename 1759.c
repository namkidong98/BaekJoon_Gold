//��ȣ �����(���5, ���Ʈ ����)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct {
	char character; //���� ��
	int vowel; //0�̸� ����, 1�̸� ���� --> ���� ��
	int use; //1�̸� ���� ��, 0�̸� �� �Ȱ� --> ��ȭ�ϴ� ��
}alphabet;

int L, C;
alphabet string[16];

void choose(int left, int vowel, int cons, int current) { //L���� ���� ���ڰ���, ���� ���Ե� ��������, ���� ���Ե� ��������, ���� ��ġ
	if (left == 0 && vowel >= 1 && cons >= 2) { //L����ŭ ����� ������ 1�� �̻�, ������ 2�� �̻� ���Ե� ��� --> ���
		for (int i = 0; i < C; i++) {
			if (string[i].use == 1) printf("%c", string[i].character);
		}
		printf("\n");
	}

	if (left > 0) {
		for (int i = current; i < C; i++) {
			if (string[i].use == 0) {
				string[i].use = 1;
				if (string[i].vowel == 1) choose(left - 1, vowel + 1, cons, i + 1);
				else choose(left - 1, vowel, cons + 1, i + 1);
				string[i].use = 0;
			}
		}
	}
}

int main() {
	char temp;
	scanf("%d %d", &L, &C);
	for (int i = 0; i < C; i++) {
		scanf(" %c", &string[i].character);
	}

	//���� ������ �°� ���� �� �ʱ�ȭ
	for (int i = 0; i < C - 1; i++) {
		for (int j = i + 1; j < C; j++) {
			if (string[i].character > string[j].character) { //���� �������� j��°�� �ռ��� SWAP
				temp = string[i].character;
				string[i].character = string[j].character;
				string[j].character = temp;
			}
		}
	}
	for (int i = 0; i < C; i++) {
		if (string[i].character == 'a' || string[i].character == 'e' || string[i].character == 'i' || string[i].character == 'o' || string[i].character == 'u') string[i].vowel = 1;
		else string[i].vowel = 0;
		string[i].use = 0; //��� �ȵ����� �ʱ�ȭ
	}

	choose(L, 0, 0, 0); //L�� ���ڸ� �����ϰ�, ���Ե� ���� ���� 0��, ���Ե� ���� ���� 0��, 0��°���� ����
}