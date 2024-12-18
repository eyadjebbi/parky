#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "parking.h"
#include<string.h>



    void on_butajouter_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *idparking, *nomparking, *nbplaces, *capacite, *adresse , *labelparky  , *sortieparking ;
    char idpark[20], nb[20], cap[20], nnpark[50], adr[50];

    idparking = lookup_widget(GTK_WIDGET(button), "idparking");
    nomparking = lookup_widget(GTK_WIDGET(button), "nomparking");
    nbplaces = lookup_widget(GTK_WIDGET(button), "nbplaces");
    capacite = lookup_widget(GTK_WIDGET(button), "capacite");
    adresse = lookup_widget(GTK_WIDGET(button), "adresse");
    sortieparking= lookup_widget(GTK_WIDGET(button), "sortieparking");
  
     strcpy(idpark, gtk_entry_get_text(GTK_ENTRY(idparking)));
    strcpy(nnpark, gtk_entry_get_text(GTK_ENTRY(nomparking)));
    strcpy(nb, gtk_entry_get_text(GTK_ENTRY(nbplaces)));
    strcpy(cap, gtk_entry_get_text(GTK_ENTRY(capacite)));
    strcpy(adr, gtk_entry_get_text(GTK_ENTRY(adresse)));

    if (strlen(idpark) == 0 || strlen(nnpark) == 0 || strlen(nb) == 0 || 
        strlen(cap) == 0 || strlen(adr) == 0) {
        g_warning("Veuillez remplir tous les champs correctement");
       gtk_label_set_text(GTK_LABEL(sortieparking)," Veuillez remplir tous les champs correctement");
         return;
   }
    parking p;
    strcpy(p.id,idpark);
    strcpy(p.nomparking,nnpark);
    strcpy(p.capacite,cap);
    strcpy(p.nbplacesdispo,nb);
    strcpy(p.adresse,adr);


  int x=ajouterparking( p  );
  if (x=0){ 
   g_warning("parking non ajouté ");
    return ; }
  if (x=1) {
    g_warning("parking ajouté avec succées ");
   gtk_label_set_text(GTK_LABEL(sortieparking),"Parking ajouté  avec succées ");
     return ;}
  

}

void on_but1modifier_clicked(GtkButton *button, gpointer user_data) {

 GtkWidget *idmodif, *nommodif, *nbplacesmodif, *capacitemodif, *adressemodif, *modiflabel;
 char idparkmodif[20], nbmodif[20], capmodif[20], nnmodif[50], adrmodif[50] ,nb_str[10],cap_str[10];

    idmodif = lookup_widget(GTK_WIDGET(button), "idmodif");
    nommodif = lookup_widget(GTK_WIDGET(button), "nommodif");
    nbplacesmodif = lookup_widget(GTK_WIDGET(button), "nbplacesmodif");
    capacitemodif = lookup_widget(GTK_WIDGET(button), "capacitemodif");
    adressemodif = lookup_widget(GTK_WIDGET(button), "adressemodif");
     modiflabel= lookup_widget(GTK_WIDGET(button), "modiflabel");
    const gchar *idmodiftext= gtk_combo_box_get_active_text(GTK_COMBO_BOX(idmodif));
     strcpy(idparkmodif,idmodiftext);
    strcpy(nnmodif, gtk_entry_get_text(GTK_ENTRY(nommodif)));
   int nb = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(nbplacesmodif));
   sprintf( nb_str, "%d", nb);
    strcpy(nbmodif,nb_str);
     int cap = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(capacitemodif));
   sprintf( cap_str, "%d", cap);
    strcpy(capmodif,cap_str);
    strcpy(adrmodif, gtk_entry_get_text(GTK_ENTRY(adressemodif))) ; 

   
    parking nouv ; 
    strcpy(nouv.id,idparkmodif);
    strcpy(nouv.nomparking,nnmodif);
    strcpy(nouv.capacite,capmodif);
    strcpy(nouv.nbplacesdispo,nbmodif);
    strcpy(nouv.adresse,adrmodif);
    int tr  = modifierparking( idparkmodif , nouv  );

     if (tr==0){ 
     g_warning("parking non modifie ");
    return ; }
      if (tr==1) {
    g_warning("parking modifie avec succées ");
      gtk_label_set_text(GTK_LABEL(modiflabel),"Parking modifié avec succées "); 
     return ;}

}

void
on_butsupprimer_clicked (GtkButton *button, gpointer user_data)
{
   GtkWidget *idsupprimer , *supp_park , *supprimerlabel;
   char idparksupp[10];

  
   idsupprimer = lookup_widget(GTK_WIDGET(button), "idsupprimer");
  supprimerlabel= lookup_widget(GTK_WIDGET(button), "supprimerlabel");
    gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(supp_park));
   if (GTK_IS_COMBO_BOX(idsupprimer)) {
       const gchar *idsupprimertext = gtk_combo_box_get_active_text(GTK_COMBO_BOX(idsupprimer));
       if (idsupprimertext != NULL) {
           strcpy(idparksupp, idsupprimertext);
       } else {
           g_warning("Aucun texte sélectionné dans le combo box");
           return;
       }
   }
   
       if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(supp_park))){
		gtk_label_set_text(GTK_LABEL(supprimerlabel), "veuillez confirmer");}
	else{
		strcpy(idparksupp, gtk_entry_get_text(GTK_ENTRY(idsupprimer)));
}
   int tr = supprimerparking(idparksupp);
   if (tr == 1) {
       g_warning("Parking supprimé avec succès.");
      gtk_label_set_text(GTK_LABEL(supprimerlabel), "Parking supprimé avec succées  ");
       return;
   } else {
       g_warning("Échec de la suppression du parking.");
	gtk_label_set_text(GTK_LABEL(supprimerlabel), "Échec de la suppression du parking.");
   }
}

void on_butajouteragent_clicked(GtkButton *button, gpointer user_data)
{
    GtkWidget *idagent, *nomagent, *prenomagent, *calendaragent , *sortieagent ;
    char id[50], nnagent[50], pragent[50];
    agentparking ap;
    guint year, month, day;

    
    idagent = lookup_widget(GTK_WIDGET(button), "idagent");
    nomagent = lookup_widget(GTK_WIDGET(button), "nomagent");
    prenomagent = lookup_widget(GTK_WIDGET(button), "prenomagent");
    calendaragent = lookup_widget(GTK_WIDGET(button), "calendaragent");
    sortieagent= lookup_widget(GTK_WIDGET(button), "sortieagent");
   
     const gchar *idagenttext = gtk_combo_box_get_active_text(GTK_COMBO_BOX(idagent));
     strcpy(id, idagenttext);
      

   
    strcpy(nnagent, gtk_entry_get_text(GTK_ENTRY(nomagent)));
    strcpy(pragent, gtk_entry_get_text(GTK_ENTRY(prenomagent)));

 
    gtk_calendar_get_date(GTK_CALENDAR(calendaragent), &year, &month, &day);
    snprintf(ap.date.jour, sizeof(ap.date.jour), "%02d", day);
    snprintf(ap.date.mois, sizeof(ap.date.mois), "%02d", month + 1);  
    snprintf(ap.date.annee, sizeof(ap.date.annee), "%04d", year);


    if (strlen(id) == 0 || strlen(nnagent) == 0 || strlen(pragent) == 0 ||
        strlen(ap.date.jour) == 0 || strlen(ap.date.mois) == 0 || strlen(ap.date.annee) == 0) {
        g_warning("Veuillez remplir tous les champs correctement.");
	 gtk_label_set_text(GTK_LABEL(sortieagent),"Veuillez remplir tous les champs correctement. ");
        return;
    }

    strcpy(ap.idagent, id);
    strcpy(ap.nomagent, nnagent);
    strcpy(ap.prenomagent, pragent);
    strcpy(ap.idparking, ""); 

    
    int x = ajouteragent(ap);

    if (x == 0) {
        g_warning("Agent non ajouté.");
        return;
    }
    if (x == 1) {
        g_warning("Agent ajouté avec succès.");
	 gtk_label_set_text(GTK_LABEL(sortieagent),"agent ajouté avec succées ");
        return;
    }
}

