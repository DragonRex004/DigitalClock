windres resource.rc -o resource.o

gcc main.c resource.o -o digital_clock.exe -I./raylib -L./raylib -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows

digital_clock.exe