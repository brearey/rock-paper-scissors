// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUF_MAX 4096

typedef struct player {
  char* name;
  int score;
  int curr_elem_ind;
} player;

int get_random_ind() {
  srand(time(NULL));
  int random_ind = rand() % 3;
  return random_ind;
}

void init_game(player* p1, player* p2, unsigned int* lvl_count) {
  printf("How many levels do you want\n");
  scanf("%d", lvl_count);
  printf("What is your name?\n");
  char tmp_name[BUF_MAX];
  scanf("%s", tmp_name);
  p1->name = malloc(strlen(tmp_name) + 1);
  strcpy(p1->name, tmp_name);
  p1->score = 0;
  p1->curr_elem_ind = -1;

  p2->name = "Computer";
  p2->score = 0;
  p2->curr_elem_ind = -1;

  printf("Game is beginning: %s vs %s\n", p1->name, p2->name);
}

void next_round(player* p1, player* p2) {
  char* elements[3];
  elements[0] = "Stone";
  elements[1] = "Cutter";
  elements[2] = "Paper";

  printf("Your voice? Please enter a number\n");
  for (int i = 0; i < 3; i++) {
    printf("%d. %s\n", i, elements[i]);
  }
  scanf("%d", &(p1->curr_elem_ind));
  if (p1->curr_elem_ind > 2 || p1->curr_elem_ind < 0) {
    fprintf(stderr, "Incorrect number");
    exit(1);
  }
  p2->curr_elem_ind = get_random_ind();
  printf("%s's choice is %s\n", p2->name, elements[p2->curr_elem_ind]);
}

void print_round_res(int status, player p1, player p2) {
  // 1 - p1 win
  // 2 - p2 win
  // 3 - equal
  if (status == 1) {
    printf("%s win\n", p1.name);
  }
  if (status == 2) {
    printf("%s win\n", p2.name);
  }
  if (status == 3) {
    printf("%s and %s equal\n", p1.name, p2.name);
  }
}

void who_win_round(player* p1, player* p2) {
  if (p1->curr_elem_ind == 0 && p2->curr_elem_ind == 0) {
    print_round_res(3, *p1, *p2);
  } else if (p1->curr_elem_ind == 0 && p2->curr_elem_ind == 1) {
    print_round_res(1, *p1, *p2);
    p1->score += 1;
  } else if (p1->curr_elem_ind == 0 && p2->curr_elem_ind == 2) {
    print_round_res(2, *p1, *p2);
    p2->score += 1;
  } else if (p1->curr_elem_ind == 1 && p2->curr_elem_ind == 0) {
    print_round_res(2, *p1, *p2);
    p2->score += 1;
  } else if (p1->curr_elem_ind == 1 && p2->curr_elem_ind == 1) {
    print_round_res(3, *p1, *p2);
  } else if (p1->curr_elem_ind == 1 && p2->curr_elem_ind == 2) {
    print_round_res(1, *p1, *p2);
    p1->score += 1;
  } else if (p1->curr_elem_ind == 2 && p2->curr_elem_ind == 0) {
    print_round_res(1, *p1, *p2);
    p1->score += 1;
  } else if (p1->curr_elem_ind == 2 && p2->curr_elem_ind == 1) {
    print_round_res(2, *p1, *p2);
    p2->score += 1;
  } else if (p1->curr_elem_ind == 2 && p2->curr_elem_ind == 2) {
    print_round_res(3, *p1, *p2);
  }
}

void who_win_game(player p1, player p2) {
  printf("=======================\n");
  if (p1.score > p2.score) {
    printf("%s win the game with score %d\n", p1.name, p1.score);
  } else {
    printf("%s win the game with score %d\n", p2.name, p2.score);
  }
}

int main(void) {
  player p1, p2;
  unsigned int lvl_count;

  init_game(&p1, &p2, &lvl_count);
  for (unsigned int i = 0; i < lvl_count; i++) {
    next_round(&p1, &p2);
    who_win_round(&p1, &p2);
  }
  who_win_game(p1, p2);

  return 0;
}