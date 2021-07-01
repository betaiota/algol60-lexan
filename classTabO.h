struct IDSTR//идентификатор
    {
        char name[32];
        int deep;
        IDSTR *next;
        int idtype;
        int vartype;
        //дополнительные атрибуты
    };

    struct CONSTSTR//константа
    {
        char name[32];
        //дополнительные атрибуты
    };



    class table
{
private:
    IDSTR **tabid; // указатель на таблицу идентификаторов
    CONSTSTR **tabconst; // указатель на таблицу числовых констант
    int idcout; // счётчик идентификаторов
    int concout; // счётчик числовых констант
    char tabword[22][16];
public:
    table();
    void* newdatatable(int flag);
    int InsertId(char *idin);
    int SearchId(char *idin, int *numtub);
    int InsertCont(char *conname);
    int SetIdAtr(int i, int flag);
    int GetIdAtr(int i);
    char* GetConst(int i);
    char* GetName(int i);
    int SearchConst(char *conname, int *numtub);
    int print();
    ~table();
} TabLex;
