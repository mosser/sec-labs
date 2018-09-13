class EcExe;
class EvalItem;
class EvalItemList;
#define NotInitialized  1
#define NotComputed  2
#define DivisionByZero  4
#define ArithmeticOverflow  8
union CValue {
        int bool_v;
        int int_v;
        double double_v;
        const char* extern_v;
};
enum EvalItemType {
        EI_UNKNOWN_TYPE,
        EI_BOOL_TYPE,
        EI_INT_TYPE,
        EI_REAL_TYPE,
        EI_EXTERN_TYPE
};
class EvalItem {
public:
        virtual ~EvalItem(){}
        int arity;
        EvalItem** operands;
        EvalItemType typ;
        CValue val;
        int nil;
        EvalItemType type(){ return typ;};
        void set_nil(int code){ nil = code;}
        void set_bool_value(int b){ val.bool_v = b; nil = 0; }  
        void set_int_value(int i){ val.int_v = i; nil = 0; }
        void set_double_value(double f){ val.double_v = f; nil = 0; }
        void set_extern_value(const char* e){ val.extern_v = e; nil = 0; }
        int is_nil(){ return nil;};
        int bool_value(){ return val.bool_v; };
        int int_value(){ return val.int_v; };
        double double_value(){ return val.double_v; };
        const char* extern_value(){ return val.extern_v; };
        static int counter;
        int index;
        int unique_index(){ return index; }
        EvalItem(EvalItemType t, int ar){
                        index = EvalItem::counter++;
                        typ = t;
                        arity = ar;
                        operands = new EvalItem*[ar];
                        nil = 1;
                        rec_mark = 0;
        }
        void set_operand(int index, EvalItem* op){
                operands[index] = op;
        }
        int rec_mark;
        int marked(int cur_step){ return (rec_mark == cur_step); }
        void mark(int cur_step){ rec_mark = cur_step; }
        void reset_mark(int mark);
        void reset();
        virtual void local_reset(){}
        void eval(int cur_step){
                if(marked(cur_step)) return;
                mark(cur_step);
                compute(cur_step);
        }
        virtual void compute(int /*cur_step*/){
                Error("EvalItem::compute is only virtual\n");
        }
        virtual void compute_next(int /*cur_step*/){
                Error("EvalItem::compute_next only virtual\n");
        }
        virtual void rewrite(){
                Error("EvalItem::rewrite only virtual\n");
        }
        virtual int is_bottom(){
                //Error("EvalItem::is_bottom only virtual\n");
                return 0;
        }
virtual int extern_type_name(){
        Warning("EvalItem:extern_type_name: called on non extern type");
        return -1;
}
        int* bool_res(){ return &(val.bool_v); }
        int* int_res(){ return &(val.int_v); }
        double* double_res(){ return &(val.double_v); }
        const char** extern_res(){ return &(val.extern_v); }
        void* loc_res(){
                switch(typ){
                        case EI_UNKNOWN_TYPE:
                                return NULL;
                        break;
                        case EI_BOOL_TYPE:
                                return (void*)(bool_res());
                        break;
                        case EI_INT_TYPE:
                                return (void*)(int_res());
                        break;
                        case EI_REAL_TYPE:
                                return (void*)(double_res());
                        break;
                        case EI_EXTERN_TYPE:
                                return (void*)(extern_res());
                        break;
                }
                return NULL;
        }
};
class CONST_bool_EI : public EvalItem {
        virtual ~CONST_bool_EI(){}
public :
        CONST_bool_EI(int val):EvalItem(EI_BOOL_TYPE, 0){set_bool_value(val); }
        void local_reset(){ set_bool_value(bool_value()); }
        void compute(int /*cur_step*/){}
};
class CONST_int_EI : public EvalItem {
        virtual ~CONST_int_EI(){}
public :
        CONST_int_EI(int val):EvalItem(EI_INT_TYPE, 0){ set_int_value(val); }
        void local_reset(){ set_int_value(int_value()); }
        void compute(int /*cur_step*/){}
};
class CONST_double_EI : public EvalItem {
        virtual ~CONST_double_EI(){}
public :

