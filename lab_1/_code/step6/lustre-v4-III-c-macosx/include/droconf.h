/*
Struct necessary for building a DRO archive
(Dynamically linkable Reactive Object)
Such an archive can be loaded by simec/luciole
*/
#define DROVERSION "1.1"
#define xstr(s) str(s)  /* converts macro to string */
#define str(s) #s
/* should be of type type dro_desc_t */
#define DRO_DESC_NAME  dro_desc
struct dro_var_t {
        const char* ident;
        const char* type;
        void* valptr;
};

struct dro_desc_t {
        const char* version;
        const char* name;
        int nbins;
        struct dro_var_t* intab;
        int nbouts;
        struct dro_var_t* outab;
        int ( *step )();
        void ( *reset )();
        void ( *init )();
}; 
