NAME = scop
CHECKER = .scop

all: $(CHECKER)
	
$(CHECKER):
	mkdir -p build
	cd build && cmake .. && make
	cp build/$(NAME) .
	touch $(CHECKER)

clean:
	rm -rf build

fclean: clean
	rm -f $(NAME)
	rm -f $(CHECKER)

re: fclean all

.PHONY: all re clean fclean
