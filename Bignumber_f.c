#include "Bignumber.h"

void delete_bigint(bigint_st_ptr *bi_X) //? 구조체에 할당된 메모리를 지우는 작업과 동시에, 초기화를 시켜줌.
{
   if (*bi_X == NULL)
      return;
   for (int j = 0; j < (*bi_X)->wordlen; j++)
   {
      (*bi_X)->a[j] = 0x0; //기존  구조체 메모리가 점유하는 부분의 값을 초기화
   }
   free((*bi_X)->a); //Big_int 구조체 멤버변수 a에 할당된 메모리 free
   free(*bi_X);      //Big_ing 구조체 포인터에 할당된 메모리 free
   *bi_X = NULL;
}

void set_bigint(bigint_st_ptr *bi_X, int sign, int wordlen, word *Input) //? Big_int 구조체에 값 설정해주는 함수
{
   if (*bi_X != NULL) //기존의 포인터값이 할당되어있을경우 해제
      delete_bigint(bi_X);

   *bi_X = (bigint_st *)calloc(1, sizeof(bigint_st));
   (*bi_X)->a = (word *)calloc(wordlen, sizeof(word));

   int cnt_i;
   for (cnt_i = 0; cnt_i < wordlen; cnt_i++)
   {
      (*bi_X)->a[cnt_i] = Input[cnt_i]; //Input된 배열의 값을 실질적으로 대입해줌
   }
   (*bi_X)->wordlen = wordlen;
   (*bi_X)->sign = sign;
}

void show(bigint_st *X)//? 숫자를 보여주는 함수
{
   int cnt_i;
   if (X->sign == NEGATIVE)
      printf("-"); //음수일경우 '-'표시

   printf("0x");
   for (cnt_i = X->wordlen - 1; cnt_i >= 0; cnt_i--)
   { 
#if WORD_BITLEN == 8
      printf("%02x", X->a[cnt_i]); // Wordbitlen = 8일 경우 즉 1byte가 1워드인경우

#elif WORD_BITLEN == 32
      printf("%08x", X->a[cnt_i]); // Wordbitlen = 32일 경우 즉 4byte가 1워드인경우
#else
      printf("%016llx", X->a[cnt_i]); // Wordbitlen = 64일 경우 즉 8byte가 1워드인경우
#endif
   }
   printf("\n");
}

void set_one(bigint_st_ptr *bi_X) //? big_num구조체에서 숫자 1을 만들어주는 함수
{
   if (*bi_X != NULL)
      delete_bigint(bi_X);

   (*bi_X) = (bigint_st *)calloc(1, sizeof(bigint_st));
   (*bi_X)->a = (word *)calloc(1, sizeof(word));
   (*bi_X)->a[0] = 0x1;
   (*bi_X)->wordlen = 1;
}

void set_zero(bigint_st_ptr *bi_X) //? big_num구조체에서 숫자 0을 만들어주는 함수
{
   if (*bi_X != NULL)
      delete_bigint(bi_X);

   (*bi_X) = (bigint_st *)calloc(1, sizeof(bigint_st));
   (*bi_X)->a = (word *)calloc(1, sizeof(word));
   (*bi_X)->a[0] = 0x0;
   (*bi_X)->wordlen = 1;
}

void integer_copy(bigint_st_ptr *bi_dst, bigint_st_ptr *bi_src) //? bigint_src를 bigint_dst에 복사하는 함수
{
   if (*bi_dst != NULL)
      delete_bigint(bi_dst);

   (*bi_dst) = (bigint_st *)calloc(1, sizeof(bigint_st));           //bigint_dst 포인터에 구조체 할당
   (*bi_dst)->a = (word *)calloc((*bi_src)->wordlen, sizeof(word)); //구조체 할당 후 구조체 멤버변수에 워드 할당
   for (int cnt_i = 0; cnt_i < (*bi_src)->wordlen; cnt_i++)
   {
      (*bi_dst)->a[cnt_i] = (*bi_src)->a[cnt_i]; // 할당된 워드에 복사할 값을 대입
   }
   (*bi_dst)->wordlen = (*bi_src)->wordlen; //src의 wordlen 맞춰주기
   (*bi_dst)->sign = (*bi_src)->sign;       //src의 sign 맞춰주기
}

unsigned char get_rand_8bits() //? 8bit의 랜덤 수 생성
{
   return rand() & 0xff; //? rand()함수 설정 후, 8bit 랜덤수 생성이므로 0xff와 &연산
}

unsigned int get_rand_32bits() //? 32bit의 랜덤 수 생성
{

   unsigned int temp = get_rand_8bits(); //8bit 랜덤수를 먼저 생성한다.
   temp = temp << 8;                     //8bit Left shifting 시킨다 총 16bit
   temp ^= get_rand_8bits();// 16bit에서 후 8bit는 0비트로 채워져있고 XoR연산과 get_rand_8bit를 이용해서 값을 채워준다.
   temp = temp << 8;
   temp ^= get_rand_8bits(); // 위와 같은 방식으로 만들어준다.
   temp = temp << 8;
   temp ^= get_rand_8bits();
   return temp; //return 값은 총 32비트의 랜덤 수 이다
}

unsigned long long get_rand_64bits() //64bit도 32bit와 동일하게 만들어준다.
{
   unsigned long long temp = get_rand_32bits(); // 32bit의 랜덤 수 생성
   temp = temp << 32;                           //32bit left shifting
   temp ^= get_rand_32bits();                   //총 64bit 랜덤 수 생성
   return temp;
}

#if WORD_BITLEN == 8
word get_random_word()
{
   return (word)get_rand_8bits();
}
#elif WORD_BITLEN == 32
word get_random_word()
{
   return (word)get_rand_32bits();
}
#else
word get_random_word()
{
   return (word)get_rand_64bits();
}

#endif

void get_random_array(word dst[], int size) //? Word의 배열과 , Wordlen(size)를 받을떄 랜덤값을 대입해 주는 함수
{
   int cnt_j = 0;
   for (cnt_j = 0; cnt_j < size; cnt_j++)
   {
      dst[cnt_j] = get_random_word(); //각각 배열의 원소에 랜덤 값 대입
   }
}

void generate_random_integer(bigint_st_ptr *bi_X, int sign, int wordlen) //? 랜덤한 숫자를 갖는 bigint 구조체 만들어 주는 함수
{ 
   if (*bi_X != NULL)
      delete_bigint(bi_X);

   int cnt_i;
   word *Input;// Word의 배열을 동적할당으로 만들어주고 배열에 랜덤값을 대입, 최종적으로 Set_bigint 함수의 input값을 맞춰줌
   Input = (word *)calloc(wordlen, sizeof(word)); // 배열 동적할당
   get_random_array(Input, wordlen);              // 기존에 만들어 놓았던 랜덤 함수를 이용 값을 대입시켜 줌.

   set_bigint(bi_X, sign, wordlen, Input);
   free(Input);    // 할당된 메모리를 Free
}

int get_sign(bigint_st_ptr *bi_X) //? Get_sign
{
   return (*bi_X)->sign;
}

void flip_sign(bigint_st_ptr *bi_X) //? flip_sign
{
   (*bi_X)->sign = (*bi_X)->sign ^ 1;
}

void swap_integer(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y) //? Swap_integer
{
   bigint_st_ptr temp = NULL; //Swap함수도 기존 정수 Swap함수와 마찬가지로 포인터를 만들어줘서 Swap 해주면 된다,\.
   temp = (bigint_st_ptr)calloc(1, sizeof(bigint_st));

   temp = *bi_X;
   *bi_X = *bi_Y;
   *bi_Y = temp;
}

