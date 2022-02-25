#pragma once
#ifndef BASE_GLPROGRAM_H
#define BASE_GLPROGRAM_H

#include <xstring>

using namespace std;

class GLProgram
{
public:
	GLProgram(string,string);
	~GLProgram();
	bool useProgram();
private:
	unsigned int createShader(string&,int);
	unsigned int createProgam();
	string _vertStr;
	string _fragStr;
	unsigned int fragmentShader;
	unsigned int vertexShader;
	unsigned int shaderProgram;
};

#endif
