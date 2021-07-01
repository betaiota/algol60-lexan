#include <cstring>


int CodeGen(const char *filename)
{
    ofstream dfout("datafile.dat");
    ofstream hfout("headfile.dat");
    ofstream efout("endfile.dat");
    ofstream sfout("startfile.dat");
    ofstream rfout("resultfile.txt");
    ifstream dfin, hfin, efin, sfin;
    char buffer[100];
    sfout <<".386" << endl;
    sfout <<".MODEL flat, stdcall" << endl;
    sfout <<".STACK 4096" << endl;
    dfout <<".data" << endl;
    dfout <<"ExitProcess PROTO, dwExitCode: DWORD" << endl;
    hfout << ".code" << endl;
    SinTree.go(dfout, hfout, efout, sfout);
    dfout.close();
    hfout.close();
    efout.close();
    sfout.close();
    dfin.open("datafile.dat");
    hfin.open("headfile.dat");
    efin.open("endfile.dat");
    sfin.open("startfile.dat");
    while (!sfin.eof())
    {
        memset(buffer,0,sizeof(buffer));
        sfin.read((char*)buffer,sizeof(buffer)-1);
        rfout << buffer;
    }
    while (!dfin.eof())
    {
        memset(buffer,0,sizeof(buffer));
        dfin.read((char*)buffer,sizeof(buffer)-1);
        rfout << buffer;
    }
    while (!hfin.eof())
    {
        memset(buffer,0,sizeof(buffer));
        hfin.read((char*)buffer,sizeof(buffer)-1);
        rfout << buffer;
    }
    while (!efin.eof())
    {
        memset(buffer,0,sizeof(buffer));
        efin.read((char*)buffer,sizeof(buffer)-1);
        rfout << buffer;
    }
    sfin.close();
    dfin.close();
    hfin.close();
    efin.close();
    rfout.close();
   /* remove("datafile.dat");
    remove("headfile.dat");
    remove("endfile.dat");*/
    return 0;
}


int FunGen(node * leaf, int flag, ofstream &dfout,  ofstream &hfout, ofstream &efout, ofstream &rfout)
{
    node *temp = leaf;
    if (flag)
    {
        // написать в файл
        hfout << "main PROC" << endl;
        temp = leaf->left;
        while (temp)
        {
            if (DescrHead(temp->left, dfout, hfout, efout, rfout)) return 1;
            temp = temp->right;
        }
        temp = leaf->right;
        while (temp)
        {
            if (Oper(temp->left, hfout)) return 1;
            temp = temp->right;
        }
        hfout << "INVOKE ExitProcess, 0" << endl;
        hfout << "main ENDP" << endl;
    }
    else
    {
        //написать файл определение функции
        efout << leaf->dop << " PROC" << endl;
        int i=0;
        temp = leaf->left->left;
        while(temp)
        {
            i++;
            temp = temp->left;
            //что-то
        }
        temp = leaf->left->right->right;
        dfout << leaf->dop << " PROTO";
        while (temp)
        {
            if (DescrFun(temp->left, leaf->left->right->left, dfout)) return 1;
            temp = temp->right;
        }
        dfout << endl;
        if (BodyGen(leaf->right, efout))
        return 1;
        efout << "ret" << endl;
        efout << leaf->dop << " ENDP" << endl;
    }
    //написать
    return 0;
}

int DescrFun(node * leaf, node * val, ofstream &dfout)
{
    node *temp = leaf, *temp1 = val;
    int j = 1, i =0;
    if (leaf->type ==DESCRTP)
    while (temp)
    {
        temp->left->type = temp->token.lex_num;
        dfout << "," << endl << temp->left->dop << " : ";
        temp1=val;
        while (temp1)
        {
            if (!strcmp(temp1->dop, temp->left->dop))
            {
                dfout << "PTR " ;
                break;
            }
            temp1 = temp1->left;
        }
        switch(temp->token.lex_num)
        {
        case INTEGER:
            dfout <<  " SDWORD" ;
            break;
        case REAL:
            dfout <<  " REAL4" ;
            break;
        case BOOLEAN:
            dfout <<  " BYTE " ;
            break;
        }
        temp = temp->right;
        j++;
    }
    else if (leaf->type == DESCRAR)
    {
        temp = leaf -> left;
        dfout << "," << endl << temp->dop << " : ";
        temp->type = leaf->token.lex_num;
        temp1 =  temp =leaf->right;
        temp1=val;
        while (temp1)
        {
            if (!strcmp(temp1->dop, leaf -> left ->dop))
            {
                dfout << "PTR " ;
                break;
            }
            temp1 = temp1->left;
        }
        switch(leaf->token.lex_num)
            {
            case INTEGER:
                dfout <<  " SDWORD";
                break;
            case REAL:
                dfout <<  " REAL4 ";
                break;
            case BOOLEAN:
                dfout <<  " BYTE " ;
                break;
            }
    }
    return 0;
}

