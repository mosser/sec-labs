/********
* ec2c version 0.67
* context   method = HEAP
* ext call  method = PROCEDURES
* c header file generated for node : cpt 
* to be used with : cpt.c 
********/
#ifndef _cpt_EC2C_H_FILE
#define _cpt_EC2C_H_FILE
/*-------- Predefined types ---------*/
#ifndef _EC2C_PREDEF_TYPES
#define _EC2C_PREDEF_TYPES
typedef int _boolean;
typedef int _integer;
typedef char* _string;
typedef double _real;
typedef double _double;
typedef float _float;
#define _false 0
#define _true 1
#endif
/*--------- Pragmas ----------------*/
//MODULE: cpt 1 1
//IN: _boolean reset
//OUT: _boolean led_on
#ifndef _cpt_EC2C_SRC_FILE
/*--------Context type -------------*/
struct cpt_ctx;
/*-------- Input procedures -------------*/
extern void cpt_I_reset(struct cpt_ctx* ctx, _boolean);
/*-------- Reset procedure -----------*/
extern void cpt_reset(struct cpt_ctx* ctx);
/*--------Context copy -------------*/
extern void cpt_copy_ctx(struct cpt_ctx* dest, struct cpt_ctx* src);
/*--------Context allocation --------*/
extern struct cpt_ctx* cpt_new_ctx(void* client_data);
/*-------- Step procedure -----------*/
extern void cpt_step(struct cpt_ctx* ctx);
#endif
#endif
