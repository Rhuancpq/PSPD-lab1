#include <stdio.h>
#include <math.h>

typedef float Item;

#define key(A) A

#define less(A, B) (key(A) <  key(B))

#define lessequal(A, B) (key(A) <=  key(B))

#define exch(A, B) {Item t = A; A = B; B = t;}

#define cmpexch(A, B) {if(less(B, A)) exch(A, B)}

int separa(Item *v, int l, int r){
    Item c = v[r];
    int j = l;
    for(int k = l; k < r; k++){
        if(lessequal(v[k], c)){
            exch(v[k], v[j]);
            j++;
        }
    }
    exch(v[j], v[r]);
    return j;
}

void quickselect(Item *v, int l, int r, int k){
    cmpexch(v[(l+r)/2], v[r]);
    cmpexch(v[l], v[(l+r)/2]);
    cmpexch(v[r], v[(l+r)/2]);
    int i;
    i = separa(v, l, r);
    if(i > k) quickselect(v,l,i-1, k);
    if(i < k) quickselect(v, i+1, r, k);
}

typedef struct {
    float f, l;
} Pair;

Pair get_minor_and_major(int n, float * v) {
    int i;
    float min, max;
    min = max = v[0];
    for (i = 1; i < n; i++) {
        if (v[i] < min) {
            min = v[i];
        }
        if (v[i] > max) {
            max = v[i];
        }
    }

    Pair p;
    p.f = min;
    p.l = max;

    return p;
}

Pair get_minor_and_major_qs(int n, int * v) {
    // TODO

    return (Pair) {0, 0};
}

int main (int argc, char *argv[]) {
    float v[10];
 
    for (int i = 0; i < 10; i++) {
        v[i] = (i - 5) * (i - 5);
    }

    for (int i = 0; i < 10; i++) {
        v[i] = sqrt(v[i]);
    }

    Pair p = get_minor_and_major(10, v);

    printf("minor: %f\n", p.f);
    printf("major: %f\n", p.l);

   return 0;
}