#include "Bignumber.h"
#if 1
int main() //! Longdivision 잘 작동되는지 확인하는 함수 (Verfication)
{
    int i = 100; // 몇번 확인할지 값 대입
    srand(time(NULL));
    while ((i >= 0))
    {
        bigint_st_ptr A = NULL; // 변수 생성
        bigint_st_ptr B = NULL;
        bigint_st_ptr Q = NULL;
        bigint_st_ptr R = NULL;
        i--;
        generate_random_integer(&A, NON_NEGATIVE, 128); // 임의의 숫자 생성 
        generate_random_integer(&B, NON_NEGATIVE, 64); // 임의의 숫자 생성 
        printf("a = ");
        show(A);
        printf("b = ");
        show(B);

        LongDivision_Bit(&A,&B,&Q,&R);

        printf("q = ");
        show(Q);
        printf("r = ");
        show(R);
        printf("\n");

        // 파이썬 문법으로 작성하였다. 컴파일 하면 파이썬에서 내가 확인하고 싶은 데이터들의 개수만큼.
        // 파이썬문법으로 조건문이 나온다.

        // printf("if  (b*q) + r == a :\n"); //* 생략가능
        // printf("   print \"True\"\n");

        printf("if (b*q) + r != a :\n");
        printf("   print hex(a)\n");
        printf("   print hex(b)\n");
        printf("   print hex(q)\n");
        printf("   print hex(a//b)\n");
        printf("   print hex(r)\n");
        printf("   print hex(a%%b)\n");
    
        delete_bigint(&A);//메모리 동적할당 해제
        delete_bigint(&B);
        delete_bigint(&Q);
        delete_bigint(&R);
    }
    return 0;
}
#endif
#if 0
//!performance test Long Division_Bit version --> Long Division_Bit version 성능을 체크해주는 함수 이다.
int main()
{
    clock_t start, end;
    double cpu_time_used1;
    double cpu_time_used2;

    int i =100; //? 총 몇번 계산할지에 대한 변수 값
    int size1 = 128;//? A의 wordlen size 
    int size2 = 64;//? B의 wordlen size 
    //? 위의 세변수만 바꾸어주면 쉽게 연산량을 확인할 수 있음.밑부분은 수정할 필요 없음.
    
    int store_i = i;
    srand(time(NULL));
    start = clock(); //*첫번쨰 측정시작.
    while ((i >= 0))  //! 첫번째 while문에서는 A B Q R 변수를 generate하는 시간과, 해제하는 시간을 측정한다.
    {
        i--;
        bigint_st_ptr A = NULL;
        bigint_st_ptr B = NULL;
        bigint_st_ptr Q = NULL;
        bigint_st_ptr R = NULL;
        generate_random_integer(&A, NON_NEGATIVE, size1);
        generate_random_integer(&B, NON_NEGATIVE, size2);
        delete_bigint(&A);
        delete_bigint(&B);
        delete_bigint(&Q);
        delete_bigint(&R);
    }
    end = clock();//*첫번쨰 측정완료.
    cpu_time_used1 = ((double)(end - start)) / CLOCKS_PER_SEC;

    i = store_i;
    start = clock(); //*두번째 측정시작
     while ((i >= 0)) 
    {//! 두번째 while문에서는 A,B 변수를 generate하고 Long division Bit version 통해 Q, R를 구하는 시간, 그리고 해제하는 시간을 측정한다.
        i--;
        bigint_st_ptr A = NULL;
        bigint_st_ptr B = NULL;
        bigint_st_ptr Q = NULL;
        bigint_st_ptr R = NULL;
        generate_random_integer(&A, NON_NEGATIVE, size1);
        generate_random_integer(&B, NON_NEGATIVE, size2);
        LongDivision_Bit(&A, &B, &Q,&R);
        delete_bigint(&A);
        delete_bigint(&B);
        delete_bigint(&Q);
        delete_bigint(&R);
    }
    end = clock();//*두번쨰 측정완료
    cpu_time_used2 = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nElapsed time with Long division_Bit version: %lf\n", cpu_time_used2 - cpu_time_used1);
    //! 두번째 구한 시간에서 첫번째 구한 시간을 뺴주게 되면, 근사적으로 Long division_ Bit Version 수행하는 시간을 구해줄 수 있다.
    return 0;
}
#endif

