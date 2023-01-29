#Name of the application
APPLICATION = CRYPTBENCH

#Which default board to use. The "?" allows to override this value
BOARD ?= native

#This is important! It tells the application where the RIOT-OS is
RIOTBASE ?= $(CURDIR)/RIOT

# Binds a directory to the build process and makes it available to RIOT
BIN_DIRS += algorithms
BIN_USEMODULE += algorithms
BIN_USEMODULE += $(APPLICATION_MODULE)
DIST_FILES += Makefile

AES_KEY_SIZE ?= 128 # Defines which key size is to be used. Can be overriden in the make command

USEMODULE += shell_commands # RIOT SHELL COMMANDS
USEMODULE += shell 			    # RIOT SHELL MODULE
USEMODULE += od				      # Object Dump: Used to present the encryption/decryption. Should only be used for debugging
USEMODULE += od_string		  # OD as String: Same as the od module
USEMODULE += random
USEMODULE += xtimer
USEMODULE += cipher_modes

ifneq ($(AES_KEY_SIZE),128)
  USEMODULE += crypto_aes_128	# AES Library
endif
ifneq ($(AES_KEY_SIZE),192)
  USEMODULE += crypto_aes_192	# AES Library
endif
ifneq ($(AES_KEY_SIZE),256)
  UUSEMODULE += crypto_aes_256	# AES Library
endif

CFLAGS += -DDEVELHELP=1

#Appends target specific values to variables
include $(RIOTBASE)/Makefile.include
