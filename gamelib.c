#include "gamelib.h"

static struct Caverna *Pca = NULL;        //primo cunicolo arvais
static struct Caverna *Pch = NULL;    //primo cunicolo hartornen;
static struct Scavatrice arvais;
static struct Scavatrice hartornen;
static void crea_cunicoli ();
static void ins_caverna (struct Caverna **Pc);
static void stampa_lista (struct Caverna **Pc);
static void canc_caverna (struct Caverna **Pc);
static int prob ();    //probabilità
static void stato_caverna (struct Caverna **Pc);   //tipo caverna
static void fmelassa (struct Caverna **Pc);  // randomizzazione quantità melassa
static void fimprevisto (struct Caverna **Pc);  // randomizzazione imprevisto
static void fmateriali (struct Caverna **Pc); //randomizzazione materiali
static void turnoArvais ();  //turno di gioco arvais
static void turnoHartornen (); // turno di gioco hartornen
static void turnofinaleArvais (); //turno scontro finale arvais
static void turnofinaleHartornen ();  //turno scontro finale hartornen
static void avanza (struct Caverna **Pc, struct Scavatrice *fam);
static void abbatti (struct Caverna **Pc, struct Scavatrice *fam);
static void aggira (struct Caverna **Pc, struct Scavatrice *fam);
static void controllofinale ();   //controllo vincitore
static void scontrofinale ();  //scontro incrocio scavatrici
static void statfamiglia ();  //statistiche di base famiglie
static int probcritico ();  //probabilità colpo critico
static int probscontroA = 3; //percentuale progressiva scontro arvais
static int probscontroH = 3; //percentuale progressiva scontro Hartornen
static int probuscita = 0;
static int controllocunicoli = 0;
static int controllocunicolivecchi = 0;
static void gioca ();
static void termina_gioco (struct Caverna **Pc);
static void presentazione ();
static char controllo_scelta ();


static void ins_caverna (struct Caverna **Pc) {
char scelta;
//Dichiarazione nuova caverna
struct Caverna *nc =(struct Caverna*) malloc(sizeof(struct Caverna));  //nuova caverna
  nc->avanti = NULL;
  nc->destra = NULL;
  nc->sinistra = NULL;

//Menù direzione creazione nuova caverna
printf("Inserire una direzione\n");
printf("1 per creare una caverna di fronte\n");
printf("2 per creare una caverna a destra\n");
printf("3 per creare una caverna a sinistra\n");
//scanf("%d", &scelta);
scelta = controllo_scelta ();

    if (*Pc == NULL) {
      *Pc = nc;
      }
      else {
  switch (scelta) {
    //Caverna avanti
    case '1':
      nc->avanti = *Pc;
      nc->destra = NULL;
      nc->sinistra = NULL;
      *Pc = nc;
    break;
    //caverna a destra
    case '2':
      nc->avanti = NULL;
      nc->destra = *Pc;
      nc->sinistra = NULL;
      *Pc = nc;
    break;
    //caverna a sinistra
    case '3':
      nc->avanti = NULL;
      nc->destra = NULL;
      nc->sinistra = *Pc;
      *Pc = nc;
      break;
      default:
        printf("Comando non valido\n");
      break;
           }
     }
}

static void crea_cunicoli () {
  char scelta;
  char scelta2;
  int i = 0;
  int j = 0;
  printf("Creazione caverne famiglia Arvais\n");
  while (i < 10) {
    //menù scelta iniziale
  printf("Effettuare una scelta\n");
  printf("Premere 1 per creare cunicolo\n");
  printf("Premere 2 per cancellare una caverna precedente\n");
  printf("Premere 3 per stampare i cunicoli creati\n");
  printf("Premere 4 per uscire\n");
  //scanf("%d", &scelta);
  scelta = controllo_scelta ();

  switch (scelta) {
    case '1':
      ins_caverna (&Pca);
      stato_caverna (&Pca);
      fimprevisto (&Pca);
      fmelassa (&Pca);
      fmateriali (&Pca);
      i++;
    break;
    case '2':
      canc_caverna (&Pca);
    break;
    case '3':
      stampa_lista (&Pca);
    break;
    case '4':
        printf("Errore: creare minimo 10 caverne\n");
    break;
    default:
      printf("Comando non valido\n");
       }
  }
  system("clear");
  printf("Creazione caverne famiglia Hartornen\n");

  while (j < 10) {
    //menù scelta iniziale
  printf("Effettuare una scelta\n");
  printf("Premere 1 per creare cunicolo\n");
  printf("Premere 2 per cancellare un cunicolo precedente\n");
  printf("Premere 3 per stampare i cunicoli creati\n");
  printf("Premere 4 per uscire\n");
  //scanf("%d", &scelta2);
  scelta2 = controllo_scelta ();

  switch (scelta2) {
    case '1':
      ins_caverna (&Pch);
      stato_caverna (&Pch);
      fimprevisto (&Pch);
      fmelassa (&Pch);
      fmateriali (&Pch);
      j++;
    break;
    case '2':
      canc_caverna (&Pch);
    break;
    case '3':
      stampa_lista (&Pch);
    break;
    case '4':
      printf("Errore: creare minimo 10 caverne\n");
    break;
    default:
      printf("Comando non valido\n");
    }
  }
  system("clear");
  controllocunicoli = 1;
}

