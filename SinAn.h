
ios::pos_type pos = 0;
char* help(node* lol){ return (char*)"non";}
char* GetSrt(int kek, int chaburek){return (char*)"lol";}


int getToken(ifstream &fin, int &lex_num)
{
    int token=-1;
    pos = fin.tellg();
    fin.read((char*)&token,sizeof(int));
    fin.read((char*)&lex_num,sizeof(int));
    cout << token << "  " << lex_num << endl;
    return token;
}

int putToken(ifstream &fin)
{
    fin.clear();
    fin.seekg(pos);
    return 0;
}








int Mnojit(ifstream &fin, int &token, int &lex_num, char* leaf)
{
    char temp[256]="";
   // node *temp1 = NULL;
    if (token == TABCONST)
    {
        strcat(leaf,TabLex.GetConst(lex_num));
        strcat(leaf," ");
        return 0;
    }
    if (!Variable(fin, token, lex_num, temp) )
    {
        strcat(leaf,temp);
        strcat(leaf," ");
        return 0;
    }
   /* if (!ProcOp(fin, token, lex_num, &temp1))
    {
        strcat(leaf,help(temp1));
        strcat(leaf," ");
        delete temp1;
        return 0;
    }*/
    temp[0] = 0;
    if (token != '(') return 1;
    token = getToken(fin, lex_num);
    if (arfViral(fin, token, lex_num, temp)) return 1;
    token = getToken(fin, lex_num);
    if (token != ')') return 1;
    strcat(leaf,temp);
    strcat(leaf," ");
    return 0;
}

int elTerm(ifstream &fin, int &token, int &lex_num, char* leaf)
{
    char t[2]={(char)token, 0};
    if ( token != '*' && token != '/')
    {
        putToken(fin);
        return 0;
    }
    token = getToken(fin, lex_num);
    if (Mnojit(fin, token, lex_num, leaf)) return 1;
    strcat(leaf, t);
    strcat(leaf," ");
    token = getToken(fin, lex_num);
    if (elTerm(fin, token, lex_num, leaf)) return 1;
    return 0;
}

int Term(ifstream &fin, int &token, int &lex_num, char* leaf)
{
    if (Mnojit(fin, token, lex_num, leaf)) return 1;
    token = getToken(fin, lex_num);
    if (elTerm(fin, token, lex_num, leaf)) return 1;
    return 0;
}

int elarfViral(ifstream &fin, int &token, int &lex_num, char* leaf)
{
    char t[2]={(char)token, 0};
    if (token != '+' && token != '-')
    {
        putToken(fin);
        return 0;
    }
    token = getToken(fin, lex_num);
    if (Term(fin, token, lex_num, leaf)) return 1;
    strcat(leaf, t);
    strcat(leaf," ");
    token = getToken(fin, lex_num);
    if (elarfViral(fin, token, lex_num, leaf)) return 1;
    return 0;
}

int arfViral(ifstream &fin, int &token, int &lex_num, char* leaf)
{
    if (Term(fin, token, lex_num, leaf)) return 1;
    token = getToken(fin, lex_num);
    if (elarfViral(fin, token, lex_num, leaf)) return 1;
    return 0;
}

int logVar(ifstream &fin, int &token, int &lex_num, char* leaf)
{
    int tt;
    if (arfViral(fin, token, lex_num, leaf)) return 1;
    token = getToken(fin, lex_num);
    if (token != '>' && token != '<' && token != '=' && token != LR && token != SR) return 1;
    tt= token;
    token = getToken(fin, lex_num);
    if (arfViral(fin, token, lex_num, leaf)) return 1;
    switch (tt)
    {
        case '>':
        strcat(leaf, ">");
        break;
        case '<':
        strcat(leaf, "<");
        break;
        case '=':
        strcat(leaf, "=");
        break;
        case LR:
        strcat(leaf, ">=");
        break;
        case SR:
        strcat(leaf, "<=");
        break;
    }
    strcat(leaf," ");
    cout << "logVar = " << leaf << endl;
    return 0;
}

int elSpisType(ifstream &fin, int &token, int &lex_num, node** leaf, int type)
{
    node *temp = NULL;
    int tt=token,lt=lex_num;
    if (token != ',')
    {
        putToken(fin);
        return 0;
    }
    token = getToken(fin,lex_num);
    tt=token;lt=lex_num;
    if (token != TABID) return 1;
    TabLex.SetIdAtr(lex_num, 1);
    SinTree.add_node(leaf,DESCRTP, TABWORD, type);
    token = getToken(fin,lex_num);
    if (elSpisType(fin, token, lex_num, &temp, type)) return 1;
    (*leaf)->right = temp;
    (*leaf)->left = SinTree.add_node(&temp, TABID, tt, lt);
    strcpy((*leaf)->left->dop,TabLex.GetName(lt));
    return 0;
}

