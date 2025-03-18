#include <iostream>
#include <fstream>
#include <cstring>
#include <graphics.h>

using namespace std;

const char* filename = "cod.in";
ifstream fin(filename);

const int MAX=202;
int W=1000;
//int H=50;

int mx, my;
char t[MAX];
int n;
int top;
int s_in_out, s_left_right, s_up_down;

int STG, SUS, SUSinitial;

struct nod
{
    char info[MAX];
    int nrfii=0;
    int nrspatii = 0;
    int tip;
    int indice;
    nod *parinte = NULL;
    nod *fii[MAX];
}*a = new nod;

nod *aux[1001];

// 0 = atribuire/ citire
// 1 = daca
// 2 = atfel
// 3 = cat_timp
// 4 = pentru
// 5 = switch
// 6 = repeta
// 7 = pana_cand

struct propozitie
{
    char text[MAX];
    int nrspatii;
}cuv[1001];


int Spatii(char s[]);

void read_input();

void Initializare_nod();
void arbore();

void read_input()
{
    a = NULL;
    a = new nod;
    n=0;

    fin.open(filename);
    while(fin.getline(t, 202))
    {
        ++n;
        strcpy(cuv[n].text, t);
        cuv[n].nrspatii = Spatii(t);
    }
    fin.close();
}

int type (char cuv[MAX])                   //return tip nod
{
    if(strstr(cuv, "daca") != 0)      return 1;
    if(strstr(cuv, "altfel") != 0)    return 2;
    if(strstr(cuv, "cat_timp") != 0)  return 3;
    if(strstr(cuv, "pentru") != 0)    return 4;
    if(strstr(cuv, "switch") != 0)    return 5;
    if(strstr(cuv, "repeta") != 0)    return 6;
    if(strstr(cuv, "pana_cand") != 0) return 7;
    return 0;
}

int Spatii(char s[202])                // numarul de spatii
{
    int i = 0, nrspatii = 0;
    while(s[i] == ' ' && s[i] != 0)
        {
          nrspatii++;
          i++;
        }
    return nrspatii;
}

void Initializare_nod(nod *&p, char s[MAX], int spatii, int tip)
{
    strcpy(p->info, s);
    p->nrfii = 0;
    p->nrspatii = spatii;
    p->parinte = NULL;
    p->indice = 0;
    p->tip = tip;
}

void arbore(int n, nod *a)  //se creaza arborele cu ajutorul unei stive
{
    top = 0;
    aux[top] = a;
    for(int i = 1; i <= n; i++)
    {
        nod *p = new nod;
        Initializare_nod(p, cuv[i].text, cuv[i].nrspatii, type(cuv[i].text));
        while(top != 0 && aux[top]->nrspatii >= p->nrspatii)    //se tot scoate din stiva pana se ajunge la tatal corespunzator lui p
            top--;
        aux[top]->nrfii++;       //se actualizeaza nr de fii
        aux[top]->fii[aux[top]->nrfii] = p; //se adauga p ca fiu
        p->parinte = aux[top];       //se actualizeaza parintele lui p
        p->indice = aux[top]->nrfii; //p este ultimul fiu curent al parintelui
        aux[++top] = p; //se adauga in stiva
    }
}
