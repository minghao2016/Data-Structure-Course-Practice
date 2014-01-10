#include <iostream>
#include <cstdlib>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;

int randInt(int i, int j)
{
	/**
	 If we uncomment the following srand, it would be hard to run.
	 And, why?
	 */
	
    //srand(((unsigned)time(NULL)));
    return rand() % j-i+1 + i;
}

void algo1(int a[],int N)
{
	/**
	 To compare the random number generation, with out srand.
	 */
	
    //srand(((unsigned)time(NULL)));
    int i = 0;
    
    while (i < N) {
        a[i] = randInt(1, N);
        for (int k = 0; k < i; k++) {
            if ( a[i] == a[k]) {
                i--;
                break;
            }
        }
        i++;
    }
    
    /*for (int i = 0; i < N; i++) {
     cout<<a[i]<<"\t";
     }*/
    
}


void algo2(int a[], int N)
{
    int i = 0;
    bool used[N];
	
    while (i < N) {
        a[i] = randInt(1, N);
		if(a[i]==0)
			a[i]=N;
        if (used[a[i]]-1 == 1) {
            i--;
        } else {
            used[a[i]-1] = 1;
        }
        i++;
    }
    
    /*for (int i = 0; i < N; i++) {
     cout<<a[i]<<"\t";
    }*/
    
}


void algo3(int a[], int N)
{
    for (int i = 0; i < N; i++) {
        a[i] = i+1;
    }
    for (int i = 1; i < N; i++) {
        swap(a[i], a[randInt(0, i)]);
    }
    /*for (int i = 0; i < N; i++) {
     cout<<a[i]<<"\t";
     }*/
}


//typedef void(*pFunction) (int a[], int);

double estimate_time1(int N)
{
    int a[N];
    double Time1=0;
    double tic,toc,t_elapsed;
    
    printf("-- Algorithm 1. N = %d --\n\n",N);
    for (int i = 0; i < 10; i++) {
        tic = clock();
        algo1(a, N);
        toc = clock();
        t_elapsed = (toc - tic) / CLOCKS_PER_SEC;
        Time1 += t_elapsed;
        printf("  Time: %f\n", t_elapsed);
    }
    
    printf("\n-- Algorithm Done. --\n");
    printf("-- Average:  %f --\n\n",Time1 / 10);
    
    return Time1 / 10;
}

double estimate_time2(int N)
{
    int a[N];
    double Time2=0;
    double tic,toc,t_elapsed;
    
    printf("-- Algorithm 2. N = %d --\n\n",N);
    for (int i = 0; i < 10; i++) {
        tic = clock();
        algo2(a, N);
        toc = clock();
        t_elapsed = (toc - tic) / CLOCKS_PER_SEC;
        Time2 += t_elapsed;
        printf("  Time: %f\n", t_elapsed);
    }
    
    printf("\n-- Algorithm Done. --\n");
    printf("-- Average:  %f --\n\n",Time2 / 10);
    
    return Time2 / 10;
}

double estimate_time3(int N)
{
    int a[N];
    double Time3=0;
    double tic,toc,t_elapsed;
    
    printf("-- Algorithm 3. N = %d --\n\n",N);
    for (int i = 0; i < 10; i++) {
        tic = clock();
        algo3(a, N);
        toc = clock();
        t_elapsed = (toc - tic) / CLOCKS_PER_SEC;
        Time3 += t_elapsed;
        printf("  Time: %f\n", t_elapsed);
    }
    
    printf("\n-- Algorithm Done. --\n");
    printf("-- Average:  %f --\n\n",Time3 / 10);
    
    return Time3 / 10;
}

int main()
{
	//vector<double> result;
	double result1[7];
	int test1[7]={250, 500, 1000, 2000, 4000, 8000, 16000};
	for(int i =0; i < 6; i++){
		result1[i] = estimate_time1(test1[i]);
		//result[i] = result1[i];
	}
	
	double result2[7];
	int test2[7]={25000, 50000, 100000, 200000, 400000, 800000, 1600000};
	for(int i =0; i < 7; i++){
		result2[i] = estimate_time2(test2[i]);
		//result[i+7] = result1[i];
	}
    
	double result3[7];
	int test3[7]={100000, 200000, 400000, 800000, 1600000, 3200000, 6400000};
	for(int i =0; i < 5; i++){
		result3[i] = estimate_time3(test3[i]);
		//result[i+14] = result1[i];
	}
	printf("* The program would crash down when N > 1600000.\nSo I did not calculate this step.\n\n");
	
	printf("   Algo 1.\t Algo 2.\t Algo 3.\n");
	printf("-----------------------------------------\n");
	for(int i = 0; i < 7; i++)
		printf("  %f\t%f\t%f\n",result1[i],result2[i],result3[i]);
	printf("-----------------------------------------\n\n");
	
	
	// Experiment Part.
	double a1[7],a2[7],a3[7];
	for(int i =0; i < 7; i++){
		a1[i] = result1[i] / test1[i];
		a2[i] = result1[i] / test1[i]*test1[i];
		a3[i] = result1[i] / test1[i]*log(test1[i]);
	}
	printf("Algo 1.\t O(N)\t O(N^2)\t O(Nlog(N))\n");
	printf("-------------------------------------------------\n");
	for(int i = 0; i < 7; i++)
		printf("N=%d\t %f\t %f\t %f\n",test1[i],a1[i],a2[i],a3[i]);
	printf("-------------------------------------------------\n\n");
	
	
	
	for(int i =0; i < 7; i++){
		a1[i] = result2[i] / test2[i];
		a2[i] = result2[i] / test2[i]*test2[i];
		a3[i] = result2[i] / test2[i]*log(test2[i]);
	}
	printf("Algo 2.\t\t O(N)\t\t O(N^2)\t\t O(Nlog(N))\n");
	printf("---------------------------------------------------------\n");
	for(int i = 0; i < 7; i++)
		printf("N=%d\t %f\t %f\t %f\n",test2[i],a1[i],a2[i],a3[i]);
	printf("---------------------------------------------------------\n\n");
	
	
	
	for(int i =0; i < 7; i++){
		a1[i] = result3[i] / test3[i];
		a2[i] = result3[i] / test3[i]*test3[i];
		a3[i] = result3[i] / test3[i]*log(test3[i]);
	}
	printf("Algo 3.\t\t O(N)\t\t O(N^2)\t\t O(Nlog(N))\n");
	printf("---------------------------------------------------------\n");
	for(int i = 0; i < 7; i++)
		printf("N=%d\t %f\t %f\t %f\n",test3[i],a1[i],a2[i],a3[i]);
	printf("---------------------------------------------------------\n");
	
	
	
	
    return 0;
}