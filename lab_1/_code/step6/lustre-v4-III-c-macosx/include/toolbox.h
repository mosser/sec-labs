/*
Liste generique :
- Implementation ``legere'' : une seule structure 
(i.e. pas de difference entre la tete de liste et les autres).
- NULL code la liste vide
Permet :
- insertion au debut
- insertion a la fin/concatenation
- acces a la longeur
-> NE PERMET PAS LA SUPPRESSION

Idee :
  De manière classique, chaque noeud comporte :
  - un fils (son)
  - un noeud suivant (nxt)
  De plus, pour accellerer les insertion a la fin et le
calcul de la longueur, on stocke deux infos :
  - la dernière longueur connue
  - le dernier de la liste connu
  En général, et bien que toutes les sous-listes
soient théoriquement accessibles, on accède aux méthodes
(insertion, longueur) toujours par le même élément : il
y a donc bien une ``tête de liste'' effective.
  Pour ne pas lui donner de statut particulier, on va donc
se debrouiller pour que les noeuds qui sont des tetes de liste
effectives aient leurs informations a jour (longueur et queue de liste).
Pour les autres noeuds, ces infos ne sera pas forcement a jour.
*/ 

#ifndef AddGenericList
#define AddGenericList(TYLIST, TY) \
class TYLIST {\
	int len;\
   TYLIST* lst;\
   TY son;\
   TYLIST* nxt;\
	void uplast(){\
		if(! this) return;\
		if(lst->nxt){\
			lst->uplast();\
			len = len + lst->len -1;\
			lst = lst->lst;\
		}\
	}\
public :\
	TY head(){ return son; }\
	TYLIST* tail(){ return nxt;}\
	TYLIST(TY s){ len = 1; son = s; nxt = 0; lst = this; }\
	int length(){ if(! this) return 0; uplast(); return len; }\
	TYLIST(TY s, TYLIST* t){\
		son = s;\
		nxt = t;\
		if(t){ len = t->len+1; lst = t->lst; }\
		else { len = 1; lst = this; }\
	}\
	~TYLIST(){ if(nxt) delete nxt; }\
	TYLIST* append(TYLIST* l){\
		if(! l) return this;\
		if(this){\
			uplast();\
			l->uplast();\
			lst->len += l->len;\
			lst->nxt = l;\
			lst->lst = l->lst;\
			if(lst != l->lst){\
				len += l->len;\
				lst = l->lst;\
			}\
			return this;\
		} else {\
			return l;\
		}\
	}\
	TYLIST* append(TY s){\
		TYLIST* l = new TYLIST(s);\
		return append(l);\
	}\
	void concat(TYLIST* l){\
		if(l){\
			uplast();\
			l->uplast();\
			lst->len += l->len;\
			lst->nxt = l;\
			lst->lst = l->lst;\
			if(lst != l->lst){\
				len += l->len;\
				lst = l->lst;\
			}\
		}\
	}\
};
#endif


AddGenericList(IntList, int)

/*-------------------------------------------------------------------------
  	module   : pty.h
   date     : 25/11/96
   auteurs  : Pascal Raymond
----------------------------------------------------------------------------
   nature :  class PtyStream :
	Pretty print : gere les tabulation et limite la longeur des lignes.
La tabulation est une chaine de caractere quelconque (par defaut, 3 espaces)
La longueur d'une ligne est par defaut de 80 caracteres

----------------------------------------------------------------------------
	(C = constructeur, M = methode, F = fonction)

	1) Construction :

C  PtyStream(int lline=80,char* tabs=0)          Sur stdout
C  PtyStream(char* ,int lline=80,char* tabs=0)   Avec un nom de fichier 
C  PtyStream(FILE* ,int lline=80,char* tabs=0)   Avec un fichier deja ouvert

	2) Destruction :
ATTENTION ! Important car 'flushe' et ferme le fichier

	3) Impression :
M  put(char* fmt, ...)     Au format 'printf'
M  put(int)                Un entier
M  put(float)              Un flotant
M  flush()                 Vide le buffer
M  cr()                    Retour charriot (+ tabulation courante)
M  lf()                    Retour charriot (sans tabulation) 
M  tab()                   Pose une tabulation (effectif au prochain rc)
M  untab()                 Supprime une tab.   (effectif au prochain rc)

	3.bis) Impression (evoluee) :
M  vput(char* fmt, va_list args)  Au format 'vprintf'

	4) Acces :
M  FILE* file()         Retourne le fichier associe UTILISER AVEC PRECAUTION !

----------------------------------------------------------------------------
   modifs :
----------------------------------------------------------------------------
14/05/97 :
Classe derivee "TmpPtyStream" pour la gestion de fichier temporaires.

	1) Construction :
C  TmpPtyStream(int lline=80,char* tabs=0) 
=> Ouvre un NOUVEAU fichier temporaire,

	2) Destruction :
=> ATTENTION ! Une fois detruit, le contenu du fichier est perdu !

	3) Ecriture :
=>Utiliser les put(), cr(), tab etc.. de la methode de base.

	4) Recopie et destruction :
La methode put de la classe de base est surchargee :
M  PtyStream::put(TmpPtyStream*)
Le contenu du fichier temporaire est integralement recopie


--------------------------------------------------------------------------*/


#ifndef __PR_PTY_H
#define __PR_PTY_H

#include <memory.h>
#include <stdarg.h>

class PtyStream; 
class TmpPtyStream; 

class PtyStream {
protected:
	FILE* fichier;
	char* file_name;
	char tabstring[20];
	int tabnumber;
	int lline;
	int llinemax;
public:

	PtyStream(int lline=80,char* tabs=0);

	PtyStream(char* ,int lline=80,char* tabs=0) ;

	PtyStream(FILE* ,int lline=80,char* tabs=0) ;

	~PtyStream();

	void put(TmpPtyStream*);

	void put(const char* fmt, ...);

	//La version "basique" :
	void vput(const char* fmt, va_list args);

	void put(int);

	void put(float);

	void flush();
	
	void tab(){tabnumber+=1;}

	void untab();

	void space(){put(" ");} 

	void cr();

	void lf();

	void mark() { } 

	void unmark(){ }

	FILE* file(){ return fichier; }

};

class TmpPtyStream : public PtyStream {
public:
	TmpPtyStream(int lline=80,char* tabs=0);
};

