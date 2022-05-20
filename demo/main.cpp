#include <iostream>
#include <SDL2/SDL.h>
#include <cstdlib>
#include <random>
#define LARGEUR 720
#define HAUTEUR 640
// Globals variables
SDL_Window* g_pWindow = NULL;
SDL_Renderer* g_pRenderer = NULL;
bool g_pRunning = false;
SDL_Event g_pEvent;
const int line = LARGEUR, column = HAUTEUR;
bool cells[line][column];
// Prototypes functions
void initCells(void);
void init(void);
void handleEvents(void);
void update(void);
void render(void);
void clean(void);
int main(int argc, char* argv[])
{
	init();
	while (g_pRunning)
	{
		handleEvents();
		update();
		render();
	}
	clean();
	return 0;
}
void init()
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		// Something is wrong !
		std::cout << "Error to initialize SDL ! "<< std::endl;
		g_pRunning = false;
	}
	else
	{
		// Success to initialize SDL2
		g_pWindow = SDL_CreateWindow("Jeux de la Vie",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			LARGEUR,
			HAUTEUR,
			SDL_WINDOW_SHOWN);
		if (g_pWindow == NULL)
		{
			// Something is wrong !
			std::cout<<"Error to create a window"<< std::endl;
			g_pRunning = false;
		}
		else
		{
			// Success to initalize SDL2 and to create a window
			g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
			if(g_pRenderer == NULL)
			{
				// Something is wrong !
				std::cout << "Error to create a render"<< std::endl;
				g_pRunning = false;
			}
			else
			{
				// Success to initialize SDL, to create a window and to create a render
				SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);
				SDL_RenderClear(g_pRenderer);
                initCells();
				g_pRunning = true;
			}
		}
	}
}
void initCells()
{
    // Initialization of cells here !
    int val;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 6);
    for(int i=0; i< LARGEUR+10; i+=10)
    {
        for(int j=0; j< HAUTEUR+10; j+=10)
        {
            val = dist(gen);
            if(val >= 5 )
            {
                cells[i][j] = true;

            }
            else
            {
                cells[i][j] = false;
            }
        }
    }
}
void showCells(int xpos, int ypos)
{
    SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
    SDL_Rect position = {xpos, ypos, 10, 10};

    SDL_RenderFillRect(g_pRenderer, &position);
}
void dontShowCells(int xpos, int ypos)
{
    SDL_SetRenderDrawColor(g_pRenderer, 255, 255, 255, 255);
    SDL_Rect position = {xpos, ypos, 10, 10};

    SDL_RenderFillRect(g_pRenderer, &position);
}
void printCells()
{
    for(int i=0; i<LARGEUR+10; i+=10)
    {
        // Here we are at the line i
        for(int j=0; j<HAUTEUR+10; j+=10)
        {
            // here we are at the column j
            if(cells[i][j] == true)
            {
                showCells(j, i);
            }
            else
            {
                dontShowCells(j, i);
            }
        }
    }
}
void handleEvents(void)
{
	if (SDL_PollEvent(&g_pEvent))
	{
		switch (g_pEvent.type)
		{
		case SDL_QUIT :
			g_pRunning = false;
			break;
		}
	}
}
void update(void)
{
    for(int i=0; i<LARGEUR+10; i+=10)
    {
        for(int j=0; j<HAUTEUR+10; j+=10)
        {
            if(cells[i][j] == true)
            {
                int posx = i-10;
                int posy = j-10;
                int cellsAlived =0;
                for(int k=0; k<40; k+=10)
                {
                    for(int l=0; l<40; l+=10)
                    {
                        if((posx+k!=i)&&(posy+l!=j))
                        {
                            if(cells[posx+k][posy+l] == true)
                            {
                                cellsAlived++;
                            }
                        }
                    }
                }
                // Verifications
                if(cellsAlived>=2 && cellsAlived<=3)
                {
                    cells[i][j] = true;
                }
                else
                {
                    cells[i][j] = false;
                }
            }
            else
            {
                int posx = i-10;
                int posy = j-10;
                int cellsAlived =0;
                for(int k=0; k<40; k+=10)
                {
                    for(int l=0; l<40; l+=10)
                    {
                        if((posx+k!=i)&&(posy+l!=j))
                        {
                            if(cells[posx+k][posy+l] == true)
                            {
                                cellsAlived++;
                            }
                        }
                    }
                }
                if(cellsAlived == 3)
                {
                    cells[i][j] = true;
                }
                else
                {
                    cells[i][j] = false;
                }
            }
        }
    }
    for(int i=0; i<LARGEUR+10; i+=10)
    {
        for(int j=0; j<HAUTEUR+10; j+=10)
        {
            cells[i][j] = cells[i][j];
        }
    }
}
void render(void)
{
    printCells();
    SDL_RenderPresent(g_pRenderer);
}
void clean(void)
{
	SDL_DestroyRenderer(g_pRenderer);
	SDL_DestroyWindow(g_pWindow);
	SDL_Quit();
}
