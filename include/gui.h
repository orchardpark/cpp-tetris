#ifndef CPP_TETRIS_GUI_H
#define CPP_TETRIS_GUI_H
#include "observer.h"
#include <thread>
#include "game.h"
#include <map>
#include <iostream>
#include <memory>
#include <filesystem>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

class GUI : IObserver {
public:
	void Run();
	void Update(const GameState& state);
private:
    /// Start a new game
    /// \param game The game to start
    static void StartGame(std::shared_ptr<Game> game);
    /// Starts the keyboard event queue and handler in a new thread
    /// \param game The game to apply the key events to
    static void RunKeyboardController(std::shared_ptr<Game> game);
    /// Renders the current state of the game to screen
    /// \param state The current game state
    void RenderState(const GameState& state);
    /// Renders text to the screen
    /// \param x x-Coordinate of render
    /// \param y y-Coordinate of render
    /// \param text The text to be rendered
    /// \param scaleFactor The size of the render
    void RenderText(int x, int y, const char* text, float scaleFactor);
    void RenderSquare(int row, int column, Shape s);
    /// Renders the board on the screen
    /// \param board The game board
    void RenderBoard(std::vector<std::vector<Shape>>& board);
    /// Loads image textures from file
    void LoadImageTextures();
    /// Clear image textures
    void ClearImageTextures();
    /// Initialized SDL2 resources
    void InitializeSDL2();
    /// Frees all SDL2 resources
    void DeInitializeSDL2();

    SDL_Window* gWindow = nullptr;
    SDL_Renderer* gRenderer = nullptr;

    // text
    TTF_Font* font = nullptr;
    SDL_Rect* rect = nullptr;
    SDL_Texture *texture;

    // images
    std::map<std::string, SDL_Texture*> imageTextures;

    const int IMAGE_BLOCK_WIDTH = 16*2;
    const int IMAGE_BLOCK_HEIGHT = 16*2;
    const std::string TEXTURES_PATH = "../textures";

};

#endif // !CPP_TETRIS_GUI_H
