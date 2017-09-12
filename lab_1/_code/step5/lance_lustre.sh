#!/bin/sh

# Script d'installation de Lustre
# Thierry Excoffier pour MIF25, 2017
# Modifié pour CR10, ENSL 2017


###################################################
# Détermine les paquets à installer sur le système
###################################################

NEED=""
[ "$(which avr-gcc)" = "" ] && NEED="$NEED gcc-avr"
#[ "$(which arduino)" = "" ] && NEED="$NEED arduino"
[ "$(which tclsh)"   = "" ] && NEED="$NEED tcl"
if [ "$NEED" != "" ]
then
    echo "Vous devez installer les paquets suivants :"
    echo "    apt-get install    $NEED"
    exit 1
fi >&2

set -e # Arrête le script en cas de problème


###################################################
# Install LUSTRE
###################################################

# http://www-verimag.imag.fr/~raymond/?p=148
case "$1" in
    linux64) V="linux64/lustre-v4-III-ca-linux64" ;;
    linux32) V="linux32/lustre-v4-III-c-linux32"  ;;
    macosx)  V="macosx/lustre-v4-III-c-macosx"    ;;
    *)
	echo "Indiquez comme paramètre: linux64 | linux32 | macosx" >&2
	exit 1
esac

NOM="$(basename "$V")"
TGZ="http://www-verimag.imag.fr/DIST-TOOLS/SYNCHRONE/lustre-v4/distrib/$V.tgz"
if [ ! -d "$NOM" ]
then
    if [ ! -f "$NOM.tgz" ]
    then
	wget "$TGZ"
    fi
    zcat <"$NOM.tgz" | tar -xvf -
fi

###################################################
# Ajoute la commande wish si elle manque
###################################################

if [ "$(which wish)" = "" ]
then
    for I in tclsh8.5 tclsh8.6
    do
	J="$(which $I)"
	if  [ "$J" != "" ]
	then
	    ln -s "$J" "$NOM"/bin/wish || true
	    break
	fi
    done
fi


###################################################
# Configure l'environnement
###################################################

cd "$NOM"
export LUSTRE_INSTALL="$(pwd)"
. ./setenv.sh
cd ..
export PS1="###LUSTRE###$ "
echo "############################################################
Some Examples
   cd $LUSTRE_INSTALL/examples/     # Official Lustre tests
   # Simulate a node
   luciole filename.lus node
   # Compile (see the provided makefile)
############################################################
For the arduino led
   cd $(pwd)/LustreArduino
   make all upload
############################################################
If you quit this shell, you quit the Lustre environment.
############################################################
"

exec /bin/bash --norc
