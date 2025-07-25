/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Jpaulis <Jpaulis@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:23:39 by Jpaulis           #+#    #+#             */
/*   Updated: 2025/07/25 15:51:00 by Jpaulis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
#define STRUCT_H

#include <stdbool.h>


/* ============================================================================ */
/*                                 🎮 PLAYER                                   */
/*                            Joueur et ses attributs                          */
/* ============================================================================ */
typedef struct s_player {
	double x;               // Position X du joueur dans la map
	double y;               // Position Y du joueur dans la map
	double dir_x;           // Vecteur direction X (vers où regarde le joueur)
	double dir_y;           // Vecteur direction Y (vers où regarde le joueur)  
	double plane_x;         // Plan caméra X (perpendiculaire à dir, FOV)
	double plane_y;         // Plan caméra Y (généralement 0.66 pour FOV 60°)
	double move_speed;      // Vitesse de déplacement du joueur
	double rot_speed;       // Vitesse de rotation du joueur
	double angle;           // Angle de rotation actuel (en radians)
} t_player;


/* ============================================================================ */
/*                                 🗺️  MAP                                     */
/*                            Carte et textures                                */
/* ============================================================================ */
typedef struct s_map {
	char **grid;            // Grille 2D de la map ('0'=vide, '1'=mur, 'N'=spawn...)
	int width;              // Largeur de la map (nombre de colonnes)
	int height;             // Hauteur de la map (nombre de lignes)
	char *no_texture;       // Chemin texture pour mur Nord
	char *so_texture;       // Chemin texture pour mur Sud
	char *we_texture;       // Chemin texture pour mur Ouest
	char *ea_texture;       // Chemin texture pour mur Est
	int floor_color[3];     // Couleur sol [R, G, B]
	int ceiling_color[3];   // Couleur plafond [R, G, B]
} t_map;


/* ============================================================================ */
/*                                 🖼️  IMAGE                                   */
/*                          Buffer d'image pour MLX                            */
/* ============================================================================ */
typedef struct s_image {
	void *img;              // Pointeur image MLX
	char *img_data;         // Buffer de pixels (deprecated, utilise addr)
	char *addr;             // Adresse du buffer de pixels
	int bits_per_pixel;     // Bits par pixel (32 bits = 4 bytes/pixel ARGB)
	int line_length;        // Taille d'une ligne en bytes
	int endian;             // Ordre des bytes (0=little endian, 1=big endian)
} t_image;


/* ============================================================================ */
/*                                ⚡ RAYCAST                                   */
/*                         Données pour un rayon DDA                           */
/* ============================================================================ */
typedef struct s_raycast {
	// ---- 📐 Direction du rayon ----
	double ray_dir_x;       // Direction X du rayon (cosinus de l'angle)
	double ray_dir_y;       // Direction Y du rayon (sinus de l'angle)
	
	// ---- 🗺️ Position dans la grille ----
	int map_x;              // Case X actuelle dans la grille
	int map_y;              // Case Y actuelle dans la grille
	
	// ---- 📏 Distances DDA ----
	double delta_dist_x;    // Distance entre lignes verticales (abs(1/ray_dir_x))
	double delta_dist_y;    // Distance entre lignes horizontales (abs(1/ray_dir_y))
	double side_dist_x;     // Distance jusqu'à prochaine ligne verticale
	double side_dist_y;     // Distance jusqu'à prochaine ligne horizontale
	
	// ---- 🚶 Directions de marche ----
	int step_x;             // Direction de marche X (+1 ou -1)
	int step_y;             // Direction de marche Y (+1 ou -1)
	
	// ---- 🎯 Résultats de collision ----
	bool hit;               // true si un mur a été touché
	bool side;              // false=mur vertical (NS), true=mur horizontal (EW)
	double perp_wall_dist;  // Distance perpendiculaire au mur (pour hauteur)
	
	// ---- 🎨 Données pour le rendu ----
	int line_height;        // Hauteur de la ligne à dessiner à l'écran
	int draw_start;         // Pixel Y où commencer à dessiner le mur
	int draw_end;           // Pixel Y où finir de dessiner le mur
} t_raycast;


/* ============================================================================ */
/*                                 🎯 GAME                                     */
/*                          Structure principale du jeu                        */
/* ============================================================================ */
typedef struct s_game {
	void *mlx;              // Pointeur MLX (connexion au serveur graphique)
	void *win;              // Pointeur fenêtre MLX
	t_image img;            // Buffer d'image pour le rendu
	int win_width;          // Largeur de la fenêtre (ex: 800)
	int win_height;         // Hauteur de la fenêtre (ex: 600)
	t_player player;        // Données du joueur
	t_map map;              // Données de la carte
} t_game;

#endif
