//���� ����ö 2ȣ��(��� 3)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct node* node_pointer;
typedef struct node {
	int vertex;
	node_pointer link;
}node;

typedef struct pos {
	int vertex;
	int distance;
}pos;

int num_of_vertex;
node_pointer* group; // 1���� N����
int* edge_num; //�� ����ö������ ��ȯ�������� �Ÿ��� ����
int* ans; //�� ����ö������ ��ȯ�������� �Ÿ��� ����
int* visited; //�� ����ö���� �湮�Ǿ������� ����

int standard = 0;

int stack[3001];
int final_top = 0;

pos queue[3001];
int front = -1;
int rear = -1;

int end = 0;
void dfs(int index, int top) {
	int cur_index;
	node_pointer ptr;

	stack[++top] = index; visited[index] = 1;
	for (ptr = group[index]; ptr != NULL; ptr = ptr->link) {

		if (top >= 2 && ptr->vertex == standard) { //��ȯ���� �ϼ��Ǹ�
			for (int i = 0; i <= top; i++) { //���� stack�� �ִ� ����ö���� ans�� ��� 0���� ����
				ans[stack[i]] = 0;
			}
			ans[ptr->vertex] = 0;
			final_top = top;
			end = 1; //dfs ���� ǥ��
			return;
		}

		if (visited[ptr->vertex] == 0) {
			dfs(ptr->vertex, top);
		}

		if (end == 1) return;
	}
}

void bfs() {
	int index, cur_distance; node_pointer ptr;

	while (front != rear) {
		index = queue[++front].vertex; cur_distance = queue[front].distance; visited[index] = 1; ans[index] = cur_distance;
		
		for (ptr = group[index]; ptr != NULL; ptr = ptr->link) {
			if (visited[ptr->vertex] == 0) {
				queue[++rear].vertex = ptr->vertex; queue[rear].distance = cur_distance + 1;
			}
		}
	}
}

int main() {
	int vertex1, vertex2; 
	node_pointer temp;

	scanf("%d", &num_of_vertex); //��ü ����ö���� ���ڸ� �Է� �޴´�
	group = (node_pointer*)malloc(sizeof(node_pointer) * (num_of_vertex + 1));
	visited = (int*)malloc(sizeof(int) * (num_of_vertex + 1));
	ans = (int*)malloc(sizeof(int) * (num_of_vertex + 1));
	edge_num = (int*)malloc(sizeof(int) * (num_of_vertex + 1));
	
	for (int i = 0; i <= num_of_vertex; i++) { //�ʱ�ȭ
		group[i] = NULL;
		ans[i] = -1;
		visited[i] = 0;
		edge_num[i] = 0;
	}

	for (int i = 0; i < num_of_vertex; i++) { //����ö���� ���ڸ�ŭ ������ �Է� �޴´�
		scanf("%d %d", &vertex1, &vertex2);

		//vertex1 �������� vertex2 �߰�
		temp = (node_pointer)malloc(sizeof(node));
		temp->vertex = vertex2;
		temp->link = group[vertex1];
		group[vertex1] = temp;
		edge_num[vertex1]++;

		//vertex2 �������� vertex1 �߰�
		temp = (node_pointer)malloc(sizeof(node));
		temp->vertex = vertex1;
		temp->link = group[vertex2];
		group[vertex2] = temp;
		edge_num[vertex2]++;
	}
	
	for (int i = 1; i <= num_of_vertex; i++) { //Ʈ�� ������ �뼱�� ����� ��� �ش� �б����� �뼱�� 3�� �̻��� �ȴ�
		if (edge_num[i] >= 3) {
			standard = i; //������ �Ǵ� �б����� standard�� ����
			dfs(standard, -1);
			if (end == 1) { //3�� �̻��� �뼱�� ���� �б����� ���ÿ� ��ȯ���� �Ϻ��� ���
				break;
			}
			else {//3�� �̻��� �� �б��������� ��ȯ���� �Ϻδ� �ƴ� ���
				for (int j = 0; j <= num_of_vertex; j++) visited[j] = 0; //���� �б��������� dfs�� ���� visited �ʱ�ȭ
			}
		}
		
	}

	if (standard == 0) { //��ȯ���� �ְ� Ʈ�� ������ �뼱�� ���� ���
		for (int i = 1; i <= num_of_vertex; i++) printf("0 ");
		return 0;
	}

	for (int i = 0; i <= num_of_vertex; i++) visited[i] = 0; //bfs�� ���� visited �ʱ�ȭ
	for (int i = 0; i <= final_top; i++) visited[stack[i]] = 1; //��ȯ���� ��湮 �ϸ� �ȵǴ� visited 1�� ����

	for (int i = 0; i <= final_top; i++) { //��ȯ���� Ʈ�� ������ �뼱�� �б����� �Ǵ� ����ö ���� queue�� �ֱ�
		if (edge_num[stack[i]] >= 3) {
			queue[++rear].vertex = stack[i];
			queue[rear].distance = 0;
		}
	}
	bfs(); //��ȯ���� �б������� queue�� ���� ���·� bfs�� �̿��Ͽ� ���� ����ö������ �湮�Ͽ� �Ÿ� �����Ͽ� ans�� ����

	for (int i = 1; i <= num_of_vertex; i++) printf("%d ", ans[i]); //�� ���
}