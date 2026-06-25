NAME = scop

all:
	mkdir -p build
	cd build && cmake .. && make
	cp build/$(NAME) .

clean:
	rm -rf build

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all re clean fclean
