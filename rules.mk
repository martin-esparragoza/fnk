%.o: %.c
	$(CC) $(CFLAGS) -MMD -MP $(INCFLAGS) -c $< -o $@ $(CLINK)

%.fnk: program_link.ld $(OBJFILES) $(UPPEROBJS)
	$(LD) $(LDFLAGS) -o $@ -T $< --start-group $(OBJFILES) $(UPPEROBJS) --end-group $(LDLINK)