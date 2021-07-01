struct tok
{
    int token;
    int lex_num;
};

class node
{
public:
    int type;
    char dop[256];
    tok token;
    node *right, *left;
};

class tree
{
    public:
    node *TREE;
    tree();
    void del(node *);
    node * add_node(node **, int , int , int);
    int go(ofstream &, ofstream &, ofstream &, ofstream &);
    node * SearchProc(char *);
    ~tree();
}SinTree;

