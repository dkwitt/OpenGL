// Vertex shader
#version 330

// Dane pobrane z VAO
layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec3 inColor;

smooth out vec3 fragColor;

uniform int Mode;

uniform mat4 matProj;
uniform mat4 matView;
uniform mat4 matModel;


void main()
{
	switch(Mode)
    {
		case 0:	
			fragColor = inColor;
			fragColor.b += 1.0;
			break;

		case 1:
			fragColor = inColor;
			fragColor.gb -= 1.0;
			fragColor.r += 0.5;
			break;

		case 2:
			fragColor = inColor;
			fragColor.rg -= 0.5;
			break;

		case 3:
			fragColor = inColor;
			fragColor.rb -= 1.0;
			break;

	

    }


	vec4 newPosition = matProj * matView * matModel * inPosition;
	gl_Position = newPosition;
}
