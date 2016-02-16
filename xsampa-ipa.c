#include <stdio.h>
#include <string.h>
#include <termios.h>

const char* map[] = 
{
	/* Unrounded Vowels */
	"A",	"ɑ",	// open       back
	"a",	"a",	// open		  front
	"{",	"æ",	// near-open  front
	"V",	"ʌ",	// open-mid   back
	"3",	"ɜ",	// open-mid   central
	"E",	"ɛ",	// open-mid   front
	"7",	"ɤ",	// close-mid  back
	"@\\",	"ɘ",	// close-mid  central
	"e",	"e",	// close-mid  front
	"I\\",	"ᵻ",	// near-close central
	"I",	"ɪ",	// near-close near-front
	"M",	"ɯ",	// close      back
	"1",	"ɨ",	// close      central
	"i",	"i",	// close	  front

	/* Other Vowels */
	"6",	"ɐ",	// near-open central
	"@",	"ə",	// schwa

	/* Rounded Vowels */
	"Q",	"ɒ",	// open       back
	"&",	"ɶ",	// open       front
	"O",	"ɔ",	// open-mid   back
	"3\\",	"ɞ",	// open-mid   central
	"9",	"œ",	// open-mid   front
	"o",	"o",	// close-mid  back
	"8",	"ɵ",	// close-mid  central
	"2",	"ø",	// close-mid  front
	"U",	"ʊ",	// near-close near-back
	"U\\",	"ᵿ",	// near-close central
	"Y",	"ʏ",	// near-close near-front
	"u",	"u",	// close      back
	"}",	"ʉ",	// close      central
	"y",	"y",	// close      front


	/* Approximants */
	"r\\",	"ɹ",	// alveolar          
	"l",	"l",	// alveolar  lateral 
	"5",	"ɫ",	// velarized alveolar lateral
	"P",	"ʋ",	// labiadental
	"v\\",	"ʋ",	// labiodental
	"H",	"ɥ",	// labial-palatal
	"w",	"w",	// labial-velar
	"j",	"j",	// palatal			 
	"L",	"ʎ",	// palatal lateral
	"r\\`",	"ɻ",	// retroflex
	"l`",	"ɭ",	// retroflex lateral
	"M\\",	"ɰ",	// velar
	"L\\",	"ʟ",	// velar lateral

	/* Voiced Implosives */
	"d_<",	"ɗ",	// alveolar 
	"b_<",	"ɓ",	// bilabial 
	"J\\_<","ʄ",	// palatal
	"G\\_<","ʛ",	// uvular
	"g_<",	"ɠ",	// velar    

	/* Voiced Plosives */
	"d",	"d",	// alveolar  
	"b",	"b",	// bilabial
	">\\",	"ʡ",	// epiglottal (TODO voiced?)
	"J\\",	"ɟ",	// palatal
	"d`",	"ɖ",	// retroflex 
	"G\\",	"ɢ",	// uvular
	"g",	"g",	// velar	

	/* Voiceless Plosives */
	"t",	"t",	// alveolar
	"p",	"p",	// bilabial  
	"c",	"c",	// palatal   
	"t`",	"ʈ",	// retroflex
	"q",	"q",	// uvular   
	"k",	"k",	// velar     

	/* Voiced Fricatives */
	"z",	"z",	// alveolar
	"K\\",	"ɮ",	// alveolar lateral
	"z\\",	"ʑ",	// alveolo-palatal
	"B",	"β",	// bilabial
	"D",	"ð",	// dental
	"<\\",	"ʢ",	// epiglottal
	"h\\",	"ɦ",	// glottal
	"v",	"v",	// labiodental
	"j\\",	"ʝ",	// palatal
	"?\\",	"ʕ",	// pharyngeal
	"Z",	"ʒ",	// postalveolar
	"z`",	"ʐ",	// retroflex
	"R",	"ʁ",	// uvular
	"G",	"ɣ",	// velar

	/* Voiceless Fricatives */
	"s",	"s",	// alveolar
	"K",	"ɬ",	// alveolar lateral
	"s\\",	"ɕ",	// alveolo-palatal
	"p\\",	"ɸ",	// bilabial
	"T",	"θ",	// dental
	"H\\",	"ʜ",	// epiglottal
	"h",	"h",	// glottal	 
	"f",	"f",	// labiodental 
	"W",	"ʍ",	// labial-velar
	"C",	"ç",	// palatal
	"x\\",	"ɧ",	// palatal-velar
	"X\\",	"ħ",	// pharyngeal
	"S",	"ʃ",	// postalveolar
	"s`",	"ʂ",	// retroflex
	"X",	"χ",	// uvular
	"x",	"x",	// velar

	/* Trills */
	"r",	"r",	// alveolar  
	"B\\",	"ʙ",	// bilabial
	"R\\",	"ʀ",	// uvular

	/* Flaps */
	"4",	"ɾ",	// alveolar
	"l\\",	"ɺ",	// alveolar  lateral 
	"r`",	"ɽ",	// retroflex

	/* Clicks */
	"|\\|\\", "ǁ",	// aveolar lateral
	"O\\",	"ʘ",	// bilabial
	"|\\",	"ǀ",	// dental
	"=\\",	"ǂ",	// palatal
	"!\\",	"ǃ",	// postalveolar

	/* Other */
	"?",	"ʔ",	// glottal stop

	/* Nasals */
	"n",	"n",	// alveolar  
	"m",	"m",	// bilabial  
	"F",	"ɱ",	// labiodental
	"J",	"ɲ",	// palatal
	"n`",	"ɳ",	// retroflex 
	"N\\",	"ɴ",	// uvular
	"N",	"ŋ",	// velar

	/* Symbols */
	".",	".",	// syllable break
	"\"",	"ˈ",	// primary stress
	"%",	"ˌ",	// secondary stress
	"'",	"ʲ",	// palatalized
	":",	"ː",	// long
	":\\",	"ˑ",	// half long
	"^",	"ꜛ",	// upstep
	"!",	"ꜜ",	// downstep
	"|",	"|",	// minor (foot) group
	"||",	"‖",	// major (intonation) group
	"-\\",	"‿",	// linking mark
	// TODO separator
};

const int size = (sizeof(map)/sizeof(map[0])) >> 1;
char buf[27];
char next;
int p = 0;

void loop()
{
   char c = getchar();	
   printf("\b \b");
							// prints "X"
   buf[p] = c;				// 'X', p = 0, buf = "X"
   buf[p + 1] = '\0';		// p = 0, buf = "X\0"
   p++;						// p = 1
   if(c != '`' && c != '\\' && c != '_')
   {
		if(p > 1)
		{
			next = buf[p - 1];	// save the next char
			buf[p - 1] = '\0';
			for(int i = 0; i < size; i += 2)
			{
				if(strcmp(map[i], buf) == 0)
				{
					printf("[%dD[0K%s", p - 1 , map[i + 1]); 
					break;
				}
			}
			p = 1;
			buf[0] = next;
			printf("%c", next);
			buf[1] = '\0';
		}
		else
		{
			printf("%c", c);
		}
   }
   fflush(stdout);
   loop();
}

int main()
{
   struct termios old, new;
   tcgetattr(0, &old);
   new = old;
   new.c_lflag &= ~ICANON;
   tcsetattr(0, TCSANOW, &new);
   loop();
   tcsetattr(0, TCSANOW, &old);
   return 0;
}
