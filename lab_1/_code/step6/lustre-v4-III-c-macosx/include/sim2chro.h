#ifdef WITHGFX
// fonction d'initialisation 
// cette fonction doit etre la fonction appelee par
// la procedure ClassInitialize des widgets

_XFUNCPROTOBEGIN

extern void YrwInitializeWidgetSet();

_XFUNCPROTOEND
#endif // WITHGFX
#ifdef WITHGFX
// dummy
#endif // WITHGFX
#ifdef WITHGFX
#ifndef __YRW_BOUTON_H_
#define __YRW_BOUTON_H_

// ressources du widget bouton :
// celles du widget Core (je ne met que celles que j'initialise)
// et puis d'autres :
/*

 Name                           Class                           RepType                 Default Value
 ----                           -----                           -------                 -------------
// celles du Core :
 height                         Height                          Dimension               10
 width                          Width                           Dimension               30
 x                                      Position                        Position                0
 y                                      Position                        Position                0

// d'autres ( a moi )
 actions                        Callback                        XtCallbackList  NULL
 texte                          Texte                           String                  NULL
 image                          Image                           Pixmap                  NULL
 hauteur_image          Hauteur                         Dimension               0
 largeur_image          Largeur                         Dimension               0
 taillefixe                     TailleFixe                      Boolean                 False
 persistant                     Persistant                      Boolean                 False
 enfonce                        Enfonce                         Boolean                 False

*/

// accces aux champs de classe non standard 
#ifndef YrwNactions
#define YrwNactions "actions"
#define YrwCActions XtCCallback
#define YrwRActions XtRCallback
#endif

#ifndef YrwNtexte
#define YrwNtexte       "texte"
#define YrwCTexte       "Texte"
#define YrwRTexte       XtRString
#endif

#ifndef YrwNimage
#define YrwNimage       "image"
#define YrwCImage       "Image"
#define YrwRImage       XtRPixmap
#endif

#ifndef YrwNhimage
#define YrwNhimage      "himage"
#define YrwCHimage      "Hauteur"
#define YrwRHimage      XtRDimension
#endif

#ifndef YrwNlimage
#define YrwNlimage      "limage"
#define YrwCLimage      "Largeur"
#define YrwRLimage      XtRDimension
#endif

#ifndef YrwNtaillefixe
#define YrwNtaillefixe  "taillefixe"
#define YrwCTailleFixe  "TailleFixe"
#define YrwRTailleFixe  XtRBoolean
#endif

#ifndef YrwNpersistant
#define YrwNpersistant  "persistant"
#define YrwCPersistant  "Persistant"
#define YrwRPersistant  XtRBoolean
#endif

#ifndef YrwNenfonce
#define YrwNenfonce             "enfonce"
#define YrwCEnfonce             "Enfonce"
#define YrwREnfonce             XtRBoolean
#endif

extern WidgetClass              boutonWidgetClass;

typedef struct _BoutonClassRec  *BoutonWidgetClass;
typedef struct _BoutonRec               *BoutonWidget;

#endif
#endif // WITHGFX
#ifdef WITHGFX
#ifndef __YRW_BOUTON_P_H__
#define __YRW_BOUTON_P_H__

#include "bouton.h"

// une fausse declaration pour que le compilo soit heureux
typedef struct _BoutonClass {
        int dummy;                      // inutilisé
} BoutonClassPart;

// declaration du 'class record'
typedef struct _BoutonClassRec {
        CoreClassPart           core_class;             // le truc de base
        BoutonClassPart         bouton_class;   // le mien
} BoutonClassRec;

extern BoutonClassRec boutonClassRec;

// nouveaux champs pour le widget 'Bouton'
typedef struct {
        // les ressources
        XtCallbackList                  actions;
        char *                                  texte;
        Pixmap                                  image;
        Dimension                               largeur_image;
        Dimension                               hauteur_image;
        Boolean                                 taillefixe;
        Boolean                                 persistant;
        Boolean                                 enfonce;

        // les champs privés
        GC                                              leGC;
        GC                                              leGCinverse;
        Boolean                                 highlighted;
        int                                             texte_x;
        int                                             texte_y;
        Font                                    police;
        XFontStruct                             *struct_police;
        GC                                              GCImage;
        GC                                              GCInverseImage;
} BoutonPart;

// declaration finale du widget
typedef struct _BoutonRec {
        CorePart                core;
        BoutonPart              bouton;
} BoutonRec;

#endif
#endif // WITHGFX
#ifdef WITHGFX
#ifndef __YRW_FORMULAIRE_H_
#define __YRW_FORMULAIRE_H_

#include <X11/Constraint.h>

// ressources du widget formulaire :
// celles du widget Core (je ne met que celles que j'initialise)
// celles du widget Constraint
/*
 Name                           Class                           RepType                 Default Value
 ----                           -----                           -------                 -------------
 height                         Height                          Dimension               Calculé lors du realize
 width                          Width                           Dimension               Calculé lors du realize
 x                                      Position                        Position                0
 y                                      Position                        Position                0

 Name                           Class                           RepType                 Default Value
 ----                           -----                           -------                 -------------

 vertical                       Vertical                        Boolean                 True
 horizontal                     Horizontal                      Boolean                 True
 positionx                      Position                        Position                0
 positiony                      Position                        Position                0

*/

