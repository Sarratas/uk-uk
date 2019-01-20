#define WIDTH 40
#define HEIGTH 20

#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLLOW "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYNAN   "\x1B[36m"
#define WHITE   "\x1B[37m"

void clean_screen();
void printf_colour(char *, char);