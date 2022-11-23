#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct flights
{
    char name_of_airlines[200];
    double x_coordinate;
    double y_coordinate;
}flights;

void distance(struct flights SA[] , int n  ,  double dist_array[] ){
    int start = 0;
    for(int i = 0 ; i!= n-1 ; ++i){
        for(int j = i+1 ; j != n ; ++j){
            double distance_formula = sqrt(((SA[i].y_coordinate - SA[j].y_coordinate) * (SA[i].y_coordinate - SA[j].y_coordinate)) + ((SA[i].x_coordinate - SA[j].x_coordinate) * (SA[i].x_coordinate - SA[j].x_coordinate)));
            dist_array [start] = distance_formula;
            start++;
        }

    }
}
int intCmp(const void * a, const void * b) {
    return (int) (*(double*)a-*(double*)b);
}
int count (double arr[] , int n ){
    int i , count=1;
    qsort(arr , n , sizeof(double) , (int (*)(const void * , const void * )) intCmp);
    for(i = 0 ; i < n - 1 ; i++){
        //printf("%d %d", i, n);
        if( fabs( arr[i+1] - arr[0]) <= __DBL_EPSILON__*arr[i+1]*arr[0]*1000){
            count++;
        }
    }
    return count;
}
void print_pairs(double arr[] ,struct flights SA[] , int n ){
    int start = 0;
    for(int i = 0 ; i!= n-1 ; ++i){
        for(int j = i+1 ; j != n ; ++j) {
            double temp_dist = sqrt(
                    ((SA[i].y_coordinate - SA[j].y_coordinate) * (SA[i].y_coordinate - SA[j].y_coordinate)) +
                    ((SA[i].x_coordinate - SA[j].x_coordinate) * (SA[i].x_coordinate - SA[j].x_coordinate)));
            if(temp_dist - arr[0] <= __DBL_EPSILON__*temp_dist*arr[0]*1000){
                printf("%.199s - %.199s\n" , SA[start].name_of_airlines , SA[j].name_of_airlines);
            }
        }
        start++;
    }
}

flights* read_input(int * size) {
    int number_of_elements = 0;
    int max = 200;
    flights *data = (flights*) malloc(max * sizeof(*data));
    while (scanf("%lf,%lf: %s", &data[number_of_elements].x_coordinate, &data[number_of_elements].y_coordinate,data[number_of_elements].name_of_airlines) == 3) {
        if (number_of_elements >= max) {
           max = max * 2 + 1;
            data = (flights*) realloc(data, max * sizeof(*data));
        }
        number_of_elements++;
    }
    if (!feof(stdin)) {
        printf("Invalid input.\n");
        exit(1);
    }

    *size = number_of_elements;
    return data;
}


int main() {
    flights *array;
    int size = 0;
    printf("Plane coordinates:\n");
    array = read_input(&size);

    if(size >= 2){
        double * dist_array;
        int distance_array_will_have = (size - 1) * (size) / 2;
        dist_array = (double*) malloc(distance_array_will_have * sizeof(double));
        distance(array, size ,dist_array);

        int counts = count(dist_array , distance_array_will_have);


        printf("Minimum airplane distance: %lf\n",dist_array[0]);
        printf("Pairs found: %d\n",counts);
        print_pairs(dist_array , array , size);
        free(dist_array);
    }
    else{
        printf("Invalid input.\n");
    }
    free(array);
    return 0;
}
