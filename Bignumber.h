//20175204 김영범.  Advanced Application Programming 
#ifndef __PLUS__
#define __PLUS__

#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <time.h>

#define NEGATIVE 1
#define NON_NEGATIVE 0
#define TRUE 1
#define FALSE 0
#define EVEN 0
#define ODD 1
#define FST_IS_BIG 1 //!first is big for Compare function
#define BOTH_ARE_SAME 0//! both are same for Compare function
#define SCD_IS_BIG -1//! Second is big for Compare function
#define ERROR -0xeeeee //! Error
#define COUNT 2 //! Karatsuba depth

#define WORD_BITLEN 64

#if WORD_BITLEN == 8
typedef unsigned char word;
#elif WORD_BITLEN == 32
typedef unsigned int word; 
#else
typedef unsigned long long word;
#endif

typedef struct{ //! Big number struct
    int wordlen;
    int sign;
    word *a;
} bigint_st;

typedef bigint_st *bigint_st_ptr; //! typedef for bigint struct pointer

//! basic function
void delete_bigint(bigint_st_ptr *bi_X);
void set_bigint(bigint_st_ptr *bi_X, int sign, int wordlen, word *X);
void show(bigint_st *X);
void integer_copy(bigint_st_ptr *bi_dst,bigint_st_ptr *bi_src);
void set_one(bigint_st_ptr *bi_X);
void set_zero(bigint_st_ptr *bi_X);
unsigned char get_rand_8bits();
unsigned int get_rand_32bits();
unsigned long long get_rand_64bits();
word get_random_word();
void get_random_array(word dst[], int size);
void generate_random_integer(bigint_st_ptr *bi_X,int sign, int wordlen);
int get_sign(bigint_st_ptr *bi_X);
void flip_sign(bigint_st_ptr *bi_X);
void swap_integer(bigint_st_ptr *bi_X,bigint_st_ptr *bi_Y);
int get_word_length(bigint_st_ptr *bi_X);
int get_bit_length(bigint_st_ptr *bi_X);
int get_j_th_bit(bigint_st_ptr *bi_X, int j_th);
int is_zero(bigint_st_ptr *bi_X);
int is_one(bigint_st_ptr *bi_X);
int is_minus_one(bigint_st_ptr *bi_X);
int is_even_or_od(bigint_st_ptr *bi_X);
int Compare(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y);
void optimize(bigint_st_ptr *bi_X);
void Left_Shift(bigint_st_ptr *bi_X,int shift);
void Right_Shift(bigint_st_ptr *bi_X,int shift);
void Reduction(bigint_st_ptr *bi_X,int pwr_of_2);
//! Addition
void add_Core_carry(word src1, word src2, int *carry);
void add_Core(bigint_st_ptr *bi_X,bigint_st_ptr *bi_Y,bigint_st_ptr *bi_Z);
void Addition(bigint_st_ptr *bi_X,bigint_st_ptr *bi_Y,bigint_st_ptr *bi_Z);
//! Subtraction
int sub_Core_borrow(word a, word b);
void sub_Core(bigint_st_ptr *bi_X,bigint_st_ptr *bi_,bigint_st_ptr *bi_Z);
void Subtraction(bigint_st_ptr *bi_X,bigint_st_ptr *bi_Y,bigint_st_ptr *bi_Z);
//! Multiplication with Karatsuba
void Mul_Core_word(word A, word B,bigint_st_ptr *mul_word);
void Mul_Core(bigint_st_ptr *bi_X,bigint_st_ptr *bi_Y,bigint_st_ptr *bi_Z);
void Multiplication(bigint_st_ptr *bi_X,bigint_st_ptr *bi_Y,bigint_st_ptr *bi_Z);
void Wordlen_Add_Realloc(bigint_st_ptr *bi_X, int add_wordlen);
void Set_Same_Wordlen_Karatsuba(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y);
void Mul_Core_Krsb(bigint_st_ptr *bi_X,bigint_st_ptr *bi_Y, bigint_st_ptr *bi_Z,int *count);
void Multiplication_Karatsuba(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y, bigint_st_ptr *bi_Z,int *count);
//! Squaring function
void Squaring_Core_word(word A,bigint_st_ptr *squaring_word);
void Squaring_Core(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Z);
void Squaring(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Z);
void Squaring_Karatsuba(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Z,int *count);
//! Long_division_bit_version
void LongDivision_Bit(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y, bigint_st_ptr* bi_Q,bigint_st_ptr* bi_R);
 
#endif