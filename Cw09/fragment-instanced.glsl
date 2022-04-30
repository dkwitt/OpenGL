#version 150 core

in vec2 fragUV;
out vec4 outColor;

uniform sampler2D tex0;

void main()
{
   vec4 fragColor = texture( tex0, fragUV );
   if (fragColor.a <0.5)
		discard;
	
	
	outColor = fragColor;
}
