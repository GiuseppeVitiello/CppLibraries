#pragma once

#include <iostream>
#include <string>

// Absolute value
float Ass(float N) {
	return N >= 0 ? N : -N
}

// ordering
float max(float A, float B) {
	return (A > B) ? A : B;
}

float min(float A, float B) {
	return (A < B) ? A : B;
}

float* order(bool greater, float A[], int N) {
	for (int i = 0; i < N; i++) {
		for (int j = i; j < N; j++) {
			if (greater ? A[i] < A[j] : A[i] > A[j]) {
				A[i] = A[i] + A[j];
				A[j] = A[i] - A[j];
				A[i] = A[i] - A[j];
			}
		}
	}
	return A;
}


// Decimal/Fraction related functions
int Floor(float D) {

	std::string SD = std::to_string(D);
	std::string R = "";
	int A = SD.find_first_of('.');

	for (int i = 0; i < A; i++)	R += SD[i];

	return stoi(R);
}

int Ceil(float D) {
	return Floor(D) + 1;
}

std::string Simplify(std::string S) {

	int P = S.find_first_of('/');
	int Q = S.length();
	std::string SN = "", SD = "";
	std::string FN, FD;
	int N, D;

	for (int i = 0; i < P; i++)	SN += S[i];

	for (int i = P + 1; i < Q; i++)	SD += S[i];

	N = stoi(SN);
	D = stoi(SD);

	for (int i = D; i >= 2; i--) {
		if (N % i == 0 && D % i == 0) {
			N /= i;
			D /= i;
		}
	}

	FN = std::to_string(N);
	FD = std::to_string(D);

	return FN + "/" + FD;
}

std::string DecToFrac(float P) {

	float FP = P - Floor(P);
	std::string SN, SD, SP;
	std::string R;

	for (float i = 0.1, j = 10; ; i /= 10, j *= 10) {
		if (FP >= i) {
			SN = std::to_string(P * j);
			SD = std::to_string(j);
			SP = SN + "/" + SD;
			R = Simplify(SP);
			break;
		}
	}

	return R;
}


// Power related functions
float Pot(float B, int E) {

	float R = 1;

	for (int i = 0; i < E; i++)	R *= B;

	return (E == 0) ? 1 : ((E > 0) ? R : 1 / R);
}

std::string Sqrt(float N) {

	float AN = Ass(N);
	float x = AN / 2;
	std::string SN;

	if (N == 0)	return "0";

	for (int i = 0; i < 30; i++) x = 0.5 * (double)(x + AN / x);

	SN = std::to_string(x);

	return N > 0 ? "±" + SN : "±" + SN + "i";
}

std::string NthR(float N, int I) {

	float AN, X, DX;
	std::string SN;

	if (N == 0)	return "0";

	if (I % 2 == 0) {
		AN = Ass(N);
		X = AN / 2;

		for (int i = 0; i < 30; i++) {
			DX = (AN / Pot(X, I - 1) - X) / I;
			X += DX;
		}

		SN = std::to_string(X);

		return N > 0 ? "±" + SN : "NULL";
	}

	else {
		X = N / 2;

		for (int i = 0; i < 30; i++) {
			DX = (N / Pot(X, I - 1) - X) / I;
			X += DX;
		}

		SN = std::to_string(X);

		return SN;
	}

}

std::string dPot(float B, float E) {

	std::string DE = DecToFrac(E);
	int P = DE.find_first_of('/');
	int Q = DE.length();

	std::string SN = "", SD = "";
	int N, D;

	float Pt;
	std::string Rt;

	for (int i = 0; i < P; i++)	SN += DE[i];
	for (int i = P + 1; i < Q; i++) SD = DE[i];

	N = stoi(SN);
	D = stoi(SD);
	Pt = Pot(B, N);
	Rt = NthR(Pt, D);

	return Rt;
}


// Statistic functions
float aritMean(float arr[], int N) {
	float Sum = 0;
	for (int i = 0; i < N; i++) {
		Sum += arr[i];
	}
	return Sum / N;
}