static void stampa_lista (struct Caverna **Pc) {
  if(*Pc == NULL) {
      printf("Non ci sono caverne\n"); }
  else {
    struct Caverna* sonda = *Pc;

    do {
      if (sonda->tipo_caverna == 0)
        printf("Tipo: Normale\n");
      else if (sonda->tipo_caverna == 1)
        printf("Tipo: Speciale\n");
      else
        printf("Tipo: Accidentata\n");
          if (sonda->avanti != NULL)
            sonda = sonda ->avanti;
          else if (sonda->destra != NULL)
            sonda = sonda ->destra;
          else
            sonda = sonda ->sinistra;
        //sonda = sonda -> destra;
        //sonda = sonda -> sinistra;
    }while(sonda != NULL);
  }
      return;
}

static void canc_caverna (struct Caverna **Pc) {
  if (*Pc == NULL)
    printf("Non ci sono caverne\n");
  else if ((*Pc)->avanti != NULL) {
      struct Caverna *temp = (*Pc)->avanti;
      free(*Pc);
      *Pc = temp;
    }
  else if ((*Pc)->destra != NULL) {
      struct Caverna *temp = (*Pc)->destra;
      free(*Pc);
      *Pc = temp;
  }
  else {
      struct Caverna *temp = (*Pc)->sinistra;
      free(*Pc);
      *Pc = temp;
  }
    system("clear");
    return;
  }

static void stato_caverna (struct Caverna **Pc) {
  char scelta;
  //Menù stato caverna
  printf("Di che tipo deve essere la caverna?\n");
  printf("Premere 1 per creare una caverna normale\n");
  printf("Premere 2 per creare una caverna speciale\n");
  printf("Premere 3 per creare una caverna accidentata\n");
  //scanf("%d", &scelta);
  scelta = controllo_scelta ();

  switch (scelta) {
    case '1':
      (*Pc)->tipo_caverna = normale;
      break;
    case '2':
      (*Pc)->tipo_caverna = speciale;
      break;
    case '3':
      (*Pc)->tipo_caverna = accidentata;
      break;
    default:
      printf("Comando non valido\n");
      break;
  }
  system("clear");
}

static int prob () {
  return (rand () % 101);
}

static void fmelassa (struct Caverna **Pc) {
  //probabilita = 0;
  int probabilita = prob ();
  if (probabilita <= 50)
    (*Pc)->melassa = nessuna;
  else if (probabilita > 50 && probabilita <= 80)
    (*Pc)->melassa = poca;
  else if (probabilita > 80 && probabilita <= 100)
    (*Pc)->melassa = molta;
}

static void fimprevisto (struct Caverna **Pc) {
  //probabilita = 0;
  int probabilita = prob ();
  if (probabilita <= 50)
    (*Pc)->imprevisto = nessun_imprevisto;
  else if (probabilita > 50 && probabilita <= 85)
    (*Pc)->imprevisto = crollo;
  else if (probabilita > 85 && probabilita <= 100)
    (*Pc)->imprevisto = baco;
}

static void fmateriali (struct Caverna **Pc) {
  int probabilita = prob ();
  if (probabilita <= 10)
    (*Pc)->potenziamento = nessuno;
  else if (probabilita > 10 && probabilita <= 90 )
    (*Pc)->potenziamento = un_materiale;
  else
    (*Pc)->potenziamento = tre_materiali;
}

static void turnoArvais () {
  char scelta;
  //controllo stato giocatore
  if (arvais.stato == uscito)
      return;
  //controllo serbatoi giocatore
  arvais.serbatoio_energia > 4 ? arvais.serbatoio_energia = 4 : arvais.serbatoio_energia + 0;
  arvais.serbatoio_raccolta > 10 ? arvais.serbatoio_raccolta = 10 : arvais.serbatoio_raccolta + 0;
  //stato giocatore Arvais
  printf("TURNO ARVAIS\n");
  printf("Quantità serbatoio energia: %d/4\n", arvais.serbatoio_energia);
  printf("Quantità serbatoio raccolta: %d/10\n", arvais.serbatoio_raccolta);
  printf("Punti vita: %d\n", arvais.punti_vita);
  printf("Punti attacco: %d\n", arvais.punti_attacco);
  printf("Punti difesa: %d\n", arvais.punti_difesa);
  printf("Probabilità critico: %d\n", arvais.prob_critico);
  printf("\n\n");

  //Menù decisionale arvais
  printf("Cosa vuoi fare?\n");
  printf("Premere 1 per avanzare\n");
  printf("Premere 2 per abbattere; Consuma 1 punto energia\n");
  printf("Premere 3 per aggirare\n");
  printf("Premere 4 per uscire dalla caverna\n");
  //scanf("%d", &scelta);
  scelta = controllo_scelta ();

  switch (scelta) {
    case '1':
        avanza (&Pca, &arvais);
    break;
    case '2':
        abbatti (&Pca, &arvais);
    break;
    case '3':
        printf("Puoi aggirare solo in seguito ad un crollo\n");
        turnoArvais ();
    break;
    case '4':
          printf("Non puoi uscire fino a quando non trovi l'uscita\n");
          turnoArvais ();
    break;
    default:
    printf("Inserire un comando valido\n");
  }
  //controllo livello serbatoio
  if (arvais.serbatoio_energia < 0) {
    arvais.stato = morto;}
  //controllo probabilità probscontro
  if (arvais.stato != uscito && hartornen.stato != uscito) {
  int probabilita = 0;
  probabilita = prob ();
  if (probabilita < probscontroA)
    scontrofinale ();
  else
      probscontroA = probscontroA + 3;
    }
}

