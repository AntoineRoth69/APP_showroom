import pygame
import pyautogui
from pyrsistent import m
from Menu import Menu

SCREEN_WIDTH, SCREEN_HEIGHT = pyautogui.size()

class GeneralConfiguration:

    def __init__(self):
        self.initPygame()
        # Size of the menu buttons
        self.m_but_width = 400
        self.m_but_height = 100
        # Set the font for the game
        self.font = pygame.font.Font(None, 32)

    def initPygame(self):
        # Initialize pygame library
        pygame.init()
        # Set a new screen in full screen (We assume there that we always use the fisrt monitor)
        # self.screen = pygame.display.set_mode((SCREEN_WIDTH,SCREEN_HEIGHT-100))
        # For fullscreen mode
        self.screen = pygame.display.set_mode((SCREEN_WIDTH,SCREEN_HEIGHT-100), pygame.FULLSCREEN)
        
        # Sets the timer to check event every 100 ms
        pygame.time.set_timer(pygame.USEREVENT, 100)

    def setMenu(self, m):
        self.menu = m

    def setGame(self, g):
        self.game = g

    def getGame(self):
        return self.game

    def getMenu(self):
        return self.menu

    def getFont(self):
        return self.font

    def getMButWidth(self):
        return self.m_but_width

    def getMButHeight(self):
        return self.m_but_height
    
    def getScreenWidth(self):
        return self.screen.get_width()

    def getScreenHeight(self):
        return self.screen.get_height()
    
    def getScreenSize(self):
        return (self.screen.get_width(), self.screen.get_height())
    
    def getScreen(self):
        return self.screen

    def isOnButton(self, mousePos):
        buts = self.menu.getPos()
        for i in buts:
            if i[0]<mousePos[0] and mousePos[0]<i[0]+self.m_but_width and i[1]<mousePos[1] and mousePos[1]<i[1]+self.m_but_height:
                return buts.index(i)
        return -1

    def draw(self, game):
        # Set screen color to dark blue
        self.screen.fill((11, 11, 69))
        if game:
            pass
        else:
            self.getMenu().draw()

    def display(self, game):
        # Draw the new display to be displayed
        self.draw(game)

        # Update display and clears event
        pygame.display.flip()
        pygame.event.clear(pygame.USEREVENT)