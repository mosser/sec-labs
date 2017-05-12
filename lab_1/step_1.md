# SEC-Lab1, Step 1

  * M2 IF, ENS Lyon
  * Sébastien Mosser, Université Cote d'Azur, I3S, [email](mailto:mosser@i3s.unice.fr)
  * Laure Gonnord, Université Lyon 1, LIP [email](mailto:laure.gonnord@ens-lyon.fr)
  * Version: 2017.05

  * Previous step:

## Objectives

## Documentation & Bibliography

```C
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h> 

int main(void)
{
        //initialisation de ports, variables, ...
        while(1)
        {
          //des trucs
          _delay_ms(300);
        }
}
```

### Blink a led (or control a wire)
Pour allumer ou éteindre une LED, il faut configurer le registre
d'entrée/sortie sur lequel est connectée la LED. Comme l'explique la
documentation (Voir
  [port manip](https://www.arduino.cc/en/Reference/PortManipulation)). Attention,
la documentation est faite pour le langage arduino de haut
niveau. Pour manipuler une chaîne de bits en C on pourra utiliser
`0b11111110` (à la place du `B11111110`).

* Les
connections ``analog'' 0 à 5 sont contrôlées à l'aide du registre
nommé \verb!PORTC! (commande) le bit
0 de chacun de ces deux registres commande la connection 0, le bit 1 la
connection 1, ... ** todo changer pour digital 13 **

*Le registre de configuration se nomme DDRC. Chaque bit de ce
  registre représente une entrée / sortie du port C (le bit 0 pour la
  connection 0, ...). Un 0 signifie une utilisation en tant
  qu'entrée et un 1 signifie une utilisation en tant que sortie.

Other links:
[Boolean](http://playground.arduino.cc/Code/BitMath)
[AVR libc doc](http://www.nongnu.org/avr-libc/user-manual/group__util__delay.html)



## The LED example

## Expected Work



  * Going to next step: 