void on_butaffecter_clicked(GtkWidget *objet, gpointer user_data) {
    
    GtkWidget *idagentaffecter = lookup_widget(objet,"idagentaffecter"); 
    GtkWidget *idparkingaffecter = lookup_widget(objet,"idparkingaffecter");  
	 GtkWidget *sortieaffecter ; 
    char idaffecter[50], idpaffecter[50];
	sortieaffecter= lookup_widget(GTK_WIDGET(objet), "sortieaffecter");
	 strcpy(idaffecter, gtk_combo_box_get_active_text(GTK_COMBO_BOX(idagentaffecter)));
	g_warning("id ag %s\n", idaffecter);
    if (idaffecter == NULL) {
        g_warning("Aucun agent sélectionné.");
        return;
    }
    


    const gchar *idparkingaffectertext = gtk_combo_box_get_active_text(GTK_COMBO_BOX(idparkingaffecter));
    if (idparkingaffectertext == NULL) {
        g_warning("Aucun parking sélectionné.");
        return;
    }
    strcpy(idpaffecter, idparkingaffectertext);
	g_warning("id park %s\n", idpaffecter);
  
    int x = affecteragent(idaffecter, idpaffecter);

    if (x == 0) {
        g_warning("Agent non affecté.");
	 gtk_label_set_text(GTK_LABEL(sortieaffecter),"agent non affecté  ");
    } else if (x == 1) {
        g_print("Agent affecté avec succès.\n");
	 gtk_label_set_text(GTK_LABEL(sortieaffecter),"agent affecté avec succées ");
    } else {
        g_warning("Erreur inconnue lors de l'affectation de l'agent.");
    }
}



void
on_buttonajoutprecedent_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *gererparking , *ajoutdeparking;
ajoutdeparking=lookup_widget(GTK_WIDGET(button),"ajoutdeparking");
 gererparking = create_gererparking ();
gtk_widget_hide(ajoutdeparking);
 gtk_widget_show (gererparking);
}


void
on_buttonsupprimerprecedent_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *gererparking , *supprimerparking;
supprimerparking=lookup_widget(GTK_WIDGET(button),"supprimerparking");
 gererparking = create_gererparking ();
gtk_widget_hide(supprimerparking);
 gtk_widget_show (gererparking);

}


void
on_buttonmodifprecedent_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *gererparking , *modifierparking;
modifierparking=lookup_widget(GTK_WIDGET(button),"modifierparking");
 gererparking = create_gererparking ();
gtk_widget_hide(modifierparking);
 gtk_widget_show (gererparking);
}


void
on_buttonaffichageprecent_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *gererparking , *afficherparking;
afficherparking=lookup_widget(GTK_WIDGET(button),"afficherparking");
 gererparking = create_gererparking ();
gtk_widget_hide(afficherparking);
 gtk_widget_show (gererparking);
}


void
on_buttongereraffectationprecedent__clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *gererparking , *gereraffectation_;
gereraffectation_=lookup_widget(GTK_WIDGET(button),"gereraffectation_");
 gererparking = create_gererparking ();
gtk_widget_hide(gereraffectation_);
 gtk_widget_show (gererparking);
}


void
on_buttonajouterparking_clicked (GtkButton       *button, gpointer         user_data)
{

GtkWidget *ajoutdeparking , *gererparking;

gererparking=lookup_widget(GTK_WIDGET(button),"gererparking");
ajoutdeparking = create_ajoutdeparking ();


gtk_widget_hide(gererparking);
gtk_widget_show (ajoutdeparking);
}


void
on_buttonmodifierparking_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *modifierparking , *gererparking ;
gererparking=lookup_widget(GTK_WIDGET(button),"gererparking");
 modifierparking = create_modifierparking ();
gtk_widget_hide(gererparking);
 gtk_widget_show (modifierparking);
}


void
on_buttonsupprimerparking_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *supprimerparking , *gererparking;
gererparking=lookup_widget(GTK_WIDGET(button),"gererparking");
 supprimerparking = create_supprimerparking ();
 gtk_widget_hide(gererparking);
 gtk_widget_show (supprimerparking);
}


void
on_buttonafficherparking_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *treeviewparking;
	GtkWidget *afficherparking; 
	GtkWidget *gererparking ;
	gererparking=lookup_widget(GTK_WIDGET(button),"gererparking");
	gtk_widget_hide(gererparking);
	afficherparking=lookup_widget(GTK_WIDGET(button),"afficherparking"); 
	afficherparking=create_afficherparking();
	gtk_widget_show(afficherparking);
	treeviewparking=lookup_widget(afficherparking,"treeviewparking");
	afficherparking_(treeviewparking);
}


void
on_button43_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *gereraffectation_ , *gererparking;
gererparking=lookup_widget(GTK_WIDGET(button),"gererparking");
 gereraffectation_ = create_gereraffectation_ ();
 gtk_widget_hide(gererparking);
 gtk_widget_show (gereraffectation_);
}


void
on_buttongereraffectation__clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
 GtkWidget *ajoutagent_ , *gereraffectation_;
gereraffectation_=lookup_widget(GTK_WIDGET(button),"gereraffectation_");

ajoutagent_ = create_ajoutagent_ ();
gtk_widget_hide(gereraffectation_);

 gtk_widget_show (ajoutagent_);
}

void
on_buttongereraffectationafficher_clicked(GtkButton *button,gpointer user_data)
{
        GtkWidget *treeview1;
	GtkWidget *afficheraffectation_ ; 
	GtkWidget *gereraffectation_ ;
	gereraffectation_=lookup_widget(GTK_WIDGET(button),"gereraffectation_");
	gtk_widget_hide(gereraffectation_);
	afficheraffectation_ =lookup_widget(GTK_WIDGET(button),"afficheraffectation_"); 
	afficheraffectation_ =  create_afficheraffectation_();
	gtk_widget_show(afficheraffectation_);
	treeview1=lookup_widget(afficheraffectation_ ,"treeview1");
	afficheragent(treeview1); 
}

void
on_buttongereraffecterunagent__clicked (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *affecteragent_ , *gereraffectation_;
gereraffectation_=lookup_widget(GTK_WIDGET(button),"gereraffectation_");
 affecteragent_ = create_affecteragent_ ();
gtk_widget_hide(gereraffectation_);
 gtk_widget_show (affecteragent_);
}

void
on_buttonaffichagajouter_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *ajoutdeparking , *afficherparking;
afficherparking=lookup_widget(GTK_WIDGET(button),"afficherparking");
ajoutdeparking = create_ajoutdeparking ();
gtk_widget_hide(afficherparking);
 gtk_widget_show (ajoutdeparking);
}


void
on_buttonaffichagemodif_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *modifierparking , *afficherparking;
afficherparking=lookup_widget(GTK_WIDGET(button),"afficherparking");
 modifierparking = create_modifierparking ();
gtk_widget_hide(afficherparking);
 gtk_widget_show (modifierparking);
}


void
on_buttonaffichagesupprimer_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *supprimerparking, *afficherparking;
afficherparking=lookup_widget(GTK_WIDGET(button),"afficherparking");
 supprimerparking = create_supprimerparking ();
gtk_widget_hide(afficherparking);
 gtk_widget_show (supprimerparking);
}


void
on_buttonaaficherajout__clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *ajoutagent_ , *afficheraffectation_;
afficheraffectation_=lookup_widget(GTK_WIDGET(button),"afficheraffectation_");

ajoutagent_ = create_ajoutagent_ ();
gtk_widget_hide(afficheraffectation_);

 gtk_widget_show (ajoutagent_);
}





void
on_affecterprecedent__clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *affecteragent_ , *gereraffectation_;
affecteragent_=lookup_widget(GTK_WIDGET(button),"affecteragent_");
gereraffectation_ = create_gereraffectation_ ();
gtk_widget_hide(affecteragent_);
 gtk_widget_show (gereraffectation_);;
}


void
on_button30_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *gereraffectation_;
 gereraffectation_ = create_gereraffectation_ ();
 gtk_widget_show (gereraffectation_);
}


void
on_button44_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *ajoutagent_ , *gereraffectation_;
ajoutagent_=lookup_widget(GTK_WIDGET(button),"ajoutagent_");
gereraffectation_ = create_gereraffectation_ ();
gtk_widget_hide(ajoutagent_);
 gtk_widget_show (gereraffectation_);

}


void
on_buttonadministrateur_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *admincitoyen, *login;
admincitoyen=lookup_widget(GTK_WIDGET(button),"admincitoyen");
login = create_login ();
gtk_widget_hide(admincitoyen);
 gtk_widget_show (login);
}


void
on_buttonnouveaucitoyen_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *admincitoyen, *ajoutcitoyen_;

	admincitoyen=lookup_widget(GTK_WIDGET(button),"admincitoyen");
	ajoutcitoyen_= create_ajoutclient__ ();

	gtk_widget_hide(admincitoyen);
	gtk_widget_show (ajoutcitoyen_);
}


