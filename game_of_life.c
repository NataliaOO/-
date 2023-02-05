#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FIELD_WIDTH 80
#define FIELD_HEIGHT 25

#define SPEED 1000000

#define LIVE 1
#define DEAD 0

#define PICTURE_LIVE '*'
#define PICTURE_DEAD '.'

void init_field(int ***);
void fill_field(int **);

void load_picture(int **);
int copy_field(int **, int **);
void check(int **, int **);
int count_neighbours(int **, int, int);
void print_field(int **);

int getCountOne(int **);
void changeSpeed(int *);

int main() {
    int **field = NULL;
    int **new_gen_field = NULL;
    int speed = SPEED, identical_fields = 0;
    FILE *temp_garbage;

    init_field(&field);
    init_field(&new_gen_field);

    fill_field(field);
    load_picture(field);

    // вернуть поток обратно в консоль
    temp_garbage = freopen("/dev/tty", "r", stdin);
    changeSpeed(&speed);

    print_field(field);
    do {
        usleep(speed);
        check(field, new_gen_field);
        identical_fields = copy_field(field, new_gen_field);
        print_field(field);

    } while (getCountOne(field) != 0 && identical_fields);

    fclose(temp_garbage);
    free(new_gen_field);
    free(field);

    return 0;
}

void init_field(int ***field) {
    *field = malloc(FIELD_HEIGHT * FIELD_WIDTH * sizeof(int *) + FIELD_HEIGHT * sizeof(int));
    int *tmp = (int *)(*field + FIELD_HEIGHT);
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        (*field)[i] = tmp + i * FIELD_WIDTH;
    }
}

void fill_field(int **field) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            field[i][j] = DEAD;
        }
    }
}

void print_field(int **field) {
    printf("\033[H");
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (field[i][j] == LIVE)
                printf("%c", PICTURE_LIVE);
            else
                printf("%c", PICTURE_DEAD);
        }
        printf("\n");
    }
    fflush(stdout);
}

int copy_field(int **source, int **output) {
    int flag = 0;
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (source[i][j] != output[i][j]) flag = 1;
            source[i][j] = output[i][j];
        }
    }
    return flag;
}

void load_picture(int **matrix) {
    int i = 6, j = 20;
    char c;
    scanf("%c", &c);
    while (c != '/') {
        switch (c) {
            case '1':
                matrix[i][j++] = LIVE;
                break;
            case '0':
                j++;
                break;
            case '\n':
                j = 20;
                i++;
                break;
        }
        scanf("%c", &c);
    }
}

void check(int **field, int **new_gen_field) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            int count = count_neighbours(field, i, j);
            switch (count) {
                case 2:
                    new_gen_field[i][j] = field[i][j];
                    break;
                case 3:
                    new_gen_field[i][j] = LIVE;
                    break;
                default:
                    new_gen_field[i][j] = DEAD;
                    break;
            }
        }
    }
}

int count_neighbours(int **field, int i, int j) {
    int count = 0;
    for (int y = i - 1; y <= i + 1; y++) {
        for (int x = j - 1; x <= j + 1; x++) {
            count += field[(y + FIELD_HEIGHT) % (FIELD_HEIGHT)][(x + FIELD_WIDTH) % (FIELD_WIDTH)];
        }
    }
    count -= field[i][j];
    return count;
}

int getCountOne(int **field) {
    int count = 0;
    for (int i = 0; i < FIELD_HEIGHT; i++) {
        for (int j = 0; j < FIELD_WIDTH; j++) {
            if (field[i][j] == 1) count++;
        }
    }
    return count;
}

int getKey() {
    int key;
    scanf("%d", &key);
    if ((key < 1) && (key > 5)) key = 1;
    return key;
}

void changeSpeed(int *speed) {
    printf("Choose game speed from 1 to 5:\n");
    int key = getKey();
    switch (key) {
        case 1:
            *speed = 1000000;
            break;
        case 2:
            *speed = 500000;
            break;
        case 3:
            *speed = 250000;
            break;
        case 4:
            *speed = 100000;
            break;
        case 5:
            *speed = 50000;
            break;
    }
}
