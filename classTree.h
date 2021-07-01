    tree::tree()
    {
        TREE=NULL;
    }

    void tree::del(node *pn)
    {
        if (pn->left)
            del(pn->left);
        if (pn->right)
            del(pn->right);
        delete pn;
    }

    node * tree::add_node(node **temp, int type, int token=0, int lex_num=0)
    {
        *temp = new node;
        (*temp)->token.lex_num=lex_num;
        (*temp)->token.token=token;
        (*temp)->type = type;
        (*temp)->dop[0] = 0;
        (*temp)->left = NULL;
        (*temp)->right = NULL;
        return *temp;
    }

    tree::~tree()
    {
        if (TREE)
        del(TREE);
    }

    node * tree::SearchProc(char *namefun)
    {
        node *proc = TREE->left;
        while (proc)
        {
            if (!strcmp(namefun, proc->left->dop)) return proc->left;
            proc = proc -> right;
        }
        return 0;
    }

    int tree::go(ofstream &dfout,  ofstream &hfout, ofstream &efout, ofstream &rfout)
    {
        node *temp = TREE->left;
        while  (temp)
        {
            FunGen(temp->left,0, dfout, hfout, efout ,rfout);
            temp = temp->right;
        }
        FunGen(TREE->right,1, dfout, hfout, efout ,rfout);
        efout << "END main" << endl;
        return 0;
    }