int Descr (node * leaf, ofstream &hfout)
{
    node *temp = leaf, *temp1 = 0;
    int i=1;
    if (leaf->type ==DESCRTP)
    while (temp)
    {
        temp->left->type = temp->token.lex_num;
        switch(temp->token.lex_num)
        {
        case INTEGER:
            hfout << temp->left->dop << " : SDWORD" << endl;
            break;
        case REAL:
            hfout << temp->left->dop << " : REAL4" << endl;
            break;
        case BOOLEAN:
            hfout << temp->left->dop << " : BYTE " << endl;
            break;
        }
        temp = temp->right;
    }
    else if (leaf->type == DESCRAR)
    {
        temp = leaf -> left;
        hfout << temp->dop ;
        temp->type = leaf->token.lex_num;
        temp1 =  temp =leaf->right;
        while (temp)
        {
            temp =temp->left;

                i*=10;
            temp1 = temp =temp1->right;
        }
        hfout << "[ " << i << " ] " ;
        switch(leaf->token.lex_num)
            {
            case INTEGER:
                hfout <<  " :SDWORD" <<endl;
                break;
            case REAL:
                hfout <<  " :REAL4 " << endl;
                break;
            case BOOLEAN:
                hfout <<  " :BYTE " << endl;
                break;
            }
    }
    return 0;
}

int DescrHead(node * leaf, ofstream &dfout,  ofstream &hfout, ofstream &efout, ofstream &rfout)
{
    node *temp = leaf, *temp1 = 0;
    int i=0;
    if (leaf->type ==DESCRTP)
    while (temp)
    {
        temp->left->type = temp->token.lex_num;
        switch(temp->token.lex_num)
        {
        case INTEGER:
            dfout << temp->left->dop << " SDWORD 0" << endl;
            break;
        case REAL:
            dfout << temp->left->dop << " REAL4 0.0" << endl;
            break;
        case BOOLEAN:
            dfout << temp->left->dop << " BYTE 0" << endl;
            break;
        }
        temp = temp->right;
    }
    else if (leaf->type == DESCRAR)
    {
        temp = leaf -> left;
        dfout << temp->dop ;
        temp->type = leaf->token.lex_num;
        temp1 =  temp =leaf->right;
        switch(leaf->token.lex_num)
            {
            case INTEGER:
                dfout <<  " SDWORD " ;
                break;
            case REAL:
                dfout <<  " REAL4 " ;
                break;
            case BOOLEAN:
                dfout <<  " BYTE " ;
                break;
            }
        while (temp)
        {
            i++;
            temp =temp->left;
            dfout << "size" << " DUP (";
            //написать код
            temp1 = temp =temp1->right;
        }
        dfout << "0";
        while (i--)
            dfout << ")";
        dfout << endl;
    }
    return 0;
}

int Oper(node * leaf, ofstream &dfout)
{
    switch (leaf->type)
    {
    case ASSOP:
        cout << "ASSOP " << leaf->dop << endl;
        assopg(leaf, dfout);
        break;

    case IF:
        cout << "If " << leaf->dop << endl;
        ifopg(leaf, dfout);
        break;

    case FORHEAD:
        cout << "For " << leaf->dop << endl;
        foropg(leaf, dfout);
        break;

    case ADDOP:
        cout << "ADDOP "  << endl;
        addopg(leaf, dfout);
        break;

    case BLOCK:
        cout << "BLOCK "  << endl;
        blockopg(leaf, dfout);
        break;

    case PROCOP:
        cout << "PROCOP "  << endl;
        procopg(leaf, dfout);
        break;

    case SQRT:
        cout << "SQRT " << leaf->dop << endl;
        sqrtopg(leaf, dfout);
        break;

    case READ:
        cout << "READ "  << endl;
        readopg(leaf, dfout);
        break;

    case WRITE:
        cout << "WRITE "  << endl;
        writeopg(leaf, dfout);
        break;
    default:
        return 1;
    }
    return 0;
}

int BodyGen(node * leaf, ofstream &dfout)
{
    node *temp;
    temp = leaf->left;
    dfout <<"LOCAL" << endl;
    while (temp)
    {
        if (Descr(temp->left, dfout)) return 1;
        temp = temp->right;
    }
    temp = leaf->right;
    while (temp)
    {
        if (Oper(temp->left, dfout)) return 1;
        temp = temp->right;
    }
    return 0;
}


