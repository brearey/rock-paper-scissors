#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "locale.h"

#define BUF_MAX 4096

typedef struct game {
  int error;
  int end;
  int round_cnt;
  int alloc_cnt;
} game;

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

void init_game(player* p1, player* p2, game* g) {
  g->alloc_cnt = 0;
  printf(how_many_levels);
  if (scanf("%d", &(g->round_cnt)) != 1) {
    fprintf(stderr, incorrect_number);
    g->error = 1;
    return;
  }
  printf(your_name);
  char tmp_name[BUF_MAX];
  scanf("%s", tmp_name);
  p1->name = mem_alloc(&(g->alloc_cnt), tmp_name);
  strcpy(p1->name, tmp_name);
  p1->score = 0;
  p1->curr_elem_ind = -1;

  p2->name = computer;
  p2->score = 0;
  p2->curr_elem_ind = -1;

  printf(game_begin, p1->name, p2->name);
}

void next_round(player* p1, player* p2, game* g) {
  char* elements[3];
  elements[0] = rock;
  elements[1] = scissors;
  elements[2] = paper;

  printf(your_choice);
  for (int i = 0; i < 3; i++) {
    printf("%d. %s\n", i, elements[i]);
  }
  if (scanf("%d", &(p1->curr_elem_ind)) != 1) {
    fprintf(stderr, incorrect_number);
    g->error = 1;
    return;
  }
  if (p1->curr_elem_ind > 2 || p1->curr_elem_ind < 0) {
    fprintf(stderr, incorrect_number);
    g->error = 1;
    return;
  }
  p2->curr_elem_ind = get_random_ind();
  printf(choice_is, p2->name, elements[p2->curr_elem_ind]);
  g->round_cnt--;
}

void print_round_res(int status, player p1, player p2) {
  // 1 - p1 win
  // 2 - p2 win
  // 3 - standoff
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
  game g;
  player p1, p2;

  init_game(&p1, &p2, &g);
  while (g.error == 0 && g.end == 0 && g.round_cnt != 0) {
    next_round(&p1, &p2, &g);
    who_win_round(&p1, &p2);
  }
  who_win_game(p1, p2);
  mem_free(&(g.alloc_cnt), p1.name);
  return 0;
}