void
on_buttonparking_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *gerer, *gererparking;

	gerer=lookup_widget(GTK_WIDGET(button),"gerer");
	gererparking = create_gererparking ();

	gtk_widget_hide(gerer);
 	gtk_widget_show (gererparking );
}

void on_button_add_citoyen_clicked(GtkButton *button, gpointer user_data) {
    	GtkWidget *cincitoyen, *prenomcitoyen, *nomcitoyen, *telcitoyen,*ajoutlogin,*ajoutmdp;
	GtkWidget *espace_citoyen,*msg_ajout;
	GtkWidget *ajoutclient_;

    
    char nn[50], pre[50], cin[50], tel[50],msg[50],login[50],mdp[50];
	
	ajoutlogin = lookup_widget(GTK_WIDGET(button), "ajoutlogin");
	ajoutmdp= lookup_widget(GTK_WIDGET(button), "ajoutmdp");
	nomcitoyen = lookup_widget(GTK_WIDGET(button), "nomcitoyen");
	prenomcitoyen = lookup_widget(GTK_WIDGET(button), "prenomcitoyen");
	cincitoyen = lookup_widget(GTK_WIDGET(button), "cincitoyen");
	telcitoyen = lookup_widget(GTK_WIDGET(button), "telcitoyen");
	msg_ajout= lookup_widget(GTK_WIDGET(button), "msg_ajout");

    	strcpy(nn, gtk_entry_get_text(GTK_ENTRY(nomcitoyen)));
    	strcpy(pre, gtk_entry_get_text(GTK_ENTRY(prenomcitoyen)));
    	strcpy(cin, gtk_entry_get_text(GTK_ENTRY(cincitoyen)));
    	strcpy(tel, gtk_entry_get_text(GTK_ENTRY(telcitoyen)));
	strcpy(login, gtk_entry_get_text(GTK_ENTRY(ajoutlogin)));
    	strcpy(mdp, gtk_entry_get_text(GTK_ENTRY(ajoutmdp)));

    	if (strlen(nn) == 0 || strlen(pre) == 0 || strlen(cin) == 0 || strlen(tel) == 0||strlen(login)==0 			||strlen(mdp)==0) {
        gtk_label_set_text(GTK_LABEL(msg_ajout),"veuillez remplir tout les champs");
    		}

    	else{
		Citoyen citoyen;
		strcpy(citoyen.login,login);
    		strcpy(citoyen.mdp,mdp);
    		strcpy(citoyen.id, cin);
    		strcpy(citoyen.nom, nn);
    		strcpy(citoyen.prenom, pre);
    		strcpy(citoyen.tel, tel);

    		int result = ajouterProfil("citoyen.txt",citoyen);
    		if (result == 1) {
   				gtk_label_set_text(GTK_LABEL(msg_ajout),"Félicitation! vous etes bien 	inscrit");

    				}
		}
}



void
on_saveupdate_clicked                  (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *updatenom,*updateprenom,*updatetel,*updateid,*updatesortie,*update_username,*edit_mdp;
	
	char nn[50],pre[50],tel[8],id[50],user[50],mdp[50];
	
	updatenom = lookup_widget(GTK_WIDGET(button), "updatenom");
    	updateprenom= lookup_widget(GTK_WIDGET(button), "updateprenom");
    	updatetel= lookup_widget(GTK_WIDGET(button), "updatetel");
    	updatesortie= lookup_widget(GTK_WIDGET(button), "updatesortie");
	updateid= lookup_widget(GTK_WIDGET(button), "updateid");
	update_username=lookup_widget(GTK_WIDGET(button), "update_username");
	edit_mdp= lookup_widget(GTK_WIDGET(button), "edit_mdp");
	
	
	
	strcpy(nn, gtk_entry_get_text(GTK_ENTRY(updatenom)));
    	strcpy(pre, gtk_entry_get_text(GTK_ENTRY(updateprenom)));
    	strcpy(tel, gtk_entry_get_text(GTK_ENTRY(updatetel)));
	strcpy(id, gtk_entry_get_text(GTK_ENTRY(updateid)));
	strcpy(user, gtk_entry_get_text(GTK_ENTRY(update_username)));
	strcpy(mdp, gtk_entry_get_text(GTK_ENTRY(edit_mdp)));
	
	if (strlen(nn) == 0 || strlen(pre) == 0 || strlen(tel) == 0  || strlen(user) == 0  || strlen(mdp) == 0 )
	{
		gtk_label_set_text(GTK_LABEL(updatesortie),"veuillez remplir tout les champs");
	}
	else
	{
		Citoyen modifier;
		strcpy(modifier.nom,nn);
		strcpy(modifier.prenom,pre);
		strcpy(modifier.tel,tel);
		strcpy(modifier.login,user);
		strcpy(modifier.mdp,mdp);
		strcpy(modifier.id,id);
		if (chercherprofil("citoyen.txt",id)==1)
		{
			modifierProfil("citoyen.txt",id,modifier);
			gtk_label_set_text(GTK_LABEL(updatesortie),"modification faite avec succées");
		}
		else
		{gtk_label_set_text(GTK_LABEL(updatesortie),"id incorrecte");}
	
    	}
}


void
on_del_citoyen_clicked                  (GtkButton       *button,
                                        gpointer         user_data){

	GtkWidget *del_id ,*checkbox_sur,*del_out;
	GtkWidget *admincitoyen, *suppressioncitoyen;

	char id[50];

	del_id= lookup_widget(GTK_WIDGET(button), "del_id");
	checkbox_sur=lookup_widget(GTK_WIDGET(button),"checkbox_sur");
	del_out= lookup_widget(GTK_WIDGET(button), "del_out");
	gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox_sur));

	if (!gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(checkbox_sur))){
		gtk_label_set_text(GTK_LABEL(del_out), "veuillez confirmer");}
	else{
		strcpy(id, gtk_entry_get_text(GTK_ENTRY(del_id)));
   
		int x=supprimerProfil("citoyen.txt", id);
		if (x==1) {
			suppressioncitoyen=lookup_widget(GTK_WIDGET(button),"suppressioncitoyen");
			admincitoyen= create_admincitoyen();
			gtk_widget_hide(suppressioncitoyen);
 			gtk_widget_show (admincitoyen);
        
    			}
		 else {
        		gtk_label_set_text(GTK_LABEL(del_out), "Erreur lors de la suppression");
   			 }
			}
}

void
on_boutton_afficher_citoyen_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *afficher_citoyen;
	GtkWidget *espace_citoyen;

	espace_citoyen=lookup_widget(GTK_WIDGET(button),"espace_citoyen");
	afficher_citoyen=create_afficher_citoyen();

	gtk_widget_hide(espace_citoyen);
	gtk_widget_show(afficher_citoyen); 

}




void
on_button_supprimer_espace_citoyen_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *espace_citoyen;
	GtkWidget *suppressioncitoyen;

	espace_citoyen=lookup_widget(GTK_WIDGET(button),"espace_citoyen");
	suppressioncitoyen = create_suppressioncitoyen();

	gtk_widget_hide(espace_citoyen);
	gtk_widget_show(suppressioncitoyen);
}


void
on_button_modifier_espace_citoyen_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *espace_citoyen;
GtkWidget *modifiercitoyen;
espace_citoyen=lookup_widget(GTK_WIDGET(button),"espace_citoyen");
modifiercitoyen= create_modifiercitoyen();

gtk_widget_hide(espace_citoyen);
gtk_widget_show(modifiercitoyen);
}





void
on_home_supprimer_citoyen_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *espace_citoyen;
	GtkWidget *suppressioncitoyen;

	suppressioncitoyen=lookup_widget(GTK_WIDGET(button),"suppressioncitoyen");
	espace_citoyen= create_espace_citoyen();

	gtk_widget_hide(suppressioncitoyen);
	gtk_widget_show(espace_citoyen);
}


void
on_home_afficher_citoyen_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *espace_citoyen;
	GtkWidget *afficher_citoyen;

	afficher_citoyen=lookup_widget(GTK_WIDGET(button),"afficher_citoyen");
	espace_citoyen= create_espace_citoyen();

	gtk_widget_hide(afficher_citoyen);
	gtk_widget_show(espace_citoyen);
}


void
on_home_calculer_facture_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *espace_citoyen;
	GtkWidget *calculer_facture;

	calculer_facture=lookup_widget(GTK_WIDGET(button),"calculer_facture");
	espace_citoyen= create_espace_citoyen();

	gtk_widget_hide(calculer_facture);
	gtk_widget_show(espace_citoyen);
}


