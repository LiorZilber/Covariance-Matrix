
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
/*
 * returns the mean of a given row
 */
double meanRow(int n, double* firstIndex){
	double sum = 0.0; double result = 0.0;int i ;
	for( i = 0; i<n; ++i ){
		sum += *(firstIndex );
		firstIndex++;
	}
	firstIndex = firstIndex - n;
	result = sum/(double) n;
	return result;

}
/*
 * given a value and an array, subs the value of each cell
 */
void subMean(int n, double* row, double meanRow){
	int i ;
	for(i =0; i<n; ++i){
		*row = *row - meanRow;
		row++;
	}
	row = row - n;
}

/*
 * returns the dotProduct of two given vectors
 */
double dotProduct(double* firstRow, double* secondRow, int m){
	int i ; double resultProduct = 0.0;
	for(i = 0 ;i<m ; ++i){
		resultProduct += (*(firstRow)) * (*(secondRow ));
		firstRow++;
		secondRow++;
	}
	secondRow = secondRow - m;
	firstRow = firstRow - m;

return resultProduct;
}

/*
 * given an array, reads the matrix into it
 */
void writeToMatrix(double* arr, FILE* inputFile, int length)
{
	int numOfWrittenItems;
	numOfWrittenItems = fread(arr, sizeof(double),length,inputFile);
	assert(numOfWrittenItems==length);
}
/*
 * changes each cell's value by its value  minus the mean of the corresponding row
 */
void subMatrix(double* rowPointer, int numOfRows, int numOfCoulmns){
	int i ; double mean;
	for (i = 0; i<numOfRows*(numOfCoulmns); i+= numOfCoulmns){
		mean = meanRow(numOfCoulmns,rowPointer );
		subMean(numOfCoulmns,rowPointer , mean);
		rowPointer  = rowPointer + numOfCoulmns;
	}
	rowPointer  = rowPointer - numOfRows*(numOfCoulmns);

}

/* given a pointer to a row
 * calculates for each cell its dot product
 */
void dotProductForRow(double* mat,double* arr,double* pRow,int n, int m){
	int i;
	for( i=0 ; i<n ; i++ ){
		*mat = dotProduct(pRow,arr,m);
		arr = arr + m;
		mat++;
	}
	mat = mat - n;
	arr = arr - (n*m);
}

/*
 * writes the matrix into the file
 */
void rowsToFile(double* mat,double* arr,int n,int m, FILE* file){
	int i; int k; double* temp;
	temp = arr;
	for(i=0;i<n;i++){

			dotProductForRow(mat,arr,temp,n,m);
			temp = temp+m;
			k = fwrite(mat,sizeof(double),n,file);
			assert(k==n);
		}
}

int main(int argc, char* argv[]){
	FILE* inputFile; FILE* outputFile;
	double* arr; int sizes[2]; int n; int m; int numOfWrittenItems; double* mat;
	assert(argc == 3);
	inputFile = fopen(argv[1],"r");
	outputFile = fopen(argv[2],"w");
	numOfWrittenItems = fread(sizes, sizeof(int),2,inputFile);
	assert(numOfWrittenItems==2);
	n = sizes[1];
	m = sizes[0];
	arr = (double*)malloc(n*m*sizeof(double));
	assert(arr!=NULL);
	writeToMatrix(arr,inputFile,n*m);
	subMatrix(arr,n,m);
	mat = (double*)malloc(n*sizeof(double));
	assert(mat!=NULL);
	sizes[0] = n;
	numOfWrittenItems  = fwrite(sizes,sizeof(int),2,outputFile);
	assert(numOfWrittenItems == 2);
	rowsToFile(mat,arr,n,m,outputFile);
	fclose(outputFile);
	fclose(inputFile);
	free(mat);
	free(arr);

		return 0;

	}
