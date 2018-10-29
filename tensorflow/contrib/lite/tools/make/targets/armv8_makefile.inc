# Settings for armv8
ifeq ($(TARGET),armv8)
  TARGET_ARCH := armv8l
  TARGET_TOOLCHAIN_PREFIX := aarch64-linux-gnu-

  ifeq ($(TARGET_ARCH), armv8l)
    CXXFLAGS += \
			-march=armv8-a \
      -funsafe-math-optimizations \
      -ftree-vectorize \
      -fPIC

    CCFLAGS += \
      -march=armv8-a \
      -funsafe-math-optimizations \
      -ftree-vectorize \
      -fPIC

    LDFLAGS := \
      -Wl,--no-export-dynamic \
      -Wl,--exclude-libs,ALL \
      -Wl,--gc-sections \
      -Wl,--as-needed
  endif
       
  LIBS := \
    -lstdc++ \
    -lpthread \
    -lm \
    -ldl

endif
