    table::table()
    {
        idcout = concout = 0;
        tabid = new IDSTR* [10];
        tabconst = new CONSTSTR* [10];
        strcpy(tabword[0],"integer");
        strcpy(tabword[1],"boolean");
        strcpy(tabword[2],"real");
        strcpy(tabword[3],"array");
        strcpy(tabword[4],"begin");
        strcpy(tabword[5],"end");
        strcpy(tabword[6],"if");
        strcpy(tabword[7],"else");
        strcpy(tabword[8],"then");
        strcpy(tabword[9],"false");
        strcpy(tabword[10],"true");
        strcpy(tabword[11],"procedure");
        strcpy(tabword[12],"for");
        strcpy(tabword[13],"step");
        strcpy(tabword[14],"until");
        strcpy(tabword[15],"do");
        strcpy(tabword[16],"while");
        strcpy(tabword[17],"read");
        strcpy(tabword[18],"write");
        strcpy(tabword[19],"comment");
        strcpy(tabword[20],"value");
        strcpy(tabword[21],"sqrt");

    }
    void* table::newdatatable(int flag)
    {
        int i;
        void *temp=0;
        void **tempgl=0;
        if (flag)
        {
            if (idcout%10==9)
                {
                    tempgl = (void**)new IDSTR* [idcout+11];
                    for (i=0;i<idcout;i++)
                        tempgl[i]=(void*)tabid[i];
                    delete []tabid;
                    tabid=(IDSTR**)tempgl;
                }
            tabid[idcout] = new IDSTR;
        }
        else
        {
            if (concout%10==9)
                {
                    tempgl = (void**)new CONSTSTR* [concout+11];
                    for (i=0;i<concout;i++)
                        tempgl[i]=(void*)tabconst[i];
                    delete []tabconst;
                    tabconst=(CONSTSTR**)tempgl;
                }
            tabconst[concout] = new CONSTSTR;
        }
        return temp;
    }

    int table::InsertId(char *idin)
    {
        newdatatable(1);
        strcpy(tabid[idcout]->name,idin);
        tabid[idcout]->deep=0;
        tabid[idcout]->next=0;
        tabid[idcout]->idtype=0;
        tabid[idcout]->vartype=0;
        return idcout++;
    }

    int table::SearchId(char *idin, int *numtub)
    {
       int i;
       for (i=0;i<22;i++){
            if (!strcmp (tabword[i],idin))
            {
                *numtub = i;
                return 1;
            }}
       i=0;
       while (i<idcout)
       {
            if (!strcmp (tabid[i]->name,idin))
                {
                    *numtub = i;
                    return 0;
                }
            i++;
        }
        return -1;
    }

    int table::InsertCont(char *conname)
    {
        newdatatable(0);
        strcpy(tabconst[concout]->name,conname);
        return concout++;
    }

    int table::SetIdAtr(int i, int flag)
    {
         tabid[i]->idtype=flag;
         return 0;
    }

    int table::GetIdAtr(int i)
    {
         return  tabid[i]->idtype;
    }

    char* table::GetConst(int i)
    {
          return tabconst[i]->name;
    }

    char* table::GetName(int i)
    {
          return tabid[i]->name;
    }

    int table::SearchConst(char *conname, int *numtub)
    {
       int i=0;
        while (i<concout)
        {
            if (!strcmp (tabconst[i]->name,conname))
                {
                    *numtub = i;
                    return 0;
                }
            i++;
        }
        return -1;
    }

    int table::print()
    {
         for (int i=0;i<idcout;i++)
        {
            cout << tabid[i]->name << endl;
        }
        return 0;
    }

    table::~table()
    {
        int i;
        for (i=0;i<idcout;i++)
          delete [] tabid[i];
        for (i=0;i<concout;i++)
          delete [] tabconst[i];
        delete [] tabid;
        delete [] tabconst;
    }