typedef struct _FormulaireClassRec      *FormulaireWidgetClass;
typedef struct _FormulaireRec           *FormulaireWidget;

extern WidgetClass formulaireWidgetClass;

#ifndef YrwNvertical
#define YrwNvertical    "vertical"
#define YrwCVertical    "Vertical"
#define YrwRVertical    XtRBoolean
#endif 

#ifndef YrwNhorizontal
#define YrwNhorizontal  "horizontal"
#define YrwCHorizontal  "Horizontal"
#define YrwRHorizontal  XtRBoolean
#endif

#ifndef YrwNpositionx
#define YrwNpositionx   "positionx"
#define YrwCPositionx   "Positionx"
#define YrwRPositionx   XtRPosition
#endif

#ifndef YrwNpositiony
#define YrwNpositiony   "positiony"
#define YrwCPositiony   "Positiony"
#define YrwRPositiony   XtRPosition
#endif

#endif
#endif // WITHGFX
#ifdef WITHGFX
#ifndef __YRW_FORMULAIRE_P_h
#define __YRW_FORMULAIRE_P_h

#include "formulaire.h"

// un bidon pour que le compilo ne rale pas
typedef struct {
        Boolean (*recalcul)(FormulaireWidget fw);
} FormulaireClassPart;

// déclaration du 'class record'
typedef struct _FormulaireClassRec {
    CoreClassPart               core_class;                     // le truc de base
    CompositeClassPart  composite_class;        // le truc pour composite
    ConstraintClassPart constraint_class;       // le truc pour les contraintes
    FormulaireClassPart formulaire_class;       // le mien
} FormulaireClassRec;

extern FormulaireClassRec formulaireClassRec;

// nouveaux champs pour le widget 'Formulaire'
typedef struct {
        // les ressources
        Boolean         vertical; // autorise le scroll vertical
        Boolean         horizontal; // autorise le scroll horizontal
        Position        position_x,position_y; // la position de la fenetre de vue
    // les champs privés
        enum {normal,deplacement} mode;
        int posx,posy;
        int hauteur_totale,largeur_totale;
        Boolean recalcul_a_faire;
} FormulairePart;

// declaration finale du widget
typedef struct _FormulaireRec {
    CorePart            core;
    CompositePart       composite;
    ConstraintPart      constraint;
    FormulairePart      formulaire;
} FormulaireRec;

// définition de la partie 'constraint' du formulaire
typedef struct {
        int x_base,y_base;              // les coordonnees voulues du formulaire
        Boolean managed;
} FormulaireConstraintsPart;

typedef struct {
    FormulaireConstraintsPart   formulaire;
} FormulaireConstraintsRec, *FormulaireConstraints;

#endif
#endif // WITHGFX
#ifdef WITHGFX
#ifndef __YRW_VUE_H_
#define __YRW_VUE_H_

// ressources du widget vue :
// celles du widget Core (je ne met que celles que j'initialise)
// et puis d'autres :
/*

 Name                           Class                           RepType                 Default Value
 ----                           -----                           -------                 -------------
// celles du Core :
 height                         Height                          Dimension               10
 width                          Width                           Dimension               30
 x                                      Position                        Position                0
 y                                      Position                        Position                0

// d'autres ( a moi )
 exposition                     Callback                        XtCallbackList  NULL

*/

#ifndef YrwNactions
#define YrwNactions "actions"
#define YrwCActions XtCCallback
#define YrwRActions XtRCallback
#endif

extern WidgetClass              vueWidgetClass;

typedef struct _VueClassRec     *VueWidgetClass;
typedef struct _VueRec          *VueWidget;

#endif
#endif // WITHGFX
#ifdef WITHGFX
#ifndef __YRW_VUE_P_H__
#define __YRW_VUE_P_H__

#include "vue.h"

// une fausse declaration pour que le compilo soit heureux
typedef struct _VueClass {
        int dummy;                      // inutilisé
} VueClassPart;

// declaration du 'class record'
typedef struct _VueClassRec {
        CoreClassPart           core_class;             // le truc de base
        VueClassPart            vue_class;      // le mien
} VueClassRec;

extern VueClassRec vueClassRec;

// nouveaux champs pour le widget 'Vue'
typedef struct {
        // les ressources
        XtCallbackList          exposition;

        // les champs privés : rien ;-)
} VuePart;

// declaration finale du widget
typedef struct _VueRec {
        CorePart                core;
        VuePart                 vue;
} VueRec;

#endif
#endif // WITHGFX
#ifdef WITHGFX
#ifndef __YRW_ASCENSEUR_H_
#define __YRW_ASCENSEUR_H_

