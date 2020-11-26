/**
 *
 * \section COPYRIGHT
 *
 * Copyright 2013-2020 Software Radio Systems Limited
 *
 * By using this file, you agree to the terms and conditions set
 * forth in the LICENSE file which can be found at the top level of
 * the distribution.
 *
 */

#ifdef CHECK_FUNCTION_EXISTS

char CHECK_FUNCTION_EXISTS();
#ifdef __CLASSIC_C__
int main()
{
  int   ac;
  char* av[];
#else
int main(int ac, char* av[])
{

#endif
  float ac2 = sqrtf(rand());
  CHECK_FUNCTION_EXISTS();
  if (ac2 * ac > 1000) {
    return *av[0];
  }
  return 0;
}

#else /* CHECK_FUNCTION_EXISTS */

#error "CHECK_FUNCTION_EXISTS has to specify the function"

#endif /* CHECK_FUNCTION_EXISTS */
