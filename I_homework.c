#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 1000

int main() {
	int numbers[MAX] = {};
	int i = 0, ret = 0, negNumb = 0;
	char num[MAX], * check;
	int lenght = 0;
	printf("Programa papraso vartotojo ivesti sveiku skaciu seka, kuri gali susideti is neigiamu bei teigiamu ivesciu.\nSuskaiciuoja ir pabaigoje isveda kiek masyve buvo neigiamu skaiciu su nelyginiu indeksu.\n");
	printf("\nIveskite sveiku skaiciu seka, kurios pabaiga zymima ivestu 0: \n");
	//vartotojas iveda masyvo elementus, jie tikrinami ar n�ra simboliai, double
	do {
		int count = 0;
		scanf("%s", num);
		lenght = strlen(num);
		for (int l = 0; l < lenght; l++) {
			if (isdigit(num[l]) == '\0' && l != 0) {
				++count;
			}
		}
		check = num;
		ret = sscanf(check, "%d", &numbers[i]);
		//tikrinami ar teisinga ivestis
		while (count > 0 || ret == 0) {

			// jei neteisinga
			while (1) {
				count = 0;
				printf("Simbolio reiksme netinkama. Iveskite teigiama arba neigiama sveika skaiciu: \n");
				scanf("%s", num);
				check = num;
				ret = sscanf(check, "%d", &numbers[i]);
				lenght = strlen(num);
				for (int l = 0; l < lenght; l++) {
					if (isdigit(num[l]) == '\0' && l != 0) {
						++count;
					}
				}
				if (count == 0 && ret == 1)
					break;
			}
		}
		printf("Ivestis teisinga, teskite toliau. \n");
		++i;
	} while (!numbers[i - 1] == 0);

	//tikrinami kurie yra neigiami ir kiek ju yra
	for (int n = 0; n < i; n++) {
		if (numbers[n] < 0 && n % 2 != 0) {
			++negNumb;
		}
	}
	//isvedamas neigiamu elementu skaicius
	printf("\nSkacius, masyve esanciu reiksmiu su nelyginiu indeksu (kaip 1...), turinciu neigiamas reiksmes (kaip -3...) yra %d.", negNumb);

	return 0;
}
