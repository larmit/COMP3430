//-----------------------------------------
// NAME		: Tianhao Wu
// STUDENT NUMBER	: 7794580
// COURSE		: COMP 3430
// INSTRUCTOR	: Franklin Bristow
// ASSIGNMENT	: assignment 1
// QUESTION	: question calculate Pi.
//
// REMARKS: main program for calculating Pi by thread.
//
//
//-----------------------------------------
// Created by larmititoth-OS on 2019-05-29.
//

#include "Pi_thread.h"


FILE *file;
int PRECISION,DIGIT;
mpz_t M,L,X,C,sum,result,Pi,base,tenBase;


void* subCalculate(void* currentK){
    int *temp=(int*)currentK;
    int i=*temp;

    char number[(DIGIT*3)];
    mpz_t temp_1, temp_2, temp_3;
    mpz_init_set_ui(temp_1, 1);
    mpz_init_set_ui(temp_2, 1);
    mpz_init_set_ui(temp_3, 1);

    mpz_fac_ui(temp_1, (6 * i));
    mpz_fac_ui(temp_2, (3 * i));
    mpz_fac_ui(temp_3, i);
    mpz_pow_ui(temp_3, temp_3, 3);

    mpz_mul(temp_2, temp_2, temp_3);
    mpz_div(temp_1, temp_1, temp_2);
    mpz_set_ui(M, 0);
    mpz_add(M, M, temp_1);

    //calculate for L
    mpz_init_set_ui(temp_2, 545140134);
    mpz_mul_ui(temp_2, temp_2, i);
    mpz_add_ui(temp_2, temp_2, 13591409);
    mpz_set_ui(L, 0);
    mpz_add(L, temp_2, L);

    //calculate for X
    mpz_init_set(temp_3, base);
    mpz_pow_ui(temp_3, temp_3, i);
    mpz_set_ui(X, 0);
    mpz_add(X, X, temp_3);

    //calculate for sum
    mpz_mul(M, M, L);
    mpz_mul(M, M, tenBase);
    mpz_div(sum, M, X);
    mpz_get_str(number,10,sum);

    fputs(number,file);
    fputs("\n",file);

    mpz_clear(temp_1);
    mpz_clear(temp_2);
    mpz_clear(temp_3);

    return NULL;
}


void threadPi(int k,int d){
    PRECISION=k;
    DIGIT=d;
    pthread_t thread;
    file=fopen("sum_Thread.txt","w+");
    mpz_init(M);
    mpz_init(tenBase);
    mpz_init(base);
    mpz_init(L);
    mpz_init(X);
    mpz_init(C);
    mpz_init(result);
    mpz_init(sum);
    mpz_init(Pi);
    mpz_init_set_str(base,"-262537412640768000",10);
    mpz_init_set_ui(tenBase, 10);
    //expand digits
    mpz_pow_ui(tenBase,tenBase,DIGIT);


    for (int i = 0; i < PRECISION; ++i) {
        int currentK=i;
        pthread_create(&thread,NULL,subCalculate,&currentK);

        pthread_join(thread,NULL);



        char numberStr[(DIGIT*3)];
        rewind(file);
        for (int j = 0; j <=i; ++j) {
            fgets(numberStr,(DIGIT*2),file);
        }
        mpz_set_ui(sum,0);
        mpz_set_str(sum,numberStr,10);
        mpz_add(result, sum, result);
    }

    mpz_init_set_ui(C,10005);
    mpz_mul(tenBase,tenBase,tenBase);
    mpz_mul(C,C,tenBase);
    mpz_mul(C,C,tenBase);
    mpz_sqrt(C,C);
    mpz_mul_ui(C,C,426880);

    //calculate for Pi
    mpz_div(Pi,C,result);
    gmp_printf("(Thread): The value of Pi is :\n %Zd\n",Pi);
    mpz_clear(X);
    mpz_clear(M);
    mpz_clear(L);
    mpz_clear(result);
    mpz_clear(sum);
    mpz_clear(C);
    mpz_clear(base);


    fclose(file);
}
