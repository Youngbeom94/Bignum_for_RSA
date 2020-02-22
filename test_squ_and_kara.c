#include "Bignumber.h"

#if 1 //! Squaring 과 Karatsuba를 Verification 하는 함수
int main()
{
    int i = 1000;
    srand(time(NULL));
    while ((i >= 0))
    {
        int count = COUNT; //? Karatsuba depth
        bigint_st_ptr A = NULL;// 변수 생성
        bigint_st_ptr C = NULL;
        i--;
        generate_random_integer(&A, NON_NEGATIVE, 23);
        printf("a = ");
        show(A);

        // Squaring(&A,&C); //! Squaring 또는 밑에있는 카라추바 둘중에 하나 선택해서 확인을 할 수 있다.
        Squaring_Karatsuba(&A,&C,&count);
        printf("c = ");
        show(C);
        printf("\n");

        // printf("if  a * a == c :\n"); //* 생략가능.
        // printf("   print \"True\"\n");

        printf("if  a * a != c :\n");
        printf("   print hex(a)\n");
        printf("   print hex(c)\n");
        printf("   print hex(a*a)\n");
    
        delete_bigint(&A);// 메모리 동적할당 해제
        delete_bigint(&C);
    }
    return 0;
}
#endif
#if 0
//!performance test Squaring VS Karatsuba --> Squaring과  Karatsuba 성능을 체크해주는 함수 이다.
int main()
{
    clock_t start, end;
    double cpu_time_used1;
    double cpu_time_used2;

    int i =100; //? 총 몇번 계산할지에 대한 변수 값
    int size = 64;//? A의 wordlen size 
    int count = COUNT;
    //? 위의 세변수만 바꾸어주면 쉽게 연산량을 확인할 수 있음. 밑부분은 수정할 필요 없음.
    
    srand(time(NULL));
    int store_i = i;
    start = clock(); //*첫번쨰 측정시작.
    while ((i >= 0))  //! 첫번째 while문에서는 A B 변수를 generate하는 시간과, 해제하는 시간을 측정한다.
    {
        i--;
        bigint_st_ptr A = NULL;
        bigint_st_ptr C = NULL;
        generate_random_integer(&A, NON_NEGATIVE, size);
        delete_bigint(&A);
        delete_bigint(&C);
    }
    end = clock();//*첫번쨰 측정완료.
    cpu_time_used1 = ((double)(end - start)) / CLOCKS_PER_SEC;

    i = store_i;
    start = clock(); //*두번째 측정시작
     while ((i >= 0)) //! 두번째 while문에서는 A,B 변수를 generate하고 Multiplication을 통해 C를 구하는 시간, 그리고 해제하는 시간을 측정한다.
    {
        i--;
        bigint_st_ptr A = NULL;
        bigint_st_ptr C = NULL;
        generate_random_integer(&A, NON_NEGATIVE, size);
        Squaring(&A, &C);
        delete_bigint(&A);
        delete_bigint(&C);
    }
    end = clock();//*두번쨰 측정완료
    cpu_time_used2 = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nElapsed time with Squaring: %lf\n", cpu_time_used2 - cpu_time_used1);
    //! 두번째 구한 시간에서 첫번째 구한 시간을 뺴주게 되면, 근사적으로 Multiplication을 수행하는 시간을 구해줄 수 있다.

                                        //TODO 다음은 Karatsuba함수의 동작 시간을 측정하는 함수 이다.//

    i = store_i;
    start = clock(); //*첫번쨰 측정시작.
    while ((i >= 0))  //! 첫번째 while문에서는 A B 변수를 generate하는 시간과, 해제하는 시간을 측정한다.
    {
        i--;
        bigint_st_ptr A = NULL;
        bigint_st_ptr C = NULL;
        generate_random_integer(&A, NON_NEGATIVE, size);
        delete_bigint(&A);
        delete_bigint(&C);
    }
    end = clock();//*첫번쨰 측정완료.
    cpu_time_used1 = ((double)(end - start)) / CLOCKS_PER_SEC;

    i = store_i;
    start = clock(); //*두번째 측정시작
     while ((i >= 0)) //! 두번째 while문에서는 A,B 변수를 generate하고 Karatsuba 통해 C를 구하는 시간, 그리고 해제하는 시간을 측정한다.
    {
        i--;
        bigint_st_ptr A = NULL;
        bigint_st_ptr C = NULL;
        generate_random_integer(&A, NON_NEGATIVE, size);
        Squaring_Karatsuba(&A,&C,&count);
        delete_bigint(&A);
        delete_bigint(&C);
    }
    end = clock();//*두번쨰 측정완료
    cpu_time_used2 = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nElapsed time with Squaring_Karatsuba: %lf\n", cpu_time_used2 - cpu_time_used1);

    return 0;
}
#endif

