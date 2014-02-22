#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <GL/glew.h>

#include <iostream>
#include <cstdlib>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphic/VBO.hpp"
#include "graphic/VAO.hpp"

#include "graphic/Shader.hpp"
#include "graphic/Program.hpp"

#include "graphic/common.hpp"

#include "graphic/TrackballCamera.hpp"

#include "graphic/print.hpp"
#include "graphic/gcaVertex.hpp"

static const Uint32 FPS = 30;
static const Uint32 FRAME_DURATION = 1000.f / FPS;

static const Uint32 WINDOW_WIDTH = 800;
static const Uint32 WINDOW_HEIGHT = 600;
static const Uint32 WINDOW_BPP = 32;

void plop(){

	std::cout<<"Début de l'exemple de Nozick sensei"<<std::endl;

	gca::GCA_vector a(1.0, 2.0, 3.0, 1.0);
	gca::GCA_vector b;
	b << -1.0, -3.0, 2.0, 1.0;

	gca::GCA_bivector l = a ^ b; // l is a PLucker line

	l.show();

	gca::GCA_vector x1(2.0, -1.0, -1.0, 1.0);
	gca::GCA_vector x2(1.0, -1.0, 1.0, 1.0);
	gca::GCA_vector x3(-1.0, -1.0, -2.0, 1.0);
	
	gca::GCA_trivector d = x1^x2^x3; //d is a plane
	std::cout << d<<std::endl;

	std::cout << "(~d^~l) n'est pas l'intersection : "<< (~d^~l) <<std::endl;

	gca::GCA_antivector croisement = (~d^~l);

	std::cout << "~(~d^~l) est l'intersection : "<< ~croisement <<std::endl;
	//std::cout << "intersection : "<< ~d^~l <<std::endl;// ne peux pas pas compiler selon les normes du c++

	std::cout<<"Fin de l'exemple de Nozick sensei"<<std::endl;
}



int main() {
	if(-1 == SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << "Unable to initialize SDL" << std::endl;
		return EXIT_FAILURE;
	}

	if(NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_BPP, SDL_OPENGL)) {
		std::cerr << "Unable to open the window and get an OpenGL context" << std::endl;
		return EXIT_FAILURE;
	}

	SDL_WM_SetCaption("OpenGL4Imacs", NULL);

	GLenum glewCode = glewInit();
	if(GLEW_OK != glewCode) {
		std::cerr << "Unable to initialize GLEW : " << glewGetErrorString(glewCode) << std::endl;
		return EXIT_FAILURE;
	}

	//initialisation

	glimac::TrackballCamera trackballCamera;

	glimac::VBO vbo;
	vbo.bind();

	glimac::gcaVertex vertexs;

