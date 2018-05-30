
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Struct */
typedef struct matrix
{
	float ** value;
	int 	 line;
	int 	 column;

} matrix_t;

/* Function */


matrix_t zeroMatrix(int line,int column,int *errorCode)
{
	int i, j;
	
	matrix_t matrix;
	matrix.value = NULL;
	matrix.line = line;
	matrix.column = column;

	/* We can get dimension of the matrice n*m through the first line*/
	
	*errorCode = 0;

	matrix.value = malloc(matrix.line * sizeof(float*));

	/* We ensure the allocation went well */
	if (matrix.value == NULL)
	{
		return(matrix);
	}

	/* TODO: free the memory already allocate if we encouter a problem */
	for(i=0; i< matrix.line; i++)
	{
		matrix.value[i]= malloc(matrix.column * sizeof(float));
		/* Again, we check if the allocation went well */
		if(matrix.value[i]==NULL)
		{
			return(matrix);
		}
	}
	/* Then we get the values of the matrix */
	*errorCode = 1;


	for(i = 0;i < matrix.line;i++)
	{
		for(j=0;j < matrix.column;j++)
		{
			matrix.value[i][j] = 0.0f;
		}
	}
	return(matrix);
}

/* cette fonction fait tout aussi bien une multiplication de matrices entre elles  */
/* que la multiplication d'un vecteur et d'une matrice                             */


matrix_t multiply(matrix_t A,matrix_t B,int *errorCode)
{
	int error;
	matrix_t matrixRes;
	int i,j;

	matrixRes.value = NULL;

	/* We first verify that we can't actualy do the multiplication */
	if(A.column == B.line)
	{
		/* We can perform the multiplication */
		matrixRes.line = A.line;
		matrixRes.column = B.column;

		
		matrixRes = zeroMatrix(A.line,B.column,&error);
		*errorCode = 1;

		if(error == 1)
		{
				for(i=0;i < matrixRes.line;i++)
				{
					for(j=0;j < matrixRes.column;j++)
					{
						int k=0;
						for(k=0;k < A.line;k++)
						{
							matrixRes.value[i][j] += A.value[i][k] * B.value[k][j];
						}
					}
				}
		}
		else
		{
			*errorCode = 0;
			printf("[ERROR] : Unable to allocate enough space to create a third matrix !\n");
		}


	}
	else
	{
		*errorCode = -1;
		printf("[ERROR] : Can't perform multiplication due to matrix's dimensions : (%d,%d) and (%d,%d)\n",A.line,A.column,B.line,B.column);
	}

	return(matrixRes);
}



void printMatrix(matrix_t matrix)
{
	int i,j;

	for(i = 0;i < matrix.line;i++) /* we go through lines of the matrix */
	{
		for(j=0;j < matrix.column;j++) /* we go through columns of the matrix */
		{

			printf("%f \t",matrix.value[i][j]); /* we display the value of the element in the line i and the column j */
		
		}

		printf("\n");
	}
}

double produitscalaireVecteur(matrix_t X, matrix_t Y, int* errorCode)
{	
	int   k;
	double x=0;
	int   j=X.line;
	int   i=Y.line;
	
	*errorCode=0;
	
	if (j==i)
	{
		for (k=0;k<j;k++)
		{
			x+=X.value[k][0]*Y.value[k][0];
		}
		*errorCode=1;    /* tout s'est bien passé */
	}
	else 
	{
		*errorCode=-1;   /* il y a eu un  problème */
		printf("Error \n");
	}
	
	return x;
}
matrix_t creationHilbert(int N)
{
	int i,j;
	int errorCode;
	matrix_t A;
	A=zeroMatrix(N,N,&errorCode);
	for (i=1;i<N+1;i++)
	{
		for(j=1;j<N+1;j++)
		{
			A.value[i-1][j-1]=1.0/(i+j-1);
		}
	}
	return A;
}

matrix_t creationPascal(int N)
{
	int i,j;
	int errorCode;
	matrix_t A;
	A=zeroMatrix(N,N,&errorCode);
	for (i=0;i<N;i++)
	{
		A.value[i][0]=1;
		for (j=0;j<N;j++)
		{	
			A.value[0][j]=1;
			if (i>=1 && j>=1)
			{
				A.value[i][j]=A.value[i-1][j] + A.value[i][j-1];
			}
		}
	}
	return A;

}

