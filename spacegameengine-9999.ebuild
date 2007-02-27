# Copyright 1999-2006 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

inherit games subversion

DESCRIPTION="A portable easy to use engine written in C++"
HOMEPAGE="http://spacegameengine.sourceforge.net/"
ESVN_REPO_URI="https://spacegameengine.svn.sourceforge.net/svnroot/spacegameengine"

LICENSE="GPL-2"
SLOT="0"
KEYWORDS="~x86 ~amd64"
IUSE="opengl truetype devil xinput debug dga"

DEPEND="${RDEPEND}
        dev-util/scons"
RDEPEND="!games-engines/spacegame
         dev-libs/boost
         x11-libs/libX11
		 virtual/libc
		 media-fonts/corefonts
		 opengl? (
		 	media-libs/glew
			x11-libs/libXxf86vm )
         devil? ( media-libs/devil )
		 truetype? ( media-libs/freetype )
		 xinput? (dga? ( x11-libs/libXxf86dga ))"

pkg_setup() {
	if !(use opengl && use truetype && use devil && use xinput) ; then
		eerror "For now you have to enable all useflags to get a working
		engine!\nPlease do: \"games-engines/spacegameengine opengl truetype devil xinput\" >> /etc/portage/package.use"
		die
	fi
}

scons_enable() {
	if use $1; then
		echo "enable-$1=1"
	else
		echo "enable-$1=0"
	fi;
}

src_unpack() {
	subversion_src_unpack
	cd ${S}
}

src_compile() {
	scons destdir=${D} prefix=/usr libdir=$(get_libdir) cxxflags="${CXXFLAGS}" $(scons_enable debug) $(scons_enable dga) || die
}

src_install() {
	scons install destdir=${D} prefix=/usr libdir=$(get_libdir) cxxflags="${CXXFLAGS}" $(scons_enable debug) $(scons_enable dga) || die
}
