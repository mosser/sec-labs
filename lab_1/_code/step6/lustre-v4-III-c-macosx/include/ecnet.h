
/* -------------------------------------------------------------------------
 * Projet E C 2 O C
 * -------------------------------------------------------------------------
 * module   : net.h
 *
 * date     : 20/1/93
 * auteurs  : Pascal Raymond
 *--------------------------------------------------------------------------
 * nature   : Classes et structures necessaires a la representation
 *            interne du programme source.
 *--------------------------------------------------------------------------
 * Modifs   :
 *     - 17/2/93 : Definition d'une classe ExpSet : ExpList simplifiee
 *     (pas de gestion de la longeur) Cette classe est utilisee pour
 *     implementer la minimisation du reseau.
 *     - 11/3/93 : Toute la partie 'construction de reseau minimal'
 *     a lieu APRES NORMALISATION, ce travail est confie a la classe
 *     derivee NormNet.
 *     => LE CODE CORRESPONDANT A LA CONSTRUCTION D'UN RESEAU EC EST
 *     dans net_build.cc.OBS
 *     - 17/3/93 : Le calcul des types et des horloges des expressions
 *     n'est plus attache aux objets Exp, mais a l'objet Net qui gere
 *     celles-ci : en effet, pour inferer les types des expression
 *     tuple, proj et call, on a besoin d'informations que ne PEUVENT 
 *     pas connaitre les objet Exp.
 *--------------------------------------------------------------------------
 *  14 nars 94 : Nouveaux operateurs "RCL_n" et "ICL_n" 
 * (pour combinaison lineaire) 
 * 	operateurs tres speciaux : 
 *	(CL_n, arity, operands, coefs, cste) est equivalent a l'operation :
 *		sigma(pour i = 0 .. arity){coefs[i] * operands[i] } + cste 
 *	ou les coefs et spec_op sont des constantes instantanees.
 *
 *  16 janv 96 : Modif de "RCL_n" => devient une combinaison
 * RATIONNELLE  
 * -----------------------------------------------------------------------*/

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif
	
/*------------- CLASSES et STRUCTURES definies dans ce module ------------*/

class IntList;		// Liste d'entiers 
class IntIterator;	// "Macros" pour parcourir une liste d'entiers 
class EcType;		// 'Types' associes aux expressions du reseau
class IdentInfo;		// Informations associees aux ident. du prg.
class FuncInfo;		//       "         "      aux fonctions externes
class Exp; 			// Noeuds du reseau d'operateurs
class ExpList;
class ExpSet;
class Net;			// Representation abstraite du prg. source


/************************************************************************
	ExpNature : Nature des noeuds du reseau
-------------------------------------------------------------------------
	Chaque fois qu'on ajoute un operateur dans le type ExpNature,
il faut inserer dans OPKEYS la chaine correspondante AU MEME ENDROIT.
	S'il s'agit d'operateurs simples (unaire, binaires, infixes) il
faut les inserer a la fin des listes correspondantes, de maniere
a respecter les macros UnaryOp, BinaryOp et InfixedOp.
************************************************************************/

typedef unsigned long int Ptr2Ulong;

enum ExpNature { 
	ERROR_n ,
/* Feuilles */
	CONST_n ,
	INPUT_n ,
	ECREF_n ,
	MODELREF_n ,
/* Operateurs unaires */
	PRE_n ,
	CURRENT_n ,
	NOT_n ,
	UMINUS_n ,
	LAST_n,
	INIT_n,
/* Operateurs binaires */ 
	ARROW_n ,
	WHEN_n ,
	AND_n ,
	OR_n ,
	XOR_n ,
	IMPL_n ,
	EQUAL_n ,
	NEQ_n ,
	GTE_n ,
	GT_n ,
	LTE_n ,
	LT_n ,
	DIV_n ,
	MOD_n ,
	MINUS_n ,
	PLUS_n ,
	SLASH_n ,
	TIMES_n ,
	POWER_n ,
/* Operateurs ternaires */
	IF_n ,
/* Operateurs n-aires */
	TUPLE_n ,
	NOR_n ,
	DIESE_n ,
	EXACTONE_n ,
/* Operateurs n-aires speciaux */
	RCL_n ,
	ICL_n ,
/* Operateurs "unaires" speciaux */
	PROJ_n ,
	CALL_n ,

	NBExpNature
};

#define Leaf(X) (((X) >= CONST_n) && ((X) < PRE_n))
#define UnaryOp(X) (((X) >= PRE_n) && ((X) < ARROW_n))
#define BinaryOp(X) (((X) >= ARROW_n) && ((X) < IF_n))
#define TernaryOp(X) (((X) >= IF_n) && ((X) < TUPLE_n))
#define InfixedOp(X) (((X) >= TUPLE_n) && ((X) < RCL_n))
#define SpecUnaryOp(X) (((X) >= PROJ_n) && ((X) < NBExpNature))
#define CommutOp(X) (((X) == AND_n) \
						|| ((X) == OR_n) \
						|| ((X) == XOR_n) \
						|| ((X) == EQUAL_n) \
						|| ((X) == NEQ_n) \
						|| ((X) == PLUS_n) \
						|| ((X) == TIMES_n) )
#define CompareOp(X) (((X) >= EQUAL_n) && ((X) < DIV_n))

#ifdef NETSOURCE
const char* ExpNatureKeys[NBExpNature * 2] = {
	"",		"ERROR_n",
	"",		"CONST_n",
	"",		"INPUT_n",
	"",		"ECREF_n",
	"",		"MODELREF_n",
	
	"pre",	"PRE_n",
	"current",	"CURRENT_n",
	"not",	"NOT_n",
	"-",		"UMINUS_n",
	"last",		"LAST_n",
	"init",		"INIT_n",

	"->",		"ARROW_n",
	"when",	"WHEN_n",
	"and",	"AND_n",
	"or",		"OR_n",
	"xor",	"XOR_n",
	"=>",		"IMPL_n",
	"=",		"EQUAL_n",
	"<>",		"NEQ_n",
	">=",		"GTE_n",
	">",		"GT_n",
	"<=",		"LTE_n",
	"<",		"LT_n",
	"div",	"DIV_n",
	"mod",	"MOD_n",
	"-",		"MINUS_n",
	"+",		"PLUS_n",
	"/",		"SLASH_n",
	"*",		"TIMES_n",
	"**",		"POWER_n",

	"",		"IF_n",

	"",		"TUPLE_n",
	"nor",	"NOR_n",
	"#",		"DIESE_n",
	"&",		"EXACTONE",
	"",		"RCL_n",
	"",		"ICL_n",
	"",		"PROJ_n",
	"",		"CALL_n"
};
#else
extern char* ExpNatureKeys[];
#endif

#ifdef NETSOURCE
const char* nodekey(int X){ return (ExpNatureKeys[((X) << 1)+1]);}
const char* opkey(int X){ return (ExpNatureKeys[(X) << 1]);}
#else
extern const char* nodekey(int X);
extern const char* opkey(int X);
#endif


