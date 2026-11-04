#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct Stack {
	int data;
	struct Stack* next;
} Stack;

int Push(int, Stack*);
int Pop(Stack*, int*);
int DeleteStack(Stack*);
int EvaluatePostfix(const char*, Stack*, int*);
int IsNumber(const char*);
int IsOperator(const char*);

int main(void) {
	Stack head = { 0 };

	int result;
	if (EvaluatePostfix("postfix.txt", &head, &result) == 0) {
		printf("Rjesenje je: %d\n", result);
	}
	else {
		puts("Doslo je do greske pri evaluaciji postfix izraza!");
	}

	DeleteStack(&head);

	return 0;
}

int Push(int data, Stack* head) {
	Stack* newNode = (Stack*)malloc(sizeof(Stack));
	if (!newNode) {
		puts("Greska pri alokaciji memorije!");
		return -1;
	}

	newNode->data = data;
	newNode->next = head->next;
	head->next = newNode;

	return 0;
}

int Pop(Stack* head, int* data) {
	if (!head->next) {
		puts("Stog je prazan!");
		return -1;
	}

	Stack* temp = head->next;
	*data = temp->data;
	head->next = temp->next;

	free(temp);

	return 0;
}

int DeleteStack(Stack* head) {
	while (head->next) {
		Stack* temp = head->next;
		head->next = temp->next;
		free(temp);
	}

	return 0;
}

int IsNumber(const char* str) {
	if (str[0] == '\0') return 0;

	int val = 0;
	int len = strlen(str);

	if ((len <= 1) && (str[0] == '+' || str[0] == '-')) {
		return 0;
	}
	else if ((len > 1) && (str[0] == '+' || str[0] == '-')) {
		val = 1;
	}

	for (int i = val; i < len; i++) {
		if (!isdigit(str[i])) {
			return 0;
		}
	}

	return 1;
}

int IsOperator(const char* str) {
	return (strcmp(str, "+") == 0 || strcmp(str, "-") == 0 || strcmp(str, "*") == 0 || strcmp(str, "/") == 0) ? 1 : 0;
}

int EvaluatePostfix(const char* fileName, Stack* head, int* result) {
	if (head->next) DeleteStack(head);

	FILE* fp = fopen(fileName, "r");
	if (!fp) {
		puts("Greska pri otvaranju datoteke!");
		return -1;
	}

	char buffer[MAX];
	while (fscanf(fp, "%s", buffer) == 1) {
		if (IsOperator(buffer)) {

			int right;
			int left;

			if (Pop(head, &right) != 0) {
				puts("Doslo je do greske pri skidanju elemenata sa stoga!");
				DeleteStack(head);
				fclose(fp);
				return -1;
			}

			if (Pop(head, &left) != 0) {
				puts("Doslo je do greske pri skidanju elemenata sa stoga!");
				DeleteStack(head);
				fclose(fp);
				return -1;
			}

			if (strcmp(buffer, "+") == 0) {
				Push(left + right, head);
			}
			else if (strcmp(buffer, "-") == 0) {
				Push(left - right, head);
			}
			else if (strcmp(buffer, "*") == 0) {
				Push(left * right, head);
			}
			else if (strcmp(buffer, "/") == 0) {
				if (right != 0) {
					Push(left / right, head);
				}
				else {
					puts("Dijeljenje s nulom nije moguce!");
					DeleteStack(head);
					fclose(fp);
					return -1;
				}
			}
		}
		else if (IsNumber(buffer)) {
			Push(atoi(buffer), head);
		}
		else {
			puts("Postfix izraz je u neispravnom formatu!");
			DeleteStack(head);
			fclose(fp);
			return -1;
		}
	}

	fclose(fp);

	if (head->next && head->next->next) {
		puts("Ostalo je previse operanada na stogu, neispravan format postfix izraza!");
		DeleteStack(head);
		return -1;
	}

	if (Pop(head, result) != 0) {
		puts("Doslo je do greske pri skidanju elemenata sa stoga!");
		DeleteStack(head);
		return -1;
	}

	return 0;
}