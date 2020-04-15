#include "Game.h"

Game::Game() : isTicking{ false }, ticksPerSecond{ 0 }, ticksSinceLastSecond{ 0 }, lastTickTimePoint{ std::chrono::high_resolution_clock::now() }, consoleBufferInfo{ NULL }, consoleHandle{ GetStdHandle(STD_OUTPUT_HANDLE)  }
{
	

}


/*
			Setters / Getters
*/

void Game::setIsTicking(bool r, bool tickNow)
{
	isTicking = r;
	if (tickNow) tick();
}

bool Game::getIsTicking()
{
	return isTicking;
}

void Game::setTicksPerSecond(float tps)
{
	ticksPerSecond = tps;
}

float Game::getTicksPerSecond()
{
	return ticksPerSecond;
}


void Game::setTicksSinceLastSecond(int t)
{
	ticksSinceLastSecond = t;
}

int Game::getTicksSinceLastSecond()
{
	return ticksSinceLastSecond;
}

void Game::setLastTickTimePoint(std::chrono::high_resolution_clock::time_point timePoint)
{
	lastTickTimePoint = timePoint;
}

std::chrono::high_resolution_clock::time_point Game::getLastTickTimePoint()
{
	return lastTickTimePoint;
}




void Game::tick(bool loop)		// main game loop
{
	if (loop) setIsTicking(true, false);
	do
	{

		// calculate ticksPerSecond
		setTicksSinceLastSecond(getTicksSinceLastSecond() + 1);
		auto timeSinceLastTickTimePoint = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - lastTickTimePoint).count();
		if (timeSinceLastTickTimePoint >= 1.0)		// if its been longer than a second since our last timepoint check
		{
			// divide the counts of ticks by the duration
			float tps = (float)ticksSinceLastSecond / (float)timeSinceLastTickTimePoint;
			setTicksPerSecond(tps);
			setTicksSinceLastSecond(0);
			setLastTickTimePoint(std::chrono::high_resolution_clock::now());
		}

		// clear the garbage from the screen that might have been there previously
		system("CLS");

		// get the console buffer info (size of the console window, cursor location, cell attributes like color, etc
		GetConsoleScreenBufferInfo(consoleHandle, &consoleBufferInfo);

		// grab a copy of the size of the buffer (current x value of right side of console window and y value of bottom side of console window)
		COORD bufferSize{ consoleBufferInfo.dwSize };




		// print the tps
		std::cout << getTicksPerSecond() << '\n';
	} while (getIsTicking());
}