// ressources du widget ascenseur :
// celles du widget Core (je ne met que celles que j'initialise)
// et puis d'autres :
/*

 Name                           Class                           RepType                 Default Value
 ----                           -----                           -------                 -------------
// celles du Core :
 height                         Height                          Dimension               10
 width                          Width                           Dimension               30
 x                                      Position                        Position                0
 y                                      Position                        Position                0

// d'autres ( a moi )
 deplacement            Callback                        XtCallbackList  NULL
 clic                           Callback                        XtCallbackList  NULL
 sommet                         Sommet                          Float                   1.0
 visible                        Visible                         Float                   1.0
 horizontal                     Horizontal                      Boolean                 True //horizontal
 dontnotify                     DontNotify                      Boolean                 Fase // ne pas appeler
                                                                                                                        // le call back dans
                                                                                                                        // le SetValues

*/

// accces aux champs de classe non standard 
#ifndef YrwNdeplacement
#define YrwNdeplacement "deplacement"
#define YrwCDeplacement XtCCallback
#define YrwRDeplacement XtRCallback
#endif

#ifndef YrwNclic
#define YrwNclic                "clic"
#define YrwCClic                XtCCallback
#define YrwRClic                XtRCallback
#endif

#ifndef YrwNsommet
#define YrwNsommet              "sommet"
#define YrwCSommet              "Sommet"
#define YrwRSommet              XtRFloat
#endif

#ifndef YrwNvisible
#define YrwNvisible             "visible"
#define YrwCVisible             "Visible"
#define YrwRVisible             XtRFloat
#endif

#ifndef YrwNhorizontal
#define YrwNhorizontal          "horizontal"
#define YrwCHorizontal          "Horizontal"
#define YrwRHorizontal          XtRBool
#endif

#ifndef YrwNdontNotify
#define YrwNdontNotify          "dontNotify"
#define YrwCDontNotify          "DontNotify"
#define YrwRDontNotify          XtRBool
#endif

extern WidgetClass              ascenseurWidgetClass;

typedef struct _AscenseurClassRec       *AscenseurWidgetClass;
typedef struct _AscenseurRec            *AscenseurWidget;

#endif
#endif // WITHGFX
#ifdef WITHGFX
#ifndef __YRW_ASCENSEUR_P_H__
#define __YRW_ASCENSEUR_P_H__

#include "ascenseur.h"

// une fausse declaration pour que le compilo soit heureux
typedef struct {
        int dummy;                      // inutilisé
} AscenseurClassPart;

// declaration du 'class record'
typedef struct _AscenseurClassRec {
        CoreClassPart           core_class;             // le truc de base
        AscenseurClassPart      ascenseur_class;        // le mien
} AscenseurClassRec;

extern AscenseurClassRec ascenseurClassRec;

// nouveaux champs pour le widget 'Ascenseur'
typedef struct {
        // les ressources
        XtCallbackList                  deplacement;
        XtCallbackList                  clic;
        float                                   sommet;
        float                                   visible;
        Bool                                    horiz;
        Bool                                    dontNotify;

        // les champs privés
        GC                                              leGCforeground;
        GC                                              leGCbackground;
        int                                             hauteur_visible; // visible*core->height
        int                                             largeur_visible; // visible*core->width
        int                                             position_clic;
        int                                             mode;
} AscenseurPart;

// declaration finale du widget
typedef struct _AscenseurRec {
        CorePart                core;
        AscenseurPart   ascenseur;
} AscenseurRec;

#endif
#endif // WITHGFX
#ifdef WITHGFX
#ifndef __YRW_SAISIE_H_
#define __YRW_SAISIE_H_

// ressources du widget saisie :
// celles du widget Core (je ne met que celles que j'initialise)
// et puis d'autres :
/*

 Name                           Class                           RepType                 Default Value
 ----                           -----                           -------                 -------------
// celles du Core :
 height                         Height                          Dimension               10
 width                          Width                           Dimension               30
 x                                      Position                        Position                0
 y                                      Position                        Position                0

// d'autres ( a moi )
 new_line                       Callback                        XtCallbackList  NULL
 actions                        Callback                        XtCallbackList  NULL
 texte                          Texte                           String                  NULL
 keyboardFocus          KeyboardFocus           Boolean                 False

*/

// accces aux champs de classe non standard 
#ifndef YrwNnew_line
#define YrwNnew_line "new_line"
#define YrwCNew_line XtCCallback
#define YrwRNew_line XtRCallback
#endif

#ifndef YrwNactions
#define YrwNactions "actions"
#define YrwCActions XtCCallback
#define YrwRActions XtRCallback
#endif

#ifndef YrwNtexte
#define YrwNtexte       "texte"
#define YrwCTexte       "Texte"
#define YrwRTexte       XtRString
#endif

#ifndef YrwNkeyboardFocus
#define YrwNkeyboardFocus       "keyboardFocus"
#define YrwCKeyboardFocus       "KeyboardFocus"
#define YrwRKeyboardFocus       XtRBoolean
#endif

extern WidgetClass              saisieWidgetClass;

typedef struct _SaisieClassRec  *SaisieWidgetClass;
typedef struct _SaisieRec               *SaisieWidget;

