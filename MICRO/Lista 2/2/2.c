
#include <p18f4520.h>

#define Porta_Lcd PORTD
#define RS_1 PORTCbits.RC0
#define RS_2 PORTCbits.RC3
#define E_1 PORTCbits.RC1
#define E_2 PORTCbits.RC2

void Envia_Comando_Lcd_1 (char comando);
void Envia_Comando_Lcd_2 (char comando);
void Envia_Dado_Lcd_1 (char dado);
void Envia_Dado_Lcd_2 (char dado);
void Inicializa_Lcd_1 (void);
void Inicializa_Lcd_2 (void);
void Print_Mensagem_Lcd_1 (char *mensagem);
void Print_Mensagem_Lcd_2 (char *mensagem);
void Delay_inicializacao_LCD();

char mensagem1 [] = "Casa";
char mensagem2 [] = "House";

void Delay_LCD () // tempo ~ 1ms 
{
	int i;
	for (i=0;i<400;i++){}
}

void Envia_Comando_Lcd_1 (char comando) // Envia_Comando_Lcd (0x38)
{
    E_1=0; // LCD desabilitado
	E_2=0;
	RS_1=0; //seleciona o envio de instrução

	E_1=1;
	Porta_Lcd=comando; // Envia a metade alta (D4-D7)
	E_1=0; // Habilita o LCD a receber informação

	E_1=1; // Prepara para transferir dados
	comando = comando<<4;
	Porta_Lcd=comando;
	E_1=0; // Habilita o lcd a receber a informacao

	Delay_LCD(); // Da o delay sugerido pelo fabricante
}

void Envia_Comando_Lcd_2(char comando) // Envia_Comando_Lcd (0x38)
{
	E_1=0;
    E_2=0; // LCD desabilitado
	RS_2=0; //seleciona o envio de instrução

	E_2=1;
	Porta_Lcd=comando; // Envia a metade alta (D4-D7)
	E_2=0; // Habilita o LCD a receber informação

	E_2=1; // Prepara para transferir dados
	comando = comando<<4;
	Porta_Lcd=comando;
	E_2=0; // Habilita o lcd a receber a informacao

	Delay_LCD(); // Da o delay sugerido pelo fabricante
}

void Envia_Dado_Lcd_1 (char dado)
{
	E_1=0;
	E_2=0;
	RS_1=1; // Seleciona o registrador de dados(LCD)
	RS_2=0;
	
	E_1=1;
	Porta_Lcd=dado;
	E_1=0;
	
	E_1=1;
	dado=dado<<4;
	Porta_Lcd=dado;
	E_1=0;

	Delay_LCD();
}

void Envia_Dado_Lcd_2 (char dado)
{
	E_1=0;
	E_2=0;
	RS_1=0; // Seleciona o registrador de dados(LCD)
	RS_2=1;
	
	E_2=1;
	Porta_Lcd=dado;
	E_2=0;
	
	E_2=1;
	dado=dado<<4;
	Porta_Lcd=dado;
	E_2=0;

	Delay_LCD();
}

void Inicializa_Lcd_1 (void)
{
	Delay_inicializacao_LCD ();
	Envia_Comando_Lcd_1 (0b000000010); // Lcd 4 bits
	Envia_Comando_Lcd_1 (0b001001000); // 
	Envia_Comando_Lcd_1 (0b000001110); // 
	Envia_Comando_Lcd_1 (0b000000001); // 
    
}
void Inicializa_Lcd_2 (void)
{
	Delay_inicializacao_LCD ();
	Envia_Comando_Lcd_2 (0b000000010); // Lcd 4 bits
	Envia_Comando_Lcd_2 (0b001001000); // 
	Envia_Comando_Lcd_2 (0b000001110); // 
	Envia_Comando_Lcd_2 (0b000000001); // 
   
}

void Print_Mensagem_Lcd_1 (char *mensagem)
{
	int i=0;
	while (mensagem[i]) {
		Envia_Dado_Lcd_1 (mensagem[i]);
		i++;
	}
}

void Print_Mensagem_Lcd_2 (char *mensagem)
{
	int i=0;
	while (mensagem[i]) {
		Envia_Dado_Lcd_2 (mensagem[i]);
		i++;
	}
}

void Delay_inicializacao_LCD () // tempo ~ 1ms
{
	int i;
	for (i=0;i<4000;i++) {}
}

void main()
{
	int i;
	TRISC=0b11110000; // Pinos de controle do LCD como saida
	TRISD=0b00000000; // Configura a porta do lcd

	Inicializa_Lcd_1 ();
    Print_Mensagem_Lcd_1 (mensagem1);
	
 	Inicializa_Lcd_2 ();
    Print_Mensagem_Lcd_2 (mensagem2);
   
	while(1){
		
    }
  
}