void ECmdLCD (char cmd, int i){
	if (i==1){
		E1=0;
		E2=0;         //
		RS=0;         //registrador habilitado para comando
		
		E1=1;
		PLCD=cmd;     //
		E1=0;         //
		
		E1=1;
		cmd=cmd<<4;   //desloamento de 4b para direita
		PLCD=cmd;     //
		E1=0;         //

	}
	if (i==2){
		E1=0;
		E2=0;         //
		RS=0;         //registrador habilitado para comando
		
		E2=1;
		PLCD=cmd;     //
		E2=0;         //
		
		E2=1;
		cmd=cmd<<4;   //desloamento de 4b para direita
		PLCD=cmd;     //
		E2=0;         //
		
	}
	DelayLCD ();
	
}

void EDadoLCD (char cmd, int i){
	if (i==1){
		E1=0;
		E2=0;         //
		RS=1;         //registrador habilitado para dado
		
		E1=1;
		PLCD=cmd;     //
		E1=0;         //
		
		E1=1;
		cmd=cmd<<4;   //desloamento de 4b para direita
		PLCD=cmd;     //
		E1=0;         //
		
	}
	if (i==2){
		E1=0;
		E2=0;         //
		RS=1;         //registrador habilitado para dado
		
		E2=1;
		PLCD=cmd;     //
		E2=0;         //
		
		E2=1;
		cmd=cmd<<4;   //desloamento de 4b para direita
		PLCD=cmd;     //
		E2=0;         //
		
		DelayLCD ();
	}
	DelayLCD ();
}