float geoMean(float arr[], int N) {
	float Prod = 1;
	float G;
	for (int i = 0; i < N; i++) {
		Prod *= arr[i];
	}
	G = stof(NthR(Prod, N));
	return G;
}

float harMean(float arr[], int N) {
	float invSum = 0;
	float mA;
	for (int i = 0; i < N; i++) {
		invSum += 1 / arr[i];
	}
	mA = N * Pot(invSum, -1);
	return mA;
}

float quaMean(float arr[], int N){
	float sqSum = 0;
	float qM;
	for (int i = 0; i < N; i++) {
		sqSum += Pot(arr[i], 2);
	}
	qM = stof(Sqrt(sqSum / N));
	return qM;
}

float Median(float arr[], int N) {
	float Med;
	order(true, arr, N)
	if (N % 2 == 0) {
		Med = (arr[N / 2] + arr[N / 2 - 1]) / 2;
	}
	else {
		Med = arr[(N - 1) / 2];
	}
	return Med;
}

int* Freq(float arr[], int N) {

	int* Counter = new int[N];
	bool* Control = new bool[N];

	for (int k = 0; k < N; k++) {
		Control[k] = false;
		Counter[k] = 0;
	}


	for (int i = 0; i < N; i++) {
		Control[i] = true;
		Counter[i]++;
		for (int j = 0; j < N; j++) {
			if (i != j) {
				if (!Control[j]) {
					if (arr[j] = arr[i]) {
						Control[j] = true;
						Counter[i]++;
					}
				}
			}
		}
	}

	return Counter;
}

float* rFreq(float arr[], int N) {

	float* rel = new float[N];
	int* abs = Freq(arr, N);

	for (int i = 0; i < N; i++) {
		rel[i] = abs[i] / N;
	}

	return rel;
}

float* pFreq(float arr[], int N) {

	float* perc = new float[N];
	float* rel = rFreq(arr, N);

	for (int i = 0; i < N; i++) {
		perc[i] = rel[i] * 100;
	}

	return perc;
}

float Mode(float arr[], int N) {

	int* Counter = Freq(arr, N);
	int MAX = 0, max = 0;

	for (int n = 0; n < N; n++) {
		if (Counter[n] > MAX) {
			MAX = Counter[n];
			max = n;
		}
	}

	return arr[max];

}

float* Scart(float arr[], int N) {
	float* SS = new float[N];
	float M = aritMean(arr, N);
	for (int i = 0; i < N; i++) {
		SS[i] = arr[i] - M;
	}
	return SS;
}

float SSM(float arr[], int N) {
	float* SS = Scart(arr, N);
	float aSum = 0;
	for (int i = 0; i < N; i++) {
		aSum += Ass(SS[i]);
	}
	return aSum / N;
}

float SQM(float arr[], int N) {
	float* SS = Scart(arr, N);
	float qSum = 0;
	float Q;
	for (int i = 0; i < N; i++) {
		qSum += Pot(SS[i], 2);
	}
	Q = stof(Sqrt(qSum / (N - 1)));
	return Q;
}

float Var(float arr[], int N) {
	return Pot(SQM(arr, N), 2);
}

float coVar(float X[], float Y[], int N) {
	float* SSX = Scart(X, N);
	float* SSY = Scart(Y, N);
	float cSum = 0;
	for (int i = 0; i < N; i++) {
		cSum += SSX[i] * SSY[i];
	}
	return cSum / (N - 1);
}

float cCorr(float X[], float Y[], int N) {
	return coVar(X, Y, N) / (SQM(X, N) * SQM(Y, N));
}

float* lReg(float X[], float Y[], int N) {
	float* coeff = new float[2];
	coeff[0] = coVar(X, Y, N) / Var(X, N);
	coeff[1] = aritMean(Y, N) - aritMean(X, N) * coeff[0];
	return coeff;
}
