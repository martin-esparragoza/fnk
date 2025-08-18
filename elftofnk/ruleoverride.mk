elftofnk/lib/%.o: elftofnk/lib/%.c
	@echo NATIVE!
	$(CCNATIVE) $(CNATIVEFLAGS) -MMD -MP $(INCFLAGS) -c $< -o $@ $(CNATIVELINK)

elftofnk/src/%.o: elftofnk/src/%.c $(LIBOBJFILES)
	@echo NATIVE!
	$(CCNATIVE) $(CNATIVEFLAGS) -MMD -MP $(INCFLAGS) $< -o $@ $(LIBOBJFILES) $(CNATIVELINK)