#endif

/*-------------------------------------------------------------------------
  	module : symbols.h
   date     : 27/09/95
   auteurs  : Pascal Raymond
----------------------------------------------------------------------------
   nature : class SymbolTable :
	Gere une correspondance entre chaine de caractere et entiers
----------------------------------------------------------------------------
	17 juin 2000 :
	class SymbolInfos :
		permet d'associer des informations aux identificateurs d'une SymbolTable.	
		- plusieurs SymbolInfos pour une meme SymbolTable
		- destruction
----------------------------------------------------------------------------
(C = constructeur, M = methode, F = fonction)

C  SymbolTable()              Creation
M  int add(char* n)           Associe un index unique a 'n'
M  Bool find(char* n)        	True si 'n' est dans la table 
M  Bool find_then_add(int* res, char* fmt ...);
                              Combine 'find' et 'add' 
                              (index unique dans 'result')
M  Bool find_then_get(int* res, char* fmt ...)
                              Recherche 'n' dans la table,
                              renvoie true + l'index dans 'result'
                              Ne modifie pas la table sinon
M  char* operator[](int i)    Rends la chaine no 'i'
M  int card()                 Nombre de chaines dans la table
M  void print()               Imprime le contenue de la table


----------------------------------------------------------------------------
   modifs :
----------------------------------------------------------------------------
   11/03/97 la méthode "SymbolTable::add" prend en entree un format
		(comme printf) et une liste variable de parametres.
		i.e. pour find et find_then_add.
	N.B. LE PROFIL DE "find_then_add" a change !
	(on a garde le vieux code quand meme).
--------------------------------------------------------------------------*/

#ifndef __PR_SYMBOLS_H
#define __PR_SYMBOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <memory.h>

#ifndef Bool
typedef int Bool;
#endif

#ifndef False
#define False ((int)0)
#endif
#ifndef True
#define True ((int)1)
#endif

struct STapePage;			//Type des pages memoire utilisees par le ruban 
struct STapeHashItem;	//Type des elements de la table de hash du ruban
class StringTape;			//Type du ruban
class SymbolTable;		//Table de symbole INCLUANT un ruban

struct STapeHashItem {
	char* value;
	int index;
	STapeHashItem* next;
	STapeHashItem(char* v, int i, STapeHashItem* n){
		next = n;
		index = i;
		value = v;
	}
	STapeHashItem(){next = (STapeHashItem*)NULL;};
	~STapeHashItem(){
		if(next) delete next;
	}

};

//Au pif :
#define __PR95_STRING_TAPE_PAGE (16380)

//Recommandee par le dragon :
//#define __PR95_STRING_TAPE_HASH_SIZE 211	
#define __PR95_STRING_TAPE_HASH_SIZE 5041 

struct STapePage {
	STapePage* next;
	char tab[__PR95_STRING_TAPE_PAGE];
	STapePage(){next = (STapePage*)NULL;};	
	STapePage(STapePage* n){next = n;};	
	~STapePage(){
		if(next) delete next;
	}
};

class StringTape {
friend class SymbolTable;
protected :
	int hash_code(char* nme); //hashcode de nme
private :
	//Table de hash :
	STapeHashItem** hash_table;
	int hash_size;

	//recherche de nme dans list
	STapeHashItem* search(STapeHashItem* list, char* nme); 

	//Nombre d'elements :
	int nb_strings;
	//Nombre de cases occupe'es dans la hash-tab :
	int nb_occupied;
	//Nombre de collisions max dans la hash-tab :
	int nb_col_max;

	//Gestion de la memoire : le "ruban" est constitue d'une
	//liste de pages alouees au fur et a mesure des besoins
	STapePage* cur_page;
	int free_in_cur_page;	
	char* ruban;
	char* new_string(char* value);
	void init(int hsz);
protected :
	//recherche de nme dans la table
	STapeHashItem* internal_find(char* nme);
	STapeHashItem* internal_add(char* nme);
public :
	~StringTape();
	//Creation avec taille de la hash-tab :
	StringTape(int hsz){ init(hsz); }
	//Creation taille par defaut de la hash-tab :
	StringTape(){ init(__PR95_STRING_TAPE_HASH_SIZE); }
	//Recherche et (eventuelle) insersion de n :
	char* add(char* n){
		return internal_add(n)->value;
	};
	//Recherche SANS insertion de n :
	char* find(char* n){
		STapeHashItem* r = internal_find(n);
		return (r)? (r->value) : (char*)NULL;
	};
	int card(){ return nb_strings; };
	void print_statistics(FILE* f){
		fprintf(f,"hash size  : %5d\n", hash_size);
		fprintf(f,"occupied   : %5d\n", nb_occupied);
		fprintf(f,"coll max   : %5d\n", nb_col_max);
		fprintf(f,"nb strings : %5d\n", nb_strings);
	}
};

/* Gestion d'un "tableau" non borne de chaines de caracteres */

class StringArray {
	char** page;
	int page_size;
	StringArray* next_part;
	int bound;
	int first_index;
public:
	StringArray(int s, int fi = 0){
		page_size = s;
		page = new char*[page_size];	
		next_part = (StringArray*)NULL;
		bound = -1;
		first_index = fi;
	}
	~StringArray(){
		if(next_part)
			delete next_part;
		delete[] page;
	}
	char*& operator[](int i){
		if(i < page_size){
			if(i > bound) bound = i;
			return page[i];
		} else {
			if(! next_part){
				bound = page_size-1;
				next_part = new StringArray(page_size, first_index+page_size);
			}
			return (*next_part)[i - page_size];
		}
	}	
	void print(){
		for(int i = 0; i <= bound; i++){
			printf("%d: ", first_index+i);
			if(page[i]){
				printf("\"%s\"\n", page[i]);
			} else {
				printf("null\n");
			}
		}
		if(next_part) next_part->print();
	}
	int size(){
		if(bound < page_size-1){
			return bound+1;
		} else {
			if(next_part) return (next_part->size()+page_size);
			else return page_size;
		}
	}
};

class SymbolTable {
	int nb_symbols;
	StringTape* strings;
	int table_page_size ;
	StringArray* table;
	inline void init(int psz){
		table_page_size = psz;
		nb_symbols = 0;
		table = new StringArray(table_page_size); 
	}
public:

