#include "test2.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;


Test2::Test2() {}

void Test2::_ready()
{
	UtilityFunctions::print("Hello world");
}

void Test2::_physics_process(double p_delta)
{
	test+=0.01;
	this->set_position(this->get_position()+(Vector3(sin(-test),cos(-test),sin(-test))/100));
}

void Test2::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_ready_cpp"), &Test2::_ready);
}
