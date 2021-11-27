all:
	+$(MAKE) -C Grammar

clean:
	+$(MAKE) clean -C Grammar

mvp:
	+$(MAKE) -C Test_MVP

mvp_clean:
	+$(MAKE) clean -C Test_MVP

mvp_debug:
	+$(MAKE) debug -C Test_MVP