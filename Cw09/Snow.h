#ifndef __SNOW_H
#define __SNOW_H





#define NUMBER_OF_FLAKES	100000
glm::mat4 matModels[NUMBER_OF_FLAKES];
std::vector<glm::vec3> OBJ_vertices;
float Time = 0.0;
GLuint Snow_Program;
GLuint vArray;
GLuint TextureID;
glm::mat4x4 matModel;

void InitSnow()
{
	for (int i=0; i<NUMBER_OF_FLAKES; i++)
	{
		// losowac pozycje (-20 do 20)
		float x = -100 + (rand()%400)/2.0;
		float y = -100 + (rand()%400)/2.0;
		float z = -100 + (rand()%400)/2.0;

		float scale = 0.2 + (rand()%80)/10.0;
		float rot = (rand()%(2*318))/100.0;

		matModels[i] = glm::translate(glm::mat4(1.0), glm::vec3(x, y, z));
		matModels[i] = glm::rotate(matModels[i], rot, glm::vec3(0.0, 1.0, 0.0));
		matModels[i] = glm::scale(matModels[i], glm::vec3(rot));

	}
}

void MakeSnow()
{
    // AKTYWUJEMY program
	glUseProgram( Snow_Program );

		glUniform1f( glGetUniformLocation(Snow_Program, "Time"), Time );

		// Przekazujemy zmienne uniform do programu
		glUniformMatrix4fv( glGetUniformLocation( Snow_Program, "matProj" ), 1, GL_FALSE, glm::value_ptr(matProj) );
		glUniformMatrix4fv( glGetUniformLocation( Snow_Program, "matView" ), 1, GL_FALSE, glm::value_ptr(matView) );
		glUniformMatrix4fv( glGetUniformLocation( Snow_Program, "matModel" ), 1, GL_FALSE, glm::value_ptr(matModel) );


		// Tekstury
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureID);


		glUniform1i(glGetUniformLocation(Snow_Program, "tex0"), 0);


		// Renderowanie obiektu
		glBindVertexArray( vArray );
			glDrawArraysInstanced( GL_TRIANGLES, 0, OBJ_vertices.size(), NUMBER_OF_FLAKES );
		glBindVertexArray( 0 );



    glUseProgram( 0);
}


void LetItSnow()
{

	std::vector<glm::vec2> OBJ_uvs;
	std::vector<glm::vec3> OBJ_normals;
	if (!loadOBJ("flower.obj", OBJ_vertices, OBJ_uvs, OBJ_normals))
	{
		printf("Not loaded!\n");
		exit(1);
	}



    // Tworzenie tekstury
	int tex_width, tex_height, tex_n;
	unsigned char *tex_data;
	tex_data = stbi_load("snowflake.png", &tex_width, &tex_height, &tex_n, 0);
	if (!tex_data) { printf("File error!\n"); }

	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	if (tex_n == 3)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
	else if (tex_n == 4)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);

	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);



	// Tworzenie potoku OpenGL
	Snow_Program = glCreateProgram();
	glAttachShader( Snow_Program, LoadShader(GL_VERTEX_SHADER, "vertex-instanced.glsl"));
	glAttachShader( Snow_Program, LoadShader(GL_FRAGMENT_SHADER, "fragment-instanced.glsl"));
	LinkAndValidateProgram( Snow_Program );

	// VAO

	glGenVertexArrays( 1, &vArray );
	glBindVertexArray( vArray );

	// VBO
	// Wspolrzedne wierzcholkow
	GLuint vBuffer_pos;
	glGenBuffers( 1, &vBuffer_pos );
	glBindBuffer( GL_ARRAY_BUFFER, vBuffer_pos );
	glBufferData( GL_ARRAY_BUFFER, OBJ_vertices.size() * sizeof(glm::vec3), &OBJ_vertices[0], GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 0 );

	// Wspolrzedne textury UV
	GLuint vBuffer_uv;
	glGenBuffers( 1, &vBuffer_uv );
	glBindBuffer( GL_ARRAY_BUFFER, vBuffer_uv );
	glBufferData( GL_ARRAY_BUFFER, OBJ_uvs.size() * sizeof(glm::vec2), &OBJ_uvs[0], GL_STATIC_DRAW );
	glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 1 );

	// Wektory normalne
	GLuint vBuffer_normal;
	glGenBuffers( 1, &vBuffer_normal );
	glBindBuffer( GL_ARRAY_BUFFER, vBuffer_normal );
	glBufferData( GL_ARRAY_BUFFER, OBJ_normals.size() * sizeof(glm::vec3), &OBJ_normals[0], GL_STATIC_DRAW );
	glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, NULL );
	glEnableVertexAttribArray( 2 );

	// Wektory normalne
	GLuint vBuffer_inst;
	glGenBuffers( 1, &vBuffer_inst );
	glBindBuffer( GL_ARRAY_BUFFER, vBuffer_inst );
	glBufferData( GL_ARRAY_BUFFER, NUMBER_OF_FLAKES * sizeof(glm::mat4), &matModels[0], GL_STATIC_DRAW );

	glVertexAttribPointer (3, 4, GL_FLOAT , GL_FALSE , sizeof (glm :: mat4), (void *)0);
	glVertexAttribPointer (4, 4, GL_FLOAT , GL_FALSE , sizeof (glm :: mat4), (void *)( sizeof (glm :: vec4 )));
	glVertexAttribPointer (5, 4, GL_FLOAT , GL_FALSE , sizeof (glm :: mat4), (void *)(2 * sizeof (glm :: vec4 )));
	glVertexAttribPointer (6, 4, GL_FLOAT , GL_FALSE , sizeof (glm :: mat4), (void *)(3 * sizeof (glm :: vec4 )));

	glEnableVertexAttribArray (3);
	glEnableVertexAttribArray (4);
	glEnableVertexAttribArray (5);
	glEnableVertexAttribArray (6);
	glVertexAttribDivisor (3, 1);
	glVertexAttribDivisor (4, 1);
	glVertexAttribDivisor (5, 1);
	glVertexAttribDivisor (6, 1);

	glBindVertexArray( 0 );
}

#endif // __SNOW
