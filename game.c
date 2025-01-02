#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "locale.h"

#define BUF_MAX 4096

typedef struct player {
  char* name;
  int score;
  int curr_elem_ind;
} player;

void* mem_alloc(int* alloc_cnt, void* obj) {
  void* res = malloc(strlen(obj) + 1);
  if (res != NULL) (*alloc_cnt)++;
  return res;
}

void mem_free(int* alloc_cnt, void* obj) {
  if (obj != NULL) (*alloc_cnt)--;
  free(obj);
}

int get_random_ind() {
  srand(time(NULL));
  int random_ind = rand() % 3;
  return random_ind;
}

void init_game(player* p1, player* p2, unsigned int* lvl_count,
               int* alloc_cnt) {
  printf(how_many_levels);
  scanf("%d", lvl_count);
  printf(your_name);
  char tmp_name[BUF_MAX];
  scanf("%s", tmp_name);
  // p1->name = malloc(strlen(tmp_name) + 1);
  p1->name = mem_alloc(alloc_cnt, tmp_name);
  strcpy(p1->name, tmp_name);
  p1->score = 0;
  p1->curr_elem_ind = -1;

  p2->name = computer;
  p2->score = 0;
  p2->curr_elem_ind = -1;

  printf(game_begin, p1->name, p2->name);
}

void next_round(player* p1, player* p2) {
  char* elements[3];
  elements[0] = rock;
  elements[1] = scissors;
  elements[2] = paper;

  printf(your_choice);
  for (int i = 0; i < 3; i++) {
    printf("%d. %s\n", i, elements[i]);
  }
  scanf("%d", &(p1->curr_elem_ind));
  if (p1->curr_elem_ind > 2 || p1->curr_elem_ind < 0) {
    fprintf(stderr, incorrect_number);
    exit(1);
  }
  p2->curr_elem_ind = get_random_ind();
  printf(choice_is, p2->name, elements[p2->curr_elem_ind]);
}

void print_round_res(int status, player p1, player p2) {
  // 1 - p1 win
  // 2 - p2 win
  // 3 - equal
  if (status == 1) {
    printf(win, p1.name);
  }
  if (status == 2) {
    printf(win, p2.name);
  }
  if (status == 3) {
    printf(players_identical, p1.name, p2.name);
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
    printf(win_with_score, p1.name, p1.score);
  } else if (p1.score == p2.score) {
    printf(standoff);
  } else {
    printf(win_with_score, p2.name, p2.score);
  }
}

int main(void) {
  int alloc_cnt = 0;
  player p1, p2;
  unsigned int lvl_count;

  init_game(&p1, &p2, &lvl_count, &alloc_cnt);
  for (unsigned int i = 0; i < lvl_count; i++) {
    next_round(&p1, &p2);
    who_win_round(&p1, &p2);
  }
  who_win_game(p1, p2);
  mem_free(&alloc_cnt, p1.name);
  return 0;
}