static void turnofinaleArvais () {
  int danno = 0;
  char scelta;
  printf("TURNO ARVAIS\n");
  printf("Punti vita: %d\n", arvais.punti_vita);
  printf("Punti attacco: %d\n", arvais.punti_attacco);
  printf("Punti difesa: %d\n", arvais.punti_difesa);
  printf("Probabilità critico: %d\n", arvais.prob_critico);
  if ((arvais.punti_vita == 7) && (arvais.punti_attacco == 7) && (arvais.punti_difesa == 7)) {
    printf("***********\n");
    printf("* LUCKY 7 *\n");
    printf("***********\n");
    printf("Punti vita: %d\n", arvais.punti_vita);
    printf("Punti attacco: %d\n", arvais.punti_attacco);
    printf("Punti difesa: %d\n", arvais.punti_difesa);
      arvais.punti_vita = 7777;
      arvais.punti_attacco = 7777;
      arvais.punti_difesa = 7777;}
  printf("\n\n");
  printf("Cosa vuoi fare\n");
  printf("Premere 1 per attaccare\n");
  //scanf("%d", &scelta);
  scelta = controllo_scelta ();

  switch (scelta) {
    case '1':
    danno = ((arvais.punti_attacco - hartornen.punti_difesa)*probcritico ());
      if (danno < 0)
        danno = 1;
      hartornen.punti_vita = hartornen.punti_vita - danno;
    break;
    default:
      printf("Comando non valido\n");
    break;
  }
  if (hartornen.punti_vita <= 0)
    hartornen.stato = morto;
  printf("La scavatrice Arvais ha totalizzato %d danni/o\n", danno);
}

static void turnoHartornen () {
  char scelta;
  //controllo stato giocatore
    if (hartornen.stato == uscito)
      return;
      //controllo serbatoi giocatore
hartornen.serbatoio_energia > 4 ? hartornen.serbatoio_energia = 4 : hartornen.serbatoio_energia + 0;
hartornen.serbatoio_raccolta > 10 ? hartornen.serbatoio_raccolta = 10 : hartornen.serbatoio_raccolta + 0;
  //stato giocatore Hartornen
  printf("TURNO HARTORNEN\n");
  printf("Quantità serbatoio energia: %d/4\n", hartornen.serbatoio_energia);
  printf("Quantità serbatoio raccolta: %d/10\n", hartornen.serbatoio_raccolta);
  printf("Punti vita: %d\n", hartornen.punti_vita);
  printf("Punti attacco: %d\n", hartornen.punti_attacco);
  printf("Punti difesa: %d\n", hartornen.punti_difesa);
  printf("Probabilità critico: %d\n", hartornen.prob_critico);
  printf("\n\n");

    //menù decisionale
  printf("Cosa vuoi fare?\n");
  printf("Premere 1 per avanzare\n");
  printf("Premere 2 per abbattere; Consuma 1 punto energia\n");
  printf("Premere 3 per aggirare\n");
  printf("Premere 4 per uscire dalla caverna\n");
  //scanf("%d", &scelta);
  scelta = controllo_scelta ();

  switch (scelta) {
    case '1':
        avanza (&Pch, &hartornen);
    break;
    case '2':
        abbatti (&Pch, &hartornen);
    break;
    case '3':
        printf("Puoi aggirare solo in seguito ad un crollo\n");
        turnoHartornen ();
    break;
    case '4':
        printf("Non puoi uscire fino a quando non trovi l'uscita\n");
        turnoHartornen ();
    break;
    default:
    printf("Comando non valido\n");
  }
  if (hartornen.serbatoio_energia < 0) {
    hartornen.stato = morto;}
    //probabilità scontro finale
    if (arvais.stato != uscito && hartornen.stato != uscito) {
int probabilita = 0;
probabilita = prob ();
if (probabilita < probscontroH)
      scontrofinale ();
else
      probscontroH = probscontroH + 3;
    }
}

