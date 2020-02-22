#include "Bignumber.h"

int main()
{

    word Input[56] = {0x8e, 0x3f, 0x44, 0x6d, 0x92, 0x34, 0xab, 0xcd, 0xff, 0xcd, 0x6b, 0x75, 0xac, 0xd2, 0x37, 0xf7, 0x1f, 0x92, 0x34, 0xab, 0xcd, 0xff, 0xcd, 0x6b, 0x75, 0xac, 0xd2, 0x37, 0xf7, 0x1f, 0x92, 0x34, 0xab, 0xcd, 0xff, 0xcd, 0x6b, 0x75, 0xac, 0xd2, 0x37, 0xf7, 0x1f, 0x92, 0x34, 0xab, 0xcd, 0xff, 0xcd, 0x6b, 0x75, 0xac, 0xd2, 0x37, 0xf7, 0x2f};
    word Input2[3] = {0x12, 0x34, 0x19};
    word Input3[3] = {0x12, 0x34, 0x13};
    word Input4[5] = {0xf2, 0x3d, 0xea, 0xf1, 0xd7};//! Set integer를 위한 input array

    bigint_st_ptr A = NULL;//! 변수 설정
    bigint_st_ptr B = NULL;
    bigint_st_ptr C = NULL;
    bigint_st_ptr D = NULL;
    bigint_st_ptr Q = NULL;
    bigint_st_ptr R = NULL;//! 변수 설정

    srand(time(NULL));
    int count = COUNT;//! Karatsuba를 위한 Depth 설정

    printf("[Set Integer]\n"); //? Set integer(Randomly)
    // set_bigint(&A, NON_NEGATIVE, 3, Input2);
    generate_random_integer(&A,NON_NEGATIVE,5);
    printf("A = ");
    show(A);

    // set_bigint(&B, NON_NEGATIVE, 3, Input3);
    generate_random_integer(&B, NON_NEGATIVE, 5);
    printf("B = ");
    show(B);

    // set_bigint(&C, NON_NEGATIVE, 56, Input);
    // generate_random_integer(&C, NON_NEGATIVE, 30);
    // show(C);

    // printf("\n[Integer Copy]\n"); //? Integer copy
    // integer_copy(&A, &B);
    // show(A);
    // show(B);

    // printf("\n[Set One]\n"); //? Set one
    // set_one(&A);
    // show(A);

    // printf("\n[Set Zero]\n");//? Set zero
    // set_zero(&A);
    // show(A);

    // printf("\n[Flip Sign]\n"); //? Flip sign
    // show(A);
    // flip_sign(&A);
    // show(A);

    // printf("\n[Swap integer]\n");//? Swap integer
    // swap_integer(&A, &B);
    // show(A);
    // show(B);

    // printf("\n[Get word length]\n");//? Get word length
    // printf("%d\n", get_word_length(&A));
    
    // printf("[Get bit length]\n");//? Get bit length
    // printf("%d\n", get_bit_length(&A));

    // printf("\n[Get j-th bit]\n");//? Get j-th bit
    // int cnt_i;
    // for (cnt_i = 0; cnt_i < get_bit_length(&A); cnt_i++)
    // {
    //     printf("%d", get_j_th_bit(&A, cnt_i));
    // }

    // printf("\n[Is Zero?]\n");//? Is zero?
    // if (is_zero(&A) == TRUE)
    //     printf("ZERO\n");
    // if (is_zero(&A) == FALSE)
    //     printf("NON_ZERO\n");

    // printf("\n[Is One?]\n");//? Is one?
    // if (is_one(&A) == TRUE)
    //     printf("ONE\n");
    // if (is_one(&A) == FALSE)
    //     printf("NOT_ONE\n");

    // printf("\n[Is Even or ODD?]\n");//? Is Even or Odd?
    // if (is_even_or_od(&A) == EVEN)
    //     printf("EVEN\n");
    // if (is_even_or_od(&A) == ODD)
    //     printf("ODD\n");

    // printf("\n[Compare]\n");//? Compare
    // if (Compare(&A, &B) == FST_IS_BIG)
    //     printf("Fist is big\n");
    // if (Compare(&A, &B) == SCD_IS_BIG)
    //     printf("Second is big\n");
    // if (Compare(&A, &B) == BOTH_ARE_SAME)
    //     printf("both are same\n");

    // printf("\n[Left shift]\n");//? Left shift
    // Left_Shift(&A, 1);
    // show(A);

    // printf("\n[Right shift]\n");//? Right shift
    // Right_Shift(&A, 16);
    // show(A);

    // printf("\n[Reduction]\n");//? Reduction
    // Reduction(&A, 57);
    // show(A);

    // printf("\n[ADD]\n");  //? ADDITION
    // Addition(&A, &B,&C);
    // show(C);

    // printf("\n[SUB]\n"); //? SUBTRACTION
    // Subtraction(&A, &B,&C);
    // show(C);

    // printf("\n[MUL]\n"); //? MULTIPLICATION
    // Multiplication(&A, &B, &C);
    // show(C);

    // printf("\n[MUL_Karatsuba]\n"); //?? MUL_KARATSUBA
    // Multiplication_Karatsuba(&A, &B, &C,&count);
    // show(C);

    //  printf("\n[Squaring]\n"); //? SQUARING
    // Squaring(&A,&C);
    // show(C);

    //  printf("\n[Squaring_Karatsuba]\n"); //? SQUARING_KARATSUBA
    // Squaring_Karatsuba(&A,&C,&count);
    // show(C);

    // printf("\n[Long_Division_Bit]\n"); //? LONG DIVISION
    // LongDivision_Bit(&A,&B,&Q,&R);
    // printf("q = ");
    // show(Q);
    // printf("r = ");
    // show(R);

    printf("\n[Free variable]\n");

    delete_bigint(&A);//! Free function 
    delete_bigint(&B);
    delete_bigint(&C);
    delete_bigint(&D);
    delete_bigint(&Q);
    delete_bigint(&R);

    return 0;
}