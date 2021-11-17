#include "PhysicsComponent.h"
#include "Engine.h"

namespace nc
{
	void PhysicsComponent::Update()
	{
		velocity += acceleration * owner->scene->engine->time.deltaTime;
		owner->transform.position += velocity * owner->scene->engine->time.deltaTime;
		velocity *= drag;

		acceleration = glm::vec3{0};
	}

	bool PhysicsComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool PhysicsComponent::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, drag);
		JSON_READ(value, force);
		JSON_READ(value, velocity);
		JSON_READ(value, acceleration);

		return true;
	}
}