int get_word_length(bigint_st_ptr *bi_X) //? get_word_length
{
   return (*bi_X)->wordlen;
}
int get_bit_length(bigint_st_ptr *bi_X) //? get_bit_length.
{
   int temp = ((*bi_X)->wordlen)  * WORD_BITLEN;// 먼저 WordBitlen에 input data의 wordlen 만큼 구해준다.
   int cnt_i, count = 0;// for loop를 위한 cnt_i 변수, bi_X의 마지막배열에서 정확한 비트길이를 계산하기 위한 count 변수

   for(cnt_i = WORD_BITLEN; (cnt_i>=0) && (((*bi_X)->a[(*bi_X)->wordlen - 1] >> (cnt_i - 1) ) == 0) ; cnt_i --  )
      {
         count ++; // 만약 shifting 결과가 0이라면 count++; 최상위 비트부터 0의 개수를 확인, 1의 나오기 전까지
      }
   return temp - count; // 두 값을 빼주면 된다.
}
int get_j_th_bit(bigint_st_ptr *bi_X, int j_th) //? get_j th bit
{
   if (j_th >= WORD_BITLEN)
      return (((*bi_X)->a[j_th / WORD_BITLEN] >> (j_th % WORD_BITLEN)) & 1); //Wordbitlen 단위이기때문에, 이를 근거로 j 번째 비트를 찾는다.

   return (((*bi_X)->a[0] >> j_th) & 1);
}

int is_zero(bigint_st_ptr *bi_X) //? 0인지 판별하는 함수
{
   optimize(bi_X); //optimize Bi_X
   if ((*bi_X)->wordlen == 1 && (*bi_X)->a[0] == 0)
      return TRUE;

   return FALSE;
}
int is_one(bigint_st_ptr *bi_X) //? 1인지 판별하는 함수
{
   optimize(bi_X); //optimize bi_X
   if (((*bi_X)->wordlen == 1) && ((*bi_X)->a[0] == 1) && (*bi_X)->sign == NON_NEGATIVE)
      return TRUE;

   return FALSE;
}

int is_minus_one(bigint_st_ptr *bi_X)
{
   if (((*bi_X)->wordlen == 1) && ((*bi_X)->a[0] == 1) && (*bi_X)->sign == NEGATIVE) //? -1인지 판별하는 함수
      return TRUE;

   return FALSE;
}

int is_even_or_od(bigint_st_ptr *bi_X) //?홀수인지 짝수인지 판별하는 함수
{
   if (((*bi_X)->a[0] & 0x1) == 0)
      return EVEN;

   return ODD;
}

int Compare(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y) //? bi_X,bi_Y의 크기를  비교해주는 함수
{
   if ((*bi_X)->sign == NON_NEGATIVE && (*bi_Y)->sign == NEGATIVE)
      return FST_IS_BIG; // bi_X는 양수, bi_Y는 음수일 경우 반환은 First is Big
   if ((*bi_X)->sign == NEGATIVE && (*bi_Y)->sign == NON_NEGATIVE)
      return SCD_IS_BIG;                                               // 반대일 경우, 반환은 Second is big
   if ((*bi_X)->sign == NON_NEGATIVE && (*bi_Y)->sign == NON_NEGATIVE) // 비교하려는 두수의 부호가 동일한 경우
   {
      if ((*bi_X)->wordlen > ((*bi_Y)->wordlen))
         return FST_IS_BIG; // Wordlen 비교
      if ((*bi_X)->wordlen < ((*bi_Y)->wordlen))
         return SCD_IS_BIG; // Wordlen 비교
      int cnt_i;
      for (cnt_i = (*bi_X)->wordlen - 1; cnt_i >= 0; cnt_i--)
      {
         if ((*bi_X)->a[cnt_i] > (*bi_Y)->a[cnt_i]) // 두수의 wordlen이 같을때 배열의 각 word를 비교하기
            return FST_IS_BIG;                      // First is big (bi_X>bi_Y)
         if ((*bi_X)->a[cnt_i] < (*bi_Y)->a[cnt_i])
            return SCD_IS_BIG; // Second is big
      }
      return BOTH_ARE_SAME; // 만약 해당하는것이 아무것도 없는경우 두수는 같다고 표현
   }
   if ((*bi_X)->sign == NEGATIVE && (*bi_Y)->sign == NEGATIVE) // 바로 위의 if Condition과 같은 논리이다.
   {
      if ((*bi_X)->wordlen > ((*bi_Y)->wordlen))
         return SCD_IS_BIG;
      if ((*bi_X)->wordlen < ((*bi_Y)->wordlen))
         return FST_IS_BIG;
      int cnt_i;
      for (cnt_i = (*bi_X)->wordlen - 1; cnt_i >= 0; cnt_i--)
      {
         if ((*bi_X)->a[cnt_i] > (*bi_Y)->a[cnt_i])
            return SCD_IS_BIG;
         if ((*bi_X)->a[cnt_i] < (*bi_Y)->a[cnt_i])
            return FST_IS_BIG;
      }
      return BOTH_ARE_SAME;
   }

   return ERROR;
}

void optimize(bigint_st_ptr *bi_X) //? optimize function ; 배열의 끝부분에 0이 있을경우 없애주는 함수.
{
   int cnt_i = (*bi_X)->wordlen - 1; //변수 설정
   int zero_cnt = 0;                 // 배열의 끝부분부터 연속적으로 0이 존재하는 word Counting
   while ((*bi_X)->a[cnt_i] == 0 && cnt_i >= 0)
   {
      zero_cnt += 1;
      cnt_i--;
   }
   if (zero_cnt == (*bi_X)->wordlen) // 만약 zero_count가 wordlen이랑 같으면 0이므로 set_zero
   {
      set_zero(bi_X);
   }

#if WORD_BITLEN == 8
      else
   {
      (*bi_X)->a = (word *)realloc((*bi_X)->a, ((*bi_X)->wordlen) - zero_cnt); // 아닌경우 메모리 relloc을 해준다.
      (*bi_X)->wordlen -= zero_cnt;
   }

#elif WORD_BITLEN == 32
      else
   {
      (*bi_X)->a = (word *)realloc((*bi_X)->a, (((*bi_X)->wordlen) - zero_cnt)*4); // 아닌경우 메모리 relloc을 해준다.
      (*bi_X)->wordlen -= zero_cnt;
   }
#else
      else
   {
      (*bi_X)->a = (word *)realloc((*bi_X)->a, (((*bi_X)->wordlen) - zero_cnt)*8); // 아닌경우 메모리 relloc을 해준다.
      (*bi_X)->wordlen -= zero_cnt;
   }
#endif   
}

