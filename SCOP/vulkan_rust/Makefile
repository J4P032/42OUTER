NAME = scop
CHECKER = .scop

all: $(CHECKER)
	

$(CHECKER):
	-cargo init
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
