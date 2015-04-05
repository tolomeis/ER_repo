//******************************************//
//******** VARIABILI DI MOVIMENTO **********//
//******************************************//

void impostaComportamento(){
	//Soglia di distanza dalla torretta frontale per cui il robot si ferma
	sogliaTorrettaFrontale = 33;   //(misure in cm)
	//******************

	//Soglia di distanza dai sensori IR, che comporta il riconoscimento dell'ostacolo.
	sogliaIR= 18;
	//Se l'offset di distanza fra i sensori IR è minore di questo, allora il robot si ferma.
	//Altrimenti sterza aggirando l'ostacolo.
	offsetIR = 10;

	sogliaIR_sterzata = 25;
}


