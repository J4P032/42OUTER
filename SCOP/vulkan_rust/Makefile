NAME = scop
CHECKER = .scop

# Definicion de contenido de Cargo.toml especial para Vulkan
define CARGO_TOML_CONTENT
[package]
name = "vulkan_rust"
version = "0.1.0"
edition = "2021"

[dependencies]
ash = "0.38"
vk-mem = "0.4.0"

[features]
default = ["sdl2"]
sdl2 = ["dep:sdl2"]

[dependencies.sdl2]
version = "0.36"
optional = true

#esto es para hacer que rust meta las variables para valgrind
#valgrind: RUST_BACKTRACE=1 valgrind --leak-check=full ./scop teapot.obj
[profile.dev]
debug = 2
split-debuginfo = "off"

endef
export CARGO_TOML_CONTENT

all: $(CHECKER)

$(CHECKER):
	clear
	@if [ ! -f Cargo.toml ]; then echo "$$CARGO_TOML_CONTENT" > Cargo.toml; fi
	cargo build
	mv target/debug/vulkan_rust ./$(NAME)
	@touch $(CHECKER)

clean:
	@if [ -f Cargo.toml ]; then cargo clean; fi

fclean: clean
	@-rm -f $(NAME)
	@-rm -f Cargo.lock Cargo.toml
	@-rm -f $(CHECKER)
	@-rm -rf target

re: fclean all

.PHONY: all re clean fclean
