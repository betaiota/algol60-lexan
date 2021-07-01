#include <iostream>
#include <fstream>
#include <cctype>
#include <string.h>
using namespace std;
#include "directiveFile.h"
#include "DescriptionFile.h"
#include "classTab.h"
#include "classTree.h"
#include "CodeGen.h"
#include "LexAn.h"
#include "SinAn.h"



//table TabLex;


int main()
{
    if (LexAnal("example.txt"))
            return -1;
    else if (SintAnal("resultlex.txt"))
            return -1;
    else if (CodeGen("tablex.obj"))
        return -1;
    return 0;
}