int spisType(ifstream &fin, int &token, int &lex_num, node** leaf, int type)
{
    node *temp = NULL;
    int tt=token,lt=lex_num;
    if (token != TABID ) return 1;
    TabLex.SetIdAtr(lex_num, 1);
    token = getToken(fin,lex_num);
    if (elSpisType(fin, token, lex_num, &temp, type)) return 1;
    (*leaf)->right = temp;
    SinTree.add_node(&((*leaf)->left), TABID, tt, lt);
    strcpy((*leaf)->left->dop,TabLex.GetName(lt));
    return 0;
}

int opType(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    int tt=token,lt=lex_num;
    if (token == TABWORD && (lex_num == INTEGER || lex_num == BOOLEAN || lex_num == REAL))
    {
        SinTree.add_node(leaf,DESCRTP, tt, lt);
        token = getToken(fin,lex_num);
        if (spisType(fin, token, lex_num, leaf, lt)) return 1;
        return 0;
    }
    return 1;
}

int bordDoub(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    char temp[256]= "", temp1[256]="";
    if(arfViral(fin, token, lex_num, temp)) return 1;
    cout << " opmastemp = " << temp << endl;
    token = getToken(fin,lex_num);
    if (token != ':') return 1;
    token = getToken(fin,lex_num);
    if(arfViral(fin, token, lex_num, temp1))return 1;
    cout << " opmastemp1 = " << temp1 << endl;
    SinTree.add_node(leaf,DESCRAR);
    SinTree.add_node(&((*leaf)->left), -1);
    SinTree.add_node(&((*leaf)->right), -1);
    strcpy((*leaf)->left->dop,temp);
    strcpy((*leaf)->right->dop,temp1);
    return 0;

}

int elSpisBordDoub(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp = NULL, *temp1=NULL;
    if (token != ',')
    {
        putToken(fin);
        return 0;
    }
    token = getToken(fin,lex_num);
    if (bordDoub(fin, token, lex_num, &temp)) return 1;
    token = getToken(fin,lex_num);
    if (elSpisBordDoub(fin, token, lex_num, &temp1)) return 1;
    SinTree.add_node(leaf,DESCRAR);
    (*leaf)->left = temp;
    (*leaf)->right = temp1;
    return 0;
}

int SpisBordDoub(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp = NULL, *temp1=NULL;
    if (bordDoub(fin, token, lex_num, &temp)) return 1;
    token = getToken(fin,lex_num);
    if (elSpisBordDoub(fin, token, lex_num, &temp1))return 1;
    SinTree.add_node(leaf,DESCRAR);
    (*leaf)->left = temp;
    (*leaf)->right = temp1;
    return 0;
}

int SegMas(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp = NULL;
    int tt=token,lt=lex_num;
    if (token != TABID ) return 1;
    TabLex.SetIdAtr(lex_num, 2);
    token = getToken(fin,lex_num);
    if (token != '[') return 1;
    token = getToken(fin,lex_num);
    if (SpisBordDoub(fin, token, lex_num, &temp)) return 1;
    token = getToken(fin,lex_num);
    if (token != ']') return 1;
    SinTree.add_node(&((*leaf)->left), TABID, tt, lt);
    strcpy((*leaf)->left->dop,TabLex.GetName(lt));
    (*leaf)->right = temp;
    return 0;

}

int OpisatelMas(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    if (token == TABWORD && lex_num == ARRAY)
    {
        token = getToken(fin,lex_num);
        if (SegMas(fin, token, lex_num, leaf)) return 1;
        return 0;
    }
    return 1;
}

int OpMas(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    int tt=token,lt=lex_num;
    if (token == TABWORD && (lex_num == INTEGER || lex_num == BOOLEAN || lex_num == REAL))
    {
        SinTree.add_node(leaf,DESCRAR, tt, lt);
        token = getToken(fin,lex_num);
        if (OpisatelMas(fin, token, lex_num, leaf)) return 1;
        return 0;
    }
    return 1;
}

