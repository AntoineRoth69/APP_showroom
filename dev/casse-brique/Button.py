import pygame

class Button:

    def __init__(self, parent, width, height):
        self.parent = parent
        self.width = width
        self.height = height

    def getLocation(self):
        return self.location

    def getWidth(self):
        return self.width

    def getHeight(self):
        return self.height

    def getParent(self):
        return self.parent

    def draw(self, num):
        img = pygame.draw.rect(self.parent.getGc().getScreen(), (0, 0, 169), [(self.parent.getGc().getScreenWidth()-self.width)//2, (num)*((self.parent.getGc().getScreenHeight()-3*self.height)//6)+num*self.height+((self.parent.getGc().getScreenHeight()-3*self.height)//3), self.width, self.height], border_radius=10)
        self.location = img.topleft
        self.parent.addPos(self.location)

    def drawText(self, str):
        img = self.parent.getGc().getFont().render(str, True, (255, 255, 255))
        self.parent.getGc().getScreen().blit(img, [self.location[0]+(self.width-img.get_width())//2, self.location[1]+(self.height-img.get_height())//2])