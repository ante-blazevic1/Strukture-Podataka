#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30

typedef struct _Person {
	char name[MAX];
	char lastName[MAX];
	int yearOfBirth;
	struct _Person* next;
} Person;

int insertBegin(char*, char*, int, Person*);
int printList(Person*);
int insertEnd(char*, char*, int, Person*);
Person* findByLastName(char*, Person*);
int deletePerson(char*, Person*);
int deleteAll(Person*);

int main(void) {

	Person head = { 0 };

	int choice = -1;

	while (choice) {
		printf("\nIZBORNIK\n");
		printf("1. Dodaj na pocetak\n");
		printf("2. Dodaj na kraj\n");
		printf("3. Ispisi listu\n");
		printf("4. Pronadji po prezimenu\n");
		printf("5. Obrisi po prezimenu\n");
		printf("0. Izlaz\n");
		printf("Odaberite opciju: ");
		scanf("%d", &choice);
		
		switch (choice)
		{
			case 1: {
				Person newP;
				printf("Unesite ime, prezime i godinu rodjenja: ");
				scanf("%s %s %d", newP.name, newP.lastName, &newP.yearOfBirth);
				insertBegin(newP.name, newP.lastName, newP.yearOfBirth, &head);
				break;
			}

			case 2: {
				Person newP;
				printf("Unesite ime, prezime i godinu rodjenja: ");
				scanf("%s %s %d", newP.name, newP.lastName, &newP.yearOfBirth);
				insertEnd(newP.name, newP.lastName, newP.yearOfBirth, &head);
				break;
			}

			case 3: {
				printList(&head);
				break;
			}

			case 4: {
				char _lastName[MAX];
				printf("Unesite prezime: ");
				scanf("%s", _lastName);

				Person* newP = findByLastName(_lastName, &head);

				if (newP) {
					printf("Pronadjena osoba %s %s %d!\n", newP->name, newP->lastName, newP->yearOfBirth);
				}
				else {
					printf("Osoba s prezimenom %s nije pronadjena!\n", _lastName);
				}

				break;
			}

			case 5: {
				char _lastName[MAX];
				printf("Unesite prezime: ");
				scanf("%s", _lastName);

				if (deletePerson(_lastName, &head) == 0) {
					puts("Osoba je uspjesno obrisana!");
				}

				break;
			}

			case 0: {
				puts("Izlaz!");
				deleteAll(&head);
				break;
			}

			default: {
				puts("Krivi izbor, pokusajte ponovno!");
				break;
			}
		}
	}

	return 0;
}

int insertBegin(char* _name, char* _lastName, int _yearOfBirth, Person* head) {
	Person* newP = (Person*)malloc(sizeof(Person));

	if (!newP) {
		puts("Greska!");
		return -1;
	}

	strcpy(newP->name, _name);
	strcpy(newP->lastName, _lastName);
	newP->yearOfBirth = _yearOfBirth;

	newP->next = head->next;
	head->next = newP;

	return 0;
}

int printList(Person* head) {
	Person* curr = head->next;

	if (!curr) {
		puts("Lista je prazna!");
		return 0;
	}

	while (curr) {
		printf("\n%s %s %d\n", curr->name, curr->lastName, curr->yearOfBirth);
		curr = curr->next;
	}

	return 0;
}

int insertEnd(char* _name, char* _lastName, int _yearOfBirth, Person* head) {
	Person* newP = (Person*)malloc(sizeof(Person));

	if (!newP) {
		puts("Greska!");
		return -1;
	}

	strcpy(newP->name, _name);
	strcpy(newP->lastName, _lastName);
	newP->yearOfBirth = _yearOfBirth;

	Person* curr = head;

	while (curr->next) {
		curr = curr->next;
	}

	newP->next = curr->next;
	curr->next = newP;

	return 0;
}

Person* findByLastName(char* _lastName, Person* head) {
	Person* curr = head->next;

	while (curr) {
		if (!strcmp(curr->lastName, _lastName)) {
			return curr;
		}

		curr = curr->next;
	}

	return NULL;
}

int deletePerson(char* _lastName, Person* head) {
	Person* prev = head;

	if (!prev->next) {
		puts("Lista je prazna!");
		return 1;
	}

	Person* curr = findByLastName(_lastName, prev);
	if (!curr) {
		puts("Osoba nije pronadjena!");
		return 1;
	}

	while (prev->next != curr) {
		prev = prev->next;
	}

	prev->next = curr->next;

	free(curr);

	return 0;
}

int deleteAll(Person* head) {

	if (!head->next) {
		puts("Lista je prazna!");
		return 0;
	}

	while (head->next) {
		Person* temp = head->next->next;

		free(head->next);

		head->next = temp;
	}

	return 0;
}