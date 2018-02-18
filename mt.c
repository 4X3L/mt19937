#include "mt.h"

#include <string.h>
#include <assert.h>

#define N 624
#define M 397
#define A 0x9908b0df /* The "matrix" */
#define UM 0x80000000 /* Upper bit mask */
#define LM 0x7fffffff /* Lower bit mask */
#define B 0x9d2c5680
#define C 0xefc60000
#define U(y) (y >> 11)
#define S(y) (y << 7)
#define T(y) (y << 15)
#define L(y) (y >> 18)

static void
gen_array (struct mt_gen32 *g)
{
  uint32_t i;
  for (i = 0; i < N - M; i++)
    {
      uint32_t y = (g->x[i] & UM) | (g->x[i+1] & LM);
      g->x[i] = g->x[i+M] ^ (y >> 1);
      if (y & 1)
        g->x[i] ^= A;
      else
        g->x[i] ^= 0;
    }
  for (; i < N-1; i++)
    {
      uint32_t y = (g->x[i] & UM) | (g->x[i+1] & LM);
      g->x[i] = g->x[i+(M-N)] ^ (y >> 1);
      if (y & 1)
        g->x[i] ^= A;
      else
        g->x[i] ^= 0;
    }
  uint32_t y = (g->x[N-1]&UM) | (g->x[0]&LM);
  g->x[N-1] = g->x[M-1] ^ (y >> 1);
  if (y & 1)
    g->x[N-1] ^= A;
  else
    g->x[N-1] ^= 0;
  g->i = 0;
}

#ifdef __LINUX__

#include <sys/random.h>

int
mt_init_default_gen32 (struct mt_gen32 *g)
{
  if (getrandom (g->x, N, GRND_NONBLOCK) == -1)
    return -1;
  gen_array (g);
  return 0;
}

#endif /* __LINUX__ */
 
void
mt_init_gen32 (struct mt_gen32 *g, const uint32_t *seed) 
{
  memcpy (g->x, seed, N * sizeof (uint32_t));
  gen_array (g);
}

uint32_t
mt_next_uint32 (struct mt_gen32 *g)
{
  if (g->i >= N)
    gen_array (g);
  uint32_t y = g->x[g->i];
  y ^= U(y);
  y ^= S(y) & B;
  y ^= T(y) & C;
  y ^= L(y);
  g->i++;
  return y;
};

/* Generate in range [0, i] */
static uint32_t 
mt_zero_uint32 (struct mt_gen32 *g, uint32_t i)
{
  uint32_t divisor = UINT32_MAX / (i+1);
  uint32_t retval;

  do
    { 
      retval = mt_next_uint32 (g) / divisor;
    } while (retval > i);
  
  return retval;
}

uint32_t
mt_next_uint32_range (struct mt_gen32 *g, uint32_t m, uint32_t n) 
{
  assert (m <= n);
  return m + mt_zero_uint32 (g, n - m);
};

int32_t
mt_next_int32_range (struct mt_gen32 *g, int32_t m, int32_t n) 
{
  assert (m <= n);
  return m + mt_zero_uint32 (g, n - m);
};

float
mt_next_float (struct mt_gen32 *g) 
{
  return 0x3f800000 | (mt_next_uint32 (g) & 0x007FFFFF);
};

/*
 * Copyright © 2018 Alex Benishek
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the “Software”), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions: 
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software. 

 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 */
