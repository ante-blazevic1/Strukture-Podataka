#include <stdio.h>
#include <stdlib.h>

#define MAX_BROJ_BODOVA 95

typedef struct _Student {
	char name[20];
	char LName[30];
	int bodovi;
} stud;

double RelBrBodova(stud*);
int Ispis(stud*, double);

int main() {
	char buffer[50] = { 0 };
	int brojac = 0;
	int i = 0;
	FILE* fp = fopen("popis.txt", "r");
	if (!fp) {
		printf("Greska!\n");
		return -1;
	}

	while (!feof(fp)) {
		fgets(buffer, 50, fp);
		brojac++;
	}
	//printf("%d\n", brojac);return 0;
	
	stud* studenti = NULL;
	studenti = (stud*)malloc(brojac * sizeof(stud));
	if (!studenti) {
		printf("Greska!\n");
		free(studenti);
		fclose(fp);
		return -1;
	}
	
	rewind(fp);

	while (!feof(fp)) {
		fscanf(fp, "%s %s %d", studenti[i].name, studenti[i].LName, &studenti[i].bodovi);
		i++;
	}

	fclose(fp);
	
	for (i = 0; i < brojac; i++) {
		Ispis(&studenti[i], RelBrBodova(&studenti[i]));
	}

	free(studenti);

	return 0;
}

int Ispis(stud* s, double relBrBod) {
	printf("%s %s %d %.2lf\n", s->name, s->LName, s->bodovi, relBrBod);
	return 0;
}

double RelBrBodova(stud* s) {
	return ((double)s->bodovi / MAX_BROJ_BODOVA) * 100;
}