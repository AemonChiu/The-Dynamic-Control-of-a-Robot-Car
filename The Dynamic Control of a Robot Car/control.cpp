void control(int &left, int &right) 
{
	//PWM values of the wheels
	int pwmL;
	int pwmR;
	
	//Counts of the wheels
	int vCL;
	int vCR;
	
	//Target speed
	float v = 1;
	
	//Target speeds of the wheel
	double vL;
	double vR;

	//Difference in the counts of the two wheels
	int E;
	
	//Difference between the target speed and the previously measured speed of the two wheels
	double EL;
	double ER;
	
	//D(z) of the digital controller, a temporary value
	double D;

	//Initialisation of the values, setting the errors and D(z) to 0, and PWM to 15000
	//Also, getting the measurement and assigning to vCL and vCR
	static int Epre = 0;
	static double Dpre = 0;
	static int pwmLpre = 15000;
	static int pwmRpre = 15000;
	static double ELpre = 0;
	static double ERpre = 0;
	vCL = left;
	vCR = right;
	E = vCL - vCR;
	
	//Implementing the control system:
	//D = Dpre + 0.5503*E - 0.55*Epre;
	//pwmL = pwmLpre + 1001*EL - 998.8*ELpre;
	//pwmR = pwmRpre + 1001*ER - 998.8*ERpre;
	D = Dpre + 0.5503*E - 0.55*Epre;
	vL = v - D;
	EL = vL - vCL;
	pwmL = pwmLpre + 1002 * EL - 998.3*ELpre;

	vR = v + D;
	ER = vR - vCR;
	pwmR = pwmRpre + 1002 * ER - 998.3*ERpre;
	
	//Set the PWM values to the calculated ones
	left = pwmL;
	right = pwmR;
	
	//Preparing for the next cycle
	Epre = E;
	Dpre = D;
	pwmLpre = pwmL;
	pwmRpre = pwmR;
	ELpre = EL;
	ERpre = ER;
}