/*-------------------------------------------------------------------
	CLASSE EcType : 
---------------------------------------------------------------------
Permet au net d'associer un type a chaque expression (meme "tuple")
Ces objets ne peuvent etre crees que par le Net, qui en gere 
la liste.
-------------------------------------------------------------------*/
class EcType{
	/* L'index associe au type s'il s'agit d'un type
      simple non pre-defini. Les index vont de 1 a
      nb_usr_def_type
   */
	int usr_def_index;
	IntList* usr_def_consts;

	/* Type enumere */	
	int enum_size;
	IdentInfo** enum_consts;

	int is_tup;
   union {
      int stype;
      IntList* ttype;
   };
	EcType* nxt;
public :
	int is_tuple(){return is_tup;}
	int tuple_length(){
		return (is_tup)? ttype->length():0;
	}
	int is_named(){return !(is_tup);}
	int name(){return stype;}
	// Renvoie le NOM du ieme type simple composant le tuple :
	int member(int index){
   	if(!is_tuple())
      	IError("file net.cc\n EcType::member() called on non tuple type\n");
	
   	IntList* l = ttype;
   	int k = 1;
   	while(k++ != index) l = l->tail(); 
   	return l->head();
	};
	int is_extern(){return usr_def_index;};
	IntList* consts(){ return usr_def_consts; };
	void add_usr_const(int index){
		append_list(usr_def_consts, index);
	}
	int is_enum(){return enum_size;};
	IntList* name_list(){ return ttype;};
	EcType* next(){return nxt;};
	IntList* names(){return ttype;};
	EcType(){};
	void set_extern(int i){ usr_def_index = i;}; 
	void set_enum(int nb_consts){
		enum_size = nb_consts;
		enum_consts = new IdentInfo*[enum_size];
	}
	void add_enum_const(int ci, IdentInfo* info){
		enum_consts[ci] = info;
	}
	int nb_enum_const(){
		return enum_size;
	}
	IdentInfo* enum_const(int c){
		if(! enum_size){
			IError("file net.cc\n%s",
				"EcType::enum_const(int) called on non enumerate type\n");
		}
		return enum_consts[c];
	}
	EcType(int st, EcType* n){
		usr_def_index = 0;
		usr_def_consts = NULL;
		enum_size = 0; enum_consts = NULL;
		is_tup = 0;
		stype = st;
		nxt = n;
	};
	EcType(IntList* tt, EcType* n){
		usr_def_index = 0;
		usr_def_consts = NULL;
		enum_size = 0; enum_consts = NULL;
		is_tup = 1;
		ttype = tt;
		nxt = n;
	};
	EcType(int* ttab, int tsize, EcType* n){
		usr_def_index = 0;
		usr_def_consts = NULL;
		enum_size = 0; enum_consts = NULL;
		is_tup = 1;
		ttype = new IntList(ttab, tsize);
		nxt = n;
	};
	void print(SymbolTable* st, PtyStream* ostream){
		if (is_tuple()){
		/* Imprime une liste d'idents separes par des ';' */
			IntList* tl = name_list();
			ostream->put((*st)[tl->head()]);
			while((tl = tl->tail())){
				ostream->put("; ");
				ostream->put((*st)[tl->head()]);
			}
		} else {
		/* Imprime le nom */
			ostream->put((*st)[name()]);
		}
	};

};


/*--------------------------------------------------------------------
	CLASSES  Exp, ExpList, ExpSet :
----------------------------------------------------------------------
      Noeud pour la representation graphique des expressions
----------------------------------------------------------------------
NB : Classe generale, qui est utilisee pour des arbres, des DAG etc...
--------------------------------------------------------------------*/

/* Pour le parcours des expressions : */
extern int take_a_key();

#define UNKNOWN_CLOCK ((int)(-1))

class ExpInfo{
friend class Exp;
protected:
	int the_key;
	void* the_info;
	ExpInfo* next;
	ExpInfo(int k, void* i, ExpInfo* n){
		the_key = k; the_info = i; next = n;
	}
};

class Exp{
friend class IdentInfo;
friend class Net;
friend class NetCtr;

	EcType* typ; //Accede via la classe friend Net
	int clk;     //Accede via la classe friend Net

//Pour les parcours recursifs :
	int rec_mark;
	ExpInfo* infos;

public :
	int bclass;

	int ident;
	ExpNature nature;
	int arity;
	Exp** operands;
	int spec_info; // Operande supplementaire (pour CALL et PROJ et RCL_n)

	// Operandes  pour ICL_n :
	int* int_coefs; 
	int int_const; 

	// Operandes pour RCL_n (rationels) :
	Fract* rat_coefs;
	Fract rat_const;		

/*------------ METHODES ------------------------------------------ */
	void ExpInit(){ /*------ Doit etre appele par tous les constructeurs */
		typ = NULL;
		clk = UNKNOWN_CLOCK;
		nature =  ERROR_n ;
		ident = arity = 0;
		operands = NULL;
		spec_info = 0;
		rat_coefs = NULL;
		int_coefs = NULL;
		int_const = 0;
		bclass = 0;
		infos = NULL;
		rec_mark = 0;
	};	
	Exp(){ExpInit();};
	Exp(ExpNature n, Exp* op1);            /* Creation d'une boite unaire */
	Exp(ExpNature n, Exp* op1, int spec);  /* Creation d'une "   speciale */
	Exp(ExpNature n, Exp* op1, Exp* op2);  /*    "            "   binaire */
	Exp(ExpNature n, Exp* op1, Exp* op2, Exp* op3); /* "      "  ternaire */
	Exp(ExpNature n, ExpList* o);                   /* "      "    n-aire */
	Exp(ExpNature n, int ar, Exp** ops);            /* "      "    n-aire */

	/* pour les CL_n : */
	Exp(ExpNature n, int ar, Exp** ops, Fract* cofs, Fract co);
	Exp(ExpNature n, int ar, Exp** ops, int* cofs, int co);
			

	/* Creation d'une feuille : outre la nature et l'ident associe, */
	/*    il faut fournir le type et l'horloge de l'expresion  :    */
	Exp(ExpNature n, int id, EcType* ty, int ck);
	Exp(ExpNature n, int id, EcType* ty);

	/* Pour les CALL_n et les PROJ_n, il faut une info   */
	/* supplementaire :                                  */ 
	int special_info(){ return spec_info;};

	/* MEME CHOSE MAIS DEBBUG */
	int projection_order(){
		if(nature != PROJ_n){
			IError("file 'net.h':\nExp::projection_order called on '%s' operator", nodekey(nature));
			return 0;
		} else {
			return spec_info;
		}
	};
	int function_ident(){
		if(nature != CALL_n){
			IError("file 'net.h':\nExp::function_name called on '%s' operator", nodekey(nature));
			return 0;
		} else {
			return spec_info;
		}
	};

	/* Impression des expressions au format "ec" */
	void print(PtyStream* ostream, SymbolTable* stab);
	void print_def(PtyStream* ostream, SymbolTable* stab);

	/* i.e. mais traite les recursions non gardees */ 
	void Iprint(PtyStream* ostream, SymbolTable* stab);
	void Iprint_def(PtyStream* ostream, SymbolTable* stab);

