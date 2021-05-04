import vostok4
import pygame
from sprite import Sprite
import os


def process_graphics():
    clock.tick(FPS)
    print("tick")
    screen.fill((0,0,0))
    all_sprites.update()
    all_sprites.draw(screen)
    pygame.display.flip()


def process_events():
    global running
    for event in pygame.event.get():
        # проверить закрытие окна
        if event.type == pygame.QUIT:
            running = False


def remove_destroyed_sprites():
    global all_sprites
    sprites_to_remove = []
    for sprite in all_sprites.sprites():
        if (sprite.body.check_is_destroyed()):
            sprites_to_remove.append(sprite)
    all_sprites.remove(sprites_to_remove)


def find_sprite_by_id(id : int):
    global all_sprites
    for sprite in all_sprites.sprites():
        if sprite.id == id:
            return sprite
    return None


def update_sprite_list():
    global all_sprites
    vostok4.Scene.reset_body_index()
    cur_body = vostok4.Scene.get_cur_body()
    while not (cur_body is None):
        if find_sprite_by_id(cur_body.get_sceneID()) is None:
            all_sprites.add(Sprite(cur_body))
        cur_body = vostok4.Scene.get_next_body()


WIDTH = 1280
HEIGHT = 720
FPS = 30


if __name__ == "__main__":
    pygame.init()
    screen = pygame.display.set_mode((WIDTH, HEIGHT))
    vostok4.init_game(0)
    all_sprites = pygame.sprite.Group()

    running = True
    clock = pygame.time.Clock()

    while running:
        vostok4.Scene.process_physics()
        process_graphics()
        remove_destroyed_sprites()
        vostok4.Scene.manage_scene()
    
        update_sprite_list()
        process_events()

    pygame.quit()