#include "gamelib.h"

static struct Caverna *Pca = NULL;        //primo cunicolo arvais
static struct Caverna *Pch = NULL;    //primo cunicolo hartornen;
static struct Scavatrice arvais;
static struct Scavatrice hartornen;
void crea_cunicoli ();
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
static int probscontro = 3; //percentuale progressiva scontro
void gioca ();


static void ins_caverna (struct Caverna **Pc) {
  int scelta;
//Dichiarazione nuova caverna
struct Caverna *nc =(struct Caverna*) malloc(sizeof(struct Caverna));  //nuova caverna
  printf("Inserire un valore di a\n");
  scanf("%d", &(nc->a));
  nc->avanti = NULL;
  nc->destra = NULL;
  nc->sinistra = NULL;

//Menù direzione creazione nuova caverna
printf("Inserire una direzione\n");
printf("1 per creare una caverna di fronte\n");
printf("2 per creare una caverna a destra\n");
printf("3 per creare una caverna a sinistra\n");
scanf("%d", &scelta);

    if (*Pc == NULL) {
      *Pc = nc;
      }
      else {
  switch (scelta) {
    //Caverna avanti
    case 1:
      nc->avanti = *Pc;
      nc->destra = NULL;
      nc->sinistra = NULL;
      *Pc = nc;
    break;
    //caverna a destra
    case 2:
      nc->avanti = NULL;
      nc->destra = *Pc;
      nc->sinistra = NULL;
      *Pc = nc;
    break;
    //caverna a sinistra
    case 3:
      nc->avanti = NULL;
      nc->destra = NULL;
      nc->sinistra = *Pc;
      *Pc = nc;
      break;
      //case 4:
        //return;
      default:
        printf("Comando non valido\n");
      break;
           }
     }
     //system("clear");
}

void crea_cunicoli () {
  int scelta = 0;
  int scelta2 = 0;
  int i = 0;
  int j = 0;
  printf("Creazione caverne famiglia Arvais\n");
  while (i <= 10) {
    //menù scelta iniziale
  printf("Effettuare una scelta\n");
  printf("Premere 1 per creare cunicolo\n");
  printf("Premere 2 per cancellare una caverna precedente\n");
  printf("Premere 3 per stampare i cunicoli creati\n");
  printf("Premere 4 per uscire\n");
  scanf("%d", &scelta);

  switch (scelta) {
    case 1:
      ins_caverna (&Pca);
      stato_caverna (&Pca);
      fimprevisto (&Pca);
      fmelassa (&Pca);
      fmateriali (&Pca);
      i++;
    break;
    case 2:
      canc_caverna (&Pca);
    break;
    case 3:
      stampa_lista (&Pca);
    break;
    case 4:
        printf("Errore: creare minimo 10 caverne oltre quella iniziale\n");
    break;
    default:
      printf("Comando non valido\n");
       }
  }
  system("clear");
  printf("Creazione caverne famiglia Hartornen\n");

  while (j <= 10) {
    //menù scelta iniziale
  printf("Effettuare una scelta\n");
  printf("Premere 1 per creare cunicolo\n");
  printf("Premere 2 per cancellare un cunicolo precedente\n");
  printf("Premere 3 per stampare i cunicoli creati\n");
  printf("Premere 4 per uscire\n");
  scanf("%d", &scelta2);

  switch (scelta2) {
    case 1:
      ins_caverna (&Pch);
      stato_caverna (&Pch);
      fimprevisto (&Pch);
      fmelassa (&Pch);
      fmateriali (&Pch);
      j++;
    break;
    case 2:
      canc_caverna (&Pch);
    break;
    case 3:
      stampa_lista (&Pch);
    break;
    case 4:
      printf("Errore: creare minimo 10 caverne oltre quella iniziale\n");
    break;
    default:
      printf("Comando non valido\n");
    }
  }
  system("clear");
}