void Left_Shift(bigint_st_ptr *bi_X, int shift) //? Leftshifting 쉬프팅 값은 정수로 받는다.
{
   int cnt_i;
   if (shift % WORD_BITLEN == 0) // wordbit단위로 나뉘어 질때, 단순히 배열크기만 늘리고, 값 이동시켜주면됨
   { // (shift % WORD_BITLEN(=8) == 0)
#if WORD_BITLEN == 8
      (*bi_X)->a = (word *)realloc((*bi_X)->a, ((*bi_X)->wordlen) + (shift / WORD_BITLEN)); // 배열의 크기를 늘리는 realloc
#elif WORD_BITLEN == 32
      (*bi_X)->a = (word *)realloc((*bi_X)->a, 4 * (((*bi_X)->wordlen) + (shift / WORD_BITLEN))); // 배열의 크기를 늘리는 realloc
#else
      (*bi_X)->a = (word *)realloc((*bi_X)->a, 8 * (((*bi_X)->wordlen) + (shift / WORD_BITLEN))); // 배열의 크기를 늘리는 realloc
#endif
      (*bi_X)->wordlen += shift / WORD_BITLEN;                                              //wordlen 수정
      for (cnt_i = ((*bi_X)->wordlen) - (shift / WORD_BITLEN) - 1; cnt_i >= 0; cnt_i--)     // 추가된만큼 배열 이동
      {
         (*bi_X)->a[cnt_i + (shift / WORD_BITLEN)] = (*bi_X)->a[cnt_i];
      }
      for (cnt_i = 0; cnt_i < (shift / WORD_BITLEN); cnt_i++) //추가된 배열 이동후 남는공간에 0x00 대입
      {
         (*bi_X)->a[cnt_i] = 0x00;
      }
   }
   else // (shift % WORD_BITLEN(=8) != 0) 이경우 몫과 나머지로 나누어서 생각해줘야함
   {
#if WORD_BITLEN == 8
      (*bi_X)->a = (word *)realloc((*bi_X)->a, ((*bi_X)->wordlen) + (shift / WORD_BITLEN) + 1); //몫에 해당하는 부분을 realloc
#elif WORD_BITLEN == 32
     (*bi_X)->a = (word *)realloc((*bi_X)->a, 4 * (((*bi_X)->wordlen) + (shift / WORD_BITLEN) + 1)); //몫에 해당하는 부분을 realloc
#else
     (*bi_X)->a = (word *)realloc((*bi_X)->a, 8 * (((*bi_X)->wordlen) + (shift / WORD_BITLEN) + 1)); //몫에 해당하는 부분을 realloc
#endif
      (*bi_X)->wordlen += shift / WORD_BITLEN + 1;
      for (cnt_i = (*bi_X)->wordlen - 2; cnt_i > (shift / WORD_BITLEN) - 1; cnt_i--)
      {
         (*bi_X)->a[cnt_i] = (*bi_X)->a[cnt_i - (shift / WORD_BITLEN)];
      }
      for (cnt_i = 0; cnt_i < shift / WORD_BITLEN; cnt_i++) //두개의 loop은 나머지만큼의 비트시프팅과 &,| 연산을 통해 값을 맞춰주는 함수 이다.
      {
         (*bi_X)->a[cnt_i] = 0x0;
      }
      (*bi_X)->a[(*bi_X)->wordlen - 1] = (*bi_X)->a[(*bi_X)->wordlen - 2] >> (WORD_BITLEN - shift % WORD_BITLEN);
      for (cnt_i = (*bi_X)->wordlen - 2; cnt_i > shift / WORD_BITLEN; cnt_i--)
      {
         (*bi_X)->a[cnt_i] = ((*bi_X)->a[cnt_i] << (shift % WORD_BITLEN)) | ((*bi_X)->a[cnt_i - 1] >> (WORD_BITLEN - shift % WORD_BITLEN));
      }
      (*bi_X)->a[shift / WORD_BITLEN] = (*bi_X)->a[shift / WORD_BITLEN] << (shift % WORD_BITLEN);

      if ((*bi_X)->a[(*bi_X)->wordlen - 1] == 0x0) //마지막배열이 0x00인경우 Optimize;
      {
#if WORD_BITLEN == 8
         (*bi_X)->a = (word *)realloc((*bi_X)->a, ((*bi_X)->wordlen) + (shift / WORD_BITLEN));
         (*bi_X)->wordlen -= 1;
#elif WORD_BITLEN == 32
          (*bi_X)->a = (word *)realloc((*bi_X)->a, 4*(((*bi_X)->wordlen) + (shift / WORD_BITLEN)));
         (*bi_X)->wordlen -= 1;
#else 
          (*bi_X)->a = (word *)realloc((*bi_X)->a, 8*(((*bi_X)->wordlen) + (shift / WORD_BITLEN)));
         (*bi_X)->wordlen -= 1;
#endif
      }
   }
}
void Right_Shift(bigint_st_ptr *bi_X, int shift) //? Right shifting 쉬프팅 값은 정수로 받는다.
{
   int cnt_i;
   if (shift % WORD_BITLEN == 0) //Left shifting과 동일한 방법으로 배열단위로 움직인다.
   {
      for (cnt_i = 0; cnt_i < (*bi_X)->wordlen - shift / WORD_BITLEN; cnt_i++)
      {
         (*bi_X)->a[cnt_i] = (*bi_X)->a[cnt_i + (shift / WORD_BITLEN)]; //배열의 이동
      }
      for (cnt_i = (*bi_X)->wordlen - shift / WORD_BITLEN; cnt_i < (*bi_X)->wordlen; cnt_i++) //이동후 남는 뒷자리 부분에 0채워넣어주기
      {
         (*bi_X)->a[cnt_i] = 0x0;
      }
      optimize(bi_X); // optimize를 해줘야한다.
   }
   else // (shift % WORD_BITLEN(=8) != 0), Left shifting 과 동일한 방법으로 해주면 된다.
   {
      for (cnt_i = 0; cnt_i < (*bi_X)->wordlen - shift / WORD_BITLEN; cnt_i++)
      {
         (*bi_X)->a[cnt_i] = (*bi_X)->a[cnt_i + (shift / WORD_BITLEN)]; //realloc 없이 바로 값을 대입해준다.
      }
      for (cnt_i = (*bi_X)->wordlen - shift / WORD_BITLEN; cnt_i < (*bi_X)->wordlen; cnt_i++)
      {
         (*bi_X)->a[cnt_i] = 0x0; // 남은 부분은 0x00대입
      }
      for (cnt_i = 0; cnt_i < (*bi_X)->wordlen - shift / WORD_BITLEN - 1; cnt_i++) // WORDBITLEN의 배수가 아닌경우 이므로, 각각의 배열마다 shifting을 통해 값을 맞춰준다.
      {
         (*bi_X)->a[cnt_i] = (((*bi_X)->a[cnt_i] >> (shift % WORD_BITLEN)) | ((*bi_X)->a[cnt_i + 1] << (WORD_BITLEN - (shift % WORD_BITLEN))));
      }
      (*bi_X)->a[(*bi_X)->wordlen - (shift / WORD_BITLEN) - 1] = (*bi_X)->a[(*bi_X)->wordlen - (shift / WORD_BITLEN) - 1] >> ((shift % WORD_BITLEN));

      optimize(bi_X);
   }
}

void Reduction(bigint_st_ptr *bi_X, int pwr_of_2)//? Reduction 나머지를 만드는 함수. input data는 power of 2이다.
{
   if (pwr_of_2 > get_bit_length(bi_X)) //Trivial
      return;
   if (pwr_of_2 % WORD_BITLEN == 0 && pwr_of_2 < get_bit_length(bi_X)) 
   {
#if WORD_BITLEN == 8
      (*bi_X)->a = (word *)realloc((*bi_X)->a, pwr_of_2 / WORD_BITLEN);
#elif WORD_BITLEN == 32
      (*bi_X)->a = (word *)realloc((*bi_X)->a, 4*(pwr_of_2 / WORD_BITLEN));
#else
      (*bi_X)->a = (word *)realloc((*bi_X)->a, 8*(pwr_of_2 / WORD_BITLEN));
#endif
      (*bi_X)->wordlen = pwr_of_2 / WORD_BITLEN;
      return; //그리고 리턴. 끝
   } // 그외의경우 즉, input_data가 WORDBITLEN의 배수가 아닌경우, realloc을 해주고, 남은 나머지 비트만큼을 &연산을 통하여, 맞춰준다.
   (*bi_X)->a[(pwr_of_2 / WORD_BITLEN)] = (*bi_X)->a[(pwr_of_2 / WORD_BITLEN)] & (0xff >> (WORD_BITLEN - (pwr_of_2 % WORD_BITLEN)));
#if WORD_BITLEN == 8
   (*bi_X)->a = (word *)realloc((*bi_X)->a, (pwr_of_2 / WORD_BITLEN) + 1);
#elif WORD_BITLEN ==32
   (*bi_X)->a = (word *)realloc((*bi_X)->a, 4*((pwr_of_2 / WORD_BITLEN) + 1));
#else
   (*bi_X)->a = (word *)realloc((*bi_X)->a, 8*((pwr_of_2 / WORD_BITLEN) + 1));
#endif
   (*bi_X)->wordlen = (pwr_of_2 / WORD_BITLEN) + 1;
   return;
}

