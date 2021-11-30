#include<iostream>
#include <stdlib.h>     
#include <time.h>  
using namespace std;

#define num unsigned long long
// p = primo, g = base, x = exponente
// g ^ x (mod p) 

num exp_mod(num g, num x, num p)
{
	num temp = g, result;
	for (result = 1; x; x >>= 1) {
		if (x & 1)
			result = ((result % p) * (temp % p)) % p;
		temp = ((temp % p) * (temp % p)) % p;
	}
	return result;
}



bool witness(int a, int n, int t, int u)
{

	int x_0 = exp_mod(a, u, n);
	if (x_0 == 1 || x_0 == n-1) return false;

	int x_i = x_0;
	for (int i = 1; i <= t; i++) {
		x_i = exp_mod(x_i, 2, n);
		if (x_i == (n - 1)) return false; 
	}

	return true; 
}




int Miller_Rabin(int n, int s)
{

	int tmp = n - 1;
	int t = 0, u;
	while ((tmp % 2) == 0) {
		t++; 
		tmp /= 2;
	}
	u = tmp;
	int a = 0;

	for (int j = 1; j <= s; j++) {
		a = rand()%(n - 1) + 1;
		if (witness(a, n, t, u)) return true;
	}
	return false;

}

void primos_100(){
	int s_ = 4;
	for(int i = 11; i < 100; i += 2) {
		if (!Miller_Rabin(i, s_)) cout << "n: " << i << "\n";
	}
}


int main()
{
	srand(time(NULL));
	int n_, s_, a_;

	int tmp_, t_, u_;


	/*//WITNESS
	while (true) {
		cout << "n: "; cin >> n_;
		cout << "a: "; cin >> a_;
		t_ = 0;
		tmp_ = n_ - 1;
		while ((tmp_ % 2) == 0) {
			t_++; 
			tmp_ /= 2;
		}
		u_ = tmp_;

		cout << "WITNESS: ";
		if(witness(a_, n_, t_, u_)) cout << "True";
		else {
			cout << "False";
		}
		cout << "\n";
	}*/
	

	/* //
	while (true) {
		cout << "n: "; cin >> n_;
		cout << "s: "; cin >> s_;
		
		cout << s_ << " es primo? ";
		if (Miller_Rabin(n_, s_)) cout << "Si";
		else {
			cout << "No";
		}
		cout << "\n";
	
	}*/

	//PRIMOS DE DOS CIFRAS
	primos_100();

	return 0;
}