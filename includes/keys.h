/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:07:22 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/26 15:43:27 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ═══════════════════════════════════════════════════════════
// 🎮 CUB3D - CONFIGURATION COMPLÈTE LINUX
// ═══════════════════════════════════════════════════════════

#ifndef KEYS_H
# define KEYS_H

//═══════════════════════════════════════════════════════════
// 🗺️ ÉLÉMENTS DE LA CARTE
//═══════════════════════════════════════════════════════════

# define WALL               '1'     // Mur
# define FLOOR              '0'     // Sol/espace vide
# define PLAYER_NORTH       'N'     // Joueur face Nord
# define PLAYER_SOUTH       'S'     // Joueur face Sud  
# define PLAYER_EAST        'E'     // Joueur face Est
# define PLAYER_WEST        'W'     // Joueur face Ouest
# define SPRITE             '2'     // Objets/sprites

//═══════════════════════════════════════════════════════════
// 🖥️ CONFIGURATION FENÊTRE
//═══════════════════════════════════════════════════════════

# define WIN_WIDTH       1920    // Largeur fenêtre
# define WIN_HEIGHT      1080    // Hauteur fenêtre  
# define WIN_TITLE       "Cub3D - Optimized"

//═══════════════════════════════════════════════════════════
// 🎮 PARAMÈTRES DE GAMEPLAY
//═══════════════════════════════════════════════════════════

# define PLAYER_SPEED       0.05    // Vitesse déplacement
# define ROTATION_SPEED     0.03    // Vitesse rotation
# define FOV                66      // Champ de vision (degrés)

// 🎯 Vitesses alternatives
# define RUN_MULTIPLIER     2.0     // Multiplicateur course (Shift)
# define WALK_MULTIPLIER    0.5     // Multiplicateur marche lente (Ctrl)
# define MOUSE_SENSITIVITY  0.002   // Sensibilité souris

//═══════════════════════════════════════════════════════════
// 🎨 PALETTE DE COULEURS
//═══════════════════════════════════════════════════════════

# define WHITE              0x00FFFFFF  // Blanc
# define BLACK              0x00000000  // Noir
# define RED                0x00FF0000  // Rouge
# define GREEN              0x0000FF00  // Vert
# define BLUE               0x000000FF  // Bleu
# define YELLOW             0x00FFFF00  // Jaune
# define CYAN               0x0000FFFF  // Cyan
# define MAGENTA            0x00FF00FF  // Magenta

// 🎨 Couleurs spéciales
# define DARK_GRAY          0x00404040  // Gris foncé
# define LIGHT_GRAY         0x00C0C0C0  // Gris clair
# define ORANGE             0x00FF8800  // Orange
# define PURPLE             0x008800FF  // Violet

//═══════════════════════════════════════════════════════════
// ⌨️ TOUCHES DE MOUVEMENT - WASD + FLÈCHES
//═══════════════════════════════════════════════════════════

# define KEY_W              119     // Avancer
# define KEY_A              97      // Strafe gauche  
# define KEY_S              115     // Reculer
# define KEY_D              100     // Strafe droite

# define KEY_UP             65362   // Flèche haut (avancer)
# define KEY_DOWN           65364   // Flèche bas (reculer)
# define KEY_LEFT           65361   // Flèche gauche (tourner)
# define KEY_RIGHT          65363   // Flèche droite (tourner)

//═══════════════════════════════════════════════════════════
// 🎯 TOUCHES DE CONTRÔLE SYSTÈME
//═══════════════════════════════════════════════════════════

# define KEY_ESC            65307   // Quitter le jeu
# define KEY_SPACE          32      // Action (ouvrir portes)
# define KEY_ENTER          65293   // Valider
# define KEY_TAB            65289   // Menu/Carte

//═══════════════════════════════════════════════════════════
// 🔄 TOUCHES DE ROTATION AVANCÉE
//═══════════════════════════════════════════════════════════

# define KEY_Q              113     // Tourner gauche (alt)
# define KEY_E              101     // Tourner droite (alt)

//═══════════════════════════════════════════════════════════
// 🏃‍♂️ TOUCHES MODIFICATRICES
//═══════════════════════════════════════════════════════════

# define KEY_SHIFT_L        65505   // Course (vitesse x2)
# define KEY_CTRL_L         65507   // Marche lente
# define KEY_ALT_L          65513   // Mode alt

//═══════════════════════════════════════════════════════════
// 🔢 TOUCHES FONCTIONNELLES
//═══════════════════════════════════════════════════════════

# define KEY_1              49      // Option 1
# define KEY_2              50      // Option 2  
# define KEY_3              51      // Option 3
# define KEY_4              52      // Option 4
# define KEY_5              53      // Option 5
# define KEY_M              109     // Map toggle
# define KEY_P              112     // Pause
# define KEY_R              114     // Reload/Reset

//═══════════════════════════════════════════════════════════
// 🎮 ÉVÉNEMENTS MLX LINUX
//═══════════════════════════════════════════════════════════

# define ON_KEYDOWN         2       // Touche pressée
# define ON_KEYUP           3       // Touche relâchée
# define ON_MOUSEDOWN       4       // Click souris
# define ON_MOUSEUP         5       // Release souris
# define ON_MOUSEMOVE       6       // Mouvement souris
# define ON_EXPOSE          12      // Redraw window
# define ON_DESTROY         17      // Fermeture fenêtre

//═══════════════════════════════════════════════════════════
// 🖱️ BOUTONS SOURIS LINUX
//═══════════════════════════════════════════════════════════

# define MOUSE_LEFT         1       // Click gauche
# define MOUSE_RIGHT        3       // Click droit
# define MOUSE_MIDDLE       2       // Molette
# define MOUSE_SCROLL_UP    4       // Scroll up
# define MOUSE_SCROLL_DOWN  5       // Scroll down

//═══════════════════════════════════════════════════════════
// 🎯 PARAMÈTRES RAYCASTING
//═══════════════════════════════════════════════════════════

# define TEXTURE_SIZE       64      // Taille textures (64x64)
# define NUM_TEXTURES       4       // Nombre de textures murs
# define RAY_PRECISION      0.01    // Précision du raycasting

//═══════════════════════════════════════════════════════════
// 📐 CONSTANTES MATHÉMATIQUES
//═══════════════════════════════════════════════════════════

# define PI                 3.14159265359
# define TWO_PI             6.28318530718
# define HALF_PI            1.57079632679
# define DEG_TO_RAD         0.01745329252   // π/180
# define RAD_TO_DEG         57.2957795131   // 180/π

//═══════════════════════════════════════════════════════════
// 🚨 CODES D'ERREUR
//═══════════════════════════════════════════════════════════

# define SUCCESS            0
# define ERROR_ARGS         1       // Mauvais arguments
# define ERROR_FILE         2       // Erreur fichier
# define ERROR_MAP          3       // Erreur carte
# define ERROR_TEXTURE      4       // Erreur texture
# define ERROR_MLX          5       // Erreur MLX
# define ERROR_MEMORY       6       // Erreur mémoire

//═══════════════════════════════════════════════════════════
// 🎮 LIMITES DU JEU
//═══════════════════════════════════════════════════════════

# define MAX_MAP_SIZE       100     // Taille max carte
# define MAX_SPRITES        50      // Nombre max sprites
# define MAX_FILENAME       256     // Longueur max nom fichier

#endif