	SymbolTable(){
		init(1000);
		strings = new StringTape();
	};
	SymbolTable(int max){
		init(max);
		strings = new StringTape();
	};
	SymbolTable(int max, int hz){
		init(max);
		strings = new StringTape(hz);
	};
	~SymbolTable(){
		delete table;
		delete strings;
	};
	int add(const char* fmt, ...);
	int vadd(const char* fmt, va_list args);
	int find(const char* fmt, ...);
	int find_then_add(int* result, const char* fmt, ...);
//17-02-99
	int find_then_get(int* result, const char* fmt, ...);
//11-03-97 : version obsolete :
	//int find_then_add(char* nme, int* result){
		//return find_then_add(result, nme);
	//}
	inline char* operator[](int i){
		return (*table)[i-1];
	};
	int card(){ return nb_symbols; };
	void print();
	void print_statistics(FILE* f);

	int hash_code(char* s){
		return strings->hash_code(s);
	}
};

#endif
/* -------------------------------------------------------------------------
Projet : UTILITAIRES
Module : symbol
----------------------------------------------------------------------------
Classes: Symbol 
----------------------------------------------------------------------------
Représentation unique de chaines de caractères.
N.B. TYPE ABSTRAIT : s'utilise comme un type de base (int)
----------------------------------------------------------------------------
N.B. Pour l'instant : c'est juste une couche au dessus de la ``vielle''
SymbolTable. Un Symbol est donc en fait juste un entier qui pointe sur
une SymbolTable particulière (à laquelle l'utilisateur n'a pas accès)
----------------------------------------------------------------------------
Modifs :
--------------------------------------------------------------------------*/

class Symbol {
public:
/************************************************
          INTERFACE UTILISATEUR                                             
************************************************/
//-----------------------------------------------
// GENERALITES
//-----------------------------------------------
// Necessaire pour que les instances de Symbol 
// se comportent comme des rvalues classiques
// (aussi simple qu'un entier !)
//-----------------------------------------------
// - Initialisation + affectation (pour "Symbol toto = ;")
// - affectation
//-----------------------------------------------
// - Initialisation vide, pour :
// "Symbol toto;"
//-----------------------------------------------
	Symbol();
//-----------------------------------------------
// - Affectation, pour :
// "toto = exp;" ou exp est de type Symbol
//-----------------------------------------------
	Symbol& operator=(const Symbol&);
//-----------------------------------------------
// - Initialisation + affectation, pour :
// "Symbol toto = exp;" ou exp est de type Symbol
//-----------------------------------------------
	Symbol(const Symbol&);
//-----------------------------------------------
// - Destructeur, appel :
//   . implicite lors de la sortie du scope (pile)
//   . explicite lors d'un delete (tas)
//-----------------------------------------------
	~Symbol();
//-----------------------------------------------
// OPERATEURS STANDARD
//-----------------------------------------------
// - Comparaison
//-----------------------------------------------
	friend int operator==(const Symbol& , const Symbol& );
	friend int operator!=(const Symbol& , const Symbol& );
//-----------------------------------------------
// SYMBOLE NULL
//-----------------------------------------------
// - Teste la nulité 
// x.is_null() <=> x == Symbol::null()
//-----------------------------------------------
	int is_null();
	static Symbol null();
//-----------------------------------------------
// CORRESPONDANCE Symbol <-> char* 
//-----------------------------------------------
// - Initialisation à une chaine (à la printf)
// - Affectation à une chaine
// N.B. gcc interdit les operator= à plus d'un argument,
// d'ou la méthode "set" (à la printf) 
// - chaine associée (NULL si Symbol == null_symbol())
// N.B. Dans les deux cas, la chaine peut être
// ``volatile'', elle est recopiée de toute manière
// en interne.
// N.B. INTERDICTION ABSOLUE DE MODIFIER LES
// résultats de "string" !!!
//-----------------------------------------------
	Symbol(const char* fmt, ...);
	Symbol& operator=(const char* str);
	Symbol& set(const char* fmt, ...);
	const char* string();
//-----------------------------------------------
// HASH CODE
//-----------------------------------------------
// Retourne un entier qui ne depend QUE de la 
// chaine de caractere.
// N.B. Pas une bijection !
//-----------------------------------------------
	int hash_code();
//-----------------------------------------------
// UNIQ CODE
//-----------------------------------------------
// Retourne un entier qui ne depend QUE de la 
// chaine de caractere.
// N.B. BIJECTION : peut-être utilisé pour
// obtenir un ordre TOTAL sur les Symbols
// N.B. RIEN A VOIR AVEC L'ORDRE LEXICOGRAPHIQUE !!!
//-----------------------------------------------
	int uniq_code();
/************************************************
     FIN  INTERFACE UTILISATEUR                                             
************************************************/
private:
	//Gestionnaire de chaine
	static SymbolTable manager;
	int value;
protected:
friend class Symbol2Info;
friend class Symbol2Symbol;
	int index() const { return value; }
	void set_value(int v){
		value = v;
	}
};

