/*
    Name : main.c
    Goal : Programme de Facturation
    Author : Fernand Afanou
    Date : 2023/05/04
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_ARTICLES 50

// Structure d'un article
typedef struct Article
{
    int code;
    char libelle[50];
    float prix_unitaire;
} Article;

//Structre d'une ligne vente
typedef struct LigneVente
{
    Article article;
    int quantite;
    float montant;
} LigneVente;

// Prototypes des fonctions
void ajouter_article(Article *articles, int *nb_articles);
void afficher_liste(Article *articles, int nb_articles);
void modifier_article(Article *article, int nb_articles);
void info_article(Article *articles, int nb_articles);
void facturation(Article *articles, int nb_artilces);

int main()
{
    int choix, nb_articles;
    Article articles[MAX_ARTICLES];

    setlocale(LC_ALL, "");

    // Ouverture du fichier binaire
    FILE *fichier_articles = fopen("bdArticles.list", "rb");
    if (!fichier_articles)
    {
        printf("Impossible d'ouvrir le fichier bdArticles.list.\n");
        return 1;
    }

    // Lecture des articles
    nb_articles = fread(articles, sizeof(Article), MAX_ARTICLES, fichier_articles);
    fclose(fichier_articles);

    do
    {
        system("cls");
        printf("\n\tProgramme de Facturation : \n");
        printf("\n\tAffichage du Menu : \n");
        printf("1. Liste des articles\n");
        printf("2. Ajouter un article\n");
        printf("3. Modifier un article\n");
        printf("4. Afficher les informations\n");
        printf("5. Facturation\n");
        /*printf("8. Récupérer\n");*/
        printf("6. Quitter\n");

        printf("\nVotre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            afficher_liste(articles, nb_articles);
            break;
        case 2:
            ajouter_article(articles, &nb_articles);
            break;
        case 3:
            modifier_article(articles, nb_articles);
            break;
        case 4:
            info_article(articles, nb_articles);
            break;
        case 5:
            facturation(articles, nb_articles);
            break;
        case 6:
            printf("\nAu revoir !\n");
            break;
        default:
            printf("\nErreur : choix invalide\n");
        }
    }
    while(choix != 6);

    // Écriture dans le fichier binaire
    fichier_articles = fopen("bdArticles.list", "wb");
    fwrite(articles, sizeof(Article), nb_articles, fichier_articles);

    return 0;
}

// Fonction pour ajouter un nouvel article
void ajouter_article(Article *articles, int *nb_articles)
{
    int chk;

    system("cls");

    Article nouvel_article;
    printf("\n\tAjout d'un nouvel article : \n");

    do
    {
        chk = 0;

        printf("Code de l'article : ");
        scanf("%d", &nouvel_article.code);

        // Vérification si le code existe déjà
        for (int i = 0; i < *nb_articles; i++)
        {
            if (articles[i].code == nouvel_article.code)
            {
                chk++;
                break;
            }
        }

        if(chk != 0)
        {
            printf("Ce code d'article existe déjà.\n");
        }
    }
    while(chk != 0);


    printf("Libellé de l'article : ");
    scanf("%s", nouvel_article.libelle);
    printf("Prix unitaire de l'article : ");
    scanf("%f", &nouvel_article.prix_unitaire);

    // Ajout du nouvel article
    articles[*nb_articles] = nouvel_article;
    (*nb_articles)++;

    printf("L'article a été ajouté avec succès.\n");

    fflush(stdin);
    getchar();
}

// Fonction pour afficher la liste des articles
void afficher_liste(Article *articles, int nb_articles)
{
    fflush(stdin);
    system("cls");
    printf("\n\nListe des Articles : \n");
    printf("\n\n+*****************************************************+");
    printf("\n| %-10s | %-20s | %-15s |", "Code", "Libellé", "Prix unitaire");
    printf("\n+************+**********************+*****************+\n");

    for (int i = 0; i < nb_articles; i++)
    {
        printf("| %-10d | %-20s | %-15.2f |", articles[i].code, articles[i].libelle, articles[i].prix_unitaire);
        printf("\n+************+**********************+*****************+\n");
    }
    fflush(stdin);
    getchar();
}


