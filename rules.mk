%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP $(INCFLAGS) -c $< -o $@ $(CLINK)

lib%.o: $(OBJFILES)
	$(LD) $(LDFLAGS) -r -o $@ $^ $(LDLINK)

%-intermediate.o: $(OBJFILES) $(LIBFILES)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJFILES) $(LIBFILES) $(LDLINK)

#out-native/%.o: %.c
#	$(CCNATIVE) $(CNATIVEFLAGS) -MMD -MP $(INCFLAGS) -c $< -o $@ $(CNATIVELINK)

#out-native/%.o: %.c $(LIBOBJFILES)
#	$(CCNATIVE) $(CNATIVEFLAGS) -MMD -MP $(INCFLAGS) $< -o $@ $(LIBOBJFILES) $(CNATIVELINK)