	/* Ranger ou rechercher une info */ 
	int marked(int m){
      return (rec_mark == m);
	};

	void mark(int m){
		rec_mark = m;
	};

	void* get_ptr_info(int key);
	int get_int_info(int key);
   void put_info(int key, void* info);
};

AddGenericList(ExpList,Exp*)

/**** OBSOLETE
class ExpList{
	int len;
	Exp* son;
	ExpList* next;
public :
	int length(){ return len;};
	Exp* head(){ return son;};
	ExpList* tail(){ return next;};

	// Construit une liste a un seul element
	ExpList(Exp* s){
		len = 1; son = s; next = 0;
	};
	//Construit une liste "par la tete"
	ExpList(Exp* s, ExpList* t){
		len = (t)?(t->length()+1):(1); son = s; next = t;
	};
	// ajoute 'l' a la fin de la liste 'this'
	void concat(ExpList* l);
};
*****/

class ExpSet{
public :
   ExpSet(Exp* s, ExpSet* l){
      son = s; next = l;
   };
   Exp* son;
   ExpSet* next;
};


/*--------------------------------------------------------------------
	CLASSES  IdentInfo, FuncInfo, SymbolInfo
----------------------------------------------------------------------
      Informations associees aux identificateurs du prg. source 
----------------------------------------------------------------------
	IdentInfo : pour les ident. associes a des expressions 
(plusieurs modes suivant la nature exacte de l'ident).
	FuncInfo : pour ceux associes aux fonctions externes
(deux mode, suivant le type d'appel dans le prg. objet)
--------------------------------------------------------------------*/

enum IdentMode { 
	INPUT, OUTPUT, LOCAL, USR_CONST, ASSERT, BOOL_CONST, INT_CONST, REAL_CONST,
	ENUM_CONST
};

inline const char* ident_mode2string(IdentMode m){
	switch (m) {
		case INPUT:
			return "INPUT";
		break;
		case OUTPUT:
			return "OUTPUT";
		break;
		case LOCAL:
			return "LOCAL";
		break;
		case USR_CONST:
			return "USR_CONST";
		break;
		case ASSERT:
			return "ASSERT";
		break;
		case BOOL_CONST:
			return "BOOL_CONST";
		break;
		case INT_CONST:
			return "INT_CONST";
		break;
		case REAL_CONST:
			return "REAL_CONST";
		break;
		case ENUM_CONST:
			return "ENUM_CONST";
		break;
		default:
			return "??";
		break;
	} 
}

class IdentInfo{
friend class Net;

	int string; //Index dans la table des symboles
	int clk;  	//Index de l'horloge assoc.
	EcType* typ;
	IdentMode mode;
	union{
		IntList* is_member;	/* pour OUTPUT ou LOCAL */
		int int_value; 		/* pour INT_CONST */
		float real_value;		/* pour REAL_CONST */
		int usr_def_index;	/* pour USR_CONST */
	};
	Exp* EcExp;	
	Exp* EcRefExp;	
	Exp* NetEntry; // Point d'entree dans le re'seau ec 

	int index_in_list;	//Pour INPUT, OUTPUT ou LOCAL ou ENUM_CONST

public:
	void Init(){
		EcExp = EcRefExp = NetEntry = NULL ;
		is_member = NULL;
		index_in_list = -1;
	};
	IdentInfo(IdentMode mo, int nme, EcType* ty, int ck);
	void ec_link(Exp* e){ EcExp = e; e->typ = typ; e->clk = clk; };
	void ecref_link(Exp* e){ EcRefExp = e; e->typ = typ; e->clk = clk;};
	Exp* ec_def(){return EcExp;};
	Exp* ec_ref(){return EcRefExp;};

	Exp* net_def(){return NetEntry;};
	void net_set(Exp* e){NetEntry = e;};
	void net_link(Exp* e){NetEntry = e; e->typ = typ; e->clk = clk; };

	EcType* type(){return typ;}; 
	int clock(){return clk;};
	int name(){ return string; };
	void set_clock(int c){clk = c;};
	IdentMode ident_mode(){ return mode;};

	/* Acces aux infos accessoires :
	*/
	void set_int_value(int iv){ int_value = iv; };
	void set_real_value(float fv){ real_value = fv; };
	void set_usr_def_index(int i){ usr_def_index = i; };
	void set_index_in_list(int i){ index_in_list = i; };	

	int get_int_value(){
		if(mode != INT_CONST){
			IError("Ident::get_int_value: invalid call on ident '%d' (mode '%s')\n",
				string,
				ident_mode2string(mode)
			);
		}
		return int_value;
	};
	float get_real_value(){
		if(mode != REAL_CONST){
			IError("Ident::get_real_value: invalid call on ident '%d' (mode '%s')\n",
				string,
				ident_mode2string(mode)
			);
		}
		return real_value;
	};
	int get_usr_def_index(){return usr_def_index; };
	int get_index_in_list(){ return index_in_list; };	
	
	/* Uniquement pour decompiler :
	 */
	void tuple_link(IntList* tuple){ is_member = tuple; };
	IntList* tuple_linked(){ return is_member; };
	
};

enum FuncMode { 
	FUNCTION, PROCEDURE 
};
#define _SAFE_EXTERN 0
#define _UNSAFE_EXTERN 1

class FuncInfo {
	FuncMode mod;
/* 2007/3/8 => extern/unsafe*/
	int _unsafe;

	int usr_def_index;
	EcType* in_type;
	EcType* out_type;
	IntList* in_pars;	 	/* Pour la decompilation */
	IntList* out_pars;	/* uniquement.           */        
	void print_params(IntList* l, SymbolTable* st, PtyStream* os);
public :
	FuncInfo(FuncMode m, int usf, EcType* it,EcType* ot, IntList* inp, IntList* outp){
		_unsafe = usf; mod = m; in_type = it; out_type = ot; in_pars = inp; out_pars = outp;
	};
	int is_proc(){ return (mod == PROCEDURE);};
	int is_unsafe(){ return _unsafe;}
	int nb_result(){ return out_pars->length(); };
	EcType* inputs_type(){return in_type; };
	EcType* outputs_type(){return out_type; };

	void set_usr_def_index(int i){ usr_def_index = i; };
	// Renvoie la position dans la liste correspondante,
	// de 0 a nb_usr_proc-1 pour les procedures
	// de 0 a nb_usr_fun-1 pour les fonctions
	int get_usr_def_index(){return usr_def_index; };

	/* Pour la decompilation */
	void print_inputs(SymbolTable* st, PtyStream* os){
		print_params(in_pars, st, os);
	};
	void print_outputs(SymbolTable* st, PtyStream* os){
		print_params(out_pars, st, os);
	};
};

struct SymbolInfo {
	union{
		IdentInfo* ident_inf;
		FuncInfo* func_inf;
	};
	SymbolInfo(){ ident_inf = NULL; }
};

/*
typedef union{
	IdentInfo* ident_inf;
	FuncInfo* func_inf;
} SymbolInfo;
*/