static void turnofinaleHartornen () {
  int danno = 0;
  char scelta;
  printf("TURNO HARTORNEN\n");
  printf("Punti vita: %d\n", hartornen.punti_vita);
  printf("Punti attacco: %d\n", hartornen.punti_attacco);
  printf("Punti difesa: %d\n", hartornen.punti_difesa);
  printf("Probabilità critico: %d\n", hartornen.prob_critico);
  if ((hartornen.punti_vita == 7) && (hartornen.punti_attacco == 7) && (hartornen.punti_difesa == 7)) {
    printf("***********\n");
    printf("* LUCKY 7 *\n");
    printf("***********\n");
    printf("Punti vita: %d\n", hartornen.punti_vita);
    printf("Punti attacco: %d\n", hartornen.punti_attacco);
    printf("Punti difesa: %d\n", hartornen.punti_difesa);
      hartornen.punti_vita = 7777;
      hartornen.punti_attacco = 7777;
      hartornen.punti_difesa = 7777;}
  printf("\n\n");
  printf("Cosa vuoi fare?\n");
  printf("Premere 1 per attaccare\n");
  //scanf("%d", &scelta);
  scelta = controllo_scelta ();

  switch (scelta) {
    case '1':
    danno = ((hartornen.punti_attacco - arvais.punti_difesa)*probcritico ());
      if (danno < 0)
        danno = 1;
    arvais.punti_vita = arvais.punti_vita - danno;
    break;
    default:
      printf("Comando non valido\n");
    break;
  }
  if (arvais.punti_vita <= 0)
    arvais.stato = morto;
  system("clear");
  printf("La scavatrice Hartornen ha totalizzato %d danni/o\n", danno);
}

static void avanza (struct Caverna **Pc, struct Scavatrice *fam) {
  char primascelta;
  (*fam).posizione = *Pc;
  system("clear");
  if ((*Pc)->avanti==NULL && (*Pc)->destra==NULL && (*Pc)->sinistra==NULL) {
        printf("Non ci sono ulteriori caverne\n\n");
        return;}
  //controllo crollo
  if (prob () <= 25) {
    printf("Si è verificato un crollo improvviso\n\n");
    printf("Cosa vuoi fare?\n");
    printf("Premere 1 per aggirare\n");
    printf("Premere 2 per abbattere\n");
    //scanf("%d", &primascelta);
    primascelta = controllo_scelta ();

    switch (primascelta) {
      case '1':
          aggira (Pc, fam);
      break;
      case '2':
          abbatti (Pc, fam);
      break;
      default:
          printf("Comando non valido\n");
          }
      }
  else {
//puntatore non nullo = direzione
if ((*Pc)->avanti != NULL) {
    printf("Sei andato avanti\n\n");
    (*fam).posizione = (*Pc)->avanti;
    (*Pc) = (*Pc)->avanti;
  }
  else if ((*Pc)->destra != NULL) {
    printf("Hai svoltato a destra\n\n");
    (*fam).posizione = (*Pc)->destra;
    (*Pc) = (*Pc)->destra;
  }
  else {
    printf("Hai svoltato a sinistra\n\n");
    (*fam).posizione = (*Pc)->sinistra;
    (*Pc) = (*Pc)->sinistra;
  }

//tipo imprevisto
  if ((*Pc)->imprevisto == crollo) {
    printf("C'è stato un crollo: consumi 1 punto energia per liberarti dalle macerie\n\n");
    (*fam).serbatoio_energia--;
  }
  else if ((*Pc)->imprevisto == baco) {
    printf("Hai incontrato un feroce baco: sei salvo, ma perdi tutti i punti energia e raccolta accumulati\n\n");
    (*fam).serbatoio_energia = 0;
    (*fam).serbatoio_raccolta = 0;
  }
// tipo caverna
  if ((*Pc)->tipo_caverna == speciale) {
    printf("La caverna irradia melassa: guadagni 1 punto energia\n\n");
    (*fam).serbatoio_energia++;
  }
  else if ((*Pc)->tipo_caverna == accidentata) {
    printf("La caverna è accidentata: perdi 1 punto energia\n\n");
    (*fam).serbatoio_energia--;
  }

    //quantità melassa
  if ((*Pc)->melassa == poca) {
    char scelta;
    printf("La caverna contiene poca melassa: scavando, ne guadagni 1 unita\n\n");
    printf("In quale serbatoio vuoi metterla?\n");
    printf("Premere 1 per metterla nel serbatoio di energia\n");
    printf("Premere 2 per metterla nel serbatoio di raccolta\n");
    //scanf("%d", &scelta);
    scelta = controllo_scelta ();

    switch (scelta) {
      case '1':
        (*fam).serbatoio_energia++;
    break;
      case '2':
        (*fam).serbatoio_raccolta++;
    break;
    default:
        printf("Comando non valido\n");
      }
  }
  else if ((*Pc)->melassa == molta) {
    char scelta2;
    printf("La caverna contiene molta melassa: scavando, ne guadagni 3 unita\n\n");
    printf("In quale serbatoio vuoi metterla?\n");
    printf("Premere 1 per metterla nel serbatoio di energia\n");
    printf("Premere 2 per metterla nel serbatoio di raccolta\n");
    //scanf("%d", &scelta2);
    scelta2 = controllo_scelta ();

    switch (scelta2) {
    case '1':
        (*fam).serbatoio_energia += 3;
    break;
    case '2':
        (*fam).serbatoio_raccolta += 3;
    break;
    default:
        printf("Comando non valido\n");
    }
   }
   //menu potenziamento
   if ((*Pc)->potenziamento == un_materiale) {
    char scelta3;
    printf("La caverna contiene 1 materiale potenziamento. Cosa vuoi potenziare?\n");
    printf("Premere 1 per Punti Vita\n");
    printf("Premere 2 per Punti Attacco\n");
    printf("Premere 3 per Punti Difesa\n");
    //scanf("%d", &scelta3);
    scelta3 = controllo_scelta ();

    switch (scelta3) {
      case '1':
        (*fam).punti_vita += 1;
      break;
      case '2':
        (*fam).punti_attacco += 1;
      break;
      case '3':
        (*fam).punti_difesa += 1;
      break;
      default:
        printf("Comando non valido\n");
    }
  }
  if ((*Pc)->potenziamento == tre_materiali) {
   char scelta4;
   printf("La caverna contiene 3 materiali potenziamento. Cosa vuoi potenziare?\n");
   printf("Premere 1 per Punti Vita\n");
   printf("Premere 2 per Punti Attacco\n");
   printf("Premere 3 per Punti Difesa\n");
   //scanf("%d", &scelta4);
   scelta4 = controllo_scelta ();

   switch (scelta4) {
     case '1':
       (*fam).punti_vita += 3;
     break;
     case '2':
       (*fam).punti_attacco += 3;
     break;
     case '3':
       (*fam).punti_difesa += 3;
     break;
     default:
       printf("Comando non valido\n");
   }
  }
 }
}

