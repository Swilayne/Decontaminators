/**
 * \file		main.cpp 
 * \version		rendu2
 * \date		2018-04-10
 * \author		Nal et Leafe
 * \brief		Programme pour le projet du cours Programmation II
 *            
 *
 */
 
// *******************************************************************
// 		inclusion de fichiers en-tête avec la directives include

#include <GL/glu.h>
#include <GL/glui.h>


extern "C"
{
	#include "constantes.h"
	#include <stdlib.h>
}

 
// *******************************************************************
// 		

namespace
{ 
	enum STATES{OPEN,SAVE,START,STEP,EXIT};
    int main_window;
    //int data_type_open,data_type_save;
    
    //int *p;
	//char text_open[20], text_save[20];
    
    //FILE *file;
    
    GLUI *glui;
    
    GLfloat aspect_ratio ;
    
    GLUI_Panel *p_open, *p_saving, *p_simul, *p_rec, *p_cont_mod, *p_rob_cont;
    
    GLUI_EditText *ed_open, *ed_saving;
    
    GLUI_Button *but_open, *but_save, *but_start, *but_step, *but_exit;
    
    GLUI_Checkbox *check_record;
    
    GLUI_StaticText *rate, *turn, *trans, *rot;
    
    GLUI_RadioGroup *rd_group_cont;
    
    GLUI_RadioButton *rd_but_auto, *rd_but_manu;
    
}


void file_cb(int control) 
{ 
	switch (control)
	{ 
		case (OPEN):
			fopen(ed_open->get_text(),"r");
			break;
			
		case (SAVE):
			FILE *file_save;
			file_save = fopen(ed_saving->get_text(),"w+");
			fprintf(file_save,"%s","SAVING OF SIMULATION\n");
			break;
			
		default:
			printf("Not known command");
			break;
	} 
} 

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    // ré-initialisation de la matrice de transformation 
    glLoadIdentity();
    
    // ajustement du domaine visualisé selon la forme de la fenêtre
    // pour garantir d'avoir toujours au moins [-1, 1] selon X et Y
    // les derniers paramètres (profondeur) restent constants pour du 2D
    if (aspect_ratio <= 1.)
      glOrtho(-DMAX, DMAX, -DMAX/aspect_ratio, DMAX/aspect_ratio, -1.0, 1.0);
    else 
      glOrtho(-DMAX*aspect_ratio, DMAX*aspect_ratio, -DMAX, DMAX, -1.0, 1.0);
	
	
    // commandes de dessin ; ici chaque sommet a une couleur différente
    // OPENGL va interpoler les couleurs pour remplir le polygone
    glBegin(GL_POLYGON);

    glEnd();

    glutSwapBuffers();            //exchange back and front buffers
  }  


void reshape(int w, int h)
{
    //le viewport prend toute la fenêtre
    glViewport(0, 0, w, h); 
    
    // mise à jour pour usage futur par affichage()
    aspect_ratio = (GLfloat)w / (GLfloat)h ; 
} 

void glui_open(void)
{
	glui = GLUI_Master.create_glui( "Decontaminators - Controle", 0, 800, 350); 
	glui->set_main_gfx_window( main_window );
	
	p_open = glui->add_panel( "Opening");
	ed_open = glui-> add_edittext_to_panel(p_open,"File Name:");
	but_open = glui-> add_button_to_panel(p_open,"Open", OPEN, file_cb);
	
	p_saving= glui-> add_panel( "Saving");
	ed_saving = glui-> add_edittext_to_panel(p_saving,"File Name:");
	ed_saving->set_text("save.txt");
	but_save = glui-> add_button_to_panel(p_saving,"Save",SAVE, file_cb);
	
	glui->add_column(true);
	
	p_simul = glui-> add_panel( "Simulation");
	but_start = glui-> add_button_to_panel(p_simul, "START");
	but_step = glui -> add_button_to_panel(p_simul, "STEP");
	
	p_rec = glui-> add_panel( "Recording");
	check_record = glui-> add_checkbox_to_panel(p_rec,"Record");
	rate = glui-> add_statictext_to_panel(p_rec,"Rate : 0.000");
	turn = glui-> add_statictext_to_panel(p_rec,"Turn : 0");
	
	glui-> add_column(true);
	
	p_cont_mod = glui-> add_panel("Control Mode");
	rd_group_cont = glui-> add_radiogroup_to_panel(p_cont_mod);
	rd_but_auto = glui -> add_radiobutton_to_group(rd_group_cont, "Automatic");
	rd_but_manu = glui -> add_radiobutton_to_group(rd_group_cont, "Manual");
	p_rob_cont = glui -> add_panel("Robot Control");
	trans = glui -> add_statictext_to_panel (p_rob_cont, "Translation : 0.000");
	rot = glui -> add_statictext_to_panel (p_rob_cont, "Rotation : 0.000");
	
	but_exit = glui->add_button( "Quit",0,(GLUI_Update_CB)exit ); 
	
		
}



int main(int argc, char **argv)
{
	
	if( argv[1] && strcmp("ERROR", argv[1]))
	{
		
		printf("MODE ERREUR\n");
	}
	
	else if( (argv[1] && strcmp("DRAW",argv[1])) || argc==1)
	{
		
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
		glutInitWindowPosition(50, 100);
		glutInitWindowSize(700, 700);
		main_window = glutCreateWindow("Decontaminators");
		glClearColor(1.0, 1.0, 1.0, 0.0);
		
		glutDisplayFunc(display);
		glutReshapeFunc(reshape);
		glui_open();
		glutMainLoop();
	
	 }
	 
	 else printf("Invalid use of this program !\n Syntax: ./projet.x [Error|Draw, nom_fichier]");
	 
	 return EXIT_SUCCESS;
    
	
 

    
 
    

}