#endif
#endif // WITHGFX
#ifdef WITHGFX
#ifndef __YRW_SAISIE_P_H__
#define __YRW_SAISIE_P_H__

#include "saisie.h"

// une fausse declaration pour que le compilo soit heureux
typedef struct _SaisieClass {
        int dummy;                      // inutilisé
} SaisieClassPart;

// declaration du 'class record'
typedef struct _SaisieClassRec {
        CoreClassPart           core_class;             // le truc de base
        SaisieClassPart         saisie_class;   // le mien
} SaisieClassRec;

extern SaisieClassRec saisieClassRec;

// nouveaux champs pour le widget 'Saisie'
typedef struct {
        // les ressources
        XtCallbackList                  actions;
        XtCallbackList                  new_line;
        char *                                  texte;
        Boolean                                 keyboardFocus;

        // les champs privés
        GC                                              leGC;
        GC                                              leGCinverse;
        int                                             texte_x;
        int                                             texte_y;
        Font                                    police;
        XFontStruct                             *struct_police;
        int                                             pos_curseur;
} SaisiePart;

// declaration finale du widget
typedef struct _SaisieRec {
        CorePart                core;
        SaisiePart              saisie;
} SaisieRec;

#endif
#endif // WITHGFX
#ifdef WITHGFX
#ifndef __YRW_TEXTE_H_
#define __YRW_TEXTE_H_

// ressources du widget texte :
// celles du widget Core (je ne met que celles que j'initialise)
// et puis d'autres :
/*

 Name                           Class                           RepType                 Default Value
 ----                           -----                           -------                 -------------
// celles du Core :
 height                         Height                          Dimension               10
 width                          Width                           Dimension               30
 x                                      Position                        Position                0
 y                                      Position                        Position                0

// d'autres ( a moi )
 texte                          Texte                           String                  NULL
 image                          Image                           Pixmap                  NULL
 hauteur_image          Hauteur                         Dimension               0
 largeur_image          Largeur                         Dimension               0

*/

// accces aux champs de classe non standard 
#ifndef YrwNtexte
#define YrwNtexte       "texte"
#define YrwCTexte       "Texte"
#define YrwRTexte       XtRString
#endif

#ifndef YrwNimage
#define YrwNimage       "image"
#define YrwCImage       "Image"
#define YrwRImage       XtRPixmap
#endif

#ifndef YrwNhimage
#define YrwNhimage      "himage"
#define YrwCHimage      "Hauteur"
#define YrwRHimage      XtRDimension
#endif

#ifndef YrwNlimage
#define YrwNlimage      "limage"
#define YrwCLimage      "Largeur"
#define YrwRLimage      XtRDimension
#endif

extern WidgetClass              texteWidgetClass;

typedef struct _TexteClassRec   *TexteWidgetClass;
typedef struct _TexteRec                *TexteWidget;

#endif
#endif // WITHGFX
#ifdef WITHGFX
#ifndef __YRW_TEXTE_P_H__
#define __YRW_TEXTE_P_H__

#include "texte.h"

// une fausse declaration pour que le compilo soit heureux
typedef struct _TexteClass {
        int dummy;                      // inutilisé
} TexteClassPart;

// declaration du 'class record'
typedef struct _TexteClassRec {
        CoreClassPart           core_class;             // le truc de base
        TexteClassPart          texte_class;    // le mien
} TexteClassRec;

extern TexteClassRec texteClassRec;

// nouveaux champs pour le widget 'Texte'
typedef struct {
        // les ressources
        char *                                  texte;
        Pixmap                                  image;
        Dimension                               largeur_image;
        Dimension                               hauteur_image;

        // les champs privés
        GC                                              leGC;
        int                                             texte_x;
        int                                             texte_y;
        Font                                    police;
        XFontStruct                             *struct_police;
        GC                                              GCImage;
} TextePart;

// declaration finale du widget
typedef struct _TexteRec {
        CorePart                core;
        TextePart               texte;
} TexteRec;

#endif
#endif // WITHGFX
#ifdef WITHGFX
#ifndef __YRW_PLAT_H_
#define __YRW_PLAT_H_

#include <X11/Constraint.h>

// ressources du widget plat :
// celles du widget Core (je ne met que celles que j'initialise)
// celles du widget Constraint
/*
 Name                           Class                           RepType                 Default Value
 ----                           -----                           -------                 -------------
 height                         Height                          Dimension               200
 width                          Width                           Dimension               200
 x                                      Position                        Position                0
 y                                      Position                        Position                0

 Name                           Class                           RepType                 Default Value
 ----                           -----                           -------                 -------------

 espaceSouhaite         EspaceSouhaite          Dimension               0

*/

typedef struct _PlatClassRec    *PlatWidgetClass;
typedef struct _PlatRec         *PlatWidget;

extern WidgetClass platWidgetClass;

#ifndef YrwNespaceSouhaite
#define YrwNespaceSouhaite      "espaceSouhaite"
#define YrwCEspaceSouhaite      "EspaceSouhaite"
#define YrwREspaceSouhaite      XtRDimension
#endif