static void abbatti (struct Caverna **Pc, struct Scavatrice *fam) {
  system("clear");
  int probabilita;
  char scelta;
  //Dichiarazione nuova caverna
struct Caverna *abbatti = (struct Caverna*)malloc(sizeof(struct Caverna));
abbatti->avanti = NULL;
abbatti->destra = NULL;
abbatti->sinistra = NULL;

printf("Dove vuoi abbattere?\n");
printf("Premere 1 per abbattere avanti\n");
printf("Premere 2 per abbattere a destra\n");
printf("Premere 3 per abbattere a sinistra\n");
//scanf("%d", &scelta);
scelta = controllo_scelta ();

switch (scelta) {
  case '1':
    if ((*Pc)->avanti != NULL)
        printf("Spiacente, esiste già una caverna in quella direzione\n");
    else {
        (*Pc)->avanti = abbatti;
        (*Pc)->destra = NULL;
        (*Pc)->sinistra = NULL;
        (*fam).posizione = abbatti;
        (*Pc)->avanti = NULL;
        (*fam).serbatoio_energia--;
    }
  break;
  case '2':
    if ((*Pc)->destra != NULL)
        printf("Spiacente, esiste già una caverna in quella direzione\n");
    else {
        (*Pc)->avanti = NULL;
        (*Pc)->destra = abbatti;
        (*Pc)->sinistra = NULL;
        (*fam).posizione = abbatti;
        (*Pc)->destra = NULL;
        (*fam).serbatoio_energia--;
    }
  break;
  case '3':
   if ((*Pc)->sinistra != NULL)
        printf("Spiacente, esiste già una caverna in quella direzione\n");
   else {
        (*Pc)->avanti = NULL;
        (*Pc)->destra = NULL;
        (*Pc)->sinistra = abbatti;
        (*fam).posizione = abbatti;
        (*Pc)->sinistra = NULL;
        (*fam).serbatoio_energia--;
   }
   break;
   default:
        printf("Comando non valido\n");
  }
    probabilita = prob ();
  if (probabilita > (100 - probuscita)) {
      abbatti->tipo_caverna = uscita;
      printf("Sei uscito dalla caverna\n");
      (*fam).stato = uscito;}
  else if ((probabilita < (100 - probuscita)) && (probabilita > (100 - (probuscita + 20)))) {
      abbatti->tipo_caverna = accidentata;
      printf("La caverna è accidentata: perdi 1 punto energia\n\n");
      (*fam).serbatoio_energia--;}
  else if (probabilita < (100 - (probuscita + 20) / 2)) {
    printf("La caverna appena creata è normale\n");
      abbatti->tipo_caverna = normale;}
  else {
      abbatti->tipo_caverna = speciale;
      printf("La caverna irradia melassa: guadagni 1 punto energia\n\n");
      (*fam).serbatoio_energia++;
    }

if ((*fam).stato != uscito) {
    //imprevisto
  int probabilita2 = prob ();
  if (probabilita2 < 40)
      abbatti->imprevisto = nessun_imprevisto;
  else if (probabilita2 > 40 && probabilita2 < 80)
      abbatti->imprevisto = crollo;
  else
      abbatti->imprevisto = baco;

    //quantità melassa
  int probabilita3 = prob ();
  if (probabilita3 < 40)
      abbatti->melassa = nessuna;
  else if (probabilita3 > 40 && probabilita3 < 80)
      abbatti->melassa = poca;
  else
      abbatti->melassa = molta;

      //tipo imprevisto
        if (abbatti->imprevisto == crollo) {
          printf("C'è stato un crollo: consumi 1 punto energia per liberarti dalle macerie\n\n");
          (*fam).serbatoio_energia--;
        }
        else if (abbatti->imprevisto == baco) {
          printf("Hai incontrato un feroce baco: sei salvo, ma perdi tutti i punti energia e raccolta accumulati\n\n");
          (*fam).serbatoio_energia = 0;
          (*fam).serbatoio_raccolta = 0;
        }
        //quantità melassa
        if ((*Pc)->melassa == poca) {
        char scelta1;
        printf("La caverna contiene poca melassa: scavando, ne guadagni 1 unita\n\n");
        printf("In quale serbatoio vuoi metterla?\n");
        printf("Premere 1 per metterla nel serbatoio di energia\n");
        printf("Premere 2 per metterla nel serbatoio di raccolta\n");
        //scanf("%d", &scelta1);
        scelta1 = controllo_scelta ();

        switch (scelta1) {
          case '1':
            (*fam).serbatoio_energia++;
        break;
          case '2':
            (*fam).serbatoio_raccolta++;
        break;
        default:
            printf("Comando non valido\n");
          }
        }
        else if ((*Pc)->melassa == molta) {
        char scelta2;
        printf("La caverna contiene molta melassa: scavando, ne guadagni 3 unita\n\n");
        printf("In quale serbatoio vuoi metterla?\n");
        printf("Premere 1 per metterla nel serbatoio di energia\n");
        printf("Premere 2 per metterla nel serbatoio di raccolta\n");
        //scanf("%d", &scelta2);
        scelta2 = controllo_scelta ();

        switch (scelta2) {
        case '1':
            (*fam).serbatoio_energia += 3;
        break;
        case '2':
            (*fam).serbatoio_raccolta += 3;
        break;
        default:
            printf("Comando non valido\n");
        }
        }
        //menu potenziamento
        if ((*Pc)->potenziamento == un_materiale) {
        char scelta3;
        printf("La caverna contiene 1 materiale potenziamento. Cosa vuoi potenziare?\n");
        printf("Premere 1 per Punti Vita\n");
        printf("Premere 2 per Punti Attacco\n");
        printf("Premere 3 per Punti Difesa\n");
        //scanf("%d", &scelta3);
        scelta3 = controllo_scelta ();

        switch (scelta3) {
          case '1':
            (*fam).punti_vita += 1;
          break;
          case '2':
            (*fam).punti_attacco += 1;
          break;
          case '3':
            (*fam).punti_difesa += 1;
          break;
          default:
            printf("Comando non valido\n");
        }
        }
        if ((*Pc)->potenziamento == tre_materiali) {
        char scelta4;
        printf("La caverna contiene 3 materiali potenziamento. Cosa vuoi potenziare?\n");
        printf("Premere 1 per Punti Vita\n");
        printf("Premere 2 per Punti Attacco\n");
        printf("Premere 3 per Punti Difesa\n");
        //scanf("%d", &scelta4);
        scelta4 = controllo_scelta ();

        switch (scelta4) {
         case '1':
           (*fam).punti_vita += 3;
         break;
         case '2':
           (*fam).punti_attacco += 3;
         break;
         case '3':
           (*fam).punti_difesa += 3;
         break;
         default:
           printf("Comando non valido\n");
        }
        }
        }
  }