        CONST_double_EI(double val):EvalItem(EI_REAL_TYPE, 0){ set_double_value(val); }
        void local_reset(){ set_double_value(double_value()); }
        void compute(int /*cur_step*/){}
};
class CONST_extern_EI : public EvalItem {
        virtual ~CONST_extern_EI(){}
        int type_ident;
public :
        CONST_extern_EI(const char* val, int ty):EvalItem(EI_EXTERN_TYPE, 0){
                set_extern_value(val); 
                type_ident = ty;
        }
        int extern_type_name(){ return type_ident; }
        void local_reset(){ set_extern_value(extern_value()); }
        void compute(int /*cur_step*/){}
};
class INIT_bool_EI : public EvalItem {
        virtual ~INIT_bool_EI(){}
        int next_value;
public :
        INIT_bool_EI():EvalItem(EI_BOOL_TYPE, 1){
                next_value = 1;
        }
        void local_reset(){ next_value = 1; }
        void compute(int cur_step);
        void compute_next(int cur_step);
        void rewrite();
};
class BLAST_bool_EI : public EvalItem {
        virtual ~BLAST_bool_EI(){}
        int next_nil;
        int next_value;
public :
        BLAST_bool_EI():EvalItem(EI_BOOL_TYPE, 2){
                next_nil = NotInitialized;
        }
        void local_reset(){ next_nil = NotInitialized; }
        void compute(int cur_step);
        void compute_next(int cur_step);
        void rewrite();
};
class BLAST_int_EI : public EvalItem {
        virtual ~BLAST_int_EI(){}
        int next_nil;
        int next_value;
public :
        BLAST_int_EI():EvalItem(EI_INT_TYPE, 2){
                next_nil = NotInitialized;
        }
        void local_reset(){ next_nil = NotInitialized; }
        void compute(int cur_step);
        void compute_next(int cur_step);
        void rewrite();
};

class BLAST_double_EI : public EvalItem {
        virtual ~BLAST_double_EI(){}
        int next_nil;
        double next_value;
public :
        BLAST_double_EI():EvalItem(EI_REAL_TYPE, 2){
                next_nil = NotInitialized;
        }
        void local_reset(){ next_nil = NotInitialized; }
        void compute(int cur_step);
        void compute_next(int cur_step);
        void rewrite();
};
class BLAST_extern_EI : public EvalItem {
        virtual ~BLAST_extern_EI(){}
        int next_nil;
        const char* next_value;
        int type_ident;
public :
        BLAST_extern_EI(int ty):EvalItem(EI_EXTERN_TYPE, 2){
                next_nil = NotInitialized;
                type_ident = ty;
        };
        int extern_type_name(){ return type_ident; }
        void local_reset(){ next_nil = NotInitialized; };
        void compute(int cur_step);
        void compute_next(int cur_step);
        void rewrite();
};
class OUTPUT_bool_EI : public EvalItem {
        virtual ~OUTPUT_bool_EI(){}
        int bottom;
public :
        OUTPUT_bool_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
        int is_bottom();
};
class OUTPUT_int_EI : public EvalItem {
        virtual ~OUTPUT_int_EI(){}
        int bottom;
public :
        OUTPUT_int_EI():EvalItem(EI_INT_TYPE, 2){}
        void compute(int cur_step);
        int is_bottom();
};
class OUTPUT_double_EI : public EvalItem {
        virtual ~OUTPUT_double_EI(){}
        int bottom;
public :
        OUTPUT_double_EI():EvalItem(EI_REAL_TYPE, 2){}
        void compute(int cur_step);
        int is_bottom();
};
class OUTPUT_extern_EI : public EvalItem {
        virtual ~OUTPUT_extern_EI(){}
        int bottom;
        int type_ident;
public :
        OUTPUT_extern_EI(int ty):EvalItem(EI_EXTERN_TYPE, 2){
                type_ident = ty;
        }
        int extern_type_name(){ return type_ident; }
        void compute(int cur_step);
        int is_bottom();
};
class INPUT_bool_EI : public EvalItem {
        virtual ~INPUT_bool_EI(){}
        int name;
public :
        INPUT_bool_EI(int nme):EvalItem(EI_BOOL_TYPE, 0){name = nme; }
        void compute(int /*cur_step*/){ set_bool_value(bool_value()); }
};
class INPUT_int_EI : public EvalItem {
        virtual ~INPUT_int_EI(){}
        int name;
public :
        INPUT_int_EI(int nme):EvalItem(EI_INT_TYPE, 0){name = nme; }
        void compute(int /*cur_step*/){ set_int_value(int_value()); }
};
class INPUT_double_EI : public EvalItem {
        virtual ~INPUT_double_EI(){}
        int name;
public :
        INPUT_double_EI(int nme):EvalItem(EI_REAL_TYPE, 0){ name = nme;}
        void compute(int /*cur_step*/){ set_double_value(double_value()); }
};
class INPUT_extern_EI : public EvalItem {
        virtual ~INPUT_extern_EI(){}
        int name;
        int type_ident;
public :
        INPUT_extern_EI(int nme, int ty):EvalItem(EI_EXTERN_TYPE, 0){
                name = nme;
                type_ident = ty;
        }
        int extern_type_name(){ return type_ident; }
        void compute(int /*cur_step*/){ set_extern_value(extern_value()); }
};
class EQ_bool_EI : public EvalItem {
        virtual ~EQ_bool_EI(){}
public :
        EQ_bool_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};
