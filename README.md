🕹️ Cub3D

Un moteur 3D inspiré de Duke Nukem 3D, réalisé en C avec la MiniLibX dans le cadre du cursus 42.
Le projet implémente :

    🎯 Raycasting façon Wolfenstein 3D

    🚪 Portes interactives

    🧍 PNJ animés

    🗺 Mini-map

    🖼 Textures PNG/XPM

    ✅ Parsing strict des maps

🚀 Installation & Lancement

    git clone git@github.com:zobzob90/Cub_3D.git
    
    cd cub3d
    
    make
    
    ./cub3D map/valid_map/tuto.cub

📌 Pour tester toutes les maps invalides :

    make test

| Partie             | État         |
| ------------------ | ------------ |
| Norminette         | ✅ OK         |
| Partie obligatoire | ✅ OK         |
| Bonus              | ✅ Fait       |
| **Score final**    | 🏆 125 / 100 |


📸 Screenshot
<img width="1902" height="1064" alt="Cub3D Screenshot" src="https://github.com/user-attachments/assets/2651c012-a039-476c-adf6-0f3fea82a9a8" />

- 🎮 Contrôles

| Touche / Action   | Effet                        |
| ----------------- | ---------------------------- |
| **W / A / S / D** | Déplacement                  |
| **Alt** + ← / →   | Rotation caméra              |
| **E**             | Ouvrir / fermer une porte    |
| **M**             | Afficher / fermer la minimap |
| **Clic gauche**   | Tirer                        |
| **Shift**         | Sprinter                     |
| **ESC**           | Quitter le jeu               |


## 📂 Arborescence

    cub3d/
    ├── inc/ # Headers principaux
    │ └── cub3d.h
    ├── libft/ # Libft + printf + get_next_line
    │ ├── ft_*.c
    │ ├── ft_printf/
    │ ├── get_next_line/
    │ └── libft.h
    ├── map/ # Maps de test
    │ ├── valid_map/ # Maps valides
    │ └── invalid_map/ # Maps invalides
    ├── mlx/ # MiniLibX (librairie graphique)
    ├── src/
    │ ├── collision/ # Gestion des collisions
    │ ├── event/ # Événements clavier / souris
    │ ├── fire/ # Système de tir
    │ ├── minimap/ # Mini-carte
    │ ├── move/ # Déplacement joueur
    │ ├── npc/ # PNJ & sprites animés
    │ ├── parsing/ # Parsing fichiers .cub
    │ ├── raycasting/ # Moteur de rendu 3D
    │ └── utils/ # Fonctions utilitaires
    ├── texture/ # Textures PNG & XPM
    ├── main.c # Point d'entrée

## 🛠️ Technologies

    Langage : C

    Graphisme : MiniLibX (X11 / PNG / XPM)

    Compilation : Makefile

    Norme : Conforme à la Norme 42

## 📜 Licence

    Projet réalisé dans le cadre du cursus 42 – pas de licence commerciale.
    🙋‍♂️ Auteur
    👤 zobzob90
    🔗 github.com/zobzob90
