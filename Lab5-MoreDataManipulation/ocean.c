#include <stdio.h>
#include <stdlib.h>

#define OCEAN_MAX 41981

struct ocean_datum {
    int x;
    /* grid-reference east-west
     */
    int y;
    /* grid-reference north-south
     */
    double conc; /* concentration of O_2 in mL/L found at grid-ref (x,y) */
};

void print_ocean_datum(struct ocean_datum *o) {
    printf("%d %d %.4f\n", o->x, o->y, o->conc);
}

int read_ocean_datum(struct ocean_datum *o) {
    return 3 == scanf("%d %d %lg", &o->x, &o->y, &o->conc);
}

int cmp_struct(struct ocean_datum *a,struct ocean_datum *b){
    if(a->conc > b->conc){
        return 0;
    }
    return 1;
}

int main(void) {
    struct ocean_datum ocean_data[OCEAN_MAX];
    struct ocean_datum temp;
    int num_items;
    int i, p, key;

    num_items = 0;
    while (num_items < OCEAN_MAX && read_ocean_datum(&ocean_data[num_items])) {
        num_items++;
    }

    /* sort the data here */
    for(p=0; p<OCEAN_MAX-1; p++){
        key = p;
        for(i=p+1; i<OCEAN_MAX; i++){
            if(cmp_struct(&ocean_data[key], &ocean_data[i])==0){
                key = i;
            }
        }
        temp = ocean_data[p];
        ocean_data[p] = ocean_data[key];
        ocean_data[key] = temp;
        
    }
    /* print out the array of structs */
    for (i = 0; i < num_items; i++) {
        print_ocean_datum(&ocean_data[i]);
    }
    return EXIT_SUCCESS;
}
