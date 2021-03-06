#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <immintrin.h>

#define N 512

static __inline__ unsigned long long rdtsc(void)
{
  unsigned hi, lo;
  __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
  return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

int main()
{
  double execTime;
  double startTime, endTime;
  long long t;
  double * temp_b1;
  double * temp_c1;

  double *A = (double*)memalign(32, N * N * sizeof(double));
  double *B = (double*)memalign(32, N * N * sizeof(double));
  double *C = (double*)memalign(32, N * N * sizeof(double));

  for(int i = 0; i < N * N; i++)
  {
    A[i] = i + 1;
    B[i] = i + 1;
    C[i] = 0;
  }

  double duration = 0.0;
  struct timeval start;

  gettimeofday(&start, NULL);
  t = rdtsc();
  startTime = (double)(start.tv_sec + start.tv_usec/1000000.0);

#ifdef ASM
  __m128d temp_a;
  __m128d temp_b;
  __m128d temp_c;
  __m128d temp_d;
  for(int i = 0; i < N ; i++)
  {
    for(int j = 0; j < N ; j++)
    {
      temp_d = _mm_setzero_pd();
      for (int k = 0 ; k < N ; k += 2)
      {
        temp_a = _mm_loadu_pd(A + i * N + k);
        temp_b = _mm_set_pd(B[(k + 1) * N + j], B[(k + 0) * N + j]);
        temp_c = _mm_mul_pd(temp_a, temp_b);
        temp_d = _mm_add_pd(temp_d, temp_c);
      }
      temp_d = _mm_hadd_pd(temp_d, temp_d);
      _mm_store_sd(C + i * N + j, temp_d);
    }
  }
#else
  for(int i = 0; i < N; i++)
  {
    for(int j = 0; j < N; j++)
    {
      double temp = A[i * N + j];
      temp_c1 = C + i * N;
      temp_b1 = B + j * N;
      for(int k = 0; k < N; k++)
        temp_c1[k] += temp * temp_b1[k];
    }
  }
#endif
  t = rdtsc() - t;
  gettimeofday(&start, NULL);
  endTime = (double)(start.tv_sec + start.tv_usec/1000000.0);
  execTime = endTime - startTime;

  printf("Clock cycle count is %llu\n", t);
  printf("Execution time is %2.3f seconds\n", execTime);

  return 0;
}
