#include "PolynomialBasis.h"


void PolynomialOperations::SetCoefP(Polynom& a, int m){
	a.resize(m + 1); 
	a[359] = 1; 
	a[18] = 1; 
	a[4] = 1; 
	a[2] = 1; 
	a[0] = 1; 
}

void PolynomialOperations::setPolynomialFromString(string s, Polynom& a){
	int sLenght = s.length();  
	a.resize(sLenght); 
	for (int i = 0; i < sLenght; i++)   
	{
		a[sLenght - 1 - i] = s[i] - '0'; 
	}
}

string PolynomialOperations::BinaryRepresentation(Polynom& a){ 
	string result; 
	for (int i = a.size() - 1; i >= 0; i--) { 
		result += to_string(a[i]); 
	}
	return result; 
} 


int PolynomialOperations::TheMostSignificantNonZeroBit( Polynom& a){
	for (int i = a.size() - 1; i >= 0; i--) 
	{
		if (a[i] == 1) { return i; } 
		else {}
	}
	return -1;
}

Polynom PolynomialOperations::MovePolLeft( Polynom a, int shift){
	Polynom result;
	result.resize(a.size() + shift); 
	int l = result.size() - 1; 
	for (int i = l; i >= shift; i--) 
	{
		result[i] = a[i - shift]; 
	}
	for (int j = 0; j < shift; j++)  
	{
		result[j] = 0; 
	}
	return result; 
}

void PolynomialOperations::Clean(Polynom& a){ 
	for (int i = a.size() - 1; i >= 0; i--)
	{
		a.pop_back();
	}
}

void PolynomialOperations::RemoveNulls(Polynom& a){
	int TMSNB = TheMostSignificantNonZeroBit(a); 
	for (int i = a.size() - 1; i > TMSNB; i--) 
	{
		a.pop_back();
	}
}

Polynom PolynomialOperations::PolynomialSum( Polynom a,  Polynom b){
	Polynom result;
	int poly_a = a.size();
	int poly_b = b.size();
	int poly_c = max(poly_a, poly_b);
	if (poly_a >= poly_b){                                                       
		poly_c = poly_a;
		b.insert(b.end(), poly_a - poly_b, 0);   
	}
	else {
		poly_c = poly_b; 
		a.insert(a.end(), poly_b - poly_a, 0);  
	} 
	result.resize(poly_c); 
	for (int i = 0; i < poly_c; i++)  
	{
		result[i] = (a[i] + b[i]) % 2; 
	}
	return result; 
}

Polynom PolynomialOperations::PolynomialSub( Polynom a,  Polynom b){
	Polynom result;
	int poly_a = a.size(); 
	int poly_b = b.size(); 
	int poly_c = max(poly_a, poly_b); 
	if (poly_a >= poly_b) {
		poly_c = poly_a;
		b.insert(b.end(), poly_a - poly_b, 0);
	}
	else {
		poly_c = poly_b;
		a.insert(a.end(), poly_b - poly_a, 0);
	}
	result.resize(poly_c); 
	int res = 0;
	for (int i = 0; i < poly_c; i++) 
	{
		res = a[i] - b[i];
		if (res < 0) { res = res + 2; } 
		else {}
		result[i] = res; 
	}
	return result; 
}

Polynom PolynomialOperations::PolynomialMult( Polynom a,  Polynom b){
	Polynom result;
	int poly_a = a.size(); 
	int poly_b = b.size(); 
	int poly_c = max(poly_a, poly_b); 
	if (poly_a >= poly_b) {
		poly_c = poly_a; 
		b.insert(b.end(), poly_a - poly_b, 0); 
	} 
	else {
		poly_c = poly_b; 
		a.insert(a.end(), poly_b - poly_a, 0); 
	} 
	result.resize(2 * poly_c); 
	for (int j = poly_c - 1; j >= 0; j--) 
	{
		for (int i = 0; i <= poly_c - 1; i++) 
		{
			result[j + i] = (result[j + i] + a[j] * b[i]) % 2; 
		}
	}
	RemoveNulls(result);
	return result;
}

