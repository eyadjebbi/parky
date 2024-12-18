#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
#include <stdio.h>
#include <gtk/gtk.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

enum {
ID, 
Nom_parking,
Capacite,
Nb_places_disponibles, 
Adresse,
Columns
};
enum {
IDagent, 
Nom_agent,
Prenom_agent,
Jour, 
Mois , 
Annee,
ID_parking,
COLUMNS
};

typedef struct {
	char jour[10]; 
	char mois[10]; 
	char annee[10]; 
}date ; 
 
typedef struct{
	char idagent [50]; 
	char nomagent[50]; 
	char prenomagent[50];
	date date;
	char idparking[50];
        
}agentparking;

typedef struct{
	char id[50];
	char nomparking[50]; 
	char  capacite[50];
	char nbplacesdispo[50];
	char adresse[100]; 
}parking;

int ajouterparking( parking p );
int modifierparking(char id[10], parking nouv);
int supprimerparking( char id[10] );
void afficherparking_(GtkWidget  *liste);
int ajouteragent( agentparking ap );
int affecteragent( char idparking[50], char idagent[50]) ;
void afficheragent(GtkWidget *liste);


enum{
LOGIN,
MDP,
ID_C,
NOM,
PRENOM,
TEL,
COLUMNSS};
enum{
IDRESERVATION,
MOIS,
JOUR,
ANNEE,
LIBELLE,
COUT,
COLUMNNS};
typedef struct {
char login[50];
char mdp[50];
char nom[50];
char prenom[50];
char id[50];
char tel[50];

} Citoyen;
typedef struct {
	int jour; 
	int mois; 
	int annee; 
}datee ; 
 

typedef struct{
char idParking[50];
int placesDisponibles;
char nomParking[50];
}Parking;
typedef struct{
char id_park[50];
char id[10];
char libelle[50];
char cout[50];
}service;
typedef struct{
char idReservation[50];
char idClient[50];
datee date;
Parking parking;
service service ;
}Reservations;
typedef struct{
char login[50];
char mdp[50];
}connexion;
int verifier_connexion( char login[10], char mdp[10] );
int verif_conx_admin( char login[50],char mdp[50] );

int ajouterProfil(char *filename, Citoyen citoyen);
int modifierProfil(char *filename, char*id, Citoyen temp);
int supprimerProfil(char *filename, char *id);
float calculerFactureMensuelle(char *id, int mois, int annee);
int chercherprofil(char *filename, char id[10]);
int chercherreservation(char *filename, char id[10]);

enum{
	ERECID ,
	EJOUR ,
	EMOIS ,
	EANNEE, 
	ETEL,
	EIDPARK,
	EAVIS,
	EDESC,
	COLUMNS1
};
enum{

	EIDPARKT,
	EAVIST,
	ECOLUMNS
};



typedef struct
{
    int jour;
    int mois;
    int annee;

}dates;
typedef struct
{
    int recid;
    dates date; 
    char tel[9] ;
    char idpark[5];
    char avis [2];
    char desc[300];
}rec;
typedef struct {
    char idpark[20];
    int totalAvis;
    int countAvis;
    float moyenneAvis;
} ParkingInfo;


int ajouter(char *,rec ,int choix[],char ch[]);
int modifier( char *, char*,int, rec,char cha[] ,char ch[],int choix2[]);
int supprimer(char *, char* ,int,char ch[]);
rec chercher(char *, char*,int,char ch[]);
void afficherListeTrieeParAvis( char *filename);
void add( int ,char tel[]);
int pull( int ,char tel[]);
void supprimer_tre(rec,char ch[]);
void afficher_rec (GtkWidget *liste,char ch[]);
void supprimer_tretree(rec);
void afficher_rectree (GtkWidget *liste);



typedef struct
	{
	char id_park[10];
	char id[10];
	char libelle[50];
	char cout [4];
	}serviceh;


typedef struct {
	char id_reservation[10];
	char id_client[10];
	char id_parking[10];
	char id_service[10];
	} reservation;

enum {
    ID_PARK_COLUMN,
    ID_SERVICE_COLUMN,
    LIBELLE_COLUMN,
    COUT_COLUMN,
    COLUMNShoussem
};



int ajouter_services( serviceh s1 );

int modifier_services(serviceh s1, char id[10], char id_park[10]);

int supprimer_services(char id[] , char id_park[]);

serviceh chercher_services(char id[]);

void affecter_service(char id_service[10], char id_reservation[10]);

void afficher_ser(GtkWidget *liste);

#endif // POINT_H_INCLUDED
