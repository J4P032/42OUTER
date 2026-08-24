NAME        = vulkantuto
CC          = c++
CFLAGS      = -Wall -Wextra -Werror -std=c++17

# Flags para silenciar advertencias del SDK externo
CFLAGS      += -Wno-nullability-completeness -Wno-unused-parameter -Wno-missing-field-initializers -Wno-missing-braces

# 1. Rutas del SDK de Vulkan
VULKAN_DIR  = /goinfre/jrollon-/scop_vulkan/1.3.296.0/x86_64
VULKAN_INC  = -isystem $(VULKAN_DIR)/include
# VITAL: Añadimos -lshaderc_combined para que reconozca las funciones de compilación de shaders
VULKAN_LIB  = -L $(VULKAN_DIR)/lib -lvulkan -lshaderc_combined -Wl,-rpath,$(VULKAN_DIR)/lib

# 2. Rutas de GLM y SDL3 locales
GLM_INC     = -I /goinfre/jrollon-/scop_vulkan/sources/glm
SDL_INC     = -I /goinfre/jrollon-/scop_vulkan/deps_local/include
SDL_LIB     = -L /goinfre/jrollon-/scop_vulkan/deps_local/lib -lSDL3 -Wl,-rpath,/goinfre/jrollon-/scop_vulkan/deps_local/lib

INCLUDES    = $(VULKAN_INC) $(GLM_INC) $(SDL_INC)
LIBS        = $(VULKAN_LIB) $(SDL_LIB)

# Limpiamos SRCS y OBJS: Eliminamos por completo volk.c/volk.o de aquí
SRCS        = src/main.cpp src/application.cpp src/utils.cpp
OBJS        = src/main.o src/application.o src/utils.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f src/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
