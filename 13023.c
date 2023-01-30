//ABCDE (��� 5)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _node* node_pointer;
typedef struct _node {
	int index;
	node_pointer link;
}node;
node_pointer* group; //��� �� ��ŭ ������ ģ�� �������� �����ϴ� ����
int* visited; //�ش� ����� �湮�ߴ����� ��Ÿ���� ����
int flag = 0; //0�̸� ģ�����谡 ����, 1�̸� ģ�����谡 �ִ�

void dfs(int index, int depth) {
	node_pointer ptr;
	visited[index] = 1;

	if (depth >= 5) {
		flag = 1;
		return;
	}

	for (ptr = group[index]; ptr != NULL; ptr = ptr->link) {
		if (flag == 1) return;
		if (visited[ptr->index] == 0) {
			dfs(ptr->index, depth + 1);
		}
	}
	visited[index] = 0; //�ش� ����� ���� �� ���� ���ٸ� ���ư��� �Ǵµ�, �� �� �ش� ������ �湮 ǥ�� �Ǿ� ������ ����� üũ�� �� �ȴ�
	return;
}

int main() {
	int N, M; //N�� ��� ��, M�� ģ�� ���� ��
	node_pointer temp, ptr;
	int vertex1, vertex2;
	scanf("%d %d", &N, &M);
	group = (node_pointer*)malloc(sizeof(node_pointer) * N);
	visited = (int*)malloc(sizeof(int) * N);

	//group�� visited�� 0���� �ʱ�ȭ
	for (int i = 0; i < N; i++) {
		group[i] = NULL;
		visited[i] = 0;
	}

	//ģ�� ���� �� ��ŭ ���� ���� group�� �����ϱ�
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &vertex1, &vertex2);

		temp = (node_pointer)malloc(sizeof(node));
		temp->index = vertex2;
		temp->link = group[vertex1];
		group[vertex1] = temp;

		temp = (node_pointer)malloc(sizeof(node));
		temp->index = vertex1;
		temp->link = group[vertex2];
		group[vertex2] = temp;
	}

	for (int i = 0; i < N; i++) {
		dfs(i, 1); //���� ������ 0��, 1��, 2��...�̷��� �ٲ㰡�鼭 N���� ���������� �������� �ľ�
		if (flag == 1) break;
	}

	printf("%d", flag);
}