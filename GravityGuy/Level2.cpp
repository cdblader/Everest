/**********************************************************************************
// Level2 (C�digo Fonte)
//
// Cria��o:     14 Fev 2013
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   N�vel 1 do jogo
//
**********************************************************************************/

#include "GravityGuy.h"
#include "Home.h"
#include "Level2.h"
#include "GameOver.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"

#include <string>
#include <fstream>
#include "Spike.h"
#include "Strawberry.h"
using std::ifstream;
using std::string;

// ------------------------------------------------------------------------------
// Inicializa membros est�ticos da classe

Scene* Level2::scene = nullptr;
Font* Level2::font = nullptr;            // fonte para texto

// ------------------------------------------------------------------------------

void Level2::Init()
{
    // cria gerenciador de cena
    scene = new Scene();

    // pano de fundo do jogo
    backg = new Background(Color{ 1,1,1,1 });
    scene->Add(backg, STATIC);

    // adiciona jogador na cena
    scene->Add(GravityGuy::player, MOVING);

    // adiciona jogador na cena
    strawberry = new Strawberry(window->CenterX() + 300, window->Height() - 100);
    scene->Add(strawberry, MOVING);

    // ----------------------
    // plataformas
    // ----------------------

    Platform* plat;
    Spike* spike;
    float posX, posY;
    uint  platType;
    Color white{ 1,1,1,1 };

    // cria fontes para exibi��o de texto
    font = new Font("Resources/Tahoma14.png");
    font->Spacing("Resources/Tahoma14.dat");

    plat = new Platform(window->CenterX() - 550, window->Height() - 20, 2, white);
    scene->Add(plat, STATIC);

    plat = new Platform(window->CenterX() + 600, window->Height() - 20, 2, white);
    scene->Add(plat, STATIC);

    plat = new Platform(window->CenterX() - 400, 0, 2, white);
    scene->Add(plat, STATIC);

    plat = new Platform(window->CenterX() + 400, 0, 2, white);
    scene->Add(plat, STATIC);

    plat = new Platform(window->CenterX(), window->Height() + 280, 3, white);
    scene->Add(plat, STATIC);

    plat = new Platform(window->CenterX() + 200, window->Height() - 200, 2, white);
    scene->Add(plat, STATIC);

    plat = new Platform(window->Width() - 20, window->CenterY() + 400, 3, white);
    scene->Add(plat, STATIC);

    plat = new Platform(20, window->CenterY(), 3, white);
    scene->Add(plat, STATIC);

    spike = new Spike(window->CenterX() + 100, window->CenterY() + 100, 3, white);
    scene->Add(spike, STATIC);
    // ----------------------

    // inicia com m�sica
    GravityGuy::audio->Frequency(MUSIC, 0.94f);
    GravityGuy::audio->Frequency(TRANSITION, 1.0f);
    //GravityGuy::audio->Play(MUSIC);


}

// ------------------------------------------------------------------------------

void Level2::Update()
{


    if (GravityGuy::player->isDead)
    {
        if (GravityGuy::player->Y() < window->Height())
        {
            explosion = new Explosion(GravityGuy::player->X(), GravityGuy::player->Y(), scene);
        }
        else {
            explosion = new Explosion(GravityGuy::player->X(), window->Height() - 20, scene);
        }

        scene->Add(explosion, STATIC);
        strawberry->Reset();
        GravityGuy::player->deathCount++;
        GravityGuy::player->Dead();
        GravityGuy::player->MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
        GravityGuy::player->Reset();

    }

    Color deathColor{ 0.65f, 0.65f, 0.65f, 1.0f };

    deathCount.str("");
    deathCount << "x" << GravityGuy::player->deathCount;
    font->Draw(100, 100, deathCount.str(), deathColor);


    Color strawberryColor{ 1.0f, 0.5f, 0.5f, 1.0f };
    strawberryCount.str("");
    strawberryCount << "x" << GravityGuy::player->strawberryCount << " /5";
    font->Draw(100, 120, strawberryCount.str(), strawberryColor);

    if (window->KeyPress(VK_ESCAPE))
    {
        GravityGuy::audio->Stop(MUSIC);
        GravityGuy::NextLevel<Home>();
        GravityGuy::player->Reset();
    }
    else if (GravityGuy::player->Top() > window->Height())
    {
        GravityGuy::player->isDead = true;
    }
    else if (GravityGuy::player->Right() > window->Width() || window->KeyPress('N'))
    {
        GravityGuy::player->MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
        GravityGuy::player->Reset();
        if (strawberry->following)
        {
            GravityGuy::player->strawberryCount++;
            strawberry->Reset();
        }
        GravityGuy::audio->Stop(MUSIC);
        GravityGuy::NextLevel<GameOver>();
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }


}

// ------------------------------------------------------------------------------

void Level2::Draw()
{
    backg->Draw();
    scene->Draw();

    if (GravityGuy::viewBBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level2::Finalize()
{
    scene->Remove(GravityGuy::player, MOVING);
    delete scene;
}

// ------------------------------------------------------------------------------
