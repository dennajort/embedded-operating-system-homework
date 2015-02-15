#ifndef __COMMON_H__
#define __COMMON_H__

#define IPC_PATH  "/tmp"
#define IPC_PROJ_ID 4242

#define CALC_REQ  1
#define CALC_RES  2

#define CALC_ADD  0
#define CALC_SUB  1
#define CALC_MUL  2
#define CALC_DIV  3

typedef struct calc_req_s {
  long  mtype;
  long  res_id;
  short calc;
  long  a;
  long  b;
} calc_req;

typedef struct calc_res_s {
  long          mtype;
  long          res_id;
  unsigned int  ttl;
  long          result;
} calc_res;

#endif
