/**********************************************************************************
// GravityGuy (C�digo Fonte)
// 
// Cria��o:     05 Out 2011
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Jogo estilo plataforma usando a engine do curso
//
**********************************************************************************/

#include "Engine.h"
#include "GravityGuy.h"
#include "Home.h"
#include "GameOver.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

// inicializa membros est�ticos da classe
Game*   GravityGuy::level = nullptr;
Player* GravityGuy::player = nullptr;
Audio*  GravityGuy::audio = nullptr;
bool    GravityGuy::viewBBox = false;

// ------------------------------------------------------------------------------

void GravityGuy::Init() 
{
    // cria sistema de �udio
    audio = new Audio();
    audio->Add(MENU, "Resources/Menu.wav");
    audio->Add(MUSIC1, "Resources/music1.wav");
    audio->Add(MUSIC2, "Resources/music2.wav");
    audio->Add(MUSIC3, "Resources/music3.wav");
    audio->Add(ENDING, "Resources/ending.wav");
    audio->Add(WALK, "Resources/walk_sound.wav", 5);
    audio->Volume(WALK, 1.5f);
    audio->Add(JUMP, "Resources/jump_sound.wav");
    audio->Volume(JUMP, 2);
    audio->Add(DASH, "Resources/dash_sound.wav");
    audio->Volume(DASH,1.5f);
    audio->Add(STRAWBERRY, "Resources/strawberry_sound.wav");
    audio->Add(DEATH, "Resources/death_sound.wav");
    audio->Add(GRAB, "Resources/grab_sound.wav");
    audio->Volume(GRAB,1.5f);




    // bounding box n�o vis�vel
    viewBBox = false;

    // cria jogador
    player = new Player();

    // inicializa n�vel de abertura do jogo
    level = new Home();
    level->Init();
}

// ------------------------------------------------------------------------------

void GravityGuy::Update()
{
    // habilita/desabilita visualiza��o da bounding box
    if (window->KeyPress('B'))
        viewBBox = !viewBBox;    

    // atualiza n�vel
    level->Update();
} 

// ------------------------------------------------------------------------------

void GravityGuy::Draw()
{
    // desenha n�vel
    level->Draw();
} 

// ------------------------------------------------------------------------------

void GravityGuy::Finalize()
{
    level->Finalize();

    delete player;
    delete audio;
    delete level;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura o motor
    engine->window->Mode(WINDOWED);
    engine->window->Size(800, 800);
    engine->window->Color(30, 50, 80);
    engine->window->Title("Gravity Guy");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new GravityGuy());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

