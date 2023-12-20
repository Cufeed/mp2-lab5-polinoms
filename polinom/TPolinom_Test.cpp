#include <iostream>
#include "TList.h"
#include "TPolinom.h"
#include "THeadList.h"
#include "TMonom.h"
using namespace std;


int main()
{
	TMonom monom1(2.0, 5, 2, 6); // 2x5y2z6
	TMonom monom2(3.0, 0, 1, 0); // 3y
	//TMonom monom5(2.0, 3, 2, 4);
	//TMonom monom3(4.0, 1, 0, 0);
	//cout << "\nEnter monom: coef_x,y,z^degree" << endl;
	//string tmp;
	//cin >> tmp;
	//TMonom monom4(tmp);

	// Create a polynomial and add the monomials
	TPolinom poly;
	poly.AddMonom(monom1);
	poly.AddMonom(monom2);
	//poly.AddMonom(monom3);
	//poly.AddMonom(monom4);
	//poly.AddMonom(monom5);
	// Print the polynomial to the console
	std::cout << poly.ToString() << " | Pol 1" << std::endl;
	TMonom monom4(3.0, 5, 2, 6);
	TMonom monom5(2, 0, 0, 1);
	//TMonom monom6(7, 0, 1, 0);
	TPolinom poly2;
	poly2.AddMonom(monom4);
	poly2.AddMonom(monom5);
	//poly2.AddMonom(monom6);
	std::cout << poly2.ToString() << " | Pol 2" << endl;
	TPolinom poly3 = poly + poly2;
	cout << poly3.ToString() << " | Pol 3 sum" << endl;
	//cout << poly3.ToString() << " | Pol 3 sum" << endl;
	return 0;

}