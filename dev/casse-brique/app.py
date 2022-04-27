import pygame
from GeneralConfiguration import GeneralConfiguration
from Menu import Menu
from Game import Game

from pygame.locals import (
    MOUSEBUTTONDOWN,
    USEREVENT,
    QUIT
)

def main():

    # Creates the GC object
    gc = GeneralConfiguration()

    # Creates the menu
    menu = Menu(gc)

    gc.display(False)

    # Runs the game until user want to quit
    while True:
        # Handle all events that can occur during a game
        for event in pygame.event.get():
            # Event that stop the game when you click on the close window button
            if event.type == QUIT:
                pygame.quit()
                break

            if event.type == MOUSEBUTTONDOWN:
                print(event)
                leftclick, mc, rc = pygame.mouse.get_pressed()
                if leftclick == 1:
                    mousePos = pygame.mouse.get_pos()
                    match gc.isOnButton(mousePos):
                        case -1:
                            continue
                        case 0:
                            g = Game()
                            gc.setGame(g)
                        case 1:
                            continue
                        case 2:
                            pygame.quit()
                            break
                        case _:
                            continue


if __name__ == "__main__":
    main()