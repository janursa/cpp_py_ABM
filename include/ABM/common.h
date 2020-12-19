#pragma once
#include <memory.h>
#include "pybind11/pybind11.h"
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
using namespace std;
namespace py = pybind11;


/** macros and helpers **/
template <typename T> std::string type_name();
#define TYPENAME(A) { std::cout<< #A; }
//#define DEBUG

#ifdef DEBUG
#define LOG(str) do { std::cout << str ; } while( false )
#else
#define LOG(str) do { } while ( false )
#endif
template<class ENV, class AGENT, class PATCH>
struct HATCH_CONFIG{
	HATCH_CONFIG (bool flag = false, 
		    shared_ptr<PATCH> _patch = nullptr, 
		    bool inherit = false,
		    bool quiet = false,
		    bool reset = false
		    ):
			_flag(flag),_patch(_patch),_inherit(inherit),
			_quiet(quiet),_reset(reset)
	{
		
	};
	bool _flag;
	shared_ptr<PATCH> _patch;
	bool _inherit;
	bool _quiet; //!< if it's throw, upon failure in moving, even due to patch unavailability, and exception will be thrown 
	bool _reset; //!< Reset upon failure in hatching. If false, the agent will try in the next steps again
};
template<class ENV, class AGENT, class PATCH>
struct MOVE_CONFIG{
	MOVE_CONFIG (bool flag = false, 
		    shared_ptr<PATCH> _patch = nullptr, 
		    bool quiet = false,
		    bool reset = false
		    ):
			_flag(flag),_patch(_patch), _quiet(quiet), _reset(reset)
	{};
	bool _flag;
	shared_ptr<PATCH> _patch;
	bool _quiet; //!< if it's throw, upon failure in moving, even due to patch unavailability, and exception will be thrown 
	bool _reset;
};
struct SWITCH_CONFIG{
	SWITCH_CONFIG (bool flag = false, 
		    string to = ""
		    ):
			_flag(flag),_to(to)
	{};
	bool _flag;
	string _to;
};
/** Exceptions **/
struct base_exception_class{
    base_exception_class(std::string msg):message(msg){}
    std::string message;
    const char *what() const throw() {
        return message.c_str();
    }
};
struct invalid_directory: public base_exception_class{
    using base_exception_class::base_exception_class;
};
struct convergence_error: public base_exception_class{
    using base_exception_class::base_exception_class;
};
struct patch_availibility: public base_exception_class{
    using base_exception_class::base_exception_class;
};
struct undefined_member: public base_exception_class{
    using base_exception_class::base_exception_class;
};


//** directories **//

const std::string main_output_folder = "outputs/";

