#define WIDTH 100
#define HEIGTH 50

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYNAN "\x1B[36m"
#define WHITE "\x1B[37m"

void clean_screen();
void printf_colour(char *, char);
void print_matrix(char[HEIGTH][WIDTH]);
int roll_matrix_and_rand_stones(char[HEIGTH][WIDTH], int);
void print_ammo_and_points(int, int);