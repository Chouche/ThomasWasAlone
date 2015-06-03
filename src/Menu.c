#include "../include/Menu.h"

void DrawMenu(int menu,GLuint textureID[10]){
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
		dessinCarre(1,r1,v1,b1,-122,-34+52,3,18);
		dessinCarre(1,r1,v1,b1,-119,-34+58,6,3);
		dessinCarre(1,r1,v1,b1,-119,-34+67,6,3);
		dessinCarre(1,r1,v1,b1,-113,-34+61,3,6);
		//L//
		dessinCarre(1,r1,v1,b1,-104,-34+52,3,18);
		dessinCarre(1,r1,v1,b1,-101,-34+52,9,3);
		//A//
		dessinCarre(1,r1,v1,b1,-86,-34+52,3,18);
		dessinCarre(1,r1,v1,b1,-83,-34+67,6,3);
		dessinCarre(1,r1,v1,b1,-83,-34+58,6,3);
		dessinCarre(1,r1,v1,b1,-78,-34+52,3,18);
		//Y//
		dessinCarre(1,r1,v1,b1,-69,-34+67,3,3);
		dessinCarre(1,r1,v1,b1,-66.5,-34+64,3,3);
		dessinCarre(1,r1,v1,b1,-63.5,-34+64,3,3);
		dessinCarre(1,r1,v1,b1,-62,-34+67,3,3);
		dessinCarre(1,r1,v1,b1,-65,-34+52,3,12);
	

		//CASE 2//
	

		//L//
		dessinCarre(1,r2,v2,b2,-39,-34+52,3,18);
		dessinCarre(1,r2,v2,b2,-36,-34+52,9,3);
		//E//
		dessinCarre(1,r2,v2,b2,-26,-34+52,3,18);
		dessinCarre(1,r2,v2,b2,-23,-34+52,9,3);
		dessinCarre(1,r2,v2,b2,-23,-34+67,9,3);
		dessinCarre(1,r2,v2,b2,-23,-34+59.5,6,3);
		//V//
		dessinCarre(1,r2,v2,b2,-13,-34+58,3,12);
		dessinCarre(1,r2,v2,b2,-11.5,-34+55,3,3);
		dessinCarre(1,r2,v2,b2,-8.5,-34+52,3,3);
		dessinCarre(1,r2,v2,b2,-5.5,-34+55,3,3);
		dessinCarre(1,r2,v2,b2,-4,-34+58,3,12);
		//E//
		dessinCarre(1,r2,v2,b2,0,-34+52,3,18);
		dessinCarre(1,r2,v2,b2,3,-34+52,9,3);
		dessinCarre(1,r2,v2,b2,3,-34+67,9,3);
		dessinCarre(1,r2,v2,b2,3,-34+59.5,6,3);
		//L//
		dessinCarre(1,r2,v2,b2,13,-34+52,3,18);
		dessinCarre(1,r2,v2,b2,16,-34+52,9,3);

		//S//
		dessinCarre(1,r2,v2,b2,26,-34+52,12,3);
		dessinCarre(1,r2,v2,b2,35,-34+55,3,4.5);
		dessinCarre(1,r2,v2,b2,26,-34+59.5,12,3);
		dessinCarre(1,r2,v2,b2,26,-34+62.5,3,4.5);
		dessinCarre(1,r2,v2,b2,26,-34+67,12,3);

	
		//CASE 3//

		//C//
		dessinCarre(1,r3,v3,b3,51,-34+58,3,6);
		dessinCarre(1,r3,v3,b3,54,-34+55,3,3);
		dessinCarre(1,r3,v3,b3,54,-34+64,3,3);
		dessinCarre(1,r3,v3,b3,57,-34+67,6,3);
		dessinCarre(1,r3,v3,b3,57,-34+52,6,3);
		//R//
		dessinCarre(1,r3,v3,b3,64,-34+52,3,18);
		dessinCarre(1,r3,v3,b3,67,-34+67,6,3);
		dessinCarre(1,r3,v3,b3,67,-34+58,6,3);
		dessinCarre(1,r3,v3,b3,73,-34+61,3,6);
		dessinCarre(1,r3,v3,b3,73,-34+52,3,6);
		//E//
		dessinCarre(1,r3,v3,b3,77,-34+52,3,18);
		dessinCarre(1,r3,v3,b3,80,-34+52,9,3);
		dessinCarre(1,r3,v3,b3,80,-34+67,9,3);
		dessinCarre(1,r3,v3,b3,80,-34+59.5,6,3);
		//D//
		dessinCarre(1,r3,v3,b3,90,-34+52,3,18);
		dessinCarre(1,r3,v3,b3,93,-34+52,3,3);
		dessinCarre(1,r3,v3,b3,96,-34+55,3,3);
		dessinCarre(1,r3,v3,b3,99,-34+58,3,6);
		dessinCarre(1,r3,v3,b3,96,-34+64,3,3);
		dessinCarre(1,r3,v3,b3,93,-34+67,3,3);
		//I//
		dessinCarre(1,r3,v3,b3,103,-34+67,12,3);
		dessinCarre(1,r3,v3,b3,103,-34+52,12,3);
		dessinCarre(1,r3,v3,b3,107.5,-34+55,3,12);
		//T//
		dessinCarre(1,r3,v3,b3,116,-34+67,12,3);
		dessinCarre(1,r3,v3,b3,120.5,-34+52,3,18);
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



	glEnable(GL_TEXTURE_2D);
    // FIXME : Bind texture
    /* Dessin du quad */
    glColor3ub(50,50,50);
    glBindTexture(GL_TEXTURE_2D, 1);
    glBegin(GL_QUADS);
      glColor3f(1,1,1);

      glTexCoord2f(0, 1);
      glVertex2f(-150, -100);

      glTexCoord2f(1, 1);
      glVertex2f(150, -100);

      glTexCoord2f(1, 0);
      glVertex2f(150, 100);

      glTexCoord2f(0, 0);
      glVertex2f(-150, 100);

    glEnd();


  glBindTexture(GL_TEXTURE_2D, 0);

  glDisable(GL_TEXTURE_2D);
}		