void add_Core_carry(word src1, word src2, int *carry) //? Addition의 carry를 계산해 주는 함수.
{
   if (src1 > src2) // carry가 발생하지 않는 경우
      *carry = 0;
   if (src1 < src2) // carry가 발생하는 경우
      *carry = 1;
}

void add_Core(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y, bigint_st_ptr *bi_Z)//? 실질적 Addition 함수의 Core이다
{                                                               // 이함수는 bi_X >= bi_Y >=0임을 가정하고 만든 함수이다.
   delete_bigint(bi_Z);                                         // 초기에 bi_Z값이 할당되어있을 수있기 때문에, delete 해준다.
   *bi_Z = (bigint_st_ptr)calloc(1, sizeof(bigint_st));         // 그후에 bi_Z값을 할당해준다.
   (*bi_Z)->wordlen = (*bi_X)->wordlen + 1;                     // 덧셈결과는 Bi_X +1 (최대), 마지막에 optimize 해줄것이다.
   (*bi_Z)->a = (word *)calloc((*bi_Z)->wordlen, sizeof(word)); //wordlen 만큼 word배열 생성
   (*bi_Z)->sign = NON_NEGATIVE;                                //가정에 의해 양수

   int cnt_i;     //for loop counting variable
   int carry = 0; // Carry

   for (cnt_i = 0; cnt_i < get_word_length(bi_Y); cnt_i++) // bi_Y가 wordlen이 더 작으므로 bi_Y까지 bi_X와 bi_Y를 더해주면서, Carry계산도 해준다.
   {
      (*bi_Z)->a[cnt_i] = (*bi_X)->a[cnt_i] + (*bi_Y)->a[cnt_i] + carry; // 단순 덧셈. modulo는 자동적으로 작동
      add_Core_carry((*bi_Z)->a[cnt_i], (*bi_X)->a[cnt_i], &carry);      // 계산된 bi_Z값에 carry값을 더해주는 함수. 위에 구현되어있다.
   }
   for (cnt_i = get_word_length(bi_Y); cnt_i < get_word_length(bi_X); cnt_i++)
   {                                                                //가정이 bi_X >= bi_Y이므로 bi_X가 bi_Y 보다 가지는 추가부분을 덧셈해줘야한다
      (*bi_Z)->a[cnt_i] = (*bi_X)->a[cnt_i] + carry;                //추가부분은 bi_Y배열의 값이 0이므로 그냥 carry만 계산해주면된다.
      add_Core_carry((*bi_Z)->a[cnt_i], (*bi_X)->a[cnt_i], &carry); //carry값은 계속 계산해줘야한다. 999999+1인경우 carry값은 계속올라가기 떄문이다.
   }
   (*bi_Z)->a[get_word_length(bi_X)] = carry; // 마지막 배열의 값은 carry값이므로 그대로 대입해준다.
   optimize(bi_Z);
}

void Addition(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y, bigint_st_ptr *bi_Z)//? Addition Core를 바탕으로 만들어진 최종 Addition 함수.
 //addcore을 바탕으로 Addition함수를 만들었다.
//addcore은 인풋데이터가 bi_X>=bi_Y>=0인 가정을 바탕으로 만들어주었기 때문에,무작위 데이터에 관하여, addcore func의 input 값을 맞춰준다.
//항상 Addition을 호출할때, bi_Z에 관하여 delete를 해준다.(초기화)
{                                                                          
   delete_bigint(bi_Z);                                        
   if (is_zero(bi_X) == TRUE) //Trivial
   {
      integer_copy(bi_Z, bi_Y);
      return;
   }
   if (is_zero(bi_Y) == TRUE) //Trivial
   {
      integer_copy(bi_Z, bi_X);
      return;
   }
   if (get_sign(bi_X) == NON_NEGATIVE && get_sign(bi_Y) == NEGATIVE) //부호가 다른경우, 실제 덧셈은 뺄셈이다.
   {
      flip_sign(bi_Y);
      Subtraction(bi_X, bi_Y, bi_Z);
      flip_sign(bi_Y);
      return;
   }
   if (get_sign(bi_X) == NEGATIVE && get_sign(bi_Y) == NON_NEGATIVE) // 부호가 다른경우 실제 덧셈은 뺼셈이다.
   {
      flip_sign(bi_X);
      Subtraction(bi_Y, bi_X, bi_Z);
      flip_sign(bi_X);
      return;
   }
   if ((get_sign(bi_X) == get_sign(bi_Y)) && (Compare(bi_X, bi_Y) == FST_IS_BIG || Compare(bi_X, bi_Y) == BOTH_ARE_SAME))
   {
      add_Core(bi_X, bi_Y, bi_Z);
      return;
   }
   if ((get_sign(bi_X) == get_sign(bi_Y)) && (Compare(bi_X, bi_Y) == SCD_IS_BIG)) //bi_Y가 더 큰경우는 역으로 함수에 들어가면된다.
   {
      add_Core(bi_Y, bi_X, bi_Z);
      return;
   }
}

int sub_Core_borrow(word a, word b) //? Addition에서는 carry, Subtraction에서는 borrow.  borrow를 생각해주는 함수이다.
{
   if (a >= b)
      return 0;

   return 1;
}

void sub_Core(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y, bigint_st_ptr *bi_Z)//? Subtraction_Core function이다.
{                                              //아울리 이함수도 add_core과 마찬가지로 bi_X >= bi_Y >= 0임을 가정하였다.
   delete_bigint(bi_Z);                                              // 초기화
   *bi_Z = (bigint_st_ptr)calloc(1, sizeof(bigint_st));              //구조체 할당
   (*bi_Z)->a = (word *)calloc(get_word_length(bi_X), sizeof(word)); //구조체 배열할당. 구조체의 wordlen은 뺄셈이므로 bi_X와 동일하다.
   (*bi_Z)->sign = NON_NEGATIVE;                                     // 가정에 의하여 양수이다.
   (*bi_Z)->wordlen = get_word_length(bi_X);                         // 가정에 의하여 bi_Z가 가질수 있는 최대 wordlen은 bi_X

   int borrow = 0;
   int cnt_i = 0;
   for (cnt_i = 0; cnt_i < get_word_length(bi_Y); cnt_i++) //bi_Y의 wordlen까지 뺼셈을 해준다. 루프안의 각각경우마다 두번의 뺄셈이들어간다.
   {                                                       //1번째 뺄셈은 bi_X와 borrow값, 2번쨰 뺄셈은 1번쨰 뺼셈의 결과와 bi_Y.
      (*bi_Z)->a[cnt_i] = (*bi_X)->a[cnt_i] - borrow;
      borrow = sub_Core_borrow((*bi_X)->a[cnt_i], borrow); //borrow는 연속적으로 계산을 해줘야한다.
      borrow += sub_Core_borrow((*bi_Z)->a[cnt_i], (*bi_Y)->a[cnt_i]);
      (*bi_Z)->a[cnt_i] = (*bi_Z)->a[cnt_i] - (*bi_Y)->a[cnt_i];
   }
   for (cnt_i = get_word_length(bi_Y); cnt_i < get_word_length(bi_X); cnt_i++) 
   {                                   //가정에 의하여 bi_X 배열중 bi_Y의 배열과 대응안되는것이 있을 수 있다. 그 경우 borrow를 생각해주면서 뺴자.
      (*bi_Z)->a[cnt_i] = (*bi_X)->a[cnt_i] - borrow;             //덧셈과 마찬가지로 100000-1인경우를 생각해야한다. (borrow 유지)
      borrow = sub_Core_borrow((*bi_X)->a[cnt_i], borrow);
   }
   optimize(bi_Z); // optimize함수는 필수이다.
}

