#ifndef SUBTITLEEDITOR_H
#define SUBTITLEEDITOR_H

#include "Subtitle.h"
#include<string>
#include "Style.h"
#include "Stack.h"
using namespace std;

typedef struct elem {
	Subtitle* sub;
	struct elem* next;
}Elem;


class SubtitleEditor {
public:
	SubtitleEditor();
	SubtitleEditor(string subtitles);

	~SubtitleEditor();

	int loadSubtitles(string subtitles);
	string saveSubtitles();

	void addToSelection(int start, int end);
	void deselect();

	void boldText(int start, int end);
    void italicText(int start, int end);
	void underlineText(int start, int end);
	void removeStyle();

	void shiftForward(int ms);
	void shiftBackward(int ms);

	void insertSubtitle(int start, int length, string text);

	void deleteSubtitles();

	void merge(string subtitles);

	void fixLongLines(int max);

	void fixLongTime(int ms);

	void undo();


private:
	Elem* first; // glava liste titlova
	Elem* last; // rep liste titlova
	Stack* stack;

	int selectionExists();
	void deleteSequence(Elem* head);
};

#endif