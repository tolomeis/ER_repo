long durata, cm;

int leggiTorretta() {   
 pinMode(4, OUTPUT);
 digitalWrite(4, LOW);
 delayMicroseconds(2);
 digitalWrite(4, HIGH);
 delayMicroseconds(5);
 digitalWrite(4, LOW);
 
 pinMode(4, INPUT);
 durata = pulseIn(4, HIGH);
 cm = durata / 29 / 2;
 cm = constrain(cm, 5, 200);
 return cm;
}


float leggiDX() {
  int sensorValue = analogRead(A1);
  float mvolt = map(sensorValue, 0, 1023, 0, 5000);
  float mm = 1085534.81 * pow(mvolt, -1.2);
  float cm = mm / 10;
  cm = constrain(cm, 6, 70);
  return cm;
}

float leggiSX() {
  int sensorValue = analogRead(A2);
  float mvolt = map(sensorValue, 0, 1023, 0, 5000);
  float mm = 1085534.81 * pow(mvolt, -1.2);
  float cm = mm / 10;
  cm = constrain(cm, 6, 70);
  return cm;
}


void Avanti() {
 digitalWrite(dir_destro, HIGH);
 digitalWrite(dir_sinistro, LOW);
 delay(200);
 analogWrite(vel_destro, 255);
 analogWrite(vel_sinistro, 255);
}


void Stop() {
 analogWrite(vel_destro, 0);
 analogWrite(vel_sinistro, 0);
}



 
void giraDX() {
 digitalWrite(dir_destro, HIGH);
 digitalWrite(dir_sinistro, HIGH);
 delay(200);
 delay(100);
 analogWrite(vel_destro, 255);
 analogWrite(vel_sinistro, 255);
 delay(3500);
 Stop();
}


void giraSX() {
 
 digitalWrite(dir_destro, LOW);
 digitalWrite(dir_sinistro, LOW);
 delay(200);
 analogWrite(vel_destro, 255);
 analogWrite(vel_sinistro, 255);
 delay(3500);
 Stop();
}





void retrocedi(int cm) {
 digitalWrite(dir_destro, LOW);
 digitalWrite(dir_sinistro, HIGH);
 delay(100);
 analogWrite(vel_destro, 255);
 analogWrite(vel_sinistro, 255);
 int tempo = (cm/8)*1000;
 delay(tempo);
 Stop();
 delay(100);
 Test();  

}

void sterzaDX(){
 digitalWrite(dir_destro, HIGH);
 digitalWrite(dir_sinistro, LOW);
 analogWrite(vel_destro, 255);
 analogWrite(vel_sinistro, 0);
}


void sterzaSX(){
 digitalWrite(dir_destro, HIGH);
 digitalWrite(dir_sinistro, LOW);
 delay(200);
 analogWrite(vel_sinistro, 255);
 analogWrite(vel_destro, 0);
}
