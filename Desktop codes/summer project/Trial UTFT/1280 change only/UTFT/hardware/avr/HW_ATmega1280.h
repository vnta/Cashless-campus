// *** Hardwarespecific functions ***
void UTFT::_hw_special_init()
{
}

void UTFT::LCD_Writ_Bus(char VH,char VL, byte mode)
{   
	switch (mode)
	{
	case 1:
		if (display_serial_mode==SERIAL_4PIN)
		{
		if (VH==1)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		}
		else
		{
		if (VH==1)
			sbi(P_RS, B_RS);
		else
			cbi(P_RS, B_RS);
		}

		if (VL & 0x80)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x40)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x20)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x10)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x08)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x04)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x02)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		if (VL & 0x01)
			sbi(P_SDA, B_SDA);
		else
			cbi(P_SDA, B_SDA);
		pulse_low(P_SCL, B_SCL);
		break;
	case 8:
if (VH & 0x01)
		PORTE |= (1<<0);
	else
		PORTE &= ~(1<<0);
	if (VH & 0x02)
		PORTE |= (1<<1);
	else
		PORTE &= ~(1<<1);
	if (VH & 0x04)
		PORTE |= (1<<4);
	else
		PORTE &= ~(1<<4);
	if (VH & 0x08)
		PORTE |= (1<<5);
	else
		PORTE &= ~(1<<5);
	if (VH & 0x10)
		PORTG |= (1<<5);
	else
		PORTG &= ~(1<<5);
	if (VH & 0x20)
		PORTE |= (1<<3);
	else
		PORTE &= ~(1<<3);
	if (VH & 0x40)
		PORTH |= (1<<3);
	else
		PORTH &= ~(1<<3);
	if (VH & 0x80)
		PORTH |= (1<<4);
	else
		PORTH &= ~(1<<4);

		pulse_low(P_WR, B_WR);
		// PORTA = VL;
	if (VL & 0x01)
		PORTE |= (1<<0);
	else
		PORTE &= ~(1<<0);
	if (VL & 0x02)
		PORTE |= (1<<1);
	else
		PORTE &= ~(1<<1);
	if (VL & 0x04)
		PORTE |= (1<<4);
	else
		PORTE &= ~(1<<4);
	if (VL & 0x08)
		PORTE |= (1<<5);
	else
		PORTE &= ~(1<<5);
	if (VL & 0x10)
		PORTG |= (1<<5);
	else
		PORTG &= ~(1<<5);
	if (VL & 0x20)
		PORTE |= (1<<3);
	else
		PORTE &= ~(1<<3);
	if (VL & 0x40)
		PORTH |= (1<<3);
	else
		PORTH &= ~(1<<3);
	if (VL & 0x80)
		PORTH |= (1<<4);
	else
		PORTH &= ~(1<<4);
		pulse_low(P_WR, B_WR);
		break;
	case 16:
		PORTA = VH;
		PORTC = VL;
		pulse_low(P_WR, B_WR);
		break;
	case LATCHED_16:
		PORTG &= ~0x20;	
		PORTG |= (VH & 0x10)<<1;	
		PORTH &= ~0x18;	
		PORTH |= (VH & 0xC0)>>3;	
		PORTE &= ~0x3B;	
		PORTE |= (VH & 0x03) + ((VH & 0x0C)<<2) + ((VH & 0x20)>>2);
		cbi(P_ALE, B_ALE);
		pulse_high(P_ALE, B_ALE);
		cbi(P_CS, B_CS);
		PORTG &= ~0x20;	
		PORTG |= (VL & 0x10)<<1;	
		PORTH &= ~0x18;	
		PORTH |= (VL & 0xC0)>>3;	
		PORTE &= ~0x3B;	
		PORTE |= (VL & 0x03) + ((VL & 0x0C)<<2) + ((VL & 0x20)>>2);
		pulse_low(P_WR, B_WR);
		sbi(P_CS, B_CS);
		break;
	}
}

void UTFT::_set_direction_registers(byte mode)
{
	if (mode!=LATCHED_16)
	{
		pinMode(0, OUTPUT);
			pinMode(1, OUTPUT);
			pinMode(2, OUTPUT);
			pinMode(3, OUTPUT);
			pinMode(4, OUTPUT);
			pinMode(5, OUTPUT);
			pinMode(6, OUTPUT);
			pinMode(7, OUTPUT);
		if (mode==16)
			DDRC = 0xFF;
	}
	else
	{
		DDRH = 0x18;
		DDRG = 0x20;
		DDRE = 0x3B;
	}
}

void UTFT::_fast_fill_16(int ch, int cl, long pix)
{
	long blocks;

	PORTA = ch;
	PORTC = cl;

	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
	}
	if ((pix % 16) != 0)
		for (int i=0; i<(pix % 16); i++)
		{
			pulse_low(P_WR, B_WR);
		}
}

void UTFT::_fast_fill_8(int ch, long pix)
{
	long blocks;

	PORTA = ch;

	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
	}
	if ((pix % 16) != 0)
		for (int i=0; i<(pix % 16); i++)
		{
			pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		}
}
