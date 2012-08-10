#!/bin/sh

INCLUDE_BINARY="check_includes"

"${INCLUDE_BINARY}" include || exit

"${INCLUDE_BINARY}" src/include || exit

"${INCLUDE_BINARY}" alda/include || exit

"${INCLUDE_BINARY}" alda/src/include || exit

check_src() {
	"${INCLUDE_BINARY}" src/"$1"/include || exit
}

check_src cegui
check_src cg
check_src charconv
check_src config
check_src console
check_src font/bitmap
check_src font/draw
check_src image
check_src image2d
check_src input
check_src line_drawer
check_src media
check_src model/md3
check_src opencl
check_src parse
check_src plugin
check_src projectile
check_src renderer
check_src systems
check_src texture
check_src viewport

check_example() {
	"${INCLUDE_BINARY}" examples/"$1"/include || exit
	"${INCLUDE_BINARY}" examples/"$1"/src/include || exit
}

check_example rucksack/testbed

for i in src/plugins/* ; do
	if [[ -d "${i}" ]] ; then
		"${INCLUDE_BINARY}" "$i"/include || exit
	fi
done
