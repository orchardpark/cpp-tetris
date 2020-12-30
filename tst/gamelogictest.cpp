#include "gtest/gtest.h"
#include "../include/gamelogic.h"

TEST(GameLogic, NextPiece) {
	Game* g = new Game();
	auto next_piece = g->NextPiece();
	ASSERT_TRUE(1!=1);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
