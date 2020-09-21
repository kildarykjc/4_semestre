#include <p18f4520.h>
#define RS LATCbits.LATC0
#define E  LATCbits.LATC1
int sinal_0, aux;

void Delay_LCD ();
void Envia_Comando_Lcd (char comando);
void Envia_Dado_Lcd (char dado);
void ISR_baixa_prioridade();
void ISR_alta_prioridade();

#pragma code int_alta = 0x0008

void int_alta(void)
{
	_asm
		GOTO ISR_alta_prioridade	// Desvia o programa para a fun??o ISR_alta_prioridade.
	_endasm
}
#pragma code


#pragma code int_baixa = 0x0018

void Delay_LCD () // tempo ~ 1ms 
{
	int i;
	for (i=0;i<1000;i++){}
}

void Envia_Comando_Lcd (char comando) 
{
	E=0; 
	RS=0; 

    LATD = comando;

	E=1;
	E=0; 

	Delay_LCD(); 
}

void Envia_Dado_Lcd (char dado)
{
	E=0;
	RS=1; // Seleciona o registrador de dados(LCD)
	
    LATD = dado;

	E=1;
	E=0;
	
	Delay_LCD();
}


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
	if (INTCONbits.INT0IF == 1 || INTCON3bits.INT1IF == 1 || INTCON3bits.INT2IF == 1 )
	{
		LATCbits.LATC0=~LATCbits.LATC0;
		INTCONbits.INT0IF = 0;
		INTCON3bits.INT1IF = 0;
		INTCON3bits.INT2IF = 0;
	}	


}

#pragma interrupt ISR_baixa_prioridade

void ISR_baixa_prioridade()
{
}


void main()
{
	// configura??o da interrup??o externa 0
	
	TRISC=0;
	TRISD=0;
	
	Delay_LCD ();
	Envia_Comando_Lcd (0x38);
	Envia_Comando_Lcd (0x0C);
	Envia_Comando_Lcd (0x0E);
    Envia_Comando_Lcd (0x01);

	ADCON0 = 0B00000001;
    ADCON1 = 0B00001011;
    ADCON2 = 0B10111100;

	while(1)
	{	 
		ADCON0bits.GO = 1; 
        while (ADCON0bits.GO) {};
        {
            Envia_Comando_Lcd(0x80);
            sinal_0 = ADRESH*256 + ADRESL;

            aux = sinal_0/1000;
            aux = aux +0x30;
            Envia_Dado_Lcd (aux);
            sinal_0 = sinal_0%1000;
              
            aux = sinal_0/100;
            aux = aux +0x30;
            Envia_Dado_Lcd (aux);
            sinal_0 = sinal_0%100;
            
            aux = sinal_0/10;
            aux = aux +0x30;
            Envia_Dado_Lcd (aux);
            sinal_0 = sinal_0%10; 
            
            aux = sinal_0/1;
            aux = aux +0x30;
            Envia_Dado_Lcd (aux);
            sinal_0 = sinal_0%1;
        }
	}
}