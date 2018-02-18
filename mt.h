#ifndef MT_H
#define MT_H

/* Taken from the paper "Merseene Twister: A 623-dimensionally eqidistributed 
   uniform pseduorandom number generator" by Makoto Matsumoto and Takuji 
   Nishimura 

   The code here is fairly, "naive", more for the purpose of teaching myself 
   about seudo-random numbers and less about getting a fast or high quality
   generator. (Although I have no reason to believe it is slow and should be as
   good as any other implementation of Merseen Twister) 
   
   None of the functions use mutable global state should be thread safe. 

   This code is licensed under the MIT License, which can be found at the end of
   this file.
*/

#include <stdint.h>

#define MT_GEN32_SIZE 624

struct mt_gen32
{
  uint32_t i;
  uint32_t x[MT_GEN32_SIZE];
};

/* Initialize the generator with some seed. This function will attempt to get a 
   source of entropy directly from the OS so calling this is probably better 
   than initializing the generator yourself unless you have a good reason. If 
   you want a consistent seed, call this function once and save the resulting
   generator state. 
   
   On an error, -1 is returned and errno is set.
*/
int
mt_init_default_gen32 (struct mt_gen32 *g);

/* State is an array of 624 integers. I nammed it "state" so that it is clear
   that if a generator is seeded, some numbers are generated, then the state is
   saved, the current state of the generator will be put into the "state" array
   not the original seed. However, if no numbers are generated, then the seed 
   will be the same. In other code...
   
   uint32_t init[624];
   uint32_t state[624]; 

   // ... initialize the initial seed "init" to some value ... 

   struct mt_gen32 g;
   mt_init_gen32 (&g, init);
   mt_save_state (state, &g);
   
   boolen b = true;
   for (uint32_t i = 0; i < 624; i++)
     assert (b && init[i] == state [i])

   uint32_t i = mt_next_uint32 (&g);
   
   mt_save_state (state, &g);
   b = false;
   for (uint32_t i = 0; i < 624; i++)
     assert (b || init[i] != state[i])
*/
void
mt_save_state32 (uint32_t *state, const struct mt_gen32 *g);

/* Seed is an array of 624 unsigned 32bit integers */
void
mt_init_gen32 (struct mt_gen32 *g, const uint32_t *seed);

uint32_t
mt_next_uint32 (struct mt_gen32 *g);

/* next_uint32_range, next_int32_range, and mt_next_float all call
   mt_next_uint32 internally.

   Using modulo to round off the output of a random number generator will 
   introduce biased results so range generates multiple numbers until finding
   one that is less than some multiple of a number less than 2^32 - 1. 
   
   All ranges are inclusive, [m, n], and m <= n. This is ensured by an 
   insertion in the function definitions. */
uint32_t
mt_next_uint32_range (struct mt_gen32 *g, uint32_t m, uint32_t n);

int32_t
mt_next_int32_range (struct mt_gen32 *g, int32_t m, int32_t n);

/* Generates a float in [0,1). The generator gives us actually a little bit more
   entropy than what we would need for a float, but does not give us the 52 bits
   required for a double */
float
mt_next_float (struct mt_gen32 *g);

#endif /* MT_H */

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