AddGenericList(SymbolList, Symbol)
/*
inline Symbol::Symbol(){
	value = 0;
	//GC? => ajouter aux vivants 
}
inline Symbol::Symbol(const Symbol& sym){
	value = sym.value;
	//GC? => ajouter aux vivants 
}
inline Symbol::Symbol(char* fmt, ...){
	va_list args;
	va_start(args,fmt);
	value = Symbol::manager.add(fmt, args);
	//GC? => ajouter aux vivants 
}
inline Symbol::~Symbol(){
	//GC? => supprimer des vivants 
}
inline Symbol& Symbol::operator=(const Symbol& s){
	value = s.value;
	return *this;	
}
inline Symbol& Symbol::operator=(char* str){
	value = Symbol::manager.add(str);
	return *this;
}
inline Symbol& Symbol::set(char* fmt, ...){
	va_list args;
	va_start(args,fmt);
	value = Symbol::manager.add(fmt, args);
	return *this;
}
inline int Symbol::is_null(){
	return (value)? 0 : 1;
}
inline const char* Symbol::string(){
	return (value)? Symbol::manager[value] : NULL;
}
inline int operator==(const Symbol& sym1, const Symbol& sym2){
	return (sym1.value == sym2.value);
}
inline int operator!=(const Symbol& sym1, const Symbol& sym2){
	return (sym1.value != sym2.value);
}
inline int Symbol::hash_code(){
	return Symbol::manager.hash_code((char*)string());
}
*/
/* -------------------------------------------------------------------------
Projet : UTILITAIRES
Module : key2info 
----------------------------------------------------------------------------
Classes: 
	key2Info
----------------------------------------------------------------------------
Table d'association Key => Info
Ou simplement, ensemble de Key (associés à NULL par défaut)
----------------------------------------------------------------------------

Pour ne pas avoir de templates :
on utilise des 
- GenericKey (ulong)
- GenericInfo (void*)

Pour avoir un toto2titi propre il est VIVEMENT RECOMMANDE
de dériver une classe qui caste PROPREMENT :
- le ou les créateurs, qui force l'initialisation de la table :
	toto2titi : key2info() { ......}
- le add
- les deux get
- le occupied
- le iterate

Pour des titi/toto qui sont TOUS LES DEUX des r-value
(i.e. castable directement) on a une macro qui fait ça :

AddKey2Info(TABTYP, KEYTYP, INFOTYP)

N.B. int -> int est prédéfini :

AddKey2Info(Int2Int, int, int)

----------------------------------------------------------------------------
N.B. De manière interne, il s'agit d'une structure "mixte" : arbre
binaire de recherche balancé, dont les noeuds sont des tableaux de taille fixe.
Le "tag" utilisé pour la comparaison est l'index des Int (protégé).
Cet index est purement interne et n'a en particulier rien a voir
avec l'ordre lexicographique !
D'après les benchs effectués, marche très bien : n*log(n) pour l'insertion
aléatoire, n pour l'insertion "ordonnée". Supporte sans problème
des ensembles de plusieurs centaines de milliers de Int.
----------------------------------------------------------------------------
Modifs :
--------------------------------------------------------------------------*/

#ifndef KEY2INFO_H
#define KEY2INFO_H

typedef unsigned long GenericKey ;
//typedef void* GenericInfo ;
typedef unsigned long GenericInfo ;

typedef void (*GenericInfoDelFunc)(GenericInfo);

/* CLASSE PRIVEE : NE PAS UTILISER */
class Key2InfoItem ;

class Key2Info {
private:
	//Pour être sur que ça va pas foirer ... 
	static int _do_init_class;
	static int _init_class();

	void init(GenericInfoDelFunc delcb );
/************************************************
          INTERFACE UTILISATEUR                                             
************************************************/
public:
//-----------------------------------------------
// CONSTRUCTION ET DESTRUCTION
//-----------------------------------------------
// N.B. Est bien évidemment incapable de détruire
// les infos (dont le type n'est pas connu) =>
// utiliser le mécanisme d'itération s'il y a lieu. 
// SI ON PASSE A LA CONSTRUCTION UNE FONCTION
// DE DESTRUCTION, ELLE SERA APPELLEE CHAQUE FOIS
// QU'UN ELEMENT EST VIRE, ET A LA DESTRUCTION AUSSI
//-----------------------------------------------
	Key2Info( GenericInfoDelFunc delcb ){ init(delcb); }
	Key2Info(){ init( (GenericInfoDelFunc)NULL ); }
	~Key2Info();
//-----------------------------------------------
// NETTOYAGE TOTAL
//-----------------------------------------------
	void clear();
//-----------------------------------------------
// NETTOYAGE PARTIEL 
// On passe en param la fonction à détruire l'info
// ou rien du tout...
//-----------------------------------------------
	void remove( GenericKey ix );
//-----------------------------------------------
// AJOUT D'ELEMENTS
//-----------------------------------------------
// - Avec une info
// - Sans info (association à NULL par défaut)
//-----------------------------------------------
	void add(GenericKey ix, GenericInfo in);
	void add(GenericKey ix);
//-----------------------------------------------
// RECHERCHE D'INFOS 
//-----------------------------------------------
// - Le get simple renvoie NULL si :
//   . pas d'association pour s
//   . s associé à NULL 
// - Le get a deux arguments renoie :
//   . 0 si pas d'association pour s
//   . 1 + l'info associé dans res sinon
// - occupied renvoie :
//   . 0 si pas d'association 
//   . 1 sinon
//-----------------------------------------------
	GenericInfo get(GenericKey ix);
	bool get(GenericKey ix, GenericInfo* res);
	bool occupied(GenericKey ix);
//-----------------------------------------------
// MECANISME D'ITERATION
//-----------------------------------------------
// - init_iterate : comme son nom l'indique ...
// - end_iterate : stoppe l'iteration en cours
// - iterate : un pas d'itération
//   . 0 si fini
//   . 1 + le Inte dans cursymb
//       + L'info associée dans curinfo
//-----------------------------------------------
// N.B. Ne pas inserer dans une table en cours
// d'itération : le comportement est non défini !
//-----------------------------------------------
	void init_iterate();
	void end_iterate();
	bool iterate(GenericKey* curindex, GenericInfo* curinfo);
//-----------------------------------------------
// IMPRESSION SOUS FORME D'ARBRE 
//-----------------------------------------------
// Pour debug uniquement !
//-----------------------------------------------
	void print();
/************************************************
     FIN  INTERFACE UTILISATEUR                                             
************************************************/
protected:
	//Head of the tree structure
	Key2InfoItem* head;
	//First of the list structure
	Key2InfoItem* first;
	//Iteration
	bool iterating;
	Key2InfoItem* cur_tab;
	GenericKey cur_elt;
	//Info delete callback
	GenericInfoDelFunc _delinfo_callback;
};

//--------------------------------------------------------------------------------
// MACRO : force le typage des infos
//--------------------------------------------------------------------------------
#define AddKey2Info(TABTYP, KEYTYP, INFOTYP) \
class TABTYP : public Key2Info {\
public:\
	TABTYP():Key2Info(){}\
   void add(KEYTYP ix, INFOTYP in){\
      Key2Info::add((GenericKey)ix, (GenericInfo)in);\
   }\
   INFOTYP get(KEYTYP ix){\
      return (INFOTYP)Key2Info::get((GenericKey)ix);\
   }\
   bool get(KEYTYP ix, INFOTYP* res){\
      return Key2Info::get((GenericKey)ix, (GenericInfo*)res);\
   }\
   bool occupied(KEYTYP ix){\
      return Key2Info::occupied((GenericKey)ix);\
   }\
   bool iterate(KEYTYP* curindex, INFOTYP* curinfo){\
      return Key2Info::iterate((GenericKey*)curindex, (GenericInfo*)curinfo);\
   }\
};

