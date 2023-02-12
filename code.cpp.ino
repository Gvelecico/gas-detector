#include<LiquidCrystal.h>
int sensorPin = 0; //temperatura
int auxDisplay =0;
int anteDis =1;
LiquidCrystal lcd(13,12,6,7,10,11);
void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT); //LED VERDE 
  pinMode(3, OUTPUT); //LED AMARELO
  pinMode(4, OUTPUT); //LED LARANJA
  pinMode(5, OUTPUT); //LED VERMELHO
  pinMode(9, OUTPUT); //ALARME
  pinMode(8, OUTPUT); //MOTOR
  lcd.begin(16,2);
}
 
void loop()
{
 //sensor temperatura
 int reading = analogRead(A1);
 // USAR 5 VOLTS PARA O MEDIDOR DE TEMPERATURA
 float voltagem = reading * 4.68;
 voltagem /= 1024.0;
 float temperatura = (voltagem - 0.5) * 100;
 //=========================================
 
 //sensor gas
 int gas = analogRead(A0); 

 //codigo
  if(temperatura < 52 && gas <86){ 
    anteDis = auxDisplay;
    auxDisplay=1;
  }
  else if(temperatura >=52 && gas >= 86){
    anteDis = auxDisplay;
    auxDisplay=2;
  }
  
  else if(temperatura >=52 || gas >= 86){
    anteDis = auxDisplay;
    auxDisplay=3;
  }

  if(anteDis != auxDisplay){
    
   switch(auxDisplay){
     case 1:
      lcd.clear();
      noTone(9);
      digitalWrite(4, LOW);
      digitalWrite(3,LOW);
      digitalWrite(5,LOW);
      digitalWrite(8,LOW);
      digitalWrite(2,HIGH);
      lcd.print("SEGURO");
     break;
     
     case 2:
      lcd.clear();
      digitalWrite(2,LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(8,HIGH);
      tone(9,440);
      lcd.print("PERIGO");
     break;
     
     case 3:
      lcd.clear();
      noTone(9);
      digitalWrite(2,LOW);
      digitalWrite(5,LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(8,HIGH);
      lcd.print("CUIDADO"); 
     break;
   } 

  }
  
 //TESTE TERMINAL 
 //Serial.print(temperatura); //medidor de temp
 //Serial.println(" GRAUS C"); //medidor de temp
 //Serial.println("Gas: " + (String)gas );
 //digitalWrite(5,LOW); 
}

