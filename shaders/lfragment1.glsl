#version 330 core

out vec4 color;
uniform vec3 isLight;

void main()
{
	if (isLight.y > 0.0)
	{
		color = vec4(0.51f, 0.90f, 1.0f, 1.0f);
	}
	else
	{
		color = vec4(0.7f, 0.7f, 0.7f, 1.0f);
	}
}
