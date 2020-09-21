#include <p18f4520.h>
#include <stdio.h>

#define coluna1 LATCbits.LATC7
#define coluna2 LATCbits.LATC6
#define coluna3 LATCbits.LATC5

#define linha1 PORTBbits.RB4
#define linha2 PORTBbits.RB5
#define linha3 PORTBbits.RB6
#define linha4 PORTBbits.RB7

#define Porta_Lcd PORTD
#define RS PORTCbits.RC0
#define E PORTCbits.RC1
int aux;

char tecla;

char LE_Teclado (void);
void ISR_baixa_prioridade();
void ISR_alta_prioridade();

//void disp_horario();                           //Função para mostrar as horas
//void relogio();                                //Função de controle das variáveis do relógio
//void ajusta_relogio();                         //Função para ajustar o relógio

void Envia_Comando_Lcd (char comando);
void Envia_Dado_Lcd (char dado);
void Inicializa_Lcd (void);
void Print_Mensagem_Lcd (char *mensagem);
void Delay_inicializacao_LCD();
void ajusta_Relogio(char *aux);

char *text [] = "00:00:00";                      //Ponteiro para texto do relógio no LCD
char flags = 0x00;                             //Registrador auxiliar para armazenar estado dos botões

char horas = 0x00, minutos = 0x00, segundos = 0x00;          //Variáveis do relógio

char control_adj_watch = 0x05;                 //Controle do ajuste do relógiO

char mensagem1 [] = "00:00:00";

#pragma code int_alta = 0x0008

void int_alta(void)
{
    _asm
        GOTO ISR_alta_prioridade
    _endasm
}
#pragma code

#pragma code int_baixa = 0x0018

void int_baixa()
{
    _asm
        GOTO ISR_baixa_prioridade
    _endasm
}

#pragma code

#pragma interrupt ISR_alta_prioridade

void ISR_alta_prioridade()
{
    if (INTCONbits.INT0IF)
    {
        INTCONbits.INT0IF = 0;
    }
    if (INTCONbits.TMR0IF)
    {
        TMR0H = 0xC2;
        TMR0L = 0xF7;
        INTCONbits.TMR0IF = 0;
    }

    if (INTCONbits.RBIF)
    {
        aux = LE_Teclado ();
        if(aux)
        {
            tecla = aux;
			ajusta_Relogio(aux);

        }
        else
        {
            tecla = 0;
        }
        tecla=0;
        coluna1=0;
        coluna2=0;
        coluna3=0;
        INTCONbits.RBIF=0;

    }

}

void ISR_baixa_prioridade()
{
}

void disp_horario()                            //Função para exibir a hora atual
{

     
     mensagem1[7] = segundos%10 + '0';
     mensagem1[6] = segundos/10 + '0';
     mensagem1[4] = minutos%10 + '0';
     mensagem1[3] = minutos/10 + '0';
     mensagem1[1] = horas%10 + '0';
     mensagem1[0] = horas/10 + '0';

     //Print_Mensagem_Lcd (mensagem1);                        //Imprimi o horário no display

}


void relogio()                                 //Função para controle das variáveis do relógio
{
	while(1){
		Print_Mensagem_Lcd (mensagem1);
		
		Envia_Comando_Lcd (0b000000011);
		segundos++;
		mensagem1[7] = segundos%10 + '0';
     	mensagem1[6] = segundos/10 + '0';
   		mensagem1[4] = minutos%10 + '0';
    	mensagem1[3] = minutos/10 + '0';
     	mensagem1[1] = horas%10 + '0';
     	mensagem1[0] = horas/10 + '0'; 
		                             //Incrementa os segundos
	 	if (!linha4)
   		{
       		break;
   			 }
     	if(segundos == 0x3c)                      //Segundos igual a 60?
    	 {                                         //Sim...
        	segundos = 0x00;                      //Reinicia os segundos
        	minutos++;
		                          //Incrementa os minutos
        	 if(minutos == 0x3c)                   //Minutos igual a 60?
         	{                                     //Sim...
           		minutos = 0x00;                    //Reinicia os minutos
           		horas++; 
				                       //Incrementa as horas
            	if(horas == 0x18)                  //Horas igual a 24 ?
           		{                                  //Sim...
            		horas = 0x00;  
				                 //Reinicia as horas
            	} //end if horas

         	} //end if minutos

     	}
     }

}

void ajusta_Relogio(char *aux){
	*aux = LE_Teclado();
	if(*aux == '%'){
		minutos++;
		
		
	}
	if(*aux == ' '){
		horas++;
			
	}

}
char LE_Teclado (void)
{
    coluna1=0;
    coluna2=1;
    coluna3=1;
    if (!linha1)
    {
        //return '3';
    }
    if (!linha2)
    {
       // return '6';
    }
    if (!linha3)
    {
        //return '9';
    }
    if (!linha4)
    {
		//minutos++;
        return '%';
		//*
    }

    coluna1 = 1;
    coluna2 = 0;
    coluna3 = 1;

    if (!linha1)
    {
        //return '2';
    }
    if (!linha2)
    {
        //return '5';
    }
    if (!linha3)
    {
        //return '8';
    }
    if (!linha4)
    {
       // return '0';
    }
    coluna1 = 1;
    coluna2 = 1;
    coluna3 = 0;

    if (!linha1)
    {
        //return '1';
    }
    if (!linha2)
    {
       // return '4';
    }
    if (!linha3)
    {
        //return '7';
    }
    if (!linha4)
    {
	//	horas++;
        return ' ';
		//#
    }

    return 0;
}

void Delay_LCD () // tempo ~ 1ms 
{
	int i;
	for (i=0;i<6000;i++){}
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

	Delay_LCD(); // Da o delay sugerido pelo fabricante
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

	Delay_LCD();
}

void Inicializa_Lcd (void)
{
	Delay_inicializacao_LCD ();
	Envia_Comando_Lcd (0b000000010); // Lcd 4 bits
	Envia_Comando_Lcd (0b001001000); // 
	Envia_Comando_Lcd (0b000001110); // 
	Envia_Comando_Lcd (0b000000001); // 
    
    //Envia_Dado_Lcd ('A');
    //while(1);
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

void main ()
{
	TRISC=0b11111100; // Pinos de controle do LCD como saida
	TRISD=0b00000000; // Configura a porta do lcd
	Inicializa_Lcd ();

	TRISB = 0B11111111;
    TRISCbits.RC5 = 0;
    TRISCbits.RC6 = 0;
    TRISCbits.RC7 = 0;

    ADCON1 = 0b00001111;

    INTCON2bits.INTEDG0 = 0;
    INTCONbits.INT0IF = 0;
    INTCONbits.INT0IE = 1;
    INTCONbits.GIE = 1;


    T0CONbits.TMR0ON = 1;
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS2 = 0;
    T0CONbits.T0PS1 = 0;


    TMR0H = 0xC2;
    TMR0L = 0xF7;

    INTCONbits.TMR0IE = 1;

    //aux = PORTB;
    INTCONbits.RBIF = 0;
    INTCON2bits.RBIP = 1;
    INTCON2bits.RBPU = 0;
    INTCONbits.RBIE = 1;

    coluna1 = 0;
    coluna2 = 0;
    coluna3 = 0;
	
	relogio();
	

    while(1){

	}
}