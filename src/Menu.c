#include "../include/Menu.h"

void DrawMenu(int menu,GLuint textureID[10],int windowWidth, int windowHeight){
	int r1,r2,r3,v1,v2,v3,b1,b2,b3;
	//carrée pour tout effacer 
	dessinCarre(1, 255,  255, 255 , -500, -500.,5000., 5000. );
	if(menu==0||menu==11){
		r1=0;
		v1=0;
		b1=0;

		r2=200;
		v2=200;
		b2=200;

		r3=200;
		v3=200;
		b3=200;
	}
	if(menu==1||menu==12){
		r1=200;
		v1=200;
		b1=200;

		r2=0;
		v2=0;
		b2=0;

		r3=200;
		v3=200;
		b3=200;
	}

		if(menu==2||menu == 13){
		r1=200;
		v1=200;
		b1=200;

		r2=200;
		v2=200;
		b2=200;

		r3=0;
		v3=0;
		b3=0;
	}
	dessinCarre(0, r1,  v1, b1 , -130., -40.,80., 80. );
	dessinCarre(0, r2,  v2, b2 , -40., -40.,80., 80. );
	dessinCarre(0, r3,  v3, b3 , 50., -40.,80, 80 );
		if(menu<5){
		
		//CASE 1//

		//P//
		dessinCarre(1,r1,v1,b1,-122,-60+52,3,18);
		dessinCarre(1,r1,v1,b1,-119,-60+58,6,3);
		dessinCarre(1,r1,v1,b1,-119,-60+67,6,3);
		dessinCarre(1,r1,v1,b1,-113,-60+61,3,6);
		//L//
		dessinCarre(1,r1,v1,b1,-104,-60+52,3,18);
		dessinCarre(1,r1,v1,b1,-101,-60+52,9,3);
		//A//
		dessinCarre(1,r1,v1,b1,-86,-60+52,3,18);
		dessinCarre(1,r1,v1,b1,-83,-60+67,6,3);
		dessinCarre(1,r1,v1,b1,-83,-60+58,6,3);
		dessinCarre(1,r1,v1,b1,-78,-60+52,3,18);
		//Y//
		dessinCarre(1,r1,v1,b1,-69,-60+67,3,3);
		dessinCarre(1,r1,v1,b1,-66.5,-60+64,3,3);
		dessinCarre(1,r1,v1,b1,-63.5,-60+64,3,3);
		dessinCarre(1,r1,v1,b1,-62,-60+67,3,3);
		dessinCarre(1,r1,v1,b1,-65,-60+52,3,12);
	

		//CASE 2//
	

		//L//
		dessinCarre(1,r2,v2,b2,-39,-60+52,3,18);
		dessinCarre(1,r2,v2,b2,-36,-60+52,9,3);
		//E//
		dessinCarre(1,r2,v2,b2,-26,-60+52,3,18);
		dessinCarre(1,r2,v2,b2,-23,-60+52,9,3);
		dessinCarre(1,r2,v2,b2,-23,-60+67,9,3);
		dessinCarre(1,r2,v2,b2,-23,-60+59.5,6,3);
		//V//
		dessinCarre(1,r2,v2,b2,-13,-60+58,3,12);
		dessinCarre(1,r2,v2,b2,-11.5,-60+55,3,3);
		dessinCarre(1,r2,v2,b2,-8.5,-60+52,3,3);
		dessinCarre(1,r2,v2,b2,-5.5,-60+55,3,3);
		dessinCarre(1,r2,v2,b2,-4,-60+58,3,12);
		//E//
		dessinCarre(1,r2,v2,b2,0,-60+52,3,18);
		dessinCarre(1,r2,v2,b2,3,-60+52,9,3);
		dessinCarre(1,r2,v2,b2,3,-60+67,9,3);
		dessinCarre(1,r2,v2,b2,3,-60+59.5,6,3);
		//L//
		dessinCarre(1,r2,v2,b2,13,-60+52,3,18);
		dessinCarre(1,r2,v2,b2,16,-60+52,9,3);

		//S//
		dessinCarre(1,r2,v2,b2,26,-60+52,12,3);
		dessinCarre(1,r2,v2,b2,35,-60+55,3,4.5);
		dessinCarre(1,r2,v2,b2,26,-60+59.5,12,3);
		dessinCarre(1,r2,v2,b2,26,-60+62.5,3,4.5);
		dessinCarre(1,r2,v2,b2,26,-60+67,12,3);

	
		//CASE 3//

		//C//
		dessinCarre(1,r3,v3,b3,51,-60+58,3,6);
		dessinCarre(1,r3,v3,b3,54,-60+55,3,3);
		dessinCarre(1,r3,v3,b3,54,-60+64,3,3);
		dessinCarre(1,r3,v3,b3,57,-60+67,6,3);
		dessinCarre(1,r3,v3,b3,57,-60+52,6,3);
		//R//
		dessinCarre(1,r3,v3,b3,64,-60+52,3,18);
		dessinCarre(1,r3,v3,b3,67,-60+67,6,3);
		dessinCarre(1,r3,v3,b3,67,-60+58,6,3);
		dessinCarre(1,r3,v3,b3,73,-60+61,3,6);
		dessinCarre(1,r3,v3,b3,73,-60+52,3,6);
		//E//
		dessinCarre(1,r3,v3,b3,77,-60+52,3,18);
		dessinCarre(1,r3,v3,b3,80,-60+52,9,3);
		dessinCarre(1,r3,v3,b3,80,-60+67,9,3);
		dessinCarre(1,r3,v3,b3,80,-60+59.5,6,3);
		//D//
		dessinCarre(1,r3,v3,b3,90,-60+52,3,18);
		dessinCarre(1,r3,v3,b3,93,-60+52,3,3);
		dessinCarre(1,r3,v3,b3,96,-60+55,3,3);
		dessinCarre(1,r3,v3,b3,99,-60+58,3,6);
		dessinCarre(1,r3,v3,b3,96,-60+64,3,3);
		dessinCarre(1,r3,v3,b3,93,-60+67,3,3);
		//I//
		dessinCarre(1,r3,v3,b3,103,-60+67,12,3);
		dessinCarre(1,r3,v3,b3,103,-60+52,12,3);
		dessinCarre(1,r3,v3,b3,107.5,-60+55,3,12);
		//T//
		dessinCarre(1,r3,v3,b3,116,-60+67,12,3);
		dessinCarre(1,r3,v3,b3,120.5,-60+52,3,18);
	}
	else
	{

		//CASE 1//
		dessinCarre(1,r1,v1,b1,-110,-30,40,10);
		dessinCarre(1,r1,v1,b1,-90,-20,10,50);
		dessinCarre(1,r1,v1,b1,-110,0,10,10);
		dessinCarre(1,r1,v1,b1,-100,10,10,10);

		//case 2//
		dessinCarre(1,r2,v2,b2,-20,-30,40,10);
		dessinCarre(1,r2,v2,b2,-20,-20,10,10);
		dessinCarre(1,r2,v2,b2,-10,-10,20,10);
		dessinCarre(1,r2,v2,b2,10,0,10,20);
		dessinCarre(1,r2,v2,b2,-20,10,10,10);
		dessinCarre(1,r2,v2,b2,-10,20,20,10);

		//case 3//
		dessinCarre(1,r3,v3,b3,80,-30,20,10);
		dessinCarre(1,r3,v3,b3,70,-20,10,10);
		dessinCarre(1,r3,v3,b3,100,-20,10,15);
		dessinCarre(1,r3,v3,b3,100,5,10,15);
		dessinCarre(1,r3,v3,b3,80,20,20,10);
		dessinCarre(1,r3,v3,b3,70,10,10,10);
		dessinCarre(1,r3,v3,b3,80,-5,20,10);
	}


	//Image "HENRY WAS ALONE"
	glEnable(GL_TEXTURE_2D);
    // FIXME : Bind texture
    /* Dessin du quad */
    glColor3ub(50,50,50);
    glBindTexture(GL_TEXTURE_2D, 2);
    glBegin(GL_QUADS);
      glColor3f(1,1,1);

      glTexCoord2f(0, 1);
      glVertex2f(-75, 50);

      glTexCoord2f(1, 1);
      glVertex2f(75, 50);

      glTexCoord2f(1, 0);
      glVertex2f(75, 90);

      glTexCoord2f(0, 0);
      glVertex2f(-75, 90);

    glEnd();


  glBindTexture(GL_TEXTURE_2D, 0);

  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
    // FIXME : Bind texture
    /* Dessin du quad */
    glColor3ub(50,50,50);
    glBindTexture(GL_TEXTURE_2D, 3);
    glBegin(GL_QUADS);
      glColor3f(1,1,1);

      glTexCoord2f(0, 0);
      glVertex2f(-110, -40);

      glTexCoord2f(1, 0);
      glVertex2f(110, -40);

      glTexCoord2f(1, 1);
      glVertex2f(110, -100);

      glTexCoord2f(0,1);
      glVertex2f(-110, -100);

    glEnd();


  glBindTexture(GL_TEXTURE_2D, 0);

  glDisable(GL_TEXTURE_2D);


}		

