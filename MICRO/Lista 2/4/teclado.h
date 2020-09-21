#ifndef KEYPAD_H
#define	KEYPAD_H

#define PB7     7 
#define PB6     6
#define PB5     5
#define PB4     4
#define PB3     3
#define PB2     2
#define PB1     1
#define PB0     0

/* LINHAS-SAIDAS */
#define ROW1   PB0
#define ROW2   PB1
#define ROW3   PB2
#define ROW4   PB3
/* COLUNAS-ENTRADAS */
#define COL1   PB4
#define COL2   PB5
#define COL3   PB6
#define COL4   PB7

#define PTECLADO  TRISB
#define FILAS     LATB
#define COLUMNAS  PORTB

void teclado_init (void);
char teclado_getc(void);

#endif	/* KEYPAD_H */