#endif
#endif // WITHGFX
#ifdef WITHGFX
#ifndef __YRW_PLAT_P_h
#define __YRW_PLAT_P_h

#include "plat.h"

// un bidon pour que le compilo ne rale pas
typedef struct {
        Boolean (*recalcul)(PlatWidget fw);
} PlatClassPart;

// déclaration du 'class record'
typedef struct _PlatClassRec {
    CoreClassPart               core_class;                     // le truc de base
    CompositeClassPart  composite_class;        // le truc pour composite
    ConstraintClassPart constraint_class;       // le truc pour les contraintes
    PlatClassPart       plat_class;     // le mien
} PlatClassRec;

extern PlatClassRec platClassRec;

// nouveaux champs pour le widget 'Plat'
typedef struct {
        // les ressources
        Dimension               espaceSouhaite;

    // les champs privés
        int hauteur_totale,largeur_totale;
        Boolean recalcul_a_faire;
} PlatPart;

// declaration finale du widget
typedef struct _PlatRec {
    CorePart            core;
    CompositePart       composite;
    ConstraintPart      constraint;
    PlatPart            plat;
} PlatRec;

// définition de la partie 'constraint' du plat
typedef struct {
        int x_base,y_base;              // les coordonnees voulues du plat
        Boolean managed;
} PlatConstraintsPart;

typedef struct {
    PlatConstraintsPart plat;
} PlatConstraintsRec, *PlatConstraints;

