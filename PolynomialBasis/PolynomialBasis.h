#include"iostream"
#include "math.h"
#include "string"
#include <vector>
#include <random>

using namespace std;
using Polynom = vector<int>; 

class PolynomialOperations {
public:
    void SetCoefP(Polynom& a,  int m);
    void setPolynomialFromString(string s, Polynom& a);
    string BinaryRepresentation(Polynom& a);

    int TheMostSignificantNonZeroBit( Polynom& a);

    Polynom MovePolLeft( Polynom a, int shift);

    void Clean(Polynom& a);
    void RemoveNulls(Polynom& a);

    Polynom PolynomialDivisionByModule(Polynom a, Polynom m);

    Polynom PolynomialSum( Polynom a,  Polynom b);
    Polynom PolynomialSub( Polynom a,  Polynom b);
    Polynom PolynomialMult( Polynom a,  Polynom b);

    int PolynomialTrace(Polynom a,  Polynom g,  int m);
    Polynom PolynomialSquare(Polynom a, Polynom m);
    Polynom PolynomialPow( Polynom a,  Polynom b,  Polynom g);
    Polynom PolynomialInvers(Polynom a,  Polynom g,  int m);

    void GenerateRandomPolynomial(Polynom& a, int m);
};