int Opisanie(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    int tt=token,lt=lex_num;
     if (token == TABWORD && (lex_num == INTEGER || lex_num == BOOLEAN || lex_num == REAL))
    {
        SinTree.add_node(leaf,DESCRTP, tt, lt);
        token = getToken(fin,lex_num);
        if (!OpisatelMas(fin, token, lex_num, leaf))
        {
            (*leaf)->type = DESCRAR;
            return 0;
        }
        if (spisType(fin, token, lex_num, leaf, lt)) return 1;
            return 0;
    }
    return 1;
}

int HeadFun(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    int tt=token,lt=lex_num;
    if (token != TABWORD || lex_num != BEGIN) return 1;
    token = getToken(fin, lex_num);
    SinTree.add_node(leaf,-2);
    if (Block(fin, token, lex_num, leaf)) return 1;
    (*leaf)->token.token = tt;
    (*leaf)->token.lex_num = lt;
    return 0;
}

int SpisOpisFun(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp = NULL, *temp1 = NULL;
    if (OpProc(fin, token, lex_num, &temp))
    {
        putToken(fin);
        return 0;
    }
    token = getToken(fin, lex_num);
    if (SpisOpisFun(fin, token, lex_num, &temp1)) return 1;
    SinTree.add_node(leaf,DESCRPR);
    (*leaf)->left = temp;
    (*leaf)->right = temp1;
    return 0;
}

int SpisFun(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp = NULL, *temp1 = NULL;
    if (SpisOpisFun(fin, token, lex_num, &temp)) return 1;
    token = getToken(fin, lex_num);
    if (HeadFun(fin, token, lex_num, &temp1)) return 1;
    SinTree.add_node(leaf,ZERO);
    (*leaf)->left = temp;
    (*leaf)->right = temp1;
    return 0;
}

int Condition(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    char temp[256]= "";
    if(token == TABWORD && lex_num == IF)
        token = getToken(fin, lex_num);
    else return 1;
    if(logVar(fin, token, lex_num, temp)) return 1;
    token = getToken(fin, lex_num);
    if(token == TABWORD && lex_num == THEN)
    {
        SinTree.add_node(leaf,IF, TABWORD, IF);
        strcpy((*leaf)->dop,temp);
        return 0;
    }
    else return 1;
}

int elseOp(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    if(token == TABWORD && lex_num == ELSE)
    {
        token = getToken(fin, lex_num);
        if(Operator(fin, token, lex_num, leaf)) return 1;
        return 0;
    }
    else
    {
        putToken(fin);
        return 0;
    }
}

int conditOp(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp = NULL, *temp1 = NULL;
    if(Condition(fin, token, lex_num, leaf)) return 1;
    token = getToken(fin, lex_num);
    if(unConditOp(fin, token, lex_num, &temp)) return 1;
    token = getToken(fin, lex_num);
    if(elseOp(fin, token, lex_num, &temp1)) return 1;
    (*leaf)->left = temp;
    (*leaf)->right= temp1;
    return 0;
}

int cycleBegin(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    char temp[256] = "", temp1[256] = "";

    if(token == TABWORD && lex_num == STEP)
        token = getToken(fin, lex_num);
    else if(token == TABWORD && lex_num == WHILE)
    {
        token = getToken(fin, lex_num);
        if(logVar(fin, token, lex_num, temp)) return 1;
        SinTree.add_node(leaf,WHILE,TABWORD, WHILE);
        strcpy((*leaf)->dop,temp);
        return 0;
    }
    else return 1;
    if(arfViral(fin, token, lex_num, temp)) return 1;
    token = getToken(fin, lex_num);
    if(token == TABWORD && lex_num == UNTIL)
        token = getToken(fin, lex_num);
    else return 1;
    if(logVar(fin, token, lex_num, temp1)) return 1;
    SinTree.add_node(leaf,STEP,TABWORD, STEP);
    SinTree.add_node(&((*leaf)->left), -1);
    SinTree.add_node(&((*leaf)->right), -1);
    strcpy((*leaf)->right->dop,temp1);
    strcpy((*leaf)->left->dop,temp);
    return 0;
}

int cycleHead(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp = NULL;
    node *temp1=NULL;
    if(token == TABWORD && lex_num == FOR)
        token = getToken(fin, lex_num);
    else return 1;
    if (assignOp(fin, token, lex_num, &temp)) return 1;
    token = getToken(fin, lex_num);
    if(cycleBegin(fin, token, lex_num, &temp1)) return 1;
    token = getToken(fin, lex_num);
    if(token == TABWORD && lex_num == DO)
    {
        SinTree.add_node(leaf,FORHEAD,TABWORD, FOR);
        strcpy((*leaf)->dop,temp->dop);
        (*leaf)->left=temp1;
        delete temp;
        return 0;
    }
    else return 1;
}

