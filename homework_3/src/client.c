#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include "common.h"

void print_usage() {
  printf("Usage: ./client {ADD/SUB/MUL/DIV} {a} {b}\n");
}

void send_to_queue(int msgqid, calc_req *req) {
  calc_res  buff;
  size_t    msgsz;

  msgsnd(msgqid, req, sizeof(*req), 0);
  while (1) {
    msgsz = msgrcv(msgqid, &buff, sizeof(buff), CALC_RES, MSG_NOERROR);
    if (msgsz == sizeof(buff)) {
      if (buff.res_id == req->res_id) {
        printf("%ld\n", buff.result);
        return;
      } else {
        buff.ttl -= 1;
        if (buff.ttl > 0) {
          msgsnd(msgqid, &buff, sizeof(buff), 0);
        }
      }
    }
  }
}

int do_ipc(calc_req *req) {
  key_t tok;
  int   msgqid;

  tok = ftok(IPC_PATH, IPC_PROJ_ID);
  if (tok == -1) {
    perror("Failed to do ftok");
    return 1;
  }
  msgqid = msgget(tok, IPC_CREAT|0600);
  if (msgqid == -1) {
    perror("Failed to do msgget");
    return 1;
  }
  send_to_queue(msgqid, req);
  return 0;
}

int main(int ac, char **av) {
  calc_req  req;

  if (ac != 4) {
    print_usage();
    return 1;
  }

  req.mtype = CALC_REQ;
  srand(time(NULL) + getpid() + clock());
  req.res_id = rand();
  req.a = atol(av[2]);
  req.b = atol(av[3]);
  if (strcmp(av[1], "ADD") == 0) {
    req.calc = CALC_ADD;
  } else if (strcmp(av[1], "SUB") == 0) {
    req.calc = CALC_SUB;
  } else if (strcmp(av[1], "MUL") == 0) {
    req.calc = CALC_MUL;
  } else if (strcmp(av[1], "DIV") == 0) {
    req.calc = CALC_DIV;
  } else {
    printf("Unknow calcul %s\n", av[1]);
    print_usage();
    return 1;
  }
  return do_ipc(&req);
}
