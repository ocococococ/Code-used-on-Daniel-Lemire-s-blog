#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int int_log2(uint32_t x) { return 31 - __builtin_clz(x | 1); }

// credit: kwillets
/**
 * (1 << 32) + (0 << 32), // ceil(log10(1)) = 0
(1 << 32) -  10 + (1 << 32), // ceil(log10(2)) = 1
(1 << 32) -  10 + (1 << 32), // ceil(log10(4)) = 1
(1 << 32) -  10 + (1 << 32), // ceil(log10(8)) = 1
(1 << 32) -  100 + (2 << 32), // ceil(log10(16)) = 2
(1 << 32) -  100 + (2 << 32), // ceil(log10(32)) = 2
(1 << 32) -  100 + (2 << 32), // ceil(log10(64)) = 2
(1 << 32) -  1000 + (3 << 32), // ceil(log10(128)) = 3
(1 << 32) -  1000 + (3 << 32), // ceil(log10(256)) = 3
(1 << 32) -  1000 + (3 << 32), // ceil(log10(512)) = 3
(1 << 32) -  10000 + (4 << 32), // ceil(log10(1024)) = 4
(1 << 32) -  10000 + (4 << 32), // ceil(log10(2048)) = 4
(1 << 32) -  10000 + (4 << 32), // ceil(log10(4096)) = 4
(1 << 32) -  10000 + (4 << 32), // ceil(log10(8192)) = 4
(1 << 32) -  100000 + (5 << 32), // ceil(log10(16384)) = 5
(1 << 32) -  100000 + (5 << 32), // ceil(log10(32768)) = 5
(1 << 32) -  100000 + (5 << 32), // ceil(log10(65536)) = 5
(1 << 32) -  1000000 + (6 << 32), // ceil(log10(131072)) = 6
(1 << 32) -  1000000 + (6 << 32), // ceil(log10(262144)) = 6
(1 << 32) -  1000000 + (6 << 32), // ceil(log10(524288)) = 6
(1 << 32) -  10000000 + (7 << 32), // ceil(log10(1048576)) = 7
(1 << 32) -  10000000 + (7 << 32), // ceil(log10(2097152)) = 7
(1 << 32) -  10000000 + (7 << 32), // ceil(log10(4194304)) = 7
(1 << 32) -  10000000 + (7 << 32), // ceil(log10(8388608)) = 7
(1 << 32) -  100000000 + (8 << 32), // ceil(log10(16777216)) = 8
(1 << 32) -  100000000 + (8 << 32), // ceil(log10(33554432)) = 8
(1 << 32) -  100000000 + (8 << 32), // ceil(log10(67108864)) = 8
(1 << 32) -  1000000000 + (9 << 32), // ceil(log10(134217728)) = 9
(1 << 32) -  1000000000 + (9 << 32), // ceil(log10(268435456)) = 9
(1 << 32) -  1000000000 + (9 << 32), // ceil(log10(536870912)) = 9
*/
int fast_digit_count(uint32_t x) {
  static uint64_t table[] = {
      4294967296,  8589934582,  8589934582,  8589934582,  12884901788,
      12884901788, 12884901788, 17179868184, 17179868184, 17179868184,
      21474826480, 21474826480, 21474826480, 21474826480, 25769703776,
      25769703776, 25769703776, 30063771072, 30063771072, 30063771072,
      34349738368, 34349738368, 34349738368, 34349738368, 38554705664,
      38554705664, 38554705664, 41949672960, 41949672960, 41949672960,
      42949672960, 42949672960};
  return (x + table[int_log2(x)]) >> 32;
}
int digit_count(uint32_t x) {
  static uint32_t table[] = {9,      99,      999,      9999,     99999,
                             999999, 9999999, 99999999, 999999999};
  int y = (9 * int_log2(x)) >> 5;
  y += x > table[y];
  return y + 1;
}

int main() {
  for (uint32_t val = 1; val != 0; val++) {
    if (fast_digit_count(val) != digit_count(val)) {
      printf("%u %d %d \n", val, digit_count(val), fast_digit_count(val));
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}