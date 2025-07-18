/* Test program to verify memory leak fixes */
#include "cub3d.h"

int main(int argc, char **argv)
{
    t_game game;
    t_map map;

    if (argc != 2)
        return (ft_putstr_fd("Usage: ./test_memory <map.cub>\n", 2), 1);
    
    if (!parse_file(argv[1], &map))
        return (ft_putstr_fd("Error: Failed to parse file\n", 2), 1);
    
    init_game(&game);
    game.player = map.player;
    init_player_from_map(&game.player);
    game.map = &map;
    game.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
    game.img_data = mlx_get_data_addr(game.img,
            &game.bpp, &game.size_line, &game.endian);
    
    // Load initial textures (including gun)
    load_textures(&game);
    
    // Test gun firing multiple times to check for memory leaks
    printf("Testing gun firing sequences...\n");
    for (int i = 0; i < 5; i++) {
        gun_fire(&game);
        gun_stop_fire(&game);
    }
    printf("Gun firing test completed.\n");
    
    // Clean exit
    cleanup_game(&game);
    free_map(&map);
    
    printf("Test completed successfully.\n");
    return (0);
}
