#include "classTabO.h"
#include "classTreeO.h"


//Лексический генератор
int LexAnal(const char *);
int commentbreak(ifstream &);
int nextToken(ifstream &, ofstream&, int &, int &);
int writeString(ifstream &, ofstream &);

//Синтаксический генератор
int getToken(ifstream &, int &);
int putToken(ifstream &);


char* help(node* );
char* GetSrt(int , int );


int maska(ifstream &, int &, int &, char*);
int Mnojit(ifstream &, int &, int &, char*);
int elTerm(ifstream &, int &, int &, char*);
int Term(ifstream &, int &, int &, char*);
int elarfViral(ifstream &, int &, int &, char*);
int arfViral(ifstream &, int &, int &, char*);
int elSpisInd(ifstream &, int &, int &, char*);
int SpisInd(ifstream &, int &, int &, char*);
int Variable(ifstream &, int &, int &, char*);
int elSpisType(ifstream &, int &, int &, node**,int);
int spisType(ifstream &, int &, int &, node**,int);
int opType(ifstream &, int &, int &, node**);
int bordDoub(ifstream &, int &, int &, node**);
int elSpisBordDoub(ifstream &, int &, int &, node**);
int SpisBordDoub(ifstream &, int &, int &, node**);
int SegMas(ifstream &, int &, int &, node**);
int OpisatelMas(ifstream &, int &, int &, node**);
int OpMas(ifstream &, int &, int &, node**);
int Opisanie(ifstream &, int &, int &, node**);
int HeadFun(ifstream &, int &, int &, node**);
int SpisOpisFun(ifstream &, int &, int &, node**);
int SpisFun(ifstream &, int &, int &, node**);
int Condition(ifstream &, int &, int &, node**);
int elseOp(ifstream &, int &, int &, node**);
int conditOp(ifstream &, int &, int &, node**);
int cycleBegin(ifstream &, int &, int &, node**);
int cycleHead(ifstream &, int &, int &, node**);
int cycleOp(ifstream &, int &, int &, node**);
int logVar(ifstream &, int &, int &, char*);
int assignOp(ifstream &, int &, int &, node**);
int Expression(ifstream &, int &, int &, char*);
int elSpisFacPar(ifstream &, int &, int &, node**);
int SpisFacPar(ifstream &, int &, int &, node**);
int ProcOp(ifstream &, int &, int &, node**);
int OpSqrt(ifstream &, int &, int &, node**);
int isString(ifstream &, int &, int &, char*);
int elSpisRead(ifstream &, int &, int &, node**);
int spisRead(ifstream &, int &, int &, node**);
int elSpisWrite(ifstream &, int &, int &, node**);
int spisWrite(ifstream &, int &, int &, node**);
int OpRead(ifstream &, int &, int &, node**);
int opWrite(ifstream &, int &, int &, node**);
int elSpisIdk(ifstream &, int &, int &, node**, node*);
int SpisIdk(ifstream &, int &, int &, node**, node*);
//int elSpisId(ifstream &, int &, int &, node**, int);
//int SpisId(ifstream &, int &, int &, node**, int);
int SpisVal(ifstream &, int &, int &, node**, node*);
int OpPerMas(ifstream &, int &, int &, node**,int);
int elSpisForPar(ifstream &, int &, int &, node**);
int SpisForPar(ifstream &, int &, int &, node**);
int elSpisSpec(ifstream &, int &, int &, node**);
int SpisSpec(ifstream &, int &, int &, node**);
int NameProc(ifstream &, int &, int &, node**);
int OpProc(ifstream &, int &, int &, node**);
int elSpisOperator(ifstream &, int &, int &, node**);
int SpisOperator(ifstream &, int &, int &, node**);
int BeginOpis(ifstream &, int &, int &, node**);
int HeadBlock(ifstream &, int &, int &, node**);
int AddOper(ifstream &, int &, int &, node**);
int Block(ifstream &, int &, int &, node**);
int Prog(ifstream &, int &, int &, node**);
int HeadOp(ifstream &, int &, int &, node**);
int unConditOp(ifstream &, int &, int &, node**);
int Operator(ifstream &, int &, int &, node**);


// Генератор кода
int FunGen(node *, int, ofstream &,  ofstream &, ofstream &, ofstream &);
int BodyGen(node *, ofstream &);
int DescrFun (node *, node *, ofstream &);
int Descr (node *, ofstream &);
int DescrHead (node *, ofstream &,  ofstream &, ofstream &, ofstream &);
int Oper (node *, ofstream &);
int assopg (node *, ofstream &);
int ifopg (node *, ofstream &);
int foropg (node *, ofstream &);
int addopg (node *, ofstream &);
int blockopg (node *, ofstream &);
int procopg (node *, ofstream &);
int sqrtopg (node *, ofstream &);
int readopg (node *, ofstream &);
int writeopg (node *, ofstream &);
