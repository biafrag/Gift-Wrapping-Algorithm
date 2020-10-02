#version 330 core

uniform vec3 color;
in vec3 testePos;
out vec4 finalColor;

void main()
{
   //finalColor = vec4(1,1,0,1);
    //finalColor = vec4(testePos + 1, 1);
    finalColor = vec4(color, 1);
}
