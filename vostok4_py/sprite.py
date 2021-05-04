import pygame
import vostok4
import os

game_folder = os.path.dirname(__file__)
img_folder = os.path.join(game_folder, '..\\resources')
print(img_folder)
WIDTH = 1280
HEIGHT = 720

class Sprite(pygame.sprite.Sprite):
    def __init__(self, body : vostok4.Body):
        pygame.sprite.Sprite.__init__(self)
        self.body = body
        print("Hi!", body.get_sprite_name())
        self.image = pygame.image.load(os.path.join(img_folder, body.get_sprite_name()))
        self.rect = self.image.get_rect()
        print(self.image.get_rect().size[1])
        #self.body.set_collider_size(self.image.get_rect().size[1])
        self.image = self.image.convert()
        print("Hi.......")
        self.rect.center = (body.get_position().x, body.get_position().y)
        self.id = body.get_sceneID()

    def update(self):
        print(self.body.get_position().x + WIDTH/2, " ", self.body.get_position().y + HEIGHT/2)
        self.rect.center = (self.body.get_position().x + WIDTH/2, self.body.get_position().y + HEIGHT/2)
        