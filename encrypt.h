#pragma once

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>

#pragma warning (disable: 4996)

#define elif else if
#define I64 int64_t

using namespace std;

// Arrays containing the two primes [0] and [1], their product [2] and totient [3], and the two keys [4] and [5]
I64 Info[6];
string InfoNames[6] = {
	"Public Key: ",
	"Private Key: ",
	"Product: ",
	"1st prime: ",
	"2nd prime: ",
	"Totient: "
};



// -----------------------------------------------------------------
// Useless functions
// -----------------------------------------------------------------

// greatest common divisor
I64 gcd(I64 _firstNumber, I64 _secondNumber) {
	I64 _q, n1, n2, r;
	if (_firstNumber > _secondNumber)
		n1 = _firstNumber, n2 = _secondNumber;
	else
		n1 = _secondNumber, n2 = _firstNumber;
	while (n2 > 0) {
		_q = n1 / n2;
		r = n1 - _q * n2;
		n1 = n2;
		n2 = r;
	}
	return n1;
}

// lowest common multiple
I64 lcm(I64 _firstNumber, I64 _secondNumber) {
	if (_firstNumber > _secondNumber)
		return (_firstNumber * _secondNumber) / (gcd(_firstNumber, _secondNumber));
	else
		return (_firstNumber * _secondNumber) / (gcd(_secondNumber, _firstNumber));
}

// optimized power and modulo function
I64 PowMod(I64 _base, I64 _exponent, I64 _modulo) {
	I64 _result = 1;
	while (_exponent) {
		if ((_exponent & 1) == 1)
			_result = _base * _result % _modulo;
		_exponent >>= 1;
		_base = _base * _base % _modulo;
	}
	return _result;
}

// prime testing function using Miller-Rabin algorithm
bool PrimeTest(I64 _base, I64 _possiblePrime) {
	I64 n = _possiblePrime - 1;
	I64 r = 0;
	while (n % 2 == 0) {
		r++;
		n /= 2;
	}
	I64 m = n;
	I64 T = PowMod(_base, m, _possiblePrime);
	if (T == 1 || T == _possiblePrime - 1)
		return true;
	for (I64 j = 0; j < r; j++) {
		T = PowMod(T, 2, _possiblePrime);
		if (T == 1)
			return false;
		if (T == _possiblePrime - 1)
			return true;
	}
	return false;
}

// multiplicative inverse function
I64 multInverse(I64 _modulo, I64 _element) {
	I64 _inverse = 0;
	I64 _q;
	I64 r, r1 = _modulo, r2 = _element;
	I64 t, t1 = 0, t2 = 1;
	while (r2 > 0) {
		_q = r1 / r2;

		r = r1 - _q * r2;
		r1 = r2;
		r2 = r;

		t = t1 - _q * t2;
		t1 = t2;
		t2 = t;
	}
	if (r1 == 1)
		_inverse = t1;
	if (_inverse < 0)
		_inverse += _modulo;
	return _inverse;
}


// Prime generating function
void PrimeGenerator() {
	I64 _firstPrime, _secondPrime;
	do {
		do
			_firstPrime = rand();
		while (_firstPrime % 2 == 0);
	} while (!PrimeTest(2, _firstPrime));

	do {
		do
			_secondPrime = rand();
		while (_secondPrime % 2 == 0);
	} while (!PrimeTest(2, _secondPrime));
	Info[0] = _firstPrime;
	Info[1] = _secondPrime;
}

// Key generating function
void KeyGenerator() {
	I64 _product = Info[0] * Info[1];
	I64 _totient = lcm(Info[0] - 1, Info[1] - 1);
	I64 _publicKey, _privateKey;
	do
		_publicKey = rand() % (_totient - 2) + 2;
	while (gcd(_publicKey, _totient) != 1);
	_privateKey = multInverse(_totient, _publicKey);
	Info[2] = _product;
	Info[3] = _totient;
	Info[4] = _publicKey;
	Info[5] = _privateKey;
}



// -----------------------------------------------------------------
// Useful functions
// -----------------------------------------------------------------

// get the info array
I64* getInfo() {
	return Info;
}

// encrypt data
string encrypt(string _plainPassword) {
	srand(unsigned(time(0)));
	string _encryptedPassword = "";
	PrimeGenerator();
	KeyGenerator();
	for (unsigned i = 0; i < _plainPassword.length(); i++) {
		char ch = _plainPassword[i];
		if (ch == -1)
			break;
		I64 value = int(ch);
		I64 _encryptChar = PowMod(value, getInfo()[4], getInfo()[2]);
		_encryptedPassword += to_string(_encryptChar) + " ";
	}
	return _encryptedPassword;
}

// decrypt data
string decrypt(string encryptedPassword) {
	string _decryptedPassword = "";
	unsigned lastSpace = 0;
	while (true) {
		I64 block = 0;
		string blockString = "";
		if (lastSpace >= encryptedPassword.length())
			break;
		for (unsigned i = lastSpace; i < encryptedPassword.length(); i++) {
			if (encryptedPassword[i] == ' ') {
				lastSpace = i + 1;
				break;
			}
			else
				blockString += encryptedPassword[i];

		}
		try {
			block = stoi(blockString);
		}
		catch (out_of_range) {}

		_decryptedPassword += char(PowMod(block, getInfo()[5], getInfo()[2]));
	}
	return _decryptedPassword;
}