class SymbolInfoArray {
	SymbolInfo* page;
	int page_size;
	SymbolInfoArray* next_part;
	int bound;
	int first_index;
public:
	SymbolInfoArray(int s, int fi = 0);
	~SymbolInfoArray();
	SymbolInfo& operator[](int i);
	int size();
};


/*--------------------------------------------------------------------
	CLASSE  Net 
----------------------------------------------------------------------
            Stockage des infos relatives au programme 'ec'
----------------------------------------------------------------------
--------------------------------------------------------------------*/
class Net{
protected :
	/* variables "globales" */
	EcType* bool_t;
	EcType* int_t;
	EcType* real_t;
	int base_ck;
	Exp* true_e, *false_e, *bottom_e, *nil_e;

	SymbolTable* symbol_table; /* La table des symboles */
	int node_name;             /* L'index du nom du noeud */

	/* Ce tableau permet de stocker les infos relatives
		aux variables,  constantes et fonctions, en les
		indexant par les indices retournes par la table 
		des symboles 
	*/
	SymbolInfoArray* symbol_infos;

	/* Pour les identificateurs, on gere des listes
		d'entiers qui sont a la fois des entrees dans
		la table des symboles et dans la table symbol_infos
	*/
	IntList* inputs;
	IntList* outputs;
	IntList* locals;
	IntList* assertions;
	IntList* usr_consts;
	IntList* usr_funcs;
	IntList* usr_procs;
	int nb_ins;
	int nb_outs;
	int nb_locs;
	int nb_ass;
	int nb_usr_types;
	int nb_usr_consts;
	int nb_usr_funcs;
	int nb_usr_procs;

	/* Pour les types, on gere l'unicite de la representation
		grace a une liste de "types connus". Les champs "type"
		des expressions ou des identificateurs ne peuvent 
		pointer que sur les structures stockees dans cette
		liste. Pour les types externes, on gere la liste
		'usr_types', qui ne sert que pour decompiler le prg.
	*/
	IntList* usr_types;
	EcType* known_types;

	/* methodes utilises pour l'affichage	*/
public:
	void print_all_clocked_ident_list(IntList* idents, PtyStream* ostream);
	void print_clocked_ident_list(IntList* idents, PtyStream* ostream);
	void print_ident_list(IntList* idents, PtyStream* ostream);
	void print_func_list(IntList* funcs, PtyStream* ostream);
	void print_func_decl(int func_ident, PtyStream* ostream);
	void print_ident_def(IntList* idents, PtyStream* ostream);
	void print_assert_def(PtyStream* ostream);
	void NetInit(SymbolTable* st);

public:
	/* ----------------------------------------------------
		Constructeur : 
	-------------------------------------------------------*/
	Net(SymbolTable* st){
		NetInit(st);
	};
	/* ----------------------------------------------------
		Definition du nom du noeud : 
	-------------------------------------------------------*/
	void def_name(int nme){ node_name = nme;}; 
	int name(){return  node_name;}; 

	/* ----------------------------------------------------
		Gestion des listes d'identificateurs : 
	-------------------------------------------------------*/
	void add_usr_type(int);
	void add_usr_type(int, IntList*);
	void add_enum_const(int name, EcType* type, int clock, int index_in_type);
/* 2007/3/8 => unsafe/extern */
	void add_usr_func(int, int, EcType*, EcType*,IntList*,IntList*);
	void add_usr_unsafe_proc(int, EcType*, EcType*,IntList*,IntList*);

	void add_usr_const(int name, EcType* type, int clock);
	void add_input(int name, EcType* type, int clock);
	void add_output(int name, EcType* type, int clock, int at_top = 0);
	void add_local(int name, EcType* type, int clock);
	/*-------- Gestion de la liste des assertions : ------*/
	void add_assertion(Exp* assert);

	/*-------- Associe une expression a une variable -----*/
	void define_variable(int name, Exp* def){
		get_ident_info(name)->ec_link(def);
	};	
	void define_member_variable(IntList* tuple, int name, Exp* def){
		define_variable(name, def);
		get_ident_info(name)->tuple_link(tuple);
	};	
	void define_tuple(IntList* names, Exp* def);

	/* -----------------------------------------------------
		Gestions des constantes predefinies :
	--------------------------------------------------------
	l'"unicite" des expressions associees aux constantes est 
	garantie	par la table des symboles : pas de problemes pour
	les booleens et les entiers, mais pour les reels, on n'a
	donc qu'une equivalence "syntaxique" (1.0e+1 != 10.0 )
	-------------------------------------------------------*/
	Exp* get_bool_const(int string);
	Exp* get_int_const(int string);
	Exp* get_real_const(int string);

	/* -----------------------------------------------------
		Acces aux variables "globales"
	------------------------------------------------------*/
	EcType* bool_type(){return bool_t;};
	EcType* int_type(){return int_t;};
	EcType* real_type(){return real_t;};
	int base_clock(){return base_ck;};
	Exp* true_exp(){return true_e;};
	Exp* false_exp(){return false_e;};
	Exp* bottom_exp(){return bottom_e;};
	Exp* nil_exp(){return nil_e;};

	/* ----------------------------------------------------
		Construction des expressions combinees
	-------------------------------------------------------*/
	Exp* get_exp(ExpNature nature, Exp* operand){
		return new Exp(nature, operand);
	};
	Exp* get_exp(ExpNature nature, Exp* operand, int info){
		return new Exp(nature, operand, info);
	};
	Exp* get_exp(ExpNature nature, Exp* op1, Exp* op2){
		return new Exp(nature, op1, op2);	
	};
	Exp* get_exp(ExpNature nature, Exp* op1, Exp* op2, Exp* op3){
		return new Exp(nature, op1, op2, op3);
	};
	Exp* get_exp(ExpNature nature, ExpList* ops){
		return new Exp(nature, ops);
	};

	/* ----------------------------------------------------
		Acces aux informations sur les identificateurs :
	-------------------------------------------------------*/
	IdentInfo* get_ident_info(int ident){
		return (*symbol_infos)[ident].ident_inf;
	};
	FuncInfo* get_func_info(int ident){
		return (*symbol_infos)[ident].func_inf;
	};
	int is_unsafe_func_id(int ident){
		return get_func_info(ident)->is_unsafe();
	}

	char* symbol(int id){ return ((*symbol_table)[id]); };
	SymbolTable* symbols(){ return symbol_table; };
	int def_symbol(char* str){ return (symbol_table->add(str)); };

	/* ----------------------------------------------------
		Acces aux listes d'identificateurs :
	-------------------------------------------------------*/
	IntList* input_list(){ return inputs;};
	IntList* output_list(){ return outputs;};
	IntList* local_list(){ return locals;};
	IntList* assertion_list(){ return assertions;};
	IntList* usr_const_list(){ return usr_consts;};
	IntList* usr_func_list(){ return usr_funcs;};
	IntList* usr_proc_list(){ return usr_procs;};
	IntList* usr_type_list(){ return usr_types;};