void Subtraction(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y, bigint_st_ptr *bi_Z)
{                             //? Addition과 마찬가지로, sub_core함수의 input data들을 맞춰주는 함수이다. 즉 bi_X >= bi_Y >=0이 되도록
   if (is_zero(bi_X) == TRUE) //Trivial
   {
      integer_copy(bi_Z, bi_Y);
      flip_sign(bi_Z);
      return;
   }
   if (is_zero(bi_Y) == TRUE) //Trivial
   {
      integer_copy(bi_Z, bi_X);
      return;
   }
   if (get_sign(bi_X) == NON_NEGATIVE && get_sign(bi_Y) == NON_NEGATIVE && (Compare(bi_X, bi_Y) == FST_IS_BIG || Compare(bi_X, bi_Y) == BOTH_ARE_SAME))
   {
      sub_Core(bi_X, bi_Y, bi_Z);
      return;
   }
   if (get_sign(bi_X) == NON_NEGATIVE && get_sign(bi_Y) == NON_NEGATIVE && Compare(bi_X, bi_Y) == SCD_IS_BIG) //flip해주면 된다.물론 sign도
   {
      sub_Core(bi_Y, bi_X, bi_Z);
      flip_sign(bi_Z);
      return;
   }
   if (get_sign(bi_X) == NEGATIVE && get_sign(bi_Y) == NEGATIVE && (Compare(bi_X, bi_Y) == FST_IS_BIG || Compare(bi_X, bi_Y) == BOTH_ARE_SAME))
   { //둘다 음수 일경우는 크기를 따져 보아야 한다.
      flip_sign(bi_X);
      flip_sign(bi_Y);
      sub_Core(bi_Y, bi_X, bi_Z);
      flip_sign(bi_X);
      flip_sign(bi_Y);
      return;
   }
   if (get_sign(bi_X) == NEGATIVE && get_sign(bi_Y) == NEGATIVE && Compare(bi_X, bi_Y) == SCD_IS_BIG)
   { //위 함수와마찬가지로 해준다.
      flip_sign(bi_X);
      flip_sign(bi_Y);
      sub_Core(bi_X, bi_Y, bi_Z);
      flip_sign(bi_X);
      flip_sign(bi_Y);
      flip_sign(bi_Z);
      return;
   }
   if (get_sign(bi_X) == NON_NEGATIVE && get_sign(bi_Y) == NEGATIVE)
   { // 실질적으로 덧셈이 발생하는 경우
      flip_sign(bi_Y);
      Addition(bi_X, bi_Y, bi_Z);
      flip_sign(bi_Y);
      return;
   }
   if (get_sign(bi_X) == NEGATIVE && get_sign(bi_Y) == NON_NEGATIVE)
   { //실질적으로 덧셈이 발생하는 경우이고 마지막에 부호만 바꾸어주면된다.
      flip_sign(bi_X);
      Addition(bi_X, bi_Y, bi_Z);
      flip_sign(bi_X);
      flip_sign(bi_Z);
      return;
   }
}

void Mul_Core_word(word A, word B, bigint_st_ptr *Mul_word) //? 단일 word A, B에 관하여 곱셈을 해주는 함수이다.
{
   bigint_st_ptr T1 = NULL; //변수 생성 : A1 * B1, A0 *B0를 저장해주는 변수
   bigint_st_ptr T2 = NULL; //변수 생성 : A1 * B0를 저장해주는 변수
   bigint_st_ptr T3 = NULL; //변수 생성 : A0 * B1를 저장해주는 변수
   set_zero(&T1);
   set_zero(&T2);
   set_zero(&T3);

   T1->a = (word *)realloc(T1->a, 2 * (sizeof(word))); //T1,T2,T3전부 2Word이므로 그에 맞게 할당 , T2,T3는 뒤에서 Leftshift로 해줌.
   T1->wordlen = 2;
   T1->a[1] = (A >> (WORD_BITLEN / 2)) * (B >> (WORD_BITLEN / 2)); //T->a1[1]에는 A1*B1

   T1->a[0] = (A & ((1LL << (WORD_BITLEN / 2)) - 1)) * (B & ((1LL << (WORD_BITLEN / 2)) - 1)); //T->a1[0]에는 A0*B0
   T2->a[0] = ((B & ((1LL << (WORD_BITLEN / 2)) - 1)) * (A >> (WORD_BITLEN / 2)));
   //T2->a[0]에 A1 * B0를 저장해주고 뒤에서 Leftshift를 해줘서 2word를 맞춰준다.
   T3->a[0] = ((A & ((1LL << (WORD_BITLEN / 2)) - 1)) * (B >> (WORD_BITLEN / 2)));
   //T3->a[0]에 A0 * B1를 저장해주고 뒤에서 Leftshift를 해줘서 2word를 맞춰준다.

   Left_Shift(&T2, WORD_BITLEN / 2); // 2Word 맞춰주기
   Left_Shift(&T3, WORD_BITLEN / 2);
   bigint_st_ptr Temp = NULL; // Addition 함수를 호출하기 위한 저장값
   set_zero(&Temp);

   Addition(&T1, &T2, &Temp); //T1,T2,T3를 전부 더해준다.
   Addition(&Temp, &T3, Mul_word);
   delete_bigint(&T1);
   delete_bigint(&T2);
   delete_bigint(&T3);
   delete_bigint(&Temp);
}
void Mul_Core(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y, bigint_st_ptr *bi_Z)//? Word들로 이루워진 두 bigint구조체의 곱셈이다.
{
   delete_bigint(bi_Z); //bi_Z초기화 후 구조체 0으로 만든다.
   set_zero(bi_Z);
   if ((*bi_X)->sign != (*bi_Y)->sign) //set_zero함수는 기본적으로 NON_NEGATIVE, 만약 input_data가 서로 부호가 다르면 NEGATIVE.
      (*bi_Z)->sign = NEGATIVE;

   int cnt_i, cnt_j = 0;
   bigint_st_ptr Temp = NULL;     // Addition 호출을 위한 저장값
   bigint_st_ptr Mul_word = NULL; // 위와같음
   for (cnt_i = 0; cnt_i < get_word_length(bi_X); cnt_i++)
   {
      for (cnt_j = 0; cnt_j < get_word_length(bi_Y); cnt_j++)
      {
         Mul_Core_word((*bi_X)->a[cnt_i], (*bi_Y)->a[cnt_j], &Mul_word); //각 자리 곱샘을 Mul_word에 저장시킨다.
         Left_Shift(&Mul_word, WORD_BITLEN * (cnt_i + cnt_j));           // 그 후 Mul_word를 Shifting한다. 워드길이 * (i+j)만큼
         Addition(bi_Z, &Mul_word, &Temp);                               //그후 bi_Z <- bi_Z + Mulword를 해준다.
         integer_copy(bi_Z, &Temp);                                      //위와 같음
      }
   }
   delete_bigint(&Temp);     //메모리 동적할당 Free
   delete_bigint(&Mul_word); //메모리 동적할당 Free
   optimize(bi_Z);           //Optimize
}

