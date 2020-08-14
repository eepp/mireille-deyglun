# Copyright (c) 2020 Philippe Proulx <eepp.ca>
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# add main target
set (PROG_BASE_NAME mireille-deyglun)
add_executable (
	${PROG_BASE_NAME}
	mireille.cpp
)
target_compile_definitions (
	${PROG_BASE_NAME} PRIVATE
	-DF_CPU=${MD_MCU_FREQ}
)
target_compile_options (
	${PROG_BASE_NAME} PRIVATE
	-Wall -Wextra
	-fshort-enums
	-funsigned-bitfields
	-funsigned-char
	-mmcu=${MD_MCU_TYPE}
)
target_link_options (
	${PROG_BASE_NAME} PRIVATE
	-mmcu=${MD_MCU_TYPE}
)

# add hex file target (to program the MCU)
add_custom_target (
	${PROG_BASE_NAME}-hex ALL
	COMMAND
		"${CMAKE_OBJCOPY}" -j .text -j .data -O ihex ${PROG_BASE_NAME} ${PROG_BASE_NAME}.hex
	DEPENDS ${PROG_BASE_NAME}
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
)
