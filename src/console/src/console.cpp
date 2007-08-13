// C++
#include <fstream>

// Boost
#include <boost/regex.hpp>
#include <boost/spirit.hpp>
#include <boost/bind.hpp>

// Eigenes
#include "../console.hpp"

void sge::con::singleton::read_config_file(const sge::con::string &filename)
{
	std::ifstream stream(filename.c_str());
	if (!stream.is_open())
		throw exception("Couldn't read config file \"" + filename + "\".\n");

	boost::regex expression("^([^=]+)=(.*)$", boost::regex::perl);
	while (!stream.eof())
	{
		sge::con::string line;
		std::getline(stream,line);

		boost::smatch results;
		if (!boost::regex_match(line,results,expression))
			continue;

		const string result1 = results[1];

		if (vars_.find(result1) == vars_.end())
			throw exception("Console variable \"" + results[1] + "\" not found!");

		vars_[result1]->set_string(results[2]);
	}
}

void sge::con::singleton::eval(const sge::con::string &line)
{
	using namespace boost::spirit;

	arg_list args;

	string command_str;
	string chat_str;

	// Grammatik
	rule<> argument = confix_p(ch_p('\''),(*anychar_p)[push_back_a(args)],ch_p('\'')) | 
										(+(~ch_p(' ')))[push_back_a(args)];
	rule<> arguments = (+ch_p(' ') >> argument >> arguments) | +ch_p(' ') | epsilon_p;
	rule<> command =   ch_p(prefix_) >> (+(~ch_p(' ')))[assign_a(command_str)] >> arguments;
	rule<> chat_line = ~ch_p(prefix_) >> (*anychar_p);
	rule<> r = chat_line[assign_a(chat_str)] | command;

	parse(line.c_str(),r);

	if (chat_str.length() > 0)
	{
		if (chat_callback_)
			chat_callback_(chat_str);
		return;
	}

	args.insert(args.begin(),command_str);
	if (funcs_.find(command_str) == funcs_.end())
		throw exception("Couldn't find function \"" + command_str + "\"!");

	funcs_[command_str](args);
}


sge::con::singleton &sge::con::instance()
{
	static singleton c;
	return c;
}

sge::con::var_base::var_base(const sge::con::string &name_) : name_(name_) 
{
	instance().add(name_,*this);
}

const sge::con::string &sge::con::var_base::name() const
{
	return name_;
}

sge::con::var_base::~var_base()
{
	instance().remove(name_);
}

sge::con::exception::exception(const sge::con::string& s)
: sge::exception(s)
{}

sge::con::singleton::singleton()
: prefix_('/')
{}

void sge::con::singleton::add(const string &function_name,function fn)
{
	if (funcs_.find(function_name) != funcs_.end())
		throw exception("A function with name \"" + function_name + "\" already exists!");
	funcs_[function_name] = fn;
}

void sge::con::singleton::add(const string &var_name,var_base &var) 
{ 
	if (vars_.find(var_name) != vars_.end())
		throw exception("A variable with name \"" + var_name + "\" already exists!");
	vars_[var_name] = &var; 
}

void sge::con::singleton::remove(const string &var_name)
{
	if (vars_.find(var_name) == vars_.end())
		throw exception("A variable with name \"" + var_name + "\" does not exist and thus cannot be removed!");
	vars_.erase(var_name);
}


sge::con::singleton::var_container &sge::con::singleton::vars()
{
	return vars_;
}

sge::con::singleton::func_container &sge::con::singleton::funcs()
{
	return funcs_;
}

sge::con::string::value_type sge::con::singleton::prefix() const
{
	return prefix_;
}

void sge::con::singleton::prefix(const string::value_type n)
{
	prefix_ = n;
}

void sge::con::singleton::chat_callback(const chat_callback_type& c)
{
	chat_callback_ = c;
}
