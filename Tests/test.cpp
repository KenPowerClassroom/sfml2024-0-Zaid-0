#include "pch.h"

const int HEIGHT = 25;
const int WIDTH = 40;
const int tileSize = 18;

#include"../16_SFML_Games/Grid.h"
#include"../16_SFML_Games/Player.h"
#include "SnakeGameLogic.h"


// This test makes sure the snake actually moves down
TEST(SnakeGameLogicTest, SnakeMovesDownCorrectly) {
	SnakeGameLogic game;
	game.setDirection(Down);
	int oldY = game.snake[0].y;

	game.tick();

	EXPECT_EQ(game.snake[0].y, oldY + 1);
}


// This test checks that the snake gets longer when it eats a fruit.
TEST(SnakeGameLogicTest, FruitIsEatenAndSnakeGrows) {
	SnakeGameLogic game;

	game.fruit.x = game.snake[0].x;
	game.fruit.y = game.snake[0].y;

	int oldLength = game.snakeLength;

	game.tick();

	EXPECT_EQ(game.snakeLength, oldLength + 1);
}


// This test checks that the snake wraps around when it goes past the right edge
TEST(SnakeGameLogicTest, WrapAroundRightEdge) {
	SnakeGameLogic game;

	game.snake[0].x = GRID_WIDTH + 1;  //  out of bounds
	game.tick();

	EXPECT_EQ(game.snake[0].x, 0);
	//The snake should appear on the left side of the grid (x = 0)
	// instead of staying out of bounds.
}

// This test checks that the snake loses length when it runs into itself
TEST(SnakeGameLogicTest, SelfCollisionReducesLength) {
	SnakeGameLogic game;

	game.snakeLength = 5;

	game.snake[0] = { 5, 5 };
	game.snake[2] = { 5, 5 };

	game.tick();

	EXPECT_EQ(game.snakeLength, 2);
}


TEST(Grid, HasWallsAndInterior) {

	Grid grid;

	EXPECT_EQ(Grid::tile::WALL, grid.cell(0, 0));
	EXPECT_EQ(Grid::tile::WALL, grid.cell(24, 39));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(10, 10));

}

TEST(Grid, CreateNewWall) {

	Grid grid;

	grid.newWall(10, 10);
	EXPECT_EQ(Grid::tile::NEW_WALL, grid.cell(10, 10));

}


TEST(Grid, GridsIsClearedExceptForWalls) {

	Grid grid;

	grid.newWall(10, 10);

	grid.clear();
	EXPECT_EQ(Grid::tile::WALL, grid.cell(0, 0));
	EXPECT_EQ(Grid::tile::WALL, grid.cell(24, 39));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(10, 10));

}

//------------------------
//|                      |
//|                      |
//|         filled       |
//|                      |
//|                      |
//|----------------------|
//|                      |
//|                      |
//|         not filled   |
//|                      |
//|                      |
//------------------------

TEST(Grid, GridsIsFilledWithHorizWall) {

	Grid grid;

	for(int i=1;i<WIDTH-1;i++)
		grid.newWall(10, i);

	grid.markConnectedCellsNotToBeFilled(11, 1);

	grid.fillEmptyCells();

	EXPECT_EQ(Grid::tile::WALL, grid.cell(1, 1));
	EXPECT_EQ(Grid::tile::WALL, grid.cell(9, 38));

	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(11, 1));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(23, 38));

}

//------------------------
//|                      |
//|                      |
//|        not filled    |
//|                      |
//|                      |
//|-------------         |
//|            |         |
//|            |         |
//|   filled   |         |
//|            |         |
//|            |         |
//------------------------

TEST(Grid, GridsIsFilledWithHorizAndVertWall) {

	Grid grid;

	for (int x = 1; x < 10; x++)
		grid.newWall(10, x);
	for (int y = 10; y < HEIGHT-1; y++)
		grid.newWall(y, 10);

	grid.markConnectedCellsNotToBeFilled(2, 2);

	grid.fillEmptyCells();

	EXPECT_EQ(Grid::tile::WALL, grid.cell(11, 1));
	EXPECT_EQ(Grid::tile::WALL, grid.cell(23, 9));

	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(1, 1));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(9, 38));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(23, 38));


}


TEST(Player, ConstrainedHorizontallyRight) {

	Player p;

	p.x = 10, p.y = 10;

	p.goRight();

	for (int i = 0; i < 100; i++)
		p.move();

	EXPECT_EQ(10, p.y);
	EXPECT_EQ(WIDTH-1, p.x);
}

TEST(Player, ConstrainedHorizontallyLeft) {

	Player p;

	p.x = 10, p.y = 10;

	p.goLeft();

	for (int i = 0; i < 100; i++)
		p.move();

	EXPECT_EQ(10, p.y);
	EXPECT_EQ(0, p.x);
}

TEST(Player, ConstrainedVerticallyUp) {

	Player p;

	p.x = 10, p.y = 10;

	p.goUp();

	for (int i = 0; i < 100; i++)
		p.move();

	EXPECT_EQ(0, p.y);
	EXPECT_EQ(10, p.x);
}

TEST(Player, ConstrainedDiagonallyFast) {

	Player p;

	p.x = 10, p.y = 10;
	p.dx = 5;
	p.dy = 6;

	
	for (int i = 0; i < 100; i++)
		p.move();

	EXPECT_EQ(HEIGHT-1, p.y);
	EXPECT_EQ(WIDTH-1, p.x);
}

