//문자열 생성
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define TOTAL 2000 //문자열의 길이 제한
#define LIMIT 2 //한 줄 출력 길이 제한

void new_string(char* string, int front, int rear) {
	int temp_front, temp_rear;
	int count = 0;

	while (front != rear) {
		//시작과 끝이 다른 경우
		if (string[front] < string[rear]) { //앞이 더 먼저인 경우(아스키코드 기준)
			printf("%c", string[front]); //앞을 출력
			front++;
			count++;
		}
		else if (string[front] > string[rear]) { //뒤가 더 먼저인 경우
			printf("%c", string[rear]); //뒤를 출력
			rear--;
			count++;
		}

		//시작과 끝이 같은 경우
		else {
			//그 다음꺼까지 비교한 뒤 먼저 오는 것이 있는 쪽을 출력
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
	//front와 rear이 같아진 상태(마지막 문자 1개 남은 상태)
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