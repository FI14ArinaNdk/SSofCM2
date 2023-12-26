#include "PolynomialBasis.h"
#include <chrono>

using namespace chrono;
using namespace std;

int main()
{
	PolynomialOperations pol;
	Polynom g;
	int m = 359;
	pol.SetCoefP(g, m);
	
	string aa = "00000010010010000100100111101100100000101110011010000101011010110100110111000000100100011000110110011100110100111110110011100010011011001101010001110011111011100010100101000110001000101110010111011101001010111010010111110000010110111001110000011010110010101001011100100101001100111001001010000110100111111010010011100001101111000101001010001001101101011000001";
	string bb = "10111000111011110101100111000011111100001111100001000011110100101100111111110000111010010001111011100101111010000000000101010001001001000010100111100110000010001010110001011101010000111110100111001000001001100100010111000111101110111111001011110010111001110001011101110110011001011011111110101010101011010101001101100100101101001101000110111010011110110001001";
	string cc = "11100100011101011011010000111110101010101011011010100101111110101110010000010100010110001110011010001110011010010000000001100101111111010101111000001011001100110000000101000100011001101100000000101011100110111010101110110001000010001101010011111001111100110110100001110100111011011001110110000011010111001010100000010110110010001000011001010001100110010000111";

	Polynom a, b, c;
	pol.setPolynomialFromString(aa, a);   
	pol.setPolynomialFromString(bb, b);   
	pol.setPolynomialFromString(cc, c);  
	
	
	cout<<"a =" << pol.BinaryRepresentation(a) <<endl;
	cout<<"b =" << pol.BinaryRepresentation(b) <<endl;
	cout<<"c =" << pol.BinaryRepresentation(c) <<endl;
	cout << "\n" << endl;

	Polynom Sum = pol.PolynomialSum(a,b);
	cout << "a+b =" << pol.BinaryRepresentation(Sum) << endl;
	cout << "\n" << endl;

	Polynom mult0 =  pol.PolynomialMult(a,b);   
	Polynom Mult = pol.PolynomialDivisionByModule(mult0,g);   
	cout << "a*b =" << pol.BinaryRepresentation(Mult) << endl;
	cout << "\n" << endl; 

	int Trace= pol.PolynomialTrace(a,g,m); 
	cout << "trace(a) =" << Trace << endl; 
	cout << "\n" << endl;

	Polynom Square= pol.PolynomialSquare(a,g);
	cout << "a^2 =" << pol.BinaryRepresentation(Square) << endl; 
	cout << "\n" << endl;

	Polynom Invers = pol.PolynomialInvers(a, g, m); 
	cout << "a^-1 =" << pol.BinaryRepresentation(Invers) << endl; 
	cout << "\n" << endl;

	Polynom Power= pol.PolynomialPow(a,c,g); 
	cout << "a^c =" << pol.BinaryRepresentation(Power) << endl;  
	cout << "\n" << endl;


	cout << "\t" << endl;
	cout << "\t" << endl;

	cout << "Test time:" << endl;
	//Test 1
	Polynom left_side = pol.PolynomialMult(pol.PolynomialSum(a, b), c);
	Polynom right_side = pol.PolynomialSum(pol.PolynomialMult(b, c), pol.PolynomialMult(c, a));
	cout << "Test 1: (a + b)* c = b * c + c * a - ";
	if (pol.BinaryRepresentation(left_side) == pol.BinaryRepresentation(right_side)) {
		cout << "Passed" << endl;
	}
	else { cout << "Failed" << endl; }

	string kk = "1010";
	string ll = "1101";
	string hh = "1001";
	Polynom k, l, h;
	pol.setPolynomialFromString(kk, k);
	pol.setPolynomialFromString(ll, l);
	pol.setPolynomialFromString(hh, h);

	//Test 2
	string expected = "0111";
	Polynom sum = pol.PolynomialSum(k, l);
	string sum_result = pol.BinaryRepresentation(sum);
	if (sum_result == expected) {
		cout << "Test Sum - Passed\n";
	}
	else {
		cout << "Test Sum - Failed\n";
	}

	//Test 3
	string expected1 = "1110010";
	Polynom mult = pol.PolynomialMult(k, l);
	string mult_result = pol.BinaryRepresentation(mult);
	if (mult_result == expected1) {
		cout << "Test Mult - Passed\n";
	}
	else {
		cout << "Test Mult - Failed\n";
	}

	//Test 4
	string expected2 = "01000100";
	Polynom Sq = pol.PolynomialSquare(k, g);
	string Sq_result = pol.BinaryRepresentation(Sq);
	if (Sq_result == expected2) {
		cout << "Test Square - Passed\n";
	}
	else {
		cout << "Test Square - Failed\n";
	}
	 

	/*
	const int iterations = 10;
	double totalAdditionDuration = 0.0;
	double totalSubtractionDuration = 0.0;
	double totalMultiplicationDuration = 0.0; 
	double totalTraceDuration = 0.0;
	double totalSquareDuration = 0.0;
	double totalInversDuration = 0.0; 
	double totalPowerDuration = 0.0; 


	for (int i = 0; i < iterations; ++i) { 
		Polynom A, B, C; 
		pol.GenerateRandomPolynomial(A, m);   
		pol.GenerateRandomPolynomial(B, m);  
		pol.GenerateRandomPolynomial(C, m);  

		auto startAddition = std::chrono::steady_clock::now(); 
		pol.PolynomialSum(A, B);  
		auto endAddition = std::chrono::steady_clock::now(); 
		std::chrono::duration<double, std::micro> additionDuration = endAddition - startAddition;
		totalAdditionDuration += additionDuration.count(); 
		
		auto startSubtraction = std::chrono::steady_clock::now();
		Polynom sub = pol.PolynomialSub(A, B);
		auto endSubtraction = std::chrono::steady_clock::now(); 
		std::chrono::duration<double, std::micro> subtractionDuration = endSubtraction - startSubtraction;
		totalSubtractionDuration += subtractionDuration.count(); 
		
		auto startMultiplication = std::chrono::steady_clock::now();
		Polynom mul0 = pol.PolynomialMult(A, B); 
		Polynom mul = pol.PolynomialDivisionByModule(mul0, g); 
		auto endMultiplication = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::micro> multiplicationDuration = endMultiplication - startMultiplication;
		totalMultiplicationDuration += multiplicationDuration.count();

		auto startTrace = std::chrono::steady_clock::now(); 
		pol.PolynomialTrace(A, g, m);
		auto endTrace = std::chrono::steady_clock::now(); 
		std::chrono::duration<double, std::micro> TraceDuration = endTrace - startTrace;  
		totalTraceDuration += TraceDuration.count(); 

		auto startSquare = std::chrono::steady_clock::now();
		pol.PolynomialSquare(A, B);
		auto endSquare = std::chrono::steady_clock::now(); 
		std::chrono::duration<double, std::micro> SquareDuration = endSquare - startSquare; 
		totalSquareDuration += SquareDuration.count(); 

		auto startInvers = std::chrono::steady_clock::now();
		pol.PolynomialInvers(A, g, m);
		auto endInvers = std::chrono::steady_clock::now();
		std::chrono::duration<double, std::micro> InversDuration = endInvers - startInvers;
		totalInversDuration += InversDuration.count();

		auto startPower = std::chrono::steady_clock::now();
		pol.PolynomialPow(A, C, g); 
		auto endPower = std::chrono::steady_clock::now(); 
		std::chrono::duration<double, std::micro> PowerDuration = endPower - startPower; 
		totalPowerDuration += PowerDuration.count();
	}

	double averageAdditionTime = totalAdditionDuration / iterations;
	double averageSubtractionTime = totalSubtractionDuration / iterations;
	double averageMultiplicationTime = totalMultiplicationDuration / iterations;
	double averageTraceTime = totalTraceDuration / iterations;
	double averageSquareTime = totalSquareDuration / iterations;
	double averageInversTime = totalInversDuration / iterations;
	double averagePowerTime = totalPowerDuration / iterations;

	cout << "Average time for polynomial addition: " << averageAdditionTime << " microsec\n";
	cout << "Average time for polynomial subtraction: " << averageSubtractionTime << " microsec\n";
	cout << "Average time for polynomial multiplication: " << averageMultiplicationTime << " microsec\n";
	cout << "Average time for polynomial trace: " << averageTraceTime << " microsec\n"; 
	cout << "Average time for polynomial squareT: " << averageSquareTime << " microsec\n"; 
	cout << "Average time for polynomial invers: " << averageInversTime << " microsec\n"; 
	cout << "Average time for polynomial power: " << averagePowerTime << " microsec\n";
	*/

	return 0;
}