void
on_home_modifier_citoyen_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *espace_citoyen;
	GtkWidget *modifiercitoyen;

	modifiercitoyen=lookup_widget(GTK_WIDGET(button),"modifiercitoyen");
	espace_citoyen= create_espace_citoyen();

	gtk_widget_hide(modifiercitoyen);
	gtk_widget_show(espace_citoyen);
}


void
on_espace_calculer_facture_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *espace_citoyen;
	GtkWidget *calculer_facture;

	espace_citoyen=lookup_widget(GTK_WIDGET(button),"espace_citoyen");
	calculer_facture= create_calculer_facture();

	gtk_widget_hide(espace_citoyen);
	gtk_widget_show(calculer_facture);
}


void
on_buttonanciencitoyen_clicked         (GtkButton       *button,
                                        gpointer         user_data)

{	
	GtkWidget *admincitoyen,*logincitoyen;

	admincitoyen=lookup_widget(GTK_WIDGET(button),"admincitoyen");
	logincitoyen= create_logincitoyen();

	gtk_widget_hide(admincitoyen);
	gtk_widget_show(logincitoyen);
}


void
on_button_login_citoyen_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *login_citoyen,*mdp_citoyen,*msg_logincitoyen;
	GtkWidget *espace_citoyen,*logincitoyen;
	
	char login[50],mdp[50];
	
	login_citoyen= lookup_widget(GTK_WIDGET(button), "login_citoyen");
    	mdp_citoyen= lookup_widget(GTK_WIDGET(button), "mdp_citoyen");
	msg_logincitoyen= lookup_widget(GTK_WIDGET(button), "msg_logincitoyen");
	
	strcpy(login, gtk_entry_get_text(GTK_ENTRY(login_citoyen)));
    	strcpy(mdp, gtk_entry_get_text(GTK_ENTRY(mdp_citoyen)));
    	if (strlen(login) == 0 || strlen(mdp) == 0  )
	{
		gtk_label_set_text(GTK_LABEL(msg_logincitoyen),"veuillez remplir tout \n les champs correctement!");
	}
	
	int x=verifier_connexion( login, mdp );
	if (x==1){
		logincitoyen=lookup_widget(GTK_WIDGET(button),"logincitoyen");
		espace_citoyen= create_espace_citoyen();

		gtk_widget_hide(logincitoyen);
		gtk_widget_show(espace_citoyen);
		}
	if (x==-1){gtk_label_set_text(GTK_LABEL(msg_logincitoyen),"compte innexsistant");
	}
}


void
on_retour_init_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *admincitoyen,*logincitoyen;

	logincitoyen=lookup_widget(GTK_WIDGET(button),"logincitoyen");
	admincitoyen= create_admincitoyen();

	gtk_widget_hide(logincitoyen);
	gtk_widget_show(admincitoyen);
}


void
on_deconect_espace_citoyen_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *admincitoyen,*espace_citoyen;

	espace_citoyen=lookup_widget(GTK_WIDGET(button),"espace_citoyen");
	admincitoyen= create_admincitoyen();

	gtk_widget_hide(espace_citoyen);
	gtk_widget_show(admincitoyen);
}





void
on_cnx_loginadmin_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *loginadmin,*mdpadmin,*msg_loginadmin;
	GtkWidget *gerer,*login;
	
	char log[50],mdp[50];
	
	loginadmin= lookup_widget(GTK_WIDGET(button), "loginadmin");
    	mdpadmin= lookup_widget(GTK_WIDGET(button), "mdpadmin");
	msg_loginadmin= lookup_widget(GTK_WIDGET(button), "msg_loginadmin");
	
	strcpy(log, gtk_entry_get_text(GTK_ENTRY(loginadmin)));
    	strcpy(mdp, gtk_entry_get_text(GTK_ENTRY(mdpadmin)));
    	if (strlen(log) == 0 || strlen(mdp) == 0  )
	{
		gtk_label_set_text(GTK_LABEL(msg_loginadmin),"veuillez remplir tout \n les champs correctement!");
	}
	
	int x=verif_conx_admin( log, mdp );
	if (x==1){
		login=lookup_widget(GTK_WIDGET(button),"login");
		gerer= create_gerer();

		gtk_widget_hide(login);
		gtk_widget_show(gerer);
		}
	if (x==-1){gtk_label_set_text(GTK_LABEL(msg_loginadmin),"compte innexsistant");
	}
}



void
on_retour_admin_init_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *admincitoyen,*login;
	login=lookup_widget(GTK_WIDGET(button),"login");
	admincitoyen= create_admincitoyen();

	gtk_widget_hide(login);
	gtk_widget_show(admincitoyen);
}


void
on_button_retour_ladmincitoyen_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *admincitoyen,*gerer;
	gerer=lookup_widget(GTK_WIDGET(button),"gerer");
	admincitoyen= create_admincitoyen();

	gtk_widget_hide(gerer);
	gtk_widget_show(admincitoyen);
}


void
on_retour_ajout_citoyen_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *espace_citoyen;
	GtkWidget *ajoutclient__;

	ajoutclient__=lookup_widget(GTK_WIDGET(button),"ajoutclient__");
	espace_citoyen= create_espace_citoyen();

	gtk_widget_hide(ajoutclient__);
	gtk_widget_show(espace_citoyen);
	gtk_widget_hide(ajoutclient__);
}


void
on_dcnx_du_calcul_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *admincitoyen,*afficher_citoyen;

	afficher_citoyen=lookup_widget(GTK_WIDGET(button),"afficher_citoyen");
	admincitoyen= create_admincitoyen();

	gtk_widget_hide(afficher_citoyen);
	gtk_widget_show(admincitoyen);
}




void
on_button45_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *ajoutagent_ , *affecteragent_;

	ajoutagent_=lookup_widget(GTK_WIDGET(button),"ajoutagent_");
	affecteragent_ = create_affecteragent_ ();

	gtk_widget_hide(ajoutagent_);
	gtk_widget_show (affecteragent_);

}




void
on_boutton_calculer_fact_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *sortie_cout, *mois_facture, *annee_facture, *read_id;
    	int mois, annee;
	char *id;
    	char result[50]; 

	mois_facture = lookup_widget(GTK_WIDGET(button), "mois_facture");
	annee_facture = lookup_widget(GTK_WIDGET(button), "annee_facture");
	read_id = lookup_widget(GTK_WIDGET(button), "read_id");
	sortie_cout = lookup_widget(GTK_WIDGET(button), "sortie_cout");

	mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(mois_facture));
	annee = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(annee_facture));
	id = (char *)gtk_entry_get_text(GTK_ENTRY(read_id));

    
    	float facture = calculerFactureMensuelle(id, mois, annee);

    	if (facture == -1.0) {
        	snprintf(result, sizeof(result), "Aucune réservation trouvée !");
    			} 
	else {
        	snprintf(result, sizeof(result), "%.2f TND", facture);
	
    		}

    gtk_label_set_text(GTK_LABEL(sortie_cout), result);
}


void
on_deconect_facture_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *admincitoyen,*calculer_facture;

	calculer_facture=lookup_widget(GTK_WIDGET(button),"calculer_facture");
	admincitoyen= create_admincitoyen();

	gtk_widget_hide(calculer_facture);
	gtk_widget_show(admincitoyen);
}


