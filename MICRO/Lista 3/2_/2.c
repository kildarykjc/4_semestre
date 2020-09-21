#include <p18f4520.h>

#define coluna1 LATCbits.LATC7
#define coluna2 LATCbits.LATC6
#define coluna3 LATCbits.LATC5

#define linha1 PORTBbits.RB4
#define linha2 PORTBbits.RB5
#define linha3 PORTBbits.RB6
#define linha4 PORTBbits.RB7

char aux;
char tecla;

char LE_Teclado (void);
void ISR_baixa_prioridade();
void ISR_alta_prioridade();

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

char LE_Teclado (void)
{
    coluna1=0;
    coluna2=1;
    coluna3=1;
    if (!linha1)
    {
        return '1';
    }
    if (!linha2)
    {
        return '4';
    }
    if (!linha3)
    {
        return '7';
    }
    if (!linha4)
    {
        return ' ';
    }

    coluna1 = 1;
    coluna2 = 0;
    coluna3 = 1;

    if (!linha1)
    {
        return '2';
    }
    if (!linha2)
    {
        return '5';
    }
    if (!linha3)
    {
        return '8';
    }
    if (!linha4)
    {
        return'0';
    }
    coluna1 = 1;
    coluna2 = 1;
    coluna3 = 0;

    if (!linha1)
    {
        return '3';
    }
    if (!linha2)
    {
        return '6';
    }
    if (!linha3)
    {
        return '9';
    }
    if (!linha4);
    {
        return'%';
    }

    return 0;
}

void main ()
{
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
    T0CONbits.T0PS2 = 1;
    T0CONbits.T0PS1 = 1;
	T0CONbits.T0PS0 = 0;


    TMR0H = 0xC2;
    TMR0L = 0xF7;

    INTCONbits.TMR0IE = 1;

	// Configuração da porta B
	
	INTCONbits.RBIF = 0;
	INTCON2bits.RBIP = 1;
	INTCON2bits.RBPU = 0;
	INTCONbits.RBIE = 1;
    
    coluna1 = 0;
    coluna2 = 0;
    coluna3 = 0;

    while(1){}
}