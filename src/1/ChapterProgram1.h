#pragma once
#ifndef CHAPTERPROGRAM_1
#define CHAPTERPROGRAM_1
#include "base/GLProgram.h"
#include "base/FileUtil.h"


class ChapterProgram1 :  GLProgram
{
public:
	ChapterProgram1();
	virtual bool init() override;
	virtual void render() override;
private:

};

#endif // !CHAPTERPROGRAM_1