class NE_bool_EI : public EvalItem {
        virtual ~NE_bool_EI(){}
public :
        NE_bool_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};
class COND_bool_EI : public EvalItem {
        virtual ~COND_bool_EI(){}
public :
        COND_bool_EI():EvalItem(EI_BOOL_TYPE, 3){}
        void compute(int cur_step);
};
class AND_bool_EI : public EvalItem {
        virtual ~AND_bool_EI(){}
public :
        AND_bool_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};
class OR_bool_EI : public EvalItem {
        virtual ~OR_bool_EI(){}
public :
        OR_bool_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};
class IMPL_bool_EI : public EvalItem {
        virtual ~IMPL_bool_EI(){}
public :
        IMPL_bool_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};
class NOT_bool_EI : public EvalItem {
        virtual ~NOT_bool_EI(){}
public :
        NOT_bool_EI():EvalItem(EI_BOOL_TYPE, 1){}
        void compute(int cur_step);
};
class DIESE_bool_EI : public EvalItem {
        virtual ~DIESE_bool_EI(){}
public :
        DIESE_bool_EI(int ar):EvalItem(EI_BOOL_TYPE, ar){}
        void compute(int cur_step);
};
class NOR_bool_EI : public EvalItem {
        virtual ~NOR_bool_EI(){}
public :
        NOR_bool_EI(int ar):EvalItem(EI_BOOL_TYPE, ar){}
        void compute(int cur_step);
};
class EQ_int_EI : public EvalItem {
        virtual ~EQ_int_EI(){}
public :
        EQ_int_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};
class NE_int_EI : public EvalItem {
        virtual ~NE_int_EI(){}
public :
        NE_int_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};

class COND_int_EI : public EvalItem {
        virtual ~COND_int_EI(){}
public :
        COND_int_EI():EvalItem(EI_INT_TYPE, 3){}
        void compute(int cur_step);
};

class LT_int_EI : public EvalItem {
        virtual ~LT_int_EI(){}
public :
        LT_int_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};

class LE_int_EI : public EvalItem {
        virtual ~LE_int_EI(){}
public :
        LE_int_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};

class GT_int_EI : public EvalItem {
        virtual ~GT_int_EI(){}
public :
        GT_int_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};

class GE_int_EI : public EvalItem {
        virtual ~GE_int_EI(){}
public :
        GE_int_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};

class PLUS_int_EI : public EvalItem {
        virtual ~PLUS_int_EI(){}
public :
        PLUS_int_EI():EvalItem(EI_INT_TYPE, 2){}
        void compute(int cur_step);
};

class MINUS_int_EI : public EvalItem {
        virtual ~MINUS_int_EI(){}
public :
        MINUS_int_EI():EvalItem(EI_INT_TYPE, 2){}
        void compute(int cur_step);
};

class TIMES_int_EI : public EvalItem {
        virtual ~TIMES_int_EI(){}
public :
        TIMES_int_EI():EvalItem(EI_INT_TYPE, 2){}
        void compute(int cur_step);
};

class MOD_int_EI : public EvalItem {
        virtual ~MOD_int_EI(){}
public :
        MOD_int_EI():EvalItem(EI_INT_TYPE, 2){}
        void compute(int cur_step);
};

class DIV_int_EI : public EvalItem {
        virtual ~DIV_int_EI(){}
public :
        DIV_int_EI():EvalItem(EI_INT_TYPE, 2){}
        void compute(int cur_step);
};

class UMINUS_int_EI : public EvalItem {
        virtual ~UMINUS_int_EI(){}
public :
        UMINUS_int_EI():EvalItem(EI_INT_TYPE, 1){}
        void compute(int cur_step);
};

class EQ_double_EI : public EvalItem {
        virtual ~EQ_double_EI(){}
public :
        EQ_double_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};

class NE_double_EI : public EvalItem {
        virtual ~NE_double_EI(){}
public :
        NE_double_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};

class COND_double_EI : public EvalItem {
        virtual ~COND_double_EI(){}
public :
        COND_double_EI():EvalItem(EI_REAL_TYPE, 3){}
        void compute(int cur_step);
};

