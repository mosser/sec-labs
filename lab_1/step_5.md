# SEC-Lab1, Step 5

  * M2 IF, ENS Lyon
  * Sébastien Mosser, Université Cote d'Azur, I3S, [email](mailto:mosser@i3s.unice.fr)
  * Laure Gonnord, Université Lyon 1, LIP [email](mailto:laure.gonnord@ens-lyon.fr)
  * Version: 2017.05

  * Previous step: [Step #4](https://github.com/mosser/sec-labs/blob/master/lab_1/step_4.md)


## Objectives



## Documentation & Bibliography

[Lustre official webpage](http://www-verimag.imag.fr/Lustre-V6.html?lang=fr)

**TODO voir ce qui vient avec lustre V6, sinon back to V4**

![Lustre compilation flow](figs/compilChainLustre.pdf)

## The LED example
```
node cpt(reset:bool) returns  (led_on: bool) ;
let
   led_on = false -> if reset then true pre(led_on);
tel
```

## Expected Work


  * Going to next step: [Step #6](https://github.com/mosser/sec-labs/blob/master/lab_1/step_6.md)
