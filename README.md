
2. Still reachable
3. Rajouter texture mur en plus

STILL REACHABLE DANS NOTRE CODE : 

==25389== 338 bytes in 13 blocks are still reachable in loss record 54 of 70
==25389==    by 0x115B6C: ft_strdup (in /home/tazokami/Projets/Campus19/Cub3D/cub3d)
==25389==    by 0x112F53: handle_line_copy (parse_map.c:20)  ← TON CODE !!
==25389==    by 0x1130F7: parse_map_line (parse_map.c:55)   ← TON CODE !!

==25389== 338 bytes in 13 blocks are still reachable in loss record 55 of 70
==25389==    by 0x11328E: build_final_map (parse_map.c:104) ← TON CODE !!

==25389== 104 bytes in 1 blocks are still reachable in loss record 32 of 70
==25389==    by 0x113092: parse_map_line (parse_map.c:47)  ← TON CODE !!

==25389== 104 bytes in 1 blocks are still reachable in loss record 33 of 70
==25389==    by 0x11323E: build_final_map (parse_map.c:98) ← TON CODE !!
