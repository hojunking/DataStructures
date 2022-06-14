#include <stdio.h>
#include <string.h>
#define MAX_DEGREE 101
typedef struct {
	int degree;
	int coef[MAX_DEGREE];
} polynomial;
/*
input degree 3, coef 1 2 3 4
input degree 4, coef 1 2 3 4 5
add coef result C
*/

void inputCoefficients(polynomial* T,int len) {
	for (int i = len; 0<= i ; i--) 
		scanf_s("%d", &(T->coef[i]));
}

void printPoly(polynomial T, char t) {
	printf("%c(X) = ", t);
	for (int i = T.degree; 0 <= i; i--) {
		if (i == T.degree) printf("%dx^%d ", T.coef[i], i);
		else if(i == 0) printf("+ %d ", T.coef[i]);
		else if (i < T.degree) printf("+ %dx^%d ", T.coef[i], i);
	}
	printf("\n");
}
void addPoly(polynomial A, polynomial B, polynomial* C) {
	for (int i = 0; i <= A.degree; i++) 
		C->coef[i] += A.coef[i];

	for (int i = 0; i <= B.degree; i++)
		C->coef[i] += B.coef[i];
	C->degree = A.degree > B.degree ? A.degree : B.degree; //둘 중 큰 값
}


int main(void) {
	polynomial A, B, C;
	memset(A.coef, 0, sizeof(A.coef)); //구조체 타입 0으로 초괴화
	memset(B.coef, 0, sizeof(B.coef));
	memset(C.coef, 0, sizeof(C.coef));
	int i;

	printf("<< C(x) = A(x) + B(x) >>\n");
	printf("Input the degree of items of A(x) : ");
	scanf_s("%d", &i); A.degree = i;
	printf("Input the coefficients A(x) : ");
	inputCoefficients(&A, i);
	
	printf("Input the degree of items of B(x) : ");
	scanf_s("%d", &i); B.degree = i;
	printf("Input the coefficients B(x) : ");
	inputCoefficients(&B, i);

	printPoly(A, 'A');
	printPoly(B, 'B');
	addPoly(A, B, &C);
	printPoly(C, 'C');
}