#ifndef CHAPTERPROGRAM_2
#define CHAPTERPROGRAM_2

#include "base/GLProgram.h"
#include "base/FileUtil.h"

class ChapterProgram2 : GLProgram
{
public:
	ChapterProgram2();
	virtual bool init() override;
	virtual void render() override;
	unsigned char*  loadPng(string path,int& width, int& height, int& nrChannels);
private:
	unsigned int textureUnti;
};

#endif // !CHAPTERPROGRAM_2
