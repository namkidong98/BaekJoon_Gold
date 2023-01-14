//���ڿ� ����(���� 2)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	int i, j;
	char string[1000001];
	char target[37];
	scanf("%s", string);
	scanf("%s", target);
	int str_len = strlen(string);
	int tar_len = strlen(target);
	char* str_stack;
	char* prt_stack;
	str_stack = (char*)malloc(sizeof(char) * str_len);
	prt_stack = (char*)malloc(sizeof(char) * str_len);
	int str_top = -1;
	int prt_top = -1;
	
	//str_stack ����(���� ���;� �ϴ� string�� ó���� �� ���� ������ ���ÿ� �ݴ�� �׾Ƴ���)
	for (i = str_len - 1; i >= 0; i--) {
		str_stack[++str_top] = string[i];
	}

	while (str_top != -1) {
		if (str_stack[str_top] == target[0]) { //���� ���ڿ��� ���۰� ������
			for (i = 0; i < tar_len; i++) {
				if (str_stack[str_top - i] != target[i]) break;
			}
			if (i == tar_len) { //���� ���ڿ��� ��ġ�ϸ�
				str_top -= tar_len; //�ش� ���̸�ŭ ���� ���ڿ��� pop
			}
			else prt_stack[++prt_top] = str_stack[str_top--]; //���� ���ڿ��� ��ġ���� ������ �׳� push

		}
		else prt_stack[++prt_top] = str_stack[str_top--]; //str_stack���� pop�ؼ� prt_stack�� push

		//prt_stack�� ���� ���ڿ��� ���� ���ڿ��� �Ǿ����� Ȯ��(������ Ȯ��)
		if (prt_stack[prt_top] == target[tar_len - 1]) { 
			for (j = 0; j < tar_len; j++) {
				if (prt_stack[prt_top - j] != target[tar_len - j - 1]) break;
			}

			if (j == tar_len) { //prt_stack���� ���� ���ڿ��� �ϼ��Ǹ�
				prt_top -= tar_len; //���� ���ڿ� ���̸�ŭ prt_stack���� pop
			}
		}
	}

	if (prt_top == -1) printf("FRULA");
	else {
		for (i = 0; i <= prt_top; i++) {
			printf("%c", prt_stack[i]);
		}
	}
	return 0;
}

//ó������ �Ʒ��� ���� ������ �Ⱦ��� �����ߴµ�, �̷��� �����ϴ� ��� target(���� ���ڿ�)�� ������� ���� string�� ������ ���� �ϴ°� ��������
//�ð� ���⵵�� ��������. ���� 2�ʶ�� �ð� ������ ��Ű�� ���� �ð� �ʰ� ������ �߻��Ѵ�.
/*
for (i = 0; i < str_len; i++) {
	if (string[i] == target[0]) {
		for (j = 0; j < tar_len; j++) {
			if (string[i + j] != target[j]) break;
		}
	}
	if (j == tar_len) { //���� ���ڿ��� �߰� �Ǿ��ٴ� ��
		for (k = i; k < str_len - 2; k++) {
			string[k] = string[k + tar_len];
		}
		str_len -= tar_len; //���� ���� ���ڿ��� ���̰� �پ�����
		i -= tar_len; //�޺κ��� ���� �پ ���� ���ڿ��� �� ���� ������
		j = 0;
	}
}
*/