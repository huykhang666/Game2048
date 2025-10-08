#pragma once
#include "Utils.h"

//Lớp cơ sở: cho phép kế thừa
class GameObject {
public:
	virtual void render() const = 0;
	virtual void update() = 0;
	virtual ~GameObject() = default;
};