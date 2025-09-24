#ifndef TEST2_H
#define TEST2_H

#include <godot_cpp/classes/node3d.hpp>
using namespace godot;

class Test2 : public Node3D
{
public:
	GDCLASS(Test2, Node3D);
	Test2();

public:
	void _ready();
	void _physics_process(double p_delta);

protected:
	static void _bind_methods();

private:
	real_t test = 0;
};

#endif // TEST2_H
