int pow(int a, int b) {
	int res = 1;
	while(b) {
		if(b % 2) {
			res = res*a;
		}
		b /= 2;
		a = a*a;
	}
	return res;
}