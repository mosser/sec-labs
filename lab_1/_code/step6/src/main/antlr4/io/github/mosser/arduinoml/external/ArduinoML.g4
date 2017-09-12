grammar ArduinoML;


/******************
 ** Parser rules **
 ******************/


app         :   'application' name=IDENTIFIER '{' actuator+ state+ '}';

actuator    :   'actuator' location ;
location    :   id=IDENTIFIER ':' port=PORT_NUMBER;

state       :   initial? name=IDENTIFIER '{'  action+ next '}';
action      :   receiver=IDENTIFIER 'is' value=SIGNAL;
next        :   'goto' target=IDENTIFIER ;
initial     :   '->';

/*****************
 ** Lexer rules **
 *****************/

PORT_NUMBER     :   [1-9] | '11' | '12' | '13';
IDENTIFIER      :   LOWERCASE (LOWERCASE|UPPERCASE)+;
SIGNAL          :   'HIGH' | 'LOW';

/*************
 ** Helpers **
 *************/

fragment LOWERCASE  : [a-z];                                 // abstract rule, does not really exists
fragment UPPERCASE  : [A-Z];
NEWLINE             : ('\r'? '\n' | '\r')+      -> skip;
WS                  : ((' ' | '\t')+)           -> skip;     // who cares about whitespaces?
COMMENT             : '#' ~( '\r' | '\n' )*     -> skip;     // Single line comments, starting with a #