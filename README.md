# 🕹️ Cub3D

Un moteur 3D inspiré de *Duke Nukem 3D*, réalisé en **C** avec la **MiniLibX** dans le cadre du cursus 42.  
Ce projet implémente le raycasting, un système de portes interactives, des PNJ animés, un mini-map et la gestion de textures PNG/XPM.

---
## 🚀 Installation & Lancement

bash
git clone git@github.com:zobzob90/Cub_3D.git
cd cub3d
make
./cub3D map/valid_map/tuto.cub
make test
test toutes les maps invalides

🏷️ Badges

Norminette Mandatory Bonus Score
✅ Statut du Projet
✅ Norminette : OK
✅ Partie obligatoire : OK
✅ Bonus : Fait
🏆 Score final : 125/100

## Screenshot
<img width="1902" height="1064" alt="image" src="https://github.com/user-attachments/assets/2651c012-a039-476c-adf6-0f3fea82a9a8" />

- 🎮 Contrôles

W / A / S / D    → déplacement
Alt puis ← / →   → rotation de la caméra
E                → ouvrir / fermer une porte
M                → Afficher / Fermer Minimap
Clic gauche      → tirer
Shit             → Sprinter
ESC              → quitter le jeu

- Arborescence
cub3d/
├── inc/                     # Headers principaux
│   └── cub3d.h
├── libft/                   # Libft + printf + get_next_line
│   ├── ft_*.c
│   ├── ft_printf/
│   ├── get_next_line/
│   └── libft.h
├── map/                     # Maps de test
│   ├── valid_map/           # Maps valides (jouables)
│   └── invalid_map/         # Maps invalides (tests parsing)
├── mlx/                     # MiniLibX (librairie graphique)
├── src/
│   ├── collision/           # Gestion des collisions
│   ├── event/               # Gestion des événements clavier/souris
│   ├── fire/                # Système de tir
│   ├── minimap/             # Affichage de la mini-carte
│   ├── move/                # Déplacement du joueur
│   ├── npc/                 # Gestion des PNJ et sprites animés
│   ├── parsing/             # Parsing et validation des fichiers .cub
│   ├── raycasting/          # Moteur de rendu 3D
│   └── utils/               # Fonctions utilitaires
├── texture/                 # Textures PNG & XPM
│   ├── wall/ gun/ npc/
│   └── ...
├── main.c                   # Point d'entrée
├── Makefile                 # Compilation

- 🛠️ Technologies

Langage : C
Graphisme : MiniLibX (X11 / PNG / XPM)
Compilation : Makefile
Conforme à la Norme 42


📜 Licence

Projet réalisé dans le cadre du cursus 42 – pas de licence commerciale.
🙋‍♂️ Auteur
👤 zobzob90
🔗 github.com/zobzob90
