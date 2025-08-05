❯ valgrind --suppressions=mlx_suppressions.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3d maps/test_map/tets_map1.cub

==63770== Memcheck, a memory error detector
==63770== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==63770== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==63770== Command: ./cub3d maps/test_map/tets_map1.cub
==63770== 
🗺️ Loading map from: maps/test_map/tets_map1.cub
✅ File maps/test_map/tets_map1.cub opened successfully
✅ Floor color: 255,204,153
✅ Ceiling color: 102,178,250
✅ All parsing elements completed successfully
✅ Map loaded successfully!
🖼️ Loading textures...
✅ All textures loaded successfully!
==63770== 
==63770== HEAP SUMMARY:
==63770==     in use at exit: 95,002 bytes in 152 blocks
==63770==   total heap usage: 1,195 allocs, 1,043 frees, 958,110 bytes allocated
==63770== 
==63770== 112 bytes in 1 blocks are still reachable in loss record 34 of 71
==63770==    at 0x484DB80: realloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==63770==    by 0x1130AC: parse_map_line (parse_map.c:47)
==63770==    by 0x111928: process_line (parser.c:48)
==63770==    by 0x1119B3: parse_cub_file (parser.c:68)
==63770==    by 0x111A2B: load_map (parser.c:80)
==63770==    by 0x10FB6E: main (main.c:40)
==63770== 
==63770== 112 bytes in 1 blocks are still reachable in loss record 35 of 71
==63770==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==63770==    by 0x113258: build_final_map (parse_map.c:98)
==63770==    by 0x111A5F: load_map (parser.c:85)
==63770==    by 0x10FB6E: main (main.c:40)
==63770== 
==63770== 124 bytes in 4 blocks are still reachable in loss record 36 of 71
==63770==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==63770==    by 0x115B8C: ft_strdup (in /home/tazokami/Projets/Campus19/Cub3D/cub3d)
==63770==    by 0x1125DC: extract_path (parse_textures.c:38)
==63770==    by 0x1126D3: parse_texture_line (parse_textures.c:62)
==63770==    by 0x1118DE: process_line (parser.c:44)
==63770==    by 0x1119B3: parse_cub_file (parser.c:68)
==63770==    by 0x111A2B: load_map (parser.c:80)
==63770==    by 0x10FB6E: main (main.c:40)
==63770== 
==63770== 445 bytes in 14 blocks are still reachable in loss record 56 of 71
==63770==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==63770==    by 0x115B8C: ft_strdup (in /home/tazokami/Projets/Campus19/Cub3D/cub3d)
==63770==    by 0x112F6D: handle_line_copy (parse_map.c:20)
==63770==    by 0x113111: parse_map_line (parse_map.c:55)
==63770==    by 0x111928: process_line (parser.c:48)
==63770==    by 0x1119B3: parse_cub_file (parser.c:68)
==63770==    by 0x111A2B: load_map (parser.c:80)
==63770==    by 0x10FB6E: main (main.c:40)
==63770== 
==63770== 476 bytes in 14 blocks are still reachable in loss record 57 of 71
==63770==    at 0x4846828: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==63770==    by 0x1132A8: build_final_map (parse_map.c:104)
==63770==    by 0x111A5F: load_map (parser.c:85)
==63770==    by 0x10FB6E: main (main.c:40)
==63770== 
==63770== LEAK SUMMARY:
==63770==    definitely lost: 0 bytes in 0 blocks
==63770==    indirectly lost: 0 bytes in 0 blocks
==63770==      possibly lost: 0 bytes in 0 blocks
==63770==    still reachable: 1,269 bytes in 34 blocks
==63770==         suppressed: 93,733 bytes in 118 blocks
==63770== 
==63770== For lists of detected and suppressed errors, rerun with: -s
==63770== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 3 from 1)






FONCTION INTERDTE : new_lines = realloc(map_lines, sizeof(char *) * (count + 1));