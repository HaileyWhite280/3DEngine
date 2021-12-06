#include "ModelComponent.h"
#include "CameraComponent.h"
#include "Object/Actor.h"
#include "Object/Scene.h"

namespace nc
{

	void ModelComponent::Update()
	{

	}

	void ModelComponent::Draw(Renderer* renderer)
	{
		//program->SetUniform("model", owner->transform.matrix);
		material->shader->SetUniform("model", owner->transform.matrix);
		auto actor = owner->scene->FindActor("camera");

		if (actor != nullptr)
		{
			//program->SetUniform("view", actor->GetComponent<CameraComponent>()->view);
			material->shader->SetUniform("view", actor->GetComponent<CameraComponent>()->view);
			//program->SetUniform("projection", actor->GetComponent<CameraComponent>()->projection);
			material->shader->SetUniform("projection", actor->GetComponent<CameraComponent>()->projection);
		}

		material->Set();
		model->Draw();
	}

	bool ModelComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool ModelComponent::Read(const rapidjson::Value& value)
	{
		return true;
	}
}