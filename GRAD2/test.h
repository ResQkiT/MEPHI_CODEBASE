 #include <stdio.h>
 #define mu_assert(message, test) do { if (!(test)) return message; } while (0)
 #define mu_run_test(test) do { char *message = test(); tests_run++; if (message){ printf(message); tests_failed++;}else{tests_succses++;} } while (0);
 extern int tests_run;
 extern int tests_failed;
 extern int tests_succses;