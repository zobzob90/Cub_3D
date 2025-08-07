/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_npc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:57:41 by ertrigna          #+#    #+#             */
/*   Updated: 2025/08/07 13:33:00 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/**
 * npc_moving - Vérifie si un NPC peut se déplacer vers une nouvelle position
 * @game: Pointeur vers la structure de jeu contenant la carte
 * @new_x: Nouvelle coordonnée X proposée pour le NPC
 * @new_y: Nouvelle coordonnée Y proposée pour le NPC
 *
 * Return: true si le mouvement est autorisé, false sinon
 *
 * Cette fonction valide qu'un NPC peut se déplacer vers les coordonnées
 * spécifiées en effectuant plusieurs vérifications :
 * 1. Conversion des coordonnées monde en coordonnées grille (troncature)
 * 2. Vérification que la position reste dans les limites de la carte
 * 3. Contrôle que la cellule de destination n'est pas un obstacle
 *
 * Les obstacles qui bloquent le mouvement sont :
 * - '1' : murs solides
 * - 'D' : portes fermées
 * Cette fonction est essentielle pour empêcher les NPCs de traverser
 * les murs ou de sortir de la carte, maintenant ainsi la cohérence
 * physique du monde de jeu.
 */
static bool	npc_moving(t_game *game, double new_x, double new_y)
{
	int	map_x;
	int	map_y;

	map_x = (int)new_x;
	map_y = (int)new_y;
	if (map_x < 0 || map_x >= game->map->width
		|| map_y < 0 || map_y >= game->map->height)
		return (false);
	if (game->map->grid[map_y][map_x] == '1'
		|| game->map->grid[map_y][map_x] == 'D')
		return (false);
	return (true);
}

/**
 * update_single_npc - Met à jour le comportement et la position d'un NPC
 * @game: Pointeur vers la structure de jeu contenant le joueur et la carte
 * @npc: Pointeur vers le NPC à mettre à jour
 *
 * Cette fonction implémente l'intelligence artificielle basique d'un NPC.
 * Elle gère la détection du joueur et le mouvement de poursuite :
 *
 * Algorithme de comportement :
 * 1. Calcule le vecteur distance entre le NPC et le joueur (dx, dy)
 * 2. Détermine la distance euclidienne avec sqrt(dx² + dy²)
 * 3. Si le joueur est dans un rayon de 5.0 unités :
 *    - Active la détection (see_player = true)
 *    - Normalise le vecteur direction vers le joueur
 *    - Calcule la nouvelle position avec une vitesse de 0.01
 *    - Valide et applique le mouvement si possible
 * 4. Sinon, désactive la détection (see_player = false)
 *
 * Cette approche simple mais efficace crée un comportement de poursuite
 * réaliste où les NPCs se dirigent vers le joueur quand il est proche.
 */
void	update_single_npc(t_game *game, t_npc *npc)
{
	int		new_x;
	int		new_y;
	double	dx;
	double	dy;
	double	distance;

	dx = game->player.x - npc->x;
	dy = game->player.y - npc->y;
	distance = sqrt(dx * dx + dy * dy);
	if (distance < 5.0)
	{
		npc->see_player = true;
		npc->dir_x = dx / distance;
		npc->dir_y = dy / distance;
		new_x = npc->x + npc->dir_x * 0.01;
		new_y = npc->y + npc->dir_y * 0.01;
		if (npc_moving(game, new_x, new_y))
		{
			npc->x = new_x;
			npc->y = new_y;
		}
	}
	else
		npc->see_player = false;
}

/**
 * update_npc - Met à jour tous les NPCs présents dans le jeu
 * @game: Pointeur vers la structure de jeu contenant la carte et les NPCs
 *
 * Cette fonction principale orchestre la mise à jour de tous les NPCs
 * du jeu à chaque frame. Elle gère deux aspects essentiels :
 *
 * 1. Animation des sprites :
 *    - Incrémente le timer d'animation de chaque NPC
 *    - Change de frame toutes les 40 ticks (anim_timer >= 40)
 *    - Cycle entre 3 frames d'animation (0, 1, 2) avec modulo
 *    - Remet le timer à zéro après changement de frame
 *
 * 2. Comportement et mouvement :
 *    - Appelle update_single_npc() pour chaque NPC
 *    - Gère la logique de poursuite du joueur
 *    - Valide et applique les mouvements
 *
 * Cette fonction doit être appelée à chaque frame de la boucle de jeu
 * pour maintenir l'animation fluide et le comportement réactif des NPCs.
 * Le timing d'animation (40 ticks) est calibré pour une fluidité visuelle
 * optimale avec la fréquence de rafraîchissement du jeu.
 */
void	update_npc(t_game *game)
{
	int		i;
	t_npc	*npc;

	i = 0;
	while (i < game->map->num_npcs)
	{
		npc = &game->map->npcs[i];
		npc->anim_timer++;
		if (npc->anim_timer >= 40)
		{
			npc->anim_frame = (npc->anim_frame + 1) % 3;
			npc->anim_timer = 0;
		}
		update_single_npc(game, npc);
		i++;
	}
}