//--------------------------------------------------------------------------------
// CLASSE PRIVEE : implemente un noeud de l'arbre de recherche
//--------------------------------------------------------------------------------
//You may change this value (better with 2^n)
#define KEY2INF_ULONG_NB 1
//Don't modify those constants !
#define KEY2INF_ULONG_SIZE (sizeof(unsigned long) * 8)
#define KEY2INFO_ARRAY_SIZE (KEY2INF_ULONG_SIZE * KEY2INF_ULONG_NB)

class Key2InfoItem {
friend class Key2Info;
	//INFORMATIONS ASSOCIATED TO INDEXES
	GenericInfo info[KEY2INFO_ARRAY_SIZE];
	//PRESENCE OF INFORMATION FOR EACH INDEXES
	unsigned long present[KEY2INF_ULONG_NB];
	//THE INDEX OF THE ARRAY IN THE GLOBAL STRUCTURE 
	GenericKey array_index;
	//THE SIZE OF THE SUB-TREE
	//(USED TO BALANCE THE TREE)
	int size;
	//HIGHER AND LOWER INDEXES SUB-TREES
	Key2InfoItem* hpart;
	Key2InfoItem* lpart; 
	//Internal chain for iteration
	Key2InfoItem* next;

	//Info delete callback is specified BY THE MANAGER
	//at the construction
	GenericInfoDelFunc _delinfo_callback;
protected:
	Key2InfoItem(GenericKey set,
		Key2InfoItem* h,
		Key2InfoItem* l,
		GenericInfoDelFunc delcb
	);
	//add is the only method that can create instances
	//so it must be called with the callback proc
	Key2InfoItem* add(
		GenericKey ix,     //array index
		GenericKey elt,    //elt index in array
		GenericInfo in,   //info
		Key2InfoItem** first, //first of the iterate list
		Key2InfoItem* prec,    //known prec in the iterate list
		GenericInfoDelFunc delcb //delete info callback (in case a node is created)
	);
	~Key2InfoItem();
	void add_elt(GenericKey elt, GenericInfo in);
	void rec_print(char* pfx, int lp, int hp);
	bool get_elt(GenericKey elt, GenericInfo* res);
	bool get(GenericKey set, GenericKey elt, GenericInfo* res);
	void remove(GenericKey ix, GenericKey elt);
	void remove_elt(GenericKey elt);
	void print();
};

//--------------------------------------------------------------------------------
// PREDEFINITION DE Key2Int
//--------------------------------------------------------------------------------
AddKey2Info(Int2Int, int, int)


#endif /* KEY2INFO_H */
/* -------------------------------------------------------------------------
Projet : UTILITAIRES
Module : symbol2info 
----------------------------------------------------------------------------
Classes:
--------

Symbol2Info : Symbol -> void*
Symbol2Int  : Symbol -> int
Int2Symbol  : int -> Symbol
Symbol2Symbol : Symbol -> Symbol

Macro :
-------

AddSymbol2Info(tabtyp, typ) : Symbol -> typ (uniquement r-value !)

N.B. Toutes ces classes sont basées sur key2info (unsigned long -> void*)
on utilise à fond la correspondance Symbol <-> char* 

--------------------------------------------------------------------------*/

#ifndef SYMBOL2INFO_H
#define SYMBOL2INFO_H

//----------------
// Symbol -> void*
//----------------
class Symbol2Info : public Key2Info {
public:
	Symbol2Info():Key2Info(){}
	Symbol2Info(GenericInfoDelFunc dicb):Key2Info(dicb){}
	//Ajouter
	void add(const Symbol& ix){
		Key2Info::add((GenericKey) ix.index());
	}
   void add(const Symbol& ix, GenericInfo in){
      Key2Info::add((GenericKey) ix.index(), in);
   }
	//Remettre à vide
	void remove(const Symbol& ix){
		Key2Info::remove((GenericKey) ix.index());
	}
	//Rechercher
   GenericInfo get(const Symbol& ix){
      return Key2Info::get((GenericKey) ix.index());
   }
   bool get(const Symbol& ix, GenericInfo* res){
      return Key2Info::get((GenericKey) ix.index(), res);
   }
   bool occupied(const Symbol& ix){
      return Key2Info::occupied((GenericKey) ix.index());
   }
	//Iterer
   bool iterate(Symbol* curindex, GenericInfo* curinfo){
		GenericKey curint = 0;
      bool res = Key2Info::iterate(&curint, curinfo);
		curindex->set_value((int)curint);
		return res;
   }
};

//--------------------------------------------------------------------------------
// MACRO : Symbol -> typ
//--------------------------------------------------------------------------------
#define AddSymbol2Info(TABTYP, TYP) \
class TABTYP : public Symbol2Info {\
public:\
	TABTYP():Symbol2Info(){}\
   void add(const Symbol& ix, TYP in){\
      Symbol2Info::add(ix, (GenericInfo)in);\
   }\
   TYP get(const Symbol& ix){\
      return (TYP)Symbol2Info::get(ix);\
   }\
   bool get(const Symbol& ix, TYP* res){\
      return (bool)Symbol2Info::get(ix, (GenericInfo*)res);\
   }\
   bool occupied(const Symbol& ix){\
      return (bool)Symbol2Info::occupied(ix);\
   }\
   bool iterate(Symbol* curindex, TYP* curinfo){\
      return Symbol2Info::iterate(curindex, (GenericInfo*)curinfo);\
   }\
};

//--------------
// Symbol -> int
//--------------
AddSymbol2Info(Symbol2Int, int)

//----------------
// int -> Symbol
//----------------
class Int2Symbol : public Key2Info {
public:
	Int2Symbol():Key2Info(){}
	//Ajouter
   void add(GenericKey ix, Symbol in){
		char* str = (char*)(in.string());
      Key2Info::add(ix, (GenericInfo)str);
   }
	//Rechercher
   Symbol get(GenericKey ix){
      return Symbol((char*)(Key2Info::get(ix)));
   }
   bool get(GenericKey ix, Symbol* syres){
		char* stres;
      //bool res = (bool)Key2Info::get(ix, &((GenericInfo)stres));
      bool res = (bool)Key2Info::get(ix, (GenericInfo*)(&stres));
		*syres = Symbol(stres);
		return res;
		
   }
	//Iterer
   bool iterate(GenericKey* curindex, Symbol* curinfo){
		char* curstring = NULL;
      //bool res = Key2Info::iterate(curindex, &((GenericInfo)curstring));
      bool res = Key2Info::iterate(curindex, (GenericInfo*)(&curstring));
		*curinfo = Symbol(curstring);
		return res;
   }
};