class LT_double_EI : public EvalItem {
        virtual ~LT_double_EI(){}
public :
        LT_double_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};

class LE_double_EI : public EvalItem {
        virtual ~LE_double_EI(){}
public :
        LE_double_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};

class GT_double_EI : public EvalItem {
        virtual ~GT_double_EI(){}
public :
        GT_double_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};

class GE_double_EI : public EvalItem {
        virtual ~GE_double_EI(){}
public :
        GE_double_EI():EvalItem(EI_BOOL_TYPE, 2){}
        void compute(int cur_step);
};

class PLUS_double_EI : public EvalItem {
        virtual ~PLUS_double_EI(){}
public :
        PLUS_double_EI():EvalItem(EI_REAL_TYPE, 2){}
        void compute(int cur_step);
};

class MINUS_double_EI : public EvalItem {
        virtual ~MINUS_double_EI(){}
public :
        MINUS_double_EI():EvalItem(EI_REAL_TYPE, 2){}
        void compute(int cur_step);
};

class TIMES_double_EI : public EvalItem {
        virtual ~TIMES_double_EI(){}
public :
        TIMES_double_EI():EvalItem(EI_REAL_TYPE, 2){}
        void compute(int cur_step);
};

class DIV_double_EI : public EvalItem {
        virtual ~DIV_double_EI(){}
public :
        DIV_double_EI():EvalItem(EI_REAL_TYPE, 2){}
        void compute(int cur_step);
};

class UMINUS_double_EI : public EvalItem {
        virtual ~UMINUS_double_EI(){}
public :
        UMINUS_double_EI():EvalItem(EI_REAL_TYPE, 1){}
        void compute(int cur_step);
};
class EXTERNAL_CALL_EI : public EvalItem {
        virtual ~EXTERNAL_CALL_EI(){}
        int func_name;
public :
        EXTERNAL_CALL_EI(int f, int a):EvalItem(EI_UNKNOWN_TYPE, a){
                func_name = f;
        }
};
class INT2REAL_double_EI : public EvalItem {
        virtual ~INT2REAL_double_EI(){}
public :
        INT2REAL_double_EI():EvalItem(EI_REAL_TYPE, 1){}
        void compute(int cur_step);
};
class REAL2INT_int_EI : public EvalItem {
        virtual ~REAL2INT_int_EI(){}
public :
        REAL2INT_int_EI():EvalItem(EI_INT_TYPE, 1){}
        void compute(int cur_step);
};
typedef double (*D2D_ptr) (double);
typedef double (*DxD2D_ptr) (double, double);
typedef long int (*IxI2I_ptr) (long int, long int);
typedef int (*B2B_ptr) (int);
class UFUNC_double_EI : public EvalItem {
        virtual ~UFUNC_double_EI(){}
        D2D_ptr func;
public :
        UFUNC_double_EI(D2D_ptr f):EvalItem(EI_REAL_TYPE, 1){
                func = f;
        }
        void compute(int cur_step);
};
class UFUNC_bool_EI : public EvalItem {
        virtual ~UFUNC_bool_EI(){}
        B2B_ptr func;
public :
        UFUNC_bool_EI(B2B_ptr f):EvalItem(EI_BOOL_TYPE, 1){
                func = f;
        }
        void compute(int cur_step);
};
class BFUNC_double_EI : public EvalItem {
        virtual ~BFUNC_double_EI(){}
        DxD2D_ptr func;
public :
        BFUNC_double_EI(DxD2D_ptr f):EvalItem(EI_REAL_TYPE, 2){
                func = f;
        }
        void compute(int cur_step);
};
class BFUNC_int_EI : public EvalItem {
        virtual ~BFUNC_int_EI(){}
        IxI2I_ptr func;
public :
        BFUNC_int_EI(IxI2I_ptr f):EvalItem(EI_INT_TYPE, 2){
                func = f;
        }
        void compute(int cur_step);
};

class EQ_extern_EI : public EvalItem {
        virtual ~EQ_extern_EI(){}
        int type_ident;
public :
        EQ_extern_EI(int ty):EvalItem(EI_BOOL_TYPE, 2){
                type_ident = ty;
        }
        int extern_type_name(){ return type_ident; }
        void compute(int cur_step);
};

class NE_extern_EI : public EvalItem {
        virtual ~NE_extern_EI(){}
        int type_ident;
public :
        NE_extern_EI(int ty):EvalItem(EI_BOOL_TYPE, 2){
                type_ident = ty;
        }
        int extern_type_name(){ return type_ident; }
        void compute(int cur_step);
};

