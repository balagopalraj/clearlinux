/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_htop
#define HEADER_htop
/*
htop - htop.h
(C) 2004-2011 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

//#link m

#define COPYRIGHT "(C) 2004-2012 Hisham Muhammad"

typedef bool(*ForeachProcessFn)(Process*, size_t);

void sortBy(Panel* panel, ProcessList* pl, Settings* settings, int headerHeight, FunctionBar* defaultBar, Header* header);

int main(int argc, char** argv);

#endif