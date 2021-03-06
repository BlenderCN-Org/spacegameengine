# - Try to find Direct3D 9
# This module defines the following variables
#
#	D3D9_FOUND - True when Direct Input was found
#	D3D9_INCLUDE_DIRS - Include directory for Direct Input
#	D3D9_LIBRARIES - Libraries to link to

find_path(
	D3D9_INCLUDE_DIR
	d3d9.h
	HINTS
	"${D3D9_INCLUDEDIR}"
)

find_library(
	D3D9_LIBRARY
	NAMES d3d9
	HINTS
	"${D3D9_LIBRARYDIR}"
)

include(
	FindPackageHandleStandardArgs
)

find_package_handle_standard_args(
	D3D9
	DEFAULT_MSG
	D3D9_INCLUDE_DIR
	D3D9_LIBRARY
)

if(
	D3D9_FOUND
)
	set(
		D3D9_LIBRARIES
		"${D3D9_LIBRARY}"
	)

	set(
		D3D9_INCLUDE_DIRS
		"${D3D9_INCLUDE_DIR}"
	)
endif()

mark_as_advanced(
	D3D9_INCLUDE_DIR
	D3D9_LIBRARY
)
