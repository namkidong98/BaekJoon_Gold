//���ڿ� ����
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define TOTAL 2000 //���ڿ��� ���� ����
#define LIMIT 2 //�� �� ��� ���� ����

void new_string(char* string, int front, int rear) {
	int temp_front, temp_rear;
	int count = 0;

	while (front != rear) {
		//���۰� ���� �ٸ� ���
		if (string[front] < string[rear]) { //���� �� ������ ���(�ƽ�Ű�ڵ� ����)
			printf("%c", string[front]); //���� ���
			front++;
			count++;
		}
		else if (string[front] > string[rear]) { //�ڰ� �� ������ ���
			printf("%c", string[rear]); //�ڸ� ���
			rear--;
			count++;
		}

		//���۰� ���� ���� ���
		else {
			//�� ���������� ���� �� ���� ���� ���� �ִ� ���� ���
			temp_front = front + 1;
			temp_rear = rear - 1;
			while (string[temp_front] == string[temp_rear]) {
				temp_front++;
				temp_rear--;
			}
			if (string[temp_front] < string[temp_rear]) {
				printf("%c", string[front]);
				front++;
				count++;
			}
			else if (string[temp_front] > string[temp_rear]) {
				printf("%c", string[rear]);
				rear--;
				count++;
			}
		}
		if (count == LIMIT) {
			printf("\n");
			count = 0;
		}
		
	}
	//front�� rear�� ������ ����(������ ���� 1�� ���� ����)
	printf("%c", string[front]);
}

int main() {
	int i, num;
	char string[TOTAL + 1];
	int front, rear;

	scanf("%d", &num);
	for (i = 0; i < num; i++) {
		scanf("\n%c", &string[i]);
	}
	front = 0;
	rear = num - 1;
	new_string(string, front, rear);
}