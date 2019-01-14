
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <limits.h> 

typedef int bool;
#define true 1
#define false 0


typedef struct node
{
int info;
struct node * fils;
struct node * frere;
}tree;

typedef struct sNode 
{ 
  tree *t; 
  struct sNode *next; 
}pile; 

/******************************************************************************
                            Fonctions de bases sur pile pour arbre 
*******************************************************************************/

/* initialiser la pile */ 

void Init_stack(pile **p)
{
    (*p)=NULL;
}

/* vérifier si la pile est vide */ 

bool PisEmpty (pile *p)
{
    if (p==NULL) return (true); else return (false);
}



/* Fonction qui Empile un élement dans la pile */

void push(pile ** Sommet, tree *t) 
{ 
  /* allocate tNode */
  pile * new_tNode = 
            (pile *) malloc(sizeof(pile)); 
  
  if(new_tNode == NULL) 
  { 
     printf("Stack Overflow \n"); 
     getchar(); 
     exit(0); 
  }   
 /* mettre l'@ de l'arbre  */
  new_tNode->t  = t; 
  
  /* faire le chainage dans la pile  */
  new_tNode->next = (*Sommet);    
  
  /* changer le sommet  */
  (*Sommet)    = new_tNode; 
} 

/* Fonction qui depiler une élement de la pile*/
tree *pop(pile ** Sommet) 
{ 
  tree *res; 
  pile *top; 
  
  /*si la pile est vide afficher une erreur */
  if(PisEmpty(*Sommet)) 
  { 
     printf("Stack Underflow \n"); 
     getchar(); 
     exit(0); 
  } 
  else
  { 
     top = *Sommet; 
     res = (*Sommet)->t; 
     *Sommet = top->next; 
     free(top); 
     return res; 
  } 
} 
 
/******************************************************************************
                            Fonctions de bases sur arbre
*******************************************************************************/


bool IsEmpty( tree *T)
{
   if (T==NULL) return (true);
   return (false);
}


tree * fils( tree *T)
{
if ( IsEmpty(T) )
return NULL;
else
return T->fils;
}

tree * frere( tree *T)
{
if ( IsEmpty(T) )
return NULL;
else
return T->frere;
}

bool IsLeave(tree *T)
{
if (IsEmpty(T))
return false;
else if (IsEmpty(fils(T)))
return true;
else
return false;
}


bool IsInternalNode(tree *T)
{
return (! IsLeave(T) );
}





/******************************************************************************
                            Fonctions serie du TD.
*******************************************************************************/

unsigned NbNode(tree *T)
{
if( IsEmpty(T) )
return 0;
else
return 1 + NbNode(fils(T)) + NbNode(frere(T));
}

unsigned NbLeaves( tree *T)
{
if( IsEmpty(T) )
return 0;
else if ( IsLeave(T) )
return 1+NbLeaves(frere(T));
else
return (NbLeaves(fils(T)) + NbLeaves(frere(T)));
}

unsigned Somme (tree *T)
{
if ( IsEmpty(T) )
return 0;
else
return T->info +  Somme(fils(T) ) + Somme(frere(T) ) ;
}

tree * Rand_Tree()
{   tree *T, *AB, *P;
    int i,k;
   // time_t t;
    
    T=(tree *)malloc (sizeof(tree));
    T->info =1;
    T->frere =NULL;
    T->fils = (tree *) malloc (sizeof(tree));
    T->fils->info =2;AB =T->fils;
    for (i=0;i<3;i++) {AB->frere=(tree *) malloc (sizeof(tree));
                       AB=AB->frere;
                       AB->info =3+i;
                       }
    AB->frere=NULL;
    AB=T->fils;
    P=AB; k=6;
    while (AB!=NULL)
    {
    AB->fils = (tree *) malloc (sizeof(tree));
    AB->fils->info =k;P =AB->fils;k++;
    for (i=0;i<2;i++) {P->frere=(tree *) malloc (sizeof(tree));
                       P=P->frere;
                       P->fils = NULL;k=k+i;
                       P->info =k;
                       }
                       P->frere=NULL;
     AB=AB->frere;k++;
    }
    return (T);
}

void afficher (tree *T)
{
    if (!IsEmpty (T)) { printf ("%d  ", T->info );
                        afficher(T->fils);
                        afficher(T->frere);
                        
                              }
}






unsigned Taille_iter (tree *T)
{
  unsigned var=0;
  pile *p;
  tree *ABR;
  
  ABR =T;
  
  Init_stack(&p);
  push (&p, ABR); 
  
  while  (!PisEmpty(p))
  {
      ABR = pop (&p);
      var ++;
      if (!IsEmpty(ABR->fils)) push (&p, ABR->fils); 
      if (!IsEmpty(ABR->frere)) push (&p, ABR->frere); 
      
  }
  
  return (var);
}







int main()
{
    
    tree *T, *R;
    int option;
    bool check;
    int k;
    
    T= Rand_Tree();
    afficher (T);
clrscr();
do
{
printf("\n\n *****MENU PRINCIPALE *****");
printf("\n 1: Trouver la taille d'un arbre N-aires(récursive)");
printf("\n 2: Trouver le nombre de feuilles d’un arbre N-aires(récursive)");
printf("\n 3: Calculer la somme de tous les noeuds d’un arbre N-aires(récursive)");
printf("\n 4: Trouver la taille d'un arbre N-aires(itérative)");
printf("\n 14: Sortir");
printf("\n\n Entez votre choix : ");
scanf("%d", &option);
switch(option)
{
case 1: printf("La taille de l'arbre est de : %u \n",NbNode(T));
break;
case 2: printf("Le nombre de feuilles de l'arbre est de : %u \n",NbLeaves(T));
break;
case 3: printf("Le Somme d'élement de l'arbre est de : %u \n",Somme(T));
break;
case 4:printf("La taille de l'arbre est de : %u \n",Taille_iter(T));
break;
}
}while(option != 14);
getch();
    return 0;
}
