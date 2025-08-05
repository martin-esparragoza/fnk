%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP $(INCFLAGS) -c $< -o $@ $(CLINK)

lib%.o: $(OBJFILES)
	$(LD) $(LDFLAGS) -r -o $@ $^ $(LDLINK)
	
%-intermediate.o: $(OBJFILES) $(LIBFILES)
	$(LD) -r $(LDFLAGS) -o $@ $(OBJFILES) $(LIBFILES) $(LDLINK)