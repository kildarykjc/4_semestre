
#include <p18f4520.h>

//declarar as suas variaveis de hardware

#define Porta_Lcd PORTD
#define RS PORTCbits.RC0
#define E PORTCbits.RC1

// Teclado

#ifndef column_1
#define column_1 LATCbits.LATC4
#endif
#ifndef column_2
#define column_2 LATCbits.LATC3
#endif
#ifndef column_3
#define column_3 LATCbits.LATC2
#endif

#ifndef row_1
#define row_1 PORTDbits.RD4
#endif
#ifndef row_2
#define row_2 PORTDbits.RD5
#endif
#ifndef row_3
#define row_3 PORTDbits.RD6
#endif
#ifndef row_4
#define row_4 PORTDbits.RD7
#endif

#ifndef NULL_CHAR
#define NULL_CHAR '\0'
#endif

void Envia_Comando_Lcd (char comando);
void Envia_Dado_Lcd (char dado);
void Inicializa_Lcd (void);
void Print_Mensagem_Lcd (char *mensagem);
void Delay_inicializacao_LCD();
void getTeclado();

char read_keyboard();

char mensagem1 [] = "KILDARY JUCA";

void Delay_LCD (int n) // tempo ~ 1ms 
{
   int i;
   for (i=0;i<400*n;i++){}
}

void Envia_Comando_Lcd (char comando) // Envia_Comando_Lcd (0x38)
{
   E=0; // LCD desabilitado
   RS=0; //seleciona o envio de instrução

   E=1;
   Porta_Lcd=comando; // Envia a metade alta (D4-D7)
   E=0; // Habilita o LCD a receber informação

   E=1; // Prepara para transferir dados
   comando = comando<<4;
   Porta_Lcd = comando;
   E=0; // Habilita o lcd a receber a informacao

   Delay_LCD(1); // Da o delay sugerido pelo fabricante
}

void Envia_Dado_Lcd (char dado)
{
   E=0;
   RS=1; // Seleciona o registrador de dados(LCD)
   
   E=1;
   Porta_Lcd=dado;
   E=0;
   
   E=1;
   dado=dado<<4;
   Porta_Lcd=dado;
   E=0;

   Delay_LCD(1);
}

void Inicializa_Lcd (void)
{
   Delay_inicializacao_LCD ();
   Envia_Comando_Lcd (0b000000010); // Lcd 4 bits
   Envia_Comando_Lcd (0b001001000); // 
   Envia_Comando_Lcd (0b000001110); // 
   Envia_Comando_Lcd (0b000000001); // 
    
}

void Print_Mensagem_Lcd (char *mensagem)
{
   int i=0;
   while (mensagem[i]) {
      Envia_Dado_Lcd (mensagem[i]);
      i++;
   }
}

void Delay_inicializacao_LCD () // tempo ~ 1ms
{
   int i;
   for (i=0;i<4000;i++) {}
}

char read_keyboard(){
	char aux = NULL_CHAR;
	column_1 = 0;
	column_2 = 1;
	column_3 = 1;
	if (!row_1){
		aux = '1';
	}
	if (!row_2) {
		aux = '4';
	}
	if (!row_3) {
		aux = '7';
	}
	if (!row_4) {
		aux = '*';
	}

	
	column_1 = 1;
	column_2 = 0;
	column_3 = 1;
	if (!row_1){
		aux = '2';
	}
	if (!row_2) {
		aux = '5';
	}
	if (!row_3) {
		aux = '8';
	}
	if (!row_4) {
		aux = '0';
	}


	column_1 = 1;
	column_2 = 1;
	column_3 = 0;
	if (!row_1){
		aux = '3';
	}
	if (!row_2) {
		aux = '6';
	}
	if (!row_3) {
		aux = '9';
	}
	if (!row_4) {
		aux = '#';
	}


	column_1 = 0;
	column_2 = 0;
	column_3 = 0;
	Delay_LCD (5);
	return aux;
}


void main()
{
   int i;
   TRISB=0b10111100;
   TRISC=0b10111100; // Pinos de controle do LCD como saida
   TRISD=0b00000000; // Configura a porta do lcd
   //Inicializa_Lcd ();
   //Print_Mensagem_Lcd (mensagem1);
   
   while(1){
      getTeclado();
	  //Print_Mensagem_Lcd (mensagem1);
    }
  
}

void getTeclado(){
	char tecla = read_keyboard();
	if(tecla != NULL_CHAR){
		//Inicializa_Lcd ();
		Envia_Dado_Lcd (tecla);
	}
	
}
