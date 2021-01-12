#include "../include/textui.h"

void StartGame(std::unique_ptr<Game> g) 
{
	g->Run();
}
void TextUI::Run() 
{
	auto g = std::make_unique<Game>();
	g->Attach(this);
	std::thread t (StartGame, std::move(g));
	t.join();
}
void ClearScreen()
{
	int n;
	for (n = 0; n < 10; n++)
		printf("\n\n\n\n\n\n\n\n\n\n");
}
void TextUI::Update(const GameState& state) 
{
	//ClearScreen();
	std::cout << StateToString(state);

}

std::string TextUI::StateToString(const GameState &state) {
    return std::string();
}

