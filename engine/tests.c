// #include <stdio.h>
// #include <wchar.h>
// #include <stdlib.h>
// #include <locale.h>

/* UTF8 */

// int main() {
//	int r;
//	wchar_t myChar1 = L'Ω';
//	setlocale(LC_CTYPE, "");
//	r = wprintf(L"char is %lc (%x)\n", myChar1, myChar1);
// }

/* ANIMACJA */
// #include <stdio.h>

// void advance_cursor() {
//   static int pos=0;
//   char cursor[4]={'/','-','\\','|'};
//   printf("12 %c\b\b\b\b", cursor[pos]);
//   fflush(stdout);
//   pos = (pos+1) % 4;
// }

// int main(int argc, char **argv) {
//   int i;
//   for (i=0; i<100; i++) {
//	advance_cursor();
//	usleep(100000);
//   }
//   printf("\n");
//   return 0;
// }

/* KOLORY */
// #include <stdio.h>

// #define KNRM  "\x1B[0m"
// #define KRED  "\x1B[31m"
// #define KGRN  "\x1B[32m"
// #define KYEL  "\x1B[33m"
// #define KBLU  "\x1B[34m"
// #define KMAG  "\x1B[35m"
// #define KCYN  "\x1B[36m"
// #define KWHT  "\x1B[37m"

// int main()
// {
//	printf("%sred\n", KRED);
//	printf("%sgreen\n", KGRN);
//	printf("%syellow\n", KYEL);
//	printf("%sblue\n", KBLU);
//	printf("%smagenta\n", KMAG);
//	printf("%scyan\n", KCYN);
//	printf("%swhite\n", KWHT);
//	printf("%snormal\n", KNRM);

//	return 0;
// }

/* ROZMIAR TERMINALA */

// #include <sys/ioctl.h>
// #include <stdio.h>
// #include <unistd.h>

// int main (int argc, char **argv)
// {
// 	struct winsize w;
// 	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

// 	printf ("lines %d\n", w.ws_row);
// 	printf ("columns %d\n", w.ws_col);
// 	return 0;  // make sure your main returns int
// }
