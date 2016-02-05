// gobl.m.cpp

#include <goblb_board.h>
#include <goblb_space_state.h>

#include <iostream>
#include <sstream>

namespace {

void handleInput(goblb::Board& board, bool& black, const std::string& input)
{
    std::istringstream stream(input);
    unsigned int i;
    unsigned int j;

    if(!(stream >> i >> j))
    {
        std::cout << "Failed to parse move in the form \"i j\"."
                  << std::endl;

        return;
    }

    if(goblb::SpaceState::EMPTY != board.state(i, j))
    {
        std::cout << "There is already a stone at " << i
                  << ' ' << j << std::endl;

        return;
    }

    if(board.ko() && i == board.ko()->i() && j == board.ko()->j())
    {
        std::cout << "It is against the rules to play within a ko."
                  << std::endl;

        return;
    }

    board.play(
          i
        , j
        , black ? goblb::SpaceState::BLACK : goblb::SpaceState::WHITE
    );

    black = !black;
}

} // Close anonymous

int main(int argc, char* argv[])
{
    goblb::Board board;
    std::string line;

    bool black = true;

    std::cout << board << std::endl << std::endl
              << "BLACK'S TURN" << std::endl;

    while(std::getline(std::cin, line))
    {
        handleInput(board, black, line);

        std::cout << std::endl << board << std::endl;

        if(board.ko())
        {
            std::cout << "KO AT " << board.ko()->i()
                      << ' ' << board.ko()->j()
                      << std::endl;
        }

        std::cout << (black ? "BLACK" : "WHITE")
                  << "'S TURN" << std::endl;
    }

    std::cout << "---------------------------------" << std::endl
              << "---------- FINAL BOARD ----------" << std::endl
              << "---------------------------------" << std::endl
              << std::endl << board << std::endl;

    return 0;
}
