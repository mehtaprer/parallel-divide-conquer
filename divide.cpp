#include <iostream>
#include <vector>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <time.h>

#define lu(x) printf("%lu\n",x);
#define d(x) printf("%d\n",x);
#define f(x) printf("%.2f\t",x);
#define loop0(i,n) for(int i=0;i<n;i++)
#define loop(i,m,n) for(int i=m;i<n;i++)

#define MAX 100 // maximum size of float value
using namespace std;

class subMatrix{
    public:
    float **m;
    int row,col,size;
    subMatrix(float **a,int r,int c,int n){
        m=a;
        row=r;
        col=c;
        size=n;
    }
};

subMatrix multiply(subMatrix,subMatrix,int);
void divide(int);
float** init(int);
void clear(float**,int);
void generate(float **a,int n);
void add(subMatrix c,subMatrix a,subMatrix b,int n);
subMatrix multiply(const subMatrix a,const subMatrix b,int n);

double time_elapsed(struct timespec start, struct timespec end) {
    double t;
    t = (end.tv_sec - start.tv_sec); //diff of tv_sec
    t += (end.tv_nsec - start.tv_nsec) * 0.000000001; //add diff of tv_nsec too
    return t;
}


int main(){
    srand(time(NULL));
    int n;
    cin>>n;
    divide(n);
    return 0;
}

//Function to create a matrix in heap
float** init(int n){
    float **a=new float*[n];
    loop0(i,n){
        a[i]=new float[n];
    }
    return a;
}

//function to clear the memory allocated to arrays
void clear(float **a,int n){
    loop0(i,n){
        delete(a[i]);
    }
    delete(a);
}

//Function to fill a matrix with random values
void generate(float **a,int n){
    
    loop0(i,n){
        loop0(j,n){
            a[i][j]=((float)rand()/(float)RAND_MAX)*MAX;
        }
    }

}


//Divide and Conquer
void divide(int n){
    struct timespec start,end;
    float **m1=init(n);
    float **m2=init(n);
    generate(m1,n);
    generate(m2,n);
    loop0(i,n){
        loop0(j,n){
            m1[i][j]=1;
            m2[i][j]=1; 
        }
    }

    subMatrix mat1 = subMatrix(m1,0,0,n);
    subMatrix mat2 = subMatrix(m2,0,0,n);
    clock_gettime(CLOCK_REALTIME,&start);
    subMatrix res = multiply(mat1,mat2,n);
    clock_gettime(CLOCK_REALTIME,&end);
    cout<<time_elapsed(start,end)<<"\n";
    clear(m1,n);
    clear(m2,n);
}


//Addind two matrix
void add(subMatrix c,subMatrix a,subMatrix b,int n){
    loop0(i,n){
        loop0(j,n){
            c.m[c.row+i][c.col+j]=a.m[a.row+i][a.col+j]+b.m[b.row+i][b.col+j];
        }
    }
}

//Recurssive multiply function
subMatrix multiply(const subMatrix a,const subMatrix b,int n){
    float **c = init(n);
    subMatrix cm = subMatrix(c,0,0,n);
    if(n<9){
        loop0(i,n){
            loop0(j,n){
                int sum = 0;
                loop0(k,n){
                    sum +=a.m[a.row+i][a.col+k]*b.m[b.row+k][b.col+j];
                }
                cm.m[cm.row+i][cm.col+j]=sum;
            }
        }
    }
    else{
        subMatrix a11 = subMatrix(a.m,0,0,n/2);
        subMatrix a12 = subMatrix(a.m,0,n/2,n/2);
        subMatrix a21 = subMatrix(a.m,n/2,0,n/2);
        subMatrix a22 = subMatrix(a.m,n/2,n/2,n/2);
        subMatrix b11 = subMatrix(b.m,0,0,n/2);
        subMatrix b12 = subMatrix(b.m,0,n/2,n/2);
        subMatrix b21 = subMatrix(b.m,n/2,0,n/2);
        subMatrix b22 = subMatrix(b.m,n/2,n/2,n/2);
        subMatrix x1=multiply(a11,b11,n/2);
        subMatrix x2=multiply(a12,b21,n/2);
        subMatrix x3=multiply(a11,b12,n/2);
        subMatrix x4=multiply(a12,b22,n/2);
        subMatrix x5=multiply(a21,b11,n/2);
        subMatrix x6=multiply(a22,b21,n/2);
        subMatrix x7=multiply(a21,b12,n/2);
        subMatrix x8=multiply(a22,b22,n/2);
        subMatrix c11 = subMatrix(c,0,0,n);
        subMatrix c21 = subMatrix(c,n/2,0,n);
        subMatrix c12 = subMatrix(c,0,n/2,n);
        subMatrix c22 = subMatrix(c,n/2,n/2,n); 
        add(c11,x1,x2,n/2);
        add(c12,x3,x4,n/2);
        add(c21,x5,x6,n/2);
        add(c22,x7,x8,n/2);
        clear(x1.m,n/2); 
        clear(x2.m,n/2);
        clear(x3.m,n/2);
        clear(x4.m,n/2);
        clear(x5.m,n/2);
        clear(x6.m,n/2);
        clear(x7.m,n/2);
        clear(x8.m,n/2);
    }
    return cm;
}
