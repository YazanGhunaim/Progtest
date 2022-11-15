// [1,2,3,4,5]
// length of array is 5
// resulting RangeSum array should be sum of 4! "4+3+2+1"
// [3,4,5,6,5,6,7,7,8,9]

#include <stdio.h>
#include <stdlib.h>

/*
	RangeArrayMax:
		preprocessor value is defined as the maximum number of elements the
		RangeSumArray can hold when the input array reaches the defined max of 2000. (this number has been derived by calculating the nth triangular number of 2000)

	MAX:
		defined as the max number of elements that can be inputed as the original array
		"According to Progtest Specifications"
*/
#define RANGEARRAYMAX 1999000
#define MAX 2000

/*
	rangeSum:
		@brief: sums the values of an array using defined start and end parameters and returns the sum

		@example: [1,2,3,4,5] rangeSum(array,1,4) -> 1+2+3+4+5 = 15

	fillArray:
		@brief: the core function of this program, using rangeSum and the answer array defined in main it generates an array with the appropriate nth triangular number length
				based of the length of the original array, and inserts range sum values in respected indexes. (the array returned here is the one used to count equal pairs).

		@parameters:
			- input array head address
			- return array head address
			- length of original input array
			- desired length of output array

	countDuplicates:
		@brief: Counts how many pairs in the answer array have the same sum (the result the progtest needs)

		@parameters:
			- answer array head address
			- its length

	readData:
		@brief: takes address head of input array and starts scanning for user input of the elements for the array
				while keeping track of the correct index and size, returning the size to main using pointers with the use
				of output parameters. Also checks if the size ever reaches over 2000 and/or the input is not a valid integer which
				results in invalid input

		@parameters:
			- head address of input array
			- address of length variable in main so it can modify it
*/
int rangeSum(int array[], int start, int end, int prefixSum[]);
void fillArray(int filled[], int array[], int lengthofArray, int lengthOfFilled, int prefixSum[]);
int countDuplicates(int answer[], int n);
int readData(int array[], int *n);
void prefixSumArray(int array[], int lengthofArray, int prefixSum[]);

int main()
{
	// initializing lengthOfRangeSumArray array as 0
	// declaring input array with size MAX defined as 2000
	// declaring answer array with size RANGEARRAYMAX defined as 1999000
	// int n will hold values from the scanf and input them in the array
	int lengthOfRangeSumArray = 0;
	int array[MAX];
	int answer[RANGEARRAYMAX];
	int prefixSum[MAX];

	// initializing input array length as 0 and incrementing it as we input more elements same with index
	int length = 0;

	printf("Input sequence:\n");
	if (!readData(array, &length))
	{
		printf("Invalid input.\n");
		return 1;
	}

	lengthOfRangeSumArray = (0.5 * length) * (length - 1);
	prefixSumArray(array,length,prefixSum);
	// using fillArray to fill answer with the rangesums of elements inputed
	fillArray(answer, array, length, lengthOfRangeSumArray, prefixSum);

	// printing the desired result of how many pairs of ranges have equal sums
	printf("Total pairs: %d\n", countDuplicates(answer, lengthOfRangeSumArray));

	return 0;
}

int readData(int array[], int *n)
{
	int length = 0;
	int index = 0;
	int input = 0;
	while (scanf("%d", &input) == 1)
	{
		// if length ever reaches 2000 and we are still asking for user input, ie EOF not reached then exceeds required.
		if (length == MAX)
		{
			return 0;
		}
		array[index] = input;
		length++;
		index++;
	}

	if (!feof(stdin) || length == 0)
	{
		return 0;
	}
	// assigns value of length to address of n, now length in main is modified
	*n = length;
	return 1;
}

int rangeSum(int array[], int start, int end, int prefixSums[])
{
	int sum = prefixSums[end];
	if (start > 0)
		sum -= prefixSums[start - 1];

	// for (int i = start; i <= end; ++i)
	// 	sum += array[i];

	return sum;
}

/*
	Index variable keeps track of what index to insert the value of the sum out of the length of the entire answer array

	example of how everything works together:

		array[] = {1,2,3,4,5}

		values at the starts:
			- length of array: 5
			- length of filled: (0.5*5)*(4) = 10
			- index: 0
			- i: 0
			- count = k : 1
			- j: 0

		first loop:
			assigns answer[0] to rangeSum(array,0,1)
			-inner loops keeps running until rangeSum(array,0,4)
			and so on to fill entirity of answer array with respected values.
*/

void prefixSumArray(int array[], int lengthofArray, int prefixSum[])
{
	int sum = 0;
	for (int i = 0; i < lengthofArray; i++)
	{
		sum += array[i];
		prefixSum[i] = sum;
	}
}

void fillArray(int answer[], int array[], int lengthofArray, int lengthOfFilled, int prefixSum[])
{

	int index = 0;
	for (int i = 0; i < lengthOfFilled; i++)
	{
		int count = i + 1;
		for (int j = 0, k = count; j < lengthofArray - 1 && k < lengthofArray; j++)
		{
			answer[index] = rangeSum(array, i, k, prefixSum);
			index++;
			k++;
		}
	}
}

int countDuplicates(int answer[], int n)
{

	int ans = 0;

	// for each index i and j
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)

			// finding the index with same
			// value but different index.
			if (answer[i] == answer[j])
				ans++;
	return ans;
}