	int nb_inputs(){ return nb_ins; };
	int nb_outputs(){ return nb_outs; };
	int nb_locals(){ return nb_locs; };
	int nb_asserts(){ return nb_ass; };
	int nb_u_types(){ return nb_usr_types;};
	int nb_u_consts(){ return nb_usr_consts; }
	int nb_u_funcs(){ return nb_usr_funcs; }
	int nb_u_procs(){ return nb_usr_procs; }
	/* ----------------------------------------------------
		Gestion de la liste des types connus
		Deux maniere d'acceder aux types tuple :
		- via une liste dse types de base
		- via un tableau de types de base (avec sa taille).
	-------------------------------------------------------*/
	EcType* define_type(IntList* tl);
	EcType* define_type(int* ttab, int tsize);
	EcType* define_type(int nme);

	/* ----------------------------------------------------
		Calcul du type et de l'horloge d'une expression
	-------------------------------------------------------*/
	EcType* type(Exp* e);
	EcType* type(int ident){
		return get_ident_info(ident)->type();
	};
	int clock(Exp* e);
	
	/* ----------------------------------------------------
		Impression du programme EC correspondant sur stdout : 
	. print_exp : affiche en priorite l'identificateur
   (eventuel) associe a l'expression.
	. print_exp_def : ignore l'ident (eventuel) associe
	a l'expression (sauf bien sur pour les inputs !).
	-------------------------------------------------------*/
	void print_exp(Exp* e); 
	void print_exp_def(Exp* e); 
	void print_exp(PtyStream* os, Exp* e); 
	void print_exp_def(PtyStream* os, Exp* e); 
	void print_ec(); 
	void print_lus(); 

};

/* -------------------------------------------------------------------------
 * Projet E C 2 O C
 * -------------------------------------------------------------------------
 * module   : net_ctr.h
 *
 * date     : 02/2/93
 * auteurs  : Pascal Raymond
 *--------------------------------------------------------------------------
 * nature   : Structure dédiée à la gestion de l'unicité des expressions
 *      dans un réseau d'opérateurs.
 *      Les operateurs sont partitiones en :
 *          UnaryOp
 *          BinaryOp && CommutOp
 *          BinaryOp && ! CommutOp
 *          TernaryOp
 *          InfixedOp
 *          SpecUnaryOp
 *      N.B. La structure ne gere pas les feuilles !
 *
 *      Pour gerer les expressions recurentes (i.e. les boucles du reseau)
 *      on dispose de deux procedures : 
 *          - getabox() creer une "boite bidon" de type Exp qui peut etre
 *      utilisee comme operande d'une expressiomn recurente
 *          - update(box, exp) recopie dans "box" les caracteristiques de "exp".
 *      "box" etant alors parfaitement definie, elle est rangee dans la classe
 *      de "exp", MAIS AVANT "exp" : c'est donc elle (et non pas "exp") qui 
 *      sera donc renvoyee lors d'une eventuelle consulatation. 
 *      N.B. "exp" n'est pas detruite : si cette expression n'est pas utilisee
 *      lors de "update" on ne l'utilisera jamais, puisque "box" devient 
 *      prioritaire.
 *      Mais on ne peut pas la detruire car il se peut qu'elle soit deja 
 *      utilisee lors du "update" : c'est le cas (rare) des definitions 
 *      recurentes equivalentes un peu complexes qu'on ne sait pas gerer. 
 *--------------------------------------------------------------------------
 * Modifs   : 
 *  2007-3-8 dans les appels externes, le flag unsafe interdit un éventuel partage
 * -----------------------------------------------------------------------*/

#define EXP_HASH_SIZE 5041 /* D'apres l'experience de la V3.0 ! */

class NetCtr {
friend class NetSemantic;

	ExpList* hash_tab[EXP_HASH_SIZE];

	/* Calcul des fonctions de hash */
	int binary_hash_code(Exp* e0,Exp* e1);
	int unary_hash_code(Exp* e);
	int ternary_hash_code(Exp* e0,Exp* e1,Exp* e2);
	int tuple_hash_code(int ar, Exp** w);

protected:
	Net* net;

public:
	NetCtr(){
		net = NULL;
		int i = EXP_HASH_SIZE;
		while ( i--) { hash_tab[i] = NULL; }
	};
	void init(Net* nt){ net = nt; };
	/*----- Consultation de la table --------------------------------------*/
	Exp* neg(Exp* e);
	Exp* true_exp(){ return net->true_exp(); };
	Exp* false_exp(){ return net->false_exp(); };
	Exp* nil_exp(){ return net->nil_exp(); };
	Exp* operator()(int int_const);
	Exp* operator()(float real_const);
	Exp* operator()(ExpNature nature, Exp* op);
	Exp* operator()(ExpNature nature, Exp* op, int spec);
	Exp* operator()(ExpNature nature, Exp* op1, Exp* op2);
	Exp* operator()(ExpNature nature, Exp* op1, Exp* op2, Exp* op3);
	Exp* operator()(ExpNature nature, int arity, Exp** ops);

	// TRES SPECIFIQUE (pour CL_n)
	Exp* operator()(ExpNature nature, int arity, Exp** ops, Fract* cofs, Fract co);
	Exp* operator()(ExpNature nature, int arity, Exp** ops, int* cofs, int co);

	/*----- Gestion des boucles dans le reseau ----------------------------*/
	Exp* getabox();
	void update(Exp* box, Exp* def);
	void put_in_hash_tab(Exp* e);

};


#ifndef PR93_NET_NORM_ARGS
#define PR93_NET_NORM_ARGS

/***********
	OPTIONS DU MODULE net_norm
***********/
enum MinimizeMode {
   STD_BISIMULATION_0,
   STD_BISIMULATION_1,
   STD_BISIMULATION_2,
	NO_BISIMULATION
};

#endif

/* -------------------------------------------------------------------------
 * Projet E C 2 O C
 * -------------------------------------------------------------------------
 * module   : net_norm.h
 *
 * date     : 12/3/93
 * auteurs  : Pascal Raymond
 *--------------------------------------------------------------------------
 * nature   : Interface de la classe NormNet :
 *    Classe de'rive'e de Net, de'die'e a` la normalisation des
 *    expressions 'ec', puis a` la consruction d'un re'seau
 *    d'expressions normalise'es minimal.
 *    N.B. : LA CONSTRUCTION DU RESEAU NORMALISE EST FAITE EN TROIS TPS :
 *       - Construction de DAG's normalise's
 *       - Calcul d'une bisimulation sur ces DAG's
 *       - Construction d'un reseau minimal a partir des classes de
 *       cette bisimulation.
 *--------------------------------------------------------------------------
 * Modifs   :
 *		27/10/93 Optimisation du calcul de la bisimulation (il en a bien besoin !)
 *		la methode "init_classes()" cree une partition initiale de
 *		l'ensemble des operateurs cree lors de la normalisation. 
 *			Rmq : cette partition initiale pourrait etre cree au fur et a mesure
 *		qu'on cree les operateurs normalises ... Menfin, soyons prudent !
 * -----------------------------------------------------------------------*/

class NormNet : public Net {
	//Option de minimisation :
	MinimizeMode mini_mode;

	// Pour le hash-codage du reseau 
	NetCtr netify;       

