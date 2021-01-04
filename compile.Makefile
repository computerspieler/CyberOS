include $(CONFIG_MAKEFILE)

.PRECIOUS: $(OBJS) $(DEPS)

objs/%.s.o: src/%.s
	$(ECHO) AS $(patsubst objs/%,%,$@)
	$(MKDIR) objs
	$(AS) $(ASFLAGS) -o $@ $<

objs/%.c.o: src/%.c
	$(ECHO) CC $(patsubst objs/%,%,$@)
	$(MKDIR) objs
	$(CC) $(CCFLAGS) -o $@ $<

deps/%.c.d: src/%.c
	$(MKDIR) deps
	$(CC) $(CCFLAGS) -M -o $@ $< -MT $(patsubst src/%.c,objs/%.c.o,$<)

-include $(DEPS)

%.bin: $(OBJS)
	$(ECHO) LINK $(patsubst $(BINDIR)/%,%,$@)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

%.a: $(OBJS)
	$(ECHO) AR $(patsubst $(BINDIR)/%,%,$@)
	$(AR) $(ARFLAGS) $@ $(OBJS)

debug: build
release: build

clean:
	$(DEL) objs
	$(DEL) deps