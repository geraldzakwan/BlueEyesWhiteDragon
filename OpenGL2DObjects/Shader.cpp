#include "Shader.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace glm;

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
static string LoadShader(const string& fileName);
static GLuint CreateShader(const string& text, unsigned int type);

Shader::Shader(const string& fileName)
{
	prog = glCreateProgram();
	arsiranArray[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	arsiranArray[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < 2; i++)
		glAttachShader(prog, arsiranArray[i]);

	//Binding attribute di file vs
	glBindAttribLocation(prog, 0, "pos");
	glBindAttribLocation(prog, 1, "texCoord");

	glLinkProgram(prog);
	CheckShaderError(prog, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(prog);
	CheckShaderError(prog, GL_LINK_STATUS, true, "Invalid shader program");

	//Untuk transformasi/animasi
	transform = glGetUniformLocation(prog, "transform");
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < 2; i++)
	{
		glDetachShader(prog, arsiranArray[i]);
		glDeleteShader(arsiranArray[i]);
	}

	glDeleteProgram(prog);
}

void Shader::Bind()
{
	glUseProgram(prog);
}

void Shader::Update(const Animation& animate)
{
	//mat4 MVP = transform.GetMVP(camera);
	mat4 animate_matrix = animate.GetAnimationMatrix();

	//Matrix 4x4 floating values
	//GL_FALSE-nya buat biar OpenGL ngk melakukan transpose matrix

	glUniformMatrix4fv(transform, 1, GL_FALSE, &animate_matrix[0][0]);	
}

static string LoadShader(const string& fileName)
{
	ifstream file;
	file.open((fileName).c_str());

	string output;
	string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		cerr << "Unable to load shader: " << fileName << std::endl;
	}

	return output;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		cerr << errorMessage << ": '" << error << "'" << endl;
	}
}

static GLuint CreateShader(const string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type);

	if (shader == 0)
		cerr << "Error compiling shader type " << type << std::endl;

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: shader compilation failed!");

	return shader;
}