/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/console/cursor.hpp>
#include <fcppt/text.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(cursor)
{
	sge::console::cursor c;
	
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("_"));
			
	BOOST_REQUIRE(
		c.edited(false) == 
			FCPPT_TEXT(" "));
	
	BOOST_REQUIRE(
		c.string() == 
			FCPPT_TEXT(""));
			
	BOOST_REQUIRE(
		c.empty());
	
	c.insert(
		FCPPT_TEXT('f'));
	c.insert(
		FCPPT_TEXT('o'));
	c.insert(
		FCPPT_TEXT('o'));
		
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("foo_"));
			
	BOOST_REQUIRE(
		c.edited(false) == 
			FCPPT_TEXT("foo "));
			
	BOOST_REQUIRE(
		c.string() == 
			FCPPT_TEXT("foo"));
	
	c.erase_word();
	
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("_"));
			
	BOOST_REQUIRE(
		c.edited(false) == 
			FCPPT_TEXT(" "));
			
	BOOST_REQUIRE(
		c.string() == 
			FCPPT_TEXT(""));
	
	c.string(
		FCPPT_TEXT("bar"));
		
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("bar_"));
			
	BOOST_REQUIRE(
		c.edited(false) == 
			FCPPT_TEXT("bar "));
			
	BOOST_REQUIRE(
		c.string() == 
			FCPPT_TEXT("bar"));
	
	c.left();
	c.left();
	c.left();
	c.left();
	
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("_ar "));
			
	BOOST_REQUIRE(
		c.edited(false) == 
			FCPPT_TEXT("bar "));
			
	BOOST_REQUIRE(
		c.string() == 
			FCPPT_TEXT("bar"));
	
	c.erase_char();
	
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("_r "));
			
	BOOST_REQUIRE(
		c.edited(false) == 
			FCPPT_TEXT("ar "));
			
	BOOST_REQUIRE(
		c.string() == 
			FCPPT_TEXT("ar"));
	
	c.erase_char();
	c.erase_char();
	c.erase_char();
	
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("_"));
			
	BOOST_REQUIRE(
		c.edited(false) == 
			FCPPT_TEXT(" "));
			
	BOOST_REQUIRE(
		c.string() == 
			FCPPT_TEXT(""));
	
	c.string(
		FCPPT_TEXT("foo"));
	
	c.left();
	c.left();
	
	c.insert(
		FCPPT_TEXT('b'));
		
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("fb_o "));
			
	BOOST_REQUIRE(
		c.edited(false) == 
			FCPPT_TEXT("fboo "));
			
	BOOST_REQUIRE(
		c.string() == 
			FCPPT_TEXT("fboo"));
	
	c.left();
	
	c.insert(
		FCPPT_TEXT('r'));
		
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("fr_oo "));
			
	BOOST_REQUIRE(
		c.edited(false) == 
			FCPPT_TEXT("frboo "));
			
	BOOST_REQUIRE(
		c.string() == 
			FCPPT_TEXT("frboo"));
	
	c.right();
	c.right();
	c.right();
	c.right();
	c.right();
	c.right();
	c.right();
	
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("frboo_"));
			
	BOOST_REQUIRE(
		c.edited(false) == 
			FCPPT_TEXT("frboo "));
			
	BOOST_REQUIRE(
		c.string() == 
			FCPPT_TEXT("frboo"));
	
	c.to_start();
	
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("_rboo "));
			
	BOOST_REQUIRE(
		c.edited(false) == 
			FCPPT_TEXT("frboo "));
			
	BOOST_REQUIRE(
		c.string() == 
			FCPPT_TEXT("frboo"));
			
	BOOST_REQUIRE(
		c.at_start());
	
	c.to_end();
	
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("frboo_"));
			
	BOOST_REQUIRE(
		c.edited(false) == 
			FCPPT_TEXT("frboo "));
			
	BOOST_REQUIRE(
		c.string() == 
			FCPPT_TEXT("frboo"));
	
	c.string(
		FCPPT_TEXT("foo bar"));
	c.left();
	c.left();
	c.left();
	c.left();
	c.erase_word();
	
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("_bar "));
			
	BOOST_REQUIRE(
		c.edited(false) == 
			FCPPT_TEXT(" bar "));
			
	BOOST_REQUIRE(
		c.string() == 
			FCPPT_TEXT(" bar"));
			
	c.erase_word();
	
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("_bar "));
			
	BOOST_REQUIRE(
		c.edited(false) == 
			FCPPT_TEXT(" bar "));
			
	BOOST_REQUIRE(
		c.string() == 
			FCPPT_TEXT(" bar"));
	
	c.string(
		FCPPT_TEXT("foo"));
	c.left();
	c.left();

	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("f_o "));

	c.insert(
		FCPPT_TEXT('a'));
	
	BOOST_REQUIRE(
		c.edited(true) == 
			FCPPT_TEXT("fa_o "));
}
