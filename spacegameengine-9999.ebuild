# Copyright 1999-2006 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

inherit games subversion

DESCRIPTION="A portable easy to use engine written in C++"
HOMEPAGE="http://spacegameengine.sourceforge.net/"
ESVN_REPO_URI="https://spacegameengine.svn.sourceforge.net/svnroot/spacegameengine"

LICENSE="LGPL-2"
SLOT="0"
KEYWORDS="~x86 ~amd64"
IUSE="debug devil dga openal opengl test truetype vorbis wave xinput zlib"

DEPEND="${RDEPEND}
        dev-util/pkgconfig
        dev-util/cmake"
RDEPEND="dev-libs/boost
         x11-libs/libX11
         virtual/libc
         virtual/libiconv
         opengl? (
             media-libs/glew
             x11-libs/libXxf86vm )
         devil? ( media-libs/devil )
         truetype? ( media-libs/freetype )
         xinput? ( dga? ( x11-libs/libXxf86dga ) )
         vorbis? ( media-libs/libvorbis )
         openal? ( media-libs/openal )
         zlib? ( media-libs/zlib )"

src_unpack() {
	subversion_src_unpack
	cd ${S}
}

src_compile() {
	local myconf=""

	if use debug; then
		myconf="${myconf} -D ENABLE_DEBUG:=1"
	fi

	if use devil; then
		myconf="${myconf} -D ENABLE_DEVIL:=1"
	fi

	if use dga; then
		myconf="${myconf} -D ENABLE_DGA:=1"
	fi

	if use opengl; then
		myconf="${myconf} -D ENABLE_OPENGL:=1"
	fi

	if use openal; then
		myconf="${myconf} -D ENABLE_OPENAL:=1"
	fi

	if use test; then
		myconf="${myconf} -D ENABLE_TEST:=1"
	fi

	if use truetype; then
		myconf="${myconf} -D ENABLE_FREETYPE:=1"
	fi

	if use vorbis; then
		myconf="${myconf} -D ENABLE_VORBIS:=1"
	fi

	if use wave; then
		myconf="${myconf} -D ENABLE_WAVE:=1"
	fi

	if use xinput; then
		myconf="${myconf} -D ENABLE_XINPUT:=1"
	fi

	cmake ${myconf} \
		-DCMAKE_C_FLAGS="${CFLAGS}" \
		-DCMAKE_CXX_FLAGS="${CXXFLAGS}" \
		-DCMAKE_INSTALL_PREFIX=/usr \
		. || die "cmake failed"

	emake || die "emake failed"
}

src_install() {
	emake DESTDIR=${D} install || die "emake install failed"
}
