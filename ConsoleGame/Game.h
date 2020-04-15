#ifndef GAME_H
#define GAME_H
#include <chrono>
#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <Windows.h>


class Game
{
	// variables
public:


private:
	bool isTicking;
	float ticksPerSecond;
	int ticksSinceLastSecond;
	std::chrono::high_resolution_clock::time_point lastTickTimePoint;
	CONSOLE_SCREEN_BUFFER_INFO consoleBufferInfo;
	HANDLE consoleHandle;

	// functions
public:
	Game();
	void setIsTicking(bool r, bool tickNow = true);
	bool getIsTicking();
	float getTicksPerSecond();
	void tick(bool loop = false);

private:
	void setTicksPerSecond(float tps);
	void setTicksSinceLastSecond(int t);
	int getTicksSinceLastSecond();
	void setLastTickTimePoint(std::chrono::high_resolution_clock::time_point timePoint = std::chrono::high_resolution_clock::now());
	std::chrono::high_resolution_clock::time_point getLastTickTimePoint();
	

};

#endif


