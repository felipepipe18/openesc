// Voltage_protection.c

#include	<Voltage_protection.h>

//params
float Unom = U_NOM;

bool		Check_Voltage(uint16_t U)
{
  	bool	alarm = true;
	float	fU;
	
	fU = (float)U * KTR_UIN;
	if ((fU > U_MAX) || (fU < U_MIN))
	  	alarm = false;

	return	alarm;
}

uint16_t	Correct_Uin(uint16_t Uin, uint16_t Out)
{
  	float	k_Uin = 1.0;
	
  	k_Uin = Unom / ((float)Uin * KTR_UIN);
	
	return (uint16_t)((float)Out * k_Uin);
}