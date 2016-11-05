// IEEE-754 single-precision floating-point format (binary32)
// <--> decimal conversion practice
// Created by Jason Li (´･ω･`) on May 21, 2016
#include <iostream>
#include <sstream>
#include <bitset>
#include <ctime>
#include <cmath>
#include <cstdlib>

using namespace std;


string input(const string&);
template <typename T> string str(T);
template <typename T> double dbl(const T&);
char rand01();
int randint(int, int);
string ranSP(int);
double spTOdec(const string&);
double choose();


int main(){
	cout << "IEEE-754 single-precision floating-point format conversion practice.\n";
	cout << ":)It will appear in ENGG1203 final exam. You bet.\n\n";

	// set time as randoom seed
	srand(time(0));

	int win = 0;
	while (true){
		double choice = choose();
		if (choice == 0) return 0;

		string b = ranSP(5);
		char s = b[0];
		string e = b.substr(1,8);
		string mantissa = b.substr(9);
		// Calculate the decimal representation
		double d = spTOdec(b);

		
		// d may be too long for cout and sstream
		// when the user wants to view the answer
		while (dbl(str(d)) != d){
			//too many digits, reset
			b = ranSP(5);
			s = b[0];
			e = b.substr(1,8);
			mantissa = b.substr(9);
			// Calculate the decimal representation
			d = spTOdec(b);
		}

		//For debugging: print the data out
		// cout << s << " " << e << " " << mantissa << endl;
		// cout << d << endl;

		if (choice == 1){
			cout << "The IEEE-754 SP format of the number is\n";
			cout << s << " " << e << " " << mantissa << endl;

			while (true){
				cout << "Please convert it to decimal format:\n";
				if (d == dbl(input(">>> "))){
					cout << "Correct! Congratulations!\n\n";
					if (win < 0)
						win = 0;
					win += 1;
					break;
				}
				else{
					cout << "Oops, please press Enter to retry. Enter 0 to show answer.\n";
					string response = input(">>> ");
					if (response == "0"){
						cout << "Ans: " << d << "\n\n";
						if (win > 0)
							win = 0;
						win -= 1;
						break;
					}
				}
			}
		}
		else if (choice == 2){
			cout << "The decimal format of the number is\n";
			cout << d << endl;
			cout << "Please enter the IEEE-754 SP format.\n";
			while (true){
				string sAns = input("The sign bit = ");
				string eAns = input("The exponent = ");
				string mAns = input("The mantissa (first 5 digit) = ");
				if (s == sAns[0] && e == eAns
								&& mantissa.substr(0,5) == mAns){
					cout << "Correct! Congratulations!\n\n";
					if (win < 0)
						win = 0;
					win += 1;
					break;
				}
				else{
					cout << "Oops, press Enter to retry. Enter 0 to show answer.\n";
					string response = input(">>> ");
					if (response == "0"){
						cout << "Ans: " << s << " ";
						cout << e << " " << mantissa << "\n";
						if (win > 0)
							win = 0;
						win -= 1;
						break;
					}
				}
			}
		}
		if (win > 4)
			cout << ":) " << win << " WIN COMBO!\n";
		if (win < -4)
			cout << "QAQ " << -win << " LOSE COMBO!\n";
	}
	return 0;
}


string input(const string& caption){
	cout << caption;
	string s;
	getline(cin, s);
	return s;
}


template <typename T>
string str(T number){
	stringstream ss;
	ss << number;
	return ss.str();
}


template <typename T>
double dbl(const T& s){
	stringstream ss(s);
	double d;
	return ss >> d ? d : -1;
}


char rand01(){
	// rand() return a random integer in (0, 2^31 - 1)
	return 0 == rand() % 2 ? '0' : '1';
}


int randint(int a, int b){
	//generate a random integer in [a, b]
	if (a >= b) return -1;// Error
	int length = b - a + 1;
	return a + (rand() % length);
}


string ranSP(int significandDigits){
	string b = "";
	// Generate random IEEE-754 SP,
	// with significand of 5 digits

	// the sign bit
	b += rand01();

	// the 8 exponent bits
	bitset<8> e = randint(-6 + 127, 10 + 127);
	// 01111001 to 10000101

	//append e to b
	b += str(e);

	// the mantissa
	for (int i = 0; i < significandDigits; ++i){
		b += rand01();
	}
	for (int i = 0; i < 23 - significandDigits; ++i){
		b += '0';
	}

	return b;
}


double spTOdec(const string& b){
	stringstream ss(b.substr(1,8));
	bitset<8> e;
	ss >> e;
	unsigned long biasedExponent = e.to_ulong();

	double significand = 0;
	for (int i = 0; i < 23; ++i){
		significand += pow(0.5, i + 1) * (b[9 + i] == '0' ? 0 : 1);
	}
	// exponent = biasedExponent - 127.0
	// .0 is necessary because biasedExponent is unsigned long
	// if biasedExponent - 127 < 0, it returns -inf
	return (b[0] == '0' ? 1 : -1) * (significand + 1) * pow(2, biasedExponent - 127.0);
}


double choose(){
	while (true){
		try{
			cout << "Enter 1: IEEE-754 SP -> DEC\n";
			cout << "Enter 2: DEC -> IEEE-754 SP\n";
			cout << "Enter 0: exit\n";
			double choice = dbl(input(">>> "));
			if (choice != 1 && choice != 2 && choice != 0)
				throw 233;
			return choice;;
		}
		catch(int errorNum){
			if (errorNum == 233)
				cout << "Invalid input. Please retry.\n";
			else
				cout << "Unknown error. Please retry.\n";
		}
	}
}