//-----------------
// Symbol -> Symbol
//-----------------

class Symbol2Symbol : public Key2Info {
public:
   Symbol2Symbol():Key2Info(){}
   //Ajouter
   void add(const Symbol& ix, Symbol in);
   //Rechercher
   Symbol get(const Symbol& ix);
   bool get(const Symbol& ix, Symbol* syres);
   bool occupied(const Symbol& ix);
   //Iterer
   bool iterate(Symbol* curindex, Symbol* curinfo);
};

#endif /* SYMBOL2INFO_H */
/*-------------------------------------------------------------------------
  	module   : errors.h
   date     : 25/11/1996 
   auteurs  : Pascal Raymond
----------------------------------------------------------------------------
10-2003 : révision
	On rajoute les versions en va_list
----------------------------------------------------------------------------
   nature :  Gestion des erreurs et des messages (sur stderr) :
----------------------------------------------------------------------------
	(C = constructeur, M = methode, F = fonction)
-----------------------------------------------------
F  set_errors_tool_name(char*)     Definit un prefixe aux messages d'erreur
F  IError(const char* fmt, ...)          'internal error' et exit  
F  Error(const char* fmt, ...)           'error' et exit  
F  GError(const char* fmt, ...)          'error' sans exit
F  GErrors()                       Le nombre d'appel de GError
F  GErrorRecover()                 Exit si GError avant 
F  Warning(const char* fmt, ...)         'warning' (sans exit)
F  set_verbose_mode()              Passe en mode verbeux niveau 1
F  set_verbose_mode(int i)         Passe en mode verbeux niveau i
                                      (0 pour non-verbeux)
F  int Verbose()                   Le mode verbeux courant
F  Verbose(const char* fmt, ...)         Affiche message si mode verbeux >= 1
F  Verbose(int i, const char* fmt, ...)  Affiche message si mode verbeux >= i 

--> les même en version "va_list"
F  vaIError(const char* fmt, va_list args)          'internal error' et exit  
F  vaError(const char* fmt, va_list args)           'error' et exit  
F  vaGError(const char* fmt, va_list args)          'error' sans exit
F  vaWarning(const char* fmt, va_list args)         'warning' (sans exit)
F  vaVerbose(const char* fmt, va_list args)         Affiche message si mode verbeux >= 1
F  vaVerbose(int i, const char* fmt, va_list args)  Affiche message si mode verbeux >= i 
----------------------------------------------------------------------------
   modifs :

--------------------------------------------------------------------------*/

#include <stdarg.h>

#ifndef __PR_ERRORS_H
#define __PR_ERRORS_H

extern void IError(const char* fmt, ...);
extern void Error(const char* fmt, ...);
extern void GError(const char* fmt, ...);
extern int GErrors();
extern void GErrorRecover();
extern void Warning(const char* fmt, ...);
extern void set_errors_tool_name(const char* tn);
extern void set_verbose_mode();
extern void set_pipe_mode();
extern void set_verbose_mode(int i);
extern int Verbose(const char* fmt, ...);
extern int Verbose(int i, const char* fmt, ...);
extern int Verbose();
#define VERBOSE(X,Y) {if(Verbose() >= X) { Y; }}

extern void  vaIError(const char* fmt, va_list args);
extern void  vaError(const char* fmt, va_list args);
extern void  vaGError(const char* fmt, va_list args);
extern void  vaWarning(const char* fmt, va_list args);
extern int  vaVerbose(const char* fmt, va_list args);
extern int  vaVerbose(int i, const char* fmt, va_list args);

extern int VerboseWheel(int step);

inline int PERCENT(int c, int m){
	return (100*(m-c)/m);
}

#endif
/*-------------------------------------------------------------------------
   module   : errors.h
   date     : 25/11/996
   auteurs  : Pascal Raymond
----------------------------------------------------------------------------
   nature :  Utilisation de "bitstrings" pour la representation d'ensembles.
  		 
VarSet : cette classe permet de definir une instance de variable
	de type "ensemble". 
	ATTENTION un set est defini comme un sous-ensemble de l'intervalle entier 1..n
LES ELEMENTS SONT NUMEROTES DE 1 a N !
  
SetTable : cette classe permet de gerer un grand nombre de "constantes"
  	de type ensemble, ayant toutes la meme taille maximale.
  
MonomialTable : est une adaptation de SetTable qui permet de gerer des
  	constantes "monomes"
----------------------------------------------------------------------------
   modifs :
--------------------------------------------------------------------------*/

#ifndef __PR_SETS_H
#define __PR_SETS_H

#ifndef Bool
#define Bool int
#endif
#ifndef True
#define True  ((int)1)
#endif
#ifndef False
#define False ((int)0)
#endif
 
typedef unsigned int BitString;

class VarSet {
	int current;
	int size;
	int tab_size;
	BitString* tab;
public :

	VarSet(int sz);		//Construction
	VarSet(VarSet* s);	//Construction
	~VarSet();				//Destruction

	void set_empty();// REMISE a "vide"
	void set_all(int max);//MISE a {1,2, ... , max} 
	void set_all(){ set_all(size); };//MISE a {1,2, ... , size} 
	Bool operator()(int);// APPARTENNANCE d'un element (style fonctionnel)

	// PROCEDURE D'ENUMERATION de l'ensemble
	void reset(){current = 0;}//Prepare l'enumeration
	int operator()();//Renvoie 0 si on a enumere tous les elements

	void add(int);// INCLURE un nouvel element
	void sub(int);// SOUSTRAIRE un element

	//TOUTES les operations sur les sets se font avec stockage
	//implicite, pour eviter le passage de structure (cher)
	void operator=(VarSet&);
	void operator|=(VarSet&);// UNION
	void operator&=(VarSet&);// INTERSECTION
	void operator-=(VarSet&);// SOUSTRACTION 

