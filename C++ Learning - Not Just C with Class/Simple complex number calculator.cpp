#include <iostream>
#include <sstream>
#include <string>
#include <iomanip> // in order to set the precision of output

using namespace std;

class Complex {
	constexpr static const double eps = 1e-7;

	double real, imaginary;
	bool realIsZero, imaginaryIsZero, imaginaryIsNegative;

public:
	static void Version() {
		cout << "Version: 1.0, created on 2nd March, 2022 by PY." << endl;
	}
	Complex() : Complex(0){}
	Complex(double r, double i = 0) {
		real = r, imaginary = i;
		UpdateState();
	}
	void UpdateState() {
		// Three important state variables will and should be updated 
		//after certain operations with this function called.
		realIsZero = (-eps < real && real < eps);
		imaginaryIsZero = (-eps < imaginary && imaginary < eps);
		imaginaryIsNegative = (imaginary < 0);
	}
	stringstream GetOutput(){
		//return stringstream value just for convenience
		stringstream output;
		if (!realIsZero && !imaginaryIsZero) {
			if (imaginaryIsNegative) output << real << imaginary << 'i';
			else output << real << '+' << imaginary << 'i';
		}
		else if (!realIsZero) output << real;
		else if (!imaginaryIsZero) output << imaginary << 'i';
		else output << "0";
		return output;
	}
	void Add(Complex& num2) { 
		real += num2.real;
		imaginary += num2.imaginary;
		UpdateState();
	}
	Complex operator +(Complex& num2) {
		Complex res(this->real, this->imaginary);
		res.Add(num2);
		return res;
	}

	void Sub(Complex& num2) { 
		real -= num2.real;
		imaginary -= num2.imaginary;
		UpdateState();
	}
	Complex operator -(Complex& num2) { 
		Complex res(this->real, this->imaginary);
		res.Sub(num2);
		return res;
	}

	void Mul(Complex& num2) {
		double r = real, i = imaginary;
		real = real * num2.real - imaginary * num2.imaginary;
		imaginary = r * num2.imaginary + i * num2.real;
		UpdateState();
	}
	Complex operator *(Complex& num2) {
		Complex res(this->real, this->imaginary);
		res.Mul(num2);
		return res;
	}

	void Div(Complex& num2) {
		if (num2.realIsZero && num2.imaginaryIsZero) throw runtime_error("Can not be divided by zero!");
		else {
			double denominator = num2.real * num2.real + num2.imaginary * num2.imaginary;
			Complex num2Conjugated(num2.real, -num2.imaginary);
			this->Mul(num2Conjugated);
			this->real /= denominator;
			this->imaginary /= denominator;
			UpdateState();
		}
	}
	Complex operator /(Complex& num2) {
		Complex res(this->real, this->imaginary);
		try {
			res.Div(num2);
		}
		catch (runtime_error err) {
			cerr << err.what() << endl;
			res.real = res.imaginary = 0;
		}
		return res;
	}

	double Modulus() {
		//using x_(k+1) = 0.5(x_k + a / x_k) to work out sqrt(a)
		double x = real * real + imaginary * imaginary;
		double x_0 = x / 2; //set initial value to be half the original value
		double x_1 = 0.5 * (x_0 + x / x_0);
		while ( !(x_1 - x_0 < eps && x_1 - x_0 > -eps) ) {
			x_0 = x_1;
			x_1 = 0.5 * (x_0 + x / x_0);
		}
		return x_1;
	}

	void UserInput() {
		/*
		cout << "Input the real part:";
		while (!(cin >> real) ) { cout << "ERROR! Try again!"; }
		cout << "Input the imaginary part:";
		while (!(cin >> imaginary) ) { cout << "ERROR! Try again!"; }
		UpdateState();*/
		//BUG FIXED ON 2 Mar, 2022
		
		cout << "Input the real part:";
		while (!(cin >> real)) { 
			cout << "ERROR! Try again:"; 
			cin.clear(); //clear state conditions
			cin.ignore(INT_MAX, '\n'); //clear input buffer
		}
		cout << "Input the imaginary part:";
		while (!(cin >> imaginary)) { 
			cout << "ERROR! Try again:"; 
			cin.clear();
			cin.ignore(INT_MAX, '\n'); 
		}
		UpdateState();
	}
};

ostream& operator <<(ostream& os, Complex x) {
	//overload operator << so that we can write cout << x
	//remember that we should never return a reference of a local variable
	//so here we override the function with parameter Complex x instead of Complex &x
	//for the convenience when dealing with outputting calculation results.
	os << x.GetOutput().str();
	return os;
}

int main() {
	string op;

	cout << "Complex Number Calculator\n=========================" << endl;
	cout << " A. X+Y\n B. X-Y\n C. X*Y\n D. X/Y\n E. |X|\nYour choice:" << endl;
	cin >> op;
	switch (op[0]) {
	case 'a':
	case 'A': {
		auto a = new Complex();
		auto b = new Complex();
		a->UserInput();
		b->UserInput();
		cout << (*a + *b);
		delete a;
		delete b;
		break;
	}
	case 'b':
	case 'B': {
		auto a = new Complex();
		auto b = new Complex();
		a->UserInput();
		b->UserInput();
		cout << (*a - *b);
		delete a;
		delete b;
		break;
	}
	case 'c':
	case 'C': {
		auto a = new Complex();
		auto b = new Complex();
		a->UserInput();
		b->UserInput();
		cout << (*a * *b);
		delete a;
		delete b;
		break;
	}
	case 'd':
	case 'D': {
		auto a = new Complex();
		auto b = new Complex();
		a->UserInput();
		b->UserInput();
		cout << (*a / *b);
		delete a;
		delete b;
		break;
	}
	default: {
		auto a = new Complex();
		a->UserInput();
		cout << setprecision(9) << a->Modulus();
		delete a;
		break;
	}
	}
	return 0;
}
