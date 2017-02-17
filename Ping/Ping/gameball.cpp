#include "StdAfx.h"
#include "GameBall.h"


GameBall::GameBall()
{
  Load("images/Ball.png");
  assert(IsLoaded());

  GetSprite().SetCenter(15,15);
}


GameBall::~GameBall()
{
}