int cycleOp(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp = NULL;
    if(cycleHead(fin, token, lex_num, leaf)) return 1;
    token = getToken(fin, lex_num);
    if(Operator(fin, token, lex_num, &temp)) return 1;
    (*leaf)->right=temp;
    return 0;
}

int assignOp(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    char temp[256]="";
    if (Variable(fin, token, lex_num, temp)) return 1;
    strcat(temp," ");
    token = getToken(fin, lex_num);
    if(token != RAV) return 1;
    token = getToken(fin, lex_num);
    if(arfViral(fin, token, lex_num, temp)) return 1;
    SinTree.add_node(leaf, ASSOP);
    strcat(temp,":=");
    strcat(temp," ");
    strcpy((*leaf)->dop,temp);
    cout << " assoptemp = " << temp << endl;
    return 0;
}

int elSpisInd(ifstream &fin, int &token, int &lex_num, char* leaf)
{
    if (token != ',')
    {
        putToken(fin);
        return 0;
    }
    strcat(leaf,", ");
    token = getToken(fin, lex_num);
    if (arfViral(fin, token, lex_num, leaf))return 1;
    token = getToken(fin, lex_num);
    if (elSpisInd(fin, token, lex_num, leaf)) return 1;
    return 0;
}

int SpisInd(ifstream &fin, int &token, int &lex_num, char* leaf)
{
    if (arfViral(fin, token, lex_num, leaf)) return 1;
    token = getToken(fin, lex_num);
    if (elSpisInd(fin, token, lex_num, leaf)) return 1;
    return 0;
}

int Variable(ifstream &fin, int &token, int &lex_num, char* leaf)
{
    if (token == TABID && TabLex.GetIdAtr(lex_num) == 1)
    {
        strcat(leaf,TabLex.GetName(lex_num));
        return 0;
    }
    if (token == TABID && TabLex.GetIdAtr(lex_num) == 2)
    {
        strcat(leaf,TabLex.GetName(lex_num));
        strcat(leaf," ");
        token = getToken(fin, lex_num);
        if (token != '[') return 1;
        strcat(leaf,"[");
        strcat(leaf," ");
        token = getToken(fin, lex_num);
        if (SpisInd(fin, token, lex_num,leaf)) return 1;
        token = getToken(fin, lex_num);
        if (token != ']') return 1;
        strcat(leaf,"]");
        return 0;
    }
    return 1;
}

int Expression(ifstream &fin, int &token, int &lex_num, char* leaf)
{
   int tt;
   if (arfViral(fin, token, lex_num, leaf)) return 1;
    token = getToken(fin, lex_num);
    if (token != '>' && token != '<' && token != '=' && token != LR && token != SR)
    {
        strcat(leaf," ");
        cout << "arVar = " << leaf << endl;
        putToken(fin);
        return 0;
    }
    tt= token;
    token = getToken(fin, lex_num);
    if (arfViral(fin, token, lex_num, leaf)) return 1;
    switch (tt)
    {
        case '>':
        strcat(leaf, ">");
        break;
        case '<':
        strcat(leaf, "<");
        break;
        case '=':
        strcat(leaf, "=");
        break;
        case LR:
        strcat(leaf, ">=");
        break;
        case SR:
        strcat(leaf, "<=");
        break;
    }
    strcat(leaf," ");
    cout << "logVar = " << leaf << endl;
    return 0;
}

int maska(ifstream &fin, int &token, int &lex_num, char* leaf)
{
    if (token == TABID && TabLex.GetIdAtr(lex_num) == 2)
    {
        strcat(leaf,TabLex.GetName(lex_num));
        strcat(leaf," ");
        token = getToken(fin, lex_num);
        if (token != '[')
        {
            putToken(fin);
            return 0;
        }
        strcat(leaf,"[");
        strcat(leaf," ");
        token = getToken(fin, lex_num);
        if (SpisInd(fin, token, lex_num, leaf)) return 1;
        token = getToken(fin, lex_num);
        if (token != ']') return 1;
        strcat(leaf,"]");
        strcat(leaf," ");
        return 0;
    }
    else return 1;
}

