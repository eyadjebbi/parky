#include "parking.h"
#include <string.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <config.h>
#define MAX_PARKINGS 1000




int ajouterparking( parking p )
{
    
    FILE * f=fopen("parking.txt", "a");
    if(f!=NULL)
    {
        fprintf(f,"%s %s %s %s %s \n",p.id,p.nomparking,p.capacite,p.nbplacesdispo,p.adresse);
        fclose(f);
        return 1;
    }
    else return 0;
}
int modifierparking(  char id[10], parking nouv )
{
    int tr=0;
    parking p ; 
    FILE * f=fopen("parking.txt", "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %s %s %s %s \n",p.id,p.nomparking,p.capacite,p.nbplacesdispo,p.adresse)!=EOF)
        {
          if (strcmp(p.id, id) == 0)

            {
                fprintf(f2,"%s %s %s %s %s \n",nouv.id,nouv.nomparking,nouv.capacite,nouv.nbplacesdispo,nouv.adresse);
                tr=1;
            }
            else
                fprintf(f2,"%s %s %s %s %s \n",p.id,p.nomparking,p.capacite,p.nbplacesdispo,p.adresse);

        }
    }
    fclose(f);
    fclose(f2);
    remove("parking.txt");
    rename("nouv.txt", "parking.txt");
    return tr;

}
int supprimerparking( char id[10])
{
    int tr=0;
    parking p;
    FILE * f=fopen("parking.txt", "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%s %s %s %s %s \n",p.id,p.nomparking,p.capacite,p.nbplacesdispo,p.adresse)!=EOF)
        {
            if (strcmp(p.id, id) == 0)

                tr=1;
            else
                fprintf(f2,"%s %s %s %s %s \n",p.id,p.nomparking,p.capacite,p.nbplacesdispo,p.adresse);
        }
    }
    fclose(f);
    fclose(f2);
    remove("parking.txt");
    rename("nouv.txt", "parking.txt");
    return tr;
}
void afficherparking_(GtkWidget *liste){
	GtkCellRenderer *renderer; 
        GtkTreeViewColumn * column ; 
	GtkTreeIter iter ; 

	GtkListStore *store ; 

        char id[50];
	char nomparking[50]; 
	char  capacite[50];
	char nbplacesdispo[50];
	char adresse[100];

	store=NULL ; 

         FILE * f;
	  
         store=GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste))); 
 	 if (store==NULL)
	{ 
	renderer=gtk_cell_renderer_text_new(); 
	column=gtk_tree_view_column_new_with_attributes("id " , renderer , "text" ,ID,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
 
        renderer=gtk_cell_renderer_text_new(); 
	column=gtk_tree_view_column_new_with_attributes("nomparking " , renderer , "text" , Nom_parking ,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

 	renderer=gtk_cell_renderer_text_new(); 
	column=gtk_tree_view_column_new_with_attributes("capacite" , renderer , "text" ,Capacite,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new(); 
	column=gtk_tree_view_column_new_with_attributes("nbplacesdispo " , renderer , "text" ,Nb_places_disponibles,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new(); 
	column=gtk_tree_view_column_new_with_attributes("adresse" , renderer , "text" ,Adresse,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	store=gtk_list_store_new(Columns , G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	
	f=fopen("parking.txt","r"); 
  	if (f=NULL)
	{
		return; 
	}
	else 
	{ 
		f=fopen("parking.txt","a+") ; 
	
	while(fscanf(f,"%s %s %s %s %s \n",id,nomparking,capacite,nbplacesdispo,adresse)!=EOF){
	gtk_list_store_append(store,&iter); 
	gtk_list_store_set(store,&iter,ID,id, Nom_parking,nomparking ,Capacite ,capacite ,Nb_places_disponibles , nbplacesdispo, Adresse,adresse ,-1 ) ;
	} 
	  fclose(f); 
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	g_object_unref(store);
        }
 }
}

int ajouteragent( agentparking ap) {
    FILE *f = fopen("agent.txt", "a");
    if (f != NULL) {
        if (strlen(ap.idparking) == 0) {
           fprintf(f, "%s %s %s %s %s %s NULL\n",
                ap.idagent, ap.nomagent, ap.prenomagent,
                ap.date.jour, ap.date.mois, ap.date.annee);
    } else {
        fprintf(f, "%s %s %s %s %s %s %s\n",
                ap.idagent, ap.nomagent, ap.prenomagent,
                ap.date.jour, ap.date.mois, ap.date.annee,
                ap.idparking);
    }
}

    fclose(f);
    return 1;
}


int affecteragent( char idagent[50], char idparking[50]) {
    FILE *f = fopen("agent.txt", "r");
 
    FILE *temp = fopen("temp.txt", "w");
   

    agentparking ap;
    int found = 0;
    if (f!= NULL){
    while (fscanf(f, "%s %s %s %s %s %s %s\n",
                  ap.idagent, ap.nomagent, ap.prenomagent,
                  ap.date.jour, ap.date.mois, ap.date.annee,
                  ap.idparking) != EOF) {
		
        if (strcmp(ap.idagent, idagent) == 0 ) {
            strcpy(ap.idparking, idparking);
		printf("idpark %s\n",ap.idparking);
            found = 1;
        }
        fprintf(temp, "%s %s %s %s %s %s %s\n", ap.idagent, ap.nomagent, ap.prenomagent,
                ap.date.jour, ap.date.mois, ap.date.annee, ap.idparking);
    }}

    fclose(f);
    fclose(temp);

    if (found==1){
	 remove("agent.txt");
         rename("temp.txt", "agent.txt");
        return 1;
    } else {
        printf("Agent non trouvé ou déjà affecté.\n");
        remove("temp.txt");
        return 0;
    }
}




void afficheragent(GtkWidget *liste) {
        GtkCellRenderer *renderer; 
        GtkTreeViewColumn * column ; 
	GtkTreeIter iter ; 

	GtkListStore *store ; 

        char idagent[50];
	char nomagent[50]; 
	char  prenomagent[50];
	char date[50];
	char idparking[100];
	char jour [10]; 
	char mois[10]; 
	char annee[10]; 
	

	store=NULL ; 

         FILE * f;
	  
         store=GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste))); 
 	 if (store==NULL)
	{ 
	renderer=gtk_cell_renderer_text_new(); 
	column=gtk_tree_view_column_new_with_attributes("idagent " , renderer , "text" ,IDagent,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
 
        renderer=gtk_cell_renderer_text_new(); 
	column=gtk_tree_view_column_new_with_attributes("nomagent " , renderer , "text" , Nom_agent ,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

 	renderer=gtk_cell_renderer_text_new(); 
	column=gtk_tree_view_column_new_with_attributes("prenomagent" , renderer , "text" ,Prenom_agent,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new(); 
	column=gtk_tree_view_column_new_with_attributes("jour  " , renderer , "text" ,Jour,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new(); 
	column=gtk_tree_view_column_new_with_attributes("mois  " , renderer , "text" ,Mois,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new(); 
	column=gtk_tree_view_column_new_with_attributes("annee  " , renderer , "text" ,Annee,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	renderer=gtk_cell_renderer_text_new(); 
	column=gtk_tree_view_column_new_with_attributes("idparking" , renderer , "text" ,ID_parking,NULL); 
	gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	store=gtk_list_store_new(COLUMNS , G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING);
	
	f=fopen("agent.txt","r"); 
  	if (f=NULL)
	{
		return; 
	}
	else 
	{ 
		f=fopen("agent.txt","a+") ; 
	
	while(fscanf(f,"%s %s %s %s %s %s %s \n",idagent,nomagent,prenomagent,jour,mois,annee,idparking)!=EOF){
	gtk_list_store_append(store,&iter); 
	gtk_list_store_set(store,&iter,IDagent ,idagent, Nom_agent,nomagent ,Prenom_agent ,prenomagent ,Jour , jour , Mois , mois ,Annee,annee ,ID_parking,idparking , -1 );}                       
	  fclose(f); 
	gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
	g_object_unref(store);
        }
}}
int verif_conx_admin( char login[50],char mdp[50] ){
	int verifier=0;
	connexion cnx;
	FILE* f;

	f=fopen("comptes.txt", "r");

	if(f!=NULL)
		{
	 while (fscanf(f, "%s %s\n",
		cnx.login,cnx.mdp) != EOF) 
				{        
				if(strcmp(cnx.login,login)==0 && strcmp(cnx.mdp,mdp)==0 )
        				{
					verifier= 1;
					
					}
				else{verifier=-1;}
				}
		}

	fclose(f);

	return verifier;
	}

///////////////////////////////////////////////////////////////
int ajouterProfil(char *filename,Citoyen citoyen) {
    	FILE *f = fopen("citoyen.txt", "a");
 	
    	if (f != NULL) {

        		fprintf(f, "%s %s %s %s %s %s\n",citoyen.login,citoyen.mdp, citoyen.nom, citoyen.prenom,citoyen.id, citoyen.tel);
			fclose(f);
    			return 1;} 	
			
	
        return 0 ; }
   
int modifierProfil(char *filename, char *id, Citoyen temp) {
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    int trouv = 0;
    Citoyen citoyen;

    if (f == NULL || f2 == NULL) {
        g_warning("Erreur d'ouverture de fichier");
        return 0;
    }

    while (fscanf(f, "%s %s %s %s %s %s \n", citoyen.login, citoyen.mdp, citoyen.nom, citoyen.prenom, citoyen.id, citoyen.tel) != EOF) {
        if (strcmp(citoyen.id, id) == 0) {
            fprintf(f2, "%s %s %s %s %s %s \n", temp.login, temp.mdp, temp.nom, temp.prenom, temp.id, temp.tel);
            trouv = 1;
        } else {
            fprintf(f2, "%s %s %s %s %s %s \n", citoyen.login, citoyen.mdp, citoyen.nom, citoyen.prenom, citoyen.id, citoyen.tel);
        }
    }

    fclose(f);
    fclose(f2);

    if (trouv) {
        remove(filename);
        rename("nouv.txt", filename);
    } else {
        remove("nouv.txt");
    }

    return trouv;
}
int supprimerProfil(char *filename, char *id) {
    	FILE *f = fopen(filename, "r");
    	FILE *f2 = fopen("nouv.txt", "w");
    	int trouv = 0;
    	Citoyen citoyen;

    	if (f != NULL && f2 != NULL){
		while (fscanf(f, "%s %s %s %s %s %s\n",
citoyen.login,citoyen.mdp, citoyen.nom, citoyen.prenom,citoyen.id, citoyen.tel) != EOF) {

            		if (strcmp(citoyen.id, id)==0) {
               			trouv = 1;}
            		else {
            fprintf(f2,  "%s %s %s %s %s %s\n",
citoyen.login,citoyen.mdp, citoyen.nom, citoyen.prenom,citoyen.id, citoyen.tel);}
            }}

    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return trouv;
}

int chercherprofil(char *filename, char *id){
	FILE *f = fopen("citoyen.txt", "r");
	Citoyen existing;
    	int trouv = -1;
    	if (f != NULL) {
        	while (fscanf(f, "%s %s %s %s %s %s\n",existing.login,existing.mdp,existing.nom, existing.prenom, existing.id,existing.tel) != EOF) {
            		if (strcmp(existing.id,id) == 0) {
				trouv=1;
			}
		}
	}
	fclose(f);
	return trouv;
		}
float calculerFactureMensuelle(char *id, int mois, int annee) {
    FILE *f = fopen("reservations.txt", "r");

    if (f == NULL) {
        perror("Erreur d'ouverture du fichier");
        return -1.0; 
    }

    float total = 0.0;
    Reservations reservation;

    while (fscanf(f, "%s %s %d %d %d %s %d %s %s %s %s %s \n", 
                  reservation.idReservation, 
                  reservation.idClient, 
                  &reservation.date.jour, 
                  &reservation.date.mois, 
                  &reservation.date.annee,
                  
                  reservation.parking.idParking,
                  &reservation.parking.placesDisponibles,
                  reservation.parking.nomParking,
                  reservation.service.id_park,
                  reservation.service.id,
                  reservation.service.libelle,
                  reservation.service.cout) != EOF) {
        
        // Debug: afficher toutes les valeurs lues
        printf("ID Client: %s, Mois: %d, Année: %d, Cout: %s\n", 
               reservation.idClient, reservation.date.mois, reservation.date.annee, reservation.service.cout);

        // Vérification de la comparaison de l'ID et de la date
        if (strcmp(reservation.idClient, id) == 0 && 
            reservation.date.annee == annee && 
            reservation.date.mois == mois) {
            
            // Debug: afficher le montant de chaque service avant de l'ajouter
            float montant = atof(reservation.service.cout);
            printf("Montant du service: %.2f\n", montant);

            total += montant;  // Ajout du montant au total
            printf("Total après ajout: %.2f\n", total);  // Affichage du total après chaque ajout
        }
    }

    fclose(f);

    // Debug: afficher le total final calculé
    printf("Total final calculé: %.2f\n", total);
    return total;
}
int verifier_connexion( char login[50], char mdp[50] )
{	
	int verifier=0;
	Citoyen citoyen;
	FILE* f;

	f=fopen("citoyen.txt", "r");

	if(f!=NULL)
		{
	 while (fscanf(f, "%s %s %s %s %s %s\n",
		citoyen.login,citoyen.mdp,citoyen.id,citoyen.nom, citoyen.prenom,  citoyen.tel) != EOF) 
				{        
				if(strcmp(citoyen.login,login)==0 && strcmp(citoyen.mdp,mdp)==0 )
        				{
					verifier= 1;
					
					}
				else{verifier=-1;}
				}
		}

	fclose(f);

	return verifier;

}

int chercherreservation(char *filename, char id[10]){
FILE *f = fopen("reservations.txt", "r");
	Reservations reserv;
    	int trouv = -1;
    	if (f != NULL) {
        	while (fscanf(f, "%s %s %d %d %d %s %d %s %s %s %s %s \n", reserv.idReservation, 	reserv.idClient,&reserv.date.jour,&reserv.date.mois,&reserv.date.annee, reserv.parking.idParking,&reserv.parking.placesDisponibles,reserv.parking.nomParking,
reserv.service.id_park,reserv.service.id,reserv.service.libelle,
reserv.service.cout ) != EOF) {
            		if (strcmp(reserv.idClient,id) == 0) {
				trouv=1;
			
		}
	}
	fclose(f);
	return trouv;}}





////////////////////////////////////////////////////////////////////////////////////////////////////////

int ajouter(char *filename, rec d, int choix[], char ch[])
{

    for (int i = 0; d.tel[i] != '\0'; i++) {
    if (d.tel[i] < '0' || d.tel[i] > '9') { 
        return 0;
    }
}
        if (strlen(d.tel) != 8) {
	return 0;
    }
 if (strcmp(d.desc,"")==0){return 0;}

    FILE *f = fopen(filename, "a+");  
    if (f != NULL)
    {
        strcpy(ch, "");  
        if (choix[0] == 1)
            strcat(ch, "/Problème_de_paiement/");
        if (choix[1] == 1)
            strcat(ch, "/Problème_avec_le_service_client/");
        if (choix[2] == 1)
            strcat(ch, "/Dommages_au_véhicule/");
        if (choix[3] == 1)
            strcat(ch, "/Autre/");

        for (int i = 0; d.desc[i] != '\0'; i++) {
            if (d.desc[i] == ' ') {
                d.desc[i] = '_';
            }
        }

        int lastRecid = 0;
        rec temp;

        while (fscanf(f, "%d %d %d %d %s %s %s %s %s\n", &temp.recid, &temp.date.jour, &temp.date.mois, &temp.date.annee, temp.tel, temp.idpark, temp.avis, temp.desc, ch) != EOF)
        {
            if (temp.recid > lastRecid)
                lastRecid = temp.recid;
        }

        d.recid = lastRecid + 1; 
      
        fprintf(f, "%d %d %d %d %s %s %s %s %s\n", d.recid, d.date.jour, d.date.mois, d.date.annee, d.tel, d.idpark, d.avis, d.desc, ch);
        fclose(f);
        return 1;
    }
    else
        return 0;
}




////////////////////////////////////////////////////////////////////////////////////////////////////////

int pull( int recid,char tel[9]){
   FILE *f = fopen("add.txt", "r");
    if (f != NULL)
    {
        fscanf(f, "%d",&recid);
        fclose(f);
    }
	remove("add.txt");
	return recid;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////

void add( int recid,char tel[9]){
   FILE *f = fopen("add.txt", "w");
    if (f != NULL)
    {
        fprintf(f, "%d",recid);
        fclose(f); 
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////

int modifier(char *filename, char tel[], int recid, rec nouv, char cha[], char ch[], int choix2[])
{
    
    for (int i = 0; nouv.tel[i] != '\0'; i++) {
    if (nouv.tel[i] < '0' || nouv.tel[i] > '9') { 
        return 0;
    }
}
        if (strlen(nouv.tel) != 8) {
	return 0;
    }
  if (strcmp(nouv.desc,"")==0){return 0;}


    rec t;
    int tr = 0;
    FILE *f = fopen(filename, "r");
    FILE *f2 = fopen("nouv.txt", "w");
    
    if (f != NULL && f2 != NULL)
    {
    strcpy(cha, "");
    if (choix2[0] == 1)
        strcat(cha, "/Problème_de_paiement/");
    if (choix2[1] == 1)
        strcat(cha, "/Problème_avec_le_service_client/");
    if (choix2[2] == 1)
        strcat(cha, "/Dommages_au_véhicule/");
    if (choix2[3] == 1)
        strcat(cha, "/Autre/");

    for (int i = 0; nouv.desc[i] != '\0'; i++) {
        if (nouv.desc[i] == ' ') {
            nouv.desc[i] = '_';
        }
    }
        while (fscanf(f, "%d %d %d %d %s %s %s %s %s\n",
                      &t.recid, &t.date.jour, &t.date.mois, &t.date.annee, 
                      t.tel, t.avis, t.idpark, t.desc, ch) != EOF)
        {
            if (recid == t.recid)
            {
                fprintf(f2, "%d %d %d %d %s %s %s %s %s\n", 
                        t.recid, nouv.date.jour, nouv.date.mois, 
                        nouv.date.annee, nouv.tel, nouv.avis, 
                        nouv.idpark, nouv.desc, cha);
                tr = 1; 
            }
            else
            {
                fprintf(f2, "%d %d %d %d %s %s %s %s %s\n", 
                        t.recid, t.date.jour, t.date.mois, 
                        t.date.annee, t.tel, t.avis, 
                        t.idpark, t.desc, ch);
            }
        }

        fclose(f);
        fclose(f2);
        remove(filename);
        rename("nouv.txt", filename);
        return tr;
    }
    else
    {
        
        if (f != NULL) fclose(f);
        if (f2 != NULL) fclose(f2);
        return -1; 
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

 int supprimer(char * filename, char tel[], int recid,char ch[])
{
    int tr=0;
    rec d;
    FILE * f=fopen(filename, "r");
    FILE * f2=fopen("nouv.txt", "w");
    if(f!=NULL && f2!=NULL)
    {
        while(fscanf(f,"%d %d %d %d %s %s %s %s %s\n",&d.recid, &d.date.jour, &d.date.mois, &d.date.annee, d.tel, d.idpark, d.avis , d.desc,ch)!=EOF)
        {
            if( recid==d.recid)
                tr=1;
            else
                fprintf(f2,"%d %d %d %d %s %s %s %s %s\n",d.recid,d.date.jour,d.date.mois,d.date.annee,d.tel ,d.idpark, d.avis , d.desc,ch);
        }
    }
    fclose(f);
    fclose(f2);
    remove(filename);
    rename("nouv.txt", filename);
    return tr;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////

rec chercher(char * filename, char tel[],int recid,char ch[])
{
    rec d;
    int tr=0;
    FILE * f=fopen(filename, "r");
    if(f!=NULL)
    {    
        while(tr==0&& fscanf(f,"%d %d %d %d %s %s %s %s %s\n",&d.recid, &d.date.jour, &d.date.mois, &d.date.annee, d.tel,d.idpark, d.avis , d.desc ,ch)!=EOF)
        {
            if(strcmp(d.tel,tel)==0 && recid == d.recid)
                tr=1;
        }
    }
    fclose(f);
    if(tr==0)
        strcpy(d.tel,"-1");
    return d;

}
///////////////////////////////////////////////////////////////////////////////////////////////////

void afficherListeTrieeParAvis(char *filename) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("\nErreur.\n");
        return;
    }

    ParkingInfo parkingList[MAX_PARKINGS];
    int count = 0;
    rec claim;
    char ch[100];

    while (fscanf(f, "%d %d %d %d %s %s %s %s %s\n",
                  &claim.recid, &claim.date.jour, &claim.date.mois, &claim.date.annee,
                  claim.tel, claim.avis, claim.idpark, claim.desc, ch) != EOF) {
        int avis = atoi(claim.avis);
        int found = 0;

        for (int i = 0; i < count; i++) {
            if (strcmp(parkingList[i].idpark, claim.idpark) == 0) {
                parkingList[i].totalAvis += avis;
                parkingList[i].countAvis++;
                found = 1;
                break;
            }
        }

        if (!found) {
            strcpy(parkingList[count].idpark, claim.idpark);
            parkingList[count].totalAvis = avis;
            parkingList[count].countAvis = 1;
            count++;
        }
    }

    fclose(f);

    for (int i = 0; i < count; i++) {
        parkingList[i].moyenneAvis = (float)parkingList[i].totalAvis / parkingList[i].countAvis;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (parkingList[i].moyenneAvis < parkingList[j].moyenneAvis) {
                ParkingInfo temp = parkingList[i];
                parkingList[i] = parkingList[j];
                parkingList[j] = temp;
            }
        }
    }

    FILE *liste = fopen("parking_trie.txt", "w");
    if (liste == NULL) {
        printf("\nErreur.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(liste, "%s %.1f\n", parkingList[i].idpark, parkingList[i].moyenneAvis);
    }

    fclose(liste);
  

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void afficher_rec (GtkWidget *liste,char ch[]){
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter ;
	GtkListStore *store;
    	

	int recid; 
    	int jour;  
   	int mois;  
    	int annee; 
    	char tel[9] , idpark[5];
    	char avis[2];
    	char desc[300];
	store =NULL;


	FILE *f;
	store=gtk_tree_view_get_model(liste);
	if (store==NULL){
		renderer = gtk_cell_renderer_text_new ();
		column =gtk_tree_view_column_new_with_attributes("ID ",renderer,"text",ERECID,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("jour",renderer,"text",EJOUR,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("mois",renderer,"text",EMOIS,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column =gtk_tree_view_column_new_with_attributes("annee",renderer,"text",EANNEE,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("tel",renderer,"text",ETEL,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("id park",renderer,"text", EAVIS,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("avis",renderer,"text",EIDPARK,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

		renderer = gtk_cell_renderer_text_new ();
		column =gtk_tree_view_column_new_with_attributes("description",renderer,"text",EDESC,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
	

	
	}
	store=gtk_list_store_new (COLUMNS1 ,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_INT,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_STRING ,G_TYPE_STRING);
	f=fopen("reclamations.txt", "r");
	if (f==NULL){
		return;
	}
	else {
		f=fopen("reclamations.txt", "a+");
		while (fscanf(f,"%d %d %d %d %s %s %s %s %s\n",&recid, &jour, &mois, &annee,tel,idpark,avis,desc,ch)!=EOF){

			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store ,&iter ,ERECID ,recid ,EJOUR, jour ,EMOIS,mois,EANNEE ,annee ,ETEL, tel ,EIDPARK,idpark,EAVIS,avis,EDESC,desc,-1);
	}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
		g_object_unref(store);


}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////



void supprimer_tre(rec r,char ch[])
{

	int recid;
    	int jour;
   	int mois;
    	int annee;
    	char tel[9] , avis[2];
    	char desc[300];
    	char idpark[5];


	rec r2;
	FILE *f,*g;
	f=fopen("reclamations.txt","r");
	g=fopen("dumb.txt","w");
	if (f==NULL || g==NULL){
		return;
	}
	else {
		while(fscanf(f,"%d %d %d %d %s %s %s %s %s\n",&r2.recid,&r2.date.jour,&r2.date.mois,&r2.date.annee,r2.tel,r2.idpark,r2.avis,r2.desc,ch)!=EOF){
			if (r.recid != r2.recid ||r.date.jour != r2.date.jour ||r.date.mois != r2.date.mois ||r.date.annee != r2.date.annee || strcmp(r.tel,r2.tel)!=0|| strcmp(r.idpark,r2.idpark)!=0 || strcmp(r.avis,r2.avis)!=0 || strcmp(r.desc,r2.desc)!=0)
				fprintf(g,"%d %d %d %d %s %s %s %s %s\n",r2.recid,r2.date.jour,r2.date.mois,r2.date.annee,r2.tel,r2.idpark,r2.avis,r2.desc,ch);
		}

	} 
	fclose(f);
	fclose(g);
	remove("reclamations.txt");
	rename("dumb.txt","reclamations.txt");
}


//////////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void afficher_rectree (GtkWidget *liste){
	GtkCellRenderer *renderer;
	GtkTreeViewColumn *column;
	GtkTreeIter iter ;
	GtkListStore *store;
    	  


    	char idpark[5];
    	char avis[4];

	store =NULL;


	FILE *f;
	store=gtk_tree_view_get_model(liste);
	if (store==NULL){


		renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("id park",renderer,"text",EIDPARKT ,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);
			renderer = gtk_cell_renderer_text_new ();
		column = gtk_tree_view_column_new_with_attributes("avis",renderer,"text",EAVIST,NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(liste),column);

	}
	store=gtk_list_store_new (ECOLUMNS ,G_TYPE_STRING ,G_TYPE_STRING);
	f=fopen("parking_trie.txt", "r");
	if (f==NULL){
		return;
	}
	else {
		f=fopen("parking_trie.txt", "a+");
		while (fscanf(f,"%s %s\n",idpark,avis)!=EOF){

			gtk_list_store_append(store,&iter);
			gtk_list_store_set(store ,&iter ,EAVIST,avis,EIDPARKT,idpark,-1);
	}
		fclose(f);
		gtk_tree_view_set_model(GTK_TREE_VIEW(liste),GTK_TREE_MODEL(store));
		g_object_unref(store);


}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////



void supprimer_tretree(rec r)
{

	
    	char avis[2];
    	char idpark[5];


	rec r2;
	FILE *f,*g;
	f=fopen("parking_trie.txt","r");
	g=fopen("dumb.txt","w");
	if (f==NULL || g==NULL){
		return;
	}
	else {
		while(fscanf(f,"%s %s\n",r2.idpark,r2.avis)!=EOF){
			if ( strcmp(r.idpark,r2.idpark)!=0 || strcmp(r.avis,r2.avis)!=0 )
				fprintf(g,"%s %s\n",r2.idpark,r2.avis);
		}

	} 
	fclose(f);
	fclose(g);
	remove("parking_trie.txt");
	rename("dumb.txt","parking_trie.txt");
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ajouter_services( serviceh s1 )
{	
	int ajouter=1;
	serviceh s;
	FILE* f;

	f=fopen("services.txt", "a+");

	if(f==NULL)
		{
			printf("Erreur de creation du fichier!");
			return 0;
		}
	else
		{
			 while (fscanf(f,"%9[^,], %9[^,], %49[^,], %3[^,\n],\n",s.id_park,s.id,s.libelle,s.cout)!=EOF)
				{        
					if(strcmp(s1.id,s.id)==0)
        					{
						ajouter= 0;
						break;
						}
				}
		}
	if(ajouter==1)
			{
			fprintf(f,"%s,%s,%s,%s,\n",s1.id_park,s1.id,s1.libelle,s1.cout);
			}

	fclose(f);
	return ajouter;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int modifier_services(serviceh s1, char id[10], char id_park[10])
{
	int modif=0;
	serviceh s;
	FILE* f=fopen("services.txt","r");
	FILE* g=fopen("nouv.txt","w");

	if ( (f==NULL) || (g==NULL) )
		{
			printf("Erreur d'ouverture du fichier!");
			return 0;
		}
	else
		{
			while (fscanf(f,"%9[^,], %9[^,], %49[^,], %3[^,\n],\n",s.id_park,s.id,s.libelle,s.cout)!=EOF)
				{
					if(strcmp(id,s.id)==0 && strcmp(s1.id_park, id_park) == 0)
        					{
							fprintf(g,"%s,%s,%s,%s,\n",s1.id_park,s1.id,s1.libelle,s1.cout);
							modif=1;
						}
					else
						{
							fprintf(g,"%s,%s,%s,%s,\n",s.id_park,s.id,s.libelle,s.cout);
							modif=0;
						}
				}
		}

	fclose(f);
	fclose(g);
	remove("services.txt");
	rename("nouv.txt","services.txt");
	return modif;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int supprimer_services(char id[] , char id_park[])
{
	int supprimer=0;
	serviceh s1;
	FILE* f=fopen("services.txt", "r");
	FILE* g=fopen("nouv.txt", "w");

	if(f==NULL || g==NULL )
		{
			printf("Erreur d'ouverture du fichier!");
			return 0;
		}
	else
		{
        	while (fscanf(f,"%9[^,], %9[^,], %49[^,], %3[^,\n],\n",s1.id_park,s1.id,s1.libelle,s1.cout)!=EOF)
			{
				if(strcmp(s1.id, id) != 0 && strcmp(s1.id_park, id_park) != 0 )
					{
                			fprintf(g,"%s, %s, %s, %s,\n",s1.id_park,s1.id,s1.libelle,s1.cout);
					}
			}
		supprimer =1;
		}

	fclose(f);
	fclose(g);
	remove("services.txt");
	rename("nouv.txt", "services.txt");
	return supprimer;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

serviceh chercher_services(char id[])
{
	serviceh s1 = {"", "", "", ""};
        serviceh s;
	FILE* f = fopen("services.txt", "r");

	if (f == NULL)
		{
        	printf("Erreur d'ouverture de fichier \n");
		}
	else
		{
		 while (fscanf(f,"%9[^,], %9[^,], %49[^,], %3[^,\n],\n",s.id_park,s.id,s.libelle,s.cout)!=EOF)
			{
        		if (strcmp(s.id, id) == 0)
	 			{
	   			strcpy(s1.id_park,s.id_park);
	   			strcpy(s1.id,s.id);  
	   			strcpy(s1.libelle,s.libelle);
				strcpy(s1.cout,s.cout);
           			printf("service trouve\n");
				break ;
				}
			else
				{
				printf("service non trouve !\n");
				break;
				}

			}
		}

	fclose(f);
	return s1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void affecter_service(char id_service[10], char id_reservation[10]) {
    serviceh s1;
    reservation res;
    int affecter = 0;
    FILE *f_reservations = fopen("reservations.txt", "r");
    FILE *f_temp = fopen("reservations_temp.txt", "w");

    if (f_reservations == NULL || f_temp == NULL) {
        printf("Erreur d'ouverture des fichiers !\n");
        if (f_reservations != NULL) fclose(f_reservations);
        if (f_temp != NULL) fclose(f_temp);
        return;
    }

    s1 = chercher_services(id_service);
    if (s1.id[0] == '\0') {
        printf("Service introuvable.\n");
        fclose(f_reservations);
        fclose(f_temp);
        return;
    }

    while (fscanf(f_reservations, "%9[^,], %9[^,], %9[^,], %9[^,\n],\n",
                  res.id_reservation, res.id_client, res.id_parking, res.id_service) == 4) {
        if (strcmp(res.id_reservation, id_reservation) == 0) {
            strcpy(res.id_service, s1.id);
            affecter = 1;
        }

        fprintf(f_temp, "%s,%s,%s,%s,\n", res.id_reservation, res.id_client, res.id_parking, res.id_service);
    }

    fclose(f_reservations);
    fclose(f_temp);

    remove("reservations.txt");
    rename("reservations_temp.txt", "reservations.txt");

    if (affecter) {
        printf("Service %s affecté à la réservation %s.\n", id_service, id_reservation);
    } else {
        printf("Réservation %s introuvable.\n", id_reservation);
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void afficher_ser(GtkWidget *liste) {	
    serviceh s;

    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkListStore *store;

    FILE *f;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(liste)));

    if (store == NULL) {
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID_parking", renderer, "text", ID_PARK_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("ID_service", renderer, "text", ID_SERVICE_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Libelle", renderer, "text", LIBELLE_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Cout", renderer, "text", COUT_COLUMN, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(liste), column);

        store = gtk_list_store_new(COLUMNShoussem, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    }

    f = fopen("services.txt", "r");
    if (f == NULL) {
        g_print("Erreur : Impossible d'ouvrir le fichier services.txt\n");
        return;
    }

    while (fscanf(f, "%9[^,], %9[^,], %49[^,], %3[^,\n],\n", s.id_park, s.id, s.libelle, s.cout) == 4) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter,
                           ID_PARK_COLUMN, s.id_park,
                           ID_SERVICE_COLUMN, s.id,
                           LIBELLE_COLUMN, s.libelle,
                           COUT_COLUMN, s.cout,
                           -1);
    }

    fclose(f);

    gtk_tree_view_set_model(GTK_TREE_VIEW(liste), GTK_TREE_MODEL(store));
    g_object_unref(store);
}