void on_affiche_fact_clicked(GtkButton *button, gpointer user_data) {
	GtkWidget *read_id, *treeviewfact,*msg;
	char id[10];
	GtkTreeIter iter;
	msg= lookup_widget(GTK_WIDGET(button), "msg");
	read_id = lookup_widget(GTK_WIDGET(button), "read_id");
	if (!read_id || !GTK_IS_ENTRY(read_id)) {
	gtk_label_set_text(GTK_LABEL(msg),"invalid id");
		
	    }

	treeviewfact = lookup_widget(GTK_WIDGET(button), "treeviewfact");

	const char *id_text = gtk_entry_get_text(GTK_ENTRY(read_id));
	if (!id_text || strlen(id_text) == 0) {
	gtk_label_set_text(GTK_LABEL(msg),"invalid id");
		
	    }
	strcpy(id, id_text);
	GtkListStore *store = gtk_list_store_new(COLUMNNS, G_TYPE_STRING, G_TYPE_INT, 
G_TYPE_INT,G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING);

	    gtk_tree_view_set_model(GTK_TREE_VIEW(treeviewfact), GTK_TREE_MODEL(store));

	    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(treeviewfact)) == 0) {
		GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
		GtkTreeViewColumn *column;

		column = gtk_tree_view_column_new_with_attributes("ID Reservation", renderer, "text", IDRESERVATION, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(treeviewfact), column);

		column = gtk_tree_view_column_new_with_attributes("Mois", renderer, "text", MOIS, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(treeviewfact), column);

		column = gtk_tree_view_column_new_with_attributes("Jour", renderer, "text", JOUR, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(treeviewfact), column);

		column = gtk_tree_view_column_new_with_attributes("Annee", renderer, "text", ANNEE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(treeviewfact), column);

		column = gtk_tree_view_column_new_with_attributes("Service", renderer, "text", LIBELLE, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(treeviewfact), column);

		column = gtk_tree_view_column_new_with_attributes("Cout", renderer, "text", COUT, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(treeviewfact), column);
	    }

	    FILE *f = fopen("reservations.txt", "r");
	    if (!f) {
		g_warning("Erreur : Impossible d'ouvrir le fichier 'reservations.txt' !");
		return;
	    }

	    char id_reservation[50], idClient[50], idParking[50], nomParking[50], id_park[50], id1[50], service[50], cout[50];
	    int placesDisponibles, mois, jour, annee;

	 
	    gtk_list_store_clear(store);

	    while (fscanf(f, "%s %s %d %d %d %s %d %s %s %s %s %s \n", id_reservation, idClient, &jour, &mois, &annee, idParking, &placesDisponibles, nomParking, id_park, id1, service, cout) != EOF) {
		if (chercherreservation("reservations.txt",id)==1) { 
		    gtk_list_store_append(store, &iter);
		    gtk_list_store_set(store, &iter,IDRESERVATION, id_reservation,MOIS, mois,JOUR, jour,ANNEE, annee,LIBELLE, service,COUT, cout, -1);
		}
	    }

	    fclose(f);

	    gtk_tree_view_set_model(GTK_TREE_VIEW(treeviewfact), GTK_TREE_MODEL(store));
	    g_object_unref(store); 
	}

void on_Affiche_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *afficher_citoyen, *id_affiche, *treeview1, *output;
    char id[10];
    afficher_citoyen = lookup_widget(GTK_WIDGET(button), "afficher_citoyen");
    treeview1 = lookup_widget(afficher_citoyen, "treeview1");
    output = lookup_widget(GTK_WIDGET(button), "output");
    id_affiche = lookup_widget(GTK_WIDGET(button), "id_affiche");


    const char *id_text = gtk_entry_get_text(GTK_ENTRY(id_affiche));
    if (!id_text || strlen(id_text) == 0) {
        gtk_label_set_text(GTK_LABEL(output), "ID invalide.");
        return;
    }
    strcpy(id, id_text);

   
    GtkListStore *store = NULL;
    if (GTK_IS_TREE_VIEW(treeview1)) {
        store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(treeview1)));
    }
    if (!store) {
        store = gtk_list_store_new(6, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                   G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
        gtk_tree_view_set_model(GTK_TREE_VIEW(treeview1), GTK_TREE_MODEL(store));
    }


    if (store) {
        gtk_list_store_clear(store);
    }

    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview1)) == 0) {
        GtkCellRenderer *renderer;
        GtkTreeViewColumn *column;

        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Login", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

        column = gtk_tree_view_column_new_with_attributes("Mot de passe", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

        column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

        column = gtk_tree_view_column_new_with_attributes("Nom", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

        column = gtk_tree_view_column_new_with_attributes("Prénom", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);

        column = gtk_tree_view_column_new_with_attributes("Téléphone", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), column);
    }


    FILE *f = fopen("citoyen.txt", "r");
    if (!f) {
        gtk_label_set_text(GTK_LABEL(output), "Erreur : Impossible d'ouvrir le fichier.");
        return;
    }

    char nom[50], prenom[50], tel[30], cin[50], login[50], mdp[50];
    GtkTreeIter iter;
    int found = 0;
    while (fscanf(f, "%s %s %s %s %s %s", login, mdp, nom, prenom, cin, tel) == 6) {
        if (strcmp(id, cin) == 0) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, 0, login,1, mdp,2, cin,3, nom, 4, prenom, 5, tel,-1);
            found = 1;
        }
    }
    fclose(f);

 
    if (!found) {
        gtk_label_set_text(GTK_LABEL(output), "Aucun citoyen trouvé avec cet ID.");
    } else {
        gtk_label_set_text(GTK_LABEL(output), "Citoyen trouvé !");
    }

  
    gtk_widget_show_all(afficher_citoyen);
}

///////////////////////////////////////////////


int supp=1;
int choix[4]={0,0,0,0};
int choix2[4]={0,0,0,0};
char ch[500]="",cha[500]="";
void
on_button_GR_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *EspaceReclamation,*GestionR ;


	EspaceReclamation=lookup_widget(GTK_WIDGET(button),"EspaceReclamation");
	gtk_widget_destroy(EspaceReclamation);
	GestionR=create_GestionR();
	gtk_widget_show(GestionR); 

}


void
on_APT_clicked                         (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *Affichagelisteparking,*EspaceReclamation ;


	EspaceReclamation=lookup_widget(GTK_WIDGET(button),"EspaceReclamation");
	gtk_widget_destroy(EspaceReclamation);
	Affichagelisteparking=create_Affichagelisteparking();
	gtk_widget_show(Affichagelisteparking);
}


void
on_historique_R_row_activated          (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
	gint* recid;
	gint* jour;
	gint* mois;
	gint* annee;
	gchar* tel;
	gchar* idpark;	
	gchar* avis;
	gchar* desc;

	
	
	rec r;
	GtkTreeModel *model = gtk_tree_view_get_model (treeview) ;

	if (gtk_tree_model_get_iter(model, &iter, path) ){

		gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0, &recid, 1, &jour, 2,&mois,3,&annee,4,&tel,5,&idpark,6,&avis,7,&desc,-1);
		r.recid = recid;
		r.date.jour = jour;
		r.date.mois = mois;
		r.date.annee = annee;
		strcpy(r.tel,tel) ;
		strcpy(r.idpark,idpark);
		strcpy(r.avis,avis) ;
		strcpy(r.desc,desc) ;

		supprimer_tre(r,ch);
		afficher_rec(treeview,ch) ;
}
}


void
on_button_M_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *ModificationR,*GestionR;


	GestionR=lookup_widget(GTK_WIDGET(button),"GestionR");
	gtk_widget_destroy(GestionR);
	ModificationR=create_ModificationR();
	gtk_widget_show(ModificationR); 
}


void
on_button_Supp_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *SuppRec,*GestionR;


	GestionR=lookup_widget(GTK_WIDGET(button),"GestionR");
	gtk_widget_destroy(GestionR);
	SuppRec=create_SuppRec();
	gtk_widget_show(SuppRec); 
}


void
on_button1_hist_r_gest_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *GestionR,*historique_R;
	GestionR = lookup_widget(GTK_WIDGET(button),"GestionR");
	historique_R=lookup_widget(GestionR,"historique_R");
	 afficher_rec (historique_R,ch);
}


void
on_button_Ajouter_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *AjouterRec,*GestionR ;


	GestionR=lookup_widget(GTK_WIDGET(button),"GestionR");
	gtk_widget_destroy(GestionR);
	AjouterRec=create_AjouterRec();
	gtk_widget_show(AjouterRec); 

}


void
on_home1_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *EspaceReclamation,*GestionR ;
	GestionR=lookup_widget(GTK_WIDGET(button),"GestionR");
	gtk_widget_destroy(GestionR);
	EspaceReclamation=create_EspaceReclamation();
	gtk_widget_show(EspaceReclamation);
}


void
on_return1_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

	GtkWidget *EspaceReclamation,*GestionR ;
	GestionR=lookup_widget(GTK_WIDGET(button),"GestionR");
	gtk_widget_destroy(GestionR);
	EspaceReclamation=create_EspaceReclamation();
	gtk_widget_show(EspaceReclamation); 
}


void
on_return2_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *GestionR,*ModificationR;
	ModificationR=lookup_widget(GTK_WIDGET(button),"ModificationR");
	gtk_widget_destroy(ModificationR);
	GestionR=create_GestionR();
	gtk_widget_show(GestionR);
}


void
on_home2_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *EspaceReclamation,*ModificationR;
	ModificationR=lookup_widget(GTK_WIDGET(button),"ModificationR");
	gtk_widget_destroy(ModificationR);
	EspaceReclamation=create_EspaceReclamation();
	gtk_widget_show(EspaceReclamation); 
}