void Multiplication(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y, bigint_st_ptr *bi_Z)//? Mul_Core를 바탕으로 곱셈해주는 함수.
{
   delete_bigint(bi_Z);
   if (is_zero(bi_X) == TRUE || is_zero(bi_Y) == TRUE) //Trivial
   {
      set_zero(bi_Z);
      return;
   }
   if (is_one(bi_X) == TRUE) //Trivial
   {
      integer_copy(bi_Z, bi_Y);
      return;
   }
   if (is_one(bi_Y) == TRUE) //Trivial
   {
      integer_copy(bi_Z, bi_X);
      return;
   }
   if (is_minus_one(bi_X) == TRUE) //Trivial
   {
      integer_copy(bi_Z, bi_Y);
      flip_sign(bi_Z);
      return;
   }
   if (is_minus_one(bi_Y) == TRUE) //Trivial
   {
      integer_copy(bi_Z, bi_X);
      flip_sign(bi_Z);
      return;
   }
   Mul_Core(bi_X, bi_Y, bi_Z); // input_data가 1 or -1 or 0 이 아닐때에는 Mul_Core를 해준다.
}

void Wordlen_Add_Realloc(bigint_st_ptr *bi_X, int add_wordlen) //? (*bi_X)->a에서 워드길이를 늘이고 싶을때 사용하는 함수. 물론 추가로 늘려진 공간은 0값 대입.
{
   int cnt_i;
#if WORD_BITLEN == 8
   (*bi_X)->a = (word *)realloc((*bi_X)->a, (*bi_X)->wordlen + add_wordlen);       // input add_wordlen만큼 추가로 realloc을 해준다.
   for (cnt_i = (*bi_X)->wordlen; cnt_i < (*bi_X)->wordlen + add_wordlen; cnt_i++) // 추가로 realloc된 공간에 0x00대입해주는 loop
   {
      (*bi_X)->a[cnt_i] = 0x00;
   }
   (*bi_X)->wordlen += add_wordlen; // wordlen 수정
#elif WORD_BITLEN == 32
   (*bi_X)->a = (word *)realloc((*bi_X)->a, 4*((*bi_X)->wordlen + add_wordlen));       // input add_wordlen만큼 추가로 realloc을 해준다.
   for (cnt_i = (*bi_X)->wordlen; cnt_i < (*bi_X)->wordlen + add_wordlen; cnt_i++) // 추가로 realloc된 공간에 0x00대입해주는 loop
   {
      (*bi_X)->a[cnt_i] = 0x00;
   }
   (*bi_X)->wordlen += add_wordlen; // wordlen 수정

#else
(*bi_X)->a = (word *)realloc((*bi_X)->a, 8*((*bi_X)->wordlen + add_wordlen));       // input add_wordlen만큼 추가로 realloc을 해준다.
   for (cnt_i = (*bi_X)->wordlen; cnt_i < (*bi_X)->wordlen + add_wordlen; cnt_i++) // 추가로 realloc된 공간에 0x00대입해주는 loop
   {
      (*bi_X)->a[cnt_i] = 0x00;
   }
   (*bi_X)->wordlen += add_wordlen; // wordlen 수정

#endif
}
void Set_Same_Wordlen_Karatsuba(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y)
{                                                      //? karatsuba에서 input data의 길이가 서로 다를때 맞추어주는함수, 또한 짝수로 맞추어준다
   if (get_word_length(bi_X) == get_word_length(bi_Y)) //wordlen이 서로 같을경우
   {
      if (get_word_length(bi_X) % 2 == 1) // 홀수일때 짝수로 변환
         Wordlen_Add_Realloc(bi_X, 1);

      if (get_word_length(bi_Y) % 2 == 1) // 위와 같음
         Wordlen_Add_Realloc(bi_Y, 1);
   }
   if (get_word_length(bi_X) != get_word_length(bi_Y)) //wordlen이 서로 다를 경우
   {
      if (get_word_length(bi_X) % 2 == 1) // 먼저 홀수이면 짝수로 변환
         Wordlen_Add_Realloc(bi_X, 1);

      if (get_word_length(bi_Y) % 2 == 1) // 위와 같음
         Wordlen_Add_Realloc(bi_Y, 1);

      if (get_word_length(bi_X) >= get_word_length(bi_Y)) // 짝수로 먼저 변환 후에 wordlen의 차이만큼 공간할당해준다
         Wordlen_Add_Realloc(bi_Y, get_word_length(bi_X) - get_word_length(bi_Y));

      if (get_word_length(bi_Y) >= get_word_length(bi_X)) // 위와 같음
         Wordlen_Add_Realloc(bi_X, get_word_length(bi_Y) - get_word_length(bi_X));
   }
}

