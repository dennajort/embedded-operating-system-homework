#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include "common.h"

void do_calc (int msgqid, calc_req *req) {
  calc_res  res;

  res.mtype = CALC_RES;
  res.res_id = req->res_id;
  res.ttl = 50;
  switch (req->calc) {
    case CALC_ADD:
      res.result = req->a + req->b;
      break;
    case CALC_SUB:
      res.result = req->a - req->b;
      break;
    case CALC_MUL:
      res.result = req->a * req->b;
      break;
    case CALC_DIV:
      if (req->b == 0) {
        res.result = 0;
      } else {
        res.result = req->a / req->b;
      }
      break;
    default:
      return;
  }
  msgsnd(msgqid, &res, sizeof(res), 0);
}

void process_queue(int msgqid) {
  calc_req  buff;
  size_t    msgsz;

  while (1) {
    msgsz = msgrcv(msgqid, &buff, sizeof(buff), CALC_REQ, MSG_NOERROR);
    if (msgsz == sizeof(buff)) {
      do_calc(msgqid, &buff);
    }
  }
}

int main() {
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
  process_queue(msgqid);
  return 0;
}
