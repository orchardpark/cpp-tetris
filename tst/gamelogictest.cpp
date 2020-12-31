#include "gtest/gtest.h"
#include "../include/gamelogic.h"
#include <set>
/*
* Tests if Nextpiece returns different kinds of pieces
*/
TEST(GameLogic, NextPiece) {
	Game* g = new Game();
	std::set<Shape,ShapeComparison> shapes;
	for (int i = 0; i < 1000; i++) {
		auto next_piece = g->NextPiece();
		shapes.insert(next_piece.GetShape());
	}
	ASSERT_GT(shapes.size(), 1);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