	// Attention ! on y va a la louche :
	Exp** Xinits;
	Exp** Xclocks;
	Exp** Ximpls;
	Exp** Xflows;

	/*
		Pour la minimation ulterieure du reseau normalise :
		Les noeuds normalises d'arite > 0 sont OBLIGATOIREMENT
		crees par une des methodes "get_norm_exp", ce qui permet
		de gerer les variables suivantes : 
		
	*/
	ExpSet* norm_ops;	//Liste des exp. normalisees d'arite > 0
	int nb_norm_ops;	//Nombre d'elements de cette liste
	int nb_norm_lbls;	//La somme des arites des norm_ops

	//Option 'opt_bool'
	// mars 2007 : propage la condact si besoin
	int opt_bool;
	Exp* get_norm_bool(ExpNature nature, int arity, Exp** ops, int ca);

	//Le nombre d'appels de get_norm : 
	//interressant en mode 'opt_bool' car eventuellement
	//different de 'nb_norm_ops'
	int nb_get_norm_calls;

	/*
		mars 2007 : gestion des condacts
		À toute  expression normalisée 
		est attachée une condact
	*/
	int condact_KEY;

	// Création de boites non zeroaires
	/* 
		mars 2007 : on passe une éventuelle condact, qui DOIT ETRE
      un résultat de Xclock.
	*/

	Exp* get_norm_exp(ExpNature nature, Exp* operand, int ca);
	Exp* get_norm_exp(ExpNature nature, Exp* operand, int info, int ca);
	Exp* get_norm_exp(ExpNature nature, Exp* op1, Exp* op2, int ca);
	Exp* get_norm_exp(ExpNature nature, Exp* op1, Exp* op2, Exp* op3, int ca);
	Exp* get_norm_exp(ExpNature nature, ExpList* ops, int ca);
	Exp* get_norm_exp(ExpNature nature, int arity, int spec_info, Exp** ops, int ca);

	// Mise en place d'info dans les exp crees par get_norm_exp :
	int norm_ops_KEY;
	void set_norm_index(Exp* e, int index){
		e->put_info(norm_ops_KEY, (void*)index);
	}
	int norm_index(Exp* e){
		return (e->get_int_info(norm_ops_KEY));
	}

	// Construction des expressions normalisees :
	// 2007-3-10
	// toutes ces operations sont deterministes,
	// et dont peuvent etre cachees
	// et meme elles le doivent => support min des unsafe
   // n.b. c'etait deja le cas pour celles qui prennent
	// un ident, mais pas celles aui prennent une exp
	int Ximpl_KEY;
	int Xflow_KEY;

	// 2012/04/23 v. 0.65, garde corresponces :
	// norm_exp -> exp
	int XIMPL_SRC;
	int XFLOW_SRC;
	int XCLK_SRC;

	Exp* Xinit(int clk);
	Exp* Xclock(int clk);
	Exp* Ximpl(Exp* ec_exp);
	Exp* Xflow(Exp* ec_exp);
	Exp* computeXimpl(Exp* ec_exp);
	Exp* computeXflow(Exp* ec_exp);
	void normalise(int ident);

	// Calcul de la bisimulation sur les expressions normalisees 
   ExpSet** classes;
   Exp** boxes;
   int nb_classes;
   Exp* through_ref(Exp* e);
   int exp_nature_cmp(Exp* in_e1, Exp*in_e2);
   int exp_cmp(Exp* in_e1, Exp* in_e2, int cur_class);
   int exp_bisim(Exp* e1, Exp* e2, int cur_class);
	int bary_split(int cur_class);
#ifndef TEST_MIN
	inline int split(int cur_class){ return bary_split(cur_class); };
#endif
	void minimize(); //Mon truc a moi

	void init_classes();
	void no_minimize();
	void init_classes_0();

public :
	Exp* Xclk2src(Exp* e) { return (Exp*)(e->get_ptr_info(XCLK_SRC)); }
	Exp* Ximpl2src(Exp* e) { return (Exp*)(e->get_ptr_info(XIMPL_SRC)); }
	Exp* Xflow2src(Exp* e) { return (Exp*)(e->get_ptr_info(XFLOW_SRC)); }

	//Pour le debuggage de la minimisation :
   void print_class(Exp* e);
   void print_class_op(Exp* e);
   void print_classes();

	void normalise();
	//Pour le debuggage de la normalisation :
	void print(); 

	NormNet(
      SymbolTable* st,
      MinimizeMode m = STD_BISIMULATION_0,
      int ob = 0
   ):Net(st){ 
		netify.init(this);
		norm_ops_KEY = take_a_key();
		Ximpl_KEY = take_a_key();
		Xflow_KEY = take_a_key();
		condact_KEY = take_a_key();
		XFLOW_SRC = take_a_key();
		XIMPL_SRC = take_a_key();
		XCLK_SRC = take_a_key();
		nb_get_norm_calls = 0;
		nb_norm_ops = 0;
		nb_norm_lbls = 0;
		norm_ops = NULL;
		classes = NULL;
		nb_classes = 1;
		opt_bool = ob;
		mini_mode = m;
	};

	void build();

	// Attention ! les classes sont numerotes de 1 a nb_boxes.
	int nb_boxes(){ return nb_classes; };
	Exp* box(int i){ return boxes[i-1]; };
	
	NetCtr* exp_maker(){ return &netify; }; 

	//Renvoie une entree dans le reseau minimal 
	//pour l'identificateur 'id'
	Exp* norm(int id);

	//Renvoie une entree dans le reseau minimal 
	//pour l'éventuelle condact de l'expression e
	Exp* condact(Exp* e);
};

/*
Un objet NetSemantic est initialise avec un objet NetCtr
*/

class NetSemantic {
	NetCtr* netify;
	Net* net;

protected:
// UTILITAIRES 
	Bool is_int_const(Exp* e){
		return (
			(e->nature == CONST_n) 
				&&
			(net->get_ident_info(e->ident)->ident_mode() == INT_CONST)
		);
	}
	Bool is_real_const(Exp* e){
		return (
			(e->nature == CONST_n) 
				&&
			(net->get_ident_info(e->ident)->ident_mode() == REAL_CONST)
		);
	}
	int int_const(Exp* e){
		return net->get_ident_info(e->ident)->get_int_value();
	}
	float real_const(Exp* e){
		return net->get_ident_info(e->ident)->get_real_value();
	}
	ExpList* call_list; //to debug...
	int keep_trace;
	virtual ~NetSemantic(){}
public :
	NetSemantic(NetCtr* ctr, int keept = 0){ 
		netify = ctr; 
		net = netify->net;
		call_list = NULL;
		keep_trace = keept;
	};
	virtual Exp* Vsimplify(Exp* e);
	Exp* simplify(Exp* e);
	ExpList* simplified(){ return call_list; }
};
/*------------------------------------------------
INFO associees au expressions du reseau.
--------------------------------------------------
CONTROLE :
Une Exp ne peut avoir qu'un numero de
'is_ctrl', 'is_cond', 'is_svar'. 
De plus, is_ctrl implique is_cond ou (exclusif) is_svar.
SORTIES, LOCALES :
Par contre, une meme expression peut correspondre a 
plusieurs sorties, ou plusieurs variables locales.
'is_out' et 'is_lcl' sont donc des listes de numero.
ASSERTIONS:
Plusieurs assertions du code source peuvent correspondre
a une meme expression. Mais on s'en fout.
-------------------------------------------------*/
class PNetInterfaceInfo{
friend class PNetInterface;
friend class NetInterface;
protected:
	int is_cond;
	int is_svar;
	int is_ctrl;
	IntList* is_out;
	IntList* is_lcl;
	int is_in;
	int is_assert;
	PNetInterfaceInfo(){
		is_out = is_lcl = NULL;
		is_ctrl = is_cond = is_svar = is_in = is_assert = 0;
	};
};

