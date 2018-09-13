class BlaReader;
class STLightItem {
friend class STLight;
protected:
        STLightItem* next;
        char* son;
        STLightItem(char* s, STLightItem* n){
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
        char* find(char* nme);
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
        char* curpragma;
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
        BlaItem get(char** val);
        BlaItem cur_item();
        char* cur_string();
};
