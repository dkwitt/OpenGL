#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

#include "shader_stuff.h"


// ---------------------------------------
// Identyfikatory obiektow

GLuint idProgram;	// programu
GLuint idVAO;		// tablic wierzcholkow
GLuint idVBO_coord;	// bufora wierzcholkow
GLuint idVBO_indices; // bufora indeks�w


// ---------------------------------------
// Wspolrzedne wierzchokow
GLfloat coords[97*2] =
{
	0.000000, 0.000000,
	0.198450, 0.542433,
	0.198450, 0.219933,
	0.520950, 0.219933,
	0.520950, 0.542433,
	0.233138, 0.194933,
	0.272200, 0.176183,
	0.315013, 0.164933,
	0.359700, 0.161183,
	0.404388, 0.164933,
	0.447200, 0.176183,
	0.486263, 0.194933,
	0.173450, 0.507745,
	0.154700, 0.468683,
	0.143450, 0.425870,
	0.139700, 0.381183,
	0.143450, 0.336495,
	0.154700, 0.293683,
	0.173450, 0.254620,
	0.486263, 0.567433,
	0.447200, 0.586183,
	0.404388, 0.597433,
	0.359700, 0.601183,
	0.315013, 0.597433,
	0.272200, 0.586183,
	0.233138, 0.567433,
	0.545950, 0.254620,
	0.564700, 0.293683,
	0.575950, 0.336495,
	0.579700, 0.381183,
	0.575950, 0.425870,
	0.564700, 0.468683,
	0.545950, 0.507745,
	0.399700, 0.181183,
	0.319700, 0.181183,
	0.399700, -0.298817,
	0.319700, -0.298817,
	0.217858, 0.239340,
	0.263659, 0.226860,
	0.311191, 0.218924,
	0.359700, 0.216183,
	0.408209, 0.218924,
	0.455742, 0.226860,
	0.501543, 0.239340,
	0.205377, 0.285141,
	0.256367, 0.277849,
	0.307877, 0.272953,
	0.359700, 0.271183,
	0.411523, 0.272953,
	0.463033, 0.277849,
	0.514023, 0.285141,
	0.197441, 0.332673,
	0.251471, 0.329360,
	0.305566, 0.327049,
	0.359700, 0.326183,
	0.413834, 0.327049,
	0.467929, 0.329360,
	0.521959, 0.332673,
	0.194700, 0.381183,
	0.249700, 0.381183,
	0.304700, 0.381183,
	0.359700, 0.381183,
	0.414700, 0.381183,
	0.469700, 0.381183,
	0.524700, 0.381183,
	0.197441, 0.429692,
	0.251471, 0.433006,
	0.305566, 0.435317,
	0.359700, 0.436183,
	0.413834, 0.435317,
	0.467929, 0.433006,
	0.521959, 0.429692,
	0.205377, 0.477224,
	0.256367, 0.484516,
	0.307877, 0.489412,
	0.359700, 0.491183,
	0.411523, 0.489412,
	0.463033, 0.484516,
	0.514023, 0.477224,
	0.217858, 0.523025,
	0.263658, 0.535506,
	0.311191, 0.543442,
	0.359700, 0.546183,
	0.408209, 0.543442,
	0.455742, 0.535506,
	0.501543, 0.523025,
	-0.720000, -0.300000,
	-0.080000, -0.300000,
	-0.720000, 0.180000,
	-0.080000, 0.180000,
	-0.800000, 0.180000,
	-0.000000, 0.180000,
	-0.400000, 0.340000,
	-0.240000, -0.060000,
	-0.560000, -0.300000,
	-0.240000, -0.300000,
	-0.560000, -0.060000,
};

