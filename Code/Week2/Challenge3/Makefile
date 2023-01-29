# name of your application
APPLICATION = example_aes_ctr_cmd

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= ${CURDIR}/../../../../RIOT

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

USEMODULE += shell			# RIOT Shell Modul
USEMODULE += shell_commands # RIOT Shell Commands
USEMODULE += crypto_aes_128		# Verschlüsselung mithilfe von AES
USEMODULE += od				# Object Dump
USEMODULE += od_string		# Object Dump String representation
USEMODULE += cipher_modes	# Um AES-CBC zu verwenden
USEMODULE += random			# Um einen zufälligen IV zu generieren

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