	//Les memes avec des BitStrings en parametre :
	void operator=(BitString*);
	void operator|=(BitString*);// UNION
	void operator&=(BitString*);// INTERSECTION
	void operator-=(BitString*);// SOUSTRACTION 

	//IMPRESSION :
	void print();

	//DIVERS :
	int card();// RENVOIE le cardinal le l'ensemble courant
	Bool empty();// ENSEMBLE VIDE : teste si l'ensemble courant est vide
	Bool cuts(VarSet* ps); //teste si l'inter. avec *ps n'est pas vide

	//COMPARAISONS :
	Bool operator<=(VarSet&); //Inclusion
	Bool operator==(VarSet&); //Egalite


};

/***************************************************************************
	CLASSE SetTable
****************************************************************************
	Cette classe permet de manipuler un "grand" nombre de constantes
"ensembles" (Set) : les constantes Set sont de simples chaines de bits
organisees en chaine de taille "BitString" ; 
le role de la StateTable est d'associer un index unique a
une chaine de bit particuliere (via une table de hash-code). 
	Pour introduire un nouveau Set dans la table, il faut passer par 
un "tampon" :
	tamp_reset() remet le tampon a "vide"
	tamp_set_true(int i)  insere le ieme elemnent dans le tampon
	tamp_set_false(int i)  extrait le ieme element du tampon
	int tamp_put() insere le tampon dans la table et renvoie un index unique,
renvoie -1 si plus de place.

***************************************************************************/

#define SET_HASH_SIZE 2047

class SetTable {
protected :
	int set_size; //L'aritee d'un Set
	int max_elts; //Le nombre max d'elements
	int base_size; //Le nombre de BitString pour un Set 

	//Tableaux des chaines de bits :
	BitString* elts_tab;
	int nb_elts;
	int head_index; //simplement nb_elts*base_size

	//Tampon :
	BitString* tampon;

	//Table de hash : elle gere les index de elts_tab deja attribues
	//N.B. un index de cette table indique le premier BitString associe
	//a un Set, et non pas l'index du Set lui-meme (il faut divise par
	//base-size pour obtenir celui-ci)
	IntList* hash_tab[SET_HASH_SIZE];

	int code_tampon();
	Bool compare_tampon(BitString*);

	//Parcours de l'ensemble :
	int current;
public :
	//------------------------------------
	// Creation :
	//------------------------------------
	SetTable(int set_sz, int max_elts);	
	~SetTable();

	//------------------------------------
	// Manipulation du tampon :
	//------------------------------------
	void tamp_reset();
	void tamp_set_true(int i);
	void tamp_set_false(int i);
	void tamp_or(BitString* op);
	int tamp_put();
	BitString* tamp_value(){ return tampon;};

	//	 Acces a un element (indexation) :
	//------------------------------------
	// "i" est l'index logique : resultat 
	// d'un appel de tamp_put. 
	//------------------------------------
	BitString* operator[](int i){ 
		return (elts_tab + (i * base_size));
	};
	
	//------------------------------------
	// Parcours de l'ensemble
	// renvoie 0 si tous l'ensemble a ete
	// parcouru, sinon 1 avec l'indice du
	// set courant dans pi, et son adresse
	// dans pbs
	//------------------------------------
	Bool get(int* pi, BitString** pbs);
	
	//------------------------------------
	// Interrogation d'un element :
	//------------------------------------
	Bool is_true(BitString* p, int i);
	Bool is_false(BitString* p, int i){ return ! is_true(p, i); }; 

	//------------------------------------
	// Nombre d'elements courant :
	//------------------------------------
	int cardinal(){return nb_elts; };
};


class MonomialTable : private SetTable {
	int nb_arguments;
public :

	//------------------------------------
	// Creation :
	//------------------------------------
	MonomialTable(int nb_args, int mx_elts)
	: SetTable(2*nb_args, mx_elts){
		nb_arguments = nb_args;
	};

	//------------------------------------
	// Manipulation du tampon :
	// (appele reg(istre) ici pour pas confondre !
	//------------------------------------
	void reg_reset(){ SetTable::tamp_reset(); };
	void reg_set_high(int i) {
		SetTable::tamp_set_true((i << 1) - 1); 
	};
	void reg_set_low(int i) { 
		SetTable::tamp_set_true(i << 1);
	};
	void reg_set_phi(int i) {	
			SetTable::tamp_set_false((i << 1) - 1);
			SetTable::tamp_set_false(i << 1);
	};
	Bool known_reg();
	BitString* add_reg(){ return SetTable::operator[](SetTable::tamp_put()); };
	
};

#endif
/*-------------------------------------------------------------------------
   module   : args.h
   date     : 25/11/996
   auteurs  : Pascal Raymond
----------------------------------------------------------------------------
   nature :  Classe ArgsMng, pour faciliter la gestion des arguments
		de commande (argc, argv). 
	ATTENTION ! C'est juste un embryon, duquel on doit deriver une
	classe correcte.
----------------------------------------------------------------------------
   (C = constructeur, M = methode, F = fonction)
-----------------------------------------------------
  modifs :
Nov 25 1998 :
- pour simplifier le traitement des versions : on peut passer a la creation
un no de version (en fait une chaine de caractere)
- on peut acceder a cette chaine par la methode ``char* version()'' qui
rend "?.?" si la version n'est pas definie.
- l'option "-version" EST PREDEFINIE : elle est interceptee par le
manager, qui imprime alors le no de version (tout seul) PUIS FAIT UN
``exit(0)''
--------------------------------------------------------------------------*/

#ifndef __PR_ARGS_H
#define __PR_ARGS_H

/* Objets definis dans ce module */
struct ArgToken;
class ArgsMng;
typedef void (*ArgAction)(ArgsMng* l, int param);

enum ArgTokenMode {
	ARG_ATOME,
	ARG_SECTION
};

/*------------------------------------------------------------
	Elements du tableau d'options :
--------------------------------------------------------------
	key : la chaine a reconnaitre
	treat : un pointeur sur la fonction a appeler	
	param : une constante entiere a fournir lors de l'appel de "treat" 
	comment : un commentaire sur l'option
------------------------------------------------------------*/
struct ArgToken {
	ArgTokenMode mode;
	int used;
   const char* key;
   ArgAction treat;
   int param;
   const char* comment;
};