int PFZ(char * expr, ofstream &dfout)
{


    return 0;
}

int assopg (node * leaf, ofstream &dfout)
{
    char buffer[256]= "";
    char *temp = buffer;
    char name[32]="";
    int i = 0;
    int lt=0;
    strcpy(buffer, leaf->dop);
    while (*temp != ':')
        temp++;
    *temp = 0;
    *(temp+1)=0;
    temp = buffer;
    while (*temp != ' ')
    {
        name[i]=*temp;
        i++;
        temp++;
        if (i==31) return 1;
    }
    name[i]=0;
    if (!TabLex.SearchId(name, &lt)) return 1;
    if (TabLex.GetIdAtr(lt) == 1)
    {
        temp++;
        PFZ(temp, dfout);
    }
    else if (TabLex.GetIdAtr(lt) == 2)
    {
        char tempbuf[256]="";
        temp++;
        if (*temp != '[') return 1;
        i=0;
        while (*temp != ']')
        {
            while(*temp != ',' && *temp != ']')
            {
                tempbuf[i]=*temp;
                i++;
                temp++;
            }
            tempbuf[i]=0;
            PFZ(tempbuf, dfout);
        }
    }
    return 0;
}

int ifopg (node * leaf, ofstream &dfout)
{
    char USL[10]="12312<312";
    //написать код
    PFZ(leaf->dop, dfout);
    dfout << ".IF " << USL << endl;
    if (Oper(leaf->left, dfout)) return 1;
    //написать код
    if (leaf->right)
    {
        dfout << ".ELSE " <<  endl;
        if (Oper(leaf->right, dfout)) return 1;
    //написать код
    }
    dfout << ".ENDIF " << endl;
    return 0;
}

int foropg (node * leaf, ofstream &dfout)
{
    node *temp = leaf;
    //написать код
     char USL[10]="12312<312";
     char forhead[100]="";
    //написать код
    PFZ(leaf->dop, dfout);
    dfout << ".WHILE " << USL << endl;
    if (Oper(leaf->right, dfout)) return 1;
    //написать код
    if (temp->left->type == WHILE)
    {
        //написать код лог выр
    }
    else if (temp->left->type == STEP)
    {
        temp = leaf->left->left;
        //написать код ариф выр
        temp = leaf->left->right;
        //написать код лог выр
        dfout << "add head , step" << endl;
    } else return 1;
    //написать код
    dfout << ".ENDW" << endl;
    return 0;
}

int addopg (node * leaf, ofstream &dfout)
{
    node *temp = leaf;
    temp = temp->right;
    while (temp)
    {
        if (Oper(temp->left, dfout)) return 1;
        temp = temp->right;
    }
    return 0;
}

int blockopg (node * leaf, ofstream &dfout )
{
    node *temp = leaf;
    temp = temp->left;
    dfout <<"LOCAL" << endl;
    while (temp)
    {
        if (Descr(temp->left, dfout)) return 1;
        temp = temp->right;
    }
    temp = temp->right;
    while (temp)
    {
        if (Oper(temp->left, dfout)) return 1;
        temp = temp->right;
    }
    return 0;
}

int procopg (node * leaf, ofstream &dfout)
{
    node *temp , *temp1;
    node *proc=0;
    int i=0,j=1;
    dfout << "INVOKE "  << leaf->dop;
    proc =  SinTree.SearchProc(leaf->dop);
    if (!proc) return 1;
    temp = proc ->left->left;
    while (temp)
    {
        i++;
        temp=temp->right;
    }
    temp = leaf->right;
    temp1 = proc ->left->right->left;
    while (temp)
    {
        dfout << ", ";
        if (temp1)
        if (temp1->type==j)
        {
            dfout << "ADDR " ;
            temp1 = temp1->left;
        }
        dfout <<temp->dop;
        temp = temp->right;
        j++;
    }
    dfout << endl;
    return 0;
}

int sqrtopg (node * leaf, ofstream &dfout)
{
    dfout << "FLD " << leaf->dop << endl;
    dfout << "FSQRT "  << endl;
    dfout << "FSTP " << leaf->dop << endl;
    return 0;
}

int readopg (node * leaf, ofstream &dfout)
{
    node *temp = leaf->right;
    while (temp)
    {
        //написать код
        temp= temp->right;
    }
    return 0;
}

int writeopg (node * leaf, ofstream &dfout)
{
    node *temp = leaf->right;
    while (temp)
    {
        //написать код
        temp= temp->right;
    }
    return 0;
}

