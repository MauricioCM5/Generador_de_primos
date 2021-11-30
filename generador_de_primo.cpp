#include<iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include<math.h>
#include<vector>
#include<algorithm>
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
	if (x_0 == 1 || x_0 == n - 1) return false;
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
		a = rand() % (n - 1) + 1;
		if (witness(a, n, t, u)) return true;
	}
	return false;

}


int generate_prime_candidate(int b) {
	int tmp = pow(2, b-1);
	
	int n = rand() %tmp + 2;;
	int m = pow(2, b -1) + 1;
	n = n | m;
	return n;

}



int generate_prime(int b) {
	int n = generate_prime_candidate(b);
	while (Miller_Rabin(n, 128))
		n += 2;
	return n;

}





void encontrar_primos() {
	int i = 0;
	int tmp;

	vector<int>primos;


	while (primos.size()<76) {
		tmp = generate_prime(10);
		if (!(find(primos.begin(), primos.end(), tmp) != primos.end())) {
			primos.push_back(tmp);
			cout << i << ". " << tmp << "\n";
			i++;
		}

	}
}



int main()
{
	srand(time(NULL));

	/* //GENERADOR DE PRIMOS
	* int tam_bits;
	cout << "GENERAR UN PRIMO -------\n";
	cout << "Introduzca un tamaño de bits: " >> tam_bits;
	cout << "Primo generado: " << generate_prime(tam_bits) << "\n";
	cout << "-----------------------\n";

	*/
	
	//Hallar primos de 10 bits
	encontrar_primos();

	return 0;
}