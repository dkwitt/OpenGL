#version 330 core

layout( location = 0 ) in vec4 inPosition;
layout( location = 1 ) in vec2 inUV;
layout( location = 2 ) in vec3 inNormal;

layout( location = 3 ) in mat4 inMatModel;

uniform mat4 matProj;
uniform mat4 matView;
uniform mat4 matModel;

out vec2 fragUV;
uniform float Time;

// predefiniowana zmienna w renderingu instancjonowanym
// in int gl_InstanceID;


void main()
{
	vec4 newPosition = inPosition;
	newPosition.y -= Time;

    gl_Position = matProj * matView * inMatModel * newPosition;

    fragUV = inUV;
}
