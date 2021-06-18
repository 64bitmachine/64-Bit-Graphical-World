#version 330 core

out vec4 color;
uniform vec3 isLight;

void main()
{
	if (isLight.x > 0.0)
	{
		color = vec4(1.0f);
	}
	else
	{
		color = vec4(0.7f, 0.7f, 0.7f, 1.0f);
	}
}
