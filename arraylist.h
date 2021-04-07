#pragma once

#include <iostream>

template <class arrayType>
class ArrayList {

private:
	arrayType* arr;
	arrayType* backupArr;

	int sz = 0;

public:
	void psh(arrayType val) {

		if (arr == nullptr) {

			arr = new arrayType[sz + 1];
			arr[sz] = val;

		}
		else {

			backupArr= new arrayType[sz];

			for (int i = 0; i < sz; i++)
				backupArr[i] = arr[i];

			arr = new arrayType[sz + 1];

			for (int i = 0; i < sz; i++)
				arr[i] = backupArr[i];

			arr[sz] = val;

		}

		sz++;

	}

	void set(int index, arrayType val) {

		arr[index] = val;

	}

	void canc(int index) {

		if (index < sz) {

			backupArr = new arrayType[sz - 1];
			for (int i = 0; i < sz - 1; i++)
				backupArr[i] = arr[i >= index ? i + 1 : i];

			arr = new arrayType[sz - 1];
			for (int i = 0; i < sz - 1; i++)
				arr[i] = backupArr[i];
			
		}

	}

	void change(int index1, int index2) {

		if (index1 <= sz && index2 <= sz) {

			arrayType* backup = new arrayType(arr[index1]);
			arr[index1] = arr[index2];
			arr[index2] = *backup;

			delete backup;

		}

	}

	arrayType get(int index) {

		if (index <= sz)
			return arr[index];

		return *(new arrayType);

	}

	int size() {

		return sz;

	}

};

template < >
class ArrayList<int> {

private:
	int* arr;
	int* backupArr;

	int sz = 0;

	void switchValues(int& a, int& b) {

		a = a + b;
		b = a - b;
		a = a - b;

	}

public:
	void add(int val) {

		if (arr == nullptr) {

			arr = new int[sz + 1];
			arr[sz] = val;

		}
		else {

			backupArr = new int[sz];

			for (int i = 0; i < sz; i++)
				backupArr[i] = arr[i];

			arr = new int[sz + 1];

			for (int i = 0; i < sz; i++)
				arr[i] = backupArr[i];

			arr[sz] = val;

		}

		sz++;

	}

	void set(int index, int val) {

		arr[index] = val;

	}

	void del(int index) {

		if (index < sz) {

			backupArr = new int[sz - 1];
			for (int i = 0; i < sz - 1; i++)
				backupArr[i] = arr[i >= index ? i + 1 : i];

			arr = new int[sz - 1];
			for (int i = 0; i < sz - 1; i++)
				arr[i] = backupArr[i];

			sz--;

		}

	}

	void sw(int index1, int index2) {

		if (index1 <= sz && index2 <= sz) {

			int* backup = new int(arr[index1]);
			arr[index1] = arr[index2];
			arr[index2] = *backup;

			delete backup;

		}

	}

	void sort(bool descending) {

		for (int i = 0; i < sz; i++)
			for (int j = i; j < sz; j++)
				if (descending ? arr[i] < arr[j] : arr[i] > arr[j])
					switchValues(arr[i], arr[j]);

	}

	int get(int index) {

		if (index <= sz)
			return arr[index];

		return *(new int);

	}

	int size() {

		return sz;

	}

};

template < >
class ArrayList<double> {

private:
	double* arr;
	double* backupArr;

	int sz = 0;

	void switchValues(double& a, double& b) {

		a = a + b;
		b = a - b;
		a = a - b;

	}

public:
	void add(double val) {

		if (arr == nullptr) {

			arr = new double[sz + 1];
			arr[sz] = val;

		}
		else {

			backupArr = new double[sz];

			for (int i = 0; i < sz; i++)
				backupArr[i] = arr[i];

			arr = new double[sz + 1];

			for (int i = 0; i < sz; i++)
				arr[i] = backupArr[i];

			arr[sz] = val;

		}

		sz++;

	}

	void set(int index, double val) {

		arr[index] = val;

	}

	void del(int index) {

		if (index < sz) {

			backupArr = new double[sz - 1];
			for (int i = 0; i < sz - 1; i++)
				backupArr[i] = arr[i >= index ? i + 1 : i];

			arr = new double[sz - 1];
			for (int i = 0; i < sz - 1; i++)
				arr[i] = backupArr[i];

			sz--;

		}

	}

	void sw(int index1, int index2) {

		if (index1 <= sz && index2 <= sz) {

			double* backup = new double(arr[index1]);
			arr[index1] = arr[index2];
			arr[index2] = *backup;

			delete backup;

		}

	}

	void sort(bool descending) {

		for (int i = 0; i < sz; i++)
			for (int j = i; j < sz; j++)
				if (descending ? arr[i] < arr[j] : arr[i] > arr[j])
					switchValues(arr[i], arr[j]);

	}

	double get(int index) {

		if (index <= sz)
			return arr[index];

		return *(new double);

	}

	int size() {

		return sz;

	}

};

template < >
class ArrayList<float> {

private:
	float* arr;
	float* backupArr;

	int sz = 0;

	void switchValues(float& a, float& b) {

		a = a + b;
		b = a - b;
		a = a - b;

	}

public:
	void add(float val) {

		if (arr == nullptr) {

			arr = new float[sz + 1];
			arr[sz] = val;

		}
		else {

			backupArr = new float[sz];

			for (int i = 0; i < sz; i++)
				backupArr[i] = arr[i];

			arr = new float[sz + 1];

			for (int i = 0; i < sz; i++)
				arr[i] = backupArr[i];

			arr[sz] = val;

		}

		sz++;

	}

	void set(int index, float val) {

		arr[index] = val;

	}

	void del(int index) {

		if (index < sz) {

			backupArr = new float[sz - 1];
			for (int i = 0; i < sz - 1; i++)
				backupArr[i] = arr[i >= index ? i + 1 : i];

			arr = new float[sz - 1];
			for (int i = 0; i < sz - 1; i++)
				arr[i] = backupArr[i];

			sz--;

		}

	}

	void sw(int index1, int index2) {

		if (index1 <= sz && index2 <= sz) {

			float* backup = new float(arr[index1]);
			arr[index1] = arr[index2];
			arr[index2] = *backup;

			delete backup;

		}

	}

	void sort(bool descending) {

		for (int i = 0; i < sz; i++)
			for (int j = i; j < sz; j++)
				if (descending ? arr[i] < arr[j] : arr[i] > arr[j])
					switchValues(arr[i], arr[j]);

	}

	float get(int index) {

		if (index <= sz)
			return arr[index];

		return *(new float);

	}

	int size() {

		return sz;

	}

};