class PNetInterface{
protected:
	NormNet* the_net; 
	int nb_conds;
	int nb_svars;
	int nb_ctrls;
	int nb_outs;
	int nb_ins;
	int nb_asserts;
	int nb_lcls;
	Exp** cond_tab;
	Exp** svar_tab;
	Exp** ctrl_tab;
	Exp** out_tab;
	Exp** in_tab;
	Exp** lcl_tab;
	int* out_ids;
	int* in_ids;
	int* lcl_ids;
	Exp** assert_tab;
	ExpList* cond_list;
	ExpList* svar_list;
	ExpList* ctrl_list;
	int control_mark;
	int is_bool_mem(Exp* e);
	int is_comp(Exp* e);
	int is_non_ev_bool(Exp* e);
	int control_order_mark;
	void check_order();	
	int rec_check_order(Exp* e);	
	void rec_find_control(Exp* e);	

	//GESTION DES INFOS ASSOCIEES AUX EXP :
	int info_mark;
	PNetInterfaceInfo* get_info(Exp* e){
		return (PNetInterfaceInfo*) e->get_ptr_info(info_mark);
	}
	PNetInterfaceInfo* get_or_add_info(Exp* e){
		PNetInterfaceInfo* info = 	get_info(e);
		if(! info) {
			info = new PNetInterfaceInfo();
			put_info(e, info);
		}
		return info;
	} 
	void put_info(Exp* e, PNetInterfaceInfo* info){
		e->put_info(info_mark, (void*)info);
	}
	void add_cond(Exp* e);
	void add_statevar(Exp* e);
	void add_output(Exp* e, int i);
	void add_input(Exp* e, int i);
	void add_assert(Exp* e);
	void add_local(Exp* e, int i);

	PNetInterface(){
		nb_conds = nb_svars = nb_ctrls = nb_outs =
		nb_ins = nb_asserts = nb_lcls = 0;
		control_mark = control_order_mark = -1;
		info_mark = take_a_key();
		assert_tab = ctrl_tab = cond_tab = svar_tab =
			out_tab = in_tab = lcl_tab = NULL;
		out_ids =  in_ids = lcl_ids = NULL;
		ctrl_list = cond_list = svar_list = NULL;
	}
};

/***********************************************************************
Contruction d'un NetInterface :

=> Dans sa version ``simple'', on passe en argument un nom 
de fichier 'ec'. Si un probleme apparait (erreur d'ouverture 
du fichier, erreur de syntaxe) le constructeur provoque un exit(1)
(et donc l'arret du programme appellant).

=> On peut aussi creer une instance vide (constructeur sans parametres),
puis appeler la methode ``init'' avec un nom de fichier.
Cette méthode renvoie :
 - 0 si tout s'est bien passe,
 - 1 si l'initialisatiopn a echouee
N.B. On peut forcer le net a utiliser une table de symbole deja crée,
sinon, il en cree une interne.

=> Les infos. de controles (variables d'etat et conditions)
ne sont disponibles qu'apres avoir appeler la methode :
	find_control(int enforce)
si 'enforce = 1' au moins une variable d'etat (bidon) sera cree.
***********************************************************************/

class NetInterface: public PNetInterface {
public :
	// CONSTRUCTION :
	int init(const char* ecfname, SymbolTable* Symbols, int nomin, int optbool);
	NetInterface();
	NetInterface(const char* ecfname);
	NetInterface(const char* ecfname, int nomin);
	NetInterface(const char* ecfname, int nomin, int optbool);
	NetInterface(const char* ecfname, SymbolTable* Symbols);
	NetInterface(const char* ecfname, SymbolTable* Symbols, int nomin);
	NetInterface(const char* ecfname, SymbolTable* Symbols, int nomin, int optbool);

	//NOM DU PROGRAMME :
	int name();

	//ACCES AUX ELEMENTS DE CONTROLES :
	//NB : POUR ACCEDER A CES INFO IL FAUT
	//AVOIR APPELE :
	void find_control(int enforce);

	inline int nb_controls();
	inline int nb_conditions();
	inline int nb_statevars();
	inline Exp* condition(int i);	// avec i = 0 .. nb_conditions()-1
	inline Exp* statevar(int i);	// avec i = 0 .. nb_statevars()-1
	inline Exp* control(int i);	// avec i = 0 .. nb_controls()-1
	inline int is_control(Exp* e);
	inline int is_condition(Exp* e);
	inline int is_statevar(Exp* e);

	//ACCES AUX INFO GENERALES :

	inline int nb_outputs();
	inline int nb_inputs();
	inline int nb_assertions();
	inline int nb_locals();
	inline Exp* output(int i);		// avec i = 0 .. nb_outputs()-1
	inline Exp* input(int i);		// avec i = 0 .. nb_input()-1
	inline Exp* assertion(int i);	// avec i = 0 .. nb_assertions()-1
	inline Exp* local(int i);	// avec i = 0 .. nb_assertions()-1

	//ACCES AUX INFOS ATTACHEES AUX Exp :
	//NB : is_output (resp. is_local) renvoie (s'il existe)
	// 1 numero d'output (resp. de local) associe a l'Exp.
	// Pour avoir TOUTS les outputs (resp. locals) associes,
	// Il faut utiliser associated_outputs (resp. associated_locals)
	// qui renvoie toute la liste.
 
	inline int is_output(Exp* e);
	inline IntList* associated_outputs(Exp* e);
	inline int is_local(Exp* e);
	inline IntList* associated_locals(Exp* e);
	inline int is_input(Exp* e);
	inline int is_assertion(Exp* e);
	inline Exp* true_exp();
	inline Exp* false_exp();
	inline Exp* bottom_exp();

	inline Exp* condact(Exp*);

	//CONSTRUCTION DE NOUVELLES EXP :
	inline NetCtr* exp_maker();
	inline Exp* not_exp(Exp* e);
	inline Exp* or_exp(Exp* e1, Exp* e2);
	inline Exp* and_exp(Exp* e1, Exp* e2);

	//CORRESPONDANCE INDICE D'OUTPUT => INDEX D'IDENT 
	inline int output_ident(int i); // avec i = 0 .. nb_outputs()-1
	inline int input_ident(int i); // avec i = 0 .. nb_input()-1
	inline int local_ident(int i); // avec i = 0 .. nb_locals()-1