void
on_button_rmod_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *ModificationR ,*Modificationunrec;
	GtkWidget *input1, *input2;
	GtkWidget *output;
	char vide[2] = "";
	char mot1[50] = "introuvable";

	
	char tel[9];int recid;
	rec r;

	ModificationR=lookup_widget(GTK_WIDGET(button),"ModificationR");
	input1 = lookup_widget(GTK_WIDGET(button), "entry5_nM");
        input2 = lookup_widget(GTK_WIDGET(button), "spinbutton9_idMM");
	output=lookup_widget(GTK_WIDGET(button),"label257_mo");

	strcpy(tel,gtk_entry_get_text(GTK_ENTRY(input1)));
	 recid =gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (input2));

	 r = chercher("reclamations.txt", tel,recid,ch);
	if(strcmp(r.tel,"-1")!=0){
	gtk_label_set_text(GTK_LABEL(output), vide);
	add(recid,tel);
 	    Modificationunrec=create_Modificationunrec();
	    gtk_widget_show(Modificationunrec);
		gtk_widget_destroy(ModificationR);
}
   	else {   
	gtk_label_set_text(GTK_LABEL(output), mot1);
}
 }

void
on_return3_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *ModificationR,*Modificationunrec;
	Modificationunrec=lookup_widget(GTK_WIDGET(button),"Modificationunrec");
	gtk_widget_destroy(Modificationunrec);
	ModificationR=create_ModificationR();
	gtk_widget_show(ModificationR);
}


void
on_home3_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *EspaceReclamation,*Modificationunrec;
	Modificationunrec=lookup_widget(GTK_WIDGET(button),"Modificationunrec");
	gtk_widget_destroy(Modificationunrec);
	EspaceReclamation=create_EspaceReclamation();
	gtk_widget_show(EspaceReclamation); 
}



void
on_button_Cmod_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
    char vide[2] = "";
   char mot1[50] = "modifier avec succès";
   char mot2[50] = "ECHEC de modif  ";
	GtkWidget *output;
int a;
char tel[9];int recid;
rec v;
recid=pull(recid,tel[9]);

GtkWidget *input1, *input2, *input3, *input4, *input5 , *input6, *input7;
GtkWidget *GestionR,*Modificationunrec;

GtkWidget *ch1,*ch2,*ch3,*ch4;

Modificationunrec=lookup_widget(button,"Modificationunrec");

    input1 = lookup_widget(GTK_WIDGET(button), "combobox1_idM");
    input2 = lookup_widget(GTK_WIDGET(button), "entry4_nMMM");
    input3 = lookup_widget(GTK_WIDGET(button), "spinbutton5_ff");
    input4 = lookup_widget(GTK_WIDGET(button), "spinbutton6_yy");
    input5 = lookup_widget(GTK_WIDGET(button), "spinbutton9_uu");
input6 = lookup_widget(GTK_WIDGET(button), "combobox2_AMM");	
input7 = lookup_widget(GTK_WIDGET(button), "entry1_descnew");	

ch1=lookup_widget(GTK_WIDGET(button),"checkbutton1_rec_mod");
ch2=lookup_widget(GTK_WIDGET(button),"checkbutton2_rec_mod");
ch3=lookup_widget(GTK_WIDGET(button),"checkbutton3_rec_mod");
ch4=lookup_widget(GTK_WIDGET(button),"checkbutton4_rec_mod");
output = lookup_widget(GTK_WIDGET(button), "label263_confrdvmb");

	strcpy(v.desc,gtk_entry_get_text(GTK_ENTRY(input7)));
	v.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (input3));
	v.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (input4));
	v.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (input5));
	strcpy(v.avis,gtk_combo_box_get_active_text(GTK_COMBO_BOX (input6)));
	strcpy(v.idpark,gtk_combo_box_get_active_text(GTK_COMBO_BOX (input1)));
	strcpy(v.tel,gtk_entry_get_text(GTK_ENTRY(input2)));



         a=modifier("reclamations.txt", tel,recid,v,cha,ch,choix2);
       if(a==1){
	afficherListeTrieeParAvis("reclamations.txt");
    choix2[0]=0;
    choix2[1]=0;
    choix2[2]=0;
    choix2[3]=0;
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(input4), 1);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(input5), 1);
        gtk_spin_button_set_value(GTK_SPIN_BUTTON(input3), 1);
                gtk_entry_set_text(GTK_ENTRY(input7), vide);
                gtk_combo_box_set_active(GTK_COMBO_BOX (input1),0);
                gtk_combo_box_set_active(GTK_COMBO_BOX (input6),0);
                gtk_entry_set_text(GTK_ENTRY(input2), vide);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ch1),FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ch2),FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ch3),FALSE);
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ch4),FALSE);
        gtk_label_set_text(GTK_LABEL(output), mot1); 
    }
	else { 
		gtk_label_set_text(GTK_LABEL(output), mot2); 
}
		

}


void
on_checkbutton2_rdv_mod_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)){
choix2[1]=1;
}
}


void
on_checkbutton1_rdv_mod_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)){
choix2[0]=1;
}
}


void
on_home4_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *EspaceReclamation,*AjouterRec;
	AjouterRec=lookup_widget(GTK_WIDGET(button),"AjouterRec");
	gtk_widget_destroy(AjouterRec);
	EspaceReclamation=create_EspaceReclamation();
	gtk_widget_show(EspaceReclamation);
}


void
on_return4_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *GestionR,*AjouterRec;
	AjouterRec=lookup_widget(GTK_WIDGET(button),"AjouterRec");
	gtk_widget_destroy(AjouterRec);
	GestionR=create_GestionR();
	gtk_widget_show(GestionR); 
}


void
on_button_A_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
 
	 char vide[2] = "";
	char mot1[50] = "Ajout avec succès";
   	 char mot2[50] = "ECHEC d'ajout  ";
	GtkWidget *output;
	GtkWidget *ch1,*ch2,*ch3,*ch4;


	ch1=lookup_widget(GTK_WIDGET(button),"checkbutton5_rec_A");
	ch2=lookup_widget(GTK_WIDGET(button),"checkbutton6_rec_A");
	ch3=lookup_widget(GTK_WIDGET(button),"checkbutton7_rec_A");
	ch4=lookup_widget(GTK_WIDGET(button),"checkbutton8_rec_A");
	output = lookup_widget(GTK_WIDGET(button), "label256");

    int a;
    rec v;
    GtkWidget *input1, *input2, *input3, *input4, *input5, *input6 ,*input7 ;
    GtkWidget *AjouterRec;

    AjouterRec = lookup_widget(GTK_WIDGET(button), "AjouterRec");
    input1 = lookup_widget(GTK_WIDGET(button), "combobox1_Areclamation");
    input2 = lookup_widget(GTK_WIDGET(button), "entry2");
    input3 = lookup_widget(GTK_WIDGET(button), "spinbutton3");
    input4 = lookup_widget(GTK_WIDGET(button), "spinbutton4");
    input5 = lookup_widget(GTK_WIDGET(button), "spinbutton_Areclamation");
    input6 = lookup_widget(GTK_WIDGET(button), "combobox2_reclamationA");
    input7 = lookup_widget(GTK_WIDGET(button), "entry_descA");
	

	strcpy(v.desc,gtk_entry_get_text(GTK_ENTRY(input7)));
	v.date.jour=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (input3));
	v.date.mois=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (input4));
	v.date.annee=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON (input5));
	strcpy(v.avis,gtk_combo_box_get_active_text(GTK_COMBO_BOX (input1)));
	strcpy(v.idpark,gtk_combo_box_get_active_text(GTK_COMBO_BOX (input6)));
	strcpy(v.tel,gtk_entry_get_text(GTK_ENTRY(input2)));


     		a=ajouter("reclamations.txt", v,choix,ch);
		   if(a==1){
	afficherListeTrieeParAvis("reclamations.txt");
		choix[0]=0;
		choix[1]=0;
		choix[2]=0;
		choix[3]=0;
		    gtk_spin_button_set_value(GTK_SPIN_BUTTON(input4), 1);
		    gtk_spin_button_set_value(GTK_SPIN_BUTTON(input5), 1);
		    gtk_spin_button_set_value(GTK_SPIN_BUTTON(input3), 1);
                    gtk_entry_set_text(GTK_ENTRY(input7), vide);
                    gtk_combo_box_set_active(GTK_COMBO_BOX (input1),0);
                    gtk_combo_box_set_active(GTK_COMBO_BOX (input6),0);
                    gtk_entry_set_text(GTK_ENTRY(input2), vide);
		    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ch1),FALSE);
		    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ch2),FALSE);
		    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ch3),FALSE);
		    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ch4),FALSE);
   			gtk_label_set_text(GTK_LABEL(output), mot1);
		      }
	else { 
		gtk_label_set_text(GTK_LABEL(output), mot2); 
}
}