int elSpisFacPar(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp=NULL;
    char temp1[256]="";
    int tt=token, lt = lex_num;
    ios::pos_type po = 0;
    if (token != ',')
    {
        putToken(fin);
        return 0;
    }
    token = getToken(fin, lex_num);
    po = fin.tellg();
    tt=token;
    lt = lex_num;
    if (Expression(fin, token, lex_num, temp1))
    {
        token = tt;
        lex_num = lt;
        fin.clear();
        fin.seekg(po);
        pos = po;
        if (maska(fin, token, lex_num, temp1)) return 1;
    }
    token = getToken(fin, lex_num);
    if (elSpisFacPar(fin, token, lex_num, &temp)) return 1;
    SinTree.add_node(leaf,PROCOP);
    strcpy((*leaf)->dop, temp1);
    (*leaf)->right = temp;
    return 0;
}

int SpisFacPar(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp=NULL;
    char temp1[256]="";
    int tt=token, lt = lex_num;
    ios::pos_type po = 0;
    po = fin.tellg();
    if (Expression(fin, token, lex_num, temp1))
    {
        token = tt;
        lex_num = lt;
        fin.clear();
        fin.seekg(po);
        pos = po;
        if (maska(fin, token, lex_num, temp1)) return 1;
    }
    token = getToken(fin, lex_num);
    if (elSpisFacPar(fin, token, lex_num, &temp)) return 1;
    SinTree.add_node(leaf,PROCOP);
    strcpy((*leaf)->dop, temp1);
    (*leaf)->right = temp;
    return 0;
}

int ProcOp(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp=NULL;
    int lt=lex_num;
    if (token == TABID && TabLex.GetIdAtr(lex_num) == 3)
    {
        token = getToken(fin, lex_num);
        if (token != '(') return 1;
        token = getToken(fin, lex_num);
        if (SpisFacPar(fin, token, lex_num, &temp)) return 1;
        token = getToken(fin, lex_num);
        if (token != ')') return 1;
        SinTree.add_node(leaf,PROCOP);
        strcpy((*leaf)->dop, TabLex.GetName(lt));
        (*leaf)->right = temp;
        return 0;
    }
    return 1;
}

int OpSqrt(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    if(token == TABWORD && lex_num == SQRT)
        token = getToken(fin, lex_num);
    else return 1;
    SinTree.add_node(leaf,SQRT);
    if(token != '(') return 1;
    token = getToken(fin, lex_num);
    if(Variable(fin, token, lex_num, (*leaf)->dop)) return 1;
    token = getToken(fin, lex_num);
    if(token != ')') return 1;
    return 0;
}

int isString(ifstream &fin, int &token, int &lex_num, char* leaf)
{
    if(token != '"') return 1;
    strcpy(leaf, GetSrt(token, lex_num));
    return 0;
}

int elSpisRead(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    char temp[256]="";
    node *temp1 = NULL;
    if(token != ',')
    {
        putToken(fin);
        return 0;
    }
    token = getToken(fin, lex_num);
    if(Variable(fin, token, lex_num, temp)) return 1;
    token = getToken(fin, lex_num);
    if(elSpisRead(fin, token, lex_num, &temp1)) return 1;
    SinTree.add_node(leaf, READ);
    strcpy((*leaf)->dop, temp);
    (*leaf)->right = temp1;
    return 0;
}

int spisRead(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    char temp[256]="";
    node *temp1 = NULL;
    if(Variable(fin, token, lex_num, temp)) return 1;
    token = getToken(fin, lex_num);
    if(elSpisRead(fin, token, lex_num, &temp1)) return 1;
    SinTree.add_node(leaf, READ);
    strcpy((*leaf)->dop, temp);
    (*leaf)->right = temp1;
    return 0;
}


int elSpisWrite(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    char temp[256]="";
    node *temp1 = NULL;
    if(token != ',')
    {
        putToken(fin);
        return 0;
    }
    token = getToken(fin, lex_num);
    if(Variable(fin, token, lex_num, temp) && isString(fin, token, lex_num, temp)) return 1;
    token = getToken(fin, lex_num);
    if(elSpisWrite(fin, token, lex_num, &temp1)) return 1;
    SinTree.add_node(leaf, WRITE);
    strcpy((*leaf)->dop, temp);
    (*leaf)->right = temp1;
    return 0;
}

