	#version 330 core

	in vec4 vertexColor;

	out vec4 FragColor;

	void main()
	{
		FragColor = vec4(vertexColor.x, vertexColor.y + 0.7, vertexColor.z, vertexColor.w);
	};