void
on_home5_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *EspaceReclamation,*SuppRec;
	SuppRec=lookup_widget(GTK_WIDGET(button),"SuppRec");
	gtk_widget_destroy(SuppRec);
	EspaceReclamation=create_EspaceReclamation();
	gtk_widget_show(EspaceReclamation); 
}


void
on_return5_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

	GtkWidget *GestionR,*SuppRec;
	SuppRec=lookup_widget(GTK_WIDGET(button),"SuppRec");
	gtk_widget_destroy(SuppRec);
	GestionR=create_GestionR();
	gtk_widget_show(GestionR);
}


void
on_button_supp1_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{

    char mot1[55] = "introuvable";
char vide[2] = "";
rec r;
char tel[9];int recid;
GtkWidget *input1,*input2;
GtkWidget*output;
GtkWidget *AssurerSuppRec;
GtkWidget *SuppRec;

SuppRec=lookup_widget(GTK_WIDGET(button),"SuppRec");
input1=lookup_widget(GTK_WIDGET(button),"entry3_teltel");
    input2 = lookup_widget(GTK_WIDGET(button), "spinbutton8_oo");
output=lookup_widget(GTK_WIDGET(button),"label259_supp");



strcpy(tel,gtk_entry_get_text(GTK_ENTRY(input1)));
 recid = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (input2));
 r = chercher("reclamations.txt", tel,recid,ch);
if(strcmp(r.tel,"-1")!=0){
     AssurerSuppRec=create_AssurerSuppRec();
    gtk_widget_show(AssurerSuppRec);
add(recid,tel);

}
	 else {
		gtk_label_set_text(GTK_LABEL(output), mot1);
}
}


void
on_return6_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *AssurerSuppRec,*SuppRec;
	AssurerSuppRec=lookup_widget(GTK_WIDGET(button),"AssurerSuppRec");
	gtk_widget_destroy(AssurerSuppRec);
	SuppRec=create_SuppRec();
	gtk_widget_show(SuppRec); 
}


void
on_radiobutton_A_toggled               (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))){
supp = 2;
}
}


void
on_radiobutton_supp_toggled            (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(GTK_RADIO_BUTTON(togglebutton))){
supp = 1;
}
}


void
on_home6_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *AssurerSuppRec,*EspaceReclamation;
	AssurerSuppRec=lookup_widget(GTK_WIDGET(button),"AssurerSuppRec");
	gtk_widget_destroy(AssurerSuppRec);
	EspaceReclamation=create_EspaceReclamation();
	gtk_widget_show(EspaceReclamation);
}


void
on_treeview1_tree_don_cin_row_activated
                                        (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
GtkTreeIter iter;
	
	gchar* idpark;	
	gchar* avis;
	
	rec r;
	GtkTreeModel *model = gtk_tree_view_get_model (treeview) ;

	if (gtk_tree_model_get_iter(model, &iter, path) ){

		gtk_tree_model_get(GTK_LIST_STORE(model), &iter, 0,&idpark,1,&avis,-1);
		
		strcpy(r.idpark,idpark);
		strcpy(r.avis,avis) ;
		supprimer_tretree(r);
		afficher_rectree(treeview) ;
}
}


void
on_return7_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
  	GtkWidget *Affichagelisteparking,*EspaceReclamation ;
	Affichagelisteparking=lookup_widget(GTK_WIDGET(button),"Affichagelisteparking");
	gtk_widget_destroy(Affichagelisteparking);
	EspaceReclamation=create_EspaceReclamation();
	gtk_widget_show(EspaceReclamation);
}


void
on_home7_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *Affichagelisteparking,*EspaceReclamation ;
	Affichagelisteparking=lookup_widget(GTK_WIDGET(button),"Affichagelisteparking");
	gtk_widget_destroy(Affichagelisteparking);
	EspaceReclamation=create_EspaceReclamation();
	gtk_widget_show(EspaceReclamation);
}


void
on_checkbutton5_rec_A_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)){
choix[0]=1;
}
}


void
on_checkbutton7_rec_A_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)){
choix[1]=1;
}
}


void
on_checkbutton6_rec_A_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)){
choix[2]=1;
}
}


void
on_checkbutton8_rec_A_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)){
choix[3]=1;
}
}


void
on_checkbutton3_rec_mod_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)){
choix2[2]=1;}
}


void
on_checkbutton4_rec_mod_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
if(gtk_toggle_button_get_active(togglebutton)){
choix2[3]=1;}
}


void
on_button52_bb_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
         
	GtkWidget *AssurerSuppRec;
	GtkWidget *SuppRec;
	char tel[9];int recid;
	recid=pull(recid,tel[9]);
	if(supp==1){
	supprimer("reclamations.txt",tel[9],recid,ch);}
	AssurerSuppRec=lookup_widget(GTK_WIDGET(button),"AssurerSuppRec");
	gtk_widget_destroy(AssurerSuppRec);
	supp =1;

}


void
on_affichertrec_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *Affichagelisteparking,*treeview1_tree_par_tri;
	Affichagelisteparking = lookup_widget(GTK_WIDGET(button),"Affichagelisteparking");
	treeview1_tree_par_tri=lookup_widget(Affichagelisteparking,"treeview1_tree_par_tri");
	 afficher_rectree (treeview1_tree_par_tri);
}


void
on_button46_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *espace_citoyen , *EspaceReclamation;
espace_citoyen=lookup_widget(GTK_WIDGET(button),"espace_citoyen");
 EspaceReclamation= create_EspaceReclamation ();
gtk_widget_hide(espace_citoyen);
 gtk_widget_show (EspaceReclamation);
}


void
on_affecter_precedent_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_affecter_acceuil_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}
gboolean is_checked;
void
on_button_ajout_service_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{

GtkWidget *entrer_id_parking, *entrer_id_service, *libelle_ajout, *service_cout , *labelhsortie;
char id_park[10],id[10], libelle[50], cout[04] , c_str[10];
const gchar *lib;
int c;


entrer_id_parking = lookup_widget(GTK_WIDGET(button), "entrer_id_parking");
entrer_id_service = lookup_widget(GTK_WIDGET(button), "entrer_id_service");
libelle_ajout = lookup_widget(GTK_WIDGET(button), "libelle_ajout");
service_cout = lookup_widget(GTK_WIDGET(button), "service_cout");
labelhsortie= lookup_widget(GTK_WIDGET(button), "labelhsortie");
lib= gtk_combo_box_get_active_text(GTK_COMBO_BOX(libelle_ajout));

c= gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(service_cout));
sprintf(c_str, "%d", c);

strcpy(id_park,gtk_entry_get_text(GTK_ENTRY(entrer_id_parking)));
strcpy(id,gtk_entry_get_text(GTK_ENTRY(entrer_id_service)));
strcpy(libelle,lib);
strcpy(cout,c_str);

if (is_checked){
serviceh service;
strcpy(service.id_park,id_park);
strcpy(service.id,id);
strcpy(service.libelle,libelle);
strcpy(service.cout,cout);


ajouter_services( service );
gtk_label_set_text(GTK_LABEL(labelhsortie), "Service ajouté avec succés ");
}
}


void
on_button_supp_service__clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *entrer_id_park_supprimer, *entrer_id_supprimer;
char id_park[10],id[10];


entrer_id_park_supprimer=lookup_widget(GTK_WIDGET(button),"entrer_id_park_supprimer");
entrer_id_supprimer=lookup_widget(GTK_WIDGET(button),"entrer_id_supprimer");

strcpy(id_park,gtk_entry_get_text(GTK_ENTRY(entrer_id_park_supprimer)));
strcpy(id,gtk_entry_get_text(GTK_ENTRY(entrer_id_supprimer)));



int i =supprimer_services(id,id_park);
}


void
on_button_modifier_service_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *entrer_id_park_modification, *entrer_id_modification, *entrer_libelle_modification, *entrer_cout_modification;
char id_park[10],id[10], libelle[50], cout[04];


entrer_id_park_modification=lookup_widget(GTK_WIDGET(button),"entrer_id_park_modification");
entrer_id_modification=lookup_widget(GTK_WIDGET(button),"entrer_id_modification");
entrer_libelle_modification=lookup_widget(GTK_WIDGET(button),"entrer_libelle_modification");
entrer_cout_modification=lookup_widget(GTK_WIDGET(button),"entrer_cout_modification");