Polynom PolynomialOperations::PolynomialDivisionByModule(Polynom a, Polynom m){
	Polynom quotient; 
	Polynom remainder; 
	Polynom temp;  

	int poly_a = TheMostSignificantNonZeroBit(a);  
	int poly_m = TheMostSignificantNonZeroBit(m);  
	remainder.resize(poly_m);  
	if (poly_m > poly_a) {
		return a;
	}
	else {
		quotient.resize(poly_a - poly_m + 1); 
		while (poly_a >= poly_m) 
		{  
			quotient[poly_a - poly_m] = 1;
			temp = MovePolLeft(m, poly_a - poly_m); 
			remainder = PolynomialSub(a, temp); 
			Clean(a);
			a = remainder; 
			poly_a = TheMostSignificantNonZeroBit(a);
		}
		RemoveNulls(remainder);
		return remainder; 
	}
}

int PolynomialOperations::PolynomialTrace(Polynom a,  Polynom g, int m){
	Polynom temp; 
	Polynom temp1; 
	Polynom res = a;   
	for (int i = 1; i <= m - 1; i++) 
	{
		Clean(temp); 
		temp = PolynomialSquare(a, g); 
		Clean(temp1);
		temp1 = PolynomialSum(res, temp);
		Clean(res); 
		res = temp1; 
		Clean(a); 
		a = temp; 
	}
	RemoveNulls(res); 
	int result = res.size(); 
	return result; 
} 

Polynom PolynomialOperations::PolynomialSquare(Polynom a, Polynom m){
	int poly_a = a.size(); 
	Polynom b; 
	Polynom result;
	b.resize(2 * poly_a);
	for (int i = 0; i < poly_a; i++) 
	{
		b[2 * i] = a[i];
	}
	result = PolynomialDivisionByModule(b, m); 
	return result;
}

Polynom PolynomialOperations::PolynomialPow( Polynom a,  Polynom b,  Polynom g){
	int poly_a = a.size(); 
	int poly_b = b.size(); 
	Polynom result;
	Polynom p = a;
	Polynom temp1, temp3; 
	result.resize(poly_a); 
	temp3.resize(poly_a); 
	result[0] = 1;
	for (int i = 0; i < poly_b; i++) 
	{
		if (b[i] == 0)
		{
			temp1 = PolynomialSquare(p, g);
			Clean(p);
			p = temp1;
			Clean(temp1);
		}
		else {
			temp1 = PolynomialMult(result, p); 
			temp3 = PolynomialDivisionByModule(temp1, g);
			Clean(temp1);
			Clean(result); 
			result = temp3;
			Clean(temp3);

			temp1 = PolynomialSquare(p, g);
			Clean(p);
			p = temp1;
			Clean(temp1);
		}
	}
	return result; 
}

Polynom PolynomialOperations::PolynomialInvers(Polynom a,  Polynom g, int m){
	Polynom temp, temp1, temp2; 
	Polynom res;
	Polynom result;
	res = a;
	for (int i = 1; i <= m - 2; i++){ 
		Clean(temp);
		temp = PolynomialSquare(a, g);
		Clean(temp1);
		temp1 = PolynomialMult(res, temp);
		Clean(temp2);
		temp2 = PolynomialDivisionByModule(temp1, g);
		Clean(res);
		res = temp2;
		Clean(a);
		a = temp;
	}
	result = PolynomialSquare(res, g); 
	return result; 
}


void PolynomialOperations::GenerateRandomPolynomial(Polynom& a, int m){
	std::random_device rd; 
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<int> dis(0, 1); 
	a.resize(m + 1);

	for (int i = 0; i <= m; ++i) {
		a[i] = dis(gen); 
	}
}