class COND_extern_EI : public EvalItem {
        virtual ~COND_extern_EI(){}
        int type_ident;
public :
        COND_extern_EI(int ty):EvalItem(EI_EXTERN_TYPE, 3){
                type_ident = ty;
        }
        int extern_type_name(){ return type_ident; }
        void compute(int cur_step);
};
class EvalItemList{
   EvalItem* val;
   EvalItemList* nxt;
        int _length;
public:
   EvalItem* head(){ return val; }
   EvalItemList* tail(){ return nxt; }
        int length(){ return _length;}
   EvalItemList(EvalItem* v, EvalItemList* n){
      val = v; nxt = n;
                _length = (nxt)? nxt->length()+1 : 1;
   }
};
enum EvalResult {
        BOTTOM_er,
        NIL_er,
        DIVZERO_er,
        TRUE_ASSERT_er,
        FALSE_ASSERT_er,
        VALUE_er,
        _nb_EvalResult
};
class EcExe : public NetInterface {
protected:
        int init_exe();
        int build_mark;
        int marked(Exp* e){
                return e->marked(build_mark);
        }
        void set_eval_item(Exp* e, EvalItem* i){
                e->mark(build_mark);
                e->put_info(build_mark, (void*)i);
        }
        EvalItem* get_eval_item(Exp* e){
                return (EvalItem*)e->get_ptr_info(build_mark);
        }
        EvalItem** local_items;
        EvalItem** output_items;
        EvalItem** assert_items;
        EvalItem** input_items;
        EvalItemList* state_item_list;
        EvalItem** state_items;
        int nb_state_items;
EvalItem* exp_to_eval_item(Exp* e);
int eval_mark;
int in_step;
public:
        EcExe(const char* ecfname, SymbolTable* st);
        EcExe();
        int init(const char* ecfname, SymbolTable* st);
int input_type(int i){
        return type(input(i))->name();
}
int output_type(int i){
        return type(output(i))->name();
}
int local_type(int i){
        return type(local(i))->name();
}
int nb_mem(){
        return state_item_list->length();
}

int* input_bool_loc(int ix){
        return (input_items[ix])->bool_res();
}
int* input_int_loc(int ix){
        return (input_items[ix])->int_res();
}
double* input_double_loc(int ix){
        return (input_items[ix])->double_res();
}
const char** input_extern_loc(int ix){
        return (input_items[ix])->extern_res();
}
void* input_loc(int ix){ return (input_items[ix])->loc_res(); }
int* output_bool_loc(int ix){
        return (output_items[ix])->bool_res();
}
int* output_int_loc(int ix){
        return (output_items[ix])->int_res();
}
double* output_double_loc(int ix){
        return (output_items[ix])->double_res();
}
const char** output_extern_loc(int ix){
        return (output_items[ix])->extern_res();
}
void* output_loc(int ix){ return (output_items[ix])->loc_res(); }

int* local_bool_loc(int ix){
        return (local_items[ix])->bool_res();
}
int* local_int_loc(int ix){
        return (local_items[ix])->int_res();
}
double* local_double_loc(int ix){
        return (local_items[ix])->double_res();
}
const char** local_extern_loc(int ix){
        return (local_items[ix])->extern_res();
}
void* local_loc(int ix){ return (local_items[ix])->loc_res(); }
void init_step(){ in_step = 1; eval_mark++; }
void end_step();
int abort_step();
EvalResult eval_output(int output_index){
        EvalItem* cur_out = output_items[output_index];
        cur_out->eval(eval_mark);
        if(cur_out->is_bottom()) return BOTTOM_er;
        else if (cur_out->is_nil() & DivisionByZero) return DIVZERO_er;
        else if (cur_out->is_nil()) return NIL_er;
        else return VALUE_er;
}
EvalResult eval_assert(int assert_index){
        EvalItem* cur_ass = assert_items[assert_index];
        cur_ass->eval(eval_mark);
        if(cur_ass->is_bottom()) return BOTTOM_er;
        else if (cur_ass->is_nil()) return NIL_er;
        else return (cur_ass->bool_value())?
                TRUE_ASSERT_er : FALSE_ASSERT_er;
}
EvalResult get_local_value(int local_index){
        EvalItem* locitem = local_items[local_index];
        if (locitem) {
                if(locitem->is_bottom()) return BOTTOM_er;
                else if (locitem->is_nil() & DivisionByZero) return DIVZERO_er;
                else if (locitem->is_nil()) return NIL_er;
                else return VALUE_er;
        } else {
                return BOTTOM_er;
        }
}
void reset_history();
};
