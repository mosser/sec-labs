class BddDumpElt;
class BddDump;
class BddRestore;

/*-------------------------------------------------------
classe BddDump (resp. BddRestore) :
---------------------------------------------------------
Permet de sauvegarder dans un fichier (resp. restaurer
depuis un fichier) un ensemble de bdds sous une forme
``compacte'' (i.e. taille, temps de sauvegarde,
temps de restauration, lineaires par rapport a la taille
de la representation interne.
---------------------------------------------------------
BddDump : 
---------
- Initialise avec un nom de fichier, ou un FILE* deja ouvert
en ecriture.
- Ajout d'un bdd dans la liste des bdd a ``dumper'' grace
a la methode "add". A chaque bdd est associe un nom (char*)
qui permet de retrouver l'info lors de la restauration.
- Le dump est realise lors de la destruction.
---------------------------------------------------------
BddRestore : 
------------
- Initialise avec un nom de fichier ou un FILE* deja ouvert
en lecture. La restauration est realisee des la creation,
on peut apres acceder aux infos suivantes :
- Nombre de bdds references (methode int nb_bdds())
- Bdd d'indice i (methode GBdd bdd(int i))
- Nom du bdd d'indice i (methode char* bdd_name(int i)) 
---------------------------------------------------------
SYNTAXE :
---------
- Toutes les lignes commencant par "#" sont des
commentaires, ou des pragmas

- La premiere ligne qui commence par "@" donne des indications
sur la taille de la structure:
   "@<nb_bdds> <nb_nodes>"
N.B. Le nombre de noeuds comprend le true et le false ! 

- Definitions des noeuds : les noeuds sont indexes 
de 0 a <nb_nodes -1>.
  a) Les index 0 et 1 sont PRE-DEFINIS (resp. false et true).
  b) Les lignes commencant par "?" sont des def de if-then-else :
  "?<i1> <i2> <i3>" signifie : "if <i1> then <i2> else <i3>"
  c) Les lignes commencant par "!" sont des defs de not :
  "!<i1> <i2>" signifie : <i1> = not <i2>

- Declaration de bdds : les lignes commencant par "%" sont des
declarations de bdds :  
   "%<string>% <index>
N.B. Le nom du bdd est ``parenthese'' entre deux "%"
-------------------------------------------------------*/
class BddDump {
	int mark;
	char* outf_name;
	FILE* outf;
	FILE* tmpf;
	int nb_elts;
	int nb_nodes;
	BddDumpElt* elts;
	void init();
	void dump(BddDumpElt*);
	long rec_dump(const GBdd&);
	void print_def(char* nme, int node);
	void print_not(int res, int op);
	void print_ite(int res, int var, int high, int low);
public:
	BddDump(char* fname);
	BddDump(FILE* f);
	~BddDump();	
	void add(GBdd b, char* nme);
};

class BddRestore {
	char* inf_name;
	FILE* inf;
	int nb_elts;
	GBdd* elts;
	char** names; 
	int nb_nodes;
	GBdd* nodes;
	char line[512];
	int elts_cpt;
	int get_line();
	void set_node(int r, const GBdd& b);
	const GBdd& get_node(int i);
	void parse();
	void parse_comment();
	void parse_header();
	void parse_not();
	void parse_ite();
	void parse_decl();
public:
	BddRestore(char* fname);
	BddRestore(FILE* f);
	int nb_bdds(){ return nb_elts; }
	GBdd bdd(int i){ return elts[i]; }
	char* bdd_name(int i){ return names[i]; }
};
