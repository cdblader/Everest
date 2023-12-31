/**********************************************************************************
// Platform (C�digo Fonte)
// 
// Cria��o:     21 Abr 2012
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Plataformas do jogo
//
**********************************************************************************/

#include "Platform.h"
#include "Player.h"

// ---------------------------------------------------------------------------------

Platform::Platform(float posX, float posY, uint platType, Color tint) : color(tint)
{
    switch (platType)
    {
    case SMALL:  platform = new Sprite("Resources/SmallGray.png"); type = SMALL; break;
    case MEDIUM: platform = new Sprite("Resources/MediumGray.png"); type = MEDIUM; break;
    case LARGE:  platform = new Sprite("Resources/LongGray.png"); type = LARGE; break;
    case FINISH: platform = new Sprite("Resources/LongGrayV.png"); type = FINISH; break;
    }


        BBox(new Rect(-platform->Width() / 2.0f,
            -platform->Height() / 2.0f,
            platform->Width() / 2.0f,
            platform->Height() / 2.0f));


    MoveTo(posX, posY, Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Platform::~Platform()
{
    delete platform;
}

// -------------------------------------------------------------------------------

void Platform::Update()
{

}

// -------------------------------------------------------------------------------

void Platform::OnCollision(Object* obj)
{
    if (obj->Type() == 0)
    {
        Player* player = (Player*)obj;

        // Colis�es eixo X

        //Plataforma na direita
        if (player->X() + 5 < x - platform->Width() / 2 + 10) {
            if (player->Y() + 15 < y - platform->Height() / 2)
            {
                player->MoveTo(x - platform->Width() / 2 - 5, player->Y(), Layer::MIDDLE);
            }
            else {

                if(window->KeyDown(VK_RIGHT))
                player->MoveTo(x - platform->Width() / 2 - 15, player->Y(), Layer::MIDDLE);
            }

            if (player->dashing)
            {
                player->velX = 0;
            }
            if (window->KeyDown(VK_RIGHT) && player->hasSideJump && !player->jumping)
            {
                if (player->hasDash)
                {
                    player->anim->Select(GRABINGRIGHT);
                }
                else {
                    player->anim->Select(GRABINGRIGHTB);
                }
                player->Translate(0, -150 * gameTime);
                player->sideJumping = false;
                if (window->KeyPress(VK_UP) && !player->dashing) {
                    player->jumping = false;
                    player->MoveTo(x - platform->Width() / 2 - 25, player->Y(), Layer::MIDDLE);
                    player->sideJumping = true;
                    player->sideJumpSide = 1;
                    player->sideJumpTimer->Start();
                    player->hasSideJump = false;
                }
            }


        }
        else

            //Plataforma na esquerda
            if (player->X() - 5 > x + platform->Width() / 2 -10) {
                if (player->Y() + 15 < y - platform->Height() / 2)
                {
                    player->MoveTo(x + platform->Width() / 2 + 5, player->Y(), Layer::MIDDLE);
                }
                else {
                    if (window->KeyDown(VK_LEFT))
                    player->MoveTo(x + platform->Width() / 2 + 15, player->Y(), Layer::MIDDLE);
                }

                if (player->dashing)
                {
                    player->velX = 0;
                }
                if (window->KeyDown(VK_LEFT) && player->hasSideJump && !player->jumping)
                {
                    
                    if (player->hasDash)
                    {
                        player->anim->Select(GRABINGLEFT);
                    }
                    else {
                        player->anim->Select(GRABINGLEFTB);
                    }
                    player->Translate(0, -150 * gameTime);
                    player->sideJumping = false;
                    if (window->KeyPress(VK_UP) && !player->dashing) {
                        player->jumping = false;
                        player->MoveTo(x + platform->Width() / 2 + 25, player->Y(), Layer::MIDDLE);
                        player->sideJumping = true;
                        player->sideJumpSide = 0;
                        player->sideJumpTimer->Start();
                        player->hasSideJump = false;
                    }
                }

            }
            else
                // Colis�es eixo Y
                    //Plataforma abaixo
                if (player->Y() < y - platform->Height() / 2) {
                    player->MoveTo(player->X(), y - platform->Height() / 2 - 20, Layer::MIDDLE);

                    if (player->X() > x - platform->Width() / 2 && player->X() < x + platform->Width() / 2 || player->X() < x + platform->Width() / 2 && player->X() > x - platform->Width() / 2)
                    {
                        if (!player->dashing) {
                            player->hasDash = true;
                        }
                        player->hasSideJump = true;
                        player->onFloor = true;
                    }

                    if (player->dashing && player->dashSide == 7 || player->dashSide == 5)
                    {
                        if (window->KeyDown(VK_SPACE)) {
                            player->MoveTo(player->X(), y - platform->Height() / 2 - 25, Layer::MIDDLE);
                            player->hasDash = true;
                            player->waveDashing = true;
                        }


                    }
                    else if (window->KeyPress(VK_UP)) {
                        if (player->X() > x - platform->Width() / 2 && player->X() < x + platform->Width() / 2 || player->X() < x + platform->Width() / 2 && player->X() > x - platform->Width() / 2)
                        {
                            player->MoveTo(player->X(), y - platform->Height() / 2 - 25, Layer::MIDDLE);
                            player->jumping = true;
                            player->jumpTimer->Start();
                        }

                    }
                }
                else
                    //Plataforma acima
                    if (player->Y() > y + platform->Height() / 2) {
                        player->MoveTo(player->X(), y + platform->Height() / 2 + 25, Layer::MIDDLE);
                        player->jumping = false;
                    }

    }

        


}