// Programa : Display LCD 16x2 e modulo I2C
// Autor : Arduino e Cia
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

//Declaração das constantes
const int led = 8;   //constante led refere-se ao pino digital 8.
const int botao = 2; //constante botão refere-se ao pino digital 2. 

//Variável que conterá os estados do botão (0 LOW, 1 HIGH).
int estadoBotao = 0;
int clicks = 0;
int ultimoEstado = 0;
int x, y = 0;
void setup()
{
 lcd.begin (16,2);
 pinMode(led,OUTPUT);  //Definindo pino digital 8 como de saída.
 pinMode(botao,INPUT); //Definindo pino digital 2 como de entrada. 
 // initialize serial communication:
 Serial.begin(9600);
}
 
void loop()
{
  lcd.setBacklight(HIGH);
  lcd.setCursor(x,y);
  lcd.print("");
  estadoBotao = digitalRead(botao);          
   
  //Verificando o estado do botão para definir se acenderá ou
  //apagará o led.
  if (estadoBotao != ultimoEstado){
    if (estadoBotao == HIGH) {      
      digitalWrite(led,HIGH); //Botão pressionado, acende o led.
      clicks++;
      if(clicks <= 16){lcd.setCursor(0,y++); lcd.print("O");}
      if(clicks == 17){x = 1; y = 0;}
      if(clicks >= 17 && clicks <= 32){lcd.setCursor(x,y++); lcd.print("O");}
      if(clicks == 32){lcd.setCursor(0,0); lcd.print("");}
      if(clicks > 32 && clicks <= 42 ){lcd.setCursor(0,0); lcd.print("CONTINUE TRABAL-"); lcd.setCursor(1,0); lcd.print("CONTINUE TRABAL-"); lcd.print("1HANDO    UNI 42.");}
    } else {
      digitalWrite(led,LOW);  //Botão não pressionado, apaga o led.    
    }
  }
  ultimoEstado = estadoBotao;
}