matrix_t opposeMatrix(matrix_t A,int* errorCode)
{
	int i,j;
	int N=A.line;
	int M=A.column;
	matrix_t X= zeroMatrix(N,M,errorCode);
	for(i=0;i<N;i++)
	{
		for(j=0;j<M;j++)
		{
			X.value[i][j]=-A.value[i][j];
		}
	}
	return X;
}

matrix_t soustractionMatrix(matrix_t A, matrix_t B,int* errorCode)
{
	int i,j;
	*errorCode=0;
	if(A.line==B.line && A.column==B.column)
	{
		for(i=0;i<A.line;i++)
		{
			for(j=0;j<A.column;j++)
			{
				A.value[i][j]-=B.value[i][j];
			}
		}
		*errorCode=1;
	}
	else
	{
		*errorCode=-1;
	}
	return A;
}

matrix_t multiplierParUnScalaire(double t, matrix_t B)
{
	int i,j;
	
	for(i=0;i<B.line;i++)
	{
		for(j=0;j<B.column;j++)
		{
			B.value[i][j]*=t;
		}
	}

	
	
	return B;
}


matrix_t additionMatrix(matrix_t A, matrix_t B,int* errorCode)
{
	int i,j;
	*errorCode=0;
	if(A.line==B.line && A.column==B.column)
	{
		for(i=0;i<A.line;i++)
		{
			for(j=0;j<A.column;j++)
			{
				A.value[i][j]+=B.value[i][j];
			}
		}
		*errorCode=1;
	}
	else
	{
		*errorCode=-1;
	}
	return A;
}

/* 	La matrice A représente la matrice symétrique définie positive 	*/
/* 	Le vecteur X (matrice (n,1)) représente le point initial       	*/
/*	Le vecteur B représente le second membre                        */

matrix_t algoGradConjug(matrix_t A, matrix_t B, float epsi, int* errorCode)
{
	matrix_t X;
	matrix_t Y;        /* cette matrice stockera la vecteur du gradient de l'itération précédente*/
	matrix_t r;        /* matrice du gradient */
	matrix_t d;        /* matrice  d=-r       */
	matrix_t q;        /* vecteur qk          */
	double   t;           /* le temps */
	double   b;           /* norme de b */
	double   z;           /* valeur du quotient de la condition dans la boucle*/
	double   beta;


	X=zeroMatrix(A.line,1,errorCode);
	Y=zeroMatrix(A.line,1,errorCode);
	r=zeroMatrix(A.line,1,errorCode);
	d=zeroMatrix(A.line,1,errorCode);
	q=zeroMatrix(A.line, 1,errorCode);

	b=sqrt(abs(produitscalaireVecteur(B,B,errorCode)));
	
	
	/*initialisation */
	r = soustractionMatrix(multiply(A,X,errorCode),B,errorCode);
	d = opposeMatrix(r,errorCode);
	z=sqrt(abs(produitscalaireVecteur(r,r,errorCode)))/b;
	
	/* fin initialisation */

	/*début itération */

	while(z>epsi)
	{
		q = multiply(A,d,errorCode);
		t = produitscalaireVecteur(r,r,errorCode)/produitscalaireVecteur(d,q,errorCode);
		X = additionMatrix(X,multiplierParUnScalaire(t,d),errorCode);
		Y = r;
		r = additionMatrix(r,multiplierParUnScalaire(t,q),errorCode);
		beta= produitscalaireVecteur(r,r,errorCode)/produitscalaireVecteur(Y,Y,errorCode);
		d = soustractionMatrix(multiplierParUnScalaire(beta,d),r,errorCode);
		z = sqrt(abs(produitscalaireVecteur(r,r,errorCode)))/b;

	}
	
	return X;


}

matrix_t secondMembre(int N,int* errorCode)
{
	int i;
	matrix_t B = zeroMatrix(N,1,errorCode);
	for(i=0;i<N;i++)
	{
		B.value[i][0]=1;
	}
	return B;
}

int main()
{
	int k,i;
	int N=20;
	int errorCode;
	float epsi= 1e-6;
	double y;
	matrix_t X;
	matrix_t Y;
	matrix_t A;
	matrix_t B;
	B=zeroMatrix(N,1,&errorCode);
	A=zeroMatrix(N,1,&errorCode);
	Y=zeroMatrix(N,1,&errorCode);
	X=zeroMatrix(N,N,&errorCode);
	B=secondMembre(N,&errorCode);
	A=creationPascal(N);
	
	X=algoGradConjug(A,B,epsi,&errorCode);
	printMatrix(X);
	return 0;
}
			
