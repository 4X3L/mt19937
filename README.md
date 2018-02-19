# Mersenne Twister

This is a simple implementation of the Mersenne Twister PRNG.

## Example Code

```
#include <stdio.h>
#include <mt.h>

int
main ()
{
  struct mt_gen32 g;
  mt_init_default_gen32 (&g);
  uint32_t state[MT_GEN32_SIZE];
  mt_save_state32 (state, &g);
  
  for (uint32_t i = 0; i < 600; i++)
    {
      for (uint32_t j = 0; j < 4; j++)
        printf ("%10u ", mt_next_uint32 (&g));
      printf ("\n");
    }
  
  printf ("\n");
  
  for (uint32_t i = 0; i < 600; i++)
    {
      for (uint32_t j = 0; j < 4; j++)
        printf ("%5d ", mt_next_int32_range (&g, -5, 5));
      printf ("\n");
    }
  
  printf ("\n");
  
  for (uint32_t i = 0; i < 600; i++)
    {
      for (uint32_t j = 0; j < 4; j++)
        printf ("%f ", mt_next_float(&g));
      printf ("\n");
    }
  
  printf ("\n");
  
  mt_init_gen32 (&g, state);
  
  for (uint32_t i = 0; i < 600; i++)
    {
      for (uint32_t j = 0; j < 4; j++)
        printf ("%10u ", mt_next_uint32 (&g));
      printf ("\n");
    }
  for (uint32_t i = 0; i < 600; i++)
    {
      for (uint32_t j = 0; j < 4; j++)
        printf ("%10u ", mt_next_uint32_range (&g, 100, 500));
      printf ("\n");
    }
}
```
