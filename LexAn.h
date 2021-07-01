int LexAnal(const char *filename)
{
   int lex_num, token;
   int line=1;
   ofstream stout("strings.txt", ios::app);
   ofstream fout("tablex.obj", ios::binary);
   ifstream fin(filename);
   while (!fin.eof())
   {
        token=nextToken(fin,stout,lex_num, line);
        if (token==-1)
            if (lex_num)
                return 1;
            else
                break;
      // fout << token << " " << lex_num << endl;
      fout.write((char*)&token,sizeof(token));
      fout.write((char*)&lex_num,sizeof(lex_num));
   }
   fout.close();
   fin.close();
   stout.close();
   return 0;
}

int writeString(ifstream &fin, ofstream &stout)
{
    cout << endl << "String founded" << endl;
    char ch=0;
    while (fin.get(ch))
    {
        if(ch == '"') break;
        cout << ch;
        stout << ch;
    }
    stout << endl;
    cout << endl << endl;
    return 0;
}

int commentbreak(ifstream &fin)
{
    char c=0;
    while (fin.get(c)&&c!=';');
    return 0;
}

int nextToken(ifstream &fin, ofstream &stout, int &lex_num, int &line_num)
{
     char c;
     static int coutstring=0;
     char nametok[32]="";
     int state=0, i=0, num_tok;
     while (1)
      {
          switch(state)
          {
          case 0:
          {
           if (!fin.get(c)) c = EOF;
            if (isalpha(c))
            {
                nametok[0]=c;
                nametok[1]=0;
                i=1;
                state=1;
            }
            else if (isdigit(c))
            {
                nametok[0]=c;
                nametok[1]=0;
                i=1;
                state=2;
            }
           else if (c =='.')
            {
                nametok[0]=c;
                nametok[1]=0;
                i=1;
                state=3;
            }
             else if (c==':')
                state=6;
             else if (c=='>')
                state=8;
            else if (c=='<')
                state=10;
            else if (c=='=')
                state=15;
            else if (c==',')
                state=13;
            else if (c=='"')
                state=14;
            else if (c==' '||c=='\t'||c=='\n')
               {
                 state=12;
                 if (c=='\n')
                    line_num++;
               }
            else if (c=='+')
                state=16;
            else if (c=='-')
                state=17;
            else if (c =='/')
                state=18;
            else if (c =='*')
                state=19;
            else if (c =='(')
                state=20;
            else if (c ==')')
                state=21;
            else if (c ==']')
                state=22;
            else if (c =='[')
                state=23;
            else if (c ==';')
                state=24;
            else if (c ==EOF)
                state=47;
            else
                state=48;
            }
          break;
          case 1:
          {
             if (!fin.get(c)) c = EOF;
             if (isalpha(c)||isdigit(c))
             {
                if (i<31)
                {
                    nametok[i++]=c;
                    nametok[i]=0;
                }
             } else
             {
                 fin.putback(c);
                 state=25;
             }
             }
          break;
          case 2:
          {
             if (!fin.get(c)) c = EOF;
             if (isdigit(c))
             {
                if (i<31){
                nametok[i++]=c;
                nametok[i]=0;
                }
             } else if (c=='.')
             {
                if (i<31){
                    nametok[i++]=c;
                    nametok[i]=0;
                }
                state=4;
             }
             else
             {
                 fin.putback(c);
                 state = 26;
             }
             }
          break;
          case 3:
          {
             if (!fin.get(c)) c = EOF;
             if (isdigit(c))
             {
                if (i<31){
                    nametok[i++]=c;
                    nametok[i]=0;
                }
                state = 5;
             }
             else
             {
                 fin.putback(c);
                 state=27;
             }
             }
          break;
          case 4:
          {
             if (!fin.get(c)) c = EOF;
             if (isdigit(c))
             {
                if (i<31){
                nametok[i++]=c;
                nametok[i]=0;
                }
                state = 5;
             }
             else
             {
                 fin.putback(c);
                 state = 48;
             }
             }
          break;
          case 5:
          {
             if (!fin.get(c)) c = EOF;
             if (isdigit(c))
             {
                if (i<31){
                nametok[i++]=c;
                nametok[i]=0;
                }
             }
             else
             {
                 fin.putback(c);
                 state = 26;
             }
             }
          break;
          case 6:
          {
              if (!fin.get(c)) c = EOF;
              if (c=='=')
              {
                  state=7;
              }
              else
              {
                  fin.putback(c);
                  state=28;
              }
          }
          break;
          case 7:
          {
                state = 29;
          }
          break;
          case 8:
          {
              if (!fin.get(c)) c = EOF;
              if (c=='=')
              {
                  state=9;
              }
              else
              {
                  fin.putback(c);
                  state=30;
              }
          }
          break;
          case 9:
          {
                state = 31;
          }
          break;
          case 10:
          {
              if (!fin.get(c)) c = EOF;
              if (c=='=')
              {
                  state=11;
              }
              else
              {
                  fin.putback(c);
                  state=32;
              }
          }
          break;
          case 11:
          {
                state = 33;
          }
          break;
          case 12:
          {
                if (!fin.get(c)) c = EOF;
                if (c!=' '&&c!='\t'&&c!='\n')
                {
                    fin.putback(c);
                    state = 34;
                }
                if (c=='\n')
                    line_num++;
          }
          break;
          case 14:
          {
                writeString(fin, stout);
                coutstring++;
                lex_num=coutstring;
                state+=22;
          }
          break;
          case 13:case 15:case 16:case 17:case 18:case 19:case 20:case 21:case 22:case 23:case 24:
          {
                state+=22;
          }
          break;
          case 25:
          {
              switch (TabLex.SearchId(nametok, &num_tok))
                 {
                 case -1:
                    lex_num=TabLex.InsertId(nametok);
                    cout <<nametok << "  " <<  TABID << "  " << lex_num << endl;
                    return TABID;
                 case 0:
                    lex_num=num_tok;
                    cout <<nametok << "  " <<  TABID << "  " << lex_num << endl;
                    return TABID;
                 case 1:
                     if (num_tok!=19)
                     {
                        lex_num=num_tok;
                        cout <<nametok << "  " <<  TABWORD << "  " << lex_num << endl;
                        return TABWORD;
                     }
                     else
                     {
                        i=0;
                        nametok[0]=0;
                        commentbreak(fin);
                        state = 0;
                        break;
                     }
                 }

          }
          break;
          case 26:
          {
              switch (TabLex.SearchConst(nametok, &num_tok))
              {
              case -1:
                    lex_num=TabLex.InsertCont(nametok);
                    cout << nametok << "  " <<  TABCONST << "  " << lex_num << endl;
                    return TABCONST;
              case 0:
                    lex_num=num_tok;
                    cout << nametok << "  " <<  TABCONST << "  " << lex_num << endl;
                    return TABCONST;
              }
          }
          break;
          case 27:
          {
              lex_num=0;
              cout << '.' << "  " <<  '.' << "  " << lex_num << endl;
              return '.';
          }
          break;
          case 28:
          {
              lex_num=0;
              cout << ':' << "  " <<  ':' << "  " << lex_num << endl;
              return ':';
          }
          break;
          case 29:
          {
              lex_num=0;
              cout << ":=" << "  " <<  RAV << "  " << lex_num <<  endl;
              return RAV;
          }
          break;
          case 30:
          {
              lex_num=0;
              cout << '>' <<  "  " <<  '>' << "  " << lex_num << endl;
              return '>';
          }
          break;
          case 31:
          {
              lex_num=0;
              cout << ">=" <<  "  " <<  LR << "  " << lex_num << endl;
              return LR;
          }
          break;
          case 32:
          {
              lex_num=0;
              cout << '<' <<  "  " <<  '<' << "  " << lex_num << endl;
              return '<';
          }
          break;
          case 33:
          {
              lex_num=0;
              cout << "<=" <<  "  " <<  SR << "  " << lex_num << endl;
              return SR;
          }
          break;
          case 34:
          {
              state=0;
          }
          break;
          case 35:case 36:case 37:case 38:case 39:case 40:case 41:case 42:case 43:case 44:case 45:case 46:
          {
              lex_num=0;
              cout << c << "  " << c << "  " << lex_num << endl;
              return c;
          }
          break;
          case 47:
              lex_num=0;
              return -1;
          case 48:
              lex_num=1;
              cout << "lex error in " << line_num << " charecter " <<c;
              return -1;
      }
    }
}
