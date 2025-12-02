#include "Game.h"

#include "Entity/Entity2D/Shape/Square/Square.h"
#include "Entity/Entity2D/Shape/Triangle/Triangle.h"
#include "TextureImporter/TextureImporter.h"
#include "CollisionManager/CollisionManager.h"
#include "Input/Input.h"

Game::Game(int width, int height) : BaseGame(width, height)
{
	Init();
}

Game::~Game()
{
	Unload();
}

void Game::Init()
{

	// ------- SAMUS -------
	TextureImporter textureImport;

	textureImport.LoadTexture("Sprites/Samus Aran Sprite Sheet.png");

	samus = new Sprite(textureImport.GetLoadedTexture(), Vector4(1, 1, 1, 1), GetRenderer());

	pos = Vector3(width / 2, height / 2, 0);
	samus->SetPosition(pos);

	scale = Vector3(width / 2, width / 2, 0);
	samus->SetScale(scale * 0.4f);

	Vector2 textureSize = Vector2(860, 762);
	Vector2 frameArea = Vector2(68, 65);

	idle = new Animation(Vector2(20, textureSize.y - 40), frameArea, textureSize, 2, 1);

	frameArea = Vector2(80, 60);

	walkingRight = new Animation(Vector2(20, textureSize.y - 215), frameArea, textureSize, 5, 1);

	walkingLeft = new Animation(Vector2(20, textureSize.y - 292), frameArea, textureSize, 5, 1);

	samus->SetAnimation(idle);

	// ------- RED SQUARE -------

	redSquare = new Square(GetRenderer(), Vector4(1, 0, 0, 1));
	redSquare->SetScale(samus->GetScale());
	redSquare->SetPosition(Vector3(samus->GetPos().x - redSquare->GetScale().x, samus->GetPos().y, samus->GetPos().z));

	startingScale = redSquare->GetScale();
	endScale = startingScale * 1.3f;

	// ------- BLUE SQUARE -------

	blueSquare = new Square(GetRenderer(), Vector4(0, 0, 1, 0.5f));
	blueSquare->SetPosition(Vector3(width / 2, height / 2, 0));
	blueSquare->SetScale(samus->GetScale() * 2);
}

void Game::Update()
{
	float delta = GetDeltaTime();

	if (!collitionDetected)
	{
		if (Input::IsKeyPressed(Keys::A) && samus)
		{
			samus->SetAnimation(walkingRight);
			samus->Translate(Vector3::Right() * movementSpeed * delta);
		}
		else if (Input::IsKeyPressed(Keys::D) && samus)
		{
			samus->SetAnimation(walkingLeft);
			samus->Translate(Vector3::Left() * movementSpeed * delta);
		}
		else
			samus->SetAnimation(idle);
	}
	else if (samus)
	{
		samus->SetPosition(Vector3(redSquare->GetPos().x + redSquare->GetScale().x, samus->GetPos().y, 0));
		samus->SetAnimation(idle);
	}

	if (Input::IsKeyPressed(Keys::LEFT))
		redSquare->Rotate(180 * delta);
	else if (Input::IsKeyPressed(Keys::RIGHT))
		redSquare->Rotate(-180 * delta);

	if (Input::IsKeyPressed(Keys::UP))
		redSquare->Scale(Vector3(100 * delta, 100 * delta, 0));
	else if (Input::IsKeyPressed(Keys::DOWN))
		redSquare->Scale(Vector3(-100 * delta, -100 * delta, 0));

	collitionDetected = CollisionManager::CheckCollision(samus, redSquare);


	if (blueSquare->GetPos().x <= width - 100.0f && isGoingLeft == true)
	{
		blueSquare->Translate(250 * delta, 0);
		blueSquare->SetRotation(0.0f);

		if (blueSquare->GetPos().x >= width - 100.0f)
		{
			isGoingLeft = false;
			isGoingRight = true;
		}
	}
	else if (blueSquare->GetPos().x >= 100.0f && isGoingRight == true)
	{
		blueSquare->Translate(-250 * delta, 0);

		blueSquare->SetRotation(180.0f);

		if (blueSquare->GetPos().x <= 100.0f)
		{
			isGoingLeft = true;
			isGoingRight = false;
		}
	}

	if (samus)
		samus->Update();

	if (samus)
		samus->Draw();

	if (redSquare)
		redSquare->Draw();

	if (blueSquare)
		blueSquare->Draw();
}

void Game::Unload()
{
	delete samus;
	delete idle;
	delete walkingRight;
	delete walkingLeft;

	delete redSquare;
	delete blueSquare;
}
