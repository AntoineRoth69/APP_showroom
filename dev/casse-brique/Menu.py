import pygame
from Button import Button

MENU_BUTTON_TEXT = ["New Game", "Leaderboards", "Quit Game"]

class Menu:

    def __init__(self, gc):
        self.gc = gc
        self.gc.setMenu(self)      
        # Liste de coordonées du coin supérieur gauche du rectangle de chaque boutton  
        self.buttons = []
    
    def getGc(self):
        return self.gc

    def addPos(self, pos):
        self.buttons.append(pos)

    def removePos(self, pos):
        self.buttons.remove(pos)

    def getPos(self):
        return self.buttons

    def clearPos(self):
        self.buttons = []

    def draw(self):
        for i in MENU_BUTTON_TEXT:
            newButton = Button(self, self.gc.getMButWidth(), self.gc.getMButHeight())
            newButton.draw(MENU_BUTTON_TEXT.index(i))
            newButton.drawText(i)