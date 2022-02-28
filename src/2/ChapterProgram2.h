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
	void loadPng();
private:

};

#endif // !CHAPTERPROGRAM_2
