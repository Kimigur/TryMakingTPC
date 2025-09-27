#include "test.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;


Test::Test()
{}

void Test::_ready()
{
	UtilityFunctions::print("Hello world");
}

void Test::_physics_process(double p_delta)
{
	test+=0.01;
    this->set_position(this->get_position()+(Vector3(cos(test),cos(test),sin(test))/100));
}

void Test::_bind_methods() {
	ClassDB::bind_method(D_METHOD("_ready_cpp"), &Test::_ready);
}
