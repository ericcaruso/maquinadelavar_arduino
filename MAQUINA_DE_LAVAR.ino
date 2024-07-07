
#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <SoftwareSerial.h> // INCLUSÃO DA BIBLIOTECA PARA COMUNICAÇÃO SERIAL
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA PARA LCD 16X2
#include <Keypad.h> //INCLUSÃO DE BIBLIOTECA
 
const byte qtdLinhas = 4; //QUANTIDADE DE LINHAS DO TECLADO
const byte qtdColunas = 3; //QUANTIDADE DE COLUNAS DO TECLADO
 
//CONSTRUÇÃO DA MATRIZ DE CARACTERES
char matriz_teclas[qtdLinhas][qtdColunas] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
 
byte PinosqtdLinhas[qtdLinhas] = {0, 1, 2}; //PINOS UTILIZADOS PELAS LINHAS
byte PinosqtdColunas[qtdColunas] = {9}; //PINOS UTILIZADOS PELAS COLUNAS

Keypad meuteclado = Keypad( makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas);


LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

  int enche = 200;
  int lava = 180;
  int bomba = 160;
  int centrif = 100;
  int buzzer = 3;
  
  
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
 Serial.begin(9600); //INICIALIZA A SERIAL
 Serial.println("Aperte uma tecla..."); //IMPRIME O TEXTO NO MONITOR SERIAL
  Serial.println(); //QUEBRA UMA LINHA NO MONITOR SERIALv
 
  pinMode(buzzer,OUTPUT); 
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(10, INPUT_PULLUP);
  lcd.begin (16,2); //SETA A QUANTIDADE DE COLUNAS(16) E O NÚMERO DE LINHAS(2) DO DISPLAY
  lcd.setBacklight(HIGH); //LIGA O BACKLIGHT (LUZ DE FUNDO)
  
  lcd.setCursor(0,0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("MAQUINA PRONTA !"); //IMPRIME O TEXTO NO DISPLAY LCD  
  lcd.setCursor(1,2); //SETA A POSIÇÃO DO CURSOR
  lcd.print("TOQUE P INICIAR"); //IMPRIME O TEXTO NO DISPLAY LCD  
  digitalWrite(4, HIGH); 
  digitalWrite(5, HIGH); 
  digitalWrite(6, HIGH); 
  digitalWrite(7, HIGH); 
  

}

// the loop function runs over and over again forever
void loop() {

   char tecla_pressionada = meuteclado.getKey();

   if (tecla_pressionada){ //SE ALGUMA TECLA FOR PRESSIONADA, FAZ
    Serial.print("Tecla pressionada : "); //IMPRIME O TEXTO NO MONITOR SERIAL
    Serial.println(tecla_pressionada); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
  }

if(digitalRead(10) == LOW) // Se o botão for pressionado
  {
Encher();
 delay(2000);
   }
   
    
     }


void Encher(){  // Função pra ligar as duas válvulas de enchimento de água

 while(enche > 0){
  enche = enche -1;
  lcd.clear();
  lcd.setCursor(0,0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("ENCHENDO..."); //IMPRIME O TEXTO NO DISPLAY LCD  
  lcd.setCursor(1,2); //SETA A POSIÇÃO DO CURSOR
  lcd.print(enche); //IMPRIME O TEXTO NO DISPLAY LCD 
  delay(1000);
  digitalWrite(7, LOW);   // turn the LED on (HIGH is the voltage level)
  if(enche == 0) {
      digitalWrite(7, HIGH);
    Lavar();
  }
 }
}


void Lavar(){  // Função pra ligar o motor e lavar a roupa

  while(lava > 0){
  lava = lava -2;
  lcd.clear();
  lcd.setCursor(0,0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("LAVANDO..."); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.setCursor(1,2); //SETA A POSIÇÃO DO CURSOR
  lcd.print(lava); //IMPRIME O TEXTO NO DISPLAY LCD  
   delay(500);
  digitalWrite(6, LOW);  
   delay(500);
  digitalWrite(6, HIGH); 
    delay(500);
  digitalWrite(5, LOW);  
   delay(500);
  digitalWrite(5 , HIGH); 
  
  if(lava ==0){
    Bomba();
  }
}
}

void Bomba(){  // Função pra ligar a bomba e despejar agua

  while(bomba > 0) {
   bomba = bomba -1;
  lcd.clear();
  lcd.setCursor(0,0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("DESPEJANDO AGUA..."); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.setCursor(1,2); //SETA A POSIÇÃO DO CURSOR
  lcd.print(bomba); //IMPRIME O TEXTO NO DISPLAY LCD 
  digitalWrite(5 , HIGH);
  digitalWrite(6 , HIGH);
  delay(1000);
  digitalWrite(4, LOW); 
  if(bomba == 0) {
  Centrifugar();
  }
 }
}

void Centrifugar(){  // Função pra ligar o motor em paralelo a bomba e iniciar a centrigufação
  
  while(centrif > 0) {
  centrif = centrif -1;
  lcd.clear();
  lcd.setCursor(0,0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("CENTRIFUGANDO..."); //IMPRIME O TEXTO NO DISPLAY LCD
  lcd.setCursor(1,2); //SETA A POSIÇÃO DO CURSOR
  lcd.print(centrif); //IMPRIME O TEXTO NO DISPLAY LCD
    digitalWrite(4, LOW);
    delay(5000);
  digitalWrite(6, LOW); 
    delay(1000);
  if(centrif == 0) {
    Acabar();
  }
 
}
 
}

void Acabar(){  // Função pra ligar o motor em paralelo a bomba e iniciar a centrigufação
  Serial.println("Roupa Lavada, programa terminado...!");
       
  digitalWrite(7,HIGH);   // DESLIGA
  digitalWrite(6, HIGH);   // DESLIGA
  digitalWrite(5, HIGH);   // DESLIGA
  digitalWrite(4, HIGH);   // DESLIGA
  
  lcd.clear();
  lcd.setCursor(0,0); //SETA A POSIÇÃO DO CURSOR
  lcd.print("LAVAGEM CONCLUIDA !"); //IMPRIME O TEXTO NO DISPLAY LCD
  
  delay(500);
  tone(buzzer,900); 
  delay(500);
   noTone(buzzer); 
      delay(500);
  tone(buzzer,900); 
  delay(500);
   noTone(buzzer); 
    delay(500);
  tone(buzzer,900); 
  delay(500);
   noTone(buzzer); 
      delay(500);
  tone(buzzer,900); 
  delay(500);
   noTone(buzzer); 
      delay(500);
  tone(buzzer,900); 
  delay(500);
   noTone(buzzer); 
      delay(500);
  tone(buzzer,900); 
  delay(500);
   noTone(buzzer); 

 
}
