#include <p18f4520.h>

void ISR_baixa_prioridade();
void ISR_alta_prioridade();

#pragma code int_alta = 0x0008

void int_alta(void)
{
	_asm
		GOTO ISR_alta_prioridade	// Desvia o programa para a função ISR_alta_prioridade.
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
	// configuração da interrupção externa 0
	
	ADCON1 = 0b00001111;		// desabilitar as entradas analógicas
	TRISBbits.RB0 =	1;			// colocar o pino como entrada B0
	TRISBbits.RB1 =	1;			// colocar o pino como entrada B1
	TRISBbits.RB2 =	1;			// colocar o pino como entrada B2

	TRISCbits.RC0 = 0;			// configura LED

	INTCONbits.INT0IF = 0;		// desativou o IF
	INTCONbits.INT0IE  = 1;		// habilita interrupção externa 0 (INT0)

	INTCON3bits.INT1IF = 0;		// desativou o IF
	INTCON3bits.INT1IE  = 1;		// habilita interrupção externa 1 (INT0)

	INTCON3bits.INT2IF = 0;		// desativou o IF
	INTCON3bits.INT2IE  = 1;		// habilita interrupção externa 1 (INT0)

	INTCONbits.GIE  = 1;		// habilita o sistema de interrupção	
	
	while(1)
	{	
		
	}
}