static void aggira (struct Caverna **Pc, struct Scavatrice *fam) {
  struct Caverna *aggira = (struct Caverna*)malloc(sizeof(struct Caverna));
      aggira->avanti = NULL;
      aggira->destra = NULL;
      aggira->sinistra = NULL;

      if ((*Pc)->avanti != NULL) {
        printf("Aggiri la caverna\n");
          aggira->avanti = *Pc;
          aggira->destra = NULL;
          aggira->sinistra = NULL;
          *Pc = aggira;
          *Pc = (*Pc)->avanti;
        }
      if ((*Pc)->destra != NULL) {
          printf("Aggiri la caverna\n");
          aggira->avanti = NULL;
          aggira->destra = *Pc;
          aggira->sinistra = NULL;
          *Pc = aggira;
          *Pc = (*Pc)->destra;
      }
     if ((*Pc)->sinistra != NULL) {
          printf("Aggiri la caverna\n");
          aggira->avanti = NULL;
          aggira->destra = NULL;
          aggira->sinistra = *Pc;
          *Pc = aggira;
          *Pc = (*Pc)->sinistra;
     }
     //prob imprevisto
     int probabilita = prob ();
     if (probabilita <= 50)
       (*Pc)->imprevisto = nessun_imprevisto;
     else if (probabilita > 50 && probabilita <= 85)
       (*Pc)->imprevisto = crollo;
     else if (probabilita > 85 && probabilita <= 100)
       (*Pc)->imprevisto = baco;

    //prob melassa
    int probabilita2 = prob ();
    if (probabilita2 <= 50)
        (*Pc)->melassa = nessuna;
    else if (probabilita2 > 50 && probabilita2 <= 80)
         (*Pc)->melassa = poca;
    else if (probabilita2 > 80 && probabilita2 <= 100)
         (*Pc)->melassa = molta;

       //tipo imprevisto
         if ((*Pc)->imprevisto == crollo) {
           printf("C'è stato un crollo: consumi 1 punto energia per liberarti dalle macerie\n\n");
           (*fam).serbatoio_energia--;
         }
         else if ((*Pc)->imprevisto == baco) {
           printf("Hai incontrato un feroce baco: sei salvo, ma perdi tutti i punti energia e raccolta accumulati\n\n");
           (*fam).serbatoio_energia = 0;
           (*fam).serbatoio_raccolta = 0;
         }
         //quantità melassa
       if ((*Pc)->melassa == poca) {
         char scelta;
         printf("La caverna contiene poca melassa: scavando, ne guadagni 1 unita\n\n");
         printf("In quale serbatoio vuoi metterla?\n");
         printf("Premere 1 per metterla nel serbatoio di energia\n");
         printf("Premere 2 per metterla nel serbatoio di raccolta\n");
         //scanf("%d", &scelta);
         scelta = controllo_scelta ();

         switch (scelta) {
           case '1':
             (*fam).serbatoio_energia++;
         break;
           case '2':
             (*fam).serbatoio_raccolta++;
         break;
         default:
             printf("Comando non valido\n");
           }
       }
       else if ((*Pc)->melassa == molta) {
         char scelta2;
         printf("La caverna contiene molta melassa: scavando, ne guadagni 3 unita\n\n");
         printf("In quale serbatoio vuoi metterla?\n");
         printf("Premere 1 per metterla nel serbatoio di energia\n");
         printf("Premere 2 per metterla nel serbatoio di raccolta\n");
         //scanf("%d", &scelta2);
         scelta2 = controllo_scelta ();

         switch (scelta2) {
         case '1':
             (*fam).serbatoio_energia += 3;
         break;
         case '2':
             (*fam).serbatoio_raccolta += 3;
         break;
         default:
             printf("Comando non valido\n");
         }
        }

}