void Mul_Core_Krsb(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y, bigint_st_ptr *bi_Z, int *count)
{ //? Mul_Core함수를 Karatsuba 버전으로 개량시킨것, 추가된 사항으로는 input에 count라는 변수가 추가됨, 수업때 일반적으로 2-3번 구현된다고 하여 count = 3으로 설정
   //? count는 depth이다, depth의 변환은 header file에서 COUNT 매크로 수를 바꿔주는것으로 가능하다.
   delete_bigint(bi_Z); //초기화
   set_zero(bi_Z);      //bi_Z를 0으로 초기화

   if ((*bi_X)->sign != (*bi_Y)->sign) //Mul_core와 같음, 부호 결정해준다 처음에
      (*bi_Z)->sign = NEGATIVE;
   
   int temp = (*count);     // count값을 저장시켜주는 temp 설정.
   bigint_st_ptr A0 = NULL; //Karatsuba에 필요한 변수들을 선언 해준다.
   bigint_st_ptr A1 = NULL;
   bigint_st_ptr B0 = NULL;
   bigint_st_ptr B1 = NULL;
   bigint_st_ptr T0 = NULL; //A0*B0을 저장해주는 변수
   bigint_st_ptr T1 = NULL; //A1*B1을 저장해주는 변수
   bigint_st_ptr R = NULL;  //T1<<WORD_BITLEN*2n +T0를 저장해 주는 변수
   bigint_st_ptr S0 = NULL; //B1 - B0
   bigint_st_ptr S1 = NULL; //A0 - A1
   integer_copy(&A1, bi_X);
   Right_Shift(&A1, (WORD_BITLEN * (get_word_length(bi_X) / 2))); //먼저 A1을 설정해준다.
   integer_copy(&A0, bi_X);
   Reduction(&A0, (WORD_BITLEN * (get_word_length(bi_X) / 2))); //위와 같은 논리
   integer_copy(&B1, bi_Y);
   Right_Shift(&B1, (WORD_BITLEN * (get_word_length(bi_Y) / 2))); //위와 같은 논리
   integer_copy(&B0, bi_Y);
   Reduction(&B0, (WORD_BITLEN * (get_word_length(bi_Y) / 2))); //위와 같은 논리

   if ((*count) > 0) //count에 의거해 0보다 크면 카라추바 곱셈을 호출한다.
      Multiplication_Karatsuba(&A1, &B1, &T1, count);
   if ((*count) <= 0)                // 그외에는 일반 곱셈을 호출한다
      Multiplication(&A1, &B1, &T1); //T1에 A1*B1값을 대입

   (*count) = temp;
   if ((*count) > 0) //count에 의거해 0보다 크면 카라추바 곱셈을 호출한다.
      Multiplication_Karatsuba(&A0, &B0, &T0, count);
   if ((*count) <= 0)                // 그외에는 일반 곱셈을 호출한다
      Multiplication(&A0, &B0, &T0); //T0에 A0*B0값을 대입

   Left_Shift(&T1, WORD_BITLEN * (get_word_length(bi_X)));  //Leftshift를 통하여 자리수를 맞추어준다.
   Addition(&T1, &T0, &R);                                  //그 후 더해서 R을 생성해준다
   Right_Shift(&T1, WORD_BITLEN * (get_word_length(bi_X))); //뒤에서 T1을 다시사용하기 위해 Rightshift를 해준다.(위에서 leftshift당함)
   Subtraction(&A0, &A1, &S1);                              //S1계산 A0 - A1
   Subtraction(&B1, &B0, &S0);                              //S2계산 B1 - B0

   (*count) = temp;
   if ((*count) > 0) //count에 의거해 0보다 크면 카라추바 곱셈을 호출한다.
      Multiplication_Karatsuba(&S0, &S1, bi_Z, count);
   if ((*count) <= 0) // 그외에는 일반 곱셈을 호출한다
      Multiplication(&S0, &S1, bi_Z);

   if (S0->sign == S1->sign) //부호 결정
      (*bi_Z)->sign = NON_NEGATIVE;
   if (S0->sign != S1->sign)
      (*bi_Z)->sign = NEGATIVE;

   Addition(&T0, &T1, &A0);       //A0에 Addition을 위한 변수를 설정해준다.(기존에 필요없는 변수 재이용 )물론 addition호출시 A0는 초기화됨
   Addition(&A0, bi_Z, &S0);                                     //그후 최종적으로 S0를 만들어준다.
   Left_Shift(&S0, (WORD_BITLEN * (get_word_length(bi_X) / 2))); //Shifting
   Addition(&R, &S0, bi_Z);                                      //최종 bi_Z가 나왔다.

   delete_bigint(&A0); //메모리 동적할당 Free
   delete_bigint(&A1); //위와 같음
   delete_bigint(&B0); //위와 같음
   delete_bigint(&B1); //위와 같음
   delete_bigint(&T0); //위와 같음
   delete_bigint(&T1); //위와 같음
   delete_bigint(&R);  //위와 같음
   delete_bigint(&S0); //위와 같음
   delete_bigint(&S1); //위와 같음
}
void Multiplication_Karatsuba(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y, bigint_st_ptr *bi_Z, int *count)
{ //? 일반적인 곱셈을 정의해준것처럼 Karatsuba도 input data에 1 or -1 or 0이 있는경우를 생각해준다.
   delete_bigint(bi_Z);
   (*count)--;              // 함수가 시작되었기 때문에 input count를 --해준다.
   if (is_zero(bi_X) == TRUE || is_zero(bi_Y) == TRUE) //Trivial
   {
      set_zero(bi_Z);
      return;
   }
   if (is_one(bi_X) == TRUE) //Trivial
   {
      integer_copy(bi_Z, bi_Y);
      return;
   }
   if (is_one(bi_Y) == TRUE) //Trivial
   {
      integer_copy(bi_Z, bi_X);
      return;
   }
   if (is_minus_one(bi_X) == TRUE) //Trivial
   {
      integer_copy(bi_Z, bi_Y);
      flip_sign(bi_Z);
      return;
   }
   if (is_minus_one(bi_Y) == TRUE) //Trivial
   {
      integer_copy(bi_Z, bi_X);
      flip_sign(bi_Z);
      return;
   }
   Set_Same_Wordlen_Karatsuba(bi_X, bi_Y); // Karatsuba를 호출전에 항상 자리수를 같게, 그리고 짝수로 맞추어준다.
   Mul_Core_Krsb(bi_X, bi_Y, bi_Z, count); // 그외 일반적인 경우 호출
   return;
}
void Squaring_Core_word(word A, bigint_st_ptr *squaring_word) //? Mul_word와 마찬가지로 단일 워드 A에 대한 제곱을 만드는 함수이다.
{
   delete_bigint(squaring_word);
   bigint_st_ptr C = NULL;                           // A1^2 *Word + A0^2을 저장하기 위한 변수
   bigint_st_ptr T = NULL;                           //A0*A1을 저장하기 위한 변수
   set_zero(&T);                                     // 0으로 초기화
   set_zero(&C);                                     // 위와같음
#if WORD_BITLEN == 8
   C->a = (word *)realloc(C->a, 2 * (sizeof(word))); //초기화후 wordlen 2로 늘려줌
#elif WORD_BITLEN == 32
   C->a = (word *)realloc(C->a, 4 * 2 * (sizeof(word))); //초기화후 wordlen 2로 늘려줌
#else 
   C->a = (word *)realloc(C->a, 8 * 2 * (sizeof(word))); //초기화후 wordlen 2로 늘려줌
#endif
   C->wordlen = 2;

   word A1 = A >> (WORD_BITLEN / 2);             //A1설정
   word A0 = A & ((1LL << (WORD_BITLEN / 2)) - 1); //A0설정
   word C1 = A1 * A1;                            //C1설정
   word C0 = A0 * A0;                            //C0설정

   C->a[0] = C0;                          //선언한 목적에 맞게 변수 대입
   C->a[1] = C1;                          //위와 같음
   T->a[0] = A0 * A1;                     //위와 같음
   Left_Shift(&T, (WORD_BITLEN / 2) + 1); //먼저 WORD_BITLEN의 절반만큼 Shifting을 해주고 2A0*A1이므로 1만큼 더 Shifting
   Addition(&C, &T, squaring_word);       //더해서 최종값 만들어준다
   delete_bigint(&C);                     //메모리 동적할당 해제
   delete_bigint(&T);                     //위와 같음
}
void Squaring_Core(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Z)
{ //? 바로 위 함수에서 단일 워드에 대한 곱셈함수를 위에 정의해 주었으므로, bigint구조체에 대한 제곱함수를 만들어준다
   delete_bigint(bi_Z);
   set_zero(bi_Z); //초기화 후 0대입
   int cnt_i, cnt_j = 0;

   bigint_st_ptr C1 = NULL;   //(A_cnt_i)^2값을 저장할 변수
   bigint_st_ptr C2 = NULL;   //(A_cnt_i * A_cnt_j)^2값을 저장할 변수
   bigint_st_ptr T = NULL;    // 계산을 위한 Temp값설정
   bigint_st_ptr Temp = NULL; //Addition을 위한 Temp(저장)값 설정.
   set_zero(&Temp);           //Temp값 초기화

   for (cnt_i = 0; cnt_i < get_word_length(bi_X); cnt_i++)
   {
      Squaring_Core_word((*bi_X)->a[cnt_i], &T); //(A_cnt_i)^2값을 저장해준다
      Left_Shift(&T, WORD_BITLEN * cnt_i * 2);   // 그후 loop에 맞게 shifting
      Addition(&Temp, &T, &C1);                  // 차근차근히 C1에 더해준다.
      integer_copy(&Temp, &C1);                  // Temp값에 C1을 복사, loop을돌면 차근차근 C1에 값이 쌓이게 된다.
   }
   set_zero(&Temp); // 초기화
   for (cnt_j = 0; cnt_j < get_word_length(bi_X); cnt_j++)
   {
      for (cnt_i = cnt_j + 1; cnt_i < get_word_length(bi_X); cnt_i++)
      {
         Mul_Core_word((*bi_X)->a[cnt_j], (*bi_X)->a[cnt_i], &T); //(A_cnt_i * A_cnt_j)^2값을 저장해준다
         Left_Shift(&T, WORD_BITLEN * (cnt_i + cnt_j));           // 그후 loop에 맞게 shifting
         Addition(&Temp, &T, &C2);                                // 차근차근히 C2에 더해준다.
         integer_copy(&Temp, &C2);                                // Temp값에 C2을 복사, loop을돌면 차근차근 C1에 값이 쌓이게 된다.
      }
   }
   Left_Shift(&C2, 1);       //제곱 함수이므로 (A_cnt_i * A_cnt_j)가 두개씩 생긴다.
   Addition(&C1, &C2, bi_Z); // 최종결과 값 만들어주기
   optimize(bi_Z);
   delete_bigint(&C1);   //메모리 동적할당 해제
   delete_bigint(&C2);   //위와같음
   delete_bigint(&T);    //위와 같음
   delete_bigint(&Temp); //위와 같음
}

