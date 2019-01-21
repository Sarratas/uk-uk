#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <termios.h>

#include "utils.h"
#include "display/display_utils.h"
#include "display/display_map.h"
#include "display/display_player.h"
#include "control/moves.h"

int main(int argc, char *argv[])
{
    queue *controls_queue = get_queue();
    void *queue_pointer = get_shared_memory(sizeof(*controls_queue));
    memcpy(queue_pointer, controls_queue, sizeof(*controls_queue));
    char matrix[HEIGTH][WIDTH] = {{0}, {0}};
    matrix[HEIGTH - 1][WIDTH / 2] = 'X';
    void *matrix_pointer = get_shared_memory((size_t)(HEIGTH * WIDTH));
    memcpy(matrix_pointer, matrix, (size_t)(HEIGTH * WIDTH));

    points_state_ammo data;
    void *state_pointer = get_shared_memory(sizeof(points_state_ammo));
    memcpy(state_pointer, &data, sizeof(int));

    static struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    pid_t pid[3];

    pid[0] = fork();
    if (pid[0] == 0)
    {
        display_map_thread((char **)(matrix_pointer), (points_state_ammo *)state_pointer);
    }
    else if (pid[0] == -1)
        return 0;

    pid[1] = fork();
    if (pid[1] == 0)
    {
        controls_thread(queue_pointer, (points_state_ammo *)state_pointer);
    }
    else if (pid[0] == -1)
        return 0;

    pid[2] = fork();
    if (pid[2] == 0)
    {
        display_player_thread(queue_pointer, (char **)(matrix_pointer), (points_state_ammo *)state_pointer);
    }
    else if (pid[2] == -1)
        return 0;

    waitpid(pid[0], NULL, 0);
    waitpid(pid[1], NULL, 0);
    waitpid(pid[2], NULL, 0);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return 0;
}