strcpy(id_park,gtk_entry_get_text(GTK_ENTRY(entrer_id_park_modification)));
strcpy(id,gtk_entry_get_text(GTK_ENTRY(entrer_id_modification)));
strcpy(libelle,gtk_entry_get_text(GTK_ENTRY(entrer_libelle_modification)));
strcpy(cout,gtk_entry_get_text(GTK_ENTRY(entrer_cout_modification)));

serviceh service;
strcpy(service.id_park , id_park);
strcpy(service.id , id);
strcpy(service.libelle , libelle);
strcpy(service.cout , cout);


modifier_services( service , id , id_park  );
}


void
on_final_chek_ajout_service_toggled    (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 is_checked = gtk_toggle_button_get_active(togglebutton);

}


void
on_button_ajouter_service_clicked (GtkButton *button,
                                   gpointer  user_data)
{
    GtkWidget *ajout, *gerer;

    gerer = lookup_widget(GTK_WIDGET(button), "gerer_service");
    
    gtk_widget_hide(gerer);
    
    ajout = create_ajouter_service();
    
    gtk_widget_show(ajout);
}



void
on_button_supprimer_service_clicked    (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *supp, *gerer;

    gerer = lookup_widget(GTK_WIDGET(button), "gerer_service");
    
    gtk_widget_hide(gerer);
   
    supp = create_supprimer_service();
    
    gtk_widget_show(supp);

}


void
on_button_mod_service_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *mod, *gerer;

    gerer = lookup_widget(GTK_WIDGET(button), "gerer_service");
    
    gtk_widget_hide(gerer); 

    mod = create_modifier_services ();  

    gtk_widget_show(mod);

}


void
on_buttonservice_retour_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *ajout, *gerer;

    ajout = lookup_widget(GTK_WIDGET(button), "ajouter_service");
    
    gtk_widget_hide(ajout);
    
    gerer = create_gerer_service();
    
    gtk_widget_show(gerer);
}


void
on_buttonservice_supp_retour_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *supp, *gerer;

    supp = lookup_widget(GTK_WIDGET(button), "supprimer_service");
    
    gtk_widget_hide(supp);
    

    gerer = create_gerer_service();
    

    gtk_widget_show(gerer);
}


void
on_buttonservie_modif_retour_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *mod, *gerer;

    mod = lookup_widget(GTK_WIDGET(button), "modifier_services");
    
    gtk_widget_hide(mod);
    
    gerer = create_gerer_service();
    
    gtk_widget_show(gerer);
}


void
on_connect_button_home_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *conn, *home;

    home = lookup_widget(GTK_WIDGET(button), "home");
    
    gtk_widget_hide(home);

    conn = create_login();
    
    gtk_widget_show(conn);

}


void
on_button_connect_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *entrerid , *entrermdp;
char log[10],mdp[10];


entrerid=lookup_widget(GTK_WIDGET(button),"entrerid");
entrermdp=lookup_widget(GTK_WIDGET(button),"entrermdp");

strcpy(log,gtk_entry_get_text(GTK_ENTRY(entrerid)));
strcpy(mdp,gtk_entry_get_text(GTK_ENTRY(entrermdp)));


	if( verifier_connexion(log, mdp)==1 )
	{
		GtkWidget *conn, *gerer;

		conn = lookup_widget(GTK_WIDGET(button), "login");
		    
		gtk_widget_hide(conn);
		    
		gerer = create_gerer();
		    
		gtk_widget_show(gerer);

	}

}

void
on_buttonservice_gerer_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *gerer_ser, *gerer;

    gerer = lookup_widget(GTK_WIDGET(button), "gerer");
    
    gtk_widget_hide(gerer);
    
    gerer_ser = create_gerer_service();
    
    gtk_widget_show(gerer_ser);

}


void
on_button_retour_to_login_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *conn, *gerer;

    gerer = lookup_widget(GTK_WIDGET(button), "gerer");
    
    gtk_widget_hide(gerer);   

    conn = create_login();
    
    gtk_widget_show(conn);

}



void
on_button_acceuil_getion_service_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *gerer_service, *admincitoyen;

    gerer_service = lookup_widget(GTK_WIDGET(button), "gerer_service");
    
    gtk_widget_hide(gerer_service);
    
    admincitoyen = create_admincitoyen();   

    gtk_widget_show(admincitoyen);
}


void
on_button_ajout_to_acceui_clicked      (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *ajouter_service, *gerer;

    ajouter_service = lookup_widget(GTK_WIDGET(button), "ajouter_service");
    
    gtk_widget_hide(ajouter_service);
   
    gerer = create_gerer();  

    gtk_widget_show(gerer);
}


void
on_button_suppresion_to_acceuil_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *supprimer_service, *gerer;

    supprimer_service = lookup_widget(GTK_WIDGET(button), "supprimer_service");
    
    gtk_widget_hide(supprimer_service);  

    gerer = create_gerer();    

    gtk_widget_show(gerer);
}


void
on_button_modification_to_acceuil_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *modifier_services, *gerer;

    modifier_services = lookup_widget(GTK_WIDGET(button), "modifier_services");
    
    gtk_widget_hide(modifier_services);
    
    gerer = create_gerer();

    gtk_widget_show(gerer);
}


void
on_button_precedent_gestion_service_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *gerer_ser, *gerer;

    gerer_ser = lookup_widget(GTK_WIDGET(button), "gerer_service");
    
    gtk_widget_hide(gerer_ser);
    

    gerer = create_gerer();
    

    gtk_widget_show(gerer);
}


void
on_bouton_precdent_affichage_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *afficher_service, *gerer;

    afficher_service = lookup_widget(GTK_WIDGET(button), "afficher__service");
    
    gtk_widget_hide(afficher_service);

    gerer = create_gerer_service();
    
    gtk_widget_show(gerer);
}

void
on_bouton_home_affichage_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *afficher_service, *gerer;

    afficher_service = lookup_widget(GTK_WIDGET(button), "afficher__service");
    
    gtk_widget_hide(afficher_service);
    
    gerer = create_gerer();
    
    gtk_widget_show(gerer);
}


void
on_button_afficher_service_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{

	GtkWidget *gerer_ser, *afficher;
	GtkWidget *treeviewhoussem;

    gerer_ser = lookup_widget(GTK_WIDGET(button), "gerer_service");
    
    gtk_widget_hide(gerer_ser);

    afficher = create_afficher__service();   

    gtk_widget_show(afficher);

    

    treeviewhoussem = lookup_widget(afficher, "treeviewhoussem");

    afficher_ser(treeviewhoussem);
}

void
on_button_affecter_reservation_clicked (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *id_service_affectation, *id_reservation_affectation;

char id_service[10],id_reservation[10];



id_service_affectation = lookup_widget(GTK_WIDGET(button), "id_service_affectation");
id_reservation_affectation = lookup_widget(GTK_WIDGET(button), "id_reservation_affectation");

strcpy(id_service,gtk_entry_get_text(GTK_ENTRY(id_service_affectation)));
strcpy(id_reservation,gtk_entry_get_text(GTK_ENTRY(id_reservation_affectation)));


affecter_service(id_service,id_reservation);
}

void
on_bouton_affecter_service_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *affecter_service, *gerer;

    gerer = lookup_widget(GTK_WIDGET(button), "gerer_service");
    
    gtk_widget_hide(gerer);
    
    affecter_service = create_affecter_service();
    
    gtk_widget_show(affecter_service);

}


void
on_affecter_precedent_h_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *affecter_service, *gerer_service;

    affecter_service = lookup_widget(GTK_WIDGET(button), "affecter_service");
    
    gtk_widget_hide(affecter_service);
    
    gerer_service = create_gerer_service();
    
    gtk_widget_show(gerer_service);
}


void
on_affecter_acceuil_h_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
    GtkWidget *affecter_service, *gerer;

    affecter_service = lookup_widget(GTK_WIDGET(button), "affecter_service");
    
    gtk_widget_hide(affecter_service);
    
    gerer = create_gerer();
    
    gtk_widget_show(gerer);
}


void
on_buttonservice_gerer_h_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
GtkWidget *gerer , *gerer_service;
gerer=lookup_widget(GTK_WIDGET(button),"gerer");
 gerer_service= create_gerer_service ();
gtk_widget_hide(gerer);
 gtk_widget_show (gerer_service);
}


