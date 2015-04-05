//******************************************************//
//****** VERSIONE 2.3 -  COMPATIBILITÀ CON HARDWARE AGGIORNATI//
//******************************************************//



#include <Servo.h>


#define dir_destro 12     //***************************************************
#define dir_sinistro 13   //Definisco i pin dell' L298N per il controllo motori
#define vel_destro 3      //***************************************************
#define vel_sinistro 11
//Definisco i pin dei sensori e delle luci
#define sens_luce 3
#define luci 8   



byte destra = 170;      //posizioni per il servo
byte sinistra = 10;
byte avanti = 90;

Servo servo1; //creo servo 

//**** VARIABILI DI DISTANZE MEMORIZZATE ****
int distanza; //distanza oggetto   
int torrettaSinistra;
int torrettaDestra;
int sensoreDestro;
int sensoreSinistro;
int luce;
int torrettaDavanti;
//***************

//*********** VARIABILI DI COMPORTAMENTO**************
//*** Vengono definite nella scheda Comportamento***
//**** tramite la funzione impostaComportamento()***
int sogliaTorrettaFrontale;
int sogliaIR;
int offsetIR;
int dist_Retromarcia;
int sogliaIR_sterzata;
//****** FINE COMPORTAMENTO*********




void setup() {
  impostaComportamento();
  Serial.begin(9600);
  pinMode(dir_destro, OUTPUT);  // Imposto PinOut
  pinMode(dir_sinistro, OUTPUT);
  pinMode(vel_destro, OUTPUT);
  pinMode(vel_sinistro, OUTPUT);
  pinMode(luci, OUTPUT);
  servo1.attach(9);
}



void loop() {

  servo1.write(avanti);

  //****************************************************************
  //**********INIZIO A LEGGERE I DATI DEI SENSORI******************
  //**************************************************************

  sensoreSinistro = leggiSX();
  sensoreDestro = leggiDX();
  luce= abs(analogRead(sens_luce));
  torrettaDavanti = leggiTorretta();


  Serial.print("Torretta: ");
  Serial.println(torrettaDavanti);
  Serial.print("IR_DX: ");
  Serial.println(sensoreDestro);
  Serial.print("IR_SX: ");
  Serial.println(sensoreSinistro);
  Serial.println("*******");
 // ***********************************************************************************************************
 //FINE LETTURA DEI SENSORI. INIZIA L'ANALISI DELLA SITUAZIONE
 //************************************************************************************************************
 if (torrettaDavanti < sogliaTorrettaFrontale){            //test eseguito solo se torretta davanti trova ostacolo o se precedentemente fermo.
   Stop();
   delay(100); 
   Test();

 } else if ((abs(sensoreSinistro - sensoreDestro) < 9) && (sensoreDestro < sogliaIR) && (sensoreSinistro < sogliaIR) ){  // Si dichara che l'oggetto DEVE coprire i 2 sensori freontali,
 Stop();                                                                                                     
 delay(100);                                                                                       
 Test();

 }else if(sensoreDestro > (sensoreSinistro + 35) && (sensoreSinistro < sogliaIR_sterzata)){     //Se l'ostacolo copre il sensore sinistro e non il destro, allora sterza a destra.
 sterzaDX();
 delay(300);

 }else if (sensoreSinistro > (sensoreDestro + 35)&& (sensoreDestro < sogliaIR_sterzata)){

  sterzaSX();
  delay(300);

  } else{
    Avanti();

  }
   //*******************************************************************
   //***** FINE DELLE CONDIZIONI DI MOVIMENTO. CONTROLLO LUCE***********
   //********************************************************************
   
   if (luce <22){
     digitalWrite(luci,HIGH);
     } else {
       digitalWrite(luci,LOW);
     }



   }

   //***********************************************************
   //***********************************************************
   //fine del ciclo loop. Dichiarazione del Test Torretta
  //***********************************************************
   //**********************************************************

   void Test() {
     delay(150);
       servo1.write(destra);               //giro il servo e aspetto 1 secondo che si stabilizzi
       delay(600);                              //leggo il sensore rivolto a destra e memorizzo la distanza
       torrettaDestra = leggiTorretta();
       delay(400);
       servo1.write(sinistra);                //giro il servo a destra
       delay(1000);                           //leggo la distanza di sinistra e memorizzo
       torrettaSinistra = leggiTorretta();
       delay(400);

       servo1.write(avanti);                                                               //il dislivello tra le verie distanze deve esere di almeno 15 cm

      if ((torrettaDestra > (torrettaSinistra + 10)) && (torrettaDestra > 25)) {          //controllo se nella direzione dove la distanza 
          giraDX();                                                                          //dell'oggetto è maggiore c'è abbastanza spazio per far girare il robot
           delay(1000);          //pausa per stabilizzare il sensore
           
           } else if ((torrettaDestra < (torrettaSinistra + 10)) && (torrettaSinistra > 25)) {
            giraSX();
            delay(1000);

            } else {
              retrocedi(35);
            } 

  }  //****************FINE TEST TORRETTA*******************




