class BlaReader;
class STLightItem {
friend class STLight;
protected:
        STLightItem* next;
        const char* son;
        STLightItem(const char* s, STLightItem* n){
                son = s; next = n;      
        }
};
class STLight {
        static const int hash_size = 51;
        STLightItem* hash_table[hash_size];
        int hash_code(const char* nme);
public:
        STLight(){
                int i;
                for(i = 0; i < hash_size; i++){
                        hash_table[i] = (STLightItem*)NULL;
                }
        }
        const char* find(const char* nme);
        const char* add(const char* nme);
};
enum BlaItem {
                BLA_EOF,
                BLA_INT,
                BLA_FLOAT,
                BLA_PRAGMA,
                BLA_END_PRAGMA,
                BLA_STRING,
                BLA_ERROR,
        NB_BlaItem
};
class BlaReader {
        FILE* infile;
        int (*infunction)();
        STLight* pragmas;
        char buffer[1024];
        BlaItem curitem;
        int cur_char;
        int get_char_buff_cpt;
        int get_char_buff[5];
        void get_char(){
                if(get_char_buff_cpt){
                        cur_char = get_char_buff[--get_char_buff_cpt];
                } else {
                        cur_char = (infile)? fgetc(infile) : (*infunction)();
                }
        }
        void unget_and_restore(int c){
                get_char_buff[get_char_buff_cpt++] = cur_char;
                cur_char = c;
        }
        const char* curpragma;
        int par_pragma_mode;
        int line_pragma_mode;
        void ignore_line();
        void ignore_comment();
public:
        const char* version(){ return "1"; }
        BlaReader(int (*f)());
        BlaReader(FILE* in);
        BlaReader();
        const char* item_name(BlaItem it);
        const char* add_pragma(const char* prag);
        BlaItem get();
        BlaItem get(const char** val);
        BlaItem cur_item();
        const char* cur_string();
};
enum RifItem {
           RIF_EOF,
           RIF_VALUE,
           RIF_ERROR,
           RIF_PROGRAM,
           RIF_RESET,
           RIF_STEP,
           RIF_INPUTS,
           RIF_OUTPUTS,
           RIF_LOCALS,
           RIF_BEGIN_OUTS,
           RIF_END_OUTS,
           RIF_BEGIN_LOCS,
           RIF_END_LOCS,
        NB_RifItem
};
class RifReader : public BlaReader {
        const char* vers;
        char error_buff[1024];
        const char* reset_pragma;
        RifItem parse_reset_pragma();
        const char* program_pragma;
        const char* pname;
        RifItem parse_program_pragma();
        const char* step_pragma;
        int stepcpt;
        RifItem parse_step_pragma();
        STLight* idents;
        const char* inputs_pragma;
        int nbins;
        const char** innames;
        const char** intypes;
        RifItem parse_inputs_pragma();
        const char* outputs_pragma;
        int nbouts;
        const char** outnames;
        const char** outtypes;
        RifItem parse_outputs_pragma();
        const char* outs_pragma;
        const char* locals_pragma;
        int nblocs;
        const char** locnames;
        const char** loctypes;
        RifItem parse_locals_pragma();
        const char* locs_pragma;
public:
        const char* rif_version() { return "0"; }
        const char* version();
        RifReader();
        RifReader(FILE* inf);
        RifReader(int (*f)() );
        RifItem get();
        const char* item_name(RifItem it);
        const char* error_msg();
        const char* cur_value();
        int is_bool_value(const char* v);
        int is_bool_value(const char* v, int* res);
        int is_int_value(const char* v);
        int is_int_value(const char* v, long* res);
        int is_real_value(const char* v);
        int is_real_value(const char* v, double* res);
        int is_bottom_value(const char* v);
        void add_program_pragma();
        const char* program_name();
        void add_reset_pragma();
        void add_step_pragma();
        int step();
        void add_inputs_pragma();
        int nb_inputs();
        const char* input_name(int i);
        const char* input_type(int i);
        void add_outputs_pragma();
        int nb_outputs();
        const char* output_name(int i);
        const char* output_type(int i);
        void add_outs_pragma();
        void add_locals_pragma();
        int nb_locals();
        const char* local_name(int i);
        const char* local_type(int i);
        void add_locs_pragma();
};