	//ACCES AU TYPE :
	inline EcType* type(Exp* e);    //D'une expression
	inline EcType* type(int ident); //D'un identificateur
	inline EcType* bool_type();
	inline EcType* int_type();
	inline EcType* real_type();

	//CORRESPONDANCE index d'ident <=> chaine de car.
	inline const char* symbol(int indent);	
	inline int add_symbol(const char* str);	
	inline SymbolTable* symbols();	

	//POUR LES EXPRESSIONS "ZEROAIRES"
	IdentInfo* get_ident_info(int ident);

	//POUR LES NOEUDS "CALL"
	FuncInfo* get_func_info(int ident);

	//IMPRESSION D'UNE EXPRESSION
	// 1) Affiche en priorite l'ident associe (s'il existe)
	void print_exp(Exp* e);
	void print_exp(PtyStream* os, Exp* e);
	// 2) Ignore l'ident associe (s'il existe)
	void print_exp_def(Exp* e);
	void print_exp_def(PtyStream* os, Exp* e);

	void print_func_decl(int fi, PtyStream* os);

	//OBJETS EXTERNES
	IntList* usr_type_list();
	IntList* usr_const_list();
	IntList* usr_func_list();	
	IntList* usr_proc_list();	

	//IMPRESSION DANS DIVERS FORMATS
	inline void print_lus();
	inline void print_norm();

	//REMONTE SOURCE (sans guarantie !)
	Exp* flow2src(Exp*);
	Exp* impl2src(Exp*);
	Exp* clk2src(Exp*);
};
/* les inlines NE PAS REGARDER */

//CONDITIONS ET VARIABLES D'ETAT
inline int NetInterface::nb_conditions(){return nb_conds;}
inline Exp* NetInterface::condition(int i){return cond_tab[i];}
inline int NetInterface::is_condition(Exp* e){
	PNetInterfaceInfo* info = get_info(e);
	return (info)? info->is_cond : 0 ;
}

inline int NetInterface::nb_controls(){return nb_ctrls;}
inline Exp* NetInterface::control(int i){return ctrl_tab[i];}
inline int NetInterface::is_control(Exp* e){
	PNetInterfaceInfo* info = get_info(e);
	return (info)? info->is_ctrl : 0 ;
}

inline int NetInterface::nb_statevars(){return nb_svars;}
inline Exp* NetInterface::statevar(int i){return svar_tab[i];}
inline int NetInterface::is_statevar(Exp* e){
	PNetInterfaceInfo* info = get_info(e);
	return (info)? info->is_svar : 0 ;
}

//ENTREES, SORTIES, LOCAUX 
inline int NetInterface::nb_inputs(){return nb_ins;}
inline Exp* NetInterface::input(int i){return in_tab[i];}
inline int NetInterface::input_ident(int i){ return in_ids[i]; }

inline int NetInterface::nb_outputs(){return nb_outs;}
inline Exp* NetInterface::output(int i){return out_tab[i];}
inline int NetInterface::output_ident(int i){ return out_ids[i]; }
inline IntList* NetInterface::associated_outputs(Exp* e){
	PNetInterfaceInfo* info = get_info(e);
	return (info)? info->is_out : NULL ;
}
inline int NetInterface::is_output(Exp* e){
	PNetInterfaceInfo* info = get_info(e);
	return (info && (info->is_out))? info->is_out->head() : 0 ;
}
inline int NetInterface::is_input(Exp* e){
	PNetInterfaceInfo* info = get_info(e);
	return (info)? info->is_in : 0 ;
}

inline int NetInterface::nb_locals(){return nb_lcls;}
inline Exp* NetInterface::local(int i){return lcl_tab[i];}
inline int NetInterface::local_ident(int i){ return lcl_ids[i]; }
inline IntList* NetInterface::associated_locals(Exp* e){
	PNetInterfaceInfo* info = get_info(e);
	return (info)? info->is_lcl : NULL ;
}
inline int NetInterface::is_local(Exp* e){
	PNetInterfaceInfo* info = get_info(e);
	return (info && (info->is_lcl))? info->is_lcl->head() : 0 ;
}

//ASSERTIONS 
inline int NetInterface::nb_assertions(){return nb_asserts;}
inline Exp* NetInterface::assertion(int i){return assert_tab[i];}
inline int NetInterface::is_assertion(Exp* e){
	PNetInterfaceInfo* info = get_info(e);
	return (info)? info->is_assert : 0 ;
}

//ACCES AUX IDENT
inline const char* NetInterface::symbol(int ident){ 
	return the_net->symbol(ident);
}
inline int NetInterface::add_symbol(const char* str){ 
	return the_net->symbols()->add(str);
}
inline SymbolTable* NetInterface::symbols(){ 
	return the_net->symbols();
}
inline IdentInfo* NetInterface::get_ident_info(int ident){
	return the_net->get_ident_info(ident);
}
inline FuncInfo* NetInterface::get_func_info(int ident){
	return the_net->get_func_info(ident);
}
inline int NetInterface::name(){ return the_net->name(); }

inline Exp* NetInterface::true_exp(){ return the_net->true_exp(); }
inline Exp* NetInterface::false_exp(){ return the_net->false_exp(); }
inline Exp* NetInterface::bottom_exp(){ return the_net->bottom_exp(); }

inline Exp* NetInterface::condact(Exp* e){ return the_net->condact(e); }

inline NetCtr* NetInterface::exp_maker(){
	return (the_net->exp_maker());
}
inline Exp* NetInterface::not_exp(Exp* e){
	return the_net->exp_maker()->neg(e);
}
inline Exp* NetInterface::or_exp(Exp* e1, Exp* e2){
	return the_net->exp_maker()->operator()(OR_n, e1, e2);
}
inline Exp* NetInterface::and_exp(Exp* e1, Exp* e2){
	return the_net->exp_maker()->operator()(AND_n, e1, e2);
}

inline EcType* NetInterface::type(Exp* e){ return the_net->type(e); }
inline EcType* NetInterface::type(int ident){ return the_net->type(ident); }
inline EcType* NetInterface::bool_type(){ return the_net->bool_type();}
inline EcType* NetInterface::int_type(){ return the_net->int_type();}
inline EcType* NetInterface::real_type(){ return the_net->real_type();}

inline void NetInterface::print_lus(){ the_net->print_lus(); }
inline void NetInterface::print_norm(){ the_net->print(); }

inline IntList* NetInterface::usr_type_list(){
	return the_net->usr_type_list();
}
inline IntList* NetInterface::usr_const_list(){
	return the_net->usr_const_list();
}
inline IntList* NetInterface::usr_func_list(){
	return the_net->usr_func_list();
}
inline IntList* NetInterface::usr_proc_list(){
	return the_net->usr_proc_list();
}

inline Exp* NetInterface::flow2src(Exp* e){ return the_net->Xflow2src(e); }
inline Exp* NetInterface::impl2src(Exp* e){ return the_net->Ximpl2src(e); }
inline Exp* NetInterface::clk2src(Exp* e){ return the_net->Xclk2src(e); }