static void stampa_lista (struct Caverna **Pc) {
  if(*Pc == NULL) {
      printf("Non ci sono caverne\n"); }
  else {
    struct Caverna* sonda = *Pc;

    do {
      if (sonda->tipo_caverna == 0)
        printf("Valore: %d, Tipo: Normale\n", sonda-> a);
      else if (sonda->tipo_caverna == 1)
        printf("Valore: %d, Tipo: Speciale\n", sonda-> a);
      else
        printf("Valore: %d, Tipo: Accidentata\n", sonda-> a);
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
  int scelta;
  //Menù stato caverna
  printf("Di che tipo deve essere la caverna?\n");
  printf("Premere 1 per creare una caverna normale\n");
  printf("Premere 2 per creare una caverna speciale\n");
  printf("Premere 3 per creare una caverna accidentata\n");
  scanf("%d", &scelta);

  switch (scelta) {
    case 1:
      (*Pc)->tipo_caverna = normale;
      break;
    case 2:
      (*Pc)->tipo_caverna = speciale;
      break;
    case 3:
      (*Pc)->tipo_caverna = accidentata;
      break;
    case 4:
      printf("Comando non valido\n");
      break;
    default:
      return;
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
  int scelta;
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
  scanf("%d", &scelta);

  switch (scelta) {
    case 1:
        avanza (&Pca, &arvais);
    break;
    case 2:
        abbatti (&Pca, &arvais);
        fimprevisto (&Pca);
        fmelassa (&Pca);
    break;
    case 3:
        printf("Puoi aggirare solo in seguito ad un crollo\n");
    break;
    case 4:
        if ((Pca)->tipo_caverna == uscita) {
          printf("Sei uscito dalla caverna\n");
          arvais.stato = uscito;}
        else {
          printf("Non puoi uscire fino a quando non trovi l'uscita\n");
          }
    break;
    default:
    printf("Inserire un comando valido\n");
  }
  //controllo livello serbatoio
  if (arvais.serbatoio_energia < 0) {
    printf("La scavatrice si è distrutta, sei morto!\n");
    arvais.stato = morto;}
  //controllo probabilità probscontro
  int probabilita = 0;
  probabilita = prob ();
  printf("Valore %d\n", probscontro);
  if (probabilita < probscontro)
    scontrofinale ();
  else
      probscontro = probscontro + 3;

}

static void turnofinaleArvais () {
  int danno = 0;
  int scelta;
  printf("TURNO ARVAIS\n");
  printf("Punti vita: %d\n", arvais.punti_vita);
  printf("Punti attacco: %d\n", arvais.punti_attacco);
  printf("Punti difesa: %d\n", arvais.punti_difesa);
  printf("Probabilità critico: %d\n", arvais.prob_critico);
  printf("\n\n");
  printf("Cosa vuoi fare\n");
  printf("Premere 1 per attaccare\n");
  scanf("%d", &scelta);

  switch (scelta) {
    case 1:
    danno = ((arvais.punti_attacco - hartornen.punti_difesa)*probcritico ());
      if (danno < 0)
        danno = 1;
      hartornen.punti_vita = hartornen.punti_vita - danno;
    break;
    default:
      printf("Comando non valido\n");
    break;
  }
  if (hartornen.punti_vita < 0)
    hartornen.stato = morto;
  system("clear");
  printf("La scavatrice Arvais ha totalizzato %d danni/o\n", danno);
}

static void turnoHartornen () {
  int scelta;
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
  scanf("%d", &scelta);

  switch (scelta) {
    case 1:
        avanza (&Pch, &hartornen);
    break;
    case 2:
        abbatti (&Pch, &hartornen);
        fmelassa (&Pch);
        fimprevisto (&Pch);
    break;
    case 3:
        printf("Puoi aggirare solo in seguito ad un crollo\n");
    break;
    case 4:
      if ((Pch)->tipo_caverna == uscita)
        printf("Sei uscito dalla caverna\n");
      else
        printf("Non puoi uscire fino a quando non trovi l'uscita\n");
    break;
    default:
    printf("Comando non valido\n");
  }
  if (hartornen.serbatoio_energia < 0) {
    printf("La scavatrice si è distrutta, sei morto!\n");
    hartornen.stato = morto;}
    //probabilità scontro finale
int probabilita = 0;
probabilita = prob ();
if (probabilita < probscontro)
      scontrofinale ();
else
      probscontro = probscontro + 3;
}

static void turnofinaleHartornen () {
  int danno = 0;
  int scelta;
  printf("TURNO HARTORNEN\n");
  printf("Punti vita: %d\n", hartornen.punti_vita);
  printf("Punti attacco: %d\n", hartornen.punti_attacco);
  printf("Punti difesa: %d\n", hartornen.punti_difesa);
  printf("Probabilità critico: %d\n", hartornen.prob_critico);
  printf("\n\n");
  printf("Cosa vuoi fare?\n");
  printf("Premere 1 per attaccare\n");
  scanf("%d", &scelta);

  switch (scelta) {
    case 1:
    danno = ((hartornen.punti_attacco - hartornen.punti_difesa)*probcritico ());
      if (danno < 0)
        danno = 1;
      arvais.punti_vita = arvais.punti_vita - danno;
    break;
    default:
      printf("Comando non valido\n");
    break;
  }
  if (arvais.punti_vita < 0)
    arvais.stato = morto;
  system("clear");
  printf("La scavatrice Hartornen ha totalizzato %d danni/o\n", danno);
}

static void avanza (struct Caverna **Pc, struct Scavatrice *fam) {
  int primascelta;
  (*fam).posizione = *Pc;
  system("clear");
  if ((*Pc)->avanti==NULL && (*Pc)->destra==NULL && (*Pc)->sinistra==NULL) {
        printf("Non ci sono ulteriori caverne\n\n");
        return;}
  //controllo crollo
  prob ();
  if (prob () <= 25) {
    printf("Si è verificato un crollo improvviso\n\n");
    printf("Cosa vuoi fare?\n");
    printf("Premere 1 per aggirare\n");
    printf("Premere 2 per abbattere\n");
    scanf("%d", &primascelta);

    switch (primascelta) {
      case 1:
          aggira (&Pca, &arvais);
      break;
      case 2:
          abbatti (&Pca, &arvais);
          fimprevisto (&Pca);
          fmelassa (&Pca);
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
  //else
    //uscita

    //quantità melassa
  if ((*Pc)->melassa == poca) {
    int scelta;
    printf("La caverna contiene poca melassa: scavando, ne guadagni 1 unita\n\n");
    printf("In quale serbatoio vuoi metterla?\n");
    printf("Premere 1 per metterla nel serbatoio di energia\n");
    printf("Premere 2 per metterla nel serbatoio di raccolta\n");
    scanf("%d", &scelta);

    switch (scelta) {
      case 1:
        (*fam).serbatoio_energia++;
    break;
      case 2:
        (*fam).serbatoio_raccolta++;
    break;
    default:
        printf("Comando non valido\n");
      }
  }
  else if ((*Pc)->melassa == molta) {
    int scelta2;
    printf("La caverna contiene molta melassa: scavando, ne guadagni 3 unita\n\n");
    printf("In quale serbatoio vuoi metterla?\n");
    printf("Premere 1 per metterla nel serbatoio di energia\n");
    printf("Premere 2 per metterla nel serbatoio di raccolta\n");
    scanf("%d", &scelta2);

    switch (scelta2) {
    case 1:
        (*fam).serbatoio_energia += 3;
    break;
    case 2:
        (*fam).serbatoio_raccolta += 3;
    break;
    default:
        printf("Comando non valido\n");
    }
   }
   //menu potenziamento
   if ((*Pc)->potenziamento == un_materiale) {
    int scelta3;
    printf("La caverna contiene 1 materiale potenziamento. Cosa vuoi potenziare?\n");
    printf("Premere 1 per Punti Vita\n");
    printf("Premere 2 per Punti Attacco\n");
    printf("Premere 3 per Punti Difesa\n");
    scanf("%d", &scelta3);

    switch (scelta3) {
      case 1:
        (*fam).punti_vita += 1;
      break;
      case 2:
        (*fam).punti_attacco += 1;
      break;
      case 3:
        (*fam).punti_difesa += 1;
      break;
      default:
        printf("Comando non valido\n");
    }
  }
  if ((*Pc)->potenziamento == tre_materiali) {
   int scelta4;
   printf("La caverna contiene 3 materiali potenziamento. Cosa vuoi potenziare?\n");
   printf("Premere 1 per Punti Vita\n");
   printf("Premere 2 per Punti Attacco\n");
   printf("Premere 3 per Punti Difesa\n");
   scanf("%d", &scelta4);

   switch (scelta4) {
     case 1:
       (*fam).punti_vita += 3;
     break;
     case 2:
       (*fam).punti_attacco += 3;
     break;
     case 3:
       (*fam).punti_difesa += 3;
     break;
     default:
       printf("Comando non valido\n");
   }
  }
 }
}

static void abbatti (struct Caverna **Pc, struct Scavatrice *fam) {
  int scelta = 0;
  //Dichiarazione nuova caverna
struct Caverna *abbatti = (struct Caverna*)malloc(sizeof(struct Caverna));
abbatti->avanti = NULL;
abbatti->destra = NULL;
abbatti->sinistra = NULL;

printf("Dove vuoi abbattere?\n");
printf("Premere 1 per abbattere avanti\n");
printf("Premere 2 per abbattere a destra\n");
printf("Premere 3 per abbattere a sinistra\n");
scanf("%d", &scelta);

switch (scelta) {
  case 1:
    if ((*Pc)->avanti != NULL)
        printf("Spiacente, esiste già una caverna in quella direzione\n");
    else {
        abbatti->avanti = *Pc;
        abbatti->destra = NULL;
        abbatti->sinistra = NULL;
        *Pc = abbatti;
        (*fam).serbatoio_energia--;
    }
  break;
  case 2:
    if ((*Pc)->destra != NULL)
        printf("Spiacente, esiste già una caverna in quella direzione\n");
    else {
        abbatti->avanti = NULL;
        abbatti->destra = *Pc;
        abbatti->sinistra = NULL;
        *Pc = abbatti;
        (*fam).serbatoio_energia--;
    }
  break;
  case 3:
   if ((*Pc)->sinistra != NULL)
        printf("Spiacente, esiste già una caverna in quella direzione\n");
   else {
        abbatti->avanti = NULL;
        abbatti->destra = NULL;
        abbatti->sinistra = *Pc;
        *Pc = abbatti;
        (*fam).serbatoio_energia--;
   }
   break;
   default:
        printf("Comando non valido\n");
  }
}

static void aggira (struct Caverna **Pc, struct Scavatrice *fam) {
  struct Caverna *aggira = (struct Caverna*)malloc(sizeof(struct Caverna));
      aggira->avanti = NULL;
      aggira->destra = NULL;
      aggira->sinistra = NULL;

      if ((*Pc)->avanti != NULL)
          printf("Aggiri la caverna\n");
      else {
          aggira->avanti = *Pc;
          aggira->destra = NULL;
          aggira->sinistra = NULL;
          *Pc = aggira;
          *Pc = (*Pc)->avanti;
        }
      if ((*Pc)->destra != NULL)
          printf("Aggiri la caverna\n");
      else {
          aggira->avanti = NULL;
          aggira->destra = *Pc;
          aggira->sinistra = NULL;
          *Pc = aggira;
          *Pc = (*Pc)->destra;
      }
     if ((*Pc)->sinistra != NULL)
          printf("Aggiri la caverna\n");
     else {
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
         int scelta;
         printf("La caverna contiene poca melassa: scavando, ne guadagni 1 unita\n\n");
         printf("In quale serbatoio vuoi metterla?\n");
         printf("Premere 1 per metterla nel serbatoio di energia\n");
         printf("Premere 2 per metterla nel serbatoio di raccolta\n");
         scanf("%d", &scelta);

         switch (scelta) {
           case 1:
             (*fam).serbatoio_energia++;
         break;
           case 2:
             (*fam).serbatoio_raccolta++;
         break;
         default:
             printf("Comando non valido\n");
           }
       }
       else if ((*Pc)->melassa == molta) {
         int scelta2;
         printf("La caverna contiene molta melassa: scavando, ne guadagni 3 unita\n\n");
         printf("In quale serbatoio vuoi metterla?\n");
         printf("Premere 1 per metterla nel serbatoio di energia\n");
         printf("Premere 2 per metterla nel serbatoio di raccolta\n");
         scanf("%d", &scelta2);

         switch (scelta2) {
         case 1:
             (*fam).serbatoio_energia += 3;
         break;
         case 2:
             (*fam).serbatoio_raccolta += 3;
         break;
         default:
             printf("Comando non valido\n");
         }
        }

}

static void controllofinale () {
    //controllo stato vita
  if (arvais.stato == morto)
    printf("La scavatrice Arvais è esplosa. Gli Hartornen vincono quindi ottengono il controllo del territorio\n");
  else if (hartornen.stato == morto)
    printf("La scavatrice Hartornen è esplosa. Gli Arvais vincono quindi ottengono il controllo del territorio\n");

    //controllo stato uscito
  if (arvais.stato == uscito && hartornen.stato == uscito) {
      if (arvais.serbatoio_raccolta > hartornen.serbatoio_raccolta)
        printf("Gli Arvais hanno raccolto più melassa. Gli Arvais vincono quindi ottengono il controllo del territorio\n");
      else if (arvais.serbatoio_raccolta < hartornen.serbatoio_raccolta)
        printf("Gli Hartornen hanno raccolto più melassa. Gli Hartornen vincono quindi ottengono il controllo del territorio\n");
      else if (arvais.serbatoio_raccolta == hartornen.serbatoio_raccolta)
        scontrofinale ();}
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
  printf("Le due scavatrici si sono incrociate: sei giunto allo scontro finale\n");
  while (1) {
    turnofinaleArvais ();
    controllofinale ();
    turnofinaleHartornen ();
    controllofinale ();}
}


void gioca () {
  statfamiglia ();
  while (1) {
  turnoArvais ();
  turnoHartornen ();
}
  controllofinale ();
}
