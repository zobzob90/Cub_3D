/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_npc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ertrigna <ertrigna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:17:16 by ertrigna          #+#    #+#             */
/*   Updated: 2025/08/07 13:29:56 by ertrigna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * init_npc - Initialise les valeurs par défaut d'un NPC
 * @npc: Pointeur vers la structure NPC à initialiser
 *
 * Cette fonction configure les valeurs initiales d'un NPC.
 * Elle définit la position de départ à (0,0), l'orientation vers l'est (dir_x=1,
 * dir_y=0), les points de vie à 100, le type à 0, et initialise les systèmes
 * d'animation et de détection du joueur. Cette initialisation garantit un état
 * cohérent pour tous les NPCs avant leur placement sur la carte.
 *
 * Valeurs initialisées :
 * - Position : (0, 0)
 * - Direction : Est (1, 0)
 * - Points de vie : 100
 * - Type : 0 (type par défaut)
 * - Vision du joueur : false
 * - Animation : frame 0, timer 0
 */
void	init_npc(t_npc *npc)
{
	npc->x = 0;
	npc->y = 0;
	npc->dir_x = 1;
	npc->dir_y = 0;
	npc->hp = 100;
	npc->type = 0;
	npc->see_player = false;
	npc->anim_frame = 0;
	npc->anim_timer = 0;
}

/**
 * count_npc - Compte le nombre de NPCs présents sur la carte
 * @map: Pointeur vers la structure de carte contenant la grille
 *
 * Return: Nombre total de NPCs trouvés sur la carte
 *
 * Cette fonction auxiliaire parcourt entièrement la grille de la carte
 * pour compter les caractères 'X' qui représentent les emplacements
 * des NPCs. Elle utilise une double boucle pour examiner chaque cellule
 * de la carte (de 0 à height-1 pour les lignes, de 0 à width-1 pour
 * les colonnes). Le compte total est retourné pour permettre l'allocation
 * du tableau de NPCs avec la taille exacte nécessaire.
 */
static	int	count_npc(t_map *map)
{
	int	i;
	int	j;
	int	npc_count;

	i = 0;
	npc_count = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 'X')
				npc_count++;
			j++;
		}
		i++;
	}
	return (npc_count);
}

/**
 * place_npc - Place les NPCs aux positions marquées 'X' sur la carte
 * @map: Pointeur vers la structure de carte contenant la grille et les NPCs
 *
 * Cette fonction parcourt la grille de la carte pour localiser tous les
 * caractères 'X' et créer un NPC à chaque position trouvée. Pour chaque
 * 'X' rencontré :
 * 1. Initialise un nouveau NPC avec init_npc()
 * 2. Définit sa position en coordonnées monde (centre de la cellule)
 * 3. Remplace le 'X' par '0' dans la grille (cellule vide)
 * 4. Incrémente le compteur de NPCs placés
 *
 * Les coordonnées sont converties en flottants avec un offset de 0.5
 * pour centrer le NPC dans sa cellule. Cette fonction doit être appelée
 * après l'allocation du tableau de NPCs avec la taille appropriée.
 */
static void	place_npc(t_map *map)
{
	int	i;
	int	j;
	int	npc_count;

	npc_count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->grid[i][j] == 'X')
			{
				init_npc(&map->npcs[npc_count]);
				map->npcs[npc_count].x = j + 0.5;
				map->npcs[npc_count].y = i + 0.5;
				map->grid[i][j] = '0';
				npc_count++;
			}
			j++;
		}
		i++;
	}
}

/**
 * init_npcs_from_map - Initialise tous les NPCs à partir de la carte
 * @map: Pointeur vers la structure de carte à traiter
 *
 * Cette fonction principale orchestre l'initialisation complète du système
 * de NPCs en analysant la carte. Processus :
 * 1. Compte les NPCs présents sur la carte avec count_npc()
 * 2. Si aucun NPC n'est trouvé, définit le tableau à NULL et termine
 * 3. Alloue la mémoire pour le tableau de NPCs selon le nombre trouvé
 * 4. Vérifie l'allocation mémoire et termine en cas d'échec
 * 5. Place tous les NPCs avec place_npc()
 *
 * Cette fonction est le point d'entrée principal pour l'initialisation
 * des NPCs et doit être appelée après le parsing complet de la carte.
 * En cas d'échec d'allocation, les NPCs ne seront pas initialisés mais
 * le jeu peut continuer sans eux.
 */
void	init_npcs_from_map(t_map *map)
{
	map->num_npcs = count_npc(map);
	if (map->num_npcs == 0)
	{
		map->npcs = NULL;
		return ;
	}
	map->npcs = malloc(sizeof(t_npc) * map->num_npcs);
	if (!map->npcs)
		return ;
	place_npc(map);
}
