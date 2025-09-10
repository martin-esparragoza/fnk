elftofnk/lib/%.o: elftofnk/lib/%.c
	$(CCNATIVE) $(CNATIVEFLAGS) -MMD -MP $(INCFLAGS) -c $< -o $@ $(CNATIVELINK)

elftofnk/src/%.o: elftofnk/src/%.c $(LIBOBJFILES)
	$(CCNATIVE) $(CNATIVEFLAGS) -MMD -MP $(INCFLAGS) $< -o $@ $(LIBOBJFILES) $(CNATIVELINK)