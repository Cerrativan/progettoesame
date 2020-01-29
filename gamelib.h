#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void menu ();

struct Scavatrice {
  struct Caverna *posizione;
  int serbatoio_energia;    //valore massimo 4
  int serbatoio_raccolta;   //valore massimo 10
  enum stato {vivo, morto, uscito} stato;
  int punti_vita;   //valore base 30
  int punti_attacco;  //valore base 3
  int punti_difesa;  //valore base 1
  int prob_critico; //valore base 5%
};

struct Caverna {
  int a;
  struct Caverna *avanti;
  struct Caverna *destra;
  struct Caverna *sinistra;
  enum melassa {nessuna, poca, molta = 3} melassa;
  enum imprevisto {nessun_imprevisto, crollo, baco} imprevisto;
  enum tipo_caverna {normale, speciale, accidentata, uscita} tipo_caverna;
  enum potenziamento {nessuno, un_materiale, tre_materiali} potenziamento;
};
