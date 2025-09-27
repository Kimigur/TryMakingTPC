#ifndef TEST_H
#define TEST_H

#include <godot_cpp/classes/node3d.hpp>
using namespace godot;

class Test : public Node3D {
	GDCLASS(Test, Node3D);
	Test();

public:
    void _ready() override;
    void _physics_process(double p_delta) override;

protected:
	static void _bind_methods();

private:
	real_t test = 0;
};

#endif // TEST_H
