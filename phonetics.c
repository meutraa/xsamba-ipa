#include <stdio.h>
#include <termios.h>

const char* di_map[] = /* r\` ɻ G\< ʛ J\< ʄ */
{
   "bb", "ɓ",
   "BB", "ʙ",
   "dd", "ɖ",
   "d'", "ɗ",
   "gg", "ɠ",
   "GG", "ɢ",
   "hh", "ɦ",
   "HH", "ʜ",
   "II", "ᵻ",
   "jj", "ʝ",
   "JJ", "ɟ",
   "KK", "ɮ",
   "l'", "ɭ",
   "ll", "ɺ",
   "LL", "ʟ",
   "MM", "ɰ",
   "nn", "ɳ",
   "NN", "ɴ",
   "OO", "ʘ",
   "pp", "ɸ",
   "r'", "ɽ",
   "rr", "ɹ",
   "RR", "ʀ",
   "s'", "ʂ",
   "ss", "ɕ",
   "tt", "ʈ",
   "UU", "ᵿ",
   "vv", "ʋ",
   "XX", "ħ",
   "z'", "ʐ",
   "zz", "ʑ",
};

const char* upper_alpha_map[] =
{
   "ɑ", "β", "ç", "ð", "ɛ", "ɱ", "ɣ", "ɥ", "ɪ", "ɲ", "ɬ", "ʎ", "ɯ",
   "ŋ", "ɔ", "ʋ", "ɒ", "ʁ", "ʃ", "θ", "ʊ", "ʌ", "ʍ", "χ", "ʏ", "ʒ",
};

const int di_size = sizeof(di_map)/sizeof(di_map[0]);
char c[2];
int j;

void prepare(int i)
{
   fflush(stdout);
   c[i] = getchar();

   switch(c[i])
   {
      case 127:
         printf("\b\b\b   \b\b\b");
      case ' ':
         prepare(0);
   }

   switch(i)
   {
      case 1:
         for(j = 0; j < di_size; j = j + 2)
         {
            if(di_map[j][0] == c[0] && di_map[j][1] == c[1])
            {
               printf("\b\b  \b\b%s", di_map[j + 1]);
               prepare(0);
            }
         }
         c[0] = c[1];
      case 0:
      {
         /* Check the latest char for matches. */
         unsigned char d = c[i] - 65;
         if(d < 26)
         {
            printf("\b%s", upper_alpha_map[d]);
         }
      }
   }
   prepare(1);
}

int main()
{
   struct termios old, new;
   tcgetattr(0, &old);
   new = old;
   new.c_lflag &= ~ICANON;
   tcsetattr(0, TCSANOW, &new);
   prepare(0);
   tcsetattr(0, TCSANOW, &old);
   return 0;
}