#endif
#endif // WITHGFX
#ifndef __SIM2CHRO_H__
#define __SIM2CHRO_H__

   #include <X11/IntrinsicP.h>
   #include <X11/StringDefs.h>
   #include <X11/Shell.h>
   #include <X11/Xatom.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <values.h>
   #include <limits.h>
   #include <math.h>
   #include <time.h>
   #include "bouton.h"
   #include "ascenseur.h"
   #include "vue.h"
   #include "formulaire.h"
   #include "saisie.h"
   #include "texte.h"
   #include "plat.h"

   #define SOLID 0
   #define DASH 1

   #define LAR_SB_PLAT 16 // sale !
      enum type_var {booleen,entier,reel};
      enum type_sortie { LaTeX, PostScript, Fig, TclTk };
      enum extint {externe,interne};
      typedef struct hash {
         unsigned long val;            // la valeur pour affichage
         char *nom;                  // le nom de la couleur
         extint type;               // le type interne==couleur predéfinie
         char *nombis;               // si type externe = nom X 
                                 // au format rgb:..../..../....
         struct hash *suiv;            // chainage
      } hash;
         // valeurs pour  le champs flag
         #define COULEUR         1
         #define COULEURNUM      2
         #define COULEURFOND      4
         #define VERTICALEAUSSI   8   // pour dire que la verticale qui relie au
                              // précédent est aussi de la couleur 'couleur'
         typedef struct liste_de_valeurs {
            double   value;         // la valeur en question
            int      numero_colonne;   // le numero de la colonne
            int      pointilles;      // le trait est-il en pointilles ?
            int      vpointilles;   // la verticale est-elle en pointilles ?
            int      flag;         // quels champs sont utilisés
            hash   *couleur;      // couleur du chronogramme
            hash   *colnum;      // couleur des valeurs
            hash   *colfond;      // couleur du fond de variables
            double   val;         // valeur après mise a l'echelle
            struct   liste_de_valeurs   *suiv;   // chainage
         } liste_de_valeurs;
         // valeurs pour  le champs flag
         #define CHAMPS_COLNOM   1
         #define CHAMPS_COLNUM   2
         #define CHAMPS_COULEUR  4
         typedef struct liste_de_variables {
            char      *nom;      // le nom de la variable
            type_var   type;      // le type de la variable
            int         flag;      // quels champs sont utilisés
            hash      *colnom;   // la couleur du nom de la variable
            hash      *colnum;   // la couleur des valeurs pour la variable
            hash      *couleur;   // la couleur du chronogramme de la variable
            double      vmin;      // valeur minimale de la variable
            double      vmax;      // valeur maximale de la variable
            liste_de_valeurs   *valeurs;   // la liste des valeurs de la variable
            liste_de_valeurs   *fin_val;   // dernier élément de la liste des valeurs
            struct liste_de_variables   *suiv;   // chainage
            int         scale;      // données utiles lors de la génération
            double      valmin,valmax;
            double      hauteur,base;
            double      coeff;
            int         visible;   // cette variable est elle visible ?
            Widget      widg;      // le Widget pour le bouton de visibilite.
         } liste_de_variables;
         #define NUMERO_COLONNE   1
         #define FOND_COLONNE   2
         typedef struct liste_de_numcol {
            int         numero;            // le numéro de colonne
            int         flag;            // quels champs sont rensignés
            int         num;            // le numéro pour l'affichage
            hash      *colfond;         // la couleur du fond
            struct liste_de_numcol   *suiv;   // chainage
         } liste_de_numcol;
      typedef struct couleur_rgb {
         char      *nom;   // le nom de la couleur
         double      red;   // la composante rouge
         double      green;   // la composante verte
         double      blue;   // la composante bleue
         int         rang;   // le rang dans la palette effectivement utilisée
      } couleur_rgb;
      typedef struct liste_color {
         couleur_rgb         couleur;   // la couleur
         struct liste_color   *suiv;      // chainage
      } liste_color;
   class sim2chro {
   public:
         sim2chro();
         sim2chro(sim2chro&);
         ~sim2chro();
      liste_de_variables *ajouter_une_variable(char *,type_var,char *,char*,char*);
      void supprimer_une_variable(liste_de_variables *);
      void ajouter_une_valeur(liste_de_variables *,double,int,int,int,char *,char *,char*,int);
      void ajouter_valeur_fin(liste_de_variables *,double,int,int,int,int,char *,char *,char*,int);
      void ajouter_numero_colonne(int,int);
      void ajouter_fond_colonne(int numero,char *colfond);
      void changer_les_couleurs_variable(liste_de_variables *,char *,char *,char *);
      void mettre_titre_fenetre(const char *);
      void generer(type_sortie);
      void changer_couleur_colonne(liste_de_variables *,int,char *,char *,char *,int);
      void supprimer_une_valeur(liste_de_variables *,int);

      void variable_visible(liste_de_variables *);
      void variable_invisible(liste_de_variables *);
      void rendre_invisible_var_widget(Widget);

      liste_de_variables *suppression_variable(liste_de_variables *,liste_de_variables *,int *);
      int ajouter_couleur(liste_color *);
      int ajout_var(liste_de_variables *);
      liste_de_valeurs *ajouter_valeur(liste_de_valeurs *,liste_de_valeurs *);
      void liberation_valeurs(liste_de_variables *);
      void mettre_a_jour_ecran();
      liste_de_numcol *maj_numcol(liste_de_numcol *,int);
      liste_de_numcol *ajouter_numcol(liste_de_numcol *,int,int,int *);
      liste_de_numcol *ajouter_colfond(liste_de_numcol *,int,hash *,int *);
      void remettre_numcol_dans_etat_correct();
      void init_hash();
      int hash_fct1(char *);
      int hash_fct2(unsigned long);
      char *NomCouleur(hash *,type_sortie);
      hash *Allocation_de_couleur(char *);
      void remettre_les_couleurs_voulues(Colormap *);
      //void click_out(Widget,XtPointer,XtPointer);
      void scrolling();
      void page_scrolling(XtPointer);
      void redimentionnement();
      void initialiser();
      void coco();
      void affichage_pos(int);
      void adjust_scroll();
      void truandage_Xt();
      void affichage_ecran();
      void bye();
      void changer_colglobale(liste_de_variables *,int *);
      int Fig_donne_la_couleur(char *);
      char *Fig_donne_la_taille(char *);
      double donne_decalage_top(char *);
      double mabs(double);
      int mettre_a_l_echelle(liste_de_variables *);
      void les_horizontales(liste_de_variables *,FILE *,double,int,hash*,type_sortie);
      void procedure_annexe(liste_de_variables *,FILE *,int,int,type_sortie);
      void generer_chrono(liste_de_variables *,FILE *,int,int,int,type_sortie);
      void affichage_chrono(liste_de_variables *,FILE *,type_sortie);
      int imprimer(liste_de_variables *,type_sortie);
      void initlogo();
      void synchro();
      void effacer();
      void arreter();
      void boucleprincipale();
      void attendrefin();

      void save_options(FILE *);
      void load_options(FILE *);

      void redraw(Region);

      void scroller_plat();
      void page_scroller_plat(XtPointer);

      // pour l'ecran, transferees depuis xfen2

      Window creer_fenetre(int largeur,                  /* largeur */
                           int hauteur,                  /* hauteur */
                           char *nom,                    /* nom     */
                           XSetWindowAttributes *attrib, /* attributs */
                           int cwattributes,             /* mask des attributs */
                           int *colors,                  /* nombre de couleurs */
                           XSizeHints *size_def,         /* taille(s) de la fenetre */
                           int inputmask,                /* mask des evenements */
                 int backstore,                /* faire du backing store? */
                Window father);                 /* fenetre pere */
      Window fenetre_simple_2(char *nom,int largeur,int hauteur,int *couleurs,
                  int backstore,Window father);
      unsigned long alloccouleur(char *nom,Colormap *Xcmap,int noquiet);

         static couleur_rgb   couleurs_fig[];
         static int         nb_col_fig;
         double   HAT_1;         /* la hauteur de chaque etage */
         double   HAT_HAUTBAS;   /* l'espace en haut et en bas */
         double   HAT_ESPACE;      /* l'espace entre deux variables */
         double   LAR_dt;         /* largeur du delta t */
         double   LAR_NOM;      /* largeur du nom */
         double   LAR_DEP;      /* largeur du depassement en marge */
         double   CORR_ESCA;      /* correction chiffres sur escalier */
         double   NUMCORR;      /* distance des numeros de colonnes au bord */
         int      CADRE;         /* affichage d'un cadre autour du chronogramme*/
         int      NONUMBER;      /* n'affiche pas les numeros de colonnes */
         int      LIGNEZERO;      /* affiche une ligne a la valeur 0 des entiers*/
         int      LIGNEPARTOUT;   /* affiche les horizontales pour les entiers*/
         int      NOINTNUMBER;   /* n'affiche pas les valeurs pour les entiers*/
         int      NEWPAGE;      /* saute une page entre les graphes*/
         int      DEUXNEWPAGE;   /* un seul saut de page entre les graphes */
         double   INTFACTOR;      /* nombre par lequel diviser les entiers*/
         int      NBCOLS;         /* nombre de colonnes par graphe */
         char*   NUMTAILLE;      /* taille des numeros de colonnes*/
         char*   NOMTAILLE;      /* taille des noms de variables*/
         char*   INTTAILLE;      /* taille des valeurs des entiers*/
         int      COLOR;         /* On utilise des couleurs */
         char*   T_COLORCADRE;   /* couleur du cadre */
         char*   T_COLORTRAI;   /* couleur des trais */
         char*   T_COLORNAME;   /* couleur des noms de variables */
         char*   T_COLORVAL;      /* couleur des valeurs des variables */
         char*   T_COLORCHRONO;   /* couleur des chronogamme */
         int      NOINDENT;      /* ne pas commencer en retrait (!) */
         int      CHEVAUCHER;      /* nombre de colonnes reprises par page */
         double   HAUTEUR_MAX;   /* hauteur maximale du chronogramme */
         int      AUTOSCALE;      /* mise a l'echelle verticale automatique */
         int      SCALELAR;      /* pas de mise a l'echelle horizontale */
         double   LARGEUR_MAX;   /* largeur maximale du chronogramme */
         int      ECRAN;         /* pas de sortie ecran */
         int      HEADER;         /* pas de header LaTeX pret-a-compiler */
         int      PLANDSCAPE;      /* sortie Paysage en PostScript */
         // ca c'est une constante
         double   CONVPOUCE;      /* 1mm=CONVPOUCE 1/72 pouces */
         double   MARGEBAS;      /* marge a laisser en bas (en mm) */
         double   MARGEY;         /* marge a laisser a gauche en landscape (mm) */
         int      NUMCOLECRAN;   /* les numero de colonnes sont affiches a l'ecran */
         int      NOQUIET;      /* on affiche des messages sur stderr */
         int      NOFLOATNUMBER;   /* n'affiche pas les valeurs pour les réels */
         char*   FLOATTAILLE;   /* taille des valeurs pour les reels */
         char*   SCRNAMEFONT;   /* Police ecran defaut pour les noms des vars */
         char*   SCRNUMFONT;      /* Police ecran defaut pour les valeurs */
         int      SPECIALFIG;      /* Texte = pas de flag special en .fig */
         int      FIG32;         /* Generer du FIG 3.2 par defaut */
         FILE*   FLOT_DE_SORTIE;   /* le fichier dans lequel écrire */
         int      AUTOFLUSH;      /* 1 => affichage mis a jour en direct */
         int      SIM2CHRO;      /* 1 => affichage logo sim2chro */
         char   *TITRE_FENETRE;   /* le titre de la fenetre */
         int      NUMBERDECIMAL;   /* nombre de décimales pour les réels affichés */
         int      PRIVATE_COLORMAP;   /* palette privée ? */

         hash   *COLORCADRE;   /* couleur du cadre */
         hash   *COLORTRAI;      /* couleur des traits (pas du chrono) */
         hash   *COLORNAME;      /* couleur des noms */
         hash   *COLORVAL;      /* couleur des valeurs */
         hash   *COLORCHRONO;   /* couleur du chronogramme */

         int      LARGEUR_COL;    /* la largeur des colonnes a l'ecran */
         int      HAUTEUR_BOOL;   /* la hauteur des booleens a l'ecran */
         int      HAUTEUR_INT;   /* la hauteur des entiers a l'ecran */
         int      HAUTEUR_REEL;   /* la hauteur des reels a l'ecran */
         int      HAUTEUR_ESP;   /* la hauteur des espaces entre variables a l'ecran */
         int      HAUTEUR_NUM;   /* la hauteur pour les numeros de colonne a l'ecran */
   private:
            liste_color         *la_liste_des_couleurs;
            liste_de_variables   *la_liste;
            liste_de_numcol      *liste_numcol;
            liste_de_numcol      *fin_numcol;
         // c'est TRES nul 256
         // c'est meme MAL
         // c'est meme change !
         hash   *hash_table1[211];
            Display            *Xdp;
            Visual            *Xvi;
            Screen            *Xsc;
            int               prof_col;
            int               Xdscreen;
            Window            Xroot;
            Window            Xw;
            GC               Xgc;
            XGCValues         Xgcvals;
            Colormap         Xcmap;
            XTextItem         xti[2];
            XFontStruct       *font_num_struct;
            int               font_num_descent;
            XFontStruct       *font_name_struct;
            Pixmap            pmpm;
            Pixmap            pixmap_copyright;
            Pixmap            Xw1;
            Widget            bt_config,bouton,form,toplevel,sb,vc,vp;
         public:
            Widget            variables_toplevel;
            Widget            config_toplevel;
            Widget            name_toplevel;
            Widget            saisie;      // pour pouvoir recupérer le nom !
            Widget            name_toplevel_opt;
            int               save_opt;
            Widget            saisie_opt;   // pour pouvoir recupérer le nom !
            Widget            adv_toplevel;
                    Widget  W0;
                    Widget  W1;
                    Widget  W2;
                    Widget  W3;
                    Widget  W4;
                    Widget  W5;
                    Widget  W6;
                    Widget  W7;
                    Widget  W8;
                    Widget  W9;
                    Widget  W10;
                    Widget  W11;
                    Widget  W12;
                    Widget  W13;
                    Widget  W14;
                    Widget  W15;
                    Widget  W16;
                    Widget  W17;
                    Widget  W18;
                    Widget  W19;
                    Widget  W20;
                    Widget  W21;
                    Widget  W22;
                    Widget  W23;
                    Widget  W24;
                    Widget  W25;
                    Widget  W26;
                    Widget  W27;
                    Widget  W28;
                    Widget  W29;
                    Widget  W30;
                    Widget  W31;
                    Widget  W32;
                    Widget  W33;
                    Widget  W34;
                    Widget  W35;
                    Widget  W36;
                    Widget  W37;
                    Widget  W38;
                    Widget  W39;
                    Widget  W40;
                    Widget  W41;
                    Widget  W42;
                    Widget  W43;
                    Widget  W44;
                    Widget  W45;
                    Widget  W46;
                    Widget  W47;
                    Widget  W48;
                    Widget  W49;
                    Widget  W50;
                    Widget  W51;
                    Widget  W52;
                    Widget  W53;
                    Widget  W54;
                    Widget  W55;
                    Widget  W56;
                    Widget  W57;
                    Widget  W58;
                    Widget  W59;
                    Widget  W60;
                    Widget  W61;
                    Widget  W62;
                    Widget  W63;
                    Widget  W64;
                    Widget  W65;
                    Widget  W66;
                    Widget  W67;
                    Widget  W68;
                    Widget  W69;
                    Widget  W70;
            Widget            variables_plat;
            Widget             variables_form2;
            Widget            variables_sb;
            int               initialise;      // pour savoir si on peut afficher !
            Widget            plat,sb_plat;
         private:
            Widget            bt_ok_variables,bt_variables;
            Widget            config_form, bt_postscript;
            Widget            bt_latex, bt_fig, bt_adv, bt_close;
            Widget            bt_ok,bt_cancel;
            XColor bck,whe;      //pour des widgets noir et blanc aussi en palette privee

            Arg               args[100];
            int               nbarg;
            XSizeHints         size_def;
            int               largeur,hauteur;
            int               NBCOLONNES;      // le nombre de colonnes affichées
            int               LARBOUTON;      // la largeur du bouton
            int               LARBORD;      // la largeur du bord (donnée par le WM)

            int               scrolled;
            float            vieux_thumb;
            int               vieux_nbcol;
            float            vieux_pos;
            int               largeur_scroll_bar;

            Pixmap            logo_verimag;
            Pixmap            logo_chroserv;
            Pixmap            logo_sim2chro;
            Pixmap            logo_bibi;
            unsigned long      *logo_fill;

            unsigned long      noir,blanc;
            unsigned long      col_chrono_defaut;

            Display            *xfen_Xdp;
            Visual            *xfen_Xvi;
            Screen            *xfen_Xsc;
            int               xfen_prof_col;
            int               xfen_Xdscreen;
            Window            xfen_Xroot;

            unsigned int      hecran;
            unsigned int      htitre;

            int      PLACE_NOM;      /* la largeur de l'espace des noms a l'ecran */
            double            FIG_X_ADJUST;
            double            FIG_Y_ADJUST;
            double            TCL_X_ADJUST;   // et Tcl/tk
            double            TCL_Y_ADJUST;
            int               numseq;
            int               nb;
            int               decal;
         public:      // hack pour sim2chro
            int               redim_necessaire;
            type_sortie         outform;
         private:
            static char            logo_verimag_data[];
            static char            logo_chroserv_data[];
            static char            logo_sim2chro_data[];
            static char            logo_bibi_data[];
            static long unsigned int logo24_verimag_data[];
            static long unsigned int logo24_chroserv_data[];
            static long unsigned int logo24_sim2chro_data[];
            static long unsigned int logo24_bibi_data[];
   };

   void initialisation_bibliotheque_sim2chro();
   void fin_bibliotheque_sim2chro();
   void sim2chro_traiter_evenements();
   void sim2chro_traiter_un_evenement();

#endif
