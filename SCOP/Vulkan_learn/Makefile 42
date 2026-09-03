NAME        = vulkantuto
CC          = c++
CFLAGS      = -Wall -Wextra -Werror -std=c++17

# Flags para silenciar advertencias del SDK externo
CFLAGS      += -Wno-nullability-completeness -Wno-unused-parameter -Wno-missing-field-initializers -Wno-missing-braces

# 1. Rutas del SDK de Vulkan (Comunes)
VULKAN_DIR  = /goinfre/jrollon-/scop_vulkan/1.3.296.0/x86_64
VULKAN_INC  = -isystem $(VULKAN_DIR)/include
VULKAN_LIB  = -L $(VULKAN_DIR)/lib -lvulkan -lshaderc_combined -Wl,-rpath,$(VULKAN_DIR)/lib

# 2. Rutas de GLM (Común)
GLM_INC     = -I /goinfre/jrollon-/scop_vulkan/sources/glm

# --- CONFIGURACIÓN CONDICIONAL DE SDL ---
# Por defecto usamos SDL3 (goinfre)
SDL_INC     = -I /goinfre/jrollon-/scop_vulkan/deps_local/include
SDL_LIB     = -L /goinfre/jrollon-/scop_vulkan/deps_local/lib -lSDL3 -Wl,-rpath,/goinfre/jrollon-/scop_vulkan/deps_local/lib

# Si el usuario escribe 'make sdl2', sobreescribimos las variables de SDL y añadimos la macro USING_SDL2
ifeq ($(MAKECMDGOALS),sdl2)
    SDL_INC  = -I /usr/include/SDL2
    SDL_LIB  = -lSDL2
    CFLAGS  += -DUSING_SDL2
endif

INCLUDES    = $(VULKAN_INC) $(GLM_INC) $(SDL_INC)
LIBS        = $(VULKAN_LIB) $(SDL_LIB)

SRCS        = src/main.cpp src/application.cpp src/utils.cpp
OBJS        = $(SRCS:.cpp=.o)

all: $(NAME)

# Regla específica para forzar la compilación con SDL2
sdl2: clean_objs $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Limpieza interna para evitar conflictos al saltar entre SDL2 y SDL3
clean_objs:
	rm -f src/*.o

clean: clean_objs

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all sdl2 clean clean_objs fclean re