int spisWrite(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    char temp[256]="";
    node *temp1 = NULL;
    if(Variable(fin, token, lex_num, temp))
    if(isString(fin, token, lex_num, temp)) return 1;
    token = getToken(fin, lex_num);
    if(elSpisWrite(fin, token, lex_num, &temp1)) return 1;
    SinTree.add_node(leaf, WRITE);
    strcpy((*leaf)->dop, temp);
    (*leaf)->right = temp1;
    return 0;
}

int OpRead(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp = NULL;
    if(token == TABWORD && lex_num == READ)
        token = getToken(fin, lex_num);
    else return 1;
    if(token != '(') return 1;
    token = getToken(fin, lex_num);
    if(spisRead(fin, token, lex_num, &temp)) return 1;
    token = getToken(fin, lex_num);
    if(token != ')') return 1;
    SinTree.add_node(leaf, READ);
    (*leaf)->right = temp;
    return 0;
}

int opWrite(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp = NULL;
    if(token == TABWORD && lex_num == WRITE)
        token = getToken(fin, lex_num);
    else return 1;
    if(token != '(') return 1;
    token = getToken(fin, lex_num);
    if(spisWrite(fin, token, lex_num, &temp)) return 1;
    token = getToken(fin, lex_num);
    if(token != ')') return 1;
    SinTree.add_node(leaf, WRITE);
    (*leaf)->right = temp;
    return 0;
}

int SpisVal(ifstream &fin, int &token, int &lex_num, node** leaf, node *spf)
{
    if (token == TABWORD && lex_num == VALUE)
    {
          token = getToken(fin,lex_num);
          if (SpisIdk(fin, token, lex_num, leaf, spf)) return 1;
          token = getToken(fin,lex_num);
          if (token != ';') return 1;
          return 0;
    }
    putToken(fin);
    return 0;
}


int elSpisIdk(ifstream &fin, int &token, int &lex_num, node** leaf, node *spf)
{
    node *temp=spf;
    char  buf2[256];
    int i=1;
    if (token != ',')
    {
        putToken(fin);
        return 0;
    }
    token = getToken(fin,lex_num);
    if (token != TABID) return 1;
    strcpy(buf2,TabLex.GetName(lex_num));
    while (strncmp(temp->dop, buf2,256))
    {
        i++;
        temp=temp->left;
    }
    SinTree.add_node(leaf, i, token, lex_num);
    strcpy((*leaf)->dop,TabLex.GetName(lex_num));
    (*leaf)->token.token = token;
    (*leaf)->token.lex_num = lex_num;
    token = getToken(fin,lex_num);
    if (elSpisIdk(fin, token, lex_num, &((*leaf)->left), spf)) return 1;
    return 0;
}

int SpisIdk(ifstream &fin, int &token, int &lex_num, node** leaf, node *spf)
{
    node *temp=spf;
    char  buf2[256];
    int i=1;
    if (token == TABID)
    {
          strcpy(buf2,TabLex.GetName(lex_num));
          while (strncmp(temp->dop, buf2,256))
          {
              i++;
              temp=temp->left;
          }
          SinTree.add_node(leaf, i,token, lex_num);
          strcpy((*leaf)->dop,TabLex.GetName(lex_num));
          (*leaf)->token.token = token;
          (*leaf)->token.lex_num = lex_num;
          token = getToken(fin,lex_num);
          if (elSpisIdk(fin, token, lex_num, &((*leaf)->left), spf)) return 1;
          return 0;
    }
    return 1;
}

/*int elSpisId(ifstream &fin, int &token, int &lex_num, node** leaf, int type)
{
    if (token != ',')
    {
        putToken(fin);
        return 0;
    }
    token = getToken(fin,lex_num);
    if (token != TABID) return 1;
    TabLex.SetIdAtr(lex_num, 1);
    SinTree.add_node(leaf, PROCOPER, token, lex_num);
    strcpy((*leaf)->dop,TabLex.GetName(lex_num));
    token = getToken(fin,lex_num);
    (*leaf)->token = token;
    (*leaf)->lex_num = lex_num;
    if (elSpisId(fin, token, lex_num, &((*leaf)->left), type)) return 1;
    return 0;
}

int SpisId(ifstream &fin, int &token, int &lex_num, node** leaf, int type)
{
    if (token == TABID)
    {
          TabLex.SetIdAtr(lex_num, 1);
          SinTree.add_node(leaf, PROCOPER, token, lex_num);
          strcpy((*leaf)->dop,TabLex.GetName(lex_num));
          token = getToken(fin,lex_num);
          (*leaf)->token = token;
          (*leaf)->lex_num = lex_num;
          if (elSpisId(fin, token, lex_num, &((*leaf)->left),type)) return 1;
          return 0;
    }
    return 1;
}*/

