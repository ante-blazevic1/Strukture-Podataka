#include <stdio.h>
#include <stdlib.h>

typedef struct _Poly {
	int koef;
	int exp;
	struct _Poly* next;
} Poly;

int sortedInput(int, int, Poly*);
int multiplyPoly(Poly*, Poly*, Poly*);
int sumPoly(Poly*, Poly*, Poly*);
int printList(Poly*);
int deleteList(Poly*);

int main(void) {

	FILE* fp = fopen("polinomi.txt", "r");
	if (!fp) {
		puts("Greska pri otvaranju datoteke!");
		return -1;
	}

	Poly headFirst = { 0 };
	Poly headSecond = { 0 };
	Poly headResultSum = { 0 };
	Poly headResultProduct = { 0 };

	int koef;
	int exp;

	while (fscanf(fp, "%d %d", &koef, &exp) == 2) {

		sortedInput(koef, exp, &headFirst);

		if (fgetc(fp) == '\n') {
			break;
		}
	}

	while (fscanf(fp, "%d %d", &koef, &exp) == 2) {

		sortedInput(koef, exp, &headSecond);
	}

	fclose(fp);

	multiplyPoly(&headFirst, &headSecond, &headResultProduct);
	sumPoly(&headFirst, &headSecond, &headResultSum);

	printf("Umnozak polinoma: ");
	printList(&headFirst);
	printf("\ni polinoma: ");
	printList(&headSecond);
	printf("\nje polinom: ");
	printList(&headResultProduct);
	
	printf("\n\n");

	printf("Zbroj polinoma: ");
	printList(&headFirst);
	printf("\ni polinoma: ");
	printList(&headSecond);
	printf("\nje polinom: ");
	printList(&headResultSum);

	printf("\n");

	deleteList(&headFirst);
	deleteList(&headSecond);
	deleteList(&headResultProduct);
	deleteList(&headResultSum);

	return 0;
}

int sortedInput(int koef, int exp, Poly* head) {

	if (koef == 0) return 0;

	Poly* curr = head;

	while (curr->next) {
		if (curr->next->exp > exp) {
			curr = curr->next;
		}
		else if (curr->next->exp == exp) {
			curr->next->koef += koef;

			if (curr->next->koef == 0) {
				Poly* temp = curr->next;
				curr->next = temp->next;
				free(temp);
			}

			return 0;
			
		}
		else {
			break;
		}
	}

	Poly* newPoly = (Poly*)malloc(sizeof(Poly));
	if (!newPoly) {
		puts("Greska pri alokaciji memorije!");
		return -1;
	}

	newPoly->koef = koef;
	newPoly->exp = exp;

	newPoly->next = curr->next;
	curr->next = newPoly;

	return 0;
}

int sumPoly(Poly* headFirst, Poly* headSecond, Poly* headResultSum) {
	Poly* p1 = headFirst->next;
	Poly* p2 = headSecond->next;

	if (!p1 && !p2) {
		puts("Obje liste su prazne, nije moguce zbrojiti polinome!");
		return -1;
	}

	while (p1 && p2) {

		if (p1->exp == p2->exp) {
			if ((p1->koef + p2->koef) != 0) {
				sortedInput(p1->koef + p2->koef, p1->exp, headResultSum);
			}
			p1 = p1->next;
			p2 = p2->next;
		}
		else if (p1->exp < p2->exp) {
			sortedInput(p2->koef, p2->exp, headResultSum);
			p2 = p2->next;
		}
		else {
			sortedInput(p1->koef, p1->exp, headResultSum);
			p1 = p1->next;
		}
	}
	
	while (p1) {
		sortedInput(p1->koef, p1->exp, headResultSum);
		p1 = p1->next;
	}

	while (p2) {
		sortedInput(p2->koef, p2->exp, headResultSum);
		p2 = p2->next;
	}

	return 0;
}

int multiplyPoly(Poly* headFirst, Poly* headSecond, Poly* headResultProduct) {
	Poly* p1 = headFirst->next;
	Poly* p2 = headSecond->next;

	if (!p1 || !p2) {
		puts("Jedna ili obje liste su prazne, nije moguce pomnoziti polinome!");
		return -1;
	}

	while (p1) {

		while (p2) {
			sortedInput(p1->koef * p2->koef, p1->exp + p2->exp, headResultProduct);
			p2 = p2->next;
		}

		p1 = p1->next;
		p2 = headSecond->next;
	}

	return 0;
}

int printList(Poly* head) {
	if (!head->next) {
		printf("\nLista je prazna!\n");
		return -1;
	}

	int isFirst = 1;
	Poly* curr = head->next;

	while (curr) {
		if (curr->koef > 0 && curr->exp != 0 && isFirst) {
			printf("%dx^%d", curr->koef, curr->exp);
			isFirst = 0;
		}
		else if (curr->koef > 0 && curr->exp != 0 && !isFirst) {
			printf("+%dx^%d", curr->koef, curr->exp);
		}
		else if (curr->koef > 0 && curr->exp == 0 && isFirst) {
			printf("%d", curr->koef);
			isFirst = 0;
		}
		else if (curr->koef > 0 && curr->exp == 0 && !isFirst) {
			printf("+%d", curr->koef);
		}
		else if (curr->koef < 0 && curr->exp != 0) {
			printf("%dx^%d", curr->koef, curr->exp);
			isFirst = 0;
		}
		else if (curr->koef < 0 && curr->exp == 0) {
			printf("%d", curr->koef);
			isFirst = 0;
		}

		curr = curr->next;
	}

	return 0;
}

int deleteList(Poly* head) {

	while (head->next) {
		Poly* temp = head->next->next;
		free(head->next);
		head->next = temp;
	}

	return 0;
}