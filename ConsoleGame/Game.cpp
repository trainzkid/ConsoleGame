#include "Game.h"

Game::Game() : isTicking{ false }, ticksPerSecond{ 0 }, ticksSinceLastSecond{ 0 }, lastTickTimePoint{ std::chrono::high_resolution_clock::now() }
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
	{			// should I just make this function call itself instead of doing a do while loop? does it matter?

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

		CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
		SMALL_RECT srctWindow;

		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);

		srctWindow = csbiInfo.srWindow;


		
		std::cout << getTicksPerSecond() << '\n';
	} while (getIsTicking());
}
