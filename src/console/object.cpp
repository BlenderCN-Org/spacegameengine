#include <sge/console/object.hpp>
#include <sge/console/exception.hpp>
#include <sge/console/callbacks.hpp>
#include <sge/console/function.hpp>
#include <sge/console/var_base.hpp>
#include <sge/auto_ptr.hpp>
#include <sge/make_auto_ptr.hpp>
#include <sge/assert.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

sge::console::object::object(string::value_type const _prefix)
:
	prefix_(_prefix)
{
}

sge::signals::auto_connection sge::console::object::insert(
	string const &name,
	callback const &c,
	string const &description)
{
	if (funcs_.find(name) != funcs_.end())
		throw exception(SGE_TEXT("registered function \"")+name+SGE_TEXT("\" twice"));

	auto_ptr<
		function
	> sig(
		make_auto_ptr<
			function
		>(description));

	std::pair<function_map::iterator,bool> const ret = 
		funcs_.insert(
			name,
			sig);

	SGE_ASSERT(ret.second);

	return ret.first->second->signal().connect(c);
}

sge::signals::auto_connection sge::console::object::register_fallback(
	fallback const &c)
{
	return fallback_.connect(c);
}

namespace
{
template <typename Iterator>
struct eval_grammar : boost::spirit::qi::grammar<
	Iterator, 
	sge::console::arg_list()>
{
	typedef boost::spirit::ascii::space_type space_type;

	eval_grammar() : eval_grammar::base_type(start)
	{
		using boost::spirit::char_;
		using boost::spirit::ascii::space;

		word  %=           +(char_ - space);
		quoted_string %=    '"' >> +(char_ - '"') >> '"';
		argument %=        quoted_string | word;
		start %=           argument % (+space);
	}

	boost::spirit::qi::rule<Iterator, sge::string()> word;
	boost::spirit::qi::rule<Iterator, sge::string()> quoted_string;
	boost::spirit::qi::rule<Iterator, sge::string()> argument;
	boost::spirit::qi::rule<Iterator, sge::console::arg_list()> start;
};
}

void sge::console::object::eval(string const &sp)
{
	if (sp.empty())
		return;

	if (sp[0] != prefix_)
	{
		fallback_(sp);
		return;
	}

	string const s = sp.substr(1);

	arg_list args;
	eval_grammar<string::const_iterator> grammar;
	string::const_iterator beg = s.begin();

	boost::spirit::qi::parse(
		beg,
		s.end(),
		grammar,
		args);

	function_map::iterator i = funcs_.find(args[0]);

	if (i == funcs_.end())
		throw exception(SGE_TEXT("couldn't find command \"")+args[0]+SGE_TEXT("\""));

	i->second->signal()(args);
}

sge::console::variable_map const &sge::console::object::variables() const
{
	return vars_;
}

sge::console::variable_map &sge::console::object::variables()
{
	return vars_;
}

sge::console::function_map const &sge::console::object::functions() const
{
	return funcs_;
}

void sge::console::object::insert(var_base &o)
{
	if (vars_.find(o.name()) != vars_.end())
		throw exception(SGE_TEXT("registered function \"")+o.name()+SGE_TEXT("\" twice"));
	vars_[o.name()] = &o;
}

void sge::console::object::erase(var_base &o)
{
	SGE_ASSERT(vars_.find(o.name()) != vars_.end());
	vars_.erase(o.name());
}
