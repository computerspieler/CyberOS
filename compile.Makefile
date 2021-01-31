include $(BASEDIR)/config.Makefile

ifdef LIBDEP
	CCFLAGS+=$(patsubst %,-I$(BASEDIR)/libs/%/include,$(LIBDEP))
	LIBS+=$(patsubst %,$(BINDIR)/libs/%.a,$(LIBDEP))
	LIBS_TARGET=$(patsubst %,libs/%,$(LIBDEP))
endif

DEPS=$(patsubst src/%,deps/%.d,$(SRCS))
OBJS=$(patsubst src/%,objs/%.o,$(SRCS))

.PRECIOUS: $(OBJS) $(DEPS)

objs/%.s.o: src/%.s
	$(ECHO) AS $(patsubst objs/%,%,$@)
	$(MKDIR) $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

objs/%.c.o: src/%.c
	$(ECHO) CC $(patsubst objs/%,%,$@)
	$(MKDIR) $(dir $@)
	$(CC) $(CCFLAGS) -o $@ $<

deps/%.c.d: src/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CCFLAGS) -M -o $@ $< -MT $(patsubst src/%.c,objs/%.c.o,$<)

-include $(DEPS)

%.bin: $(OBJS) $(LIBS_TARGET)
	$(ECHO) LINK $(notdir $@)
	$(MKDIR) $(dir $@)
	$(LD) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

%.a: $(OBJS) $(LIBS_TARGET)
	$(ECHO) AR $(notdir $@)
	$(MKDIR) $(dir $@)
	$(AR) $(ARFLAGS) $@ $(OBJS) $(LIBS)

libs/%: $(BASEDIR)/libs/%/Makefile
	$(ECHO) BUILD $@
	@(cd $(BASEDIR)/$@; make $(BUILD_TYPE) OUTDIR=$(BINDIR)/$(dir $@))

debug: build
release: build

clean:
	$(DEL) objs
	$(DEL) deps