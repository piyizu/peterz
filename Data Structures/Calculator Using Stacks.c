#include <stdio.h>
#include <stdbool.h>

/* This program uses two stacks: the number stack and the operator stack to implement a simple calculator.
    The fundermental of the algorithm is the idea of 'priority table' which indicates the priority of
    all operators including starting and endding characters.

    If the program gets an operator, it compares its priority with that of the operator at top of the
    operator stack. If the newer operator is prior to that at the top, the program will just push it in the stack.
    If the operator at top of the stack is prior, the program will first calculate the expression from right to left,
    until the top operator in the stack is not prior to the newer one. If both operators have the same priority, they are
    either a pair of brackets or a pair of '\n' (the starting and endding characters) and the situation will be much simpler.

    However, the idea of 'priority table' has its defects. It does not support negative numbers and intelligent auto-filling.
    Adding support for negative numbers proves to be a little hard and may make the program more complicated.

    But as an example for applying stacks, this program is just enough.
*/

// Please make sure the program is compiled and run in a system using ASCII
// Negative numbers are not supported. If you have to use them, rewrite them as things like '(0-3.14)'
// All blanks will be skipped.

#define STACK_MAX 128
#define EPS 1e-16

char OperatorToIndex[0xff];
const char Precede[5][5] = {
//  +,-  *,/   (    )   \n  <--op2  op1↓
	'>', '<', '<', '>', '>',      // +, -
	'>', '>', '<', '>', '>',      // *, /
	'<', '<', '<', '=', 'x',      // (
	'>', '>', 'x', '>', '>',      // )
	'<', '<', '<', 'x', '='       // \n
};

double Str2Positive(char *ch) {
	int num = *ch - '0';
	double res = 0.0;
	while( (*ch = getchar()) >= '0' && *ch <= '9' ) {
		num = num * 10 + *ch - '0';
	}
	res = (double)num;
	if(*ch == '.' || *ch == ',') { //two types of point are supported
		double base = 0.1;
		while( (*ch = getchar() ) >= '0' && *ch <= '9' ) {
			res = res + base * (*ch - '0');
			base *= 0.1;
		}
	}
	// now *ch is the first non-digit character after the number
	return res;
}

double Calc(double a, char oprt, double b) {
	switch(oprt) {
		case '+' : return a + b;
		case '-' : return a - b;
		case '*' : return a * b;
		case '/' : {
			if( (b > 0 ? b : -b) < EPS) {
				printf("x/0 detected. Check your input!\n");
				return a / EPS;
			}
			else return a / b;
		}
		default : {
			printf("Illegal calculation! Check your input!\n");
			return 0.0;
		}
	}
}

int main() {
	OperatorToIndex['+'] = OperatorToIndex['-'] = 0;
	OperatorToIndex['*'] = OperatorToIndex['/'] = 1;
	OperatorToIndex['('] = 2;
	OperatorToIndex[')'] = 3;
	OperatorToIndex['\n'] = 4;

	char ch; // used to read characters
	double Numbers[STACK_MAX];
	char Operators[STACK_MAX];
	int NumbersTop, OperatorsTop; // stack top pointers

	NumbersTop = OperatorsTop = -1; //initialise stack top pointers
	Operators[++OperatorsTop] = '\n'; //this helps simplify the code
	ch = getchar();
	bool loop_dont_stop = true;
	while(loop_dont_stop) {
		if(ch == ' ')
			ch = getchar(); //skip all blanks
		else if( ch >= '0' && ch <= '9') {
			double positive = Str2Positive(&ch);
			Numbers[++NumbersTop] = positive;
		}
		else {
			switch(Precede[ OperatorToIndex[Operators[OperatorsTop]] ][OperatorToIndex[ch]]) {
				case '>' : {
					double a, b;
					b = Numbers[NumbersTop--];
					a = Numbers[NumbersTop--];
					Numbers[++NumbersTop] = Calc(a, Operators[OperatorsTop--], b);
					//ch is still not pushed in. the comparison would continue!
					break;
				}
				case '=' : {
					if(ch == '\n')
						loop_dont_stop = false; //all calculation is done
					else {
						--OperatorsTop; // just for cancelling brackets
						ch = getchar();
					}
					break;
				}
				case '<' : {
					Operators[++OperatorsTop] = ch;
					ch = getchar();
					break;
				}
				default: {
					printf("Illegal operator combination. Check your input!\n");
					ch = getchar();
					break;
				}
			}
		}
	}

	printf("ANS = %g\n", Numbers[NumbersTop]);
	return 0;
}
