#ifndef CHAPTERPROGRAM_3
#define CHAPTERPROGRAM_3

#include "base/GLProgram.h"
#include "base/FileUtil.h"

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;

class ChapterProgram3 : GLProgram
{
public:
	ChapterProgram3();
	virtual bool init() override;
	virtual void render() override;
	unsigned char*  loadPng(string path,int& width, int& height, int& nrChannels);
	void setPerspective();
private:
	unsigned int textureUnti;
	unsigned int  u_projection;
};

#endif // !CHAPTERPROGRAM_3
