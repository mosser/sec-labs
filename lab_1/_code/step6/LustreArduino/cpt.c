/********
* ec2c version 0.67
* c file generated for node : cpt 
* context   method = HEAP
* ext call  method = PROCEDURES
********/
#include <stdlib.h>
#include <string.h>
#define _cpt_EC2C_SRC_FILE
#include "cpt.h"
/*--------
Internal structure for the call
--------*/
typedef struct  {
   void* client_data;
   //INPUTS
   _boolean _reset;
   //OUTPUTS
   _boolean _led_on;
   //REGISTERS
   _boolean M6;
   _boolean M6_nil;
   _boolean M2;
} cpt_ctx;
/*--------
Output procedures must be defined,
Input procedures must be used:
--------*/
void cpt_I_reset(cpt_ctx* ctx, _boolean V){
   ctx->_reset = V;
}
extern void cpt_O_led_on(void* cdata, _boolean);
#ifdef CKCHECK
extern void cpt_BOT_led_on(void* cdata);
#endif
/*--------
Internal reset input procedure
--------*/
static void cpt_reset_input(cpt_ctx* ctx){
   //NOTHING FOR THIS VERSION...
}
/*--------
Reset procedure
--------*/
void cpt_reset(cpt_ctx* ctx){
   ctx->M6_nil = _true;
   ctx->M2 = _true;
   cpt_reset_input(ctx);
}
/*--------
Copy the value of an internal structure
--------*/
void cpt_copy_ctx(cpt_ctx* dest, cpt_ctx* src){
   memcpy((void*)dest, (void*)src, sizeof(cpt_ctx));
}
/*--------
Dynamic allocation of an internal structure
--------*/
cpt_ctx* cpt_new_ctx(void* cdata){
   cpt_ctx* ctx = (cpt_ctx*)calloc(1, sizeof(cpt_ctx));
   ctx->client_data = cdata;
   cpt_reset(ctx);
   return ctx;
}
/*--------
Step procedure
--------*/
void cpt_step(cpt_ctx* ctx){
//LOCAL VARIABLES
   _boolean L5;
   _boolean L1;
   _boolean T6;
//CODE
   L5 = (! ctx->M6);
   if (ctx->M2) {
      L1 = _false;
   } else {
      L1 = L5;
   }
   cpt_O_led_on(ctx->client_data, L1);
   T6 = L1;
   ctx->M6 = T6;
   ctx->M6_nil = _false;
   ctx->M2 = ctx->M2 && !(_true);
}
