/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:01:44 by yoel              #+#    #+#             */
/*   Updated: 2023/03/31 18:12:04 by yridgway         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H
# include "minirt.h"

// # define WX 10
// # define WY 5
// # define IX 10
// # define IY 5
# define WX 800
# define WY 400
# define IX 800
# define IY 400
# define THREADS 20
// # define WX 1500
// # define WY 755
// # define IX 1250
// # define IY 750
# define BORDER 150
// # define WX 2000
// # define WY 1000
// # define IX 2000
// # define IY 1000
# define EXIT_ERROR -777
# define ADD_TO_MEM -666
# define EXIT_OK -555
# define FREE_ONE -444
# define SAVE_MLX -333
# define SAVE_FD -222
# define PI 3.1415926536
# define BUFFER_SIZE 10000

# define ESC 65307
# define DEL 65535
# define W 119
# define A 97
# define S 115
# define D 100
# define Q 113
# define E 101
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define PLUS 65451
# define MINUS 65453
# define SPACE 32
# define SHIFT 65505
# define CTRL 65507
# define R 114
# define T 116
# define ENTER 65293
# define OBJUP 65431
# define OBJDOWN 65433
# define OBJLEFT 65430
# define OBJRIGHT 65432
# define OBJFRONT 65436
# define OBJBEHIND 65429
# define I 105
# define O 111
# define J 106
# define K 107
# define N 110
# define M 109
# define C 99
# define H 104
# define Z 122
# define B 98
# define X 120
# define L 108

//error messages
# define TOO_MANY_CAPITALS "Too many capital letters in the scene"
# define MISSING_CAPITALS "Missing capital letters in the scene"
# define TOO_MANY_AMBIENTS "Too many ambient lights in the scene"
# define TOO_MANY_CAMERAS "Too many cameras in the scene"
# define MISSING_AMBIENT "Missing ambient light in the scene"
# define MISSING_CAMERA "Missing camera in the scene"
# define MISSING_LIGHT "Missing light in the scene"
# define CAPITAL_INSTRUCTIONS "\
\nAdd one (C)amera, one (A)mbient and at least one (L)ight in the scene"
# define CYLINDER_INSTRUCTIONS "\
\n(cy)linder: [name: 'cy', pos: (x,y,z), dir: (a,b,c), diameter, height, \
color: (r,g,b)] \
\ne.g. cy 0,0,0 0,1,0 3 8 255,0,0"
# define SPHERE_INSTRUCTIONS "\
\n(sp)here: [name: 'sp', pos: (x,y,z), diameter [-1000,1000], color: (r,g,b)] \
\ne.g. sp 0,0,0 3 255,0,0"
# define PLANE_INSTRUCTIONS "\
\n(pl)ane: [name: 'pl', pos: (x,y,z), dir: (a,b,c), color: (r,g,b)] \
\ne.g. pl 0,0,0 0,1,0 255,0,0"
# define CONE_INSTRUCTIONS "\
\n(co)ne: [name: 'co', pos: (x,y,z), dir: (a,b,c), diameter, height, \
color: (r,g,b)] \
\ne.g. co 0,0,0 0,1,0 3 8 255,0,0"
# define TRIANGLE_INSTRUCTIONS "\
\n(tr)iangle: [name: 'tr', pos1: (x,y,z), pos2: (a,b,c), pos3: (d,e,f), \
color: (r,g,b)] \
\ne.g. tr 0,0,0 0,1,0 0,0,1 255,0,0"
# define LIGHT_INSTRUCTIONS "\
\n(L)ight: [name: 'L', pos: (x,y,z), brightness: [0.0,1.0], color: (r,g,b)] \
\ne.g. l 0,0,0 0.5 255,0,0"
# define CAMERA_INSTRUCTIONS "\
\n(C)amera: [name: 'C', pos: (x,y,z), dir: (a,b,c), fov: [0-180]] \
\ne.g. c 0,0,0 0,1,0 90"
# define AMBIENT_INSTRUCTIONS "\
\n(A)mbient: [name: 'A' brightness: [0.0,1.0], color: (r,g,b)] \
\ne.g. a 0.5 255,0,0"
# define RGB_INSTRUCTIONS "\
\nRGB must be three integers between 0 and 255 and \
separated by commas: (r,g,b)\ne.g. 255,0,0"
# define RATIO_INSTRUCTIONS "\
\nRatio must be a floating point integer between 0 and 1 \
\ne.g. 0.5"
# define FOV_INSTRUCTIONS "\
\nFOV must be an integer between 0 and 180 \
\ne.g. 90"
# define POS_INSTRUCTIONS "\
\nPosition must be three floating point integers between -1000 and 1000 \
seperated by commas \
\ne.g. -24.5,15.433,20"
# define SIZE_INSTRUCTIONS "\
\nSize must be a floating point integer between 0 and 1000 \
\ne.g. 3.5"
# define NORMAL_INSTRUCTIONS "\
\nNormal must be three floating point integers between -1 and 1 seperated by \
commas, at least one value should be non-zero \
\ne.g. 0,1,-0.5"
# define OBJECT_INSTRUCTIONS "\
\nValid objects include: \
\n(C)amera, (L)ight, (A)mbient light, (sp)here, (pl)ane, (cy)linder and (co)ne \
\nValid options include: \
\n(mir)ror, (check)ered, (spec)ular, (bump)map"
# define OPTIONS_BEFORE_OBJECTS "At least one object must be defined before \
any options."
# define OPTION_INSTRUCTIONS "\
\nValid options include: \
\n(mir)ror, (check)ered, (spec)ular"
# define CHECK_INSTRUCTIONS "\
\n(check)ered: color:(r,g,b), density:[1-1000]\
\ne.g. check 255,0,0"
# define SPECULAR_INSTRUCTIONS "\
\n(spec)ular: intensity - [0.0-1.0], exponent - [1-1000] \
\ne.g. spec 0.5"
# define MIRROR_INSTRUCTIONS "\
\n(mir)ror: [0.0-1.0] \
\ne.g. mir 0.5"
# define BUMP_INSTRUCTIONS "\
\n(bump)map: [path to bmp file] \
\ne.g. bump ./textures/texture.bmp"
# define INVALID_FILE "Invalid file"
# define FILE_INSTRUCTIONS "\
\nPlease provide an existing file path, with the correct \
permissions and ending in '.rt'"
# define INVALID_OBJECT "Invalid object/option in the scene"
# define FILE_ERROR "Failed to open file"
# define CLEAN_EXIT "Program Exited Correctly :)"
# define INT_RANGE "All values must be between INT_MAX (-2147483648) and \
INT_MIN (2147483647)"
# define DOUBLE_RANGE "Double must have a precision of less than 15 digits"
# define NORMAL_RANGE "Normal must be between -1 and 1"
# define RGB_RANGE "RGB must be between 0 and 255"
# define FOV_RANGE "FOV must be between 0 and 180"
# define RATIO_RANGE "Ratio must be between 0 and 1"
# define POS_RANGE "Position must be between -1000 and 1000"
# define SIZE_RANGE "Size must be between 0 and 1000"

#endif