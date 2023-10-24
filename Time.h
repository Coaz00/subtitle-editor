#ifndef TIME_H
#define TIME_H

#include<string>
using namespace std;

class Time {
public:
	Time();
	Time(int hh, int mm, int ss, int ms);

	void setHours(int hh);
	void setMinutes(int mm);
	void setSeconds(int ss);
	void setMiliSeconds(int ms);

	int getHours();
	int getMinutes();
	int getSeconds();
	int getMiliSeconds();

	void setTime(int hh, int mm, int ss, int ms);
	Time* getTime();

	void readTime(string subtitles, int& pos, char end);
	void saveTime(string& subtitles);

	void increaseTime(int ms);
	void decreaseTime(int ms);

	void miliSecondsToTime(int ms);
	int timeToMiliSeconds();

private:
	int hh, mm, ss, ms; // sati, minuti, sekunde, milisekunde
	int readNumber(string subtitles, int& pos, char end);
	void saveNumber(string& subtitles, int number,string type);
};

#endif
