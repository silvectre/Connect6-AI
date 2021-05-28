#include <strstream>
#include <ctime>
#include <easyx.h>
void SetWindows();
bool UCT_GamePlay();
int main()
{
	SetWindows();
	AllocConsole();
	freopen("CONOUT$", "w+t", stdout);
	freopen("CONIN$", "r+t", stdin);
	while (UCT_GamePlay());
	FreeConsole();
	closegraph();
	return 0;
}