//Fonction pour modifier un article
void modifier_article(Article *articles, int n)
{
    int code;

    system("cls");

    printf("\n\tModification d'un article : ");

    printf("\nEntrer le code de l'article : ");
    scanf("%i", &code);

    int trouve = 0;

    for(int i=0; i<n; i++)
    {
        if(articles[i].code == code)
        {
            printf("Article trouvé :\n");
            printf("\n\n+*****************************************************+");
            printf("\n| %-10s | %-20s | %-15s |", "Code", "Libellé", "Prix unitaire");
            printf("\n+************+**********************+*****************+\n");
            printf("| %-10d | %-20s | %-15.2f |", articles[i].code, articles[i].libelle, articles[i].prix_unitaire);
            printf("\n+************+**********************+*****************+\n");

            printf("\n\nVeuillez saisir les nouvelles informations :\n");
            printf("Libellé : ");
            scanf("%s", articles[i].libelle);
            printf("Prix unitaire : ");
            scanf("%f", &articles[i].prix_unitaire);

            FILE *fichier = fopen("bdArticles.list", "wb");
            fseek(fichier, -sizeof(Article), SEEK_CUR);
            fwrite(&articles[i], sizeof(Article), 1, fichier);
            fclose(fichier);

            trouve++;
            break;
        }
    }

    if (!trouve)
    {
        printf("Article non trouvé\n");
    }
}

void info_article(Article *articles, int n)
{
    int tmp_code, trouve=0;

    system("cls");
    printf("\n\tRechercher informations d'un article : \n");

    printf("\nEntrer le code l'article recherché : ");
    scanf("%i", &tmp_code);

    for(int i=0; i < n; i++)
    {
        if(articles[i].code == tmp_code)
        {
            system("cls");
            printf("Article trouvé :\n");
            printf("\n\n+*****************************************************+");
            printf("\n| %-10s | %-20s | %-15s |", "Code", "Libellé", "Prix unitaire");
            printf("\n+************+**********************+*****************+\n");
            printf("| %-10d | %-20s | %-15.2f |", articles[i].code, articles[i].libelle, articles[i].prix_unitaire);
            printf("\n+************+**********************+*****************+\n");

            trouve++;
            break;
        }
    }

    if(!trouve)
    {
        printf("\n\tArticle non trouvé\n");
    }

    fflush(stdin);
    getchar();
}


void facturation(Article *articles, int nb_articles)
{
    int chk, nb_vente, tmp_code, qte;
    float somme = 0;
    LigneVente listeArticles[10];
    Article article;

    system("cls");

    printf("\n\tFaire une facture\n ");

    printf("\n=> Combien d'articles à facturer ?  ");
    scanf("%i", &nb_vente);

    for(int cpt=0; cpt < nb_vente; cpt++)
    {
        chk = 0;
        do
        {
            printf("\n\t=> Code article : ");
            scanf("%i", &tmp_code);

            for(int i=0; i<nb_articles; i++)
            {
                if(articles[i].code == tmp_code)
                {
                    article.code = tmp_code;
                    strcpy(article.libelle, articles[i].libelle);
                    article.prix_unitaire = articles[i].prix_unitaire;

                    chk++;
                    break;
                }
            }
            if(chk == 0)
            {
                printf("\n\t** Article inexistant - redonnez le code ");
                getchar();
            }

        }
        while (chk == 0);

        printf("\n\t=> Quantité de %s au prix unitaire de %.2f : ", article.libelle, article.prix_unitaire);
        scanf("%i", &qte);
        listeArticles[cpt].article = article;
        listeArticles[cpt].quantite = qte;
        listeArticles[cpt].montant = article.prix_unitaire * qte;

        somme += article.prix_unitaire * qte;
    }

    //Affiche de la facture
    printf("\n\n\t\t *** FACTURE ***\n");

    printf("\n\n+***********************************************************************+");
    printf("\n| %-20s | %-10s | %-15s | %-15s |", "ARTICLE", "QUANTITE", "PRIX UNITAIRE", "MONTANT");
    printf("\n+**********************+************+*****************+*****************+\n");

    for(int cpt =0; cpt<nb_vente; cpt++)
    {
        printf("| %-20s | %-10d | %-15.2f | %-15.2f |", listeArticles[cpt].article.libelle, listeArticles[cpt].quantite, listeArticles[cpt].article.prix_unitaire, listeArticles[cpt].montant);
        printf("\n+**********************+************+*****************+*****************+\n");
    }
    printf("|               %-20s               %11.2f          |", "TOTAL", somme);
    printf("\n+***********************************************************************+\n");

    fflush(stdin);
    getchar();
}