//////////////////*******demo/********///////////////////////////////////////////////////////////////////////////////////////
	std::vector<gca::K_blade> grassmann;
	gca::GCA_vector x(1, 0, 0, 1.0);
	gca::GCA_vector y;
	y << 0, 1, 0, 1.0;
	gca::GCA_vector z(0, 0, 1, 1.0);
	gca::GCA_vector o(0, 0, 0, 1.0);

	vertexs.getBlade(x^o, glm::vec3(1, 0, 0)); //le balde, puis la couleur
	vertexs.getBlade(y^o, glm::vec3(0, 1, 0));
	vertexs.getBlade(z^o, glm::vec3(0, 0, 1));

	plop();

	gca::GCA_vector a (3, 5, -1, 1.);
	gca::GCA_vector b(1.2, -2.7, -0.1, 1.);
	gca::GCA_vector c;
	c<< -4.1, 0.2, 2.8, 1.; 

	gca::GCA_scalar factor(3);

	a = factor^a;

	gca::GCA_bivector l = a ^ b;
	gca::GCA_antibivector antil = ~l;

	gca::GCA_trivector p = l^c;
	gca::GCA_trivector copyP(-p);
	gca::GCA_trivector otherPlan(1, 1, 1, 1);

	gca::GCA_bivector croisementPlan = ~p^~otherPlan;

	std::cout<<"point a :"<< a<<std::endl;
	std::cout<<"~a :"<< ~a<<std::endl;
	std::cout<<"point b :"<< b<<std::endl;
	std::cout<<"point c :"<< c<<std::endl;
	std::cout<<"droite l (a^b) "<< l<<std::endl;
	std::cout<<"antibivector de l"<< antil<<std::endl;
	std::cout<<"plan p (l^c)"<< p<<std::endl;
	std::cout<<"copyP = -p"<<copyP<<std::endl;
	std::cout<<"~copyP"<<~copyP<<std::endl;
	std::cout<<"otherPlan"<<otherPlan<<std::endl;
	std::cout<<"~p^~otherPlan"<<croisementPlan<<std::endl;
	std::cout<<"~(~p^~otherPlan)"<<~croisementPlan<<std::endl;

	vertexs.getBlade(a, glm::vec3(1, 0, 0));
	vertexs.getBlade(b, glm::vec3(1, 0, 0));
	vertexs.getBlade(c, glm::vec3(1, 0, 0));
	vertexs.getBlade(l, glm::vec3(1, 1, 0));
	vertexs.getBlade(p, glm::vec3(1, 1, 1));
	vertexs.getBlade(otherPlan, glm::vec3(0, 1, 1));
	vertexs.getBlade(~croisementPlan, glm::vec3(0.5, 0.5, 0.));


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	glBufferData(GL_ARRAY_BUFFER, vertexs.getVertexCount() * sizeof(glimac::ShapeVertex), vertexs.getDataPointer(), GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0); //on debind le vbo

	glimac::VAO vao;
	vao.bind();
	vbo.bind();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(	 0, // Index de l'attribut: 0 dans notre cas, l'index de la position
							 3, // Nombre de composantes de l'attribut: 2 car on à 2 float par position
							 GL_FLOAT, // Type des composantes de l'attribut: GL_FLOAT pour les float
							 GL_FALSE, // A mettre à GL_TRUE
							 sizeof(glimac::ShapeVertex), // nombre de float à parcourire depuis la position initiale pour atteintre les prochaine coordonnées (2 de position + 3 de couleurs=5)
							 (const GLvoid*) (0 * sizeof(GLfloat))); // A mettre à 0 ou NULL pour l'instant	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(	 1, // Index de l'attribut: 0 dans notre cas, l'index de la position
							 3, // Nombre de composantes de l'attribut: 3 car on à 3 float par couleur
							 GL_FLOAT, // Type des composantes de l'attribut: GL_FLOAT pour les float
							 GL_FALSE, // la normailsation est faite par la carte graphique
							 sizeof(glimac::ShapeVertex), // nombre de float à parcourire depuis la position initiale pour atteintre les prochaine coordonnées (2 de position + 3 de couleurs=5)
							 (const GLvoid*) (3 * sizeof(GLfloat))); // Un sommet est stocké dans le VBO sous la forme x y r g b. Le décalage est donc de 2 flottants car il y x y juste avant la couleur. Il faut donc passer à la fonction la valeur (const GLvoid*) (2 * sizeof(GLfloat))	
	
	glBindBuffer(GL_ARRAY_BUFFER, 0); //on debind le vbo
	glBindVertexArray(0);			//on debind le vao


	//shader
	
	glimac::Program programShader = glimac::loadProgram( "../shader/3D.vs.glsl", "../shader/color3D.fs.glsl");
	
	programShader.use();

	GLint location1 = glGetUniformLocation(programShader.getGLId(), "uMVPMatrix");
	GLint location2 = glGetUniformLocation(programShader.getGLId(), "uMVMatrix");
	GLint location3 = glGetUniformLocation(programShader.getGLId(), "uNormalMatrix");

	glEnable(GL_DEPTH_TEST); //permet d'activer le test de profondeur du GPU.


	int sourisX, sourisY;
	bool done = false;
	while(!done) {
		Uint32 tStart = SDL_GetTicks();

		// Rendering code goes here

		glm::mat4 ProjMatrix = glm::perspective(70.f, (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.1f, 100.f);
		glm::mat4 MVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0,0,-5));
		MVMatrix *= trackballCamera.getViewMatrix();
		glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));



		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		vao.bind();

			glUniformMatrix4fv(location1, 1, 0, glm::value_ptr(ProjMatrix * MVMatrix /* RotateTerre*/));
			glUniformMatrix4fv(location2, 1, 0, glm::value_ptr(MVMatrix /* RotateTerre*/));
			glUniformMatrix4fv(location3, 1, 0, glm::value_ptr(NormalMatrix));

			glDrawArrays(GL_LINES, 0, vertexs.getVertexCount());
			

		glBindVertexArray(0);			//on debind le vao

		// Application code goes here

		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			switch(e.type) {
				default:
				break;

				case SDL_MOUSEBUTTONDOWN:
					switch(e.button.button){
						case SDL_BUTTON_WHEELDOWN:
							trackballCamera.moveFront(-0.1);
						break;

						case SDL_BUTTON_WHEELUP:
							trackballCamera.moveFront(0.1);
						break;

						case SDL_BUTTON_RIGHT:
							sourisX = e.button.x;
							sourisY = e.button.y;
						break;
					}
				break;

				case SDL_QUIT:
					done = true;
				break;
			}
		}

		int x, y;
		if(SDL_GetMouseState(&x, &y) & SDL_BUTTON(3))
		{	
			trackballCamera.rotateLeft(y - sourisY);
			trackballCamera.rotateUp(x - sourisX);

			sourisX = x;
			sourisY = y;
		}

		

		// Mise à jour de la fenêtre (synchronisation implicite avec OpenGL)
		SDL_GL_SwapBuffers();

		Uint32 tEnd = SDL_GetTicks();
		Uint32 d = tEnd - tStart;
		if(d < FRAME_DURATION) {
			SDL_Delay(FRAME_DURATION - d);
		}
	}

	SDL_Quit();

	return EXIT_SUCCESS;
}