// ---------------------------------------
// Indeksy wierzcholkow
GLuint indices[137*3] =
{
	35, 34, 36,
	37, 45, 44,
	38, 46, 45,
	39, 47, 46,
	41, 47, 40,
	42, 48, 41,
	43, 49, 42,
	44, 52, 51,
	45, 53, 52,
	46, 54, 53,
	48, 54, 47,
	49, 55, 48,
	50, 56, 49,
	51, 59, 58,
	52, 60, 59,
	53, 61, 60,
	55, 61, 54,
	56, 62, 55,
	57, 63, 56,
	59, 65, 58,
	60, 66, 59,
	61, 67, 60,
	61, 69, 68,
	62, 70, 69,
	63, 71, 70,
	66, 72, 65,
	67, 73, 66,
	68, 74, 67,
	68, 76, 75,
	69, 77, 76,
	70, 78, 77,
	73, 79, 72,
	74, 80, 73,
	75, 81, 74,
	75, 83, 82,
	76, 84, 83,
	77, 85, 84,
	2, 37, 18,
	5, 38, 37,
	6, 39, 38,
	7, 40, 39,
	9, 40, 8,
	10, 41, 9,
	11, 42, 10,
	3, 43, 11,
	26, 50, 43,
	27, 57, 50,
	28, 64, 57,
	64, 30, 71,
	71, 31, 78,
	78, 32, 85,
	85, 4, 19,
	84, 19, 20,
	83, 20, 21,
	82, 21, 22,
	82, 23, 81,
	81, 24, 80,
	80, 25, 79,
	79, 1, 12,
	72, 12, 13,
	65, 13, 14,
	58, 14, 15,
	16, 58, 15,
	17, 51, 16,
	18, 44, 17,
	35, 33, 34,
	37, 38, 45,
	38, 39, 46,
	39, 40, 47,
	41, 48, 47,
	42, 49, 48,
	43, 50, 49,
	44, 45, 52,
	45, 46, 53,
	46, 47, 54,
	48, 55, 54,
	49, 56, 55,
	50, 57, 56,
	51, 52, 59,
	52, 53, 60,
	53, 54, 61,
	55, 62, 61,
	56, 63, 62,
	57, 64, 63,
	59, 66, 65,
	60, 67, 66,
	61, 68, 67,
	61, 62, 69,
	62, 63, 70,
	63, 64, 71,
	66, 73, 72,
	67, 74, 73,
	68, 75, 74,
	68, 69, 76,
	69, 70, 77,
	70, 71, 78,
	73, 80, 79,
	74, 81, 80,
	75, 82, 81,
	75, 76, 83,
	76, 77, 84,
	77, 78, 85,
	2, 5, 37,
	5, 6, 38,
	6, 7, 39,
	7, 8, 40,
	9, 41, 40,
	10, 42, 41,
	11, 43, 42,
	3, 26, 43,
	26, 27, 50,
	27, 28, 57,
	28, 29, 64,
	64, 29, 30,
	71, 30, 31,
	78, 31, 32,
	85, 32, 4,
	84, 85, 19,
	83, 84, 20,
	82, 83, 21,
	82, 22, 23,
	81, 23, 24,
	80, 24, 25,
	79, 25, 1,
	72, 79, 12,
	65, 72, 13,
	58, 65, 14,
	16, 51, 58,
	17, 44, 51,
	18, 37, 44,
	93, 89, 88,
	90, 91, 92,
	88, 86, 96,
	86, 94, 96,
	95, 87, 93,
	87, 89, 93,
	88, 96, 93
};



// ---------------------------------------
void DisplayScene()
{

	glClear( GL_COLOR_BUFFER_BIT );

	// Wlaczenie VAO i programu
	glBindVertexArray( idVAO );
	glUseProgram( idProgram );

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	// Generowanie obiektow na ekranie
	glDrawElements( GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, NULL );


	// Wylaczanie
	glUseProgram( 0 );
	glBindVertexArray( 0 );



	glutSwapBuffers();
}

// ---------------------------------------
void Initialize()
{

	glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );


	// 1. Program i shadery
	idProgram = glCreateProgram();

	glAttachShader( idProgram, LoadShader(GL_VERTEX_SHADER, "vertex.glsl"));
	glAttachShader( idProgram, LoadShader(GL_FRAGMENT_SHADER, "fragment.glsl"));

	LinkAndValidateProgram( idProgram );


	// 2. Vertex arrays
	glGenVertexArrays( 1, &idVAO );
	glBindVertexArray( idVAO );

	// Bufor na wspolrzedne wierzcholkow
	glGenBuffers( 1, &idVBO_coord );
	glBindBuffer( GL_ARRAY_BUFFER, idVBO_coord );
	glBufferData( GL_ARRAY_BUFFER, sizeof( coords ), coords, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 0 );

    // Bufor na indeksy wierzcholkow
    glGenBuffers( 1, &idVBO_indices );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, idVBO_indices );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

	glBindVertexArray( 0 );

}

// ---------------------------------------
void Reshape( int width, int height )
{
	glViewport( 0, 0, width, height );
}

// ---------------------------------------------------
void Keyboard( unsigned char key, int x, int y )
{
    switch(key)
    {
		case 27:	// ESC key
			exit(0);
			break;

		case ' ':
			printf("SPACE\n");
			// odswiezenie ekranu
			glutPostRedisplay();
			break;

    }
}


// ---------------------------------------------------
int main( int argc, char *argv[] )
{
	// GLUT
	glutInit( &argc, argv );
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
	glutInitContextVersion( 3, 2 );
	glutInitContextProfile( GLUT_CORE_PROFILE );
	glutInitWindowSize( 500, 500 );
	glutCreateWindow( "OpenGL!" );
	glutDisplayFunc( DisplayScene );
	glutReshapeFunc( Reshape );

	// Keyboard
	glutKeyboardFunc( Keyboard );


	// GLEW
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if( GLEW_OK != err )
	{
		printf("GLEW Error\n");
		exit(1);
	}

	// OpenGL
	if( !GLEW_VERSION_3_2 )
	{
		printf("Brak OpenGL 3.2!\n");
		exit(1);
	}


	Initialize();

	glutMainLoop();


	// Cleaning
	glDeleteProgram( idProgram );
	glDeleteVertexArrays( 1, &idVBO_coord );
	glDeleteVertexArrays( 1, &idVAO );

	return 0;
}
