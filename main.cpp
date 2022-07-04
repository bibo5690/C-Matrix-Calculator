#include <iostream>
#include <cmath>
using namespace std;

void mult(long double m[10][10], long double a[10][10], long double b[10][10], int a_dim1, int b_dim1, int b_dim2);
long double det(long double x[10][10], int dim);
void inverse(long double mainMat[10][10], long double x[10][10], int dim);

int main()
{
	cout << "Please enter dimensions of Matrix A:" << "\n";
	int A_dim1, A_dim2;
	cin >> A_dim1 >> A_dim2;

	cout << "Please enter dimensions of Matrix B:" << "\n";
	int B_dim1, B_dim2;
	cin >> B_dim1 >> B_dim2;

	cout << "Please enter values of Matrix A:" << "\n";
	long double A[10][10];
	for (int i = 0; i < A_dim1; i++) {
		for (int j = 0; j < A_dim2; j++) {
			cin >> A[i][j];
		}
	}

	cout << "Please enter values of Matrix B:" << "\n";
	long double B[10][10];
	for (int i = 0; i < B_dim1; i++) {
		for (int j = 0; j < B_dim2; j++) {
			cin >> B[i][j];
		}
	}

	int choice;
	do {
		cout << "Please choose operation type(1: A+B, 2: A-B, 3: AxB, 4: A*inverse(B), 5: |A|, 6: |B|, 7: quit):" << "\n";
		cin >> choice;

		if (choice == 1) {
			if (A_dim1 != B_dim1 || A_dim2 != B_dim2)
				cout << "The operation you chose is invalid for the given matrices." << "\n";
			else {
				long double sum[10][10];
				for (int i = 0; i < A_dim1; i++) {
					for (int j = 0; j < A_dim2; j++) {
						sum[i][j] = round(A[i][j] + B[i][j]);
						cout << sum[i][j] << " ";
					}
					cout << "\n";
				}
			}
		}

		else if (choice == 2) {
			if (A_dim1 != B_dim1 || A_dim2 != B_dim2)
				cout << "The operation you chose is invalid for the given matrices." << "\n";
			else {
				long double sub[10][10];
				for (int i = 0; i < A_dim1; i++) {
					for (int j = 0; j < A_dim2; j++) {
						sub[i][j] = round(A[i][j] - B[i][j]);
						cout << sub[i][j] << " ";
					}
					cout << "\n";
				}
			}
		}

		else if (choice == 3) {
			if (A_dim2 != B_dim1)
				cout << "The operation you chose is invalid for the given matrices." << "\n";
			else {
				long double mult_1[10][10];
				mult(mult_1, A, B, A_dim1, B_dim1, B_dim2);
				for (int i = 0; i < A_dim1; i++) {
					for (int j = 0; j < B_dim2; j++) {
						cout << mult_1[i][j] << " ";
					}
					cout << "\n";
				}
			}
		}

		else if (choice == 4) {
			if (B_dim1 == B_dim2 && A_dim2 == B_dim1 && (det(B, B_dim1) != 0)) {
				long double cofactor = 1 / det(B, B_dim1);
				long double inverseMat[10][10], mult_2[10][10];
				long double matOfDeterminants[10][10];
				int sign = 1;

				if (B_dim1 == 1) {
					for (int i = 0; i < A_dim1; i++) {
						for (int j = 0; j < A_dim2; j++) {
							int result = round(A[i][j] / B[0][0]);
							if (result == -0)
								result = 0;
							cout << result;
						}
						cout << "\n";
					}
				}

				else if (B_dim1 %2 ==0) {
					inverse(B, matOfDeterminants, B_dim1);
					for (int i = 0; i < B_dim1; i++) {
						for (int j = 0; j < B_dim2; j++) {
							//cout<< cofactor * matOfDeterminants[j][i]<<" ";
							inverseMat[i][j] = sign * cofactor * matOfDeterminants[j][i];
							sign *= -1;
						}
					}
					mult(mult_2, A, inverseMat, A_dim1, B_dim1, B_dim2);
					for (int i = 0; i < A_dim1; i++) {
						for (int j = 0; j < B_dim2; j++) {
							mult_2[i][j] = round(mult_2[i][j]);
							if (mult_2[i][j] == -0)
								mult_2[i][j] = 0;
							cout << mult_2[i][j] << " ";
						}
						cout << "\n";
					}
				}
				else {
					inverse(B, matOfDeterminants, B_dim1);
					for (int i = 0; i < B_dim1; i++) {
						for (int j = 0; j < B_dim2; j++) {
							//cout<< cofactor * matOfDeterminants[j][i]<<" ";
							inverseMat[i][j] = cofactor * matOfDeterminants[j][i];
						}
					}
					mult(mult_2, A, inverseMat, A_dim1, B_dim1, B_dim2);
					for (int i = 0; i < A_dim1; i++) {
						for (int j = 0; j < B_dim2; j++) {
							mult_2[i][j] = round(mult_2[i][j]);
							if (mult_2[i][j] == -0)
								mult_2[i][j] = 0;
							cout << mult_2[i][j] << " ";
						}
						cout << "\n";
					}
				}
			}
			else
				cout << "The operation you chose is invalid for the given matrices." << "\n";
		}
		else if (choice == 5) {
			if (A_dim1 != A_dim2)
				cout << "The operation you chose is invalid for the given matrices." << "\n";
			else {
				long long int AA = round(det(A, A_dim1));
				cout << AA << "\n";
			}
		}

		else if (choice == 6) {
			if (B_dim1 != B_dim2)
				cout << "The operation you chose is invalid for the given matrices." << "\n";
			else {
				long long int BB = round(det(B, B_dim1));
				cout << BB << "\n";
			}
		}

		else if (choice == 7) {
			cout << "Thank you!";
		}
		else
			cout << "The operation you chose is invalid for the given matrices." << "\n";
	} while (choice != 7);
}

