all:
	@$(MAKE) -C src

clean:
	rm -rf remulator
	@$(MAKE) clean -C src