int OpPerMas(ifstream &fin, int &token, int &lex_num, node** leaf, int type)
{

    SinTree.add_node(leaf, DESCRTP,TABWORD, type);
    if (!spisType(fin, token, lex_num, leaf, type))
    return 0;
    else if (!OpisatelMas(fin, token, lex_num, leaf))
    {
        (*leaf)->type = DESCRAR;
        return 0;
    }
    else return 1;
}

int elSpisSpec(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    int lt = lex_num;
    if (token == TABWORD && (lex_num == INTEGER || lex_num == BOOLEAN || lex_num == REAL))
    {
        SinTree.add_node(leaf, lex_num);
        token = getToken(fin,lex_num);
        if (OpPerMas(fin, token, lex_num, &((*leaf)->left), lt)) return 1;
        token = getToken(fin,lex_num);
        if (token != ';') return 1;
        token = getToken(fin,lex_num);
        if (elSpisSpec(fin, token, lex_num, &((*leaf)->right))) return 1;
        return 0;
    }
    else
    {
        putToken(fin);
        return 0;
    }
}

int SpisSpec(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    int lt = lex_num;
    if (token == TABWORD && (lex_num == INTEGER || lex_num == BOOLEAN || lex_num == REAL))
    {
        SinTree.add_node(leaf, lex_num);
        token = getToken(fin,lex_num);
        if (OpPerMas(fin, token, lex_num, &((*leaf)->left), lt)) return 1;
        token = getToken(fin,lex_num);
        if (token != ';') return 1;
        token = getToken(fin,lex_num);
        if (elSpisSpec(fin, token, lex_num, &((*leaf)->right))) return 1;
        return 0;
    }
    else return 1;
}

int elSpisForPar(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    if (token != ',')
    {
        putToken(fin);
        return 0;
    }
    token = getToken(fin,lex_num);
    if (token != TABID) return 1;
    SinTree.add_node(leaf, PROCEDURE);
    strcpy((*leaf)->dop,TabLex.GetName(lex_num));
    (*leaf)->token.token = token;
    (*leaf)->token.lex_num = lex_num;
    token = getToken(fin,lex_num);
    if (elSpisForPar(fin, token, lex_num, &((*leaf)->left))) return 1;
    return 0;
}

int SpisForPar(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    if (token != TABID) return 1;
    SinTree.add_node(leaf, PROCEDURE);
    strcpy((*leaf)->dop,TabLex.GetName(lex_num));
    (*leaf)->token.token = token;
    (*leaf)->token.lex_num = lex_num;
    token = getToken(fin,lex_num);
    if (elSpisForPar(fin, token, lex_num, &((*leaf)->left))) return 1;
    return 0;
}

int NameProc(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    char temp1[256]="";
    node *tempp = NULL, *tempp1 = NULL, *tempp2 = NULL, *tempp3 = NULL;
    if (token != TABID ) return 1;
    TabLex.SetIdAtr(lex_num, 3);
    strcpy (temp1, TabLex.GetName(lex_num));
    token = getToken(fin,lex_num);
    if (token != '(') return 1;
    token = getToken(fin,lex_num);
    if (SpisForPar(fin, token, lex_num, &tempp3)) return 1;
    token = getToken(fin,lex_num);
    if (token != ')') return 1;
    token = getToken(fin,lex_num);
    if (token != ';') return 1;
    token = getToken(fin,lex_num);
    if (SpisVal(fin, token, lex_num, &tempp1,tempp3)) return 1;
    token = getToken(fin,lex_num);
    if (SpisSpec(fin, token, lex_num, &tempp2)) return 1;
    SinTree.add_node(leaf, PROCEDURE);
    SinTree.add_node(&((*leaf)->left), PROCEDURE);
    SinTree.add_node(&tempp, PROCEDURE);
    strcpy ((*leaf)->dop,temp1);
    tempp->left = tempp1;
    tempp->right = tempp2;
    (*leaf)->left->left = tempp3;
    (*leaf)->left->right = tempp;

    return 0;

}

int OpProc(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    if (token == TABWORD && lex_num == PROCEDURE)
    {
        token = getToken(fin,lex_num);
        if (NameProc(fin, token, lex_num, leaf)) return 1;
        token = getToken(fin,lex_num);
        if (token == TABWORD && lex_num == BEGIN)
        {
            if (Prog(fin, token, lex_num, &((*leaf)->right))) return 1;
            return 0;
        }
        return 1;
    }
    return 1;
}