void mult(long double m[10][10], long double a[10][10], long double b[10][10], int a_dim1, int b_dim1, int b_dim2)
{
	for (int i = 0; i < a_dim1; i++) {
		for (int j = 0; j < b_dim2; j++) {
			m[i][j] = 0;
			for (int z = 0; z < b_dim1; z++)
				m[i][j] += a[i][z] * b[z][j];
		}
	}
}

long double det(long double x[10][10], int dim)
{
	int sign = 1;
	long double subM[10][10];
	long double deter = 0;
	if (dim == 1) {
		deter = x[0][0];
		return deter;
	}
	else if (dim == 2) {
		deter = (x[0][0] * x[1][1]) - (x[1][0] * x[0][1]);
		return deter;
	}
	else {
		for (int y = 0; y < dim; y++)
		{
			int subM_i = 0;
			//start from 1 as row 0 is cofactor
			for (int i = 1; i < dim; i++)
			{
				int subM_j = 0;
				for (int j = 0; j < dim; j++)
				{
					if (j == y)
						continue;
					subM[subM_i][subM_j] = x[i][j];
					subM_j++;
				}
				subM_i++;
			}
			long double cofactor = x[0][y];
			deter += sign * cofactor * det(subM, dim - 1);
			sign *= -1;
		}
		return deter;
	}
}

void inverse(long double mainMat[10][10], long double x[10][10], int dim)
{
	int sign = 1;
	long double subM[10][10];

	for (int o = 0; o < dim; o++) {
		for (int y = 0; y < dim; y++)
		{
			int subM_i = 0;
			for (int i = 0; i < dim; i++)
			{
				if (i == o)
					continue;
				int subM_j = 0;
				for (int j = 0; j < dim; j++)
				{
					if (j == y)
						continue;
					subM[subM_i][subM_j] = mainMat[i][j];
					subM_j++;
				}
				subM_i++;
			}
			x[o][y] = sign * det(subM, dim - 1);
			sign *= -1;
		}
	}
}


