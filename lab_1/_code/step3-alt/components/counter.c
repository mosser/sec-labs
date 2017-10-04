#include <7seg.h>

void init_counter()     { init_7Seg(); }
int counter = 0;
void displayCounter()   { displayDigit(counter); }
void resetCounter()     { counter = 0; }
void incrementCounter() { counter = (counter + 1) % 9; }