void Squaring(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Z)
{ //? inputdata에 맞게 Squaring을 해주는 함수이다. input data가-1 or 0 or 1일 경우를  생각해준다.
   delete_bigint(bi_Z);
   if (is_zero(bi_X) == TRUE) //Trivial
   {
      set_zero(bi_Z);
      return;
   }
   if (is_one(bi_X) == TRUE) //Trivial
   {
      set_one(bi_Z);
      return;
   }
   if (is_minus_one(bi_X) == TRUE) //Trivial
   {
      set_one(bi_Z);
      return;
   }
   if (get_word_length(bi_X) == 1) //input_data의 길이가 1일경우는 그냥 단일 워드 곱셈이다.
   {
      Squaring_Core_word((*bi_X)->a[0], bi_Z);
      return;
   }

   Squaring_Core(bi_X, bi_Z); //그외 일반적인 경우
}

void Squaring_Karatsuba(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Z, int *count)
{ //? 제곱 카라추바도 곱셈 카라추바와 마찬가지로 input data에 count라는 변수를 설정해준다 cout는 depth이다. count는 headerfile에서 COUNT 매크로를 수정할 수 있다.
 //? 먼저 input data에 대해 -1 or 0 or 1을 고려해 준다
   (*count)--;              // 함수가 호출되었으므로 count --
   delete_bigint(bi_Z);
   if (is_zero(bi_X) == TRUE) //Trivial
   {
      set_zero(bi_Z);
      return;
   }
   if (is_one(bi_X) == TRUE) //Trivial
   {
      set_one(bi_Z);
      return;
   }
   if (is_minus_one(bi_X) == TRUE) //Trivial
   {
      set_one(bi_Z);
      return;
   }
   if (get_word_length(bi_X) == 1) //Trivial
   {
      Squaring_Core_word((*bi_X)->a[0], bi_Z);
      return;
   }
   //그 외의 경우. Squaring karatsuba는 코드길이가 길지 않아서 통합했습니다.
   set_zero(bi_Z);                     //초기화
   if (get_word_length(bi_X) % 2 == 1) //홀수인경우 짝수로 맞추어 주기
      Wordlen_Add_Realloc(bi_X, 1);    //홀수인경우 1만큼 추가로 메모리 할당,추가공간은 0으로 초기화

   int temp = (*count);     // depth값을 저장하기 위한 변수
   bigint_st_ptr A0 = NULL; //A의 절반비트 앞부분
   bigint_st_ptr A1 = NULL; //A의 절반비트 윗부분
   bigint_st_ptr T0 = NULL; //A0^2저장하기위한 변수
   bigint_st_ptr T1 = NULL; //A1^2저장하기위한 변수
   bigint_st_ptr R = NULL;  // T1*2^WORD_BITLEN * n + T0를 저장하기위한 변수
   bigint_st_ptr S = NULL;  //A1*A0를 저장하기 위한 변수

   integer_copy(&A1, bi_X);
   Right_Shift(&A1, (WORD_BITLEN * (get_word_length(bi_X) / 2))); //A1설정

   integer_copy(&A0, bi_X);
   Reduction(&A0, (WORD_BITLEN * (get_word_length(bi_X) / 2))); //A0설정

   if ((*count) > 0) //cout>0이면 Karatsuba 호출
      Squaring_Karatsuba(&A1, &T1, count);
   if ((*count) <= 0) // 그외에는 일반 제곱
      Squaring(&A1, &T1);

   (*count) = temp; //depth 동일하게 맞춰주기 위한 작업

   if ((*count) > 0) //cout>0이면 Karatsuba 호출
      Squaring_Karatsuba(&A0, &T0, count);
   if ((*count) <= 0) // 그외에는 일반 제곱
      Squaring(&A0, &T0);

   Left_Shift(&T1, WORD_BITLEN * (get_word_length(bi_X)));
   Addition(&T0, &T1, &R);

   (*count) = temp;  //depth 동일하게 맞춰주기 위한 작업
   if ((*count) > 0) //cout>0이면 Karatsuba 호출
      Multiplication_Karatsuba(&A1, &A0, &S, count);
   if ((*count) <= 0) // 그외에는 일반 곱셈
      Multiplication(&A1, &A0, &S);

   Left_Shift(&S, 1);                                           //A0*A1은 제곱이므로 2개 생성된다, 그래서 *2해준다 ->Shifiting
   Left_Shift(&S, (WORD_BITLEN * (get_word_length(bi_X) / 2))); //자리수를 맞춰주기위한 Shifting
   Addition(&R, &S, bi_Z);                                      // 최종값 만들어주기

   delete_bigint(&A0); //메모리 동적할당 해제
   delete_bigint(&A1); //위와같음
   delete_bigint(&R);  //위와같음
   delete_bigint(&T0); //위와같음
   delete_bigint(&T1); //위와 같음
   delete_bigint(&S);  //위와 같음
}

void LongDivision_Bit(bigint_st_ptr *bi_X, bigint_st_ptr *bi_Y, bigint_st_ptr *bi_Q, bigint_st_ptr *bi_R)
{                    //? Bit version의 Long division 이다. Q는 몫이고, R은 나머지 이다.
   set_zero(bi_Q);             //몫 초기화
   set_zero(bi_R);             //나머지 초기화
   bigint_st_ptr Temp = NULL;  //Addition값을 만들어 주기 위한 Temp값 설정
   bigint_st_ptr Temp2 = NULL; //Addition값을 만들어 주기 위한 Temp2값 설정
   set_zero(&Temp);            //초기화
   set_zero(&Temp2);           //초기화
   int cnt_i, cnt_j;

   for (cnt_i = get_bit_length(bi_X) - 1; cnt_i >= 0; cnt_i--) // Bit 버전 Long_Division이므로,bit_len으로 loop
   {
      Left_Shift(bi_R, 1);
      (*bi_R)->a[0] ^= get_j_th_bit(bi_X, cnt_i); //2R + Aj를   Left Shifting 1 , 그리고 j번째 비트 XoR로 구현해준다.

      if (Compare(bi_R, bi_Y) != SCD_IS_BIG) // R>= B 인경우이다.
      {
         Subtraction(bi_R, bi_Y, &Temp); // R-B Subtraction 함수 이용
         integer_copy(bi_R, &Temp);      // bi_R을 갱신시켜주기 위해서 Temp 값을 사용했다.
         
         set_one(&Temp2);                                           // Temp2값 초기화
         Left_Shift(&Temp2, cnt_i);                                 // 몫이 생기면 Shifting
         Set_Same_Wordlen_Karatsuba(bi_Q, &Temp2);                  //wordlen 맞춰준다, XoR 해주기위하여
         for (cnt_j = 0; cnt_j < get_word_length(&Temp2); cnt_j++)  //XoR 해준다.
         {
            (*bi_Q)->a[cnt_j] ^= Temp2->a[cnt_j];
         }
      }
   }
   
   optimize(bi_Q);//optimize
   optimize(bi_R);//optimize
   delete_bigint(&Temp);  //메모리 동적할당 해제
   delete_bigint(&Temp2); //위와 같음
}