/*------------------------------------------------------------
	Classe ArgsMng :
Traitement d'une liste d'argument de programme c
--------------------------------------------------------------
	Initialise avec le couple "argc, argv" du main
	+ un tableau de ArgToken devant IMPERATIVEMENT SE TERMINER
par un token dont la cle est NULL, et qui correspond par exemple
au traitement d'une option inconnue, ou de l'argument principal.

	Lors de la creation, le tableau argv est parcourru (a partir
de l'indice 1 !) pour retrouver une entree par "key" dans la table 
des ArgToken, des qu'un token correct est rencontre, la procedure
correspondante est appelee. 
N.B : si le tableau est correct (termine par key = NULL), il y
toujours au moins un token correct pour un element de argv ! 

	Usage imprime sur stderr la liste des options dyu tableau
avec le commentaire associe.
------------------------------------------------------------*/
class ArgsMng {
private:
   int argc;
   const char** argv;
   int curarg;
   ArgToken* tokens;
	const char* vers;
	const char* too;
protected:
	virtual ~ArgsMng(){}
	ArgsMng(){vers = (char*)NULL; too = (const char*)NULL; };
	ArgsMng(const char* v ){vers = v; too = (const char*)NULL; };
	ArgsMng(const char* to, const char* v ){too = to; vers = v; };
	void parse(int ac, const char* av[], ArgToken tks[]);
public:
	const char* tool(){ return (too)? too : argv[0]; }
	const char* version(){ return (vers)? vers : (char*)"?.?"; }
	virtual void usage(int print_all = 0);
	const char* current();
	const char* next();
   ArgsMng(int ac, const char* av[], ArgToken tks[]){
		parse(ac, av, tks);
	};
};

#endif
/*-------------------------------------------------------------------------
   module   : ezargs.h
   date     : 30/08/2005
   auteurs  : Pascal Raymond

   modif    : 
----------------------------------------------------------------------------
   nature :  Classe EzArgs, pour faciliter la gestion des arguments
      de commande (argc, argv). 

   - gère un numéro de version (fourni par l'utilisateur)
   - gère un nom d'outil (déduit du argv[0] standard)
	- gère les options avec clés classiques du style :
         . <key>
         . <key> <int>
         . <key> <string>
     (n.b. les clés peuvent ne pas commencer par -)
   - gère aussi les arguments extras, non introduit par une clé
     dans ce cas, c'est l'ordre d'apparition qui est significatif
   - imprime des messages d'usage standard
   - gère des options par défaut :
     -help, -version 
----------------------------------------------------------------------------
   (C = constructeur, M = methode, F = fonction)
-----------------------------------------------------
On peut utiliser directement la classe EzArgs ou, plus
proprement, dériver sa propre classe. Voir plus bas
"MyArgs" pour un exemple simple de dérivation.

Sion, l'utilisation directe se fait en 3 temps :

1- création

   C) EzArgs::EzArgs(char* vers)

2- déclaration des options

   M) add_bool(char* key, char* man, bool* r)
   M) add_int(char* key, char* par, char* man, int* r, int dflt)
   M) add_int(char* key, char* par, char* man, int* r, bool* rset)
   M) add_string(char* key, char* par, char* man, char** r, char* dflt)
   M) add_extra(char* par, char* man, char** r, char* dflt)

   key   : la clé (sauf pour extra)
   param : un texte explicatif pour l'argument
           (sauf pour les bool) 
   man   : un texte explicatif  
   r     : pointeur sur le résultat
           (suivant le type attendu)
   dflt  : valeur par défaut pour *r
   rset  : pointeur sur un booléen qui indique si
             l'option à été parsée (int uniquement)

3- parsing

M) parse(int argc, char* argv[])

   argc, argv: paramètres de la ligne de commande,
               Y COMPRIS le nom de la commande (argv[0])

   Les arguments argv[1..argc-1] sont parsés selon les
   déclaration précédentes.
   Si une option apparaît plusieurs fois, c'est la dernière
   qui "gagne".
   Les extras sont traités dans l'ordre où ils ont été déclarés :
   la première chaîne sans clés est associée au premier extra déclaré,
   le deuxième au deuxième etc.
   S'il y a plus de chaînes sans clé que d'extra déclaré, on lève
   une erreur. 
----------------------------------------------------------------------------
Exemple de classe dérivée :

class MesArgs:public EzArgs {
	bool _t;
	int _opt;
	char* _outfile;
	char* _infile;
	char* _mainproc;
public:
	MesArgs(int argc, char* argv[]):EzArgs("0.0"){
		add_bool("-t", "test only", &_t);
		add_int("-opt", "<int>", "optimisation level", &_opt, -1);
		add_string("-o", "<fname>", "set output name", &_outfile, NULL);
		add_extra("<file>", "input file", &_infile, NULL);
		add_extra("<main>", "main procedure", &_mainproc, NULL);
		parse(argc, argv);
	}
};

int main(int argc, char* argv[]){
	MesArgs* args = new MesArgs(argc, argv);
}


--------------------------------------------------------------------------*/

#ifndef __PR_EZARGS_H
#define __PR_EZARGS_H

//restons abstrait !
class EzArgsToken ;

class EzArgs {
	int _argc;
	char** _argv;
	int _cur_arg;
	char* _toolname;
	char* _version;
	//option predefs :
	bool _givehelp;
	bool _giveversion;
protected:
	//les tokens avec clé...
	EzArgsToken* _tokens;
	//les xtras (sans clé);
	int _nb_extras;
	EzArgsToken* _extras;
public:
	EzArgs(char* ver);

	bool add_bool(const char* key, const char* man, bool* r);
	bool add_int(const char* key, char* par, const char* man, int* r, int dflt);
	bool add_int(const char* key, char* par, const char* man, int* r, bool* rset);
	bool add_string(const char* key, char* par, const char* man, char** r, char* dflt);
	bool add_extra(char* par, const char* man, char** r, char* dflt);

	bool parse(int ac, char* av[]);

	//usage par défaut ...
	void usage();

	//Les options prédéfinies
	char* version();
	char* toolname();
	void giveoptions();
	void givehelp(){ usage(); giveoptions(); }
};

#endif


extern void time_start(Symbol s);
extern void time_restart(Symbol s);
extern void time_stop(Symbol s);
extern void time_print();

extern void time_C(char*);
extern void time_R(char*);
extern void time_P();
