#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	Reset();
}

void Game::Reset()
{
	Console::SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Console::CursorVisible(false);
	paddle.width = 12;
	paddle.height = 2;
	paddle.x_position = 32;
	paddle.y_position = 30;

	ball.visage = 'O';
	ball.color = ConsoleColor::Cyan;
	ResetBall();

	// TODO #2 - Add this brick and 4 more bricks to the vector
    for (int i = 0, x = 5; i < 5; i++, x += 15)
	
	brick.width = 10;
	brick.height = 2;
	brick.x_position = 5;
	brick.y_position = 5;
	brick.doubleThick = true;
	brick.color = ConsoleColor::DarkGreen;
    bricks.push_back(brick);

	/*Box brick1;
	brick1.width = 10;
	brick1.height = 2;
	brick1.x_position = 20;
	brick1.y_position = 5;
	brick1.doubleThick = true;
	brick1.color = ConsoleColor::DarkGreen;
	bricks.push_back(brick1);

	Box brick2;
	brick2.width = 10;
	brick2.height = 2;
	brick2.x_position = 30;
	brick2.y_position = 5;
	brick2.doubleThick = true;
	brick2.color = ConsoleColor::DarkGreen;
	bricks.push_back(brick2);

	Box brick3;
	brick3.width = 10;
	brick3.height = 2;
	brick3.x_position = 40;
	brick3.y_position = 5;
	brick3.doubleThick = true;
	brick3.color = ConsoleColor::DarkGreen;
	bricks.push_back(brick3);

	Box brick4;
	brick4.width = 10;
	brick4.height = 2;
	brick4.x_position = 50;
	brick4.y_position = 5;
	brick4.doubleThick = true;
	brick4.color = ConsoleColor::DarkGreen;
	bricks.push_back(brick4);*/
	//for (int i = 0; i < 5; i++)
	//{
		//brick.x_position = i * 15;
		//bricks.push_back(brick);
	//}
}

void Game::ResetBall()
{
	ball.x_position = paddle.x_position + paddle.width / 2;
	ball.y_position = paddle.y_position - 1;
	ball.x_velocity = rand() % 2 ? 1 : -1;
	ball.y_velocity = -1;
	ball.moving = false;
}

bool Game::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x1)
		return false;

	if (GetAsyncKeyState(VK_RIGHT) && paddle.x_position < WINDOW_WIDTH - paddle.width)
		paddle.x_position += 2;

	if (GetAsyncKeyState(VK_LEFT) && paddle.x_position > 0)
		paddle.x_position -= 2;

	if (GetAsyncKeyState(VK_SPACE) & 0x1)
		ball.moving = !ball.moving;

	if (GetAsyncKeyState('R') & 0x1)
		Reset();

	ball.Update();
	CheckCollision();
	return true;
}

//  All rendering should be done between the locks in this function
void Game::Render() const
{
	Console::Lock(true);
	Console::Clear();

	
	paddle.Draw();
	ball.Draw();

	// TODO #3 - Update render to render all bricks

    for (int i = 0; i < bricks.size(); i++)
    {
        bricks[i].Draw();
    }
    Console::Lock(false);

    Console::SetCursorPosition(20, 20);
    Console::ForegroundColor(White);
    printf("Press Space to begin or pause the game.");
    Console::CursorVisible(false);

	//for (int i = 0; i < bricks.size(); i++)
	//{
		//bricks[i].Draw();
//	}
	//if (ball.y_position == WINDOW_HEIGHT)
	//{

		//Console::SetCursorPosition(5, 5);
		//std::cout << "YOU LOSE! Press R to reset";
	//}



	Console::Lock(false);

	/*Console::SetCursorPosition(20, 20);
	Console::ForegroundColor(White);
	printf("Press Space to begin or pause the game. ");
	Console::CursorVisible(false);*/
}

void Game::CheckCollision()
{
	// TODO #4 - Update collision to check all bricks
    int size = bricks.size();
	for (int i = 0; i < bricks.size(); i++)
	{
		if (bricks[i].Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			bricks[i].color = ConsoleColor(bricks[i].color - 1);
			ball.y_velocity *= -1;

			// TODO #5 - If the ball hits the same brick 3 times (color == black), remove it from the vector
			if (bricks[i].color == Black)
			{
				bricks.erase(bricks.begin() + i);
				i--;
                size--;
			}

		}
	}
	// TODO #6 - If no bricks remain, pause ball and display victory text with R to reset

    if (size == 0)
    {
        Console::SetCursorPosition(20, 20);
        Console::ForegroundColor(White);
        printf("     You win! Type R to play again.    ");
        char response;
        cin >> response;
        if (tolower(response) == tolower('R'))
        {
            Reset();
        }
    }
    if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
    {
        ball.y_velocity *= -1;
    }

    //continue;

	/*if (bricks.empty() == true)
	{
		ball.moving = false;
		std::cout << "You Win! (Press 'R' to reset the game.)";
	}

	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}*\




	/*if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}*/


	// TODO #7 - If ball touches bottom of window, pause ball and display defeat text with R to reset
    if (ball.y_position >= WINDOW_HEIGHT)
    {
        Console::SetCursorPosition(20, 20);
        Console::ForegroundColor(White);
        printf("     You lose. Type R to play again.   ");
        char response;
        cin >> response;
        if (tolower(response) == tolower('R'))
        {
            for (int x = 0; x < bricks.size(); x++)
            {
                bricks.erase(bricks.begin() + x); //delete remaining bricks
            }
            bricks.clear();
            Reset();
        }
    }

	// if (ball.y_position == WINDOW_HEIGHT)
	// {
	//	ball.moving = false;
		//Console::SetCursorPosition(5, 5);
		//std::cout << "YOU LOSE! Press R to reset";
	//}*\
	


}