static void controllofinale () {
    //controllo stato vita
  if (arvais.stato == morto) {
    printf("La scavatrice Arvais è esplosa. Gli Hartornen vincono, quindi ottengono il controllo del territorio\n");
    printf("\n\nGAME OVER\n\n");}
  else if (hartornen.stato == morto) {
    printf("La scavatrice Hartornen è esplosa. Gli Arvais vincono, quindi ottengono il controllo del territorio\n");
    printf("\n\nGAME OVER\n\n");}

    //controllo stato uscito
  if (arvais.stato == uscito && hartornen.stato == uscito) {
      if (arvais.serbatoio_raccolta > hartornen.serbatoio_raccolta) {
        printf("Gli Arvais hanno raccolto più melassa. Gli Arvais vincono, quindi ottengono il controllo del territorio\n");
        printf("\n\nGAME OVER\n\n");}
      else if (arvais.serbatoio_raccolta < hartornen.serbatoio_raccolta) {
        printf("Gli Hartornen hanno raccolto più melassa. Gli Hartornen vincono, quindi ottengono il controllo del territorio\n");
        printf("\n\nGAME OVER\n\n");}
      else if (arvais.serbatoio_raccolta == hartornen.serbatoio_raccolta) {
        scontrofinale ();
        controllofinale ();}
      }
}

static void statfamiglia () {
  arvais.serbatoio_energia = 4;
  arvais.serbatoio_raccolta = 0;
  arvais.stato = vivo;
  arvais.punti_vita = 30;
  arvais.punti_attacco = 3;
  arvais.punti_difesa = 1;
  arvais.prob_critico = 5;
  hartornen.serbatoio_energia = 4;
  hartornen.serbatoio_raccolta = 0;
  hartornen.stato = vivo;
  hartornen.punti_vita = 30;
  hartornen.punti_attacco = 3;
  hartornen.punti_difesa = 1;
  hartornen.prob_critico = 5;
}

static int probcritico () {
int probcritico = 0;
probcritico = prob ();
  if (probcritico <= 5)
    probcritico = 3;
  else
    probcritico = 1;

return probcritico;
}