int elSpisOperator(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp = NULL , *temp1 = NULL;
    if (Operator(fin, token, lex_num, &temp))
    {
        putToken(fin);
        return 0;
    }
    token = getToken(fin, lex_num);
    if (elSpisOperator(fin, token, lex_num, &temp1)) return 1;
    SinTree.add_node(leaf, 0);
    (*leaf)->left = temp;
    (*leaf)->right = temp1;
    return 0;
}

int SpisOperator(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp = NULL , *temp1 = NULL;
    if (Operator(fin, token, lex_num, &temp)) return 1;
    token = getToken(fin, lex_num);
    if (elSpisOperator(fin, token, lex_num, &temp1)) return 1;
    SinTree.add_node(leaf, 0);
    (*leaf)->left = temp;
    (*leaf)->right = temp1;
    return 0;
}

int BeginOpis(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp = NULL , *temp1 = NULL;
    if (Opisanie(fin, token, lex_num, &temp))
    {
        putToken(fin);
        return 0;
    }
    token = getToken(fin, lex_num);
    if (token != ';') return 1;
    token = getToken(fin, lex_num);
    if (BeginOpis(fin, token, lex_num, &temp1)) return 1;
    SinTree.add_node(leaf, 0);
    (*leaf)->left = temp;
    (*leaf)->right = temp1;
    cout << "lolkaman" << endl;
    return 0;
}

int HeadBlock(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    node *temp = NULL , *temp1 = NULL;
    if (Opisanie(fin, token, lex_num, &temp)) return 1;
    token = getToken(fin, lex_num);
    if (token != ';') return 1;
    token = getToken(fin, lex_num);
    if (BeginOpis(fin, token, lex_num, &temp1)) return 1;
    SinTree.add_node(leaf, 0);
    (*leaf)->left = temp;
    (*leaf)->right = temp1;
    return 0;
}

int AddOper(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    if (SpisOperator(fin, token, lex_num, &((*leaf)->right))) return 1;
    token = getToken(fin, lex_num);
    if (token != TABWORD || lex_num != END) return 1;
    token = getToken(fin, lex_num);
    if (token != ';') return 1;
    return 0;
}

int Block(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    if (HeadBlock(fin, token, lex_num, &((*leaf)->left))) return 1;
    token = getToken(fin, lex_num);
    if (SpisOperator(fin, token, lex_num, &((*leaf)->right))) return 1;
    token = getToken(fin, lex_num);
    if (token != TABWORD || lex_num != END) return 1;
    token = getToken(fin, lex_num);
    if (token != '.') return 1;
    return 0;
}

int Prog(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    if (token != TABWORD || lex_num != BEGIN) return 1;
    token = getToken(fin, lex_num);
    SinTree.add_node(leaf, -1);
    if (!Block(fin, token, lex_num, leaf))
    (*leaf)->type = BLOCK;
    else if (!AddOper(fin, token, lex_num, leaf))
    (*leaf)->type = ADDOP;
    else return 1;
    return 0;
}

int HeadOp(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    if (OpSqrt(fin, token, lex_num, leaf) && assignOp(fin, token, lex_num, leaf) && ProcOp(fin, token, lex_num, leaf)&& opWrite(fin, token, lex_num, leaf)&& OpRead(fin, token, lex_num, leaf)) return 1;
    token = getToken(fin, lex_num);
    if (token != ';') return 1;
    return 0;
}

int unConditOp(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    if (HeadOp(fin, token, lex_num, leaf) && Prog(fin, token, lex_num, leaf)) return 1;
    return 0;
}

int Operator(ifstream &fin, int &token, int &lex_num, node** leaf)
{
    if (unConditOp(fin, token, lex_num, leaf) && cycleOp(fin, token, lex_num, leaf) && conditOp(fin, token, lex_num, leaf)) return 1;
    return 0;
}


int SintAnal(const char *filename)
{
   int lex_num, token;
   ifstream fin("tablex.obj", ios::binary);
  /* while (1)
   {*/
       // if (token ==-1) break;
        //начальная функция
        token = getToken(fin, lex_num);
        cout <<  SpisFun(fin, token, lex_num, &SinTree.TREE) << endl;
   // }

   fin.close();
   return 0;
}
