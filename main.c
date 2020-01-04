#include "gamelib.h"

int main(void)  {
	int scelta;
	time_t t;
	srand((unsigned) time (&t));
	do {
		printf("Inserire una opzione\n");
		printf("Premere 1 per creare le caverne\n");
		printf("Premere 2 per giocare\n");
		printf("Premere 3 per terminare il gioco\n");
		scanf("%d", &scelta);

		switch (scelta) {
			case 1:
				crea_cunicoli ();
			break;
			case 2:
					gioca ();
				//else
					//printf("Creare i cunicoli prima di giocare\n");
			break;
			case 3:
					return 0;
			break;
			default:
				printf("Comando non valido\n");
		}
	}while(scelta != 3);
	return 0;
}