static void scontrofinale () {
  int i = 1;
  printf("Le due scavatrici si sono incrociate: sei giunto allo scontro finale\n");
  while (1) {
    printf("TURNO %d\n", i);
      if (arvais.stato==morto || hartornen.stato==morto) {
        //controllofinale ();
        return;}
      else
        turnofinaleArvais ();
      if (arvais.stato==morto || hartornen.stato==morto) {
        //controllofinale ();
        return;}
      else
        turnofinaleHartornen ();
  i++;}
}

static void gioca () {
  int i = 1;
  statfamiglia ();
  while (1) {
    printf("TURNO %d\n", i);
    if ((arvais.stato==morto || hartornen.stato==morto) || (arvais.stato==uscito && hartornen.stato==uscito)) {
      controllofinale ();
      return;}
    else
      turnoArvais ();
    if ((arvais.stato==morto || hartornen.stato==morto) || (arvais.stato==uscito && hartornen.stato==uscito)) {
      controllofinale ();
      return;}
    else
      turnoHartornen ();
  probuscita = probuscita + 5;
  i++;}
}

static void termina_gioco (struct Caverna **Pc) {
  //Deallocazione mappa
  do {
  if (*Pc == NULL)
    printf("Non ci sono caverne\n");
  else if ((*Pc)->avanti != NULL) {
    struct Caverna *temp = (*Pc)->avanti;
      free(*Pc);
      *Pc = temp;
    }
  else if ((*Pc)->destra != NULL) {
    struct Caverna *temp = (*Pc)->destra;
      free(*Pc);
      *Pc = temp;
  }
  else {
    struct Caverna *temp = (*Pc)->sinistra;
      free(*Pc);
      *Pc = temp;}
}while((*Pc) != NULL);
controllocunicoli = 0;
}

static void presentazione () {
  printf("\n");
  printf("LA ARVAIS E LA HARTORNEN SONO DUE FAMIGLIE CHE SI CONTENDONO DA ANNI IL CONTROLLO SUL PIANETA SABBIE ");
  printf("L'ESTRAZIONE DELLA MELASSA, UNA PREZIOSISSIMA SOSTANZA FONDAMENTALE PER LA STRUTTURA DELLA SOCIETÀ GALATTICA.");
  printf("L'ESTRAZIONE È OSTACOLATA DA NUMEROSI PERICOLI COME IMPROVVISE FRANE, SCONTRI CON I RIVALI E I PERICOLOSISSIMI BACHI DELLE SABBIE,");
  printf("CHE POSSONO RAGGIUNGERE LUNGHEZZE DI CENTINAIA DI METRI ED INGOIARE LE SCAVATRICI IN UN SOLO BOCCONE.");
  printf("CHI LA SPUNTERÀ E OTTERRÀ DI CONSEGUENZA IL DOMINIO SUL PIANETA?\n");
}

void menu () {
  char scelta;
  char scelta2;
  presentazione ();
  printf("\n\n");
  do {
		printf("Inserire una opzione\n");
		printf("Premere 1 per creare le caverne\n");
		printf("Premere 2 per giocare\n");
		printf("Premere 3 per eliminare le caverne precedenti o terminare il gioco\n");
		//scanf("%d", &scelta);
    scelta = controllo_scelta ();


		switch (scelta) {
			case '1':
      if (controllocunicoli == 1)
        printf("Esistono già delle caverne. Eliminare quelle precedenti e riprovare\n");
      else
				crea_cunicoli ();
			break;
			case '2':
      if (controllocunicolivecchi == 1)
        printf("Eliminare le caverne precedenti prima di rigiocare\n");
      else if (controllocunicoli == 1) {
					gioca ();
          controllocunicolivecchi = 1;}
				else
					printf("Creare le caverne prima di giocare\n");
			break;
			case '3':
          printf("Terminare il gioco o eliminare le caverne e rigiocare?\n");
          printf("Premere 1 per terminare il gioco\n");
          printf("Premere 2 per eliminare le caverne e rigiocare\n");
          //scanf("%d", &scelta2);
          scelta2 = controllo_scelta ();

          if (scelta2 == '1') {
					  termina_gioco (&Pca);
            termina_gioco (&Pch);
            free(Pca);
            free(Pch);
          return;}
          else {
            termina_gioco (&Pca);
            termina_gioco (&Pch);
            probscontroA = 3;
            probscontroH = 3;
            probuscita = 0;
            controllocunicolivecchi = 0;
            menu ();}
			break;
			//default:
          //printf("Comando non valido\n");
      //break;
		}
	}while(scelta != '3');
}

/*static char controllo_scelta () {
  char i;
  scanf("%c", &i);
  if ((i == '1') || (i == '2') || (i == '3') || (i == '4')) {
    while ( getchar() != '\n');
    return i;}
  else {
    //printf("Comando non valido\n");
    while ( getchar() != '\n');
    controllo_scelta ();
  }
}*/

static char controllo_scelta () {
  char i;
  scanf("%c", &i);
  if ((i != '1') && (i != '2') && (i != '3') && (i != '4')) {
    while ( getchar() != '\n');
    controllo_scelta ();}
  else {
    while ( getchar () != '\n');
    return i;}
}
