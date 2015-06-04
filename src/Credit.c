#include "Credit.h"

void DessinPersoPluie(int nb_perso,int nb_pluie, int currentPerso,Personnage tabPerso[],Bloc tabPluie[]){
	int i=0;
	for(i=0; i < nb_perso; i++)
	        if (i==currentPerso)
	        {
	          DessinPersonnageCarre(tabPerso[i]);
	        }
	        
	        for (i = 0; i < nb_pluie;i++)
	        {
	          DessinBlocCarre(tabPluie[i],1);
	          tabPluie[i].position.y-=5;
	          if (tabPluie[i].position.y<-200)
	          {
	            tabPluie[i].position.y=200;
	          }
	        }
}	        

void MooveYeuxTotoro(int right, int left,float *yt, float *xt, Personnage tabPerso[])
{


 if(right==1&&tabPerso[0].position.x<86&&tabPerso[0].position.x>-36)
          {
            *yt +=0.033;
            *xt +=0.015;
          
          }
        if(left==1&&tabPerso[0].position.x<86&&tabPerso[0].position.x>-36)
          {
            *yt -=0.033;
            *xt -=0.015;
          }  
        
     
      
}        

void DessinYeuxTotoro(float yt, float xt)
{
		glColor3f(0,0,0);
        glTranslatef(yt + 23.8,-12.5,0.);
        dessinCercle(10000,1);

        glTranslatef(xt+15.5,0.5,0.);
        